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
#ifndef TRANSFORM_H__
#define TRANSFORM_H__
//----------------------------------------------------------------------------------------------------------------------
/// @file Transformation.h
/// @brief a simple transformation object containing rot / tx / scale and final matrix
//----------------------------------------------------------------------------------------------------------------------
// Library includes
#include "Vec4.h"
#include "Mat4.h"
#include "NGLassert.h"
#include "Transformation.h"

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @enum decide which matrix is the current active matrix
//----------------------------------------------------------------------------------------------------------------------
enum  ACTIVEMATRIX{NORMAL,TRANSPOSE,INVERSE};
//----------------------------------------------------------------------------------------------------------------------
/// @class Transformation "include/ngl/Transformation.h"
/// @brief Transformation describes a transformation (translate, scale, rotation)
/// modifed by j macey and included into NGL
/// @author Vincent Bonnet
/// @version 1.5
/// @date 14/03/10 Last Revision 14/03/10
//----------------------------------------------------------------------------------------------------------------------
class  Transformation
{
friend class Vec4;
public:

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor
  //----------------------------------------------------------------------------------------------------------------------
  Transformation();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Copy Constructor
  //----------------------------------------------------------------------------------------------------------------------
  Transformation(const ngl::Transformation &_t);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the scale value in the transform
  /// @param[in] _scale the scale value to set for the transform
  //----------------------------------------------------------------------------------------------------------------------
  void setScale(
                const ngl::Vec4& _scale
               );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the scale value in the transform
  /// @param[in] _x x scale value
  /// @param[in] _y y scale value
  /// @param[in] _z z scale value
  //----------------------------------------------------------------------------------------------------------------------
  void setScale(
                    const Real &_x,
                    const Real &_y,
                    const Real &_z
                  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to add to the existing the scale value in the transform
  /// @param[in] _scale the scale value to set for the transform
  //----------------------------------------------------------------------------------------------------------------------
  void addScale(
                const ngl::Vec4& _scale
               );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to add to the existing the scale value in the transform
  /// @param[in] _x x scale value
  /// @param[in] _y y scale value
  /// @param[in] _z z scale value
  //----------------------------------------------------------------------------------------------------------------------
  void addScale(
                    const Real &_x,
                    const Real &_y,
                    const Real &_z
                  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the position
  /// @param[in] _position position
  //----------------------------------------------------------------------------------------------------------------------
  void setPosition(
                    const ngl::Vec4& _position
                  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the position value in the transform
  /// @param[in] _x x position value
  /// @param[in] _y y position value
  /// @param[in] _z z position value
  //----------------------------------------------------------------------------------------------------------------------
  void setPosition(
                    const Real &_x,
                    const Real &_y,
                    const Real &_z
                  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method add to the existing set the position
  /// @param[in] _position position
  //----------------------------------------------------------------------------------------------------------------------
  void addPosition(
                    const ngl::Vec4& _position
                  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to add to the existing position value in the transform
  /// @param[in] _x x position value
  /// @param[in] _y y position value
  /// @param[in] _z z position value
  //----------------------------------------------------------------------------------------------------------------------
  void addPosition(
                    const Real &_x,
                    const Real &_y,
                    const Real &_z
                  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @breif method to set the matrix directly
  /// @param[in] _m the matrix to set the m_transform to
  /// need to also re-compute the others
  //----------------------------------------------------------------------------------------------------------------------
  void setMatrix(
                  const ngl::Mat4 &_m
                );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the rotation
  /// @param[in] _rotation rotation
  /// @note each value is an axis rotation as the values are calculated
  /// mRotationX * mRotationY * mRotationZ;
  //----------------------------------------------------------------------------------------------------------------------
  void setRotation(
                    const ngl::Vec4& _rotation
                  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the rotation value in the transform
  /// @note each value is an axis rotation as the values are calculated
  /// mRotationX * mRotationY * mRotationZ;
  /// @param[in] _x x rotation value
  /// @param[in] _y y rotation value
  /// @param[in] _z z rotation value
  //----------------------------------------------------------------------------------------------------------------------
  void setRotation(
                    const Real &_x,
                    const Real &_y,
                    const Real &_z
                  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to add to the existing  rotation
  /// @param[in] _rotation rotation
  /// @note each value is an axis rotation as the values are calculated
  /// mRotationX * mRotationY * mRotationZ;
  //----------------------------------------------------------------------------------------------------------------------
  void addRotation(
                    const ngl::Vec4& _rotation
                  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to add to the existing rotation value in the transform
  /// @note each value is an axis rotation as the values are calculated
  /// mRotationX * mRotationY * mRotationZ;
  /// @param[in] _x x rotation value
  /// @param[in] _y y rotation value
  /// @param[in] _z z rotation value
  //----------------------------------------------------------------------------------------------------------------------
  void addRotation(
                    const Real &_x,
                    const Real &_y,
                    const Real &_z
                  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a method to set all the transforms to the identity
  //----------------------------------------------------------------------------------------------------------------------
  void reset();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to get the scale
  /// @returns the scale
  //----------------------------------------------------------------------------------------------------------------------
  const ngl::Vec4& getScale()  const      { return m_scale;  }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to get the position
  /// @returns the position
  //----------------------------------------------------------------------------------------------------------------------
  const ngl::Vec4& getPosition() const    { return m_position;  }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to get the rotation
  /// @returns the rotation
  //----------------------------------------------------------------------------------------------------------------------
  const ngl::Vec4& getRotation() const    { return m_rotation;  }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to get the matrix. It computes the matrix if it's dirty
  /// @returns the matrix
  //----------------------------------------------------------------------------------------------------------------------
  const ngl::Mat4& getMatrix() { computeMatrices();  return m_matrix;  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to get the transpose matrix. It computes the transpose matrix if it's dirty
  /// @returns the transpose matrix
  //----------------------------------------------------------------------------------------------------------------------
  const ngl::Mat4& getTransposeMatrix() {  computeMatrices(); return m_transposeMatrix; }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to get the inverse matrix. It computes the inverse matrix if it's dirty
  /// @returns the inverse matrix
  //----------------------------------------------------------------------------------------------------------------------
  const ngl::Mat4& getInverseMatrix()  {   computeMatrices(); return m_inverseMatrix; }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief *= operator
  /// @param _m the transformation to combine
  //----------------------------------------------------------------------------------------------------------------------
  void operator*=(
                   const Transformation &_m
                 );
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief operator for Transform multiplication will do a matrix
  /// multiplication on each of the matrices
  /// @param[in] _m the Transform to multiply the current one by
  /// @returns all the transform matrix members * my _m members
  //----------------------------------------------------------------------------------------------------------------------
  Transformation operator*(
                           const Transformation &_m
                          ) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief load the current transform matrix to the shader
  /// @param[in] _param the name of the parameter to set (varying mat4)
  /// @param[in] _which which matrix mode to use
  //----------------------------------------------------------------------------------------------------------------------
  void loadMatrixToShader(
                           const std::string &_param,
                           const ACTIVEMATRIX &_which=NORMAL
                         );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief load the current * global transform matrix to the shader
  /// @param[in] _param the name of the parameter to set (varying mat4)
  /// @param[in] _which which matrix mode to use
  //----------------------------------------------------------------------------------------------------------------------
  void loadGlobalAndCurrentMatrixToShader(
                                           const std::string &_param,
                                           ngl::Transformation &_global,
                                           const ACTIVEMATRIX &_which=NORMAL
                                         );


protected :

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief position
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec4 m_position;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  scale
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec4 m_scale;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  rotation
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec4 m_rotation;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  boolean defines if the matrix is dirty or not
  //----------------------------------------------------------------------------------------------------------------------
  bool m_isMatrixComputed;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  matrix transformation
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Mat4 m_matrix;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  transpose matrix transformation
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Mat4 m_transposeMatrix;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  inverse matrix transformation
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Mat4 m_inverseMatrix;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to compute the matrix, transpose and inverse matrix. set the m_bIsMatrixComputed variable to true.
  //----------------------------------------------------------------------------------------------------------------------
  void computeMatrices();

};

} // end ngl namespace
#endif
//----------------------------------------------------------------------------------------------------------------------
