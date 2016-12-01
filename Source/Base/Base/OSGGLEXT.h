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

#ifndef _OSGGLEXT_H_
#define _OSGGLEXT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "OSGGL.h"
#endif

// Defines needed to support some OpenGLF extensions
// There's no way to get these from OpenGL. 
// The system just has to make sure they 
// are only used when the extensions are supported.

// All these are taken verbatim from the nVidia Linux glext.h

/*---------------------------------------------------------------------*/
/*! \name GL_EXT_secondary_color                                       */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_EXT_secondary_color
#define GL_EXT_secondary_color               1
#define GL_COLOR_SUM_EXT                     0x8458
#define GL_CURRENT_SECONDARY_COLOR_EXT       0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE_EXT    0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE_EXT    0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT  0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER_EXT 0x845D
#define GL_SECONDARY_COLOR_ARRAY_EXT         0x845E
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_multitexture                                          */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_ARB_multitexture
#define GL_ARB_multitexture               1
#define GL_TEXTURE0_ARB                   0x84C0
#define GL_TEXTURE1_ARB                   0x84C1
#define GL_TEXTURE2_ARB                   0x84C2
#define GL_TEXTURE3_ARB                   0x84C3
#define GL_TEXTURE4_ARB                   0x84C4
#define GL_TEXTURE5_ARB                   0x84C5
#define GL_TEXTURE6_ARB                   0x84C6
#define GL_TEXTURE7_ARB                   0x84C7
#define GL_TEXTURE8_ARB                   0x84C8
#define GL_TEXTURE9_ARB                   0x84C9
#define GL_TEXTURE10_ARB                  0x84CA
#define GL_TEXTURE11_ARB                  0x84CB
#define GL_TEXTURE12_ARB                  0x84CC
#define GL_TEXTURE13_ARB                  0x84CD
#define GL_TEXTURE14_ARB                  0x84CE
#define GL_TEXTURE15_ARB                  0x84CF
#define GL_TEXTURE16_ARB                  0x84D0
#define GL_TEXTURE17_ARB                  0x84D1
#define GL_TEXTURE18_ARB                  0x84D2
#define GL_TEXTURE19_ARB                  0x84D3
#define GL_TEXTURE20_ARB                  0x84D4
#define GL_TEXTURE21_ARB                  0x84D5
#define GL_TEXTURE22_ARB                  0x84D6
#define GL_TEXTURE23_ARB                  0x84D7
#define GL_TEXTURE24_ARB                  0x84D8
#define GL_TEXTURE25_ARB                  0x84D9
#define GL_TEXTURE26_ARB                  0x84DA
#define GL_TEXTURE27_ARB                  0x84DB
#define GL_TEXTURE28_ARB                  0x84DC
#define GL_TEXTURE29_ARB                  0x84DD
#define GL_TEXTURE30_ARB                  0x84DE
#define GL_TEXTURE31_ARB                  0x84DF
#define GL_ACTIVE_TEXTURE_ARB             0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB      0x84E1
#define GL_MAX_TEXTURE_UNITS_ARB          0x84E2
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_texture_cube_map                                      */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_ARB_texture_cube_map
#define GL_ARB_texture_cube_map            1
#define GL_NORMAL_MAP_ARB                  0x8511
#define GL_REFLECTION_MAP_ARB              0x8512
#define GL_TEXTURE_CUBE_MAP_ARB            0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_ARB    0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB 0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARB      0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB   0x851C
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_texture_compression                                   */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

