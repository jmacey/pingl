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
#include "Transformation.h"
#include "ShaderLib.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file Transformation.cpp
/// @brief implementation files for Transformation class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{

// Constructor -------------------------------------------------------------------------------------------------------------------
Transformation::Transformation()
{
  m_position = ngl::Vec4(0,0,0);
  m_scale = ngl::Vec4(1,1,1);
  m_rotation = ngl::Vec4(0,0,0);
  m_isMatrixComputed = false;
  m_matrix=1.0;
  m_transposeMatrix=1.0;
  m_inverseMatrix=1.0;
  computeMatrices();

}

Transformation::Transformation(const Transformation &_t)
{
  m_position = _t.m_position;
  m_scale = _t.m_scale;
  m_rotation = _t.m_rotation;
  m_isMatrixComputed = false;
  m_matrix=1.0;
  m_transposeMatrix=1.0;
  m_inverseMatrix=1.0;
  computeMatrices();
}



void Transformation::setMatrix(
                                const ngl::Mat4 &_m
                              )
{
  m_matrix=_m;
  m_transposeMatrix=_m;
  m_transposeMatrix.transpose();
  m_isMatrixComputed = true;
 // computeMatrices();
}

// Set scale ---------------------------------------------------------------------------------------------------------------------
void Transformation::setScale(
                                const ngl::Vec4& _scale
                              )
{
  m_scale = _scale;
  m_isMatrixComputed = false;
  computeMatrices();
}


void Transformation::setScale(
                              const ngl::Real &_x,
                              const ngl::Real &_y,
                              const ngl::Real &_z
                              )
{
  m_scale.set(_x,_y,_z);
  m_isMatrixComputed = false;
  computeMatrices();
}

// add scale ---------------------------------------------------------------------------------------------------------------------
void Transformation::addScale(
                                const ngl::Vec4& _scale
                              )
{
  m_scale += _scale;
  m_isMatrixComputed = false;
  computeMatrices();
}


void Transformation::addScale(
                              const ngl::Real &_x,
                              const ngl::Real &_y,
                              const ngl::Real &_z
                              )
{
  m_scale.m_x+=_x;
  m_scale.m_y+=_y;
  m_scale.m_z+=_z;

  m_isMatrixComputed = false;
  computeMatrices();
}

// Set position --------------------------------------------------------------------------------------------------------------------
void Transformation::setPosition(
                                  const ngl::Vec4& _position
                                 )
{
  m_position = _position;
  m_isMatrixComputed = false;
  computeMatrices();
}
void Transformation::setPosition(
                                  const ngl::Real &_x,
                                  const ngl::Real &_y,
                                  const ngl::Real &_z
                                )
{
  m_position.set(_x,_y,_z);
  m_isMatrixComputed = false;
  computeMatrices();
}

// Set position --------------------------------------------------------------------------------------------------------------------
void Transformation::addPosition(
                                  const ngl::Vec4& _position
                                 )
{
  m_position+= _position;
  m_isMatrixComputed = false;
  computeMatrices();
}
void Transformation::addPosition(
                                  const ngl::Real &_x,
                                  const ngl::Real &_y,
                                  const ngl::Real &_z
                                )
{
  m_position.m_x+=_x;
  m_position.m_y+=_y;
  m_position.m_z+=_z;

  m_isMatrixComputed = false;
  computeMatrices();
}


// set rotation -------------------------------------------------------------------------------------------------------------------
void Transformation::setRotation(
                                  const ngl::Vec4 &_rotation
                                )
{
  m_rotation = _rotation;
  m_isMatrixComputed = false;
  computeMatrices();
}
void Transformation::setRotation(
                                  const ngl::Real &_x,
                                  const ngl::Real &_y,
                                  const ngl::Real &_z
                                 )
{
  m_rotation.set(_x,_y,_z);

  m_isMatrixComputed = false;
  computeMatrices();
}


// set rotation -------------------------------------------------------------------------------------------------------------------
void Transformation::addRotation(
                                  const ngl::Vec4 &_rotation
                                 )
{
  m_rotation+= _rotation;
  m_isMatrixComputed = false;
  computeMatrices();
}
void Transformation::addRotation(
                                  const ngl::Real &_x,
                                  const ngl::Real &_y,
                                  const ngl::Real &_z
                                 )
{
  m_rotation.m_x+=_x;
  m_rotation.m_y+=_y;
  m_rotation.m_z+=_z;


  m_isMatrixComputed = false;
  computeMatrices();
}


// reset matrix ---------------------------------------------------------------------------------------------------------------------
void Transformation::reset()
{
  m_position = ngl::Vec4(0,0,0);
  m_scale = ngl::Vec4(1,1,1);
  m_rotation = ngl::Vec4(0,0,0);
  m_isMatrixComputed = false;
  m_matrix=1.0;
  m_transposeMatrix=1.0;
  m_inverseMatrix=1.0;
  computeMatrices();
}

