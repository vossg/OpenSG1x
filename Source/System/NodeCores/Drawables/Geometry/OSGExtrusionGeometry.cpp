/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *               Andreas Fischle, Bastian Grundel                            *
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
 *                                Comments                                   *
 *                                                                           *
 * There are certainly bugs in this code, since it has not yet been          *
 * extensively tested.                                                       *
 *                                                                           *
 * There is a bit of debugging information available, but it's currently     *
 * commented out, since it consists mostly of matrix prints which we don't   *
 * consider appropriate for any debug level.                                 *
 *                                                                           *
 * The resulting surface is considered parametrized by paramters u and v,    *
 * where u parametrizes along the spine and v along the crosssection.        *
 *                                                                           *
 * The function prototypes mostly look like "data_in, flags, data_out".      *
 *                                                                           *
 * The core function makeExtrusionGeo is located somewhere near line 1700.   *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                               Known Bugs                                  *
 *                                                                           *
 * 1. There is probably a bug in the normal generation concerning v_wrapped  *
 *    surfaces. Maybe the rendercode has the same problem.                   *
 *    We're not sure yet.                                                    *
 *                                                                           *
 * 2. Surfaces of revolution are not correctly drawn.                        *
 *    We probably set up the vValues/uValues incorrectly for surfaces        *
 *    constructed by pure rotation, and maybe combinations of rotation and   *
 *    translation along the spine                                            *
 *    To be more exactly it seems we're loosing one column in the            *
 *    subdivision grid at some point or don't draw it, but wrap correctly.   *
 *    The subdivision does not cause this, but is set up incorrectly.        *
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

#include <OSGConfig.h>
#include <OSGLog.h>

#include <OSGExtrusionGeometry.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

static char cvsid[] = "@(#)$Id: $";

#ifdef __sgi
#pragma reset woff 1174
#endif

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

/* Subdivision helpers (will hopefully be rewritten anytime soon :) */
/*------------------------------------------------------------------*/

#define EPS 0.00001

#define POINTS 0
#define NORMALS 1
#define TEXTURE 2

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

struct grid
{
  /*v parametrizes along the cross section, u along spine*/

  UInt32 subfields;

  UInt32 u_wrap[3],v_wrap[3]; /* closed along u or v? (topology) */
  UInt32 ui_max[3],vi_max[3]; /* number of indices in u and v direction */

  Real32 *data[3]; /* points, normals, texture coords in this order */
  Real32 *data_orig[3]; /* backups of the pointers before subdivision */
  
  UInt32 coords[3]; /* dimensions for the above vector fields */

};

#endif            // exclude from doc

#ifdef OSG_DEBUG_PM

/* these come in handy sometimes */

static void printMatrix(Real32 *data, int rows, int cols)
{
  int i,j;

  for(i = 0; i < rows; i++)
    {
      printf("( ");
      for(j = 0; j < cols; j++)
        {
          if(data[i*cols+j] > 100.0)
            {
              printf("%-s, ", "BIGNUM");
            }

          else if(data[i*cols+j] < -100.0)
            {
              printf("%-s, ", "BIGNUM");
            }
          else
            {
              printf("%-7.4f, ",data[i*cols+j]);
            }
        }
      printf(")\n");
    }
  printf("\n");
}

static void printMatrixLayer(Real32 *data, int rows, int cols, 
                             int coords, int offset)
{
  int i,j;

  for(i = 0; i < rows; i++)
    {
      printf("( ");
      for(j = 0; j < cols; j++)
        {
          if(data[coords*(i*cols+j)+offset] > 100.0)
            {
              printf("%-s, ", "BIGNUM");
            }

          else if(data[coords*(i*cols+j)+offset] < -100.0)
            {
              printf("%-s, ", "BIGNUM");
            }
          else
            {
              printf("%-7.4f, ",data[coords*(i*cols+j)+offset]);
            }
        }
      printf(")\n");
    }
  printf("\n");
}

#endif //OSG_DEBUG

static Real32 vdist(Real32 *a, Real32 *b)
{
  Real32 d[3];

  d[0] = a[0] - b[0];
  d[1] = a[1] - b[1];
  d[2] = a[2] - b[2];

  return sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2]);
}

static void calcTextureCoords(grid *grid_in, Real32 *texCoords)
{
  //uses the following global variables:

  Real32 *knots = grid_in->data[POINTS];
  UInt32 sp = grid_in->ui_max[POINTS];
  UInt32 cs = grid_in->vi_max[POINTS];

  UInt32 uwrap = grid_in->u_wrap[POINTS];
  UInt32 vwrap = grid_in->v_wrap[POINTS];

  UInt32 tsp = uwrap ? sp + 1 : sp;
  UInt32 tcs = vwrap ? cs + 1 : cs;

  UInt32 i, j;
  UInt32 imsp, jmcs; /*these mean i mod spinepoints and ...*/

  for(i = 0; i < tsp; i++) 
    for(j = 0; j < tcs; j++)
      {
        imsp = uwrap ? i % (tsp - 1) : i;
        jmcs = vwrap ? j % (tcs - 1) : j;

		//        FLOG(("tex (%i,%i) (%i,%i)\n",j,i,jmcs,imsp));

        if(i > 0 && j > 0)
          {
            /*parameter along spine*/
            texCoords[2*(i*tcs+j)] = (vdist(knots+3*((i-1)*cs+jmcs),
                                            knots+3*(imsp*cs+jmcs))
                                      + texCoords[2*((i-1)*tcs+jmcs)]);
                                          

            /*parameter along crossection*/
            texCoords[2*(i*tcs+j)+1]= (vdist(knots+3*(imsp*cs+(j-1)),
                                             knots+3*(imsp*cs+jmcs))
                                       + texCoords[2*(imsp*tcs+(j-1))+1]); 
          }
        else if(i == 0)
          {            
            if(j == 0)
              {
                texCoords[0] = 0.0;
                texCoords[1] = 0.0;
              }
            else
              {
                texCoords[2*j] = 0.0;
                texCoords[2*j+1] = (vdist(knots+3*(j-1), knots+3*jmcs)
                                   +texCoords[2*(j-1)+1]); 
              }
          }
        else {
          //i != 0 => j = 0;
          texCoords[2*i*tcs] = (vdist(knots+3*(i-1)*cs, knots+3*imsp*cs)
                                + texCoords[2*(i-1)*tcs]);
          texCoords[2*i*tcs+1] = 0.0;

        }
      }

  /*
  printMatrix(texCoords, tsp, 2*tcs);
  printMatrixLayer(texCoords, tsp, tcs, 2, 0);
  printMatrixLayer(texCoords, tsp, tcs, 2, 1);
  */

  for(UInt32 i = 0; i < tsp; i++) 
    for(UInt32 j = 0; j < tcs; j++)
      {
        texCoords[2*(i*tcs+j)] /= texCoords[2*((tsp-1)*tcs+j)];
        texCoords[2*(i*tcs+j) + 1] /= texCoords[2*(i*tcs+(tcs-1)) + 1];
      }

  /*
  printMatrix(texCoords, tsp, 2*tcs);
  printMatrixLayer(texCoords, tsp, tcs, 2, 0);
  printMatrixLayer(texCoords, tsp, tcs, 2, 1);
  */
}

