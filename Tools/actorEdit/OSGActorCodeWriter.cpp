/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGActorCodeWriter.h"
#include "OSGActorStateElemDesc.h"

#include "OSGActorBaseTemplate_h.h"
#include "OSGActorBaseTemplate_cpp.h"
#include "OSGActorBaseTemplate_inl.h"
#include "OSGActorTemplate_h.h"
#include "OSGActorTemplate_cpp.h"
#include "OSGActorTemplate_inl.h"

#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGLog.h>

#include <cctype>

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*    Static Member Init                                                   */

ActorCodeWriter *ActorCodeWriter::_the = NULL;

ActorCodeWriter::ConditionKeyMap ActorCodeWriter::_ConditionKeys[] =
{
    {"UseLocalIncludes",          ActorCodeWriter::C_UseLocalIncludes         },
    {"Library",                   ActorCodeWriter::C_Library                  },
    {"StateElem_HAS_Header",      ActorCodeWriter::C_StateElem_HAS_Header     },
    {"StateElem_IS_Public",       ActorCodeWriter::C_StateElem_IS_Public      },
    {"StateElem_IS_Protected",    ActorCodeWriter::C_StateElem_IS_Protected   },
    {"StateElem_IS_Hierarchical", ActorCodeWriter::C_StateElem_IS_Hierarchical},
    {"EnterStore_IS_Empty",       ActorCodeWriter::C_EnterStore_IS_Empty      },
    {"LeaveStore_IS_Empty",       ActorCodeWriter::C_LeaveStore_IS_Empty      },
    {"EnterStore_IS_Simple",      ActorCodeWriter::C_EnterStore_IS_Simple     },
    {"LeaveStore_IS_Simple",      ActorCodeWriter::C_LeaveStore_IS_Simple     },
    {"EnterStore_IS_Single",      ActorCodeWriter::C_EnterStore_IS_Single     },
    {"LeaveStore_IS_Single",      ActorCodeWriter::C_LeaveStore_IS_Single     },
    {"EnterStore_IS_Multi",       ActorCodeWriter::C_EnterStore_IS_Multi      },
    {"LeaveStore_IS_Multi",       ActorCodeWriter::C_LeaveStore_IS_Multi      },
    {"HAS_Hierarchical_State",    ActorCodeWriter::C_HAS_Hierarchical_State   },

    {NULL,                        ActorCodeWriter::C_UnknownConditionKey      }
};

ActorCodeWriter::ReplaceKeyMap ActorCodeWriter::_ReplaceKeys[] =
{
    {"@!Classname!@",             ActorCodeWriter::R_Classname             },
    {"@!CLASSNAME!@",             ActorCodeWriter::R_CLASSNAME             },
    {"@!ParentName!@",            ActorCodeWriter::R_ParentName            },
    {"@!ParentHeader!@",          ActorCodeWriter::R_ParentHeader          },
    {"@!Libname!@",               ActorCodeWriter::R_Libname               },
    {"@!LIBNAME!@",               ActorCodeWriter::R_LIBNAME               },
    {"@!HeaderPrefix!@",          ActorCodeWriter::R_HeaderPrefix          },
    {"@!ParentHeaderPrefix!@",    ActorCodeWriter::R_ParentHeaderPrefix    },
    {"@!StateElemHeader!@",       ActorCodeWriter::R_StateElemHeader       },
    {"@!StateElemName!@",         ActorCodeWriter::R_StateElemName         },
    {"@!StateElemType!@",         ActorCodeWriter::R_StateElemType         },
    {"@!StateElemDefaultValue!@", ActorCodeWriter::R_StateElemDefaultValue },
    {"@!EnterStore!@",            ActorCodeWriter::R_EnterStore            },
    {"@!LeaveStore!@",            ActorCodeWriter::R_LeaveStore            },

    {NULL,                        ActorCodeWriter::R_UnknownReplaceKey     }
};

/*-------------------------------------------------------------------------*/
/*    Singleton Access                                                     */

ActorCodeWriter &
ActorCodeWriter::the(void)
{
    if(_the == NULL)
    {
        _the = new ActorCodeWriter();
    }

    return *_the;
}

/*-------------------------------------------------------------------------*/
/*    Destructor                                                           */

ActorCodeWriter::~ActorCodeWriter(void)
{
}

/*-------------------------------------------------------------------------*/
/*    Wite Code                                                            */

