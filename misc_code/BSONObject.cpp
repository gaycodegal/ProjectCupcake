//
//  BSONObject.cpp
//  Cupcake-Mac
//
//  Created by Steph on 1/3/17.
//
//

#include "BSONObject.hpp"



BSONvalue::BSONvalue(){
        type = 2;
        data._int = 0;
    }
    BSONvalue::BSONvalue(int type, BSONdata data):type(type),data(data){
        
    }
    void BSONvalue::changeTo(int type, BSONdata data, bool doDelete){
        if(doDelete && this->type >= 16){
            if(this->type == 18)
                delete data._array;
            else if(this->type == 32)
                delete data._object;
        }
        this->type =type;
        this->data = data;
    }
    void BSONvalue::deleteData(){
        if(this->type == 18)
            delete data._array;
        else if(this->type == 32)
            delete data._object;
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
                if(i != m)
                    stream << ",\n";
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
            m->data._uint = array->getUint8();
            return m;
        case 6:
            m->data._uint = array->getUint16();
            return m;
        case 7:
            m->data._uint = array->getUint32();
            return m;
        case 8:
            m->data._int = array->getInt8();
            return m;
        case 9:
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
