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

#ifndef _OSGACTORWRITER_H_
#define _OSGACTORWRITER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>

#include "OSGActorInfo.h"
#include "OSGStateElemInfo.h"

#include <iostream>
#include <string>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING ActorWriter
{
public:
     ActorWriter(void            );
     ActorWriter(ActorInfo *pInfo);

    ~ActorWriter(void            );

    void       setActorInfo(ActorInfo *pInfo);
    ActorInfo *getActorInfo(void            );

    std::string getCodeBaseDecFileName(void);
    std::string getCodeBaseImpFileName(void);
    std::string getCodeBaseInlFileName(void);

    std::string getCodeDecFileName    (void);
    std::string getCodeImpFileName    (void);
    std::string getCodeInlFileName    (void);    

    bool writeCodeBaseDec(const std::string  &outPath);
    bool writeCodeBaseDec(      std::ostream &os     );
    bool writeCodeBaseImp(const std::string  &outPath);
    bool writeCodeBaseImp(      std::ostream &os     );
    bool writeCodeBaseInl(const std::string  &outPath);
    bool writeCodeBaseInl(      std::ostream &os     );

    bool writeCodeDec    (const std::string  &outPath);
    bool writeCodeDec    (      std::ostream &os     );
    bool writeCodeImp    (const std::string  &outPath);
    bool writeCodeImp    (      std::ostream &os     );
    bool writeCodeInl    (const std::string  &outPath);
    bool writeCodeInl    (      std::ostream &os     );

private:
    bool writeTemplate(std::ostream &os, char **pTemplate);

    std::string getClassname         (      void              );
    std::string getCLASSNAME         (      void              );
    std::string getLibname           (      void              );
    std::string getLIBNAME           (      void              );
    std::string getHeaderPrefix      (      void              );
    std::string getParentName        (      void              );
    std::string getParentHeader      (      void              );
    std::string getParentHeaderPrefix(      void              );
    std::string getStateElemName     (      void              );
    std::string getStateElemType     (      void              );
    std::string getStateElemHeader   (      void              );
    std::string getStateElemDefault  (      void              );
    std::string getEnterStore        (      void              );
    std::string getLeaveStore        (      void              );

    std::string upCase               (const std::string &inStr   );
    int         strcasecmp           (const char        *string1,
                                      const char        *string2 );

    static char *_ConditionKeys[];
    static char *_ReplaceKeys  [];

    static std::string _filePrefix;
    static std::string _decFileSuffix;
    static std::string _impFileSuffix;
    static std::string _inlFileSuffix;

    ActorInfo                 *_pAI;
    ActorInfo::StateElemBagIt  _itStateElem;
};

OSG_END_NAMESPACE

#include "OSGActorWriter.inl"

#define OSGACTORWRITER_HEADER_CVSID "@(#)$Id: OSGActorWriter.h,v 1.2 2003/10/17 07:34:59 a-m-z Exp $"

#endif /* _OSGACTORWRITER_H_ */
