#pragma once
#include<iostream>
#include<cstdio>
#include<cstring>
#include <curl/curl.h>
#include <curl/easy.h>
#include<cstdlib>
#include<v8.h>
#include <v8-debug.h>
#include <pthread.h>
#include"XMLHttpRequest.h"

using namespace std;
using namespace v8;


 static	int my_trace(CURL *handle, curl_infotype type,char *data, size_t size,void *userp)
  {
	 cout<<"inside my_trace";
	 const char *text;
    (void)handle;
    string temp_data;
    temp_data.append(data, size);
    cout<<temp_data.c_str();
    return 0;
  }


size_t  WriteHeaderCallback(char *contents, size_t size, size_t nmemb, void *this_pointer)
{
	 //cout<<"writeheadercallback()\n";

	 string temp_data;
	 //cout<<"checkpoint -1";
   temp_data.append(contents, size * nmemb);
   //cout<<"checkpoint 0";
   if(temp_data.size()!=0)
   {
     XMLHttpRequest *xml=static_cast<XMLHttpRequest*>(this_pointer);
    // cout<<"checkpoint 1";
     if(temp_data.find("HTTP")==0)
     {
   	  //cout<<"checkpoint 2";
   	  string xstr =temp_data.substr(9,3);
   	       //cout<<xstr.c_str());
   	   xml->status=atoi(xstr.c_str());
   	   //cout<<"checkpoint 3";
     }
     xml->responseHeader+=temp_data;
   }

   return size * nmemb;
}

size_t  WriteBodyCallback(void *contents, size_t size, size_t nmemb, void *responseBody)
{
	//cout<<"writebodycallback()\n";

    XMLHttpRequest *xml=static_cast<XMLHttpRequest*>(responseBody);

    xml->responseText.append((char*)contents, size * nmemb);

     //cout<<response->responseText.c_str());

   return size * nmemb;
}




bool network_call(XMLHttpRequest *request)
{
	//cout<<"entering network_call()\n";
	//Response *res=new Response();
	CURL *curl_handle;
	  curl_global_init(CURL_GLOBAL_ALL);
	  curl_handle = curl_easy_init();
	  if(curl_handle){
	  curl_easy_setopt(curl_handle, CURLOPT_URL, request->site_URL.c_str());

	  if(request->type_of_request.compare("POST")==0)
	  		curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, request->Payload.c_str());

	  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteBodyCallback);
	  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, request);

	  curl_easy_setopt(curl_handle,CURLOPT_SSL_VERIFYPEER,false);

	  curl_easy_setopt(curl_handle, CURLOPT_HEADERFUNCTION, WriteHeaderCallback);
	  curl_easy_setopt(curl_handle, CURLOPT_HEADERDATA, request);

		curl_easy_setopt(curl_handle, CURLOPT_DEBUGFUNCTION, my_trace);

	  curl_easy_perform(curl_handle);

	  request->readyState=3;
	  curl_easy_cleanup(curl_handle);

	  return true;
	  }


	  return false;
}
