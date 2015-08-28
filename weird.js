
//print("56");
function myCallback2()
{
  //print("yo");
  print("Printed from JS callback function2 defined in JS source code: ");
}



var delta= new XMLHttpRequest();
delta.open("POST","https://www.example.org/",true);
delta.onreadystatechange=function ()
{
  //print("Printed from JS anonymous defined in JS source code ");
  if(delta.readyState==4  &&  delta.status==200)
  print(delta.responseText);
  //print(delta.responseHeader);

};
//delta.onreadystatechange=myCallback2;
delta.send();
