
#include <OpenSG/OSGConfig.h>

#include "OSGActorDesc.h"
#include "OSGActorDescReader.h"
#include "OSGActorCodeWriter.h"

// STL includes
#include <string>
#include <iostream>
#include <fstream>

#ifndef WIN32

// for getopt on unix like platforms
#include <unistd.h>

#else  // WIN32

/* Win32 does not have getopt, so we need a replacement there.
   See below for copyright information.
 */

int      opterr = 1;
int      optind = 1;
int      optopt = 0;
char    *optarg = 0;

int
getopt(int argc, char **argv, const char *opts);

#endif // WIN32

OSG_USING_NAMESPACE

int main(int argc, char *argv[])
{
    bool        bWriteActorBase  = false;
    bool        bWriteActor      = false;
    bool        bForce           = false;

    ActorDesc   actorDesc;

    std::ifstream inStream;
    std::ofstream outStream;

    std::string descFileName;
    std::string outPath         = "./";
    std::string outFileName;

    int         opt             = 0;
    int         retCode         = 1;
    const char *optString       = "p:abfh";

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

        case 'f':
        {
            bForce = true;

            break;
        }

        case 'h':
        {
            std::cerr << "Usage: actorEdit [OPTION]... desc_file\n"
                      << "Options:\n"
                      << "-a            write actor file.\n"
                      << "-b            write actor base file.\n"
                      << "-f            force overwrite of actor files.\n"
                      << "-h            display usage information.\n"
                      << "-p out_path   write files to given"
                      <<              " directory, instead of current\n"
                      << std::endl;

            return 0;
        }

        case 'p':
        {
            outPath.assign(optarg);

            if(outPath[outPath.size() - 1] != dirSep)
            {
                outPath += dirSep;
            }
        }

        // catch end of options.
        case -1:
            break;

        default:
        {
            std::cerr << "Unknown option: " << opt << ". ignoring."
                      << std::endl;
        }
        };
    }

    if(optind < argc)
    {
        descFileName.assign(argv[optind]);
    }
    else
    {
        std::cerr << "No description file given. aborting."
                  << std::endl;

        return 1;
    }

    // read the description file

    inStream.open(descFileName.c_str());

    if(!inStream)
    {
        std::cerr << "Could not open description file " << descFileName
                  << " aborting."                       << std::endl;

        return 1;
    }

    ActorDescReader::the().readDesc(inStream, &actorDesc);

    inStream.close();

    // write the actor base files

    if(bWriteActorBase == true)
    {
        // .h file

        outFileName  = outPath;
        outFileName += ActorCodeWriter::the().getFilePrefix     (&actorDesc);
        outFileName += ActorCodeWriter::the().getBaseDecFileName(&actorDesc);

        outStream.open(outFileName.c_str());

        if(!outStream)
        {
            std::cerr << "Could not open code file " << outFileName
                      << ". skipping."               << std::endl;
        }
        else
        {
            ActorCodeWriter::the().writeBaseCodeDec(outStream, &actorDesc);
        }

        outStream.close();

        // .cpp file

        outFileName  = outPath;
        outFileName += ActorCodeWriter::the().getFilePrefix     (&actorDesc);
        outFileName += ActorCodeWriter::the().getBaseImpFileName(&actorDesc);

        outStream.open(outFileName.c_str());

        if(!outStream)
        {
            std::cerr << "Could not open code file " << outFileName
                      << ". skipping."               << std::endl;
        }
        else
        {
            ActorCodeWriter::the().writeBaseCodeImp(outStream, &actorDesc);
        }

        outStream.close();

        // .inl file

        outFileName  = outPath;
        outFileName += ActorCodeWriter::the().getFilePrefix     (&actorDesc);
        outFileName += ActorCodeWriter::the().getBaseInlFileName(&actorDesc);

        outStream.open(outFileName.c_str());

        if(!outStream)
        {
            std::cerr << "Could not open code file " << outFileName
                      << ". skipping."               << std::endl;
        }
        else
        {
            ActorCodeWriter::the().writeBaseCodeInl(outStream, &actorDesc);
        }

        outStream.close();
    }

    // write the actor files

    if(bWriteActor == true)
    {
        // .h file

        outFileName  = outPath;
        outFileName += ActorCodeWriter::the().getFilePrefix (&actorDesc);
        outFileName += ActorCodeWriter::the().getDecFileName(&actorDesc);

        inStream.open (outFileName.c_str());

        if(!inStream || (bForce == true))
        {
            inStream.close();

            outStream.open(outFileName.c_str());

            if(!outStream)
            {
                std::cerr << "Could not open code file " << outFileName
                          << ". skipping."               << std::endl;
            }
            else
            {
                ActorCodeWriter::the().writeCodeDec(outStream, &actorDesc);
            }

            outStream.close();
        }
        else
        {
            std::cerr << "Code file " << outFileName << " exists. "
                      << "Please remove or use the -f option and retry."
                      << std::endl;

            inStream.close();
        }

        // .cpp file

        outFileName  = outPath;
        outFileName += ActorCodeWriter::the().getFilePrefix (&actorDesc);
        outFileName += ActorCodeWriter::the().getImpFileName(&actorDesc);

        inStream.open (outFileName.c_str());

        if(!inStream || (bForce == true))
        {
            inStream.close();

            outStream.open(outFileName.c_str());

            if(!outStream)
            {
                std::cerr << "Could not open code file " << outFileName
                          << ". skipping."               << std::endl;
            }
            else
            {
                ActorCodeWriter::the().writeCodeImp(outStream, &actorDesc);
            }

            outStream.close();
        }
        else
        {
            std::cerr << "Code file " << outFileName << " exists. "
                      << "Please remove or use the -f option and retry."
                      << std::endl;

            inStream.close();
        }

        // .inl file

        outFileName  = outPath;
        outFileName += ActorCodeWriter::the().getFilePrefix (&actorDesc);
        outFileName += ActorCodeWriter::the().getInlFileName(&actorDesc);

        inStream.open (outFileName.c_str());

        if(!inStream || (bForce == true))
        {
            inStream.close();

            outStream.open(outFileName.c_str());

            if(!outStream)
            {
                std::cerr << "Could not open code file " << outFileName
                          << ". skipping."               << std::endl;
            }
            else
            {
                ActorCodeWriter::the().writeCodeInl(outStream, &actorDesc);
            }

            outStream.close();
        }
        else
        {
            std::cerr << "Code file " << outFileName << " exists. "
                      << "Please remove or use the -f option and retry."
                      << std::endl;

            inStream.close();
        }
    }

    return 0;
}


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

#undef EOF
#undef ERR

#endif // WIN32