// This one is not really checked by the system, as it has no functions
#ifndef GL_ARB_texture_compression
#define GL_ARB_texture_compression            1
#define GL_COMPRESSED_ALPHA_ARB               0x84E9
#define GL_COMPRESSED_LUMINANCE_ARB           0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA_ARB     0x84EB
#define GL_COMPRESSED_INTENSITY_ARB           0x84EC
#define GL_COMPRESSED_RGB_ARB                 0x84ED
#define GL_COMPRESSED_RGBA_ARB                0x84EE
#define GL_TEXTURE_COMPRESSION_HINT_ARB       0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB  0x86A0
#define GL_TEXTURE_COMPRESSED_ARB             0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS_ARB     0x86A3
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_EXT_texture3D                                             */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_EXT_texture3D
#define GL_EXT_texture3D				  1
#define GL_PACK_SKIP_IMAGES               0x806B
#define GL_PACK_SKIP_IMAGES_EXT           0x806B
#define GL_PACK_IMAGE_HEIGHT              0x806C
#define GL_PACK_IMAGE_HEIGHT_EXT          0x806C
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_SKIP_IMAGES_EXT         0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_UNPACK_IMAGE_HEIGHT_EXT        0x806E
#define GL_TEXTURE_3D                     0x806F
#define GL_TEXTURE_3D_EXT                 0x806F
#define GL_PROXY_TEXTURE_3D               0x8070
#define GL_PROXY_TEXTURE_3D_EXT           0x8070
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_DEPTH_EXT              0x8071
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_TEXTURE_WRAP_R_EXT             0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_MAX_3D_TEXTURE_SIZE_EXT        0x8073
#else
#if defined(GL_EXT_texture3D) && ! defined(GL_TEXTURE_3D)
#define GL_PACK_SKIP_IMAGES               0x806B
#define GL_PACK_IMAGE_HEIGHT              0x806C
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_PROXY_TEXTURE_3D               0x8070
#define GL_TEXTURE_3D                     0x806F
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#endif
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_EXT_texture                                               */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_EXT_texture
#define GL_EXT_texture                    1
#define GL_ALPHA4_EXT                     0x803B
#define GL_ALPHA8_EXT                     0x803C
#define GL_ALPHA12_EXT                    0x803D
#define GL_ALPHA16_EXT                    0x803E
#define GL_LUMINANCE4_EXT                 0x803F
#define GL_LUMINANCE8_EXT                 0x8040
#define GL_LUMINANCE12_EXT                0x8041
#define GL_LUMINANCE16_EXT                0x8042
#define GL_LUMINANCE4_ALPHA4_EXT          0x8043
#define GL_LUMINANCE6_ALPHA2_EXT          0x8044
#define GL_LUMINANCE8_ALPHA8_EXT          0x8045
#define GL_LUMINANCE12_ALPHA4_EXT         0x8046
#define GL_LUMINANCE12_ALPHA12_EXT        0x8047
#define GL_LUMINANCE16_ALPHA16_EXT        0x8048
#define GL_INTENSITY_EXT                  0x8049
#define GL_INTENSITY4_EXT                 0x804A
#define GL_INTENSITY8_EXT                 0x804B
#define GL_INTENSITY12_EXT                0x804C
#define GL_INTENSITY16_EXT                0x804D
#define GL_RGB2_EXT                       0x804E
#define GL_RGB4_EXT                       0x804F
#define GL_RGB5_EXT                       0x8050
#define GL_RGB8_EXT                       0x8051
#define GL_RGB10_EXT                      0x8052
#define GL_RGB12_EXT                      0x8053
#define GL_RGB16_EXT                      0x8054
#define GL_RGBA2_EXT                      0x8055
#define GL_RGBA4_EXT                      0x8056
#define GL_RGB5_A1_EXT                    0x8057
#define GL_RGBA8_EXT                      0x8058
#define GL_RGB10_A2_EXT                   0x8059
#define GL_RGBA12_EXT                     0x805A
#define GL_RGBA16_EXT                     0x805B
#define GL_TEXTURE_RED_SIZE_EXT           0x805C
#define GL_TEXTURE_GREEN_SIZE_EXT         0x805D
#define GL_TEXTURE_BLUE_SIZE_EXT          0x805E
#define GL_TEXTURE_ALPHA_SIZE_EXT         0x805F
#define GL_TEXTURE_LUMINANCE_SIZE_EXT     0x8060
#define GL_TEXTURE_INTENSITY_SIZE_EXT     0x8061
#define GL_REPLACE_EXT                    0x8062
#define GL_PROXY_TEXTURE_1D_EXT           0x8063
#define GL_PROXY_TEXTURE_2D_EXT           0x8064
#define GL_TEXTURE_TOO_LARGE_EXT          0x8065
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_EXT_texture_integer                                       */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_EXT_texture_integer
#define GL_EXT_texture_integer            1
#define GL_RGBA32UI_EXT                   0x8D70
#define GL_RGB32UI_EXT                    0x8D71
#define GL_ALPHA32UI_EXT                  0x8D72
#define GL_INTENSITY32UI_EXT              0x8D73
#define GL_LUMINANCE32UI_EXT              0x8D74
#define GL_LUMINANCE_ALPHA32UI_EXT        0x8D75
#define GL_RGBA16UI_EXT                   0x8D76
#define GL_RGB16UI_EXT                    0x8D77
#define GL_ALPHA16UI_EXT                  0x8D78
#define GL_INTENSITY16UI_EXT              0x8D79
#define GL_LUMINANCE16UI_EXT              0x8D7A
#define GL_LUMINANCE_ALPHA16UI_EXT        0x8D7B
#define GL_RGBA8UI_EXT                    0x8D7C
#define GL_RGB8UI_EXT                     0x8D7D
#define GL_ALPHA8UI_EXT                   0x8D7E
#define GL_INTENSITY8UI_EXT               0x8D7F
#define GL_LUMINANCE8UI_EXT               0x8D80
#define GL_LUMINANCE_ALPHA8UI_EXT         0x8D81
#define GL_RGBA32I_EXT                    0x8D82
#define GL_RGB32I_EXT                     0x8D83
#define GL_ALPHA32I_EXT                   0x8D84
#define GL_INTENSITY32I_EXT               0x8D85
#define GL_LUMINANCE32I_EXT               0x8D86
#define GL_LUMINANCE_ALPHA32I_EXT         0x8D87
#define GL_RGBA16I_EXT                    0x8D88
#define GL_RGB16I_EXT                     0x8D89
#define GL_ALPHA16I_EXT                   0x8D8A
#define GL_INTENSITY16I_EXT               0x8D8B
#define GL_LUMINANCE16I_EXT               0x8D8C
#define GL_LUMINANCE_ALPHA16I_EXT         0x8D8D
#define GL_RGBA8I_EXT                     0x8D8E
#define GL_RGB8I_EXT                      0x8D8F
#define GL_ALPHA8I_EXT                    0x8D90
#define GL_INTENSITY8I_EXT                0x8D91
#define GL_LUMINANCE8I_EXT                0x8D92
#define GL_LUMINANCE_ALPHA8I_EXT          0x8D93
#define GL_RED_INTEGER_EXT                0x8D94
#define GL_GREEN_INTEGER_EXT              0x8D95
#define GL_BLUE_INTEGER_EXT               0x8D96
#define GL_ALPHA_INTEGER_EXT              0x8D97
#define GL_RGB_INTEGER_EXT                0x8D98
#define GL_RGBA_INTEGER_EXT               0x8D99
#define GL_BGR_INTEGER_EXT                0x8D9A
#define GL_BGRA_INTEGER_EXT               0x8D9B
#define GL_LUMINANCE_INTEGER_EXT          0x8D9C
#define GL_LUMINANCE_ALPHA_INTEGER_EXT    0x8D9D
#define GL_RGBA_INTEGER_MODE_EXT          0x8D9E
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_NV_register_combiners                                     */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_NV_register_combiners
#define GL_NV_register_combiners          1
#define GL_REGISTER_COMBINERS_NV          0x8522
#define GL_VARIABLE_A_NV                  0x8523
#define GL_VARIABLE_B_NV                  0x8524
#define GL_VARIABLE_C_NV                  0x8525
#define GL_VARIABLE_D_NV                  0x8526
#define GL_VARIABLE_E_NV                  0x8527
#define GL_VARIABLE_F_NV                  0x8528
#define GL_VARIABLE_G_NV                  0x8529
#define GL_CONSTANT_COLOR0_NV             0x852A
#define GL_CONSTANT_COLOR1_NV             0x852B
#define GL_PRIMARY_COLOR_NV               0x852C
#define GL_SECONDARY_COLOR_NV             0x852D
#define GL_SPARE0_NV                      0x852E
#define GL_SPARE1_NV                      0x852F
#define GL_DISCARD_NV                     0x8530
#define GL_E_TIMES_F_NV                   0x8531
#define GL_SPARE0_PLUS_SECONDARY_COLOR_NV 0x8532
#define GL_UNSIGNED_IDENTITY_NV           0x8536
#define GL_UNSIGNED_INVERT_NV             0x8537
#define GL_EXPAND_NORMAL_NV               0x8538
#define GL_EXPAND_NEGATE_NV               0x8539
#define GL_HALF_BIAS_NORMAL_NV            0x853A
#define GL_HALF_BIAS_NEGATE_NV            0x853B
#define GL_SIGNED_IDENTITY_NV             0x853C
#define GL_SIGNED_NEGATE_NV               0x853D
#define GL_SCALE_BY_TWO_NV                0x853E
#define GL_SCALE_BY_FOUR_NV               0x853F
#define GL_SCALE_BY_ONE_HALF_NV           0x8540
#define GL_BIAS_BY_NEGATIVE_ONE_HALF_NV   0x8541
#define GL_COMBINER_INPUT_NV              0x8542
#define GL_COMBINER_MAPPING_NV            0x8543
#define GL_COMBINER_COMPONENT_USAGE_NV    0x8544
#define GL_COMBINER_AB_DOT_PRODUCT_NV     0x8545
#define GL_COMBINER_CD_DOT_PRODUCT_NV     0x8546
#define GL_COMBINER_MUX_SUM_NV            0x8547
#define GL_COMBINER_SCALE_NV              0x8548
#define GL_COMBINER_BIAS_NV               0x8549
#define GL_COMBINER_AB_OUTPUT_NV          0x854A
#define GL_COMBINER_CD_OUTPUT_NV          0x854B
#define GL_COMBINER_SUM_OUTPUT_NV         0x854C
#define GL_MAX_GENERAL_COMBINERS_NV       0x854D
#define GL_NUM_GENERAL_COMBINERS_NV       0x854E
#define GL_COLOR_SUM_CLAMP_NV             0x854F
#define GL_COMBINER0_NV                   0x8550
#define GL_COMBINER1_NV                   0x8551
#define GL_COMBINER2_NV                   0x8552
#define GL_COMBINER3_NV                   0x8553
#define GL_COMBINER4_NV                   0x8554
#define GL_COMBINER5_NV                   0x8555
#define GL_COMBINER6_NV                   0x8556
#define GL_COMBINER7_NV                   0x8557
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_NV_register_combiners2                                    */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_NV_register_combiners2
#define GL_NV_register_combiners2        1
#define GL_PER_STAGE_CONSTANTS_NV        0x8535
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_multitexture                                          */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_EXT_paletted_texture
#define GL_EXT_paletted_texture 1

