
#include <OSGActorInfo.h>
#include <OSGActorDescReader.h>
#include <OSGActorWriter.h>

#include <string>
#include <iostream>
#include <fstream>

OSG_USING_NAMESPACE


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
            break;
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