/* This is the interpolation along the crosssection */
static void subdivRows(Real32 *col_in, grid *grid_in, UInt32 subfield,
                       UInt32 rows, UInt32 cols, Real32 *col_out)
{
  UInt32 i,j,lc;
  int jm1_mod_cols;
  
  if(!grid_in->v_wrap[subfield])
    {
      lc = 2*cols - 1;

      for(i = 0; i < rows; i++)
        {

          /*fill in the old points*/
          for(j = 0; j < cols; j++)
            col_out[2*(i*lc+j)] = col_in[i*cols+j];


          /* do subdivision on inner points (spare first and last 
            subdivision point) */

          for(j = 1; j < cols-2; j++)
            {
              col_out[2*(i*lc+j)+1] = 1.0/16.0*(9.0*col_in[i*cols+j]
                                                +9.0*col_in[i*cols+j+1]
                                                -col_in[i*cols+j+2]
                                                -col_in[i*cols+j-1]);
            }

          col_out[2*i*lc+1]      = (1.0/8.0)*(3.0*col_in[i*cols]
                                             +6.0*col_in[i*cols+1]
                                             -1.0*col_in[i*cols+2]);

          col_out[2*i*lc+(lc-2)] = (1.0/8.0)*(3.0*col_in[i*cols+(cols-1)]
                                              +6.0*col_in[i*cols+(cols-2)]
                                              -1.0*col_in[i*cols+(cols-3)]);
        }

    } 
  else       /*Closed crossection*/
    {
      lc = 2*cols;

      for(i = 0; i < rows; i++)
        {
          /*fill in what is known from the last subdivision step*/
          for(j = 0; j < cols; j++)
              col_out[2*(i*lc+j)] = col_in[i*cols+j];


          /*do subdivision on all points (wrapping around where neccessary)*/
          for(j = 0; j < cols; j++)
            {
              jm1_mod_cols = (int)(j-1);
              jm1_mod_cols %= (int)cols;

              /*mind the %-operator only delivers the remainder!!!*/
              if(jm1_mod_cols < 0)
                jm1_mod_cols += cols;

            col_out[2*(i*lc+j)+1] = 1.0/16.0*(9.0 *col_in[i*cols+j]
                                              +9.0*col_in[i*cols+(j+1)%cols]
                                              -1.0*col_in[i*cols+(j+2)%cols]
                                              -1.0*col_in[i*cols+jm1_mod_cols]);
            }
        }
    }
}

/* This function expects its input like the output of subdivRows looks like */
/* This is the interpolation along the spine */
static void subdivCols ( Real32 *col_in, grid *grid_in, UInt32 subfield, 
                         UInt32 rows, UInt32 cols, Real32 *col_out)
{
  UInt32 i,j,lc,lr;
  UInt32 u_wrap,v_wrap;
  int im1_mod_cols;

  u_wrap = grid_in->u_wrap[subfield];
  v_wrap = grid_in->v_wrap[subfield];

  /*calculate dimension of output*/

  lr = u_wrap ? 2*rows : 2*rows - 1;
  lc = v_wrap ? 2*cols : 2*cols - 1;

  if(!u_wrap)
    {
      /*iterate over newly inserted column points*/
      /*no subdivision for first and last row*/
      for(i = 1; i < rows-2; i ++)
        {
          for(j = 0; j < lc; j++)
              col_out[(2*i+1)*lc+j] = 1.0/16.0*(9.0*col_in[2*i*lc+j]
                                                +9.0*col_out[2*(i+1)*lc+j]
                                                -col_in[2*(i+2)*lc+j]
                                                -col_in[2*(i-1)*lc+j]);
        }

      /*fill in second upper and lower row*/
      for(j = 0; j < lc; j++)
        {
          col_out[lc+j] = 1.0/8.0*(3.0*col_in[j]
                                   +6.0*col_in[2*lc+j]
                                   -1.0*col_in[4*lc+j]);

          col_out[(lr-2)*lc+j] = 1.0/8.0*(3.0*col_in[(lr-1)*lc+j]
                                          +6.0*col_in[(lr-3)*lc+j]
                                          -1.0*col_in[(lr-5)*lc+j]);
        }
    }
  else
    {
      /*interpolation with wraparound*/
      for(i = 0; i < rows; i ++)
          for(j = 0; j < lc; j++)
            {
              im1_mod_cols = (int)(i-1);
              im1_mod_cols %= rows;

              if(im1_mod_cols < 0)
                im1_mod_cols += rows;

              col_out[(2*i+1)*lc+j] = (9.0*col_in[2*i*lc+j]
                                       +9.0*col_out[2*((i+1)%rows)*lc+j]
                                       -col_in[2*((i+2)%rows)*lc+j]
                                       -col_in[2*im1_mod_cols*lc+j]) / 16.0f;
            }
    }
}

static void initGrid(grid *grid_in)
{
  UInt32 k;

  grid_in->subfields = 3;

  for(k = 0; k < 3; k++)
    {
      grid_in->ui_max[k] = 0;
      grid_in->vi_max[k] = 0;
      grid_in->coords[k] = 0;

      grid_in->u_wrap[k] = 0;
      grid_in->v_wrap[k] = 0;

      grid_in->data[k] = NULL;
      grid_in->data_orig[k] = NULL;
    }
}

static int connectSubfieldToGrid ( Real32 *data_in, UInt32 subfield, 
                                   grid *grid_out)
{
  if(subfield < grid_out->subfields)
    {
      if(grid_out->data[subfield] != NULL)
        return -1;

      grid_out->data[subfield] = data_in;

      /*      for(UInt32 k = 0; k < grid_out->coords[subfield]; k++)
        {
          printMatrixLayer(data_in, grid_out->ui_max[subfield], 
                           grid_out->vi_max[subfield], 
                           grid_out->coords[subfield], k); 
        }
      */

      /* make a backup since the function which registered (and allocated) */
      /* the memory might be a different one than that in which we have */
      /* to free the original (nonsubdivided) data */
      grid_out->data_orig[subfield] = data_in;
    }
  return 0;
}

static void freeGrid(grid *grid_in, UInt32 freeOriginal)
{
  UInt32 k;
  
  for(k = 0; k < grid_in->subfields; k++)
    {
      if(grid_in->data[k] != NULL)
        free(grid_in->data[k]);

      if(freeOriginal && grid_in->data_orig[k] != NULL)
        {
          free(grid_in->data_orig[k]);
        }
    }
}