#if !defined(GL_TABLE_TOO_LARGE_EXT)
# define GL_TABLE_TOO_LARGE_EXT                  0x8031
#endif

#define GL_COLOR_TABLE_FORMAT_EXT               0x80D8
#define GL_COLOR_TABLE_WIDTH_EXT                0x80D9
#define GL_COLOR_TABLE_RED_SIZE_EXT             0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE_EXT           0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE_EXT            0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE_EXT           0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE_EXT       0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE_EXT       0x80DF
#define GL_TEXTURE_INDEX_SIZE_EXT               0x80ED
#define GL_COLOR_INDEX1_EXT                     0x80E2
#define GL_COLOR_INDEX2_EXT                     0x80E3
#define GL_COLOR_INDEX4_EXT                     0x80E4
#define GL_COLOR_INDEX8_EXT                     0x80E5
#define GL_COLOR_INDEX12_EXT                    0x80E6
#define GL_COLOR_INDEX16_EXT                    0x80E7

#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_multitexture                                          */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_EXT_shared_texture_palette
#define GL_EXT_shared_texture_palette           1
#define GL_SHARED_TEXTURE_PALETTE_EXT           0x81FB
#endif 

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name blend equation legacy handling                               */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

// Some legacy extension handling

// blend equation
// map the _EXT defines to the ARB_imaging defines, if necessary.
// Thus Apps can always use the ARB defines. 

#if defined(GL_FUNC_ADD_EXT) && ! defined(GL_FUNC_ADD)
#define GL_FUNC_ADD GL_FUNC_ADD_EXT
#else
#define GL_FUNC_ADD 0x8006
#endif

#if defined(GL_FUNC_SUBTRACT_EXT) && ! defined(GL_FUNC_SUBTRACT)
#define GL_FUNC_SUBTRACT GL_FUNC_SUBTRACT_EXT
#else
#define GL_FUNC_SUBTRACT 0x800A
#endif

#if   defined(GL_FUNC_REVERSE_SUBTRACT_EXT) && \
    ! defined(GL_FUNC_REVERSE_SUBTRACT)
#define GL_FUNC_REVERSE_SUBTRACT GL_FUNC_REVERSE_SUBTRACT_EXT
#else
#define GL_FUNC_REVERSE_SUBTRACT 0x800B
#endif

#if defined(GL_FUNC_MIN_EXT) && ! defined(GL_FUNC_MIN)
#define GL_FUNC_MIN GL_FUNC_MIN_EXT
#else
#define GL_FUNC_MIN 0x8007
#endif

#if defined(GL_FUNC_MAX_EXT) && ! defined(GL_FUNC_MAX)
#define GL_FUNC_MAX GL_FUNC_MAX_EXT
#else
#define GL_FUNC_MAX 0x8008
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_EXT_texture_env_combine                                   */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_EXT_texture_env_combine 
#define GL_EXT_texture_env_combine          1
#define GL_COMBINE_EXT                      0x8570
#define GL_COMBINE_RGB_EXT                  0x8571
#define GL_COMBINE_ALPHA_EXT                0x8572
#define GL_RGB_SCALE_EXT                    0x8573
#define GL_ADD_SIGNED_EXT                   0x8574
#define GL_INTERPOLATE_EXT                  0x8575
#define GL_CONSTANT_EXT                     0x8576
#define GL_PRIMARY_COLOR_EXT                0x8577
#define GL_PREVIOUS_EXT                     0x8578
#define GL_SOURCE0_RGB_EXT                  0x8580
#define GL_SOURCE1_RGB_EXT                  0x8581
#define GL_SOURCE2_RGB_EXT                  0x8582
#define GL_SOURCE0_ALPHA_EXT                0x8588
#define GL_SOURCE1_ALPHA_EXT                0x8589
#define GL_SOURCE2_ALPHA_EXT                0x858A
#define GL_OPERAND0_RGB_EXT                 0x8590
#define GL_OPERAND1_RGB_EXT                 0x8591
#define GL_OPERAND2_RGB_EXT                 0x8592
#define GL_OPERAND0_ALPHA_EXT               0x8598
#define GL_OPERAND1_ALPHA_EXT               0x8599
#define GL_OPERAND2_ALPHA_EXT               0x859A
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_point_parameters                                      */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_ARB_point_parameters
#define GL_ARB_point_parameters 1

#define GL_POINT_SIZE_MIN_ARB			    0x8126
#define GL_POINT_SIZE_MAX_ARB			    0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_ARB	0x8128
#define GL_POINT_DISTANCE_ATTENUATION_ARB   0x8129

#endif 

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_NV_point_sprite                                           */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_NV_point_sprite
#define GL_NV_point_sprite 1

#define GL_POINT_SPRITE_NV                     0x8861
#define GL_COORD_REPLACE_NV                    0x8862
#define GL_POINT_SPRITE_R_MODE_NV              0x8863

#endif 

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_vertex_program                                           */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_ARB_vertex_program
#define GL_ARB_vertex_program 1

