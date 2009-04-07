/*---------------------------------------------------------------------------*\
 *                        OpenSG openNURBS SceneFileType                     *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2007-2008 by Seac02 S.r.l.     http://www.seac02.it         *
 * Copyright (C) 2008  by Patrik Mueller    muellerptr@users.sourceforge.net *
 * Copyright (C) 2008  by Akos Balazs       edhellon@cs.uni-bonn.de          *
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

#ifndef _OSGRHINOSCENEFILETYPE_H_
#define _OSGRHINOSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include <OSGContribDef.h>
#include <OSGBaseTypes.h>

#include <OSGSceneFileType.h>

OSG_BEGIN_NAMESPACE

/*!\brief OSGRhinoSceneFileType
*/

class OSG_CONTRIBLIB_DLLMAPPING RhinoSceneFileType : public SceneFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Static Get                                 */
    /*! \{                                                                 */

    static RhinoSceneFileType &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RhinoSceneFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual const Char8 *getName(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodePtr    read        (std::istream &is,
                                    const Char8 *fileNameOrExtension) const;
    
#ifndef OSG_DISABLE_DEPRECATED
    virtual NodePtr readFile(const Char8  *fileName) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Params                                      */
    /*! \{                                                                 */

    void setDoTessellation(bool doTessellation = true);
    void setTessellationError(float tessellationError = 0.1f);
    void setCurveInterpolationSteps(int steps=100);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    NodePtr read3DM(const Char8  *fileName) const;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static const Char8            *_suffixA[];
    static       RhinoSceneFileType  _the;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    RhinoSceneFileType(const Char8  *suffixArray[],
                           UInt16  suffixByteCount,
                           bool    override,
                           UInt32  overridePriority);

    RhinoSceneFileType(const RhinoSceneFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef SceneFileType Inherited;
   
    int m_curveInterpolationSteps;
    float m_tessellationError;
    bool m_bDoTessellation;

	
	// Configuration options
    
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const RhinoSceneFileType &source);
};

typedef RhinoSceneFileType* RhinoSceneFileTypeP;

OSG_END_NAMESPACE

#define OSGRHINOSCENEFILETYPE_HEADER_CVSID "@(#)$Id: OSGRhinoSceneFileType.h,v 1.2 2009/04/07 17:09:28 neumannc Exp $"

#endif // _OSGRHINOSCENEFILETYPE_H_
