#include "test/*asdf*/header.h"
#include <stdio.h>
#include <foo/*bar*/baz.h>   

/** \brief Java style Doc String - Foo function */
int foo();

int bar(); /**< Bar function */

/// .NET Style Doc String
int g_global_var = 1;


int baz();


/*! Global variable
 *  ... */
volatile int g_global;

//! Main
int main(int argc, const char* argv)
{
    printf("/* foo bar");
    

    
    baz();
    


    baz();


    return 1;
}