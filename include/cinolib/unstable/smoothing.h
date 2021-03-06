/*********************************************************************************
*  Copyright(C) 2016: Marco Livesu                                               *
*  All rights reserved.                                                          *
*                                                                                *
*  This file is part of CinoLib                                                  *
*                                                                                *
*  CinoLib is dual-licensed:                                                     *
*                                                                                *
*   - For non-commercial use you can redistribute it and/or modify it under the  *
*     terms of the GNU General Public License as published by the Free Software  *
*     Foundation; either version 3 of the License, or (at your option) any later *
*     version.                                                                   *
*                                                                                *
*   - If you wish to use it as part of a commercial software, a proper agreement *
*     with the Author(s) must be reached, based on a proper licensing contract.  *
*                                                                                *
*  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE       *
*  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.     *
*                                                                                *
*  Author(s):                                                                    *
*                                                                                *
*     Marco Livesu (marco.livesu@gmail.com)                                      *
*     http://pers.ge.imati.cnr.it/livesu/                                        *
*                                                                                *
*     Italian National Research Council (CNR)                                    *
*     Institute for Applied Mathematics and Information Technologies (IMATI)     *
*     Via de Marini, 6                                                           *
*     16149 Genoa,                                                               *
*     Italy                                                                      *
**********************************************************************************/
#ifndef CINO_SMOOTHING_H
#define CINO_SMOOTHING_H

#include <set>
#include <sys/types.h>
#include <cinolib/cino_inline.h>
#include <cinolib/symbols.h>
#include <cinolib/meshes/abstract_mesh.h>

namespace cinolib
{

/*
 * Implementation of Taubin Smoothing.
 *
 * Reference:
 * Curve and Surface Smoothing Without Shrinkage
 * Gabriel Taubin
 * Proceeedings of IEEE 5th International Conference on Computer Vision, 1995.
 *
*/

template<class M, class V, class E, class P>
CINO_INLINE
void smooth_taubin(AbstractMesh<M,V,E,P> & m,
                   const int               mode          =  COTANGENT,
                   const std::set<uint>    do_not_smooth =  std::set<uint>(),
                   const uint              n_iters       =  10,
                   const double            lambda        =  0.89,
                   const double            mu            = -0.9);

}

#ifndef  CINO_STATIC_LIB
#include "smoothing.cpp"
#endif

#endif // CINO_SMOOTHING_H
