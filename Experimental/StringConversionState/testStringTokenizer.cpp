
#include <OSGConfig.h>
#include <OSGBaseFunctions.h>
#include <OSGBaseTypes.h>
#include "OSGStringTokenizer.h"
#include <string>

OSG_USING_NAMESPACE

int main(int argc, char** argv)
{
    osgInit(argc, argv);
    
    UInt8 numTestStrings = 7;
    string testStrings[] = {
                            string(""),
                            string("     "),
                            string("No space at front and end"),
                            string(" Space only at front"),
                            string("Space only at end "),
                            string(" Space at front and end "),
                            string(" Misc.\t stuff tested   \non \ttwo lines"),
                             };
    
    StringTokenizer tokens(testStrings[0]);

    for(UInt8 i = 0;i<numTestStrings; i++)
    { 
        //       StringTokenizer* tokens = new StringTokenizer(testStrings[i]);

        tokens.setString(testStrings[i]);
        cout << "teststring: |" << testStrings[i] << "|" << endl;
        cout << tokens.countTokens() << " in string" << endl;

        for(UInt32 tokenCount = 0; tokens.hasNext(); tokenCount++)
        {
            cout << tokenCount+1 << "/" << tokens.countTokens()
                 << "  |" << tokens.getNext() << "|  " << endl;
       }
    }
    
    return 0;
}
            
