#pragma once
#include<cstdio>
#include<cstring>
//#include <curl/curl.h>
//#include <curl/easy.h>
#include<cstdlib>
#include<v8.h>
#include <v8-debug.h>

#include "curl_network_call.h"

//#include"XMLHttpRequest.h"



using namespace std;
using namespace v8;


XMLHttpRequest* UnwrapXMLHttpRequest( const AccessorInfo& info )
			 {
						//cout<<"UnwrapXMLHttpRequest()\n";
							 //Get the self object,
					 Local<v8::Object> self = info.Holder();
							 //Fetch the c++ pointer.
				 Local<External> external = Local<External>::Cast( self->GetInternalField(0) );
							 //Get back to the type.
				 XMLHttpRequest* xml = static_cast<XMLHttpRequest*>( external->Value());
							 return xml;
			 }

			 XMLHttpRequest* UnwrapXMLHttpRequest( const Arguments& info )
			 			 {
			 						//cout<<"UnwrapXMLHttpRequest(arguments)\n";
										 //Get the self object,
			 					 Local<v8::Object> self = info.Holder();
			 						//cout<<"check 1";
										 //Fetch the c++ pointer.
			 				 Local<External> external = Local<External>::Cast( self->GetInternalField(0) );
			 							 //Get back to the type.
										 ///cout<<"check 2";
			 				 XMLHttpRequest* xml = static_cast<XMLHttpRequest*>( external->Value());

								return xml;
			 			 }

 Handle<Value>XMLHttpRequest::getresponseTextCallback(Local<String> property,const AccessorInfo& info)
	      {
	    	//cout<<"getresponseTextCallback() function \n";

						Locker lock;
						HandleScope scope;

						XMLHttpRequest* xml = UnwrapXMLHttpRequest( info );

	    	  if(xml!=NULL)
	    	  {
	    		  const char *response=(xml->getresponseText()).c_str();
	    		  ///cout<<"printing in getresponsecallback before sending Handle<Value>";
	    		  Handle<String> resT=String::New(response,-1);

	    		 return scope.Close(resT);
	    	  }
	    	  return Undefined();
	      }


Handle<Value> XMLHttpRequest::getresponseHeaderCallback(Local<String> property,const AccessorInfo& info) {
					//cout<<"getresponseHeaderCallback() function \n";
					Locker lock;
          HandleScope scope;

              XMLHttpRequest* xml = UnwrapXMLHttpRequest( info );
		    	  if(xml!=NULL)
		    	  {
		    		  const char *response=(xml->getResponseHeader()).c_str();
		    		  ///cout<<"printing in getresponsecallback before sending Handle<Value>";
		    		  Handle<String> resT=String::New(response,-1);
		    		   return scope.Close( resT );

		    	  }
		    	  return Undefined();
}



void XMLHttpRequest::setonreadystatechangeCallback(Local<String> property,Local<Value> value,const AccessorInfo & info) {
					//cout<<"setonreadystatechangeCallback() function \n";
					Locker lock;
					HandleScope scope;
					///cout<<"check 1\n";

					XMLHttpRequest* xml = UnwrapXMLHttpRequest( info );

					if(xml!=NULL)
				 xml->onreadystatechange=Persistent<Function>::New(Handle<Function>::Cast(value));
				 //cout<<"exiting from setonreadystatechangeCallback\n";
}

Handle<Value> XMLHttpRequest::getreadyStateCallback(Local<String> property,const AccessorInfo& info) {
					//	cout<<"getreadystateCallback() function \n";
						Locker lock;
						HandleScope scope;
						XMLHttpRequest* xml = UnwrapXMLHttpRequest( info );

			    	  if(xml!=NULL)
			    	  {
			    		  Handle<Integer> resT=Integer::New(xml->getreadyState());

			    		  return (scope.Close(resT));
			    	  }
			    	  return Undefined();
}



void  XMLHttpRequest::set_payload(string x){
		cout<<"XMLHttpRequest.set_payload()\n";
         if(!x.empty())
         this->Payload.assign(x);
       }

