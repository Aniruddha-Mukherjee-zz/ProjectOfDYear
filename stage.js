var ajax= new XMLHttpRequest();
ajax.open("GET","http://httpbin.org/get",true);
ajax.onreadystatechange=function ()
{
  //print("Printed from JS anonymous defined in JS source code ");
  if(ajax.readyState==4  &&  ajax.status==200)
  print(ajax.responseText);
  //print(ajax.responseHeader);

};

ajax.send();