static void setGridTopology ( grid *grid_in, UInt32 subfield, 
                              UInt32 rows, UInt32 cols, UInt32 dim, 
                              UInt32 u_wrap, UInt32 v_wrap)
{
  grid_in->u_wrap[subfield] = u_wrap;
  grid_in->v_wrap[subfield] = v_wrap;
  grid_in->vi_max[subfield] = cols;
  grid_in->ui_max[subfield] = rows;
  grid_in->coords[subfield] = dim;

  FDEBUG(("Setting Topology: uWrap: %b, vWrap: %b\n", u_wrap, v_wrap));
  FDEBUG(("Setting Topology: uValues: %i, vValues: %i\n", rows, cols));
}

static void normalizeGrid ( grid *grid_in, UInt32 subfield)
{
  UInt32 i,j,dim;
  UInt32 rows,cols;
  Real32 *base;
  Real32 length;
  
  base = grid_in->data[subfield];
  dim = grid_in->coords[subfield];
  cols = grid_in->ui_max[subfield];
  rows = grid_in->vi_max[subfield];
  
  for(i = 0; i < dim * rows * cols; i+=dim)
    {
      length = 0.0;
      for(j = 0; j < dim; j++)
        {
          length += base[i+j]*base[i+j];
        }
      
      length=sqrt(length);
      
      if(length > 0.0)
        for(j = 0; j < dim; j++)
          base[i+j] /= length;
    }
}

/* this one splits the grid into its coordinate layers              */
/* which is probably a bad idea at least for low subdivision levels */

static void splitCoords(grid *grid_in, UInt32 subfield, Real32 **d_out)
{
  Real32 *cur_out = NULL;
  Real32 *d_in = NULL;
  
  UInt32 i,j,k;
  
  UInt32 cols,rows,coords;
  
  d_in = grid_in->data[subfield];
  
  rows = grid_in->ui_max[subfield];
  cols = grid_in->vi_max[subfield];
  
  coords = grid_in->coords[subfield];
  
  for(k = 0; k < coords; k++)
    {
      cur_out = (Real32*)malloc(rows*cols*sizeof(Real32));
      if(cur_out == NULL)
        {
          exit(EXIT_FAILURE);
        }
      
      for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
          cur_out[i*cols+j] = d_in[coords*(i*cols+j)+k];
      d_out[k] = cur_out;
    }
}

/* Here we free the coordinate planes and allocate the memory for the merged */
/* grid.                                                                     */
static void mergeCoordsToGrid(Real32 **d_in, grid* grid_in, UInt32 subfield, 
                              UInt32 rows, UInt32 cols, Real32 **d_out)
{
  Real32 *cur_out;
  Real32 *d_out_ptr;
  UInt32 coords;
  UInt32 i,j,k;

  grid_in->ui_max[subfield] = rows;
  grid_in->vi_max[subfield] = cols;
  coords = grid_in->coords[subfield];

  if( (cur_out = (Real32*)malloc(rows*cols*coords*sizeof(Real32))) == NULL)
    {
      exit(EXIT_FAILURE);
    }

  for(k = 0; k < coords; k++)
    {
      //      printMatrix(d_in[k], rows, cols);
      for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
          {
            d_out_ptr = d_in[k]+i*cols+j;
            cur_out[coords*(i*cols+j)+k] = *d_out_ptr;
          }
      free(d_in[k]);
      d_in[k] = NULL;
    }

  *d_out = cur_out;
}

static void freeCoordGrids(Real32 **d_in, UInt32 coords)
{
  UInt32 k;

  for(k = 0; k < coords; k++)
    {
      free(d_in[k]);
      d_in[k] = NULL;
    }
}

/*Here we  write back to the subfield*/
static void subdivMeshSubfield(UInt32 subdivs, grid *grid_in, UInt32 subfield)
{
  UInt32 i,k;

  Real32 **d_in = NULL;
  Real32 **d_out = NULL;

  Real32 *last_mesh = NULL, *cur_mesh = NULL;
  Real32 *merged_mesh = NULL;

  UInt32 rows,cols;
  UInt32 coords;
  UInt32 lc,lr;

  coords = grid_in->coords[subfield];

  d_in = (Real32**)(malloc(coords*sizeof(Real32*)));

  d_out = (Real32**)(malloc(coords*sizeof(Real32*)));

  if(d_in == NULL || d_out == NULL)
    {
      exit(EXIT_FAILURE);
    }

  for(k = 0; k < coords; k++)
    {
      d_in[k] = NULL;
      d_out[k] = NULL;
    }

  /* this function allocates memory for the d[i] */
  splitCoords(grid_in, subfield, d_in);

  for(i = 0; i < coords; i++)
    {
      last_mesh = d_in[i];

      rows = grid_in->ui_max[subfield];
      cols = grid_in->vi_max[subfield];

      for(k = 0; k < subdivs; k++)
      {
          lc = grid_in->v_wrap[subfield] ? 2*cols : 2*cols-1;
          lr = grid_in->u_wrap[subfield] ? 2*rows : 2*rows-1;

          if( (cur_mesh = (Real32*)malloc(lc*lr*sizeof(Real32))) == NULL)
          {
            exit(EXIT_FAILURE);
          }
          
          subdivRows(last_mesh , grid_in, subfield, rows, cols, cur_mesh);
          subdivCols(cur_mesh, grid_in, subfield, rows, cols, cur_mesh);

        if(k > 0)
          free(last_mesh);

        last_mesh = cur_mesh;
        cols = lc;
        rows = lr;
      }

      d_out[i] = cur_mesh;

      if( subdivs > 0 )
          free(d_in[i]);
    }

  mergeCoordsToGrid(d_out, grid_in, subfield, rows, cols, &merged_mesh);

  /*assign subdivided mesh*/
  grid_in->data[subfield] = merged_mesh;

  freeCoordGrids(d_out, coords);

  free(d_in);
  free(d_out);
}

static void subdivSurface(UInt32 subdivs, grid *grid_in)
{
  /*do subdivisions of the available fields*/
  if (subdivs > 0) 
    {
      for(UInt32 i = 0; i < grid_in->subfields; i++)
        {
          /*0 = points, 1 = normals, 2 = textures */
          if(grid_in->data[i] != NULL)
            {
              subdivMeshSubfield(subdivs, grid_in, i);
            }
          if(grid_in->data[1] != NULL)
            {
              normalizeGrid(grid_in, 1);
            }
        }
    }
}

/* end of subdivision helpers                                                */
/*---------------------------------------------------------------------------*/


static void createSCP(const std::vector<Vec3f>  &spine,
                                 bool           *pSpineClosed,
                                 bool           *pPureRotation,
                            std::vector<Matrix> &SCP          )

