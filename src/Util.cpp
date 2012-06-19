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
#include "Types.h"
#ifdef __USINGWINDOWS__
  #include <windows.h>
#endif
#ifdef LINUX
  #include <GL/gl.h>
  #include <cstdlib>
#endif
#ifdef DARWIN
  #include <unistd.h>
  #include <OpenGL/gl3.h>
#endif
#include "Vec4.h"
//----------------------------------------------------------------------------------------------------------------------
/// @file Util.cpp
/// @brief implementation files for Util class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
Vec4  calcNormal (
                                 const ngl::Vec4 &_p1,
                                 const ngl::Vec4 &_p2,
                                 const ngl::Vec4 &_p3
                                )
{

	ngl::Real coa, cob, coc ;
	ngl::Real px1, py1, pz1 ;
	ngl::Real px2, py2, pz2 ;
	ngl::Real px3, py3, pz3 ;
	ngl::Real absvec;
	ngl::Vec4 norm;
	px1 = _p1.m_x; py1 = _p1.m_y; pz1 = _p1.m_z;
	px2 = _p2.m_x; py2 = _p2.m_y; pz2 = _p2.m_z;
	px3 = _p3.m_x; py3 = _p3.m_y; pz3 = _p3.m_z;

	// generate cross product

	coa = -(py1 * (pz2-pz3) + py2*(pz3-pz1) + py3*(pz1-pz2)) ;
	cob = -(pz1 * (px2-px3) + pz2*(px3-px1) + pz3*(px1-px2)) ;
	coc = -(px1 * (py2-py3) + px2*(py3-py1) + px3*(py1-py2)) ;

	// normalise the results to get unit length normal
  absvec = sqrtf ( ((coa*coa) + (cob*cob) + (coc*coc))) ;
	norm.m_x = coa/absvec ;
	norm.m_y = cob/absvec ;
	norm.m_z = coc/absvec ;
	norm.m_w=0.0f;

	return norm;
}


//----------------------------------------------------------------------------------------------------------------------
Vec3 calcNormal (
                                 const ngl::Vec3 &_p1,
                                 const ngl::Vec3 &_p2,
                                 const ngl::Vec3 &_p3
                                )
{

  ngl::Real coa, cob, coc ;
  ngl::Real px1, py1, pz1 ;
  ngl::Real px2, py2, pz2 ;
  ngl::Real px3, py3, pz3 ;
  ngl::Real absvec;
  ngl::Vec3 norm;
  px1 = _p1.m_x; py1 = _p1.m_y; pz1 = _p1.m_z;
  px2 = _p2.m_x; py2 = _p2.m_y; pz2 = _p2.m_z;
  px3 = _p3.m_x; py3 = _p3.m_y; pz3 = _p3.m_z;

  // generate cross product

  coa = -(py1 * (pz2-pz3) + py2*(pz3-pz1) + py3*(pz1-pz2)) ;
  cob = -(pz1 * (px2-px3) + pz2*(px3-px1) + pz3*(px1-px2)) ;
  coc = -(px1 * (py2-py3) + px2*(py3-py1) + px3*(py1-py2)) ;

  // normalise the results to get unit length normal
  absvec = sqrtf ( ((coa*coa) + (cob*cob) + (coc*coc))) ;
  norm.m_x = coa/absvec ;
  norm.m_y = cob/absvec ;
  norm.m_z = coc/absvec ;

  return norm;
}

 Real radians(
                            const ngl::Real _deg
                            )
{
	return (_deg/180.0f) * M_PI;
}

//----------------------------------------------------------------------------------------------------------------------
 Real degrees(
                            const Real _rad
                           )
{
	return (_rad / M_PI) * 180.0f;
}


  void NGLCheckGLError(
                                      const std::string  &_file,
                                      const int _line
                                    )
{
 int errNum = glGetError();

  while (errNum != GL_NO_ERROR)
  {
    std::string str;
    errNum = glGetError();
    switch(errNum)
    {
      case GL_INVALID_ENUM : str="GL_INVALID_ENUM error"; break;
      case GL_INVALID_VALUE : str="GL_INVALID_VALUE error"; break;
      case GL_INVALID_OPERATION : str="GL_INVALID_OPERATION error"; break;
      case GL_OUT_OF_MEMORY : str="GL_OUT_OF_MEMORY error"; break;
      // this should be in the spec but it's not on the mac! will check linux
      //case INVALID_FRAMEBUFFER_OPERATION : qDebug("INVALID_FRAMEBUFFER_OPERATION error"); break;
      default : break;
    }
    if(errNum !=GL_NO_ERROR)
    {
		 std::cout<<"GL Error file "<<_file<<" line "<<_line<<"\n"<<str<<"\n";
    }
   }
}


} // end of namespace

//----------------------------------------------------------------------------------------------------------------------



