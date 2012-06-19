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
#ifndef VEC2_H__
#define VEC2_H__
//----------------------------------------------------------------------------------------------------------------------
/// @file Vec2.h
/// @brief a simple 2 tuple container for compatibility with glsl
//----------------------------------------------------------------------------------------------------------------------


// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include <cmath>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
/// @file Vec2.h
/// @brief encapsulates a 2 float object like glsl Vec2 but not maths
/// use the Vec2 class for maths and the asVec2 to return a Vec2
/// @author Jonathan Macey
/// @version 1.0
/// @date 20/6/11 initial version
/// Revision History :
/// Initial Version 20/6/11
//----------------------------------------------------------------------------------------------------------------------


namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
/// @class Vec2 "include/Vec2.h"
/// @brief simple Vec2 encapsulates a 3 float object like glsl Vec2 but not maths
/// use the Vec2 class for maths and the asVec2 to return a Vec2
//----------------------------------------------------------------------------------------------------------------------

class Vec4;
class Vec2
{

public:

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the Vec2 component from 3 values
  /// @param[in]  _x the x component
  /// @param[in]  _y the y component
  //----------------------------------------------------------------------------------------------------------------------
  void set(
           const Real& _x,
           const Real& _y
          );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  Vec2
  /// @param[in]  _v the Vec2 to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set(
           const Vec2& _v
          );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  Vector
  /// @param[in]  _v the Vec2 to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set(
           const Vec4& _v
          );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  Vec2
  /// @param[in]  _v the Vec2 to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set(
           const Vec2* _v
          );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor
  /// @param[in] _v the value to set
  //----------------------------------------------------------------------------------------------------------------------
  Vec2(
          const Vec2& _v
         ) :
            m_x(_v.m_x),
            m_y(_v.m_y){;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor from a pointer to a Vertex
  /// @param[in] _v the value to set
  //----------------------------------------------------------------------------------------------------------------------
  Vec2(
          const Vec2* _v
         ) :
           m_x(_v->m_x),
           m_y(_v->m_y){;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief initialise the constructor from 3 or 4 Real
  /// @param[in]  _x x value
  /// @param[in]  _y y value
  /// @param[in]  _w 1.0f default so acts as a points
  //----------------------------------------------------------------------------------------------------------------------
   Vec2(
         const Real& _x=0.0,
         const Real& _y=0.0
         ):
           m_x(_x),
           m_y(_y){;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor using a single float all components are set to the value _x
  /// @param[in] _x the value to set all components
  //----------------------------------------------------------------------------------------------------------------------
  Vec2(
         const float& _x
        ) :
          m_x(_x),
          m_y(_x){;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor using a single int all components are set to _x
  /// @param[in] _x the value to set all components
  //----------------------------------------------------------------------------------------------------------------------
   Vec2(
				 const int& _x
				) :
						 m_x(_x),
						 m_y(_x){;}

   //----------------------------------------------------------------------------------------------------------------------
   /// @brief ctor using a double all components are set to the value _x
   /// @param[in] _x the value to set all components
   //----------------------------------------------------------------------------------------------------------------------
   Vec2(
          const double& _x
         ) :
           m_x(_x),
           m_y(_x){;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief clears the Vec2 to 0,0,0
  //----------------------------------------------------------------------------------------------------------------------
  void null();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief [] index operator to access the index component of the Vec2
  /// @returns  this[x] as a Real
  //----------------------------------------------------------------------------------------------------------------------
  Real& operator[](
                   const int& _i
                  ) ;
	const Real& operator[](
												 const int& _i
												 ) const { return m_openGL[_i]; }


  //----------------------------------------------------------------------------------------------------------------------
  /// @brief += operator add Vec2 v to current Vec2
  /// @param[in]  &_v Vec2 to add
  //----------------------------------------------------------------------------------------------------------------------
  void operator+=(
                  const Vec2& _v
                 );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief -= operator this-=v
  /// @param[in]  &_v Vec2 to subtract
  //----------------------------------------------------------------------------------------------------------------------
  void operator-=(
                  const Vec2& _v
                 );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this * i for each element
  /// @param[in]  _i the scalar to mult by
  /// @returns Vec2
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator *(
                    const Real &_i
                   )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief + operator add Vec2+Vec2
  /// @param[in]  &_v the value to add
  /// @returns the Vec2 + v
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator +(
                   const Vec2 &_v
                  )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief divide Vec2 components by a scalar
  /// @param[in] _v the scalar to divide by
  /// @returns a Vec2 V(x/v,y/v,z/v,w)
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator/(
                   const Real& _v
                  )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief divide this Vec2 components by a scalar
  /// @param[in] _v the scalar to divide by
  /// sets the Vec2 to Vec2 V(x/v,y/v)
  //----------------------------------------------------------------------------------------------------------------------
  void operator/=(
                  const Real& _v
                 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief multiply this Vec2 components by a scalar
  /// @param[in] _v the scalar to multiply by
  /// sets the Vec2 to Vec2 V(x*v,y*v)
  //----------------------------------------------------------------------------------------------------------------------
  void operator*=(
                  const Real& _v
                 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief subtraction operator subtract vevtor-Vec2
  /// @param[in]  &_v the value to sub
  /// @returns this - v
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator-(
                   const Vec2& _v
                  )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief * operator mult vevtor*Vec2
  /// @param[in]  _v the value to mult
  /// @returns new Vec2 this*v
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator*(
                   const Vec2 &_v
                  )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment operator set the current Vec2 to rhs
  /// @param[in] _v the Vec2 to set
  /// @returns a new Vec2
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 &operator =(
                     const Vec2 &_v
                    );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief negate the Vec2 components
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator-() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief check for equality uses FCompare (from Util.h) as float values
  /// @param[in] _v the Vec2 to check against
  /// @returns true or false
  //----------------------------------------------------------------------------------------------------------------------
  bool operator==(
                  const Vec2 &_v
                 )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief not equal check
  /// @param[in] _v the Vec2 to check against
  /// @returns true of false
  //----------------------------------------------------------------------------------------------------------------------
  bool operator!=(
                  const Vec2 &_v
                 )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief \ operator div Vec2/Vec2
  /// @param[in]  _v the value to div by
  /// @returns Vec2 / Vec2
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator/(
                   const Vec2& _v
                  )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor to the m_openGL matrix returns the address of the 0th element
  //----------------------------------------------------------------------------------------------------------------------
  inline Real* openGL(){return &m_openGL[0];}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief insertion operator to print out the Vec2
  /// @param[in] _output the stream to write to
  /// @param[in] _s the Vec2 to write
  //----------------------------------------------------------------------------------------------------------------------
  friend  std::ostream& operator<<(std::ostream& _output, const ngl::Vec2& _s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief extraction operator to read in  the Vec2
  /// @param[in] _input the stream read from
  /// @param[in] _s the Vec2 to write
  //----------------------------------------------------------------------------------------------------------------------
  friend  std::istream& operator>>(std::istream& _input, ngl::Vec2 &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief insertion operator to print out the Vec2
  /// @param[in] _output the stream to write to
  /// @param[in] _s the Vec2 to write
  //----------------------------------------------------------------------------------------------------------------------
  friend  std::ostream& operator<<(std::ostream& _output, const ngl::Vec2* _s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief extraction operator to read in  the Vec2
  /// @param[in] _input the stream read from
  /// @param[in] _s the Vec2 to write
  //----------------------------------------------------------------------------------------------------------------------
  friend  std::istream& operator>>(std::istream& _input, ngl::Vec2* _s);
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
      /// @brief x component of the Vec2
      //----------------------------------------------------------------------------------------------------------------------
      Real m_x;
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief y component of the Vec2
      //----------------------------------------------------------------------------------------------------------------------
      Real m_y;

#ifndef BUILDING_DOCS
    };
#endif
#pragma pack(pop)
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief array of four floats mapped to the x,y,z,w components of the Vec2 useful for openGL fv data types
  /// this is mapped as a union to the following \n
  /// m_x == m_openGL[0] \n
  /// m_y == m_openGL[1] \n
  //----------------------------------------------------------------------------------------------------------------------

  Real m_openGL[2];
#ifndef BUILDING_DOCS
  };
#endif

};


} // end namespace ngl
#endif

//----------------------------------------------------------------------------------------------------------------------
