
%{

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 111 810)
#endif

#define YY_NEVER_INTERACTIVE 1

#ifdef __cplusplus
extern "C"
{
#define YY_DECL extern "C" int yylex YY_PROTO(( void ))
}
#endif

#define y_min(a, b)               ((a)<(b)?(a):(b))

#ifdef __sgi
#pragma set woff 1110,1174
#endif

/* includes */ 
#include <unistd.h>
#include <math.h>
#include <string>
#include <stdlib.h>

#undef v2a_FLEX_DEBUG

#ifdef v2a_FLEX_DEBUG
#define prompt {printf("%s ",v2a_text);fflush(stdout);}
#else
#define prompt
#endif

extern "C"
{
int v2a_wrap()
{
    return(1);
}

extern int v2aLineNumber;
extern char v2a_text[];

#include "v2a.tab.h"
}  


static char *tmpChar = yy_full_match;

%}

%x comment



%%
"#".*               	{prompt; }
"//".*              	{prompt; }
"/*"					{prompt; BEGIN(comment); }
<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<comment>\n             ++v2aLineNumber;
<comment>"*"+"/"        BEGIN(INITIAL);

"Position"		{prompt; return (POSITION);}
"position"		{prompt; return (POSITION);}
"POSITION"		{prompt; return (POSITION);}
"Orientation"	{prompt; return (ORIENTATION);}
"orientation"	{prompt; return (ORIENTATION);}
"ORIENTATION"	{prompt; return (ORIENTATION);}
"Coordinate"	{prompt; return (COORDINATE);}
"coordinate"	{prompt; return (COORDINATE);}
"COORDINATE"	{prompt; return (COORDINATE);}
"Scalar"		{prompt; return (SCALAR);}
"scalar"		{prompt; return (SCALAR);}
"SCALAR"		{prompt; return (SCALAR);}
"Color" 		{prompt; return (COLOR);}
"color" 		{prompt; return (COLOR);}
"COLOR" 		{prompt; return (COLOR);}
"Normal" 		{prompt; return (NORMAL);}
"normal" 		{prompt; return (NORMAL);}
"NORMAL" 		{prompt; return (NORMAL);}
"["				{prompt; return (E_OPEN);}
"]"				{prompt; return (E_CLOSE);}
"{"				{prompt; return (C_OPEN);}
"}"				{prompt; return (C_CLOSE);}
","				{prompt; return (COMMA);}
"key"			{prompt; return (KEY);}
"Key"			{prompt; return (KEY);}
"KEY"			{prompt; return (KEY);}
"keyValue"		{prompt; return (KEYVALUE);}
"keyvalue"		{prompt; return (KEYVALUE);}
"KEYVALUE"		{prompt; return (KEYVALUE);}
"Duration"		{prompt; return (DURATION);}
"duration"		{prompt; return (DURATION);}
"DURATION"		{prompt; return (DURATION);}
"KEYSIZE"		{prompt; return (KEYSIZE);}
"keySize"		{prompt; return (KEYSIZE);}
"keysize"		{prompt; return (KEYSIZE);}

[+-]?([0-9]+"."?[0-9]*|[0-9]*"."?[0-9]+)([eE][+-]?[0-9]+)?	{ 
		    prompt;
		    v2a_lval.fval = atof(v2a_text);
		    return (NUMBER);
   		}

\<([^\>"]*)\>	{
		    prompt; 
		    strcpy(v2a_lval.sval,v2a_text);    
		    return (STRING);
		}
		
\"([^"]|"\\\""|\"[ \t\n]*\")*\"		{
			 char *c;
			 int l;
			 prompt; 
			 strncpy(v2a_lval.sval,v2a_text+1, y_min(255-1, strlen(v2a_text+1)));
			 v2a_lval.sval[y_min(255-1, strlen(v2a_text+1))]='\0';
			 *(strchr(v2a_lval.sval, 0)-1)=0;
			 c=v2a_lval.sval; l=strlen(v2a_lval.sval);
			 while (strchr(c, '"'))
			 {
				 if (c[-1]=='\\')
				 {
					 memmove(c-1, c, l-(c-v2a_lval.sval));
					 l--;
				 }
				 else if (c[1]==' ' || c[1]=='\t' || c[1]=='\n')
				 {
					 char *d=strchr(c, '"')+1;
					 
					 memmove(c, d+1, l-(d-v2a_lval.sval));
					 l-=d-c;
				 }
			 }	 
			 return (STRING);}
			 
[~/a-zA-Z!@#$%^&*._=|':;?][~/a-zA-Z0-9+!@#$%^&<>._\[\]|':;?-]*    {
		    strcpy(v2a_lval.sval,v2a_text); 
		    return (STRING);
		}

[ \t]+          /* eat up */;

\n              { 
#ifdef v2a_DEBUG
		    printf("\n");
#endif
		    v2aLineNumber++; 
		}

%%

#ifdef OSG_WIN32_ICL
#pragma warning (default : 111 810)
#endif