{
  /* This function makes quite heavy use of the .length() function   */
  /* For epsilon checks the 1-Norm or Inf.-Norm would probably suffice. */
  
  Vec3f yUnit(0.0 ,1.0, 0.0);
  Vec3f zUnit(0.0 ,0.0, 1.0);
  
  UInt32 sp_len = spine.size();

  bool spineClosed = false;
  bool yFound = false;
  bool zFound = false;
  
  *pPureRotation = false;

  SCP.resize(sp_len);
  
  if ((spine[0] - spine[spine.size() - 1]).length() < EPS)
    {
      spineClosed = true;
      *pSpineClosed = true;
    }
  else
    {
      spineClosed = false;
      *pSpineClosed = false;
    }
            
  /* determine the SCPBaseTransformation for the first crosssection */
  if(spineClosed)
    {
      SCP[0][1].setValue(spine[1] - spine[sp_len - 2]);
      
      if(SCP[0][1].length() > EPS) /* translation */
        {
          Vec3f tmp1 = spine[1] - spine[0];
          Vec3f tmp2 = spine[sp_len - 2] - spine[sp_len - 1];

          yFound = true;
          
          SCP[0][2].setValue(tmp1.cross(tmp2));

          if(SCP[0][2].length() > EPS)
            zFound = true;
        }
    }
  else /* spine is open */
    {
      SCP[0][1].setValue(spine[1] - spine[0]);

      if(SCP[0][1].length() > EPS)
        {
          yFound = true;
        }
    }

  for(UInt32 i = 1; i < sp_len - 1; i++)
    {
      // jbher
      SCP[i][1].setValue(spine[i + 1] - spine[i - 1]);

      if(SCP[i][1].length() > EPS) /* y_Axis defined */
        {
          /* If this is the first defined y-Axis we have to */
          /* set up the previous ones exactly like this one */
          if(!yFound)
            {
              yFound = true;

              for(UInt32 j = 0; j < i; j++)
                SCP[j][1] = SCP[i][1];
            }
          
          SCP[i][2].setValue((spine[i + 1] - spine[i]).cross(spine[i - 1] - spine[i]));
          
          if(SCP[i][2].length() > EPS) 
            {
              if(!zFound)
                {
                  zFound = true;

                  for(UInt32 j = 0; j < i; j++)
                    SCP[j][2] = SCP[i][2];
                }
            }
          else /* z_Axis is not defined, take the last one */
            if(zFound)
              {
                SCP[i][2] = SCP[i-1][2];
              }
        }
      else
        {
          if(yFound)
            {
              SCP[i][1] = SCP[i-1][1];
            } 
        }
    }

  /* SCPBaseTransformation of the last crosssection */
  if(spineClosed)
    {
      /* no translation during last step */
      if(SCP[0][1].length() < EPS)
        {
          if(yFound)
            {
              SCP[sp_len - 1][1] = SCP[sp_len - 2][1];
            }
          else
            {
              /* for a surface of revolution we can't define */
              /* a basis transformation, so we don't make one */
              SCP[0][1].setValue(yUnit);
              SCP[0][2].setValue(zUnit);
              
              /* One transformation for all spinepoints */
              SCP.resize(1);              
            }
        }
      else /* translation during last step */
        {
          SCP[sp_len - 1][1] = SCP[0][1];
        }

      if(SCP[0][2].length() < EPS)
        {
          if(zFound)
            {
              SCP[sp_len - 1][2] = SCP[sp_len - 2][2];
            }
          else /* In this case the whole spine is collinear */
            {
              if(yFound)
                {
                  Quaternion quat;
                  Vec3f v(SCP[0][1]);

                  quat.setValue(yUnit, v);
                  quat.getValue(SCP[0]);

                  SCP.resize(1);      
                }
              else
                {
                  /* for a surface of revolution we can't define */
                  /* a basis transformation */
                  SCP[0][1].setValue(yUnit);
                  SCP[0][2].setValue(zUnit);
              
                  /* One transformation for all spinepoints */
                  SCP.resize(1);

                  *pPureRotation = true;
                }
            }
        }
    }
  else /* spine is open */
    {
      SCP[sp_len - 1][1].setValue(spine[sp_len - 1] - spine[sp_len - 2]);
      /* no translation during last step */
      if(SCP[sp_len - 1][1].length() < EPS)
        {
          if(yFound)
            {
              SCP[sp_len - 1][1] = SCP[sp_len - 2][1];
            }
        }

      if(zFound)
        {
          SCP[sp_len - 1][2] = SCP[sp_len - 2][2];
        }
      else /* In this case the whole spine is collinear */
        {
          Quaternion quat;
          Vec3f v(SCP[0][1]);

          quat.setValue(yUnit, v);
          quat.getValue(SCP[0]);
          /* One transformation for all spinepoints */
          SCP.resize(1);      
        }
    }


  for(UInt32 i = 0; i < SCP.size(); i++)
    {
      if(i > 0)
        {
          if(SCP[i][2].dot(SCP[i-1][2]) < 0)
            SCP[2].negate();
        }
      
      SCP[i][0] = SCP[i][1].cross(SCP[i][2]);
      
      SCP[i][0].normalize();
      SCP[i][1].normalize();
      SCP[i][2].normalize();
    }
}
   
