/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
 *                                                                           * 
 *                            www.opensg.org                                 * 
 *                                                                           * 
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          * 
 *                                                                           * 
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    * 
 *                                                                           * 
 * This library is free software; you can redistribute it and/or modify it   * 
 * under the terms of the GNU Library General Public License as published    * 
 * by the Free Software Foundation, version 2.                               * 
 *                                                                           * 
 * This library is distributed in the hope that it will be useful, but       * 
 * WITHOUT ANY WARRANTY; without even the implied warranty of                * 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         * 
 * Library General Public License for more details.                          * 
 *                                                                           * 
 * You should have received a copy of the GNU Library General Public         * 
 * License along with this library; if not, write to the Free Software       * 
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 * 
 *                                                                           * 
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    * 
 *                                                                           * 
 *                                                                           * 
 *                                                                           * 
 *                                                                           * 
 *                                                                           * 
 *                                                                           * 
\*---------------------------------------------------------------------------*/

#include "OSGActorWriter.h"

#include "OSGActorBaseTemplate_h.h"
#include "OSGActorBaseTemplate_cpp.h"
#include "OSGActorBaseTemplate_inl.h"

#include "OSGActorTemplate_h.h"
#include "OSGActorTemplate_cpp.h"
#include "OSGActorTemplate_inl.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>

OSG_USING_NAMESPACE

char *ActorWriter::_ConditionKeys[] = 
{
    "UseLocalIncludes",
    "EnterStore_EQ_LeaveStore",
    "LeaveStore_EQ_EnterStore",
    "EnterStore_EQ_Empty",
    "EnterStore_EQ_Simple",
    "EnterStore_EQ_Single",
    "EnterStore_EQ_Multi",
    "LeaveStore_EQ_Empty",
    "LeaveStore_EQ_Simple",
    "LeaveStore_EQ_Single",
    "LeaveStore_EQ_Multi",
    "AcceptsStateAwareIterator",
    "AcceptsStateUnawareIterator",
    "HasOrderedStateElems",
    "StateElemIsOrdered",
    "StateElemIsUnorderd",
    "StateElemIsPublic",
    "StateElemIsProtected",
    "StateElemHasInclude",
    "Library",
    NULL
};

char *ActorWriter::_ReplaceKeys[] =
{
    "@!Classname!@",
    "@!CLASSNAME!@",
    "@!Libname!@",
    "@!LIBNAME!@",
    "@!HeaderPrefix!@",
    "@!ParentName!@",
    "@!ParentHeader!@",
    "@!ParentHeaderPrefix!@",
    "@!StateElemName!@",
    "@!StateElemType!@",
    "@!StateElemHeader!@",
    "@!StateElemDefault!@",
    "@!EnterStore!@",
    "@!LeaveStore!@",
    NULL
};

std::string ActorWriter::_filePrefix    = "OSG";
std::string ActorWriter::_decFileSuffix = "h";
std::string ActorWriter::_impFileSuffix = "cpp";
std::string ActorWriter::_inlFileSuffix = "inl";

ActorWriter::ActorWriter(void)
    : _pAI        (NULL),
      _itStateElem(    )
{
}

ActorWriter::ActorWriter(ActorInfo *pInfo)
    : _pAI        (pInfo),
      _itStateElem(     )
{
}

ActorWriter::~ActorWriter(void)
{
}

void
ActorWriter::setActorInfo(ActorInfo *pInfo)
{
    _pAI = pInfo;
}

ActorInfo *
ActorWriter::getActorInfo(void)
{
    return _pAI;
}

std::string
ActorWriter::getCodeBaseDecFileName(void)
{
    return _filePrefix + _pAI->getName() + "Base." + _decFileSuffix;
}

std::string
ActorWriter::getCodeBaseImpFileName(void)
{
    return _filePrefix + _pAI->getName() + "Base." + _impFileSuffix;
}

std::string
ActorWriter::getCodeBaseInlFileName(void)
{
    return _filePrefix + _pAI->getName() + "Base." + _inlFileSuffix;
}

