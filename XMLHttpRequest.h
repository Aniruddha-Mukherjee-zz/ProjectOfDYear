#pragma once
#include<cstdio>
#include<iostream>
#include<v8.h>
#include <v8-debug.h>
#include <pthread.h>

//#include"XMLHttpRequest.cpp"
using namespace std;
using namespace v8;

#define LOG(...) 	 //cout<<
#define LOGI(...) 	 //cout<<

void exposeXMLHttpRequest( Handle<ObjectTemplate> global );


class XMLHttpRequest{

public:
		string type_of_request,site_URL,requestHeader,Payload,responseHeader,responseText;
		//string Content_type;
		bool is_asynchronous;
		Persistent<Function> onreadystatechange;

		int readyState,status;

	    void open(string type,string reqURL,bool async);
	    void setRequestHeader(string label,string value );
	    void set_payload(string x);

	      /*
	      readyState = 0 After you have created the XMLHttpRequest object, but before you have called the open() method.
	      readyState = 1 After you have called the open() method, but before you have called send().
	      readyState = 2 After you have called send().
	      readyState = 3 After the browser has established a communication with the server, but before the server has completed the response.
	      readyState = 4 After the request has been completed, and the response data has been completely received from the server.
	      */
//public:

		  XMLHttpRequest() {
			  //cout<<"XMLHttpRequest() Constructor\n";

			  readyState=0; is_asynchronous=false;
			  status=404;
				//onreadystatechange=NULL;
		  	  }

	      const string& getresponseText() const {
	    	  return responseText;
	      	  }


	      	int getreadyState() const {
	      		return readyState;
	      	}



	      	const string& getResponseHeader() const {
	      		return responseHeader;
	      	}


	      	int getStatus() const {
	      		return status;
	      	}


	      	void setStatus(int status) {
	      		this->status = status;
	      	}

	      	void send( );

       static Handle<Value>getresponseTextCallback(Local<String> property,const AccessorInfo& info);
	   //static void SetresponseTextCallback(Local<String> property,Local<Value> value,Arguments& args);

	   static Handle<Value>getresponseHeaderCallback(Local<String> property,const AccessorInfo& info);
	   //static void SetresponseHeaderCallback(Local<String> property,Local<Value> value,Arguments& args);

	   static Handle<Value>getreadyStateCallback(Local<String> property,const AccessorInfo& info);
	   //static void setreadyStateCallback(Local<String> property,Local<Value> value,Arguments& args);

	   static Handle<Value>getstatusCallback(Local<String> property,const AccessorInfo& info);
	   //static void setstatusCallback(Local<String> property,Local<Value> value,Arguments& args);

	   //static Handle<Value>getonreadystatechangeCallback(Local<String> property,const Arguments& info);
	   static void setonreadystatechangeCallback(Local<String> property,Local<Value> value,const AccessorInfo& args);

	   static void openCallback(const v8::Arguments& args);
	   static void sendCallback(const v8::Arguments& args);
	   static void setRequestHeaderCallback(const v8::Arguments& args);
	   //static void wrapperCallback(const v8::Arguments& args);
};


Handle<Value> XMLHttpRequestConstructor(const Arguments &args)
{
	//std::cout<<"XMLHttpRequest()\n";

			  Locker lock;
        HandleScope scope;
        {
               //Create a c++ instance of this type,

            XMLHttpRequest *XMLHttpRequestClassObject = new XMLHttpRequest(  );
                //Create a JS version and store the pointer inside
            Persistent<Object> self = Persistent<Object>::New( args.Holder() );
                //Note that this index 0 is the internal field we created in the template!
            self->SetInternalField(0, v8::External::New( XMLHttpRequestClassObject ));
            return scope.Close( self );
        }
            //Not a valid constructor call, so undefined is returned.
        return Undefined();
}


void exposeXMLHttpRequest( Handle<ObjectTemplate> global ) {

	Locker lock;
	HandleScope scope;

					//Create the function template for the constructor, and point it to our constructor,
					//you can see this function inside XMLHttpRequest.cpp
		Persistent<FunctionTemplate>	 XMLHttpRequestTemplate = Persistent<FunctionTemplate>::New( FunctionTemplate::New( XMLHttpRequestConstructor ) );

					//We can tell the scripts what type to report. In this case, just XMLHttpRequest will do.
		 XMLHttpRequestTemplate->SetClassName(String::New("XMLHttpRequest"));

					//This template is the unique properties of this type, we can set
					//functions, getters, setters, and values directly on each new XMLHttpRequest() object.
		Handle<ObjectTemplate> XMLHttpRequestIT = XMLHttpRequestTemplate->InstanceTemplate();

					//Again, this is to store the c++ object for use in callbacks.
		XMLHttpRequestIT->SetInternalFieldCount(1);

XMLHttpRequestIT->SetAccessor(String::New("responseText"),AccessorGetter(XMLHttpRequest::getresponseTextCallback),AccessorSetter(NULL));
XMLHttpRequestIT->SetAccessor(String::New("responseHeader"),AccessorGetter(XMLHttpRequest::getresponseHeaderCallback),AccessorSetter(NULL));
XMLHttpRequestIT->SetAccessor(String::New("readyState"),AccessorGetter(XMLHttpRequest::getreadyStateCallback),AccessorSetter(NULL));
XMLHttpRequestIT->SetAccessor(String::New("status"),AccessorGetter(XMLHttpRequest::getstatusCallback),AccessorSetter(NULL));
XMLHttpRequestIT->SetAccessor(String::New("onreadystatechange"),AccessorGetter(NULL),AccessorSetter(XMLHttpRequest::setonreadystatechangeCallback));



XMLHttpRequestIT->Set( String::New("open"), FunctionTemplate::New( InvocationCallback( XMLHttpRequest::openCallback ) ));
XMLHttpRequestIT->Set( String::New("send"), FunctionTemplate::New( InvocationCallback( XMLHttpRequest::sendCallback ) ));
XMLHttpRequestIT->Set( String::New("setRequestHeader"), FunctionTemplate::New( InvocationCallback( XMLHttpRequest::setRequestHeaderCallback ) ));
       global->Set( String::New("XMLHttpRequest"), XMLHttpRequestTemplate );
 }