static void calcHullVertices(const std::vector<Vec2f     > &crossSection,
                             const std::vector<Quaternion> &orientation,
                             const std::vector<Vec2f     > &scale,
                             const std::vector<Vec3f     > &spine,
                                        bool               *uWrap, 
                                        bool               *vWrap,
                                   std::vector<Pnt3f     > &vertices)
{
  /* Closure detection in u-direction is not yet correct */
  /* Let u be the parameter of the hull surface in direction of the spine */
  /* then closure of the spine does not imply that the hull surface is */
  /* closed in u direction */

  std::vector<Matrix> SCPBaseTransform;

  UInt32 sp_len = spine.size();
  UInt32 cs_len = crossSection.size();
  UInt32 sc_len = scale.size();
  UInt32 or_len = orientation.size();

  // bool crossSectionClosed = false;
  bool spineClosed  = false;
  bool pureRotation = false;

  if((crossSection[0] - crossSection[cs_len - 1]).length() < EPS)
    {
      // crossSectionClosed = true;
      *vWrap = true;
      vertices.resize((cs_len - 1)*sp_len);
    }
  else
    {
      // crossSectionClosed = false;
      *vWrap = false;
      vertices.resize(cs_len*sp_len);
    }

  UInt32 cs_lim = *vWrap ? cs_len - 1 : cs_len;

  createSCP(spine, &spineClosed, &pureRotation, SCPBaseTransform);

  FLOG(("For the moment we assume spine closed => uWrap of surface"));

  *uWrap = (spineClosed && !pureRotation);

  for(UInt32 i = 0; i < sp_len; i++)
  {
    /* the VRML-spec does not say how to interpret the case if */
    /* we are called with more than one but less than number of */
    /* spine points orientation/scale values */
    /* If that occurs we just go on with the last value we know */

    Matrix SCPRotation;
    SCPRotation.setIdentity();

    if(or_len > i)
      {
        Quaternion tmp = orientation[i];
        //        printMatrix((Real32*)&tmp[0], 1, 4);

        tmp.getValuesOnly(SCPRotation);
        //        printMatrix((Real32*)&SCPRotation[0], 3, 4);

      }
    else
      {
        Quaternion tmp = orientation[sp_len - 1];
        //        printMatix((Real32*)&tmp[0], 1, 4);

        tmp.getValuesOnly(SCPRotation);
        //        printMatrix((Real32*)&SCPRotation[0], 3, 4);
      }

    if(sc_len >= sp_len)
      {
        Vec2f tmp;

        for(UInt32 j = 0; j < cs_lim; j++)
          {
            tmp[0] = scale[i][0]*crossSection[j][0];
            tmp[1] = scale[i][1]*crossSection[j][1];

            vertices[i*cs_lim+j].setValue((SCPRotation[0]*tmp[0] 
                                           + SCPRotation[2]*tmp[1]));
            /*
            printf("vertices[%i] : (%f, %f, %f) \n",i*cs_lim+j, 
                   vertices[i*cs_lim+j][0],
                   vertices[i*cs_lim+j][1],
                   vertices[i*cs_lim+j][2]);
            */
          }
      }
    else
      {
        for(UInt32 j = 0; j < cs_lim; j++)
          {
            Vec2f tmp;

            if(j < sc_len)
              {
                tmp[0] = scale[i][0]*crossSection[j][0];
                tmp[1] = scale[i][1]*crossSection[j][1];
              }
            else
              {
                tmp[0] = scale[sc_len - 1][0]*crossSection[j][0];
                tmp[1] = scale[sc_len - 1][1]*crossSection[j][1];
              }

            vertices[i*cs_lim+j].setValue((SCPRotation[0]*tmp[0] 
                                           + SCPRotation[2]*tmp[1]));
          }
      }
  }

  /* the spine is entirely collinear or consists only of coincident points */
  if(SCPBaseTransform.size() > 1)
    {
      for(UInt32 i = 0; i < sp_len; i++)
        {
          /* move the SCP along the spine */
          SCPBaseTransform[i][3].setValue(spine[i]);

          for(UInt32 j = 0; j < cs_lim; j++)
            SCPBaseTransform[i].multMatrixPnt(vertices[i*cs_lim +j]);
        }
    }
  else
    {
      for(UInt32 i = 0; i < sp_len; i++)
        {
          /* move the SCP along the spine */
          SCPBaseTransform[0][3].setValue(spine[i]);

          for(UInt32 j = 0; j < cs_lim; j++)
            SCPBaseTransform[0].multMatrixPnt(vertices[i*cs_lim +j]);
        }
    }
}

static void calcHullNormals(const std::vector<Vec2f     > &,
                            const std::vector<Quaternion> &,
                            const std::vector<Vec2f     > &,
                            const std::vector<Vec3f     > &,
                            const std::vector<Pnt3f     > &vertices,
                                       bool                ccw,
                                       bool                uWrap,
                                       bool                vWrap,
                                       UInt32              uValues,
                                       UInt32              vValues,
                                  std::vector<Vec3f     > &normals )
{
  normals.resize(uValues*vValues);

  UInt32 sp_len = uValues;
  UInt32 cs_len = vValues;

  UInt32 i, j;

  UInt32 ll;
  UInt32 lr;
  UInt32 ul;
  UInt32 ur;

  if(ccw)
    {
      for(i = 0; i < sp_len - 1; i++)
        {
          for(j = 0; j < cs_len - 1; j++)
            {
              Vec3f n;
              Vec3f ds,dc;
              
              /* ll = lower left, ul = upper left ... */
              ll = i*cs_len + j;
              lr = i*cs_len + (j+1);
              ul = (i+1)*cs_len + j;
              ur = (i+1)*cs_len + (j+1);
              
              // Berechnung der Dreiecksflaechen-Normalen I
              ds = vertices[ll] - vertices[ul];
              dc = vertices[ul] - vertices[lr];
              n = dc.cross(ds);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[ll] += n;
              normals[ul] += n;
              normals[lr] += n;
              
              // Berechnung der Dreiecksflaechen-Normalen II
              ds = vertices[lr] - vertices[ul];
              dc = vertices[ul] - vertices[ur];
              n = dc.cross(ds);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[lr] += n;
              normals[ul] += n;
              normals[ur] += n;
            }
          
          if (vWrap)
            {
              Vec3f n;
              Vec3f ds,dc;
              
              // Berechnung der Dreiecksflaechen-Normalen I
              ds = vertices[ll] - vertices[ul];
              dc = vertices[ul] - vertices[i*cs_len];
              n = dc.cross(ds);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[ll]       += n;
              normals[ul]       += n;
              normals[i*cs_len] += n;
              
              // Berechnung der Dreiecksflaechen-Normalen II
              ds = vertices[i*cs_len] - vertices[ul];
              dc = vertices[ul] - vertices[(i+1)*cs_len];
              n = dc.cross(ds);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[ll]  += n;
              normals[ul]  += n;
              normals[(i+1)*cs_len] += n;
            }
        }
      
      if (uWrap)
        {
          for (j = 0; j < cs_len-1; j++)
            {
              Vec3f n;
              Vec3f ds,dc;
              
              // Berechnung der Dreiecksflaechen-Normalen I
              ds = vertices[ll] - vertices[j];
              dc = vertices[j] - vertices[lr];
              n = dc.cross(ds);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[ll]  += n;
              normals[j]   += n;
              normals[lr]  += n;
              
              // Berechnung der Dreiecksflaechen-Normalen II
              ds = vertices[lr] - vertices[j];
              dc = vertices[j] - vertices[j+1];
              n = dc.cross(ds);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[lr]  += n;
              normals[j]   += n;
              normals[j+1] += n;
            }
          
          if (vWrap)
            {
              Vec3f n;
              Vec3f ds,dc;
              
              // Berechnung der Dreiecksflaechen-Normalen I
              ds = vertices[ll] - vertices[j];
              dc = vertices[j] - vertices[i*cs_len];
              n = dc.cross(ds);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[ll]  += n;
              normals[j]   += n;
              normals[i*cs_len] += n;
              
              // Berechnung der Dreiecksflaechen-Normalen II
              ds = vertices[i*cs_len] - vertices[j];
              dc = vertices[j] - vertices[0];
              n = dc.cross(ds);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[i*cs_len]  += n;
              normals[j]  += n;
              normals[0]  += n;
            }
        }
    }
  else
    {
      for(i = 0; i < sp_len - 1; i++)
        {
          for(j = 0; j < cs_len - 1; j++)
            {
              Vec3f n;
              Vec3f ds,dc;
              
              /* ll = lower left, ul = upper left ... */
              ll = i*cs_len + j;
              lr = i*cs_len + (j+1);
              ul = (i+1)*cs_len + j;
              ur = (i+1)*cs_len + (j+1);
              
              // Berechnung der Dreiecksflaechen-Normalen I
              ds = vertices[ll] - vertices[ul];
              dc = vertices[ul] - vertices[lr];
              n = ds.cross(dc);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[ll] += n;
              normals[ul] += n;
              normals[lr] += n;
              
              // Berechnung der Dreiecksflaechen-Normalen II
              ds = vertices[lr] - vertices[ul];
              dc = vertices[ul] - vertices[ur];
              n = ds.cross(dc);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[lr] += n;
              normals[ul] += n;
              normals[ur] += n;
            }
          
          if (vWrap)
            {
              Vec3f n;
              Vec3f ds,dc;
              
              // Berechnung der Dreiecksflaechen-Normalen I
              ds = vertices[ll] - vertices[ul];
              dc = vertices[ul] - vertices[i*cs_len];
              n = ds.cross(dc);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[ll]       += n;
              normals[ul]       += n;
              normals[i*cs_len] += n;
              
              // Berechnung der Dreiecksflaechen-Normalen II
              ds = vertices[i*cs_len] - vertices[ul];
              dc = vertices[ul] - vertices[(i+1)*cs_len];
              n = ds.cross(dc);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[ll]  += n;
              normals[ul]  += n;
              normals[(i+1)*cs_len] += n;
            }
        }
      
      if (uWrap)
        {
          for (j = 0; j < cs_len-1; j++)
            {
              Vec3f n;
              Vec3f ds,dc;
              
              // Berechnung der Dreiecksflaechen-Normalen I
              ds = vertices[ll] - vertices[j];
              dc = vertices[j] - vertices[lr];
              n = ds.cross(dc);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[ll]  += n;
              normals[j]   += n;
              normals[lr]  += n;
              
              // Berechnung der Dreiecksflaechen-Normalen II
              ds = vertices[lr] - vertices[j];
              dc = vertices[j] - vertices[j+1];
              n = ds.cross(dc);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[lr]  += n;
              normals[j]   += n;
              normals[j+1] += n;
            }
          
          if (vWrap)
            {
              Vec3f n;
              Vec3f ds,dc;
              
              // Berechnung der Dreiecksflaechen-Normalen I
              ds = vertices[ll] - vertices[j];
              dc = vertices[j] - vertices[i*cs_len];
              n = ds.cross(dc);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[ll]  += n;
              normals[j]   += n;
              normals[i*cs_len] += n;
              
              // Berechnung der Dreiecksflaechen-Normalen II
              ds = vertices[i*cs_len] - vertices[j];
              dc = vertices[j] - vertices[0];
              n = ds.cross(dc);
              n.normalize();
              
              // Bildung der Eck-Normalen
              normals[i*cs_len]  += n;
              normals[j]  += n;
              normals[0]  += n;
            }
        }
    }

      FLOG(("Normalizing normals, might not be necessary\n"));
      
  for (i = 0; i < sp_len; i++)
    for (j = 0; j < cs_len; j++)
      normals[i*cs_len+j].normalize();
}

  /* For transition only! To be removed during the next days, 
   specifically after subdivision cleanup */
