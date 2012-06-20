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
*/

/*
 * @file TemplatePoint.h
 *
 *  Created on: 08/2004
 *      Author: Thomas Fischer
 */

#include <exception>
#include <stdexcept>
#include <cassert>

#ifndef _TEMPLATEPOINT_H_
#define _TEMPLATEPOINT_H_

/**	\defgroup utils
 * Eine Sammlung von Werkzeugen die man gelegentlich ben&ouml;tigt.
 */

/** \defgroup math
 * Eine Sammlung von mathematischen Klassen.
 */

/** \ingroup utils
 *	\ingroup math
 */

/**
 * \brief class-template for points can be instantiated by a numeric type and a dimension.
 * \param T the coordinate type
 */
template<class COORDINATE_TYPE, size_t DIM> class TemplatePoint
{
public:
	/** Standardkonstruktor.
	 * Point () setzt die Dimension des Punktes  wie bei der Typdeklaration
	 * angegeben. Eine Initialisierung der einzelnen Koordinaten findet
	 * nicht statt.
	 */
	TemplatePoint()
	{};

	/** Konstruktor dem die Koordinaten des Punktes in einem Feld
	 * &uuml;bergeben werden.
	 *
	 * \param init_array dass der Initialisierung dienende Feld, welches
	 * vom gleichen Typ ist wie der Punkt und die gleiche Dimension hat
	 * wie der Punkt selbst.
	 */
	TemplatePoint(COORDINATE_TYPE init_array[DIM])
	{
		for (size_t i = 0; i < DIM; ++i)
			_coords[i] = init_array[i];
	};

	/** setCoordinate &uuml;berpr&uuml;ft die Grenzen und speichert,
	 * falls keine Bereichs&uuml;berschreitung aufgetreten ist, data an
	 * der spezifizierten Stelle ab
	 * \param coordinate Nummer der Koordinate
	 * \param data Datum, welches an die Stelle coordinate gesetzt werden
	 * soll
	 */
	void setCoordinate(size_t coordinate, COORDINATE_TYPE data)
	{
		if ((coordinate < 0) | (DIM <= coordinate))
			throw std::range_error("Point::setCoordinate range error");
		_coords[coordinate] = data;
	}

	/** \brief access operator
	 *  The access to the point coordinates is like the access to a field. Code example:
	 * \code
	 * TemplatePoint<double,3> point (1.0, 2.0, 3.0);
	 * double sqrNrm2 = point[0] * point[0] + point[1] * point[1] + point[2] + point[2];
	 * \endcode
	 */
	COORDINATE_TYPE& operator[](size_t idx)
	{
		assert(idx <= DIM);
		return _coords[idx];
	}

	/** \brief const access operator
	 *  The access to the point coordinates is like the access to a field. Code example:
	 * \code
	 * TemplatePoint<double,3> point (1.0, 2.0, 3.0);
	 * double sqrNrm2 = point[0] * point[0] + point[1] * point[1] + point[2] + point[2];
	 * \endcode
	 */
	const COORDINATE_TYPE& operator[](size_t idx) const
	{
		assert(idx <= DIM);
		return _coords[idx];
	}

private:
	COORDINATE_TYPE _coords[DIM];
};

#endif	//_TEMPLATEPOINT_H_
