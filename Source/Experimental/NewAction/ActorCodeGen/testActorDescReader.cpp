
#include <unistd.h>

#include <OSGActorInfo.h>
#include <OSGActorDescReader.h>
#include <OSGActorWriter.h>

#include <string>
#include <iostream>
#include <fstream>

OSG_USING_NAMESPACE

#ifdef WIN32


/*
*  This is the AT&T public domain source for getopt(3).  It is the code
*  which was given out at the 1985 UNIFORUM conference in Dallas.
*   
*  There is no manual page.  That is because the one they gave out at
*  UNIFORUM was slightly different from the current System V Release 2
*  manual page.  The difference apparently involved a note about the
*  famous rules 5 and 6, recommending using white space between an
*  option and its first argument, and not grouping options that have
*  arguments.  Getopt itself is currently lenient about both of these
*  things.  White space is allowed, but not mandatory, and the last option
*  in a group can have an argument.  That particular version of the man
*  page evidently has no official existence.  The current SVR2 man page
*  reflects the actual behavor of this getopt.
*/



/*LINTLIBRARY*/
#ifndef NULL
#define NULL    0
#endif
#define EOF     (-1)
#define ERR(str, chr) (opterr ? fprintf(stderr, "%s%s%c\n", argv[0], str, chr) : 0)

int     opterr = 1;
int     optind = 1;
int     optopt = 0;
char    *optarg = 0;

int
getopt(int argc, char **argv, const char *opts)
{
        static int sp = 1;
        register int c;
        register char *cp;

        if(sp == 1) {
                if(optind >= argc || (argv[optind][0] != '+' &&
                   argv[optind][0] != '-') || argv[optind][1] == '\0')
                        return(EOF);
                else if(strcmp(argv[optind], "--") == 0) {
                        optind++;
                        return(EOF);
                }
                /* '+' for config options, '+' should not be in the opts list */
                if (argv[optind][0] == '+') {
                        optarg = argv[optind++] + 1;
                        return '+';
                }
        }
        optopt = c = argv[optind][sp];
        if(c == ':' || (cp=strchr(opts, c)) == NULL) {
                ERR(": illegal option -- ", c);
                if(argv[optind][++sp] == '\0') {
                        optind++;
                        sp = 1;
                }
                return('\0');
        }
        if(*++cp == ':') {
                if(argv[optind][sp+1] != '\0')
                        optarg = &argv[optind++][sp+1];
                else if(++optind >= argc) {
                        ERR(": option requires an argument -- ", c);
                        sp = 1;
                        return('\0');
                } else
                        optarg = argv[optind++];
                sp = 1;
        } else {
                if(argv[optind][++sp] == '\0') {
                        sp = 1;
                        optind++;
                }
                optarg = NULL;
        }
        return(c);
}

#endif


int main(int argc, char *argv[])
{
    int         retCode         = -1;
    const char *optString       = "d:p:abh";
    bool        bWriteActorBase = false;
    bool        bWriteActor     = false;
    bool        bWriteBaseOk    = true;
    bool        bWriteOk        = true;
    int         opt             = 0;
    
    std::string descFile;
    std::string outPath = "./";

    ActorInfo        info;
    ActorDescReader  reader(&info);
    ActorWriter      writer(&info);

#ifdef WIN32
    const char dirSep = '\\';
#else
    const char dirSep = '/';
#endif

    while(opt >= 0)
    {
        opt = getopt(argc, argv, optString);

        switch(opt)
        {
        case 'd':
        {
            descFile.assign(optarg);
         
            break;
        }

        case 'p':
        {
            outPath.assign(optarg);

            if(outPath[outPath.size() - 1] != dirSep)
            {
                outPath += dirSep;
            }

            break;
        }

        case 'a':
        {
            bWriteActor = true;

            break;
        }

        case 'b':
        {
            bWriteActorBase = true;

            break;
        }

        case 'h':
        {
            std::cerr << "Usage: testActorDescReader -abh -d file.acd "
                      << "{-p outpath}" << std::endl;
            std::cerr << "  -a write actor file" << std::endl;
            std::cerr << "  -b write base file" << std::endl;
            std::cerr << "  -h print this help message" << std::endl;
            std::cerr << "  -d file.acd: description file" << std::endl;
            std::cerr << "  -p outpath: write files to outpath" << std::endl;
            
            return 0;
        }
        };
    }

    if(optind < argc)
    {
        descFile.assign(argv[optind]);
    }

    if(bWriteActorBase || bWriteActor)
    {
        if(descFile.empty())
        {
            std::cerr << "ERROR: Can't write code without description"
                      << std::endl;
        }
        else
        {
            reader.read(descFile);
        }
    }

    if(bWriteActorBase)
    {
        bWriteBaseOk &= writer.writeCodeBaseDec(outPath);
        bWriteBaseOk &= writer.writeCodeBaseImp(outPath);
        bWriteBaseOk &= writer.writeCodeBaseInl(outPath);
    }

    if(bWriteActor)
    {
        bWriteOk &= writer.writeCodeDec(outPath);
        bWriteOk &= writer.writeCodeImp(outPath);
        bWriteOk &= writer.writeCodeInl(outPath);
    }

    retCode = bWriteBaseOk ?       0 : -1;
    retCode = bWriteOk     ? retCode : -1;

    return retCode;
}