static void convertSubdivisionGrid(     grid          *ext_grid,
                                        UInt32        *_uValues,
                                        UInt32        *_vValues,
                                   std::vector<Pnt3f> &_vertices,
                                   std::vector<Vec3f> &_normals,
                                   std::vector<Vec2f> &_texCoords)


{
  Real32 *vertices  = ext_grid->data[POINTS];
  Real32 *normals   = ext_grid->data[NORMALS];
  Real32 *texCoords = ext_grid->data[TEXTURE];
  
  UInt32 sp_len = ext_grid->ui_max[POINTS];
  UInt32 cs_len = ext_grid->vi_max[POINTS];

  *_uValues = sp_len;
  *_vValues = cs_len;

  UInt32 tot_sp_len = ext_grid->ui_max[TEXTURE];
  UInt32 tot_cs_len = ext_grid->vi_max[TEXTURE];
  
  _vertices.resize(sp_len * cs_len);

  UInt32 i,j,k;
    
  for(i = 0; i < ext_grid->ui_max[POINTS]; i++)
    for(j = 0; j < ext_grid->vi_max[POINTS]; j++)
          for(k = 0; k < 3; k++)
            _vertices[i*cs_len+j][k] = vertices[3*(i*cs_len+j)+k];

  if(normals != NULL)
    {
      _normals.resize(sp_len*cs_len);
      
      for(i = 0; i < ext_grid->ui_max[NORMALS]; i++)
        for(j = 0; j < ext_grid->vi_max[NORMALS]; j++)
          for(k = 0; k < 3; k++)
            _normals[i*cs_len+j][k] = normals[3*(i*cs_len+j)+k];
    }


  if(texCoords != NULL)
    {
      _texCoords.resize(tot_sp_len*tot_cs_len);

      for(i = 0; i < ext_grid->ui_max[TEXTURE]; i++)
        for(j = 0; j < ext_grid->vi_max[TEXTURE]; j++)
          for(k = 0; k < 2; k++)
            _texCoords[i*tot_cs_len+j][k] = texCoords[2*(i*tot_cs_len+j)+k];
    }

  /* the second argument is a flag which signals if the original grid */ 
  /* constructed during linear extrusion from the original extrusion data */
  /* has also to be set free */

  /* we know this condition */
  //if(numOfSubdivision > 0)
  freeGrid(ext_grid, false);
}

