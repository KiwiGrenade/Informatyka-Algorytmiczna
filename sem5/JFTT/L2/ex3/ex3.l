%{
    #include \
    <stdio.h>
    int yywrap();
    int yylex();

    int DOC;
%}

%x include
%x string
%x multi_line_comment
%x documentation

ALL .|\n|\\\n

%%
    /*short documentation comments*/
((\/(\\\n)*\/(\\\n)*\/)|(\/(\\\n)*\/(\\\n)*!)).*(\\\n.*)*	{if(DOC) ECHO;};


    /*short comment*/
\/(\\\n)*\/.*(\\\n.*)* ;


    /*documentation mode*/
    (^[[:blank:]]*)?(\/\*\*)|(\/\*!)            {if(DOC) ECHO; BEGIN(documentation);};
    <documentation>{
        {ALL}   {if(DOC) ECHO;}
        "*/"    {if(DOC) ECHO; BEGIN(0);}
    }


    /*multi line comments*/
\/\*            {BEGIN(multi_line_comment);};
<multi_line_comment>{
    "*/"        BEGIN(0);
    {ALL}       ;
}


    /*string*/
\" ECHO; BEGIN(string);
<string>{
    /* (\\\") -> \n */
    \\\"        ECHO;
    \"          ECHO; BEGIN(0);
}

    
    /*includes*/
"#include"[ \t\n\\\n]+< ECHO; BEGIN(include);
<include>{
    ">"         ECHO; BEGIN(0);
}


%%

int yywrap(){};

int main(int argc, char** argv)
{
    if(argc > 1){
        DOC = 1;
    }
    return yylex();
}