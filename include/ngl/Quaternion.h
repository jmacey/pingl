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
//----------------------------------------------------------------------------------------------------------------------
/// @file  Quaternion.h
/// @author  Jon Macey with thanks to John Vince and Rob Bateman
/// @brief  Defines the class Quaternion based on John Vinces lecture notes
/// basically we have a scalar part and then a vector part (stored as x,y,z)
/// each component of the Quat is stored as a float value.
/// @class Quaternion "include/Quaternion.h"
//----------------------------------------------------------------------------------------------------------------------
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"


#ifndef QUATERNION_H__
#define QUATERNION_H__

#include <iostream>
#include "Vec4.h"

namespace ngl
{

// need to pre-declare the matrix class
class Mat4;


class  Quaternion
{

public:

	//----------------------------------------------------------------------------------------------------------------------
  /// @brief constructor
  /// @param [in]  _s  -  the s component of the quaternion
  /// @param [in]  _x  -  the x component of the quaternion
  /// @param [in]  _y  -  the y component of the quaternion
  /// @param [in]  _z  -  the z component of the quaternion
	//----------------------------------------------------------------------------------------------------------------------
  inline Quaternion(
                    const Real _s=0.0,
                    const Real _x=0.0,
                    const Real _y=0.0,
                    const Real _z=0.0
                   ):
                     m_s(_s),
                     m_x(_x),
                     m_y(_y),
                     m_z(_z) {;}

	//----------------------------------------------------------------------------------------------------------------------
  /// @brief copy constructor
  /// @param [in]  _q  -  the quaternion to copy
	//----------------------------------------------------------------------------------------------------------------------
  inline Quaternion(
                    const Quaternion& _q
                   ):
                     m_s(_q.m_s),
                     m_x(_q.m_x),
                     m_y(_q.m_y),
                     m_z(_q.m_z) {;}
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the quaternion values
  /// @param[in] _x the x value
  /// @param[in] _y the y value
  /// @param[in] _z the z value
  /// @param[in] _w the w value
	//----------------------------------------------------------------------------------------------------------------------
  inline void set(
										const Real& _s,
										const Real& _x,
										const Real& _y,
										const Real& _z
									)
                 {
                  m_s=_s;
                  m_x=_x;
                  m_y=_y;
                  m_z=_z;
                 }
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief accesor for the scalar part
	/// @returns m_s the scalar part of the quaternion
	//----------------------------------------------------------------------------------------------------------------------
	inline ngl::Real getS() const {return m_s;}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief accesor for the x vector components
	/// @returns m_x the scalar part of the quaternion
	//----------------------------------------------------------------------------------------------------------------------
	inline ngl::Real getX() const {return m_x;}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief accesor for the y vector components
	/// @returns m_y the scalar part of the quaternion
	//----------------------------------------------------------------------------------------------------------------------
	inline ngl::Real getY() const {return m_y;}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief accesor for the z vector components
	/// @returns m_z the scalar part of the quaternion
	//----------------------------------------------------------------------------------------------------------------------
	inline ngl::Real getZ() const {return m_z;}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief accesor for the  vector components as an ngl::Vector
	/// @returns a vector
	//----------------------------------------------------------------------------------------------------------------------
  inline ngl::Vec4 getVector() const {return ngl::Vec4(m_x,m_y,m_z,0);}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief mutator for the  vector components as an ngl::Vector
	/// @param[in] _v the vector to set the quat vector components from
	//----------------------------------------------------------------------------------------------------------------------
	inline void setVector(
                         const ngl::Vec4 &_v
												)
														{m_x=_v.m_x; m_y=_v.m_y; m_z=_v.m_z;}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief mutator for the scalar part
	/// @param[in] _s the scalar part of the quaternion to set
	//----------------------------------------------------------------------------------------------------------------------
	inline void setS(
										Real &_s
									 )
										{m_s=_s;}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief mutator for the x vector part
	/// @param[in] _x the x vector part of the quaternion to set
	//----------------------------------------------------------------------------------------------------------------------
	inline void setX(
										Real &_x
									 )
										{m_x=_x;}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief mutator for the y vector part
	/// @param[in] _x the x vector part of the quaternion to set
	//----------------------------------------------------------------------------------------------------------------------
	inline void setY(
										Real &_y
									 )
										{m_y=_y;}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief mutator for the z vector part
	/// @param[in] _z the z vector part of the quaternion to set
	//----------------------------------------------------------------------------------------------------------------------
	inline void setZ(
										Real &_z
									 )
										{m_z=_z;}

	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  Perform a multiplication between 2 quaternions
  /// @param[in] _q the rhs quaternion argument
	/// @return  the result of the mutliplication (product)
	//----------------------------------------------------------------------------------------------------------------------
  Quaternion operator *(
                        const Quaternion& _q
                       ) const;

	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  Perform a multiplication this and another quaternions
	/// sets the current quat q1 = q1*q2
  /// @param[in] _q the rhs quaternion argument
	//----------------------------------------------------------------------------------------------------------------------
	void operator *=(
										const Quaternion& _q
									 );

	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  Perform a multiplication between a quaternion and a scalar
  /// @param[in] _s the rhs scalar argument
	/// @return  the result of the mutliplication q*s
	//----------------------------------------------------------------------------------------------------------------------
	Quaternion operator *(
												 ngl::Real _s
												) const;

	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  Perform a multiplication this and  a real scalar
	/// sets the current quat to q=q*_s
  /// @param[in] _s the rhs quaternion argument
	//----------------------------------------------------------------------------------------------------------------------
	void operator *=(
									 ngl::Real _s
									);