static void generateHull(const std::vector<Vec2f     > & crossSection,
                         const std::vector<Quaternion> & orientation,
                         const std::vector<Vec2f     > & scale,
                         const std::vector<Vec3f     > & spine,
                                    bool                 ccw,
                                    bool                 buildNormal,
                                    bool                 buildTexCoord,
                                    UInt32               numOfSubdivision,
                                    bool               *_uWrap,
                                    bool               *_vWrap,
                                    UInt32             *_uValues,
                                    UInt32             *_vValues,
                               std::vector<Pnt3f     > & vertices,
                               std::vector<Vec3f     > & normals,
                               std::vector<Vec2f     > & texCoords       )
{
  /* Note : The terminology concerning the parametrization of the hull */
  /* surface differs from the spec                                     */
  /* u parametrizes the hull surface along the spine                   */
  /* v parametrizes the hull surface along the crosssection            */

  grid ext_grid;
  initGrid(&ext_grid);

  bool uWrap = false;
  bool vWrap = false;
  UInt32 uValues = 0;
  UInt32 vValues = 0;
    
  UInt32 sp_len = spine.size();
  UInt32 cs_len = crossSection.size();

  FDEBUG(("calculating hull vertices\n"));
  
  /*setup vertex data in vertices */
  calcHullVertices(crossSection, orientation, scale, spine,
                   &uWrap, &vWrap, vertices);

  /* calculate total length of crossSection and spine */
  uValues = (uWrap)  ? sp_len - 1 : sp_len;
  vValues = (vWrap)  ? cs_len - 1 : cs_len;
  
  FDEBUG(("connecting point data to subdivision grid:\n"));
  FDEBUG(("considering spineClosed and uWrap the same!\n"));
  
  setGridTopology(&ext_grid, POINTS, uValues, vValues, 3, uWrap, vWrap);
  connectSubfieldToGrid((Real32 *) &vertices[0], POINTS, &ext_grid);
  
  if(buildNormal)
    { 
      FDEBUG( ("calculating normals\n"));
      calcHullNormals(crossSection, orientation, scale, spine, vertices,
                      ccw, uWrap, vWrap, uValues, vValues, normals);
      
      FDEBUG(("connecting normal data to subdivision grid:\n\n"));
      setGridTopology(&ext_grid, NORMALS, uValues, vValues, 
                      3, uWrap, vWrap);
      connectSubfieldToGrid((Real32*) &normals[0], NORMALS, &ext_grid);
    }
  
  if(buildTexCoord)
    {
      FDEBUG(("calculating hull texture coordinates\n"));

      texCoords.resize(sp_len*cs_len);
      calcTextureCoords(&ext_grid, (Real32*) &texCoords[0]);
      
      /* register the texture coordinates */
      setGridTopology(&ext_grid, TEXTURE, sp_len, cs_len, 2, false, false);
      connectSubfieldToGrid((Real32*) &texCoords[0], TEXTURE, &ext_grid);
    }
 
  /* This prevents us from segfaulting */
  if((numOfSubdivision > 0) && (uValues > 2) && (vValues > 2))
    {
      FDEBUG(("subdividing %i times\n", numOfSubdivision));
      subdivSurface(numOfSubdivision, &ext_grid);
      
      /* This is _VERY_ ugly and subject to change in the next future*/
      convertSubdivisionGrid(&ext_grid, &uValues, &vValues,
                             vertices, normals, texCoords);
    }

  *_uWrap = uWrap;
  *_vWrap = vWrap;
  *_uValues = uValues;
  *_vValues = vValues;
}

static void renderHull(const std::vector<Pnt3f>      &vertices,
                       const std::vector<Vec3f>      &normals,
                       const std::vector<Vec2f>      &texCoords,
                                  bool                buildNormal, 
                                  bool                buildTexCoord,
                                  bool                uWrap,
                                  bool                vWrap,
                                  UInt32              uValues,
                                  UInt32              vValues,
                                  GeoPositions3fPtr  &geoVertices,
                                  GeoNormals3fPtr    &geoNormals,
                                  GeoTexCoords2fPtr  &geoTexCoords,
                                  GeoPLengthsUI32Ptr &geoLengths,
                                  GeoPTypesUI8Ptr    &geoTypes)
{
  GeoPositions3f::StoredFieldType  *geoVerticesPtr = geoVertices->getFieldPtr();
  GeoNormals3f::StoredFieldType    *geoNormalsPtr  = geoNormals->getFieldPtr();
  GeoPLengthsUI32::StoredFieldType *geoLengthsPtr = geoLengths->getFieldPtr();
  GeoPTypesUI8::StoredFieldType    *geoTypesPtr   = geoTypes->getFieldPtr();
  
  /* calculate spine and crosssection lengths */
  UInt32 tot_sp_len = uWrap ? uValues + 1 : uValues;
  UInt32 tot_cs_len = vWrap ? vValues + 1 : vValues;
  
  beginEditCP(geoLengths);
  beginEditCP(geoTypes);  
  
  UInt32 k,j;
  UInt32 il,iu;
  UInt32 ilc,iuc;

  FDEBUG(("drawing to OpenSG\n"));

  /* Maybe striping along the spine is worth to go for */
  for(k = 0; k < tot_sp_len - 1; k++)
    {
      beginEditCP(geoVertices);

      /*initialize index of first points of line i*/
      il = k*vValues;
      iu = ((k + 1) % uValues)*vValues;
      
      geoLengthsPtr->push_back(2*tot_cs_len);
      geoTypesPtr->push_back(GL_TRIANGLE_STRIP);
      
      ilc = il;
      iuc = iu;

      /* write vertices to geometry */      

      for(j = 0;j < vValues; j++)                
        { 
          geoVerticesPtr->push_back(vertices[ilc++]);
          geoVerticesPtr->push_back(vertices[iuc++]);
        }
      
      if(vWrap)
        { 
          iuc = ((k + 1) % uValues)*vValues;
          ilc = k*vValues;
          
          geoVerticesPtr->push_back(vertices[ilc]);
          geoVerticesPtr->push_back(vertices[iuc]);
        }
      
      endEditCP(geoVertices);
      
      /* write normals to geometry if necessary */
      
      if(buildNormal)
        {
          beginEditCP(geoNormals);

          ilc = il;
          iuc = iu;
          
          for(j = 0;j < vValues; j++)          
            { 
              geoNormalsPtr->push_back(normals[ilc++]);
              geoNormalsPtr->push_back(normals[iuc++]);
            }
          
          if(vWrap)
          { 
            iuc = ((k + 1) % uValues)*vValues;
            ilc = k*vValues;
            
            geoNormalsPtr->push_back(normals[ilc]);
            geoNormalsPtr->push_back(normals[iuc]);
          }
          endEditCP(geoNormals);
        }

      /* write texture coordinates to geometry if necessary */

      if(buildTexCoord)
        {
          beginEditCP(geoTexCoords);

          il = k*tot_cs_len;
          iu = (k+1)*tot_cs_len;

          for(j = 0;j < tot_cs_len; j++)
          { 
            geoTexCoords->push_back(texCoords[il++]);
            geoTexCoords->push_back(texCoords[iu++]);
          }
          beginEditCP(geoTexCoords);
        }
      endEditCP(geoLengths);
      endEditCP(geoTypes);
    }
}

