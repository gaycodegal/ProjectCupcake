//
//  BSONObject.cpp
//  Cupcake-Mac
//
//  Created by Steph on 1/3/17.
//
//

#include "BSONObject.hpp"


/**
 
 */
BSONvalue::BSONvalue(){
    type = 2;
    data._int = 0;
}

BSONvalue::BSONvalue(int32_t number){
    type = 10;
    data._int = number;
}

BSONvalue::BSONvalue(uint32_t number){
    type = 7;
    data._int = number;
}

/**
 
 */
BSONvalue::BSONvalue(int type, BSONdata data):type(type),data(data){
    
}

void BSONvalue::changeTo(int type, BSONdata data, bool doDelete){
    if(doDelete && this->type >= 16){
        deleteData();
    }
    this->type =type;
    this->data = data;
}

void BSONvalue::deleteData(){
    if(this->type == 18){
        GrowArray<BSONvalue *> * array = data._array;
        for(int i = 0, m = array->count(); i < m; ++i){
            array->get(i)->deleteData();
        }
        array->drain();
        delete array;
    }else if(this->type == 32){
        HashMap<BSONvalue *> * object = data._object;
        int at = 0;
        char * key;
        for(int i = 0, m = object->count(); i < m; ++i){
            object->getAfter(at, key)->deleteData();
        }
        object->drain();
        delete object;
    }
}

BSONvalue::~BSONvalue(){
    
}


void asPretty(BSONvalue * val, std::stringstream & stream);

std::string * asPretty(BSONvalue * val){
    std::stringstream stream;
    asPretty(val, stream);
    std::string * ret = new std::string(stream.str());
    return ret;
}

void asPretty(BSONvalue * val, std::stringstream & stream){
    switch (val->type) {
        case 1:
            stream << "null";
            return;
        case 2:
            stream << "undefined";
            return;
        case 3:
            stream << "true";
            return;
        case 4:
            stream << "false";
            return;
        case 5:
            stream << val->data._uint;
            return;
        case 6:
            stream << val->data._uint;
            return;
        case 7:
            stream << val->data._uint;
            return;
        case 8:
            stream << val->data._int;
            return;
        case 9:
            stream << val->data._int;
            return;
        case 10:
            stream << val->data._int;
            return;
        case 11:
            stream << val->data._float;
            return;
        case 16:
            stream << val->data._string;
            return;
        case 18:
        {
            GrowArray<BSONvalue *> * array = val->data._array;
            stream << "[";
            for(int i = 0, m = array->count(); i < m; ++i){
                asPretty(array->get(i), stream);
                stream << ",";
            }
            stream << "]";
            return;
        }
        case 32:
        {
            HashMap<BSONvalue *> * object = val->data._object;
            stream << "{";
            int at = 0;
            char * key;
            BSONvalue * v;
            for(int i = 0, m = object->count(); i < m; ++i){
                v = object->getAfter(at, key);
                ++at;
                stream << '"' << key << "\": ";
                asPretty(v, stream);
                if(i + 1 != m)
                    stream << ',';
            }
            stream << "}";
            return;
        }
    }
}

BSONvalue * parseBSON(CharArray * array){
    BSONvalue * m = new BSONvalue();
    m->type = array->getUint8();
    switch (m->type) {
        case 1:
            m->data._int = 0;
            return m; // NULL
        case 2:
            m->data._int = 0;
            return m; // undefined
        case 3:
            m->data._int = 1;
            return m; // true
        case 4:
            m->data._int = 0;
            return m; // false
        case 5:
            m->type = 10;
            m->data._int = array->getUint8();
            return m;
        case 6:
            m->type = 10;
            m->data._uint = array->getUint16();
            return m;
        case 7:
            m->data._uint = array->getUint32();
            return m;
        case 8:
            m->type = 10;
            m->data._int = array->getInt8();
            return m;
        case 9:
            m->type = 10;
            m->data._int = array->getInt16();
            return m;
        case 10:
            m->data._int = array->getInt32();
            return m;
        case 11:
            m->data._float = array->getFloat();
            return m;
        case 12:
            m->data._int = 0;
            return m; //not a thing yet;
        case 16:
        {
            BSONvalue * len = parseBSON(array);
            m->data._string = array->getString(len->data._int);
            delete len;
            return m;
        }
        case 18:
        {
            BSONvalue * len = parseBSON(array);
            int l = len->data._int;
            delete len;
            GrowArray<BSONvalue *> * ary = new GrowArray<BSONvalue *>(l);
            for (int i = 0; i < l; ++i) {
                ary->push(parseBSON(array));
            }
            m->data._array = ary;
            return m;
        }
        case 32:
        {
            BSONvalue * len = parseBSON(array);
            int l = len->data._int;
            delete len;
            HashMap<BSONvalue *> * entries = new HashMap<BSONvalue *>(l * 2, NULL);
            
            for(int i = 0; i < l; ++i){
                BSONvalue * key = parseBSON(array);
                entries->put(key->data._string->c_str(), parseBSON(array));
                key->deleteData();
                delete key;
            }
            m->data._object = entries;
            return m;
        }
            
    }
    return NULL;
}