void XMLHttpRequest::send() {
	cout<<"XMLHttpRequest.send()\n";
		 class dummy
	    {
	    	public:
	         	 static void* ultra(void * void_this){
	         		//cout<<"dummy::ultra called\n";
	         		XMLHttpRequest * thread_this = static_cast<XMLHttpRequest*>(void_this);
							bool result=false;
							int counter=0;

							while(++counter <=3 && result==false){
								result=network_call(thread_this);
								//cout<<"trying network call "<<counter<<" "<<result<<endl;
							}

							if(!result)
												cout<<"Failure in %s call"<<thread_this->type_of_request.c_str() ;
							else{
									/*cout<<"before crash\n";
									thread_this->onreadystatechange->Call(context->Global(),0,NULL);
									cout<<"after crash\n";*/
									thread_this->readyState=4;
							}
	         		//cout<<"exit from dummy::ultra in send() \n";
	         		}
	    };

 if(this->is_asynchronous==true){

				 pthread_t *anix=new pthread_t();
				 int is_thread_ok = pthread_create(anix, NULL,dummy::ultra, this);



					if (is_thread_ok)
						cout<<"could not create thread";
					 pthread_join(*anix,0);
					//cout<<"exiting from thread\n";
			}

 else {
	 dummy::ultra(this);
 }

 //cout<<"before crash\n";
 //cout<<xml->onreadystatechange->GetScriptLineNumber()<<endl;
 this->onreadystatechange->Call((this->onreadystatechange),0,NULL);
 //cout<<"after crash\n";

}

void XMLHttpRequest::sendCallback(const v8::Arguments& args) {
				//cout<<"in XMLHttpRequest::sendCallback() \n";
		Locker lock;
		HandleScope scope;
		XMLHttpRequest* xml = UnwrapXMLHttpRequest(args);
		if(xml!=NULL){
			if(args.Length()==1){
			 String::Utf8Value a00( args[0]->ToString());char *a0= *a00;
			 if(!a0 || a0[0]!='\0')
						xml->set_payload(a0);
						xml->send();
			}
		}

}

void  XMLHttpRequest::setRequestHeader(string ctype,string head)
			 {
					this->requestHeader=head;
			 }

   void XMLHttpRequest::setRequestHeaderCallback(const v8::Arguments& args)
                             {
															 Locker lock;
						 								 HandleScope scope;
                                 if(args.Length() ==2)
                                 {
														 XMLHttpRequest* xml = UnwrapXMLHttpRequest(args);

                                     if(xml != NULL)
                                     {
                                      String::Utf8Value uri( args[0]->ToString() );	char *a0= *uri;
                                       String::Utf8Value hd( args[1]->ToString() );		char *a1=*hd;

                                       xml->setRequestHeader(a0,a1);
                                         //return scope.Close( self );
                                     }
                                 }
                                 //return Undefined();
                             }

 void XMLHttpRequest::openCallback(const v8::Arguments& args)
 	      {
 	    	// cout<<"openCallBack() function\n";

 	    	 //Locker v8Locker();
 	    	 //HandleScope scope;
 	    	 if(args.Length()==3)
 	    	 {
					 Locker lock;
					 HandleScope scope;
					 XMLHttpRequest* xml = UnwrapXMLHttpRequest(args);
					 //if(xml==NULL)	cout<<"NULL";
 	    		 if(xml!=NULL)
 	    		 {


						 String::Utf8Value a00( args[0]->ToString());char *a0= *a00;
 	    			 String::Utf8Value a11( args[1]->ToString());char *a1= *a11;
 	    			 String::Utf8Value a22( args[2]->ToString());char *a2= *a22;

 	    			 bool x_bool;
 	    			 if(strcmp(a2,"true")==0)	x_bool=true;
 	    			if(strcmp(a2,"false")==0)	x_bool=false;
 	    			if(strcmp(a2,"true") && strcmp(a2,"false"))
 	    		 						cout<<"Syntax error in true/false argument of OPEN call";

 	    			xml->open(a0,a1,x_bool);

 	    		 }
 	    	 }

 	     }

 void XMLHttpRequest::open(string type,string reqURL,bool async){
	    	cout<<"XMLHttpRequest.open()\n";
	    	 type_of_request.assign(type);
	    	 site_URL.assign(reqURL);
	    	 is_asynchronous=async;
	    	 readyState=1;
	      }



Handle<Value> XMLHttpRequest::getstatusCallback(Local<String> property,const AccessorInfo& info) {
						//cout<<"getstatusCallback() function \n";
						Locker lock;
						HandleScope scope;
						XMLHttpRequest* xml = UnwrapXMLHttpRequest( info );

				    	  if(xml!=NULL)
				    	  {
				    		  Handle<Integer> resT=Integer::New(xml->getStatus());
				    		  //info.GetReturnValue().Set(resT);
				    		  return (scope.Close(resT));
				    	  }
				    	  return Undefined();
}



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
