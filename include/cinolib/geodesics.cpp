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
#include <cinolib/geodesics.h>
#include <cinolib/vector_field.h>
#include <cinolib/gradient.h>
#include <cinolib/laplacian.h>
#include <cinolib/vertex_mass.h>
#include <cinolib/linear_solvers.h>

namespace cinolib
{

template<class Mesh>
CINO_INLINE
ScalarField compute_geodesics(      Mesh              & m,
                              const std::vector<uint> & heat_charges,
                              const int                 laplacian_mode,
                              const float               time_scalar,
                              const bool                hard_constrain_charges)
{
    // optimize position and scale to get better numerical precision
    double d = m.bbox().diag();
    vec3d  c = m.bbox().center();
    m.translate(-c);
    m.scale(1.0/d);

    // use the squared avg edge length as time step, as suggested in the original paper
    double time = m.edge_avg_length();
    time *= time;
    time *= time_scalar;

    Eigen::SparseMatrix<double> L   = laplacian(m, laplacian_mode);
    Eigen::SparseMatrix<double> MM  = mass_matrix(m);
    Eigen::SparseMatrix<double> G   = gradient_matrix(m);
    Eigen::VectorXd             rhs = Eigen::VectorXd::Zero(m.num_verts());

    for(uint vid : heat_charges) rhs[vid] = 1.0;

    ScalarField heat(m.num_verts());
    solve_square_system(MM - time * L, rhs, heat);

    VectorField grad = G * heat;
    grad.normalize();

    ScalarField geodesics(m.num_verts());

    // this is of course not supported in the amortized version,
    // as the matrix changes every time
    if(hard_constrain_charges)
    {
        std::map<uint,double> bcs;
        for(uint vid : heat_charges) bcs[vid] = 1.0;
        solve_square_system_with_bc(-L, G.transpose() * grad, geodesics, bcs, SIMPLICIAL_LDLT);
    }
    else
    {
        solve_square_system(-L, G.transpose() * grad, geodesics, SIMPLICIAL_LDLT);
    }

    // restore original scale and position
    m.scale(d);
    m.translate(c);

    geodesics.normalize_in_01();
    return geodesics;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<class Mesh>
CINO_INLINE
ScalarField compute_geodesics_amortized(      Mesh              & m,
                                              GeodesicsCache    & cache,
                                        const std::vector<uint> & heat_charges,
                                        const int                 laplacian_mode,
                                        const float               time_scalar)
{
    // first call, heavy solve (matrix factorization + gradient matrix)
    if (cache.heat_flow_cache == NULL)
    {
        // optimize position and scale to get better numerical precision
        double d = m.bbox().diag();
        vec3d  c = m.bbox().center();
        m.translate(-c);
        m.scale(1.0/d);

        // use the squared avg edge length as time step, as suggested in the original paper
        double time = m.edge_avg_length();
        time *= time;
        time *= time_scalar;

        Eigen::SparseMatrix<double> L   = laplacian(m, laplacian_mode);
        Eigen::SparseMatrix<double> MM  = mass_matrix(m);
        Eigen::VectorXd             rhs = Eigen::VectorXd::Zero(m.num_verts());

        for(uint vid : heat_charges) rhs[vid] = 1.0;

        ScalarField heat(m.num_verts());
        cache.heat_flow_cache = new Eigen::SimplicialLLT<Eigen::SparseMatrix<double>>(MM - time * L);
        assert(cache.heat_flow_cache->info() == Eigen::Success);
        heat = cache.heat_flow_cache->solve(rhs).eval();

        cache.gradient_matrix = gradient_matrix(m);
        VectorField grad = cache.gradient_matrix * heat;
        grad.normalize();

        ScalarField geodesics(m.num_verts());
        cache.integration_cache = new Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>>(-L);
        assert(cache.integration_cache->info() == Eigen::Success);
        geodesics = cache.integration_cache->solve(cache.gradient_matrix.transpose() * grad).eval();
        geodesics.normalize_in_01();

        // restore original scale and position
        m.scale(d);
        m.translate(c);
        return geodesics;
    }
    else // solve by back-substitution using pre-factored matrices
    {
        Eigen::VectorXd rhs = Eigen::VectorXd::Zero(m.num_verts());
        for(uint vid : heat_charges) rhs[vid] = 1.0;
        ScalarField heat = cache.heat_flow_cache->solve(rhs).eval();

        VectorField grad = cache.gradient_matrix * heat;
        grad.normalize();

        ScalarField geodesics(m.num_verts());
        geodesics = cache.integration_cache->solve(cache.gradient_matrix.transpose() * grad).eval();
        geodesics.normalize_in_01();

        return geodesics;
    }

}

}