#define GL_VERTEX_PROGRAM_ARB                              0x8620
#define GL_VERTEX_PROGRAM_POINT_SIZE_ARB                   0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_ARB                     0x8643
#define GL_COLOR_SUM_ARB                                   0x8458
#define GL_PROGRAM_FORMAT_ASCII_ARB                        0x8875
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB                 0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB                    0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB                  0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB                    0x8625
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB              0x886A
#define GL_CURRENT_VERTEX_ATTRIB_ARB                       0x8626
#define GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB                 0x8645
#define GL_PROGRAM_LENGTH_ARB                              0x8627
#define GL_PROGRAM_FORMAT_ARB                              0x8876
#define GL_PROGRAM_BINDING_ARB                             0x8677
#define GL_PROGRAM_INSTRUCTIONS_ARB                        0x88A0
#define GL_MAX_PROGRAM_INSTRUCTIONS_ARB                    0x88A1
#define GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB                 0x88A2
#define GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB             0x88A3
#define GL_PROGRAM_TEMPORARIES_ARB                         0x88A4
#define GL_MAX_PROGRAM_TEMPORARIES_ARB                     0x88A5
#define GL_PROGRAM_NATIVE_TEMPORARIES_ARB                  0x88A6
#define GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB              0x88A7
#define GL_PROGRAM_PARAMETERS_ARB                          0x88A8
#define GL_MAX_PROGRAM_PARAMETERS_ARB                      0x88A9
#define GL_PROGRAM_NATIVE_PARAMETERS_ARB                   0x88AA
#define GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB               0x88AB
#define GL_PROGRAM_ATTRIBS_ARB                             0x88AC
#define GL_MAX_PROGRAM_ATTRIBS_ARB                         0x88AD
#define GL_PROGRAM_NATIVE_ATTRIBS_ARB                      0x88AE
#define GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB                  0x88AF
#define GL_PROGRAM_ADDRESS_REGISTERS_ARB                   0x88B0
#define GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB               0x88B1
#define GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB            0x88B2
#define GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB        0x88B3
#define GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB                0x88B4
#define GL_MAX_PROGRAM_ENV_PARAMETERS_ARB                  0x88B5
#define GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB                 0x88B6
#define GL_PROGRAM_STRING_ARB                              0x8628
#define GL_PROGRAM_ERROR_POSITION_ARB                      0x864B
#define GL_CURRENT_MATRIX_ARB                              0x8641
#define GL_TRANSPOSE_CURRENT_MATRIX_ARB                    0x88B7
#define GL_CURRENT_MATRIX_STACK_DEPTH_ARB                  0x8640
#define GL_MAX_VERTEX_ATTRIBS_ARB                          0x8869
#define GL_MAX_PROGRAM_MATRICES_ARB                        0x862F
#define GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB              0x862E
#define GL_PROGRAM_ERROR_STRING_ARB                        0x8874
#define GL_MATRIX0_ARB                                     0x88C0
#define GL_MATRIX1_ARB                                     0x88C1
#define GL_MATRIX2_ARB                                     0x88C2
#define GL_MATRIX3_ARB                                     0x88C3
#define GL_MATRIX4_ARB                                     0x88C4
#define GL_MATRIX5_ARB                                     0x88C5
#define GL_MATRIX6_ARB                                     0x88C6
#define GL_MATRIX7_ARB                                     0x88C7
#define GL_MATRIX8_ARB                                     0x88C8
#define GL_MATRIX9_ARB                                     0x88C9
#define GL_MATRIX10_ARB                                    0x88CA
#define GL_MATRIX11_ARB                                    0x88CB
#define GL_MATRIX12_ARB                                    0x88CC
#define GL_MATRIX13_ARB                                    0x88CD
#define GL_MATRIX14_ARB                                    0x88CE
#define GL_MATRIX15_ARB                                    0x88CF
#define GL_MATRIX16_ARB                                    0x88D0
#define GL_MATRIX17_ARB                                    0x88D1
#define GL_MATRIX18_ARB                                    0x88D2
#define GL_MATRIX19_ARB                                    0x88D3
#define GL_MATRIX20_ARB                                    0x88D4
#define GL_MATRIX21_ARB                                    0x88D5
#define GL_MATRIX22_ARB                                    0x88D6
#define GL_MATRIX23_ARB                                    0x88D7
#define GL_MATRIX24_ARB                                    0x88D8
#define GL_MATRIX25_ARB                                    0x88D9
#define GL_MATRIX26_ARB                                    0x88DA
#define GL_MATRIX27_ARB                                    0x88DB
#define GL_MATRIX28_ARB                                    0x88DC
#define GL_MATRIX29_ARB                                    0x88DD
#define GL_MATRIX30_ARB                                    0x88DE
#define GL_MATRIX31_ARB                                    0x88DF
#endif 

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_fragment_program                                      */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_ARB_fragment_program
#define GL_ARB_fragment_program 1

#define GL_FRAGMENT_PROGRAM_ARB                            0x8804
#define GL_PROGRAM_FORMAT_ASCII_ARB                        0x8875
#define GL_PROGRAM_LENGTH_ARB                              0x8627
#define GL_PROGRAM_FORMAT_ARB                              0x8876
#define GL_PROGRAM_BINDING_ARB                             0x8677
#define GL_PROGRAM_INSTRUCTIONS_ARB                        0x88A0
#define GL_MAX_PROGRAM_INSTRUCTIONS_ARB                    0x88A1
#define GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB                 0x88A2
#define GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB             0x88A3
#define GL_PROGRAM_TEMPORARIES_ARB                         0x88A4
#define GL_MAX_PROGRAM_TEMPORARIES_ARB                     0x88A5
#define GL_PROGRAM_NATIVE_TEMPORARIES_ARB                  0x88A6
#define GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB              0x88A7
#define GL_PROGRAM_PARAMETERS_ARB                          0x88A8
#define GL_MAX_PROGRAM_PARAMETERS_ARB                      0x88A9
#define GL_PROGRAM_NATIVE_PARAMETERS_ARB                   0x88AA
#define GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB               0x88AB
#define GL_PROGRAM_ATTRIBS_ARB                             0x88AC
#define GL_MAX_PROGRAM_ATTRIBS_ARB                         0x88AD
#define GL_PROGRAM_NATIVE_ATTRIBS_ARB                      0x88AE
#define GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB                  0x88AF
#define GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB                0x88B4
#define GL_MAX_PROGRAM_ENV_PARAMETERS_ARB                  0x88B5
#define GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB                 0x88B6
#define GL_PROGRAM_ALU_INSTRUCTIONS_ARB                    0x8805
#define GL_PROGRAM_TEX_INSTRUCTIONS_ARB                    0x8806
#define GL_PROGRAM_TEX_INDIRECTIONS_ARB                    0x8807
#define GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB             0x8808
#define GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB             0x8809
#define GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB             0x880A
#define GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB                0x880B
#define GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB                0x880C
#define GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB                0x880D
#define GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB         0x880E
#define GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB         0x880F
#define GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB         0x8810
#define GL_PROGRAM_STRING_ARB                              0x8628
#define GL_PROGRAM_ERROR_POSITION_ARB                      0x864B
#define GL_CURRENT_MATRIX_ARB                              0x8641
#define GL_TRANSPOSE_CURRENT_MATRIX_ARB                    0x88B7
#define GL_CURRENT_MATRIX_STACK_DEPTH_ARB                  0x8640
#define GL_MAX_PROGRAM_MATRICES_ARB                        0x862F
#define GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB              0x862E
#define GL_MAX_TEXTURE_COORDS_ARB                          0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_ARB                     0x8872
#define GL_PROGRAM_ERROR_STRING_ARB                        0x8874
#define GL_MATRIX0_ARB                                     0x88C0
#define GL_MATRIX1_ARB                                     0x88C1
#define GL_MATRIX2_ARB                                     0x88C2
#define GL_MATRIX3_ARB                                     0x88C3
#define GL_MATRIX4_ARB                                     0x88C4
#define GL_MATRIX5_ARB                                     0x88C5
#define GL_MATRIX6_ARB                                     0x88C6
#define GL_MATRIX7_ARB                                     0x88C7
#define GL_MATRIX8_ARB                                     0x88C8
#define GL_MATRIX9_ARB                                     0x88C9
#define GL_MATRIX10_ARB                                    0x88CA
#define GL_MATRIX11_ARB                                    0x88CB
#define GL_MATRIX12_ARB                                    0x88CC
#define GL_MATRIX13_ARB                                    0x88CD
#define GL_MATRIX14_ARB                                    0x88CE
#define GL_MATRIX15_ARB                                    0x88CF
#define GL_MATRIX16_ARB                                    0x88D0
#define GL_MATRIX17_ARB                                    0x88D1
#define GL_MATRIX18_ARB                                    0x88D2
#define GL_MATRIX19_ARB                                    0x88D3
#define GL_MATRIX20_ARB                                    0x88D4
#define GL_MATRIX21_ARB                                    0x88D5
#define GL_MATRIX22_ARB                                    0x88D6
#define GL_MATRIX23_ARB                                    0x88D7
#define GL_MATRIX24_ARB                                    0x88D8
#define GL_MATRIX25_ARB                                    0x88D9
#define GL_MATRIX26_ARB                                    0x88DA
#define GL_MATRIX27_ARB                                    0x88DB
#define GL_MATRIX28_ARB                                    0x88DC
#define GL_MATRIX29_ARB                                    0x88DD
#define GL_MATRIX30_ARB                                    0x88DE
#define GL_MATRIX31_ARB                                    0x88DF