std::string
ActorWriter::getCodeDecFileName(void)
{
    return _filePrefix + _pAI->getName() + "." + _decFileSuffix;
}

std::string
ActorWriter::getCodeImpFileName(void)
{
    return _filePrefix + _pAI->getName() + "." + _impFileSuffix;
}

std::string
ActorWriter::getCodeInlFileName(void)
{
    return _filePrefix + _pAI->getName() + "." + _inlFileSuffix;
}

bool
ActorWriter::writeCodeBaseDec(const std::string &outPath)
{
    bool          retCode = false;
    std::string   outFilePath(outPath + getCodeBaseDecFileName());
    std::ofstream os;

    os.open(outFilePath.c_str());

    if(os)
    {
        retCode = writeCodeBaseDec(os);
    }
    
    return retCode;
}

bool
ActorWriter::writeCodeBaseDec(std::ostream &os)
{
    return writeTemplate(os, ActorBaseTemplate_h);
}

bool
ActorWriter::writeCodeBaseImp(const std::string &outPath)
{
    bool          retCode = false;
    std::string   outFilePath(outPath + getCodeBaseImpFileName());
    std::ofstream os;

    os.open(outFilePath.c_str());

    if(os)
    {
        retCode = writeCodeBaseImp(os);
    }
    
    return retCode;
}

bool
ActorWriter::writeCodeBaseImp(std::ostream &os)
{
    return writeTemplate(os, ActorBaseTemplate_cpp);
}

bool
ActorWriter::writeCodeBaseInl(const std::string &outPath)
{
    bool          retCode = false;
    std::string   outFilePath(outPath + getCodeBaseInlFileName());
    std::ofstream os;

    os.open(outFilePath.c_str());

    if(os)
    {
        retCode = writeCodeBaseInl(os);
    }
    
    return retCode;
}

bool
ActorWriter::writeCodeBaseInl(std::ostream &os)
{
    return writeTemplate(os, ActorBaseTemplate_inl);
}

bool
ActorWriter::writeCodeDec(const std::string &outPath)
{
    bool          retCode = false;
    std::string   outFilePath(outPath + getCodeDecFileName());
    std::ifstream is;
    std::ofstream os;

    is.open(outFilePath.c_str());

    if(is)
    {
        std::cerr << "ERROR: file " << outFilePath << " exists. "
                  << "Remove it and try again."    << std::endl;
    }
    else
    {
        os.open(outFilePath.c_str());

        if(os)
        {
            retCode = writeCodeDec(os);
        }
    }

    return retCode;
}

bool
ActorWriter::writeCodeDec(std::ostream &os)
{
    return writeTemplate(os, ActorTemplate_h);
}

bool
ActorWriter::writeCodeImp(const std::string &outPath)
{
    bool          retCode = false;
    std::string   outFilePath(outPath + getCodeImpFileName());
    std::ifstream is;
    std::ofstream os;

    is.open(outFilePath.c_str());

    if(is)
    {
        std::cerr << "ERROR: file " << outFilePath << " exists. "
                  << "Remove it and try again."    << std::endl;
    }
    else
    {
        os.open(outFilePath.c_str());

        if(os)
        {
            retCode = writeCodeImp(os);
        }
    }

    return retCode;
}

bool
ActorWriter::writeCodeImp(std::ostream &os)
{
    return writeTemplate(os, ActorTemplate_cpp);
}

bool
ActorWriter::writeCodeInl(const std::string &outPath)
{
    bool          retCode = false;
    std::string   outFilePath(outPath + getCodeInlFileName());
    std::ifstream is;
    std::ofstream os;

    is.open(outFilePath.c_str());

    if(is)
    {
        std::cerr << "ERROR: file " << outFilePath << " exists. "
                  << "Remove it and try again."    << std::endl;
    }
    else
    {
        os.open(outFilePath.c_str());

        if(os)
        {
            retCode = writeCodeInl(os);
        }
    }

    return retCode;
}