int formattedBSONLength(BSONvalue * value){
    int r = 1; // type
    switch (value->type) {
        case 1:
            return r; //NULL
        case 2:
            return r; // undefined
        case 3:
            return r; // true
        case 4:
            return r; // false
        case 5:
            return r + 1; // uint8
        case 6:
            return r + 2; // uint16
        case 7:
            return r + 4; // uint32
        case 8:
            return r + 1; // int8
        case 9:
            return r + 2; // int16
        case 10:
            return r + 4; // int32
        case 11:
            return r + 4; // float
        case 12:
            return r; //not a thing yet;
        case 16:
        {
            std::string * s = value->data._string;
            int len = (int)s->length();
            BSONvalue * temp = new BSONvalue(len);
            r += formattedBSONLength(temp);
            delete temp;
            r += len;
            return r;
        }
        case 18:
        {
            GrowArray<BSONvalue *> * array = value->data._array;
            BSONdata data;
            int len = array->count();
            data._int = len;
            BSONvalue * temp = new BSONvalue(len);
            r += formattedBSONLength(temp);
            delete temp;
            
            for (int i = 0; i < len; ++i) {
                r += formattedBSONLength(array->get(i));
            }
            return r;
        }
        case 32:
        {
            
            HashMap<BSONvalue *> * object = value->data._object;
            BSONdata data;
            int len = object->count();
            data._int = len;
            BSONvalue * temp = new BSONvalue(len);
            r += formattedBSONLength(temp);
            
            int at = 0;
            char * key;
            std::string * tempstr;
            BSONvalue * v;
            for(int i = 0, m = object->count(); i < m; ++i){
                v = object->getAfter(at, key);
                ++at;
                tempstr = new std::string(key);
                data._string = tempstr;
                temp->changeTo(16, data, true);
                r += formattedBSONLength(temp);
                r += formattedBSONLength(v);
                delete tempstr;
            }
            temp->deleteData();
            delete temp;
            return r;
        }
            
    }
    return NULL;
}


void formattedBSON(BSONvalue * value, CharArray * array){
    array->writeUint8(value->type);
    switch (value->type) {
        case 1:
            return; //NULL
        case 2:
            return; // undefined
        case 3:
            return; // true
        case 4:
            return; // false
        case 5:
            array->writeUint8(value->data._uint);
            return; // uint8
        case 6:
            array->writeUint16(value->data._uint);
            return; // uint16
        case 7:
            array->writeUint32(value->data._uint);
            return; // uint32
        case 8:
            array->writeInt8(value->data._int);
            return; // int8
        case 9:
            array->writeInt16(value->data._int);
            return; // int16
        case 10:
            array->writeInt32(value->data._int);
            return; // int32
        case 11:
            array->writeFloat(value->data._float);
            return; // float
        case 12:
            return; //not a thing yet;
        case 16:
        {
            std::string * s = value->data._string;
            BSONvalue * temp = new BSONvalue((int)s->length());
            formattedBSON(temp, array);
            delete temp;
            array->writeString(s);
            return;
        }
        case 18:
        {
            GrowArray<BSONvalue *> * ary = value->data._array;
            int len = ary->count();
            BSONvalue * temp = new BSONvalue(len);
            formattedBSON(temp, array);
            delete temp;
            
            for (int i = 0; i < len; ++i) {
                formattedBSON(ary->get(i), array);
            }
            return;
        }
        case 32:
        {
            
            HashMap<BSONvalue *> * object = value->data._object;
            BSONdata data;
            int len = object->count();
            BSONvalue * temp = new BSONvalue(len);
            formattedBSON(temp, array);
            
            int at = 0;
            char * key;
            std::string * tempstr;
            BSONvalue * v;
            for(int i = 0, m = object->count(); i < m; ++i){
                v = object->getAfter(at, key);
                ++at;
                tempstr = new std::string(key);
                data._string = tempstr;
                temp->changeTo(16, data, true);
                formattedBSON(temp, array);
                formattedBSON(v, array);
                delete tempstr;
            }
            temp->deleteData();
            delete temp;
            return;
        }
            
    }
    return;
}
