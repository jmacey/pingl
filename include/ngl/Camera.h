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
#ifndef CAMERA_H__
#define CAMERA_H__
/// @file Camera.h
/// @brief a simple camera class based on the Hill Book
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include "Vec4.h"
#include "Mat4.h"
#include <cmath>
#include "Plane.h"

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @enum CAMERAPROJECTION used to specify which camera projection to use
enum   CAMERAPROJECTION  {ORTHOGRAPHIC,PERSPECTIVE,TWOPOINT,THREEPOINT};
/// @enum used to describe intercects with fustrum
enum   CAMERAINTERCEPT  {OUTSIDE, INTERSECT, INSIDE};

//----------------------------------------------------------------------------------------------------------------------
/// @class Camera
/// @brief simple camera class to allow movement in an opengl scene.
///  a lot of this stuff is from the HILL book Computer Graphics with OpenGL 2nd Ed Prentice Hall
///  a very good book
/// fustrum culling modified from http://www.lighthouse3d.com/opengl/viewfrustum/index.php?defvf
///  @author Jonathan Macey
///  @version 5.0
///  @date
/// Last Update added fustrum calculation
/// Revision History : \n
/// 27/08/08 Added experimental projection modes
/// 28/09/09 Updated to NCCA Coding standard \n
///  @todo Finish off the different projections modes at present persp and ortho work
//----------------------------------------------------------------------------------------------------------------------