bool
ActorCodeWriter::writeBaseCodeDec(std::ostream &outStream,
                                  ActorDesc    *pActorDesc)
{
    writeTemplate(outStream, pActorDesc, ActorBaseTemplate_h);

    return true;
}

bool
ActorCodeWriter::writeBaseCodeImp(std::ostream &outStream,
                                  ActorDesc    *pActorDesc)
{
    writeTemplate(outStream, pActorDesc, ActorBaseTemplate_cpp);

    return true;
}

bool
ActorCodeWriter::writeBaseCodeInl(std::ostream &outStream,
                                  ActorDesc    *pActorDesc)
{
    writeTemplate(outStream, pActorDesc, ActorBaseTemplate_inl);

    return true;
}

bool
ActorCodeWriter::writeCodeDec(std::ostream &outStream,
                              ActorDesc    *pActorDesc)
{
    writeTemplate(outStream, pActorDesc, ActorTemplate_h);

    return true;
}

bool
ActorCodeWriter::writeCodeImp(std::ostream &outStream,
                              ActorDesc    *pActorDesc)
{
    writeTemplate(outStream, pActorDesc, ActorTemplate_cpp);

    return true;
}

bool
ActorCodeWriter::writeCodeInl(std::ostream &outStream,
                              ActorDesc    *pActorDesc)
{
    writeTemplate(outStream, pActorDesc, ActorTemplate_inl);

    return true;
}

/*-------------------------------------------------------------------------*/
/*    File Names                                                           */

std::string
ActorCodeWriter::getFilePrefix(ActorDesc *pActorDesc)
{
    std::string retValue;

    if(pActorDesc->getSystemComponent() == true)
    {
        retValue = "OSG";
    }
    else
    {
        retValue = "";
    }

    return retValue;
}

std::string
ActorCodeWriter::getBaseDecFileName(ActorDesc *pActorDesc)
{
    std::string retValue;

    if(pActorDesc->getActorName().empty() == false)
    {
        retValue.append(pActorDesc->getActorName());
        retValue.append("Base.h"                  );
    }

    return retValue;
}

std::string
ActorCodeWriter::getBaseImpFileName(ActorDesc *pActorDesc)
{
    std::string retValue;

    if(pActorDesc->getActorName().empty() == false)
    {
        retValue.append(pActorDesc->getActorName());
        retValue.append("Base.cpp"                );
    }

    return retValue;
}


std::string
ActorCodeWriter::getBaseInlFileName(ActorDesc *pActorDesc)
{
    std::string retValue;

    if(pActorDesc->getActorName().empty() == false)
    {
        retValue.append(pActorDesc->getActorName());
        retValue.append("Base.inl"                );
    }

    return retValue;
}

std::string
ActorCodeWriter::getDecFileName(ActorDesc *pActorDesc)
{
        std::string retValue;

    if(pActorDesc->getActorName().empty() == false)
    {
        retValue.append(pActorDesc->getActorName());
        retValue.append(".h"                      );
    }

    return retValue;
}

std::string
ActorCodeWriter::getImpFileName(ActorDesc *pActorDesc)
{
    std::string retValue;

    if(pActorDesc->getActorName().empty() == false)
    {
        retValue.append(pActorDesc->getActorName());
        retValue.append(".cpp"                    );
    }

    return retValue;
}


std::string
ActorCodeWriter::getInlFileName(ActorDesc *pActorDesc)
{
    std::string retValue;

    if(pActorDesc->getActorName().empty() == false)
    {
        retValue.append(pActorDesc->getActorName());
        retValue.append(".inl"                    );
    }

    return retValue;
}