// comptue matrix ---------------------------------------------------------------------------------------------------------------------
void Transformation::computeMatrices()
{
  if (!m_isMatrixComputed)       // need to recalculate
  {
    ngl::Mat4 mScale;
    ngl::Mat4 mRotationX;
    ngl::Mat4 mRotationY;
    ngl::Mat4 mRotationZ;
    ngl::Mat4 mTranslate;

    // rotation/scale matrix
    ngl::Mat4 mRotationScale;
    mScale.scale(m_scale.m_x, m_scale.m_y, m_scale.m_z);

    mRotationX.rotateX(m_rotation.m_x);
    mRotationY.rotateY(m_rotation.m_y);
    mRotationZ.rotateZ(m_rotation.m_z);
    mRotationScale = mScale * mRotationX * mRotationY * mRotationZ;

    // transform matrix
    m_matrix = mRotationScale;
/*    m_matrix.m_m[0][3] = m_position.m_x;
    m_matrix.m_m[1][3] = m_position.m_y;
    m_matrix.m_m[2][3] = m_position.m_z;
    m_matrix.m_m[3][3] = 1;
*/
    m_matrix.m_m[3][0] = m_position.m_x;
    m_matrix.m_m[3][1] = m_position.m_y;
    m_matrix.m_m[3][2] = m_position.m_z;
    m_matrix.m_m[3][3] = 1;



    // tranpose matrix
    m_transposeMatrix = mRotationScale;
    m_transposeMatrix.transpose();
/*    m_transposeMatrix.m_m[3][0] = m_position.m_x;
    m_transposeMatrix.m_m[3][1] = m_position.m_y;
    m_transposeMatrix.m_m[3][2] = m_position.m_z;
    m_transposeMatrix.m_m[3][3] = 1;*/
    m_transposeMatrix.m_m[0][3] = m_position.m_x;
    m_transposeMatrix.m_m[1][3] = m_position.m_y;
    m_transposeMatrix.m_m[2][3] = m_position.m_z;
    m_transposeMatrix.m_m[3][3] = 1;

    // inverse matrix
    mTranslate.translate(-m_position.m_x, -m_position.m_y, -m_position.m_z);
    mScale.scale(1.0f / m_scale.m_x, 1.0f / m_scale.m_y, 1.0f / m_scale.m_z);
    mRotationX.rotateX(-m_rotation.m_x);
    mRotationY.rotateY(-m_rotation.m_y);
    mRotationZ.rotateZ(-m_rotation.m_z);
    m_inverseMatrix = mTranslate * mRotationZ * mRotationY * mRotationX * mScale  ;

    m_isMatrixComputed = true;
  }
}

void Transformation::operator*= (
                                  const Transformation &_m
                                 )

{
  computeMatrices();
  m_matrix*=_m.m_matrix;

  /// transpose matrix transformation
  m_transposeMatrix*=_m.m_transposeMatrix;

  /// inverse matrix transformation
  m_inverseMatrix*=_m.m_inverseMatrix;
}

Transformation Transformation::operator*(
                                         const Transformation &_m
                                        ) const

{
  Transformation t;
  t.m_matrix=this->m_matrix*_m.m_matrix;
  t.m_transposeMatrix=this->m_transposeMatrix*_m.m_transposeMatrix;
  t.m_inverseMatrix=this->m_inverseMatrix*_m.m_inverseMatrix;

  return t;
}
void Transformation::loadMatrixToShader(
                                        const std::string &_param,
                                        const ACTIVEMATRIX &_which
                                       )
{
  computeMatrices();
  ShaderLib *shader=ngl::ShaderLib::instance();
  switch (_which)
  {
    case NORMAL :
    {
      shader->setShaderParamFromMatrix(_param,m_matrix);
    }
    break;
    case TRANSPOSE :
    {
      shader->setShaderParamFromMatrix(_param,m_transposeMatrix);
    }
    break;
    case INVERSE :
    {
      shader->setShaderParamFromMatrix(_param,m_inverseMatrix);
    }
    break;

  }


}

void Transformation::loadGlobalAndCurrentMatrixToShader(
                                                        const std::string &_param,
                                                        ngl::Transformation &_global,
                                                        const ACTIVEMATRIX &_which
                                                       )
{
  computeMatrices();
  ShaderLib *shader=ngl::ShaderLib::instance();
  switch (_which)
  {
    case NORMAL :
    {
      ngl::Mat4 tx=_global.getMatrix()*this->getMatrix();
      shader->setShaderParamFromMatrix(_param,tx);
    }
    break;
    case TRANSPOSE :
    {
      ngl::Mat4 tx=_global.getTransposeMatrix()*this->getTransposeMatrix();

      shader->setShaderParamFromMatrix(_param,tx);
    }
    break;
    case INVERSE :
    {
      ngl::Mat4 tx=_global.getInverseMatrix()*this->getInverseMatrix();
      shader->setShaderParamFromMatrix(_param,tx);
    }
    break;

  }

}



} // end ngl