bool
ActorWriter::writeCodeInl(std::ostream &os)
{
    return writeTemplate(os, ActorTemplate_inl);
}

bool
ActorWriter::writeTemplate(std::ostream &os, char **pTemplate)
{
    char  **pStateLoopStart;
    int     skipIf          = 0;
    bool    bInStateLoop    = false;
    bool    bSkipStateLoop  = false;
    bool    retVal          = true;

    for(; *pTemplate != NULL; ++pTemplate)
    {
        std::string strLine(*pTemplate);

        if(skipIf > 0)
        {
            // not a special line
            if(strLine.compare(0, 2, "@@") != 0)
                continue;
                
            if(strLine.compare(0, 4, "@@if") == 0)
            {
                ++skipIf;
            }
            else if(strLine.compare(0, 7, "@@endif") == 0)
            {
                --skipIf;
            }
            else if(strLine.compare(0, 6, "@@else") == 0)
            {
                if(skipIf == 1)
                    skipIf = 0;
            }
            
            continue;
        }

        // special line
        if(strLine.compare(0, 2, "@@") == 0)
        {
            if(strLine.compare(0, 18, "@@BeginStateLoop@@") == 0)
            {
                bInStateLoop    = true;
                pStateLoopStart = pTemplate;
                _itStateElem    = _pAI->beginStateElems();

                if(_itStateElem == _pAI->endStateElems())
                    bSkipStateLoop = true;
            }
            else if(strLine.compare(0, 16, "@@EndStateLoop@@") == 0)
            {
                if(bSkipStateLoop == true)
                {
                    bInStateLoop   = false;
                    bSkipStateLoop = false;

                    continue;
                }

                ++_itStateElem;

                if(_itStateElem != _pAI->endStateElems())
                {
                    pTemplate = pStateLoopStart;
                }
                else
                {
                    bInStateLoop   = false;
                    bSkipStateLoop = false;
                }
            }
            else if(bSkipStateLoop == true)
            {
                continue;
            }
            else if(strLine.compare(0, 4, "@@if") == 0)
            {
                int  condStart = 0;
                int  condIndex = 0;
                bool bCondTrue = false;
                bool bNegate   = false;

                condStart = strLine.find_first_of    (" \t", condStart);
                condStart = strLine.find_first_not_of(" \t", condStart);

                if(strLine[condStart] == '!')
                {
                    condStart = strLine.find_first_not_of(" \t", ++condStart);
                    bNegate   = true;
                }

                std::string strCond(strLine.substr(condStart));

                for(; _ConditionKeys[condIndex] != NULL; ++condIndex)
                {
                    if(strcasecmp(strCond.c_str(), 
                                  _ConditionKeys[condIndex]) == 0)
                    {
                        break;
                    }
                }
                
                skipIf = 0;

                switch(condIndex)
                {
                case 0:      // UseLocalIncludes
                {
                    if(_pAI->getUseLocalIncludes() == true)
                    {
                        bCondTrue = true;
                    }

                    break;
                }
                
                case 1:      // EnterStore_EQ_LeaveStore
                case 2:      // LeaveStore_EQ_EnterStore
                {
                    if(_pAI->getEnterStore() == 
                       _pAI->getLeaveStore()    )
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 3:      // EnterStore_EQ_Empty
                {
                    if(_pAI->getEnterStore() == ActorInfo::EmptyStore)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 4:      // EnterStore_EQ_Simple
                {
                    if(_pAI->getEnterStore() == ActorInfo::SimpleStore)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 5:      // EnterStore_EQ_Single
                {
                    if(_pAI->getEnterStore() == ActorInfo::SingleStore)
                    {
                        bCondTrue = true;
                    }

                    break;
                } 
                    
                case 6:      // EnterStore_EQ_Multi
                {
                    if(_pAI->getEnterStore() == ActorInfo::MultiStore)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 7:      // LeaveStore_EQ_Empty
                {
                    if(_pAI->getLeaveStore() == ActorInfo::EmptyStore)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 8:      // LeaveStore_EQ_Simple
                {
                    if(_pAI->getLeaveStore() == ActorInfo::SimpleStore)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 9:      // LeaveStore_EQ_Single
                {
                    if(_pAI->getLeaveStore() == ActorInfo::SingleStore)
                    {
                        bCondTrue = true;
                    }

                    break;
                } 
                    
                case 10:     // LeaveStore_EQ_Multi
                {
                    if(_pAI->getLeaveStore() == ActorInfo::MultiStore)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 11:     // AcceptsStateAwareIterator
                {
                    if(_pAI->getAcceptStateAwareIter() == true)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 12:     // AcceptsStateUnawareIterator
                {
                    if(_pAI->getAcceptStateUnawareIter() == true)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 13:     // HasOrderedStateElems
                {
                    ActorInfo::StateElemBagIt itState  = 
                        _pAI->beginStateElems();
                    ActorInfo::StateElemBagIt endState =
                        _pAI->endStateElems  ();

                    for(; itState != endState; ++itState)
                    {
                        if(itState->getOrder() == StateElemInfo::Ordered)
                        {
                            bCondTrue = true;
                            break;
                        }
                    }
                    
                    break;
                }
                 
                case 14:     // StateElemIsOrdered
                {
                    if(_itStateElem->getOrder() == StateElemInfo::Ordered)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 15:     // StateElemIsUnordered
                {
                    if(_itStateElem->getOrder() == StateElemInfo::Unordered)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 16:     // StateElemIsPublic
                {
                    if(_itStateElem->getAccess() == StateElemInfo::PublicAccess)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 17:     // StateElemIsProtected
                {
                    if(_itStateElem->getAccess() == 
                       StateElemInfo::ProtectedAccess)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 18:     // StateElemHasHeader
                {
                    if(getStateElemHeader().length() > 0)
                    {
                        bCondTrue = true;
                    }

                    break;
                }

                case 19:     // Library
                {
                    if(_pAI->getLibName().length() > 0)
                    {
                        bCondTrue = true;
                    }
                    
                    break;
                }

                case 20:     // Unknown Condition
                default:
                {
                    std::cerr << "ActorWriter::writeTemplate: unknown "
                              << "condition " << strLine << " in line " 
                              << *pTemplate   << std::endl;

                    retVal = false;

                    break;
                }
                };

                if(bCondTrue == true)
                {
                    skipIf = bNegate ? 1 : 0;
                }
                else
                {
                    skipIf = bNegate ? 0 : 1;
                }
            }
            else if(strLine.compare(0, 6, "@@else") == 0)
            {
                skipIf = 1;
            }
            else if(strLine.compare(0, 7,"@@endif") == 0)
            {
                skipIf = 0;
            }
            else
            {
                std::cerr << "ActorWriter::writeTemplate: unknown special "
                          << strLine << " in line " << *pTemplate
                          << std::endl;

                retVal = false;
            }
        }
        else if(bSkipStateLoop)
        {
            continue;
        }
        else // verbatim text
        {
            int         start        = 0;
            int         end          = 0;
            bool        bDone        = false;
            int         replaceIndex = 0;
            std::string replaceKey;

            while(!bDone)
            {
                start = strLine.find("@!", 0, 2);
                end   = strLine.find("!@", 0, 2);

                if((start == std::string::npos) ||
                   (end   == std::string::npos)   )
                {
                    break;
                }

                replaceKey.assign(strLine.substr(start, end + 2 - start));

                for(replaceIndex = 0; _ReplaceKeys[replaceIndex] != NULL;
                    ++replaceIndex)
                {
                    if(strcmp(replaceKey.c_str(), 
                              _ReplaceKeys[replaceIndex]) == 0)
                    {
                        break;
                    }
                }

                switch(replaceIndex)
                {
                case 0:      // Classname
                {
                    strLine.replace(start, end + 2 - start, getClassname());
                    break;
                }
                
                case 1:      // CLASSNAME
                {
                    strLine.replace(start, end + 2 - start, getCLASSNAME());
                    break;
                }

                case 2:      // Libname
                {
                    strLine.replace(start, end + 2 - start, getLibname());
                    break;
                }

                case 3:      // LIBNAME
                {
                    strLine.replace(start, end + 2 - start, getLIBNAME());
                    break;
                }

                case 4:      // HeaderPrefix
                {
                    strLine.replace(start, end + 2 - start, getHeaderPrefix());
                    break;
                }
                
                case 5:      // ParentName
                {
                    strLine.replace(start, end + 2 - start, getParentName());
                    break;
                }

                case 6:      // ParentHeader
                {
                    strLine.replace(start, end + 2 - start, getParentHeader());
                    break;
                }

                case 7:      // ParentHeaderPrefix
                {
                    strLine.replace(start, end + 2 - start,
                                    getParentHeaderPrefix());
                    break;
                }

                case 8:      // StateElemName
                {
                    strLine.replace(start, end + 2 - start,
                                    getStateElemName()     );
                    break;
                }

                case 9:      // StateElemType
                {
                    strLine.replace(start, end + 2 - start,
                                    getStateElemType()     );
                    break;
                }
                
                case 10:     // StateElemHeader
                {
                    strLine.replace(start, end + 2 - start, 
                                    getStateElemHeader()   );
                    break;
                }

                case 11:     // StateElemDefault
                {
                    strLine.replace(start, end + 2 - start, 
                                    getStateElemDefault()  );
                    break;
                }
                
                case 12:     // EnterStore
                {
                    strLine.replace(start, end + 2 - start, getEnterStore());
                    break;
                }

                case 13:     // LeaveStore
                {
                    strLine.replace(start, end + 2 - start, getLeaveStore());
                    break;
                }

                case 14:     // Unknown Key
                default:    
                {
                    std::cerr << "ActorWriter::writeTemplate: unknown "
                              << "key "  << replaceKey << " in line "
                              << strLine << std::endl;

                    retVal = false;

                    break;
                }
                };
            }

            os << strLine << std::endl;
        }
    }

    return retVal;            
}


std::string
ActorWriter::getClassname(void)
{
    return _pAI->getName();
}

std::string
ActorWriter::getCLASSNAME(void)
{
 
    return upCase(_pAI->getName());
}

std::string
ActorWriter::getLibname(void)
{
    return _pAI->getLibName();
}

std::string
ActorWriter::getLIBNAME(void)
{
    return upCase(_pAI->getLibName());
}

std::string
ActorWriter::getHeaderPrefix(void)
{
    return _pAI->getHeaderPrefix();
}

std::string
ActorWriter::getParentName(void)
{
    return _pAI->getParentName();
}

std::string
ActorWriter::getParentHeader(void)
{
    return _pAI->getParentHeader();
}

std::string
ActorWriter::getParentHeaderPrefix(void)
{
    return _pAI->getParentHeaderPrefix();
}

std::string
ActorWriter::getStateElemName(void)
{
    return _itStateElem->getName();
}

std::string
ActorWriter::getStateElemType(void)
{
    return _itStateElem->getType();
}

std::string
ActorWriter::getStateElemHeader(void)
{
    return _itStateElem->getTypeHeader();
}

std::string
ActorWriter::getStateElemDefault(void)
{
    return _itStateElem->getDefaultValue();
}

std::string
ActorWriter::getEnterStore(void)
{
    return _pAI->getEnterStoreStr();
}

std::string
ActorWriter::getLeaveStore(void)
{
    return _pAI->getLeaveStoreStr();
}

std::string
ActorWriter::upCase(const std::string &inStr)
{
    std::string outStr;

    outStr.resize(inStr.length());

    std::transform(inStr.begin(), inStr.end(), outStr.begin(),
                   std::ptr_fun(toupper)                      );

    return outStr;
}

int
ActorWriter::strcasecmp(const char *string1, const char *string2)
{
#if !defined(WIN32)
    return ::strcasecmp(string1, string2);
#else
    return _stricmp    (string1, string2);
#endif
}
