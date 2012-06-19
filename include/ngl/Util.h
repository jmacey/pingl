/*
  Copyright (C) 2009 Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef UTIL_H__
#define UTIL_H__
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include <cmath>
#include <vector>
#include "Vec4.h"
//----------------------------------------------------------------------------------------------------------------------
/// @file Util.h
/// @brief some useful definitions and functions
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @file Util.h
/// @author Jonathan Macey
/// @version 1.2
/// @date 24/11/04
/// @brief lots of usful functions for ngl
//----------------------------------------------------------------------------------------------------------------------
/// @brief  pre-compute the value for value for 2*PI
//----------------------------------------------------------------------------------------------------------------------
const static  ngl::Real TWO_PI= 2*M_PI; //6.28318530717958647692   //360
//----------------------------------------------------------------------------------------------------------------------
/// @brief  pre-compute the value for value for PI based on system M_PI
//----------------------------------------------------------------------------------------------------------------------
const static  ngl::Real PI=M_PI; //3.14159265358979323846       //180
//----------------------------------------------------------------------------------------------------------------------
/// @brief  pre-compute the value for value for PI/2.0
//----------------------------------------------------------------------------------------------------------------------
const static  ngl::Real PI2=M_PI/2.0; //1.57079632679489661923      //90
//----------------------------------------------------------------------------------------------------------------------
/// @brief  pre-compute the value for value for PI/4.0
//----------------------------------------------------------------------------------------------------------------------
const static  ngl::Real PI4=M_PI/4.0; //0.785398163397448309615     //45
//----------------------------------------------------------------------------------------------------------------------
/// @brief calculates the normal from 3 points and return the new normal as a Vector
/// @param[in]  _p1 the first point
/// @param[in]  _p2 the second point
/// @param[in]  _p3 the third point
/// @returns  the normal of the 3 points
//----------------------------------------------------------------------------------------------------------------------
extern  ngl::Vec4 calcNormal(
															const Vec4 &_p1,
															const Vec4 &_p2,
															const Vec4 &_p3
															);
//----------------------------------------------------------------------------------------------------------------------
/// @brief calculates the normal from 3 points and return the new normal as a Vector
/// @param[in]  _p1 the first point
/// @param[in]  _p2 the second point
/// @param[in]  _p3 the third point
/// @returns  the normal of the 3 points
//----------------------------------------------------------------------------------------------------------------------
extern  ngl::Vec3 calcNormal(
															const Vec3 &_p1,
															const Vec3 &_p2,
															const Vec3 &_p3
															);
//----------------------------------------------------------------------------------------------------------------------
/// @brief converts Degrees to Radians
/// @param[in]  _deg the angle to convert
/// @returns the angle in Radians
//----------------------------------------------------------------------------------------------------------------------
extern  ngl::Real radians(
													const Real _deg
												 );
//----------------------------------------------------------------------------------------------------------------------
/// @brief converts Radians to Degrees
/// @param[in]  _rad the angle in radians
/// @returns the angle in Degrees
//----------------------------------------------------------------------------------------------------------------------
extern  ngl::Real degrees(
													const Real _rad
												 );



extern  void NGLCheckGLError(
															const std::string  &_file,
															const int _line
														 );
//----------------------------------------------------------------------------------------------------------------------
/// @brief a simple template function for Linear Interpolation requires that any classes have
///    + - and * scalar (i.e. Real) overloaded operators
///    In the graphics lib this will work  for Vector and Colour
/// @param [in] _a the template value for the first parameter
/// @param [in] _b the template value for the first parameter
/// @param [in] _t the value for the blend between _a and _b must be between 0 - 1
//----------------------------------------------------------------------------------------------------------------------
template <class T> T lerp(
                          T _a,
                          T _b,
                          ngl::Real _t
                          )
{
	T p;
	p=_a+(_b-_a)*_t;
	return p;
}

template <class T> T trigInterp(
                                T _a,
                                T _b,
                                ngl::Real _t
                                )
{
  ngl::Real angle=radians(90*_t);
  return _a*cos(angle)*cos(angle)+_b*sin(angle)*sin(angle);
}

template <class T> T cubic(
                           T _a,
                            T _b,
                            ngl::Real _t
                            )
{
  ngl::Real v1=(2.0*_t*_t*_t)-3.0*(_t*_t)+1.0;
  ngl::Real v2=-(2.0*_t*_t*_t)+3*(_t*_t);
  return (_a*v1)+(_b*v2);
}



}
#endif

//----------------------------------------------------------------------------------------------------------------------
