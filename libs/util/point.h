/**
 *  A class template that stores an x and y coordinate.
 *	@file		point.h
 *	@author		Tom Creusot
 */

#pragma once

#include <cmath>

namespace util
{
/**
 *  A class template that stores an x and y coordinate.
 *	@tparam T	The datatype to store.
 *
 *	@example
 *		Point<int> point(1, 0);
 *		point.x = 10;
 *		Point<int> point2(10, 10);
 *		cout << point2.Distance(point) << endl;	// 10
 *		cout << point2.Equal(point) << endl;	// false
 *
 *
 *	@author		Tom Creusot
 */

template <class T> class Point
{
public:
	/// The x variable.
	T x;
	/// The y variable.
	T y;

	/**
	 * @brief 	Default Constructor.
	 * @details	Sets all values to 0.
	 */

	Point ( )
	{
		x = 0;
		y = 0;
	}


	/**
	 * @brief		Alternate Constructor.
	 * @param val	The value to set x and y.
	 * @details		This is for testing code of users of Point.
	 */

	Point ( T val )
	{
		x = val;
		y = val;
	}

	/**
	* @brief 	Alternate Constructor
	* @param x_	The x position.
	* @param y_	The y position.
	*/

	Point ( T x_, T y_ )
	{
		x = x_;
		y = y_;
	}


	/**
	 * @brief			Alternate Constructor.
	 * @param hoursX	The whole decimal.
	 * @param minutesX	The whole minute.
	 * @param secondsX	Seconds and anything bellow.
	 * @param degreesY	The whole decimal.
	 * @param minutesY	The whole minute.
	 * @param secondsY	Seconds and anything bellow.
	 * @details Creates a Point object with the ra/dec coordinate.
	 */

	Point  ( 	T hoursX, T minutesX, T secondsX,
				T degreesY, T minutesY, T secondsY	)
	{
		Set ( hoursX * 90 / 24, minutesX, secondsX, degreesY, minutesY, secondsY );
	}

	/**
	 * @brief			Copy Constructor
	 * @param p [in]	The value to copy.
	 */

	Point ( const Point& p )
	{
		x = p.x;
		y = p.y;
	}

	/** @brief Getter of x. @return x. */
	inline T& get_x		()			{ return x; }
	/** @brief Getter of y. @return y. */
	inline T& get_y 	()			{ return y; }

	/** @brief setter of x. @param _x x. */
	inline void set_x	( T& _x )	{ x = _x; }
	/** @brief setter of y. @param _y y. */
	inline void set_y	( T& _y )	{ y = _y; }




	/**
	 * @brief		Sets the position of the x and y (for malloced pointers).
	 * @param x_	The x position.
	 * @param y_	The y position.
	 */

	void Set ( T x_, T y_ )
	{
		x = x_;
		y = y_;
	}


	/**
	 * @brief Creates a Point object with the ra/dec coordinate.
	 * @param degrees_x	The whole decimal.
	 * @param minutes_x	The whole minute.
	 * @param seconds_x	Seconds and anything below.
	 * @param degrees_y	The whole decimal.
	 * @param minutes_y	The whole minute.
	 * @param seconds_y	Seconds and anything below.
	 */
	void Set (	T degrees_x, T minutes_x, T seconds_x,
				T degrees_y, T minutes_y, T seconds_y	)
	{
		T sign = 1 - (degrees_x < 0) * 2;
		x = degrees_x + (minutes_x / 60 + seconds_x / 3600) * sign;
		sign = 1 - (degrees_y < 0) * 2;
		y = degrees_y + (minutes_y / 60 + seconds_y / 3600) * sign;
	}


	/**
	* @brief		Finds the hypotenues between this and the other point.
	* @param [in]	other The other point to measure with.
	* @return		The distance between the points.
	*/

	T Distance ( Point<T>& other ) const
	{
		return (T) hypot(x - other.x, y - other.y);
	}



	/**
	* @brief		Finds if other point is the same position.
	* @param [in]	other The other point to test against.
	* @return 		True if x and y are equal to this x and y.
	*/

	bool Equal ( Point<T>& other ) const
	{
		return Equal(other.x, other.y);
	}


	/**
	 * @brief			Finds if the other point is the same position.
	 * @param xx 		The x position to compare to.
	 * @param yy 		The y position to compare to.
	 * @return 			True if x and y are equal to xx and yy.
	 */

	bool Equal ( T xx, T yy ) const
	{
		return fabs(x - xx) < 0.0001 && fabs(y - yy) < 0.0001;
	}

};
}