	//----------------------------------------------------------------------------------------------------------------------
  /// @brief add two quaternions
  /// @param[in] _q the rhs quaternion argument
	/// @return  the result of the addition
	//----------------------------------------------------------------------------------------------------------------------
	Quaternion operator +(
                        const Quaternion& _q
                       ) const;
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  subtract two quaternions
  /// @param[in] _q the rhs quaternion argument
	/// @return  the result of the subtraction
	//----------------------------------------------------------------------------------------------------------------------
  Quaternion operator -(
                        const Quaternion& _q
                       ) const;
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  add _q to the current quaternion
  /// @param[in] _q the rhs quaternion argument
	//----------------------------------------------------------------------------------------------------------------------
	void operator +=(
										const Quaternion& _q
									 ) ;
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  subtract _q from the current quaternion
  /// @param[in] _q the rhs quaternion argument
	//----------------------------------------------------------------------------------------------------------------------
	void operator -=(
										const Quaternion& _q
									 ) ;

	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  normalise this  quaternion this sets each of the component parts
	/// by calculating the magnitude and dividing each component by this
	//----------------------------------------------------------------------------------------------------------------------
  void normalise();
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  returns the magnitude of the quaternion
  /// @return  The magnitude of the quaternion
	//----------------------------------------------------------------------------------------------------------------------
  Real magnitude() const ;
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  conjugate negate the vector part can also be done by the -() operator
  /// @returns the conjugate of the current quaternion
	//----------------------------------------------------------------------------------------------------------------------
	inline Quaternion  conjugate() const {return Quaternion(m_s,-m_x,-m_y,-m_z);}
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  conjugate negate the vector part can also be done by the -() operator
  /// @returns the conjugate of the current quaternion
	//----------------------------------------------------------------------------------------------------------------------
	inline Quaternion inverse()const {return Quaternion(m_s,-m_x,-m_y,-m_z);}

	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  conjugate negate the vector part but for the current vector -
  /// @returns the conjugate of the current quaternion
	//----------------------------------------------------------------------------------------------------------------------
	inline void operator -(){m_x=-m_x; m_y=-m_y; m_z=-m_z;}
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  returns the inverse of the quaternion (aka conjugate)
	/// the scalar part remains the same and we reverse the vector part
  /// @return  the conjugate of the quaternion
	//----------------------------------------------------------------------------------------------------------------------
  inline Quaternion operator-() const
															 {
																return Quaternion(m_s,-m_x,-m_y,-m_z );
															 }
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief test for equality
  /// @param [in] _q the quaternion to test against
  /// @returns true if the same (based on EPSILON test range) or false
	//----------------------------------------------------------------------------------------------------------------------
  bool operator == (
                     const Quaternion& _q
                    ) const;
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  this function spherically interpolates between two quaternions with respect to t
  /// @param [in]  _q1  -  the first quaternion
  /// @param [in]  _q2  -  the second quaternion
  /// @param [in]  _t  -  the interpolating t value
	//----------------------------------------------------------------------------------------------------------------------
   Quaternion slerp(
										const Quaternion &_q1,
										const Quaternion &_q2,
										const float &_t
										);

