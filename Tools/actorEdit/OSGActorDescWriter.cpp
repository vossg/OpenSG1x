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

#include "OSGActorDescWriter.h"
#include "OSGActorDesc.h"
#include "OSGActorStateElemDesc.h"

#include <fstream>

OSG_USING_NAMESPACE

/*------------------------------------------------------------------------*/
/*    Static Member Init                                                  */

ActorDescWriter *ActorDescWriter::_the = NULL;

/*------------------------------------------------------------------------*/
/*    Singleton Access                                                    */

ActorDescWriter &
ActorDescWriter::the(void)
{
    if(_the == NULL)
    {
        _the = new ActorDescWriter();
    }

    return *_the;
}

/*------------------------------------------------------------------------*/
/*    Destructor                                                          */

ActorDescWriter::~ActorDescWriter(void)
{
}

/*------------------------------------------------------------------------*/
/*    Write                                                               */

void
ActorDescWriter::writeDesc(std::ostream &outStream, ActorDesc *pActorDesc)
{
    ActorDesc::StateElemListIt itSE  = pActorDesc->beginStateElems();
    ActorDesc::StateElemListIt endSE = pActorDesc->endStateElems  ();

    outStream << "<?xml version=\"1.0\"?>\n";

    outStream << "<Actor>\n";

    outStream << "    <Name>"
              << pActorDesc->getActorName()
              << "</Name>\n";

    outStream << "    <ParentName>"
              << pActorDesc->getParentName()
              << "</ParentName>\n";

    outStream << "    <EnterFunctorStore>"
              << pActorDesc->getEnterFunctorStoreStr()
              << "</EnterFunctorStore>\n";

    outStream << "    <LeaveFunctorStore>"
              << pActorDesc->getLeaveFunctorStoreStr()
              << "</LeaveFunctorStore>\n";

    outStream << "    <UseLocalIncludes>"
              << pActorDesc->getUseLocalIncludesStr()
              << "</UseLocalIncludes>\n";

    outStream << "    <SystemComponent>"
              << pActorDesc->getSystemComponentStr()
              << "</SystemComponent>\n";

    outStream << "    <ParentSystemComponent>"
              << pActorDesc->getParentSystemComponentStr()
              << "</ParentSystemComponent>\n";

    outStream << "    <LibraryName>"
              << pActorDesc->getLibraryName()
              << "</LibraryName>\n";

    outStream << "    <StateElements>\n";

    for(; itSE != endSE; ++itSE)
    {
        outStream << "        <StateElement>\n";

        outStream << "            <Name>"
                  << itSE->getName()            << "</Name>\n";
        outStream << "            <Type>"
                  << itSE->getType()            << "</Type>\n";
        outStream << "            <Access>"
                  << itSE->getAccessStr()       << "</Access>\n";
        outStream << "            <Hierarchical>"
                  << itSE->getHierarchicalStr() << "</Hierarchical>\n";
        outStream << "            <Header>"
                  << itSE->getHeader()          << "</Header>\n";
        outStream << "            <DefaultValue>"
                  << itSE->getDefaultValue()    << "</DefaultValue>\n";

        outStream << "        </StateElement>\n";
    }

    outStream << "    </StateElements>\n";
    outStream << "</Actor>\n";

    outStream << std::endl;
}

/*------------------------------------------------------------------------*/
/*    File Names                                                          */

std::string
ActorDescWriter::getDescFileName(ActorDesc *pActorDesc)
{
    std::string retValue;

    if(pActorDesc->getActorName().empty() == false)
    {
        if(pActorDesc->getSystemComponent() == true)
        {
            retValue.append("OSG");
        }

        retValue.append(pActorDesc->getActorName());
        retValue.append(".acd"                    );
    }

    return retValue;
}

/*------------------------------------------------------------------------*/
/*    Constructors                                                        */

ActorDescWriter::ActorDescWriter(void)
{
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGActorDescWriter.cpp,v 1.1 2004/04/20 13:06:50 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGACTORDESCWRITER_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGACTORDESCWRITER_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
