#include "test/*asdf*/header.h"
#include <stdio.h>
#include <foo/*bar*/baz.h>   


int foo();

int bar(); 


int g_global_var = 1;


int baz();



volatile int g_global;


int main(int argc, const char* argv)
{
    printf("/* foo bar");
    

    
    baz();
    


    baz();


    return 1;
}
