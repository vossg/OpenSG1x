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

#ifndef _OSGACTORCODEWRITER_H_
#define _OSGACTORCODEWRITER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGActorDesc.h"

#include <string>
#include <ostream>

OSG_USING_NAMESPACE

class ActorCodeWriter
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Singleton Access                                          */
    /*! \{                                                                 */
    static ActorCodeWriter &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    ~ActorCodeWriter(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Write Code                                                */
    /*! \{                                                                 */

    bool writeBaseCodeDec(std::ostream &outStream, ActorDesc *pActorDesc);
    bool writeBaseCodeImp(std::ostream &outStream, ActorDesc *pActorDesc);
    bool writeBaseCodeInl(std::ostream &outStream, ActorDesc *pActorDesc);

    bool writeCodeDec    (std::ostream &outStream, ActorDesc *pActorDesc);
    bool writeCodeImp    (std::ostream &outStream, ActorDesc *pActorDesc);
    bool writeCodeInl    (std::ostream &outStream, ActorDesc *pActorDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    File Names                                                */
    /*! \{                                                                 */

    std::string getFilePrefix     (ActorDesc *pActorDesc);

    std::string getBaseDecFileName(ActorDesc *pActorDesc);
    std::string getBaseImpFileName(ActorDesc *pActorDesc);
    std::string getBaseInlFileName(ActorDesc *pActorDesc);

    std::string getDecFileName    (ActorDesc *pActorDesc);
    std::string getImpFileName    (ActorDesc *pActorDesc);
    std::string getInlFileName    (ActorDesc *pActorDesc);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    enum ConditionKeyE
    {
        C_UseLocalIncludes,
        C_Library,
        C_StateElem_HAS_Header,
        C_StateElem_IS_Public,
        C_StateElem_IS_Protected,
        C_StateElem_IS_Hierarchical,
        C_EnterStore_IS_Empty,
        C_LeaveStore_IS_Empty,
        C_EnterStore_IS_Simple,
        C_LeaveStore_IS_Simple,
        C_EnterStore_IS_Single,
        C_LeaveStore_IS_Single,
        C_EnterStore_IS_Multi,
        C_LeaveStore_IS_Multi,
        C_HAS_Hierarchical_State,

        C_UnknownConditionKey
    };

    struct ConditionKeyMap
    {
        const char    *_strKey;
        ConditionKeyE  _valKey;
    };

    enum ReplaceKeyE
    {
        R_Classname,
        R_CLASSNAME,
        R_ParentName,
        R_ParentHeader,
        R_Libname,
        R_LIBNAME,
        R_HeaderPrefix,
        R_ParentHeaderPrefix,
        R_StateElemHeader,
        R_StateElemName,
        R_StateElemType,
        R_StateElemDefaultValue,
        R_EnterStore,
        R_LeaveStore,

        R_UnknownReplaceKey
    };

    struct ReplaceKeyMap
    {
        const char   *_strKey;
        ReplaceKeyE   _valKey;
    };

    bool writeTemplate(std::ostream  &outStream, ActorDesc *pActorDesc,
                       char         **pTemplate                        );

    bool        getCondition  (const std::string                &strCond,
                                     ActorDesc                  *pActorDesc,
                                     ActorDesc::StateElemListIt  itSE       );
    std::string getReplacement(const std::string                &strKey,
                                     ActorDesc                  *pActorDesc,
                                     ActorDesc::StateElemListIt  itSE       );
    std::string upCase        (const std::string                &strIn      );


    static ActorCodeWriter *_the;

    static ConditionKeyMap _ConditionKeys[];
    static ReplaceKeyMap   _ReplaceKeys  [];
};

//#include "OSGActorCodeWriter.inl"

#define OSGACTORCODEWRITER_HEADER_CVSID "@(#)$Id: OSGActorCodeWriter.h,v 1.1 2004/04/20 13:06:50 neumannc Exp $"

#endif /* _OSGACTORCODEWRITER_H_ */
