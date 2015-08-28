
    #include <iostream>
    #include <v8.h>
    #include <fstream>
    #include<cstring>
    #include<streambuf>
    #include<fstream>
    #include<cstring>
    #include<unistd.h>
    #include "XMLHttpRequest.cpp"
using namespace v8;
using namespace std;


//Handle<v8::Value> value;
//Handle<v8::Object> global;



Handle<v8::Function> func;

Handle<Value> printMessage(const v8::Arguments& args)
{
    Locker locker;
    HandleScope scope;

    if( args.Length() )
    {
        String::Utf8Value message( args[0]->ToString() );
        if( message.length() )
        {
            //Print the message to stdout
            printf( "%s", *message );

                //Here we assume newline, and then if the second parameter
                //is supplied to the function, use that instead.
            bool newline = true;
            if(args.Length() == 2)
            {
                newline = args[1]->ToBoolean()->BooleanValue();
            }

            if(newline) printf("\n");

            return scope.Close( Boolean::New( true ) );
        }
    }

    return Undefined();
}

void exposePrint( Handle<ObjectTemplate> targetObject )
{
    targetObject->Set( String::New("print"), v8::FunctionTemplate::New( printMessage ));
  }




    //Handle<Context> context;

  string filetochar (const char* filename)
        {
          std::ifstream ifs(filename);

            std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            return str;
            //const char* c=str.c_str();
            //return c;
        }

        void writetofile(string file_name,string data)
        {
            ofstream myfile(file_name.c_str());
            //myfile.open(x,w)
            myfile<< data;
            myfile.close();
        }



static void* runJSfile(void * void_this){
  Locker locker;
  HandleScope handle_scope;

  Handle<ObjectTemplate> globalTemplate = ObjectTemplate::New();

  exposePrint( globalTemplate );
  exposeXMLHttpRequest( globalTemplate );

Handle<Context> context = Context::New( NULL, globalTemplate );

    context->Enter();
    cout<<"inside runJSfile"<<endl;

    const char *filename=(const char*)void_this;
    string file_data=filetochar(filename);

    Handle<String> source = String::New(file_data.c_str());

    if( source.IsEmpty() ) cout<<"Empty Source File";
        Handle<Script> script = Script::Compile(source);


     if(!script.IsEmpty()) // is script compiled ?
     {
       Handle<Value> result = script->Run();

       if(!result.IsEmpty())
       // Convert the result to an ASCII string and print it.
       String::AsciiValue ascii(result);

       else
       cout<<"Running Failed"<<endl;
     }
     else{
       cout<<"Compilation Failed"<<endl;
     }
}


    int main(int argc, char **argv)
    {
    pthread_t *anix[argc];

    for(int i=1;i<argc;i++){

      anix[i]=new pthread_t();
    int is_thread_ok = pthread_create(anix[i], NULL,runJSfile, argv[i]);

    if (is_thread_ok)
      cout<<"could not create thread for "<<argv[i]<<endl;

      //pthread_join(*anix[i],0);
    }

if(argc<2)
        printf("Usage: <scriptname.js> \n Execute the javascript file.\n");


        usleep(10000090);
        return 0;
    }