bool
ActorCodeWriter::writeTemplate(std::ostream  &outStream, ActorDesc *pActorDesc,
                               const char   **pTemplate                       )
{
    const char **pStateLoopStart;
    int          skipIf          = 0;
    bool         skipStateLoop   = false;
    bool         retValue        = true;

    ActorDesc::StateElemListIt itSE;
    ActorDesc::StateElemListIt endSE;

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
                pStateLoopStart = pTemplate;
                itSE            = pActorDesc->beginStateElems();
                endSE           = pActorDesc->endStateElems  ();

                if(itSE == endSE)
                    skipStateLoop = true;

                continue;
            }
            else if(strLine.compare(0, 16, "@@EndStateLoop@@") == 0)
            {
                if(skipStateLoop == true)
                {
                    skipStateLoop = false;

                    continue;
                }

                ++itSE;

                if(itSE != endSE)
                {
                    pTemplate = pStateLoopStart;
                }
                else
                {
                    skipStateLoop = false;
                }
            }
            else if(skipStateLoop == true)
            {
                continue;
            }
            else if(strLine.compare(0, 4, "@@if") == 0)
            {
                int  condStart  = 0;
                int  condIndex  = 0;
                bool bCondition = false;
                bool bNegate    = false;

                condStart = strLine.find_first_of    (" \t", condStart);
                condStart = strLine.find_first_not_of(" \t", condStart);

                if(strLine[condStart] == '!')
                {
                    condStart = strLine.find_first_not_of(" \t", ++condStart);
                    bNegate   = true;
                }

                std::string strCond(strLine.substr(condStart));

                bCondition = getCondition(strCond, pActorDesc, itSE);
                bCondition = bNegate    ? !bCondition : bCondition;
                skipIf     = bCondition ? 0           : 1;
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

                retValue = false;
            }
        }
        else if(skipStateLoop)
        {
            continue;
        }
        else // verbatim text
        {
            int         start        = 0;
            int         end          = 0;
            bool        bDone        = false;
            std::string replaceKey;
            std::string replaceValue;

            while(!bDone)
            {
                start = strLine.find("@!", 0, 2);
                end   = strLine.find("!@", 0, 2);

                if((start == std::string::npos) ||
                   (end   == std::string::npos)   )
                {
                    bDone = true;
                    break;
                }

                replaceKey.assign(strLine.substr(start, end + 2 - start));

                replaceValue = getReplacement(replaceKey, pActorDesc, itSE);

                strLine.replace(start, end + 2 - start, replaceValue);
            }

            outStream << strLine << std::endl;
        }
    }

    return retValue;
}

bool
ActorCodeWriter::getCondition(const std::string                &strCond,
                                    ActorDesc                  *pActorDesc,
                                    ActorDesc::StateElemListIt  itSE       )
{
    bool          retValue  = false;
    ConditionKeyE condKey   = C_UnknownConditionKey;

    for(UInt32 i = 0; _ConditionKeys[i]._strKey != NULL; ++i)
    {
        if(stringcasecmp(strCond.c_str(), _ConditionKeys[i]._strKey) == 0)
        {
            condKey = _ConditionKeys[i]._valKey;
            break;
        }
    }

    switch(condKey)
    {
    case ActorCodeWriter::C_UseLocalIncludes:
        retValue = pActorDesc->getUseLocalIncludes();
        break;

    case ActorCodeWriter::C_Library:
        retValue = !(pActorDesc->getLibraryName().empty());
        break;

    case ActorCodeWriter::C_StateElem_HAS_Header:
        retValue = !(itSE->getHeader().empty());
        break;

    case ActorCodeWriter::C_StateElem_IS_Public:
        retValue = (itSE->getAccess() == ActorDescConstants::Public);
        break;

    case ActorCodeWriter::C_StateElem_IS_Protected:
        retValue = (itSE->getAccess() == ActorDescConstants::Protected);
        break;

    case ActorCodeWriter::C_StateElem_IS_Hierarchical:
        retValue = itSE->getHierarchical();
        break;

    case ActorCodeWriter::C_EnterStore_IS_Empty:
        retValue = (pActorDesc->getEnterFunctorStore() ==
                    ActorDescConstants::Empty             );
        break;

    case ActorCodeWriter::C_LeaveStore_IS_Empty:
        retValue = (pActorDesc->getLeaveFunctorStore() ==
                    ActorDescConstants::Empty             );
        break;

    case ActorCodeWriter::C_EnterStore_IS_Simple:
        retValue = (pActorDesc->getEnterFunctorStore() ==
                    ActorDescConstants::Simple            );
        break;

    case ActorCodeWriter::C_LeaveStore_IS_Simple:
        retValue = (pActorDesc->getLeaveFunctorStore() ==
                    ActorDescConstants::Simple            );
        break;

    case ActorCodeWriter::C_EnterStore_IS_Single:
        retValue = (pActorDesc->getEnterFunctorStore() ==
                    ActorDescConstants::Single            );
        break;

    case ActorCodeWriter::C_LeaveStore_IS_Single:
        retValue = (pActorDesc->getLeaveFunctorStore() ==
                    ActorDescConstants::Single            );
        break;

    case ActorCodeWriter::C_EnterStore_IS_Multi:
        retValue = (pActorDesc->getEnterFunctorStore() ==
                    ActorDescConstants::Multi             );
        break;

    case ActorCodeWriter::C_LeaveStore_IS_Multi:
        retValue = (pActorDesc->getLeaveFunctorStore() ==
                    ActorDescConstants::Multi             );
        break;

    case ActorCodeWriter::C_HAS_Hierarchical_State:
    {
        ActorDesc::StateElemListIt iterState = pActorDesc->beginStateElems();
        ActorDesc::StateElemListIt endState  = pActorDesc->endStateElems  ();

        retValue = false;

        for(; iterState != endState; ++iterState)
        {
            if(iterState->getHierarchical() == true)
            {
                retValue = true;
                break;
            }
        }

        break;
    }

    case ActorCodeWriter::C_UnknownConditionKey:
    default:
        SWARNING << "ActorCodeWriter: encountered unknown condition: "
                 << strCond
                 << ". output may be corrupt."
                 << endLog;
        break;
    };

    return retValue;
}