#endif 

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_NV_texture_shader                                         */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_NV_texture_shader
#define GL_NV_texture_shader 1

#define GL_OFFSET_TEXTURE_RECTANGLE_NV                      0x864C
#define GL_OFFSET_TEXTURE_RECTANGLE_SCALE_NV                0x864D
#define GL_DOT_PRODUCT_TEXTURE_RECTANGLE_NV                 0x864E
#define GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV             0x86D9
#define GL_UNSIGNED_INT_S8_S8_8_8_NV                        0x86DA
#define GL_UNSIGNED_INT_8_8_S8_S8_REV_NV                    0x86DB
#define GL_DSDT_MAG_INTENSITY_NV                            0x86DC
#define GL_SHADER_CONSISTENT_NV                             0x86DD
#define GL_TEXTURE_SHADER_NV                                0x86DE
#define GL_SHADER_OPERATION_NV                              0x86DF
#define GL_CULL_MODES_NV                                    0x86E0
#define GL_OFFSET_TEXTURE_MATRIX_NV                         0x86E1
#define GL_OFFSET_TEXTURE_SCALE_NV                          0x86E2
#define GL_OFFSET_TEXTURE_BIAS_NV                           0x86E3
#define GL_OFFSET_TEXTURE_2D_MATRIX_NV    GL_OFFSET_TEXTURE_MATRIX_NV
#define GL_OFFSET_TEXTURE_2D_SCALE_NV     GL_OFFSET_TEXTURE_SCALE_NV
#define GL_OFFSET_TEXTURE_2D_BIAS_NV      GL_OFFSET_TEXTURE_BIAS_NV
#define GL_PREVIOUS_TEXTURE_INPUT_NV                        0x86E4
#define GL_CONST_EYE_NV                                     0x86E5
#define GL_PASS_THROUGH_NV                                  0x86E6
#define GL_CULL_FRAGMENT_NV                                 0x86E7
#define GL_OFFSET_TEXTURE_2D_NV                             0x86E8
#define GL_DEPENDENT_AR_TEXTURE_2D_NV                       0x86E9
#define GL_DEPENDENT_GB_TEXTURE_2D_NV                       0x86EA
#define GL_DOT_PRODUCT_NV                                   0x86EC
#define GL_DOT_PRODUCT_DEPTH_REPLACE_NV                     0x86ED
#define GL_DOT_PRODUCT_TEXTURE_2D_NV                        0x86EE
#define GL_DOT_PRODUCT_TEXTURE_CUBE_MAP_NV                  0x86F0
#define GL_DOT_PRODUCT_DIFFUSE_CUBE_MAP_NV                  0x86F1
#define GL_DOT_PRODUCT_REFLECT_CUBE_MAP_NV                  0x86F2
#define GL_DOT_PRODUCT_CONST_EYE_REFLECT_CUBE_MAP_NV        0x86F3
#define GL_HILO_NV                                          0x86F4
#define GL_DSDT_NV                                          0x86F5
#define GL_DSDT_MAG_NV                                      0x86F6
#define GL_DSDT_MAG_VIB_NV                                  0x86F7
#define GL_HILO16_NV                                        0x86F8
#define GL_SIGNED_HILO_NV                                   0x86F9
#define GL_SIGNED_HILO16_NV                                 0x86FA
#define GL_SIGNED_RGBA_NV                                   0x86FB
#define GL_SIGNED_RGBA8_NV                                  0x86FC
#define GL_SIGNED_RGB_NV                                    0x86FE
#define GL_SIGNED_RGB8_NV                                   0x86FF
#define GL_SIGNED_LUMINANCE_NV                              0x8701
#define GL_SIGNED_LUMINANCE8_NV                             0x8702
#define GL_SIGNED_LUMINANCE_ALPHA_NV                        0x8703
#define GL_SIGNED_LUMINANCE8_ALPHA8_NV                      0x8704
#define GL_SIGNED_ALPHA_NV                                  0x8705
#define GL_SIGNED_ALPHA8_NV                                 0x8706
#define GL_SIGNED_INTENSITY_NV                              0x8707
#define GL_SIGNED_INTENSITY8_NV                             0x8708
#define GL_DSDT8_NV                                         0x8709
#define GL_DSDT8_MAG8_NV                                    0x870A
#define GL_DSDT8_MAG8_INTENSITY8_NV                         0x870B
#define GL_SIGNED_RGB_UNSIGNED_ALPHA_NV                     0x870C
#define GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV                   0x870D
#define GL_HI_SCALE_NV                                      0x870E
#define GL_LO_SCALE_NV                                      0x870F
#define GL_DS_SCALE_NV                                      0x8710
#define GL_DT_SCALE_NV                                      0x8711
#define GL_MAGNITUDE_SCALE_NV                               0x8712
#define GL_VIBRANCE_SCALE_NV                                0x8713
#define GL_HI_BIAS_NV                                       0x8714
#define GL_LO_BIAS_NV                                       0x8715
#define GL_DS_BIAS_NV                                       0x8716
#define GL_DT_BIAS_NV                                       0x8717
#define GL_MAGNITUDE_BIAS_NV                                0x8718
#define GL_VIBRANCE_BIAS_NV                                 0x8719
#define GL_TEXTURE_BORDER_VALUES_NV                         0x871A
#define GL_TEXTURE_HI_SIZE_NV                               0x871B
#define GL_TEXTURE_LO_SIZE_NV                               0x871C
#define GL_TEXTURE_DS_SIZE_NV                               0x871D
#define GL_TEXTURE_DT_SIZE_NV                               0x871E
#define GL_TEXTURE_MAG_SIZE_NV                              0x871F
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_NV_texture_shader2                                        */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_NV_texture_shader2
#define GL_NV_texture_shader2 1

