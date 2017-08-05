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
#include <cinolib/meshes/polygonmesh/drawable_polygonmesh.h>


namespace cinolib
{

template<class M, class V, class E, class F>
CINO_INLINE
DrawablePolygonmesh<M,V,E,F>::DrawablePolygonmesh() : Polygonmesh<M,V,E,F>()
{
    init_drawable_stuff();
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
DrawablePolygonmesh<M,V,E,F>::DrawablePolygonmesh(const char * filename) : Polygonmesh<M,V,E,F>(filename)
{
    init_drawable_stuff();
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
DrawablePolygonmesh<M,V,E,F>::DrawablePolygonmesh(const std::vector<vec3d>             & verts,
                                                  const std::vector<std::vector<uint>> & faces)
    : Polygonmesh<M,V,E,F>(verts,faces)
{
    init_drawable_stuff();
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
DrawablePolygonmesh<M,V,E,F>::DrawablePolygonmesh(const std::vector<double>            & coords,
                                                  const std::vector<std::vector<uint>> & faces)
    : Polygonmesh<M,V,E,F>(coords,faces)
{
    init_drawable_stuff();
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::init_drawable_stuff()
{
    slicer = MeshSlicer<Polygonmesh<M,V,E,F>>(*this);

    drawlist.draw_mode = DRAW_TRIS | DRAW_TRI_SMOOTH | DRAW_TRI_FACECOLOR | DRAW_SEGS;
    drawlist.seg_width = 1;

    updateGL();
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::draw(const float) const
{
    render(drawlist);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::updateGL()
{
    drawlist.tri_coords.clear();
    drawlist.tris.clear();
    drawlist.tri_v_norms.clear();
    drawlist.tri_v_colors.clear();
    drawlist.segs.clear();
    drawlist.seg_coords.clear();
    drawlist.seg_colors.clear();

    for(uint fid=0; fid<this->num_faces(); ++fid)
    {
        if (!(this->poly_data(fid).visible)) continue;

        for(uint i=0; i< this->tessellated_faces.at(fid).size()/3; ++i)
        {
            uint vid0 = this->tessellated_faces.at(fid).at(3*i+0);
            uint vid1 = this->tessellated_faces.at(fid).at(3*i+1);
            uint vid2 = this->tessellated_faces.at(fid).at(3*i+2);

            int base_addr = drawlist.tri_coords.size()/3;

            drawlist.tris.push_back(base_addr    );
            drawlist.tris.push_back(base_addr + 1);
            drawlist.tris.push_back(base_addr + 2);

            drawlist.tri_coords.push_back(this->vert(vid0).x());
            drawlist.tri_coords.push_back(this->vert(vid0).y());
            drawlist.tri_coords.push_back(this->vert(vid0).z());
            drawlist.tri_coords.push_back(this->vert(vid1).x());
            drawlist.tri_coords.push_back(this->vert(vid1).y());
            drawlist.tri_coords.push_back(this->vert(vid1).z());
            drawlist.tri_coords.push_back(this->vert(vid2).x());
            drawlist.tri_coords.push_back(this->vert(vid2).y());
            drawlist.tri_coords.push_back(this->vert(vid2).z());

            drawlist.tri_v_norms.push_back(this->vert_data(vid0).normal.x());
            drawlist.tri_v_norms.push_back(this->vert_data(vid0).normal.y());
            drawlist.tri_v_norms.push_back(this->vert_data(vid0).normal.z());
            drawlist.tri_v_norms.push_back(this->vert_data(vid1).normal.x());
            drawlist.tri_v_norms.push_back(this->vert_data(vid1).normal.y());
            drawlist.tri_v_norms.push_back(this->vert_data(vid1).normal.z());
            drawlist.tri_v_norms.push_back(this->vert_data(vid2).normal.x());
            drawlist.tri_v_norms.push_back(this->vert_data(vid2).normal.y());
            drawlist.tri_v_norms.push_back(this->vert_data(vid2).normal.z());

            if (drawlist.draw_mode & DRAW_TRI_FACECOLOR) // replicate f color on each vertex
            {
                drawlist.tri_v_colors.push_back(this->poly_data(fid).color.r);
                drawlist.tri_v_colors.push_back(this->poly_data(fid).color.g);
                drawlist.tri_v_colors.push_back(this->poly_data(fid).color.b);
                drawlist.tri_v_colors.push_back(this->poly_data(fid).color.a);
                drawlist.tri_v_colors.push_back(this->poly_data(fid).color.r);
                drawlist.tri_v_colors.push_back(this->poly_data(fid).color.g);
                drawlist.tri_v_colors.push_back(this->poly_data(fid).color.b);
                drawlist.tri_v_colors.push_back(this->poly_data(fid).color.a);
                drawlist.tri_v_colors.push_back(this->poly_data(fid).color.r);
                drawlist.tri_v_colors.push_back(this->poly_data(fid).color.g);
                drawlist.tri_v_colors.push_back(this->poly_data(fid).color.b);
                drawlist.tri_v_colors.push_back(this->poly_data(fid).color.a);
            }
            else if (drawlist.draw_mode & DRAW_TRI_VERTCOLOR)
            {
                drawlist.tri_v_colors.push_back(this->vert_data(vid0).color.r);
                drawlist.tri_v_colors.push_back(this->vert_data(vid0).color.g);
                drawlist.tri_v_colors.push_back(this->vert_data(vid0).color.b);
                drawlist.tri_v_colors.push_back(this->vert_data(vid0).color.a);
                drawlist.tri_v_colors.push_back(this->vert_data(vid1).color.r);
                drawlist.tri_v_colors.push_back(this->vert_data(vid1).color.g);
                drawlist.tri_v_colors.push_back(this->vert_data(vid1).color.b);
                drawlist.tri_v_colors.push_back(this->vert_data(vid1).color.a);
                drawlist.tri_v_colors.push_back(this->vert_data(vid2).color.r);
                drawlist.tri_v_colors.push_back(this->vert_data(vid2).color.g);
                drawlist.tri_v_colors.push_back(this->vert_data(vid2).color.b);
                drawlist.tri_v_colors.push_back(this->vert_data(vid2).color.a);
            }
        }
    }

    // bake wireframe as border
    for(uint eid=0; eid<this->num_edges(); ++eid)
    {
        bool masked = true;
        for(uint fid : this->adj_e2p(eid))
        {
            if (this->poly_data(fid).visible) masked = false;
        }
        if (masked) continue;

        int base_addr = drawlist.seg_coords.size()/3;
        drawlist.segs.push_back(base_addr    );
        drawlist.segs.push_back(base_addr + 1);

        vec3d vid0 = this->edge_vert(eid,0);
        vec3d vid1 = this->edge_vert(eid,1);

        drawlist.seg_coords.push_back(vid0.x());
        drawlist.seg_coords.push_back(vid0.y());
        drawlist.seg_coords.push_back(vid0.z());
        drawlist.seg_coords.push_back(vid1.x());
        drawlist.seg_coords.push_back(vid1.y());
        drawlist.seg_coords.push_back(vid1.z());

        drawlist.seg_colors.push_back(this->edge_data(eid).color.r);
        drawlist.seg_colors.push_back(this->edge_data(eid).color.g);
        drawlist.seg_colors.push_back(this->edge_data(eid).color.b);
        drawlist.seg_colors.push_back(this->edge_data(eid).color.a);
        drawlist.seg_colors.push_back(this->edge_data(eid).color.r);
        drawlist.seg_colors.push_back(this->edge_data(eid).color.g);
        drawlist.seg_colors.push_back(this->edge_data(eid).color.b);
        drawlist.seg_colors.push_back(this->edge_data(eid).color.a);
    }
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::slice(const float thresh, // thresh on centroids or quality
                                         const int   item,   // X, Y, Z, L, Q
                                         const int   sign,   // either LEQ or GEQ
                                         const int   mode)   // either AND or OR
{
    slicer.update(*this, thresh, item, sign, mode); // update per element visibility flags
    updateGL();
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::show_mesh(const bool b)
{
    if (b) drawlist.draw_mode |=  DRAW_TRIS;
    else   drawlist.draw_mode &= ~DRAW_TRIS;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::show_mesh_flat()
{
    drawlist.draw_mode |=  DRAW_TRI_FLAT;
    drawlist.draw_mode &= ~DRAW_TRI_SMOOTH;
    drawlist.draw_mode &= ~DRAW_TRI_POINTS;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::show_mesh_smooth()
{
    drawlist.draw_mode |=  DRAW_TRI_SMOOTH;
    drawlist.draw_mode &= ~DRAW_TRI_FLAT;
    drawlist.draw_mode &= ~DRAW_TRI_POINTS;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::show_mesh_points()
{
    drawlist.draw_mode |=  DRAW_TRI_POINTS;
    drawlist.draw_mode &= ~DRAW_TRI_FLAT;
    drawlist.draw_mode &= ~DRAW_TRI_SMOOTH;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::show_face_color()
{
    drawlist.draw_mode |=  DRAW_TRI_FACECOLOR;
    drawlist.draw_mode &= ~DRAW_TRI_VERTCOLOR;
    drawlist.draw_mode &= ~DRAW_TRI_QUALITY;
    drawlist.draw_mode &= ~DRAW_TRI_TEXTURE1D;
    glDisable(GL_TEXTURE_1D);
    updateGL();
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::show_face_texture1D(const GLint texture)
{
    drawlist.draw_mode |=  DRAW_TRI_TEXTURE1D;
    drawlist.draw_mode &= ~DRAW_TRI_VERTCOLOR;
    drawlist.draw_mode &= ~DRAW_TRI_FACECOLOR;
    drawlist.draw_mode &= ~DRAW_TRI_QUALITY;

    if (drawlist.tri_text_id > 0) glDeleteTextures(1, &drawlist.tri_text_id);
    glGenTextures(1, &drawlist.tri_text_id);
    glBindTexture(GL_TEXTURE_1D, drawlist.tri_text_id);
    switch (texture)
    {
//        case TEXTURE_1D_ISOLINES               : glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, isolines_texture1D); break;
        case TEXTURE_1D_HSV_RAMP           : glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, quality_ramp_texture1D); break;
        case TEXTURE_1D_HSV_RAMP_W_ISOLINES: glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, quality_ramp_texture1D_with_isolines); break;
        default : assert("Unknown 1D Texture" && false);
    }
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_R,     GL_REPEAT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_TEXTURE_1D);

    updateGL();
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::show_face_wireframe(const bool b)
{
    if (b) drawlist.draw_mode |=  DRAW_SEGS;
    else   drawlist.draw_mode &= ~DRAW_SEGS;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::show_face_wireframe_color(const Color & c)
{
    this->edge_set_color(c); // NOTE: this will change alpha for ANY adge (both interior and boundary)
    updateGL();
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::show_face_wireframe_width(const float width)
{
    drawlist.seg_width = width;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class M, class V, class E, class F>
CINO_INLINE
void DrawablePolygonmesh<M,V,E,F>::show_face_wireframe_transparency(const float alpha)
{
    this->edge_set_alpha(alpha); // NOTE: this will change alpha for ANY adge (both interior and boundary)
    updateGL();
}

}
