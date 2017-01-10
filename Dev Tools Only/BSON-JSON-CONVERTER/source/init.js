

var textareaJSON = jl.make("textarea");
textareaJSON.rows = 15;
textareaJSON.cols = 80;
var doc = document.body;

var f = jl.make("button");
f.innerHTML = "open a bson file";
jl.bindFileOpen(f,jl.readbin(function(c){
  textareaJSON.value = JSON.stringify(BSON.parse(c));
}));
jl.append(doc,f);
jl.append(doc,jl.divCT("","type json here:"));
jl.append(doc,textareaJSON);
jl.append(doc,jl.divCT("","bson will download when you click this"));
var b = jl.make("button");
b.innerHTML = "download as bson";
b.onclick = function(){
  console.log(textareaJSON.value);
  try{
  BSON.stringify_array(JSON.parse(textareaJSON.value)).download("download.bson");
  }catch(e){
    alert("error! see console for more");
    console.log(e);
  }
};
jl.append(doc,b);