#define DOT_PRODUCT_TEXTURE_3D_NV                           0x86EF
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_NV_texture_shader3                                        */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_NV_texture_shader3
#define GL_NV_texture_shader3 1

#define OFFSET_PROJECTIVE_TEXTURE_2D_NV                     0x8850
#define OFFSET_PROJECTIVE_TEXTURE_2D_SCALE_NV               0x8851
#define OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_NV              0x8852
#define OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_SCALE_NV        0x8853
#define OFFSET_HILO_TEXTURE_2D_NV                           0x8854
#define OFFSET_HILO_TEXTURE_RECTANGLE_NV                    0x8855
#define OFFSET_HILO_PROJECTIVE_TEXTURE_2D_NV                0x8856
#define OFFSET_HILO_PROJECTIVE_TEXTURE_RECTANGLE_NV         0x8857
#define DEPENDENT_HILO_TEXTURE_2D_NV                        0x8858
#define DEPENDENT_RGB_TEXTURE_3D_NV                         0x8859
#define DEPENDENT_RGB_TEXTURE_CUBE_MAP_NV                   0x885A
#define DOT_PRODUCT_PASS_THROUGH_NV                         0x885B
#define DOT_PRODUCT_TEXTURE_1D_NV                           0x885C
#define DOT_PRODUCT_AFFINE_DEPTH_REPLACE_NV                 0x885D
#define FORCE_BLUE_TO_ONE_NV                                0x8860

#endif


/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_SGIS_generate_mipmap                                      */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_SGIS_generate_mipmap
#define GL_SGIS_generate_mipmap 1

#define GL_GENERATE_MIPMAP_SGIS                             0x8191
#define GL_GENERATE_MIPMAP_HINT_SGIS                        0x8192

#endif
/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_EXT_texture_lod_bias                                      */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_EXT_texture_lod_bias
#define GL_EXT_texture_lod_bias 1

#define GL_TEXTURE_FILTER_CONTROL_EXT                       0x8500
#define GL_TEXTURE_LOD_BIAS_EXT                             0x8501
#define GL_MAX_TEXTURE_LOD_BIAS_EXT                         0x84FD

#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_texture_rectangle                                     */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_ARB_texture_rectangle
#define GL_ARB_texture_rectangle            1

#define GL_TEXTURE_RECTANGLE_ARB                            0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_ARB                    0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_ARB                      0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB                   0x84F8
#endif 

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_EXT_texture_rectangle                                     */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_EXT_texture_rectangle
#define GL_EXT_texture_rectangle            1

#define GL_TEXTURE_RECTANGLE_EXT                            0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_EXT                    0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_EXT                      0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_EXT                   0x84F8
#endif 

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_texture_float                                         */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */
#ifndef GL_ARB_texture_float
#define GL_ARB_texture_float 1

#define GL_TEXTURE_RED_TYPE_ARB           0x8C10
#define GL_TEXTURE_GREEN_TYPE_ARB         0x8C11
#define GL_TEXTURE_BLUE_TYPE_ARB          0x8C12
#define GL_TEXTURE_ALPHA_TYPE_ARB         0x8C13
#define GL_TEXTURE_LUMINANCE_TYPE_ARB     0x8C14
#define GL_TEXTURE_INTENSITY_TYPE_ARB     0x8C15
#define GL_TEXTURE_DEPTH_TYPE_ARB         0x8C16
#define GL_UNSIGNED_NORMALIZED_ARB        0x8C17
#define GL_RGBA32F_ARB                    0x8814
#define GL_RGB32F_ARB                     0x8815
#define GL_ALPHA32F_ARB                   0x8816
#define GL_INTENSITY32F_ARB               0x8817
#define GL_LUMINANCE32F_ARB               0x8818
#define GL_LUMINANCE_ALPHA32F_ARB         0x8819
#define GL_RGBA16F_ARB                    0x881A
#define GL_RGB16F_ARB                     0x881B
#define GL_ALPHA16F_ARB                   0x881C
#define GL_INTENSITY16F_ARB               0x881D
#define GL_LUMINANCE16F_ARB               0x881E
#define GL_LUMINANCE_ALPHA16F_ARB         0x881F
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_shader_objects                                        */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_ARB_shader_objects
#define GL_ARB_shader_objects 1

#define GL_PROGRAM_OBJECT_ARB                               0x8B40
#define GL_SHADER_OBJECT_ARB                                0x8B48
#define GL_OBJECT_TYPE_ARB                                  0x8B4E
#define GL_OBJECT_SUBTYPE_ARB                               0x8B4F
#define GL_FLOAT_VEC2_ARB                                   0x8B50
#define GL_FLOAT_VEC3_ARB                                   0x8B51
#define GL_FLOAT_VEC4_ARB                                   0x8B52
#define GL_INT_VEC2_ARB                                     0x8B53
#define GL_INT_VEC3_ARB                                     0x8B54
#define GL_INT_VEC4_ARB                                     0x8B55
#define GL_BOOL_ARB                                         0x8B56
#define GL_BOOL_VEC2_ARB                                    0x8B57
#define GL_BOOL_VEC3_ARB                                    0x8B58
#define GL_BOOL_VEC4_ARB                                    0x8B59
#define GL_FLOAT_MAT2_ARB                                   0x8B5A
#define GL_FLOAT_MAT3_ARB                                   0x8B5B
#define GL_FLOAT_MAT4_ARB                                   0x8B5C
#define GL_OBJECT_DELETE_STATUS_ARB                         0x8B80
#define GL_OBJECT_COMPILE_STATUS_ARB                        0x8B81
#define GL_OBJECT_LINK_STATUS_ARB                           0x8B82
#define GL_OBJECT_VALIDATE_STATUS_ARB                       0x8B83
#define GL_OBJECT_INFO_LOG_LENGTH_ARB                       0x8B84
#define GL_OBJECT_ATTACHED_OBJECTS_ARB                      0x8B85
#define GL_OBJECT_ACTIVE_UNIFORMS_ARB                       0x8B86
#define GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB             0x8B87
#define GL_OBJECT_SHADER_SOURCE_LENGTH_ARB                  0x8B88