class  Camera
{

public :

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default constructor
  //----------------------------------------------------------------------------------------------------------------------
  Camera();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief constructor setting the  camera using eye look and up
  /// @param[in] _eye the eye position of the Camera
  /// @param[in] _look where the camera is  looking
  /// @param[in] _up the notion of upwardness for the  camers (get re-calculated from the other vectors)
  /// @param[in] _proj what projection mode to use based on CAMERAPROJECTION enum
  //----------------------------------------------------------------------------------------------------------------------
  Camera(
         const Vec4& _eye,
         const Vec4& _look,
         const Vec4& _up,
         const CAMERAPROJECTION _proj
        );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to set the extents of the orthographic projection volume
  /// @param[in] _l left extent
  /// @param[in] _r right extent
  /// @param[in] _t top extent
  /// @param[in] _b bottom extent
  /// @param[in] _n near extent
  /// @param[in] _f far extent
  //----------------------------------------------------------------------------------------------------------------------
  void setOrthoParams(
                      const Real _l,
                      const Real _r,
                      const Real _t,
                      const Real _b,
                      const Real _n,
                      const Real _f
                    );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief roll the cameara around the  Z axis
  /// @param[in] _angle the angle to roll in degrees
  //----------------------------------------------------------------------------------------------------------------------
  void roll(
             Real _angle
            );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief roll the cameara around the  x axis
  /// @param[in] _angle the angle to roll in degrees
  //----------------------------------------------------------------------------------------------------------------------
  void pitch(
              Real _angle
            );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief roll the cameara around the  y axis
  /// @param[in] _angle the angle to roll in degrees
  //----------------------------------------------------------------------------------------------------------------------
  void yaw(
             Real _angle
          );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief slide the camera around  the U V and N axis
  /// @param[in] _du ammount to slide in the U
  /// @param[in] _dv ammount to slide in the V
  /// @param[in] _dn ammount to slide in the N
  //----------------------------------------------------------------------------------------------------------------------
  void slide(
              Real _du,
              Real _dv,
              Real _dn
            );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the Camera position using eye look and up vectors
  /// @param[in] _eye the new  eye position
  /// @param[in] _look the new look position
  /// @param[in] _up the notional up direction of the Camera
  //----------------------------------------------------------------------------------------------------------------------
  void set(
           const Vec4 &_eye,
           const Vec4 &_look,
           const Vec4 &_up
          );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the shape of the Camera
  /// @param[in] _viewAngle the view angle  of the camera from the eye
  /// @param[in] _aspect the aspect ratio of the camera can be  calculated from Width/height
  /// @param[in] _near the near clipping plane
  /// @param[in] _far the far clipping plane
  /// @param[in] _proj the type of projection to use
  //----------------------------------------------------------------------------------------------------------------------
  void setShape(
                Real _viewAngle,
                Real _aspect,
                Real _near,
                Real _far,
                CAMERAPROJECTION _proj
                );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief re-set the aspect ratio of the camera
  /// @param[in] _asp the new aspect ratio
  //----------------------------------------------------------------------------------------------------------------------
  void setAspect(
                  Real _asp
                );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets some nice default camera values
  //----------------------------------------------------------------------------------------------------------------------
  void setDefaultCamera();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief move the camera in world space (i.e. add a translation to each of the axis
  /// @param[in] _dx the translation in the x
  /// @param[in] _dy the translation in the y
  /// @param[in] _dz the translation in the z
  //----------------------------------------------------------------------------------------------------------------------
  void move(
             Real _dx,
             Real _dy,
             Real _dz
           );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief move both the eye and the look at the same time
  /// @param[in] _dx ammount to move in the x
  /// @param[in] _dy ammount to move in the y
  /// @param[in] _dz ammount to move in the z
  //----------------------------------------------------------------------------------------------------------------------
  void moveBoth(
                 Real _dx,
                 Real _dy,
                 Real _dz
               );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief move the eye position
  /// @param[in] _dx ammount to move the eye in the x
  /// @param[in] _dy ammount to move the eye in the y
  /// @param[in] _dz ammount to move the eye in the z
  //----------------------------------------------------------------------------------------------------------------------
  void moveEye(
                Real _dx,
                Real _dy,
                Real _dz
              );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief move the look position
  /// @param[in] _dx ammount to move the look in the x
  /// @param[in] _dy ammount to move the look in the y
  /// @param[in] _dz ammount to move the look in the z
  //----------------------------------------------------------------------------------------------------------------------
  void moveLook(
                 Real _dx,
                 Real _dy,
                 Real _dz
               );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the viewangle for the Camera
  /// @param[in] _angle new angle
  //----------------------------------------------------------------------------------------------------------------------
  void setViewAngle(
                    Real _angle
                   );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Use is called to make this the current camera and set the MODELVIEW and PROJECTION matrices in OpenGL
  //----------------------------------------------------------------------------------------------------------------------
  void update();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to do a Yaw based on Euler rotation with normalised values
  /// @param[in] _angle the angle to rotate in degrees
  //----------------------------------------------------------------------------------------------------------------------
  void normalisedYaw(
                      Real _angle
                    );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to do a Pitch based on Euler rotation with normalised values
  /// @param[in] _angle the angle to rotate in degrees
  //----------------------------------------------------------------------------------------------------------------------
  void normalisedPitch(
                         Real _angle
                      );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to do a Roll based on Euler rotation with normalised values
  /// @param[in] _angle the angle to rotate in degrees
  //----------------------------------------------------------------------------------------------------------------------
  void normalisedRoll(
                       Real _angle
                      );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Set the projection matrix to a 2 point projection experimental at present
  /// @param[in] _p1 the first point for the projection
  /// @param[in] _p2 the 2nd point for the projection
  //----------------------------------------------------------------------------------------------------------------------
  void set2PointProjPoints(
                           const Vec4 &_p1,
                           const Vec4 &_p2
                          );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Set the projection matrix to a 3 point projection experimental at present
  /// @param[in] _p1 the first point for the projection
  /// @param[in] _p2 the 2nd point for the projection
  /// @param[in] _p3 the 3rd point for the projection
  //----------------------------------------------------------------------------------------------------------------------
  void set3PointProjPoints(
                           const Vec4 &_p1,
                           const Vec4 &_p2,
                           const Vec4 &_p3
                          );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief << extraction operator to prints out the colour in the format [r,g,b,a]
  /// @param[in] _output the outstream class pointer
  /// @param[in] _c the camera to print out
  //----------------------------------------------------------------------------------------------------------------------
  friend  std::ostream& operator<<(std::ostream& _output, const Camera& _c);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor to get the view matrix
  /// @returns the current view matrix
  //----------------------------------------------------------------------------------------------------------------------
  inline Mat4 & getViewMatrix(){return m_viewMatrix;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor to get the projection matrix
  /// @returns the current projection matrix
  //----------------------------------------------------------------------------------------------------------------------
  inline Mat4 & getProjectionMatrix(){return m_projectionMatrix;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the View * Projection matrix used as part of the MVP calculations
  /// @returns the m_projectionMatrix*m_viewMatrix
  //----------------------------------------------------------------------------------------------------------------------
  inline Mat4  getVPMatrix()const {return m_viewMatrix*m_projectionMatrix;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the eye position
  /// @returns the current eye pos
  //----------------------------------------------------------------------------------------------------------------------
  inline Vec4 & getEye(){return m_eye;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the eye position and re-calculate the matrices
  //----------------------------------------------------------------------------------------------------------------------
  inline void setEye(ngl::Vec4 _e){m_eye=_e; update();}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the look position
  /// @returns the current look pos
  //----------------------------------------------------------------------------------------------------------------------
  inline Vec4 & getLook(){return m_look;}

	//----------------------------------------------------------------------------------------------------------------------
  /// @brief get the u vector
  /// @returns the current u vector
  //----------------------------------------------------------------------------------------------------------------------
  inline Vec4  getU() const{return m_u;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the v vector
  /// @returns the current v vector
  //----------------------------------------------------------------------------------------------------------------------
  inline Vec4  getV()const {return m_v;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the n vector
  /// @returns the current n vector
  //----------------------------------------------------------------------------------------------------------------------
  inline Vec4  getN() const {return m_n;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the fov value
  /// @returns the current fov value
  //----------------------------------------------------------------------------------------------------------------------
	inline float getFOV() const {return m_fov;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the aspect value
  /// @returns the current aspect value
  //----------------------------------------------------------------------------------------------------------------------
	inline float getAspect() const {return m_aspect;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the near clip value
  /// @returns the current near clip value
  //----------------------------------------------------------------------------------------------------------------------
	inline float getNear() const {return m_zNear;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the far clip value
  /// @returns the current far clip value
  //----------------------------------------------------------------------------------------------------------------------
	inline float getFar() const {return m_zFar;}


  //----------------------------------------------------------------------------------------------------------------------
  /// @brief calculate the frustum for clipping etc
  //----------------------------------------------------------------------------------------------------------------------
  void calculateFrustum();

	void drawFrustum();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief check to see if the point passed in is within the frustum
  /// @param _p the point to check
  /// @returns the result of the test (inside outside intercept)
  //----------------------------------------------------------------------------------------------------------------------
  CAMERAINTERCEPT isPointInFrustum(
                                     const Vec3 &_p
                                  ) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief check to see if the sphere passed in is within the frustum
  /// @param[in] _p the center of the sphere
  /// @param[in] _radius the radius of the sphere
  /// @returns the result of the test (inside outside intercept)
  //----------------------------------------------------------------------------------------------------------------------
  CAMERAINTERCEPT isSphereInFrustum(
                                      Vec3 &_p,
                                      float _radius
                                    ) const;

protected :

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief an array of points to hold the different points for the projection calculations work in progress
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec4 m_projPoints[3];
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to set the perspective projection matrix values
  //----------------------------------------------------------------------------------------------------------------------
  void setPerspProjection();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to set the ortho projection matrix values
  //----------------------------------------------------------------------------------------------------------------------
  void setOrthoProjection();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to set the 2 point perspective projection matrix values
  //----------------------------------------------------------------------------------------------------------------------
  void setTwoPointProjection();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function used to set the 3 point perspective projection matrix values
  //----------------------------------------------------------------------------------------------------------------------
  void setThreePointProjection();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief internal function to calculate the  new rotation vectors for the camera after a roll, pitch or yaw
  /// @param[in,out] io_a the first vector to be rotated
  /// @param[in,out] io_b the second vector to be rotated
  /// @param[in] _angle the angle to rotate
  //----------------------------------------------------------------------------------------------------------------------
  void rotAxes(
               Vec4& io_a,
               Vec4& io_b,
               const Real _angle
              );


protected :

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief vector for the  Camera local cord frame
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 m_u;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief vector for the  Camera local cord frame
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 m_v;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief vector for the  Camera local cord frame
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 m_n;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  the position of the Camera  used to calculate the local cord frame
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 m_eye;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  where the camera is looking to,  used with Eye to calculate the Vector m_n
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 m_look;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  gives a general indication of which way up the camera is
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 m_up;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  the width of the display image used for some perspective projection calculations
  //----------------------------------------------------------------------------------------------------------------------
  Real m_width;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the height of the display image used for some perspective projection calculations
  //----------------------------------------------------------------------------------------------------------------------
  Real m_height;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the current camera aspect ratio (can be derived from Width / Height
  //----------------------------------------------------------------------------------------------------------------------
  Real m_aspect;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the near clipping plane of the camera view volume
  //----------------------------------------------------------------------------------------------------------------------
  Real m_zNear;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the far clipping plane of the camera view volume
  //----------------------------------------------------------------------------------------------------------------------
  Real m_zFar;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the feild of view of the camera view volume, measured from the eye
  //----------------------------------------------------------------------------------------------------------------------
  Real m_fov;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief l r t b nr fr used to specify the left right top bottom near far planes for an orthographic camera projection
  //----------------------------------------------------------------------------------------------------------------------
  Real m_l,m_r,m_t,m_b,m_nr,m_fr;
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief a Matrix to hold  the combined modelling and viewing matrix to load into OpenGL
  //----------------------------------------------------------------------------------------------------------------------
  Mat4 m_viewMatrix;
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief array of planes for fustrum
  //----------------------------------------------------------------------------------------------------------------------
	Plane m_planes[6];
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief index values for the planes array
  //----------------------------------------------------------------------------------------------------------------------
  enum  PROJPLANE { TOP = 0,BOTTOM,LEFT,RIGHT,NEARP,FARP};
  Vec3 m_ntl,m_ntr,m_nbl,m_nbr,m_ftl,m_ftr,m_fbl,m_fbr;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Projection a Matrix to hold the perspective transfomatio matrix for the camera, this can be set to be
  /// either PERSPECTIVE (OpenGL standard gluPerspective style), ORTHOGRAPHIC for 2d ortho projection
  /// TWOPOINT for two point perspective or THREEPOINT for three point perspective
  //----------------------------------------------------------------------------------------------------------------------
  Mat4 m_projectionMatrix;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  used to store the current projection mode for the camera
  //----------------------------------------------------------------------------------------------------------------------
  CAMERAPROJECTION m_projectionMode;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the modelview matrix values for the current  camera, this method load the matrix Modelview into OpenGL
  //----------------------------------------------------------------------------------------------------------------------
  void setViewMatrix();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief change the current camera's projection mode based on the enum CAMERAPROJECTION
  /// @param[in] _proj the mode to change to
  //----------------------------------------------------------------------------------------------------------------------
  void ChangeProjectionMode(
                            const CAMERAPROJECTION _proj
                           );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the projection matrix
  //----------------------------------------------------------------------------------------------------------------------
  void setProjectionMatrix();

};
}
#endif // end of  class

//----------------------------------------------------------------------------------------------------------------------