	 //----------------------------------------------------------------------------------------------------------------------
  /// @brief  the streaming operator for the quaternion
  /// @param [in]  _ifs  -  the input stream
  /// @param [in]  _q  -  the place to read the values into
	 //----------------------------------------------------------------------------------------------------------------------
  friend std::istream& operator >> (
                                    std::istream& _ifs,
                                    Quaternion &_q
                                   )
                                   {
                                    return _ifs >> _q.m_s >> _q.m_x >> _q.m_y >> _q.m_z;
                                   }
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  the streaming operator for the quaternion
  /// @param [in]  i_ifs  -  the input stream
  /// @param [in]  i_q  -  the place to read the values into
	//----------------------------------------------------------------------------------------------------------------------
  friend std::ostream& operator << (
                                    std::ostream& i_s,
                                    const Quaternion &i_q
                                   )
                                   {
                                    return i_s << i_q.m_s << " [" << i_q.m_x << "i," << i_q.m_y << "j," << i_q.m_z<<"k]";
                                   }


	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  operator to allow a quat to be multiplied by a vector
	/// V2=Q*V1 this is formed by sandwiching the vector between the current quat and the
	/// inverse of the current quat (conjugate) so we get q*_vec*q.conjugate() this is the main way to do
	/// quaternion rotation on points (or can use the rotatePoint method which does the same thing)
  /// we must ensure that the quat has been set to the correct values for rotation (i.e. set the axis and the rotation values
	/// this can be done using the rotateX/Y/Z or fromAxisAngle or fromEulerAngle methods
	/// @param[in]  _vec the vector to be multiplied
  /// @returns a vector formed from q*_vec*q^-1 (conjugate)
	//----------------------------------------------------------------------------------------------------------------------
  ngl::Vec4 operator* (
                          const ngl::Vec4 &_vec
                        ) const;


	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  set the current quaternion as a rotation around the X cartesian axis [1,0,0]
	/// @param[in] _angle the angle of rotation around the x axis in degrees
	//----------------------------------------------------------------------------------------------------------------------
	void rotateX(
								ngl::Real _angle
							 );
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  set the current quaternion as a rotation around the Y cartesian axis [0,1,0]
	/// @param[in] _angle the angle of rotation around the y axis in degrees
	//----------------------------------------------------------------------------------------------------------------------
	void rotateY(
								ngl::Real _angle
							 );
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  set the current quaternion as a rotation around the Z cartesian axis [0,0,1]
	/// @param[in] _angle the angle of rotation around the Z axis in degrees
	//----------------------------------------------------------------------------------------------------------------------
	void rotateZ(
								ngl::Real _angle
							 );

	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  set the current quaternion as a rotation around the vector _axis
	/// @brief[in] _axis the axis to rotate around (will be normalized)
	/// @param[in] _angle the angle of rotation around the Z axis in degrees
	//----------------------------------------------------------------------------------------------------------------------
	void fromAxisAngle(
                     const Vec4& _axis,
										 float _angle
										);
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  set the current quaternion as a rotation based on 3 Euler angles
	/// this will create the quat as a product of 3 seprate quats
	/// @brief[in] _x the rotation in degrees around the x axis
	/// @brief[in] _y the rotation in degrees around the y axis
	/// @brief[in] _z the rotation in degrees around the z axis
	//----------------------------------------------------------------------------------------------------------------------

	void fromEulerAngles(
											 const float _x,
											 const float _y,
											 const float _z
											);

	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  rotate our point by a quat (but can also be done using the * operator)
	/// @brief[in] _r the rotation Quat
	/// @brief[inout] io_p the point to be rotated (result we be set in this point)
	//----------------------------------------------------------------------------------------------------------------------
	void rotatePoint(
										const Quaternion& _r,
                    ngl::Vec4 & io_p
									 );
	//----------------------------------------------------------------------------------------------------------------------
  /// @brief  return the axis and angle of the current quat (angle in degrees)
	/// @brief[out] o_axis the axis of rotation (
	/// @brief[out] o_angle the angle of rotation about the quat angle in degrees
	//----------------------------------------------------------------------------------------------------------------------

	void toAxisAngle(
                     Vec4& o_axis,
										 float &o_angle
										);


protected :
    /// @brief  the quaternion data for the scalar real part
    Real m_s;
    /// @brief  the quaternion data for y
    Real m_x;
    /// @brief  the quaternion data for z
    Real m_y;
    /// @brief  the quaternion data for w
    Real m_z;

}; // end of class


}

#include "Mat4.h"

#endif
