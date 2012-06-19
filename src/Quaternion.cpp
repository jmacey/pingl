/*
  Copyright (C) 2009 Rob Bateman / Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITH ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this progra_m.  If not, see <http://www.gnu.org/licenses/>.
*/

//----------------------------------------------------------------------------------------------------------------------
/// @file Quaternion.cpp
/// @brief implementation files for Quaternion class
//----------------------------------------------------------------------------------------------------------------------

#include "Quaternion.h"
#include "Util.h"

namespace ngl
{



//----------------------------------------------------------------------------------------------------------------------
Quaternion Quaternion::operator *(
                                  const Quaternion& _q
                                 )const
{

	Quaternion ret(0.0,0.0,0.0,0.0);
	// if we have two Quaternions Qa Qb we get the following
	// Qa*Qb
	// first we do the scalar parts SaSb - A . B (where A and B are  the vector parts) . the dot product
	ret.m_s=(m_s*_q.m_s)-(m_x*_q.m_x+m_y*_q.m_y+m_z*_q.m_z);
	// now the x component of the vector part
	// this is the form of saB + sbA + sbA + A x B (X is the cross product)

	Vec4 v1( m_x, m_y, m_z );
	Vec4 v2( _q.m_x, _q.m_y, _q.m_z );

	Vec4 vectorPart = (m_s * v2) + (_q.m_s * v1) + (v1.cross(v2));

	ret.m_x=vectorPart.m_x;
	ret.m_y=vectorPart.m_y;
	ret.m_z=vectorPart.m_z;
	return ret;
}

//----------------------------------------------------------------------------------------------------------------------
void Quaternion::operator *=(
															const Quaternion& _q
												 		 )
{
		// as we have already written the code to do the mult above re-use
		*this=*this*_q;
}

//----------------------------------------------------------------------------------------------------------------------
Quaternion Quaternion::operator +(
																		const Quaternion& _q
																	 ) const
{
	Quaternion ret;
	ret.m_s=m_s+_q.m_s;
	ret.m_x=m_x+_q.m_x;
	ret.m_y=m_y+_q.m_y;
	ret.m_z=m_z+_q.m_z;
	return ret;
}

//----------------------------------------------------------------------------------------------------------------------
Quaternion Quaternion::operator -(
																	const Quaternion& _q
																 ) const
{
	Quaternion ret;
	ret.m_s=m_s-_q.m_s;
	ret.m_x=m_x-_q.m_x;
	ret.m_y=m_y-_q.m_y;
	ret.m_z=m_z-_q.m_z;
	return ret;
}


//----------------------------------------------------------------------------------------------------------------------
void Quaternion::operator +=(
															const Quaternion& _q
														 )
{
	// re-call the code from above
	*this=*this+_q;
}
//----------------------------------------------------------------------------------------------------------------------
void Quaternion::operator -=(
															const Quaternion& _q
														 )
{
	// re-call the code from above
	*this=*this-_q;
}

//----------------------------------------------------------------------------------------------------------------------
Quaternion Quaternion::operator *(
																	 ngl::Real _s
																	) const
{
	return Quaternion(m_s*_s,m_x*_s,m_y*_s,m_z*_s);

}

//----------------------------------------------------------------------------------------------------------------------
void Quaternion::operator *=(
															 ngl::Real _s
															)
{
	m_s*=_s;
	m_x*=_s;
	m_y*=_s;
	m_z*=_s;
}



//----------------------------------------------------------------------------------------------------------------------
void Quaternion::normalise()
{
	Real inverseOverOne = 1.0f/magnitude();
	m_s*=inverseOverOne;
	m_x*=inverseOverOne;
	m_y*=inverseOverOne;
	m_z*=inverseOverOne;
}


//----------------------------------------------------------------------------------------------------------------------
Real Quaternion::magnitude()const
{
	return static_cast<Real>( sqrt(m_s*m_s + m_x*m_x + m_y*m_y + m_z*m_z) );
}

//----------------------------------------------------------------------------------------------------------------------
bool Quaternion::operator == (
                              const Quaternion& _q
                             )const
{
	return (
		      FCompare(_q.m_s,m_s) &&
					FCompare(_q.m_x,m_x) &&
					FCompare(_q.m_y,m_y) &&
					FCompare(_q.m_z,m_z)
				 );
}


//----------------------------------------------------------------------------------------------------------------------
ngl::Vec4 Quaternion::operator* (
                                    const ngl::Vec4 &_vec
                                    ) const
{
	Quaternion temp=-*this;
	Quaternion point(0.0,_vec.m_x,_vec.m_y,_vec.m_z);
	point = temp*point* *this;
	return ngl::Vec4(point.m_x,point.m_y,point.m_z,1.0);
}




void Quaternion::rotateX(
													ngl::Real _angle
												 )
{
_angle/=2.0;
// q=[cos 1/2 theta, sin 1/2 theta V]
m_s=cos(ngl::radians(_angle));
m_x=sin(ngl::radians(_angle));
m_y=0;
m_z=0;
}

void Quaternion::rotateY(
													ngl::Real _angle
												)
{
	_angle/=2.0;
	// q=[cos 1/2 theta, sin 1/2 theta V]
	m_s=cos(ngl::radians(_angle));
	m_x=0;

	m_y=sin(ngl::radians(_angle));
	m_z=0;
}

void Quaternion::rotateZ(
													ngl::Real _angle
												 )
{

	_angle/=2.0;
	// q=[cos 1/2 theta, sin 1/2 theta V]
	m_s=cos(ngl::radians(_angle));
	m_x=0;
	m_y=0;
	m_z=sin(ngl::radians(_angle));

}


void Quaternion::fromAxisAngle(
                               const Vec4& _axis,
                               float _angle
															)
{
	Vec4 axis = _axis;
	axis.normalize();
	_angle=radians(_angle);
	Real sinAngle = static_cast<Real>(sin( _angle / 2.0f ));
	Real cosAngle = static_cast<Real>(cos( _angle / 2.0f ));
	m_s = cosAngle;
	m_x = axis.m_x * sinAngle;
	m_y = axis.m_y * sinAngle;
	m_z = axis.m_z * sinAngle;
}


void Quaternion::fromEulerAngles(
                                 const float _x,
                                 const float _y,
                                 const float _z
                                )
{
	Vec4 vx( 1, 0, 0 );
	Vec4 vy( 0, 1, 0 );
	Vec4 vz( 0, 0, 1 );

	Quaternion qx, qy, qz, qt;
	qx.fromAxisAngle( vx, _x );
	qy.fromAxisAngle( vy, _y );
	qz.fromAxisAngle( vz, _z );
	qt = qx * qy;
	*this = qt * qz;
}

void Quaternion::rotatePoint(
															const Quaternion& _r,
															ngl::Vec4 & io_p
														)
{
Quaternion temp = -_r;
Quaternion point(0.0,io_p.m_x, io_p.m_y, io_p.m_z);
point = temp * point * _r;
io_p.set(point.m_x, point.m_y, point.m_z,1.0);
}

void Quaternion::toAxisAngle(
                             Vec4& o_axis,
                             float &o_angle
                            )
{
	o_angle = degrees(static_cast<float>(acos( m_s ) * 2.0f));
	float sinA = static_cast<Real>(sqrt( 1.0f - m_s * m_s ));
	if( fabs( sinA ) < 0.0005f )
	{
		sinA = 1.0f;
	}
	o_axis.m_x = m_x / sinA;
	o_axis.m_y = m_y / sinA;
	o_axis.m_z = m_z / sinA;
}


} // end ngl namespace
//----------------------------------------------------------------------------------------------------------------------



