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





#ifndef _OSGMATRIXCAMERA_H_

#define _OSGMATRIXCAMERA_H_

#ifdef __sgi

#pragma once

#endif



//---------------------------------------------------------------------------

//  Includes

//---------------------------------------------------------------------------



#include <OSGConfig.h>



#include <OSGMatrixCameraBase.h>



OSG_BEGIN_NAMESPACE



/*! \brief Matrix Camera class. See \ref PageSystemWindowCameraMatrix for 

    a description.

*/



class OSG_SYSTEMLIB_DLLMAPPING MatrixCamera : public MatrixCameraBase

{



    /*==========================  PUBLIC  =================================*/

  public:

    

    /*---------------------------------------------------------------------*/

    /*! \name                    Class Get                                 */

    /*! \{                                                                 */



    static const char *getClassname(void) { return "MatrixCamera"; };

    

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/

    /*! \name                    transformation                            */

    /*! \{                                                                 */



    virtual void changed(BitVector whichField, 

                         UInt32    origin    );

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/

    /*! \name                   your_category                              */

    /*! \{                                                                 */



    virtual void draw( DrawAction * action, const Viewport& port );



    virtual void getProjection( Matrix& result, UInt32 width, UInt32 height );



    virtual void getViewing( Matrix& result, UInt32 width, UInt32 height); 



    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/

    /*! \name                    dump                                      */

    /*! \{                                                                 */



    virtual void dump(      UInt32    uiIndent = 0, 

                      const BitVector bvFlags  = 0) const;



    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/

  protected:

 

    /*---------------------------------------------------------------------*/

    /*! \name                    Constructors                              */

    /*! \{                                                                 */



    MatrixCamera(void);

    MatrixCamera(const MatrixCamera &source);

    

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/

    /*! \name                    Destructors                               */

    /*! \{                                                                 */



    virtual ~MatrixCamera(void); 

     

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/  

   

  private:



    typedef MatrixCameraBase Inherited;



    friend class FieldContainer;

    friend class MatrixCameraBase;



    static void initMethod( void );



    // prohibit default functions (move to 'public' if you need one)



    void operator =(const MatrixCamera &source);

};



//---------------------------------------------------------------------------

//   Exported Types

//---------------------------------------------------------------------------



typedef MatrixCamera *MatrixCameraP;



OSG_END_NAMESPACE



#include <OSGMatrixCameraBase.inl>

#include <OSGMatrixCamera.inl>



#define OSGMATRIXCAMERA_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.15 2002/06/01 10:37:25 vossg Exp $"



#endif /* _OSGMATRIXCAMERA_H_ */

