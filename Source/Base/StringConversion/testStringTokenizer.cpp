
#include <OSGConfig.h>
#include <OSGBaseFunctions.h>
#include <OSGBaseTypes.h>
#include <OSGLog.h>
#include "OSGStringTokenizer.h"
#include <string>

OSG_USING_NAMESPACE

int main(int argc, char** argv)
{
    osgInit(argc, argv);
    
    UInt8 numTestStrings = 7;
    std::string testStrings[] = {
                            std::string(""),
                            std::string("     "),
                            std::string("No space at front and end"),
                            std::string(" Space only at front"),
                            std::string("Space only at end "),
                            std::string(" Space at front and end "),
                            std::string(" Misc.\t stuff tested   \non \ttwo lines"),
                             };
    
    StringTokenizer tokens(testStrings[0]);

    for(UInt8 i = 0;i<numTestStrings; i++)
    { 
        //       StringTokenizer* tokens = new StringTokenizer(testStrings[i]);

        tokens.setString(testStrings[i]);
        SLOG << "teststring: |" << testStrings[i] << "|" << std::endl;
        SLOG << tokens.countTokens() << " in string" << std::endl;

        for(UInt32 tokenCount = 0; tokens.hasNext(); tokenCount++)
        {
            SLOG << tokenCount+1 << "/" << tokens.countTokens()
                 << "  |" << tokens.getNext() << "|  " << std::endl;
       }
    }
    
    return 0;
}
            
