#ifndef V2A__TAB_H
# define V2A__TAB_H

typedef union
{
    float fval;
    char sval[1024];
} YYSTYPE;
# define	POSITION	257
# define	ORIENTATION	258
# define	COORDINATE	259
# define	SCALAR	260
# define	COLOR	261
# define	NORMAL	262
# define	C_OPEN	263
# define	C_CLOSE	264
# define	E_OPEN	265
# define	E_CLOSE	266
# define	COMMA	267
# define	KEY	268
# define	KEYVALUE	269
# define	KEYSIZE	270
# define	DURATION	271
# define	STRING	272
# define	NUMBER	273


extern YYSTYPE v2a_lval;

#endif /* not V2A__TAB_H */
