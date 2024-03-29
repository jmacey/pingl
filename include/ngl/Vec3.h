/*
  Copyright (C) 2011 Jon Macey

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
#ifndef VEC3_H__
#define VEC3_H__
//----------------------------------------------------------------------------------------------------------------------
/// @file Vec3.h
/// @brief a simple 3 tuple container for compatibility with glsl
//----------------------------------------------------------------------------------------------------------------------


// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include <cmath>
#include <iostream>

//----------------------------------------------------------------------------------------------------------------------
/// @file Vec3.h
/// @brief encapsulates a 3 float object like glsl vec3 but not maths
/// use the Vec3 class for maths and the asVec3 to return a vec3
/// @author Jonathan Macey
/// @version 1.0
/// @date 20/6/11 initial version
/// Revision History :
/// Initial Version 20/6/11
//----------------------------------------------------------------------------------------------------------------------


namespace ngl
{
// pre-declare the vector class
class Vec4;

//----------------------------------------------------------------------------------------------------------------------
/// @class Vec3 "include/Vec3.h"
/// @brief simple Vec3 encapsulates a 3 float object like glsl vec3 but not maths
/// use the Vec3 class for maths and the asVec3 to return a vec3
//----------------------------------------------------------------------------------------------------------------------


class  Vec3
{

public:

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the Vec3 component from 3 values
  /// @param[in]  _x the x component
  /// @param[in]  _y the y component
  /// @param[in]  _z the z component
  //----------------------------------------------------------------------------------------------------------------------
  void set(
            Real _x,
            Real _y,
            Real _z
          );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return this dotted with _b
  /// @param[in]  _b vector to dot current vector with
  /// @returns  the dot product
  //----------------------------------------------------------------------------------------------------------------------
  Real dot(
           const Vec3 &_b
          )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  Vec3
  /// @param[in]  _v the Vec3 to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set(
           const Vec3& _v
          );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  Vector
  /// @param[in]  _v the Vec3 to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set(
           const Vec4& _v
          );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  Vec3
  /// @param[in]  _v the Vec3 to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set(
           const Vec3* _v
          );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor
  /// @param[in] _v the value to set
  //----------------------------------------------------------------------------------------------------------------------
  Vec3(
          const Vec3& _v
         ) :
            m_x(_v.m_x),
            m_y(_v.m_y),
            m_z(_v.m_z){;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor from a pointer to a Vertex
  /// @param[in] _v the value to set
  //----------------------------------------------------------------------------------------------------------------------
  Vec3(
          const Vec3* _v
         ) :
           m_x(_v->m_x),
           m_y(_v->m_y),
           m_z(_v->m_z){;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief initialise the constructor from 3 or 4 Real
  /// @param[in]  _x x value
  /// @param[in]  _y y value
  /// @param[in]  _z z value
  /// @param[in]  _w 1.0f default so acts as a points
  //----------------------------------------------------------------------------------------------------------------------
   Vec3(
          Real _x=0.0,
          Real _y=0.0,
          Real _z=0.0
         ):
           m_x(_x),
           m_y(_y),
           m_z(_z){;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor using a single float all components are set to the value _x
  /// @param[in] _x the value to set all components
  //----------------------------------------------------------------------------------------------------------------------
  Vec3(
          float _x
        ) :
          m_x(_x),
          m_y(_x),
          m_z(_x){;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor using a single int all components are set to _x
  /// @param[in] _x the value to set all components
  //----------------------------------------------------------------------------------------------------------------------
   Vec3(
         int _x
				) :
						 m_x(_x),
						 m_y(_x),
						 m_z(_x){;}

   //----------------------------------------------------------------------------------------------------------------------
   /// @brief ctor using a double all components are set to the value _x
   /// @param[in] _x the value to set all components
   //----------------------------------------------------------------------------------------------------------------------
   Vec3(
          const double& _x
         ) :
           m_x(_x),
           m_y(_x),
           m_z(_x){;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief clears the Vec3 to 0,0,0
  //----------------------------------------------------------------------------------------------------------------------
  void null();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief [] index operator to access the index component of the Vec3
  /// @returns  this[x] as a Real
  //----------------------------------------------------------------------------------------------------------------------
  Real& operator[](
                   const int& _i
                  ) ;
	const Real& operator[](
	                   const int& _i
	                   ) const { return m_openGL[_i]; }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Normalize the vector using
  /// \n \f$x=x/\sqrt{x^2+y^2+z^2} \f$
  /// \n \f$y=y/\sqrt{x^2+y^2+z^2} \f$
  /// \n \f$z=z/\sqrt{x^2+y^2+z^2} \f$
  //----------------------------------------------------------------------------------------------------------------------
  void normalize();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief calculate the inner product of this vector and vector passed in
  /// @param[in] _v the vector to calculate inner product with
  /// @returns the inner product
  //----------------------------------------------------------------------------------------------------------------------
  double inner(
               const Vec3& _v
              )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief compute the outer product of this vector and vector
  /// @param[in] _v the vector to calc against
  /// @returns a new vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 outer(
              const Vec3& _v
             )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the length of the vector
  /// @returns  \f$\sqrt{x^2+y^2+z^2} \f$
  //----------------------------------------------------------------------------------------------------------------------
  Real length() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief += operator add Vec3 v to current Vec3
  /// @param[in]  &_v Vec3 to add
  //----------------------------------------------------------------------------------------------------------------------
  void operator+=(
                  const Vec3& _v
                 );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief -= operator this-=v
  /// @param[in]  &_v Vec3 to subtract
  //----------------------------------------------------------------------------------------------------------------------
  void operator-=(
                  const Vec3& _v
                 );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this * i for each element
  /// @param[in]  _i the scalar to mult by
  /// @returns Vec3
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator *(
                     Real _i
                   )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief + operator add Vec3+Vec3
  /// @param[in]  &_v the value to add
  /// @returns the Vec3 + v
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator +(
                   const Vec3 &_v
                  )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief divide Vec3 components by a scalar
  /// @param[in] _v the scalar to divide by
  /// @returns a Vec3 V(x/v,y/v,z/v,w)
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator/(
                   const Real& _v
                  )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief divide this Vec3 components by a scalar
  /// @param[in] _v the scalar to divide by
  /// sets the Vec3 to Vec3 V(x/v,y/v,z/v,w)
  //----------------------------------------------------------------------------------------------------------------------
  void operator/=(
                  const Real& _v
                 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief multiply this Vec3 components by a scalar
  /// @param[in] _v the scalar to multiply by
  /// sets the Vec3 to Vec3 V(x*v,y*v,z*v,w)
  //----------------------------------------------------------------------------------------------------------------------
  void operator*=(
                  const Real& _v
                 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief subtraction operator subtract vevtor-Vec3
  /// @param[in]  &_v the value to sub
  /// @returns this - v
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator-(
                   const Vec3& _v
                  )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief * operator mult vevtor*Vec3
  /// @param[in]  _v the value to mult
  /// @returns new Vec3 this*v
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator*(
                   const Vec3 &_v
                  )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment operator set the current Vec3 to rhs
  /// @param[in] _v the Vec3 to set
  /// @returns a new Vec3
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 &operator =(
                     const Vec3 &_v
                    );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief negate the Vec3 components
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator-() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief check for equality uses FCompare (from Util.h) as float values
  /// @param[in] _v the Vec3 to check against
  /// @returns true or false
  //----------------------------------------------------------------------------------------------------------------------
  bool operator==(
                  const Vec3 &_v
                 )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief not equal check
  /// @param[in] _v the Vec3 to check against
  /// @returns true of false
  //----------------------------------------------------------------------------------------------------------------------
  bool operator!=(
                  const Vec3 &_v
                 )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief \ operator div Vec3/Vec3
  /// @param[in]  _v the value to div by
  /// @returns Vec3 / Vec3
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator/(
                   const Vec3& _v
                  )const;


  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the Vec3 as the cross product from 2 other Vec3
  /// @param[in]  _v1 the first vector
  /// @param[in]  _v2 the second vector
  //----------------------------------------------------------------------------------------------------------------------
  void cross(
              const Vec3& _v1,
              const Vec3& _v2
             );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return the cross product of this cross with b
  /// @param[in]  _b the vector cross this with
  /// @returns  the result of this cross b
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 cross(
               const Vec3& _b
              )const;


  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor to the m_openGL matrix returns the address of the 0th element
  //----------------------------------------------------------------------------------------------------------------------
  inline Real* openGL(){return &m_openGL[0];}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief insertion operator to print out the Vec3
  /// @param[in] _output the stream to write to
  /// @param[in] _s the Vec3 to write
  //----------------------------------------------------------------------------------------------------------------------
  friend  std::ostream& operator<<(std::ostream& _output, const ngl::Vec3& _s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief extraction operator to read in  the Vec3
  /// @param[in] _input the stream read from
  /// @param[in] _s the Vec3 to write
  //----------------------------------------------------------------------------------------------------------------------
  friend  std::istream& operator>>(std::istream& _input, ngl::Vec3 &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief insertion operator to print out the Vec3
  /// @param[in] _output the stream to write to
  /// @param[in] _s the Vec3 to write
  //----------------------------------------------------------------------------------------------------------------------
  friend  std::ostream& operator<<(std::ostream& _output, const ngl::Vec3* _s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief extraction operator to read in  the Vec3
  /// @param[in] _input the stream read from
  /// @param[in] _s the Vec3 to write
  //----------------------------------------------------------------------------------------------------------------------
  friend  std::istream& operator>>(std::istream& _input, ngl::Vec3* _s);
/// @note I've made this public as some compilers automatically make the
/// anonymous unions public whereas clang++ complains see this post
/// http://jonmacey.blogspot.com/2011/03/anonymous-union-struct-weirdness.html
public :
#pragma pack(push,1)

#ifndef BUILDING_DOCS
  union
  {
    struct
    {
#endif
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief x component of the Vec3
      //----------------------------------------------------------------------------------------------------------------------
      Real m_x;
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief y component of the Vec3
      //----------------------------------------------------------------------------------------------------------------------
      Real m_y;
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief z component of the Vec3
      //----------------------------------------------------------------------------------------------------------------------
      Real m_z;

#ifndef BUILDING_DOCS
    };
#endif
#pragma pack(pop)
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief array of four floats mapped to the x,y,z,w components of the Vec3 useful for openGL fv data types
  /// this is mapped as a union to the following \n
  /// m_x == m_openGL[0] \n
  /// m_y == m_openGL[1] \n
  /// m_z == m_openGL[2] \n
  //----------------------------------------------------------------------------------------------------------------------

  Real m_openGL[3];
#ifndef BUILDING_DOCS
  };
#endif



};
//----------------------------------------------------------------------------------------------------------------------
/// @brief scalar * vector operator
/// @param _k the float value
/// @param _v the vector value
/// @returns a vector _k*v
//----------------------------------------------------------------------------------------------------------------------
inline Vec3 operator *(float _k, const Vec3 &_v)
{
  return Vec3(_k*_v.m_x, _k*_v.m_y, _k*_v.m_z);
}


} // end namespace ngl
#endif

//----------------------------------------------------------------------------------------------------------------------