#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_EXT_geometry_shader4                                      */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_EXT_geometry_shader4
#define GL_EXT_geometry_shader4 1

#define GL_GEOMETRY_SHADER_EXT                      0x8DD9
#define GL_MAX_GEOMETRY_VARYING_COMPONENTS_EXT      0x8DDD
#define GL_MAX_VERTEX_VARYING_COMPONENTS_EXT        0x8DDE
#define GL_MAX_VARYING_COMPONENTS_EXT               0x8B4B
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT      0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT         0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT 0x8DE1
#define GL_GEOMETRY_VERTICES_OUT_EXT                0x8DDA
#define GL_GEOMETRY_INPUT_TYPE_EXT                  0x8DDB
#define GL_GEOMETRY_OUTPUT_TYPE_EXT                 0x8DDC
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT     0x8C29
#define GL_LINES_ADJACENCY_EXT                      0xA
#define GL_LINE_STRIP_ADJACENCY_EXT                 0xB
#define GL_TRIANGLES_ADJACENCY_EXT                  0xC
#define GL_TRIANGLE_STRIP_ADJACENCY_EXT             0xD
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT       0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8DA8
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_EXT   0x8DA9
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_EXT 0x8CD4
#define GL_PROGRAM_POINT_SIZE_EXT                   0x8642
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_vertex_shader                                         */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_ARB_vertex_shader
#define GL_ARB_vertex_shader 1

#define GL_VERTEX_SHADER_ARB                                0x8B31
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB                0x8B4A
#define GL_MAX_VARYING_FLOATS_ARB                           0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB               0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB             0x8B4D
#define GL_OBJECT_ACTIVE_ATTRIBUTES_ARB                     0x8B89
#define GL_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB           0x8B8A

#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_fragment_shader                                       */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_ARB_fragment_shader
#define GL_ARB_fragment_shader 1

#define GL_FRAGMENT_SHADER_ARB                              0x8B30
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB              0x8B49

#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_shading_language_100                                  */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_ARB_shading_language_100
#define GL_ARB_shading_language_100 1
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_ARB_vertex_buffer_object                                  */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_ARB_vertex_buffer_object
#define GL_ARB_vertex_buffer_object 1

#define GL_ARRAY_BUFFER_ARB               0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB       0x8893
#define GL_ARRAY_BUFFER_BINDING_ARB       0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB 0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING_ARB 0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING_ARB 0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING_ARB 0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING_ARB 0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB 0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB 0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB 0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB 0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB 0x889E
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB 0x889F
#define GL_STREAM_DRAW_ARB                0x88E0
#define GL_STREAM_READ_ARB                0x88E1
#define GL_STREAM_COPY_ARB                0x88E2
#define GL_STATIC_DRAW_ARB                0x88E4
#define GL_STATIC_READ_ARB                0x88E5
#define GL_STATIC_COPY_ARB                0x88E6
#define GL_DYNAMIC_DRAW_ARB               0x88E8
#define GL_DYNAMIC_READ_ARB               0x88E9
#define GL_DYNAMIC_COPY_ARB               0x88EA
#define GL_READ_ONLY_ARB                  0x88B8
#define GL_WRITE_ONLY_ARB                 0x88B9
#define GL_READ_WRITE_ARB                 0x88BA
#define GL_BUFFER_SIZE_ARB                0x8764
#define GL_BUFFER_USAGE_ARB               0x8765
#define GL_BUFFER_ACCESS_ARB              0x88BB
#define GL_BUFFER_MAPPED_ARB              0x88BC
#define GL_BUFFER_MAP_POINTER_ARB         0x88BD

#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_EXT_Cg_shader                                                */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */

#ifndef GL_EXT_Cg_shader
#define GL_EXT_Cg_shader 1

#define GL_CG_VERTEX_SHADER_EXT           0x890E
#define GL_CG_FRAGMENT_SHADER_EXT         0x890F

#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_NV_occlusion_query                                        */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */
/*! \}                                                                 */
/*---------------------------------------------------------------------*/

#ifndef GL_NV_occlusion_query
#define GL_NV_occlusion_query 1
#define GL_PIXEL_COUNTER_BITS_NV          0x8864
#define GL_CURRENT_OCCLUSION_QUERY_ID_NV  0x8865
#define GL_PIXEL_COUNT_NV                 0x8866
#define GL_PIXEL_COUNT_AVAILABLE_NV       0x8867
#endif

#ifndef GL_ARB_occlusion_query
#define GL_ARB_occlusion_query 1
#define GL_QUERY_COUNTER_BITS_ARB           0x8864
#define GL_CURRENT_QUERY_ARB                0x8865
#define GL_QUERY_RESULT_ARB                 0x8866
#define GL_QUERY_RESULT_AVAILABLE_ARB       0x8867
#define GL_SAMPLES_PASSED_ARB               0x8914
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name GL_HP_occlusion_test                                         */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */
/*! \}                                                                 */
/*---------------------------------------------------------------------*/

#ifndef GL_HP_occlusion_test
#define GL_HP_occlusion_test 1
#define GL_OCCLUSION_TEST_HP              0x8165
#define GL_OCCLUSION_TEST_RESULT_HP       0x8166
#endif

/*---------------------------------------------------------------------*/
/*! \name GL_EXT_texture_compression_s3tc                              */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */
/*! \}                                                                 */
/*---------------------------------------------------------------------*/
#ifndef GL_EXT_texture_compression_s3tc
#define GL_EXT_texture_compression_s3tc 1
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#endif

/*---------------------------------------------------------------------*/
/*! \name GL_EXT_texture_filter_anisotropic                            */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */
/*! \}                                                                 */
/*---------------------------------------------------------------------*/
#ifndef GL_EXT_texture_filter_anisotropic
#define GL_EXT_texture_filter_anisotropic 1
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif

/*---------------------------------------------------------------------*/
/*! \name GL_NV_half_float                                             */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */
/*! \}                                                                 */
/*---------------------------------------------------------------------*/
#ifndef GL_NV_half_float
#define GL_HALF_FLOAT_NV                  0x140B
#endif

/*---------------------------------------------------------------------*/
/*! \name GL_EXT_blend_func_separate                                   */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */
/*! \}                                                                 */
/*---------------------------------------------------------------------*/