std::string
ActorCodeWriter::getReplacement(const std::string                &strKey,
                                      ActorDesc                  *pActorDesc,
                                      ActorDesc::StateElemListIt  itSE       )
{
    std::string retValue;
    ReplaceKeyE replaceKey = R_UnknownReplaceKey;

    for(UInt32 i = 0; _ReplaceKeys[i]._strKey != NULL; ++i)
    {
        if(stringcmp(strKey.c_str(), _ReplaceKeys[i]._strKey) == 0)
        {
            replaceKey = _ReplaceKeys[i]._valKey;
            break;
        }
    }

    switch(replaceKey)
    {
    case ActorCodeWriter::R_Classname:
        retValue = pActorDesc->getActorName();
        break;

    case ActorCodeWriter::R_CLASSNAME:
        retValue = upCase(pActorDesc->getActorName());
        break;

    case ActorCodeWriter::R_ParentName:
        retValue = pActorDesc->getParentName();
        break;

    case ActorCodeWriter::R_ParentHeader:
        if(pActorDesc->getParentSystemComponent())
        {
            retValue = std::string("OSG") + pActorDesc->getParentName() +
                       std::string(".h");
        }
        else
        {
            retValue = pActorDesc->getParentName() + std::string(".h");
        }
        break;

    case ActorCodeWriter::R_Libname:
        retValue = pActorDesc->getLibraryName();
        break;

    case ActorCodeWriter::R_LIBNAME:
        retValue = upCase(pActorDesc->getLibraryName());
        break;

    case ActorCodeWriter::R_HeaderPrefix:
        retValue = pActorDesc->getSystemComponent() ? "" : "OpenSG/";
        break;

    case ActorCodeWriter::R_ParentHeaderPrefix:
        retValue = (pActorDesc->getSystemComponent()       ==
                    pActorDesc->getParentSystemComponent()    ) ? "" : "OpenSG/";
        break;

    case ActorCodeWriter::R_StateElemHeader:
        retValue = itSE->getHeader();
        break;

    case ActorCodeWriter::R_StateElemName:
        retValue = itSE->getName();
        break;

    case ActorCodeWriter::R_StateElemType:
        retValue = itSE->getType();
        break;

    case ActorCodeWriter::R_StateElemDefaultValue:
        retValue = itSE->getDefaultValue();
        break;

    case ActorCodeWriter::R_EnterStore:
        retValue = pActorDesc->getEnterFunctorStoreStr();
        break;

    case ActorCodeWriter::R_LeaveStore:
        retValue = pActorDesc->getLeaveFunctorStoreStr();
        break;

    case ActorCodeWriter::R_UnknownReplaceKey:
    default:
        SWARNING << "ActorCodeWriter: encountered unknown replace key: "
                 << strKey
                 << ". output may be corrupt."
                 << endLog;
        break;
    };

    return retValue;
}

std::string
ActorCodeWriter::upCase(const std::string &strIn)
{
    std::string                 retValue("");
    std::string::const_iterator itStr     = strIn.begin();
    std::string::const_iterator endStr    = strIn.end  ();

    for(; itStr != endStr; ++itStr)
    {
        retValue += std::toupper(*itStr);
    }

    return retValue;
}

/*------------------------------------------------------------------------*/
/*    cvs id's                                                            */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGActorCodeWriter.cpp,v 1.2 2004/09/13 09:45:20 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGACTORCODEWRITER_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGACTORCODEWRITER_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif

