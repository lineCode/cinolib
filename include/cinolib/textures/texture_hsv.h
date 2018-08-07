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
#ifndef CINO_TEXTURE_HSV_H
#define CINO_TEXTURE_HSV_H

#include <stdint.h>

namespace cinolib
{

static const uint8_t hsv_texture1D[768] =
{
    0, 0, 255,
    0, 4, 255,
    0, 8, 255,
    0, 12, 255,
    0, 16, 255,
    0, 20, 255,
    0, 24, 255,
    0, 28, 255,
    0, 32, 255,
    0, 36, 255,
    0, 40, 255,
    0, 44, 255,
    0, 48, 255,
    0, 52, 255,
    0, 56, 255,
    0, 60, 255,
    0, 64, 255,
    0, 68, 255,
    0, 72, 255,
    0, 76, 255,
    0, 80, 255,
    0, 84, 255,
    0, 88, 255,
    0, 92, 255,
    0, 96, 255,
    0, 100, 255,
    0, 104, 255,
    0, 108, 255,
    0, 112, 255,
    0, 116, 255,
    0, 120, 255,
    0, 124, 255,
    0, 128, 255,
    0, 132, 255,
    0, 136, 255,
    0, 140, 255,
    0, 144, 255,
    0, 148, 255,
    0, 152, 255,
    0, 156, 255,
    0, 160, 255,
    0, 164, 255,
    0, 168, 255,
    0, 172, 255,
    0, 176, 255,
    0, 180, 255,
    0, 184, 255,
    0, 188, 255,
    0, 192, 255,
    0, 196, 255,
    0, 200, 255,
    0, 204, 255,
    0, 208, 255,
    0, 212, 255,
    0, 216, 255,
    0, 220, 255,
    0, 224, 255,
    0, 228, 255,
    0, 232, 255,
    0, 236, 255,
    0, 240, 255,
    0, 244, 255,
    0, 248, 255,
    0, 252, 255,
    0, 255, 253,
    0, 255, 249,
    0, 255, 245,
    0, 255, 241,
    0, 255, 237,
    0, 255, 233,
    0, 255, 229,
    0, 255, 225,
    0, 255, 221,
    0, 255, 217,
    0, 255, 213,
    0, 255, 209,
    0, 255, 205,
    0, 255, 201,
    0, 255, 197,
    0, 255, 193,
    0, 255, 189,
    0, 255, 185,
    0, 255, 181,
    0, 255, 177,
    0, 255, 173,
    0, 255, 169,
    0, 255, 165,
    0, 255, 161,
    0, 255, 157,
    0, 255, 153,
    0, 255, 149,
    0, 255, 145,
    0, 255, 141,
    0, 255, 137,
    0, 255, 133,
    0, 255, 129,
    0, 255, 125,
    0, 255, 121,
    0, 255, 117,
    0, 255, 113,
    0, 255, 109,
    0, 255, 105,
    0, 255, 101,
    0, 255, 97,
    0, 255, 93,
    0, 255, 89,
    0, 255, 85,
    0, 255, 81,
    0, 255, 77,
    0, 255, 73,
    0, 255, 69,
    0, 255, 65,
    0, 255, 61,
    0, 255, 57,
    0, 255, 53,
    0, 255, 49,
    0, 255, 45,
    0, 255, 41,
    0, 255, 37,
    0, 255, 33,
    0, 255, 29,
    0, 255, 25,
    0, 255, 21,
    0, 255, 17,
    0, 255, 13,
    0, 255, 9,
    0, 255, 5,
    0, 255, 1,
    2, 255, 0,
    6, 255, 0,
    10, 255, 0,
    14, 255, 0,
    18, 255, 0,
    22, 255, 0,
    26, 255, 0,
    30, 255, 0,
    34, 255, 0,
    38, 255, 0,
    42, 255, 0,
    46, 255, 0,
    50, 255, 0,
    54, 255, 0,
    58, 255, 0,
    62, 255, 0,
    66, 255, 0,
    70, 255, 0,
    74, 255, 0,
    78, 255, 0,
    82, 255, 0,
    86, 255, 0,
    90, 255, 0,
    94, 255, 0,
    98, 255, 0,
    102, 255, 0,
    106, 255, 0,
    110, 255, 0,
    114, 255, 0,
    118, 255, 0,
    122, 255, 0,
    126, 255, 0,
    130, 255, 0,
    134, 255, 0,
    138, 255, 0,
    142, 255, 0,
    146, 255, 0,
    150, 255, 0,
    154, 255, 0,
    158, 255, 0,
    162, 255, 0,
    166, 255, 0,
    170, 255, 0,
    174, 255, 0,
    178, 255, 0,
    182, 255, 0,
    186, 255, 0,
    190, 255, 0,
    194, 255, 0,
    198, 255, 0,
    202, 255, 0,
    206, 255, 0,
    210, 255, 0,
    214, 255, 0,
    218, 255, 0,
    222, 255, 0,
    226, 255, 0,
    230, 255, 0,
    234, 255, 0,
    238, 255, 0,
    242, 255, 0,
    246, 255, 0,
    250, 255, 0,
    254, 255, 0,
    255, 251, 0,
    255, 247, 0,
    255, 243, 0,
    255, 239, 0,
    255, 235, 0,
    255, 231, 0,
    255, 227, 0,
    255, 223, 0,
    255, 219, 0,
    255, 215, 0,
    255, 211, 0,
    255, 207, 0,
    255, 203, 0,
    255, 199, 0,
    255, 195, 0,
    255, 191, 0,
    255, 187, 0,
    255, 183, 0,
    255, 179, 0,
    255, 175, 0,
    255, 171, 0,
    255, 167, 0,
    255, 163, 0,
    255, 159, 0,
    255, 155, 0,
    255, 151, 0,
    255, 147, 0,
    255, 143, 0,
    255, 139, 0,
    255, 135, 0,
    255, 131, 0,
    255, 127, 0,
    255, 123, 0,
    255, 119, 0,
    255, 115, 0,
    255, 111, 0,
    255, 107, 0,
    255, 103, 0,
    255, 99, 0,
    255, 95, 0,
    255, 91, 0,
    255, 87, 0,
    255, 83, 0,
    255, 79, 0,
    255, 75, 0,
    255, 71, 0,
    255, 67, 0,
    255, 63, 0,
    255, 59, 0,
    255, 55, 0,
    255, 51, 0,
    255, 47, 0,
    255, 43, 0,
    255, 39, 0,
    255, 35, 0,
    255, 31, 0,
    255, 27, 0,
    255, 23, 0,
    255, 19, 0,
    255, 15, 0,
    255, 11, 0,
    255, 7, 0,
    255, 3, 0,
    255, 0, 0,
};

}

#endif // CINO_TEXTURE_HSV_H