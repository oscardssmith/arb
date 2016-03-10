/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2016 Arb authors

******************************************************************************/

#include "arb_mat.h"

void
arb_mat_solve_cho_precomp(arb_mat_t X,
    const arb_mat_t L, const arb_mat_t B, slong prec)
{
    slong i, j, c, n, m;

    n = arb_mat_nrows(X);
    m = arb_mat_ncols(X);

    arb_mat_set(X, B);

    for (c = 0; c < m; c++)
    {
        /* solve Ly = b */
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < i; j++)
            {
                arb_submul(arb_mat_entry(X, i, c),
                    arb_mat_entry(L, i, j), arb_mat_entry(X, j, c), prec);
            }
            arb_div(arb_mat_entry(X, i, c), arb_mat_entry(X, i, c),
                arb_mat_entry(L, i, i), prec);
        }

        /* solve Ux = y */
        for (i = n - 1; i >= 0; i--)
        {
            for (j = i + 1; j < n; j++)
            {
                arb_submul(arb_mat_entry(X, i, c),
                    arb_mat_entry(L, j, i), arb_mat_entry(X, j, c), prec);
            }
            arb_div(arb_mat_entry(X, i, c), arb_mat_entry(X, i, c),
                arb_mat_entry(L, i, i), prec);
        }
    }
}