#ifndef GL_EXT_blend_func_separate
#define GL_BLEND_DST_RGB_EXT              0x80C8
#define GL_BLEND_SRC_RGB_EXT              0x80C9
#define GL_BLEND_DST_ALPHA_EXT            0x80CA
#define GL_BLEND_SRC_ALPHA_EXT            0x80CB
#endif


#ifndef GL_VERSION_1_2
#define GL_UNSIGNED_BYTE_3_3_2            0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_INT_8_8_8_8           0x8035
#define GL_UNSIGNED_INT_10_10_10_2        0x8036
#define GL_RESCALE_NORMAL                 0x803A
#define GL_TEXTURE_BINDING_3D             0x806A
#define GL_PACK_SKIP_IMAGES               0x806B
#define GL_PACK_IMAGE_HEIGHT              0x806C
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_TEXTURE_3D                     0x806F
#define GL_PROXY_TEXTURE_3D               0x8070
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_UNSIGNED_BYTE_2_3_3_REV        0x8362
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV       0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV     0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV     0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#define GL_BGR                            0x80E0
#define GL_BGRA                           0x80E1
#define GL_MAX_ELEMENTS_VERTICES          0x80E8
#define GL_MAX_ELEMENTS_INDICES           0x80E9
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_TEXTURE_MIN_LOD                0x813A
#define GL_TEXTURE_MAX_LOD                0x813B
#define GL_TEXTURE_BASE_LEVEL             0x813C
#define GL_TEXTURE_MAX_LEVEL              0x813D
#define GL_LIGHT_MODEL_COLOR_CONTROL      0x81F8
#define GL_SINGLE_COLOR                   0x81F9
#define GL_SEPARATE_SPECULAR_COLOR        0x81FA
#define GL_SMOOTH_POINT_SIZE_RANGE        0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY  0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE        0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY  0x0B23
#define GL_ALIASED_POINT_SIZE_RANGE       0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE       0x846E
#endif

/*---------------------------------------------------------------------*/
/*! \name GL_UNSIGNED_SHORT_5_6_5                                      */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */
/*! \}                                                                 */
/*---------------------------------------------------------------------*/

#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#endif


/*---------------------------------------------------------------------*/
/*! \name GL_ARB_imaging                                               */
/*! \ingroup GrpBaseBaseGLConstants                                    */
/*  \{                                                                 */
/*! \}                                                                 */
/*---------------------------------------------------------------------*/

#ifndef GL_ARB_imaging
#define GL_CONSTANT_COLOR                 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#define GL_CONSTANT_ALPHA                 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#define GL_BLEND_COLOR                    0x8005
#define GL_FUNC_ADD                       0x8006
#define GL_MIN                            0x8007
#define GL_MAX                            0x8008
#define GL_BLEND_EQUATION                 0x8009
#define GL_FUNC_SUBTRACT                  0x800A
#define GL_FUNC_REVERSE_SUBTRACT          0x800B
#define GL_CONVOLUTION_1D                 0x8010
#define GL_CONVOLUTION_2D                 0x8011
#define GL_SEPARABLE_2D                   0x8012
#define GL_CONVOLUTION_BORDER_MODE        0x8013
#define GL_CONVOLUTION_FILTER_SCALE       0x8014
#define GL_CONVOLUTION_FILTER_BIAS        0x8015
#define GL_REDUCE                         0x8016
#define GL_CONVOLUTION_FORMAT             0x8017
#define GL_CONVOLUTION_WIDTH              0x8018
#define GL_CONVOLUTION_HEIGHT             0x8019
#define GL_MAX_CONVOLUTION_WIDTH          0x801A
#define GL_MAX_CONVOLUTION_HEIGHT         0x801B
#define GL_POST_CONVOLUTION_RED_SCALE     0x801C
#define GL_POST_CONVOLUTION_GREEN_SCALE   0x801D
#define GL_POST_CONVOLUTION_BLUE_SCALE    0x801E
#define GL_POST_CONVOLUTION_ALPHA_SCALE   0x801F
#define GL_POST_CONVOLUTION_RED_BIAS      0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS    0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS     0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS    0x8023
#define GL_HISTOGRAM                      0x8024
#define GL_PROXY_HISTOGRAM                0x8025
#define GL_HISTOGRAM_WIDTH                0x8026
#define GL_HISTOGRAM_FORMAT               0x8027
#define GL_HISTOGRAM_RED_SIZE             0x8028
#define GL_HISTOGRAM_GREEN_SIZE           0x8029
#define GL_HISTOGRAM_BLUE_SIZE            0x802A
#define GL_HISTOGRAM_ALPHA_SIZE           0x802B
#define GL_HISTOGRAM_LUMINANCE_SIZE       0x802C
#define GL_HISTOGRAM_SINK                 0x802D
#define GL_MINMAX                         0x802E
#define GL_MINMAX_FORMAT                  0x802F
#define GL_MINMAX_SINK                    0x8030
#define GL_TABLE_TOO_LARGE                0x8031
#define GL_COLOR_MATRIX                   0x80B1
#define GL_COLOR_MATRIX_STACK_DEPTH       0x80B2
#define GL_MAX_COLOR_MATRIX_STACK_DEPTH   0x80B3
#define GL_POST_COLOR_MATRIX_RED_SCALE    0x80B4
#define GL_POST_COLOR_MATRIX_GREEN_SCALE  0x80B5
#define GL_POST_COLOR_MATRIX_BLUE_SCALE   0x80B6
#define GL_POST_COLOR_MATRIX_ALPHA_SCALE  0x80B7
#define GL_POST_COLOR_MATRIX_RED_BIAS     0x80B8
#define GL_POST_COLOR_MATRIX_GREEN_BIAS   0x80B9
#define GL_POST_COLOR_MATRIX_BLUE_BIAS    0x80BA
#define GL_POST_COLOR_MATRIX_ALPHA_BIAS   0x80BB
#define GL_COLOR_TABLE                    0x80D0
#define GL_POST_CONVOLUTION_COLOR_TABLE   0x80D1
#define GL_POST_COLOR_MATRIX_COLOR_TABLE  0x80D2
#define GL_PROXY_COLOR_TABLE              0x80D3
#define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE 0x80D4
#define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE 0x80D5
#define GL_COLOR_TABLE_SCALE              0x80D6
#define GL_COLOR_TABLE_BIAS               0x80D7
#define GL_COLOR_TABLE_FORMAT             0x80D8
#define GL_COLOR_TABLE_WIDTH              0x80D9
#define GL_COLOR_TABLE_RED_SIZE           0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE         0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE          0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE         0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE     0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE     0x80DF
#define GL_CONSTANT_BORDER                0x8151
#define GL_REPLICATE_BORDER               0x8153
#define GL_CONVOLUTION_BORDER_COLOR       0x8154
#endif

// Hack for SGI Prisms...

#ifdef GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENTS_EXT
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT 0x8CD6
#endif


#define OSGGLEXT_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGGL_H_ */
