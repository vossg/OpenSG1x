#ifndef _OSGQBIT_H_
#define _OSGQBIT_H_

#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include <OSGBase.h>

#include <OSGBaseTypes.h>
#include <OSGMField.h>
#include <OSGSField.h>


OSG_BEGIN_NAMESPACE

/*! \var typedef Char8 QBit;
 *  \brief Qbit (true, false, dont_care)
 *  \ingroup VolRen
 */

typedef UInt8 QBit;

/*! \brief QBit field traits
    \ingroup VolRen
    \ingroup SingleFields
    \ingroup MultiFields 
*/

template <>
struct FieldDataTraits1<QBit> : 
    public FieldTraitsIntegralRecurseMapper<QBit>
{
    static  DataType               _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFQBit";            }
    static Char8    *getMName     (void) { return "MFQBit";            }

    static QBit      getDefault   (void) { return 0;                   }

    static QBit      getFromString(      QBit   &outVal,
                                   const Char8 *&inVal)
    {
        if(inVal == NULL)
            return 0;

        if(inVal[0] == 'T' || inVal[0] == 't')
        {
            if(inVal[1] != 'R' && inVal[1] != 'r')
            {
                return 0;
            }

            if(inVal[2] != 'U' && inVal[2] != 'u')
            {
                return 0;
            }

            if(inVal[3] != 'E' && inVal[3] != 'e')
            {
                return 0;
            }

            outVal = 1;
        }
        else if(inVal[0] == 'F' || inVal[0] == 'f')
        {
            if(inVal[1] != 'A' && inVal[1] != 'a')
            {
                return 0;
            }

            if(inVal[2] != 'L' && inVal[2] != 'l')
            {
                return 0;
            }

            if(inVal[3] != 'S' && inVal[3] != 's')
            {
                return 0;
            }

            if(inVal[4] != 'E' && inVal[4] != 'e')
            {
                return 0;
            }

            outVal = 0;
        }
        else if(inVal[0] == 'A' || inVal[0] == 'a')
        {
            if(inVal[1] != 'U' && inVal[1] != 'u')
            {
                return 0;
            }

            if(inVal[2] != 'T' && inVal[2] != 't')
            {
                return 0;
            }

            if(inVal[3] != 'O' && inVal[3] != 'o')
            {
                return 0;
            }

            outVal = 2;
        }
        else
        {
            return 0;
        }
        
        return outVal;
    }


    static void      putToString   (const QBit                  &inVal,
                                          std::string           &outStr)
    {
        if(inVal == 1)
        {
            outStr.assign("TRUE");
        }
        else if(inVal == 0)
        {
            outStr.assign("FALSE");
        }
        else
        {
            outStr.assign("AUTO");
        }
    }
};

/*! \brief SFQBit
 *  \ingroup VolRen
 */

typedef SField<QBit, 1>     SFQBit;

#ifndef OSG_COMPILEQBITFIELDINST
OSG_DLLEXPORT_DECL2(SField, QBit, 1, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif
  

/*! \brief MFQBit
    \ingroup MultiFields
*/

typedef MField<QBit, 1>     MFQBit;

#ifndef OSG_COMPILEQBITFIELDINST
OSG_DLLEXPORT_DECL2(MField, QBit, 1, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#endif