void renderCap(const std::vector<Vec2f>      &crossSection,
               const std::vector<Pnt3f>      &hullVertices,
                          bool                ccw,
                          bool                convex,
                          bool                buildNormal,
                          bool                buildTexCoord,
                          bool                uWrap,
                          bool                vWrap,
                          UInt32              numOfCap,
                          UInt32              uValues,
                          UInt32              vValues,
                          GeoPositions3fPtr  &geoVertices,
                          GeoNormals3fPtr    &geoNormals,
                          GeoTexCoords2fPtr  &geoTexCoords,
                          GeoPLengthsUI32Ptr &geoLengths,
                          GeoPTypesUI8Ptr    &geoTypes)
{
  Vec2f baryCenter(0.0f, 0.0f);
  Vec3f vertexBaryCenter(0.0f, 0.0f, 0.0f);
  Vec3f v;

  // UInt32 tot_uValues = uWrap ? uValues + 1 : uValues;
  UInt32 tot_vValues = vWrap ? vValues + 1 : vValues;
  UInt32 v_limit = vWrap ? tot_vValues : tot_vValues + 1;

  if(!convex)
    {
      FWARNING(("OSGExtrusion: Support for nonconvex caps not yet implemented\n"));
      return ;
    }

  /* calculate barycenter of the crossSection */
  for(UInt32 j = 0; j < vValues; j++)
    {
      baryCenter += crossSection[j];
      v.setValue(hullVertices[(numOfCap % uValues)*vValues + j]);
      vertexBaryCenter += v;
    }

  baryCenter /= crossSection.size();
  vertexBaryCenter /= vValues;

  beginEditCP(geoTypes);
  beginEditCP(geoLengths);
  beginEditCP(geoVertices);
  {
    geoTypes->push_back(GL_TRIANGLE_FAN);
    geoLengths->push_back(v_limit + 1);

    geoVertices->push_back(vertexBaryCenter);

    for(UInt32 j = 0; j < v_limit; j++)
    {
      if(!uWrap)
      {
          geoVertices->push_back(
              hullVertices[numOfCap*vValues+(j % vValues)]); 
      }
      else /* u_wrap */
        {
          geoVertices->push_back(hullVertices[j % vValues]); 
        }
    }

  }
  endEditCP(geoVertices);
  endEditCP(geoTypes);
  endEditCP(geoLengths);

  if(buildNormal)
    {
      Vec3f diff1;
      Vec3f diff2;

      diff1.setValue( hullVertices[(numOfCap % uValues)* vValues]   
                      -vertexBaryCenter );
      diff2.setValue( hullVertices[(numOfCap % uValues)* vValues +1]
                      -vertexBaryCenter );

      Vec3f normal;

      /* I think it's ok if these crossproducts are zero */
      /* If anybody uses coincident crossSection points this makes trouble */
      if(uValues / 2 > numOfCap)
        {
          normal = ccw ? diff2.cross(diff1) : diff1.cross(diff2);
        }
      else /* invert the normal */
        {
          normal = ccw ? diff1.cross(diff2) : diff2.cross(diff1);
        }

      beginEditCP(geoNormals);
      {
        for(UInt32 j = 0; j < v_limit + 1; j++)
          {
            normal.normalize();
            geoNormals->push_back(normal);
          }
      }
      endEditCP(geoNormals);
    }

  if(buildTexCoord)
    {
      FWARNING(("OSGExtrusion: Texture coordinates for caps not yet implemented\n"));
      beginEditCP(geoTexCoords);      
      {
        for(UInt32 j = 0; j < v_limit + 1; j++)
          {
            Vec2f texCoord;

            texCoord = Vec2f(0.0f, 0.0f);
            geoTexCoords->push_back(texCoord);
          }
      }
      endEditCP(geoTexCoords);
    }
}


NodePtr OSG::makeExtrusion(const std::vector<Vec2f     > &crossSection,
                           const std::vector<Quaternion> &orientation,
                           const std::vector<Vec2f     > &scale,
                           const std::vector<Vec3f     > &spine,
                                      bool                beginCap,
                                      bool                endCap,
                                      bool                ccw,
                                      bool                convex,
                                      bool                buildNormal,
                                      bool                buildTexCoord,
                                      UInt32              numOfSubdivision)
{

  GeometryPtr pGeo = makeExtrusionGeo(crossSection, orientation,
                                      scale, spine, beginCap, endCap, 
                                      ccw, convex, buildNormal, 
                                      buildTexCoord, numOfSubdivision);
  
  if(pGeo == NullFC)
    {
      return NullFC;
    }
  
  NodePtr node = Node::create();
  
  beginEditCP  (node);
  node->setCore(pGeo);
  endEditCP    (node);
  
  return node;
}

GeometryPtr OSG::makeExtrusionGeo(const std::vector<Vec2f     > &crossSection,
                                  const std::vector<Quaternion> &orientation,
                                  const std::vector<Vec2f     > &scale,
                                  const std::vector<Vec3f     > &spine,
                                        bool                     beginCap,
                                        bool ,
                                        bool                     ccw,
                                        bool                     convex,
                                        bool                     buildNormal,
                                        bool                     buildTexCoord,
                                        UInt32                   numSubdivs)
{
    std::vector<Pnt3f> hullVertices;
    std::vector<Vec3f> hullNormals;
    std::vector<Vec2f> hullTexCoords;
  
    std::vector<Pnt3f> beginCapVertices;
    std::vector<Vec3f> beginCapNormals;
    std::vector<Vec2f> beginCaptexCoords;
  
    std::vector<Pnt3f> endCapVertices;
    std::vector<Vec3f> endCapNormals;
    std::vector<Vec2f> endCaptexCoords;

  GeoPositions3fPtr   geoVertices = GeoPositions3f::create();
  GeoNormals3fPtr     geoNormals  = GeoNormals3f::create();
  GeoTexCoords2fPtr   geoTexCoords= GeoTexCoords2f::create();
  GeoPLengthsUI32Ptr  geoLengths  = GeoPLengthsUI32::create();
  GeoPTypesUI8Ptr     geoTypes    = GeoPTypesUI8::create();

  /* some minimal sanity checking here */
  if( crossSection.size() < 2 || orientation.empty() ||
      spine.size() < 2 || scale.empty() )
    {
      FWARNING(("OSGExtrusion called with too little data\nReturning NullFC\n"));
      return NullFC;
    }

  bool uWrap = false;
  bool vWrap = false;

  UInt32 uValues = 0;
  UInt32 vValues = 0;

  FDEBUG(("entering hull generation\n"));
  generateHull(crossSection, orientation, scale, spine,
               ccw, buildNormal, buildTexCoord, numSubdivs, 
               &uWrap, &vWrap, &uValues, &vValues, hullVertices, 
               hullNormals, hullTexCoords);

  FDEBUG(("entering hull render\n"));
  renderHull(hullVertices, hullNormals, hullTexCoords,
             buildNormal, buildTexCoord, uWrap, vWrap,
             uValues, vValues, geoVertices, geoNormals, 
             geoTexCoords, geoLengths, geoTypes);

  UInt32 tot_uValues = uWrap ? uValues + 1 : uValues;
//  UInt32 tot_vValues = vWrap ? vValues + 1 : vValues;
  
  if(beginCap)
    {
      FDEBUG(("generating and rendering caps\n"));

      renderCap( crossSection, hullVertices, 
                 ccw, convex, buildNormal, buildTexCoord,
                 uWrap, vWrap, 0, 
                 uValues, vValues, 
                 geoVertices, geoNormals, geoTexCoords, 
                 geoLengths, geoTypes );


      renderCap( crossSection, hullVertices, 
                 ccw, convex, buildNormal, buildTexCoord,
                 uWrap, vWrap, tot_uValues - 1, 
                 uValues, vValues,
                 geoVertices, geoNormals, geoTexCoords, 
                 geoLengths, geoTypes );
      
    }


  GeometryPtr geo = Geometry::create();

  beginEditCP(geo);

  geo->setTypes(geoTypes);
  geo->setLengths(geoLengths);

  geo->setNormals(geoNormals);
  geo->setPositions(geoVertices);
  geo->setTexCoords(geoTexCoords);

  endEditCP(geo);
  
  return geo;
}
