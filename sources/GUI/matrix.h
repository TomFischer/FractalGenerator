/*
* Copyright (C) 2004-2012 Thomas Fischer
*
* This file is part of "FractalGenerator". "FractalGenerator" is free
* software: you can redistribute it and/or modify it under the terms of
* the GNU General Public License as published by the Free Software Foundation,
* either version 3 of the License, or (at your option) any later version.
*
* "FractalGenerator" is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* "FractalGenerator". If not, see <http://www.gnu.org/licenses/>.
*
* Author: Thomas Fischer
*
*/

/*
 * @file matrix.h
 *
 *  Created on: 07/2004
 *      Author: Thomas Fischer
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <new>
#include <exception>
#include <stdexcept>

/** \ingroup utils
 * \ingroup math
 */

/** Matrix repr&auml;sentiert eine Matrix beliebigen Datentyps.
 *
 * Jedoch machen einige Operationen nur mit numerischen Typen Sinn.
 */
template <class T>
class Matrix
{
public:
   Matrix (size_t rows, size_t cols);
   Matrix (const Matrix &src);
   ~Matrix ();

   size_t getRows() const { return rows; }
   size_t getCols() const { return cols; }
   T &operator()(size_t row, size_t col);
   T &operator()(size_t row, size_t col) const;

 private:
   size_t rows;
   size_t cols;
   T *data;
};

template <class T>
Matrix<T>::Matrix(size_t arows, size_t acols)
    : rows(arows), cols(acols), data(new T[rows * cols])
{}

template <class T>
Matrix<T>::Matrix(const Matrix& src)
    : rows(src.getRows()), cols(src.getCols()), data(NULL)
{
    data = new T[rows * cols];

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            data[i * cols + j] = src(i, j);
}

template <class T> Matrix<T>::~Matrix ()
{
   delete [] data;
}

template <class T>
T& Matrix<T>::operator()(size_t row, size_t col)
{
   if ( (row >= rows) | ( col >= cols) )
      throw std::range_error ("Matrix: op() range error");
   return data [row * cols + col];
}

template <class T>
T& Matrix<T>::operator()(size_t row, size_t col) const
{
    if ((row >= rows) | (col >= cols))
        throw std::range_error("Matrix: op() const range error");
    return data[row * cols + col];
}
#endif
