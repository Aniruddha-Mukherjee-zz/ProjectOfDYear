
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



    int main(int argc, char **argv)
    {
        Locker locker;
        HandleScope handle_scope;

        Handle<ObjectTemplate> globalTemplate = ObjectTemplate::New();

        exposePrint( globalTemplate );
        exposeXMLHttpRequest( globalTemplate );


      Handle<Context> context = Context::New( NULL, globalTemplate );

        //context = Context::New( NULL, globalTemplate );

        context->Enter();

    //if(argc > 1)
  {

    string file_data=filetochar("weird.js");
      //The source code of this file.
      //cout<<file_data;
      //cout<<"Working ??\n";
      Handle<String> source = String::New(file_data.c_str());

      if( source.IsEmpty() ) cout<<"Empty Source File";

        // Compile the Javascript code.
   Handle<Script> script = Script::Compile(source);
   Handle<Value> result = script->Run();

   String::AsciiValue ascii(result);
   //writetofile("anix_output.txt",*ascii);
   //printf("%s\n", *ascii);

    }

    /*else {

        //printf("Usage: <scriptname.js> \n Execute the javascript file.");
    }*/
        return 0;
    }
