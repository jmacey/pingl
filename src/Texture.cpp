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
/// @file Texture.cpp
/// @brief implementation files for Texture class
//----------------------------------------------------------------------------------------------------------------------
#include "Texture.h"
#include "NGLassert.h"
#include <Magick++.h>
#include <Magick++/Exception.h>

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
bool Texture::loadImage(
                        const std::string &_fName
                       )
{
 Magick::Image image;
 try
 {
  image.read(_fName);
 }
 catch( Magick::WarningCoder &warning )
 {
      // Process coder warning while loading file (e.g. TIFF warning)
      // Maybe the user will be interested in these warnings (or not).
      // If a warning is produced while loading an image, the image
      // can normally still be used (but not if the warning was about
      // something important!)
      std::cerr << "Coder Warning: " << warning.what() << std::endl;
 }
 catch( Magick::Warning &warning )
 {
      // Handle any other Magick++ warning.
      std::cerr << "Warning: " << warning.what() << std::endl;
 }
catch( Magick::ErrorFileOpen &error )
{
      // Process Magick++ file open error
      std::cerr << "Error: " << error.what() << std::endl;
 }


    m_width=image.rows();
    m_height=image.columns();
    m_hasAlpha=image.matte();
    if(m_hasAlpha == true)
    {
      m_bpp=4;
      m_format = GL_RGBA;
    }
    else
    {
      m_bpp=3;
      m_format = GL_RGB;
    }

    m_data = new unsigned char[ m_width*m_height*m_bpp];
    unsigned int index=0;
		Magick::Color c;
    for(unsigned int y=m_height-1; y>0; y--)
    {
      for(unsigned int x=0; x<m_width; ++x)
      {
        c=image.pixelColor(x,y);
				m_data[index]=(unsigned char)c.redQuantum();
				m_data[index+1]=(unsigned char)c.greenQuantum();
				m_data[index+2]=(unsigned char)c.blueQuantum();
        if(m_hasAlpha)
        {
					m_data[index+3]=(unsigned char)c.alphaQuantum();
        }
	index+=m_bpp;
      }
    }

    std::cout<<"Image size ="<<m_width<<"x"<<m_height<<std::endl;
    std::cout<<"has alpha = "<<m_hasAlpha<<std::endl;
    std::cout<<"bpp = "<<m_bpp<<std::endl;
    return true;
}

//----------------------------------------------------------------------------------------------------------------------
Texture::Texture()
{
	m_width=0;
	m_height=0;
	m_data=0;
  m_multiTextureID=0;
	m_hasAlpha=false;
}

//----------------------------------------------------------------------------------------------------------------------
Texture::Texture(
                 const std::string &_fName
                )
{
	m_width=0;
	m_height=0;
	m_data=NULL;
  m_multiTextureID=0;
  std::cout<<"texture ctor\n";
	loadImage(_fName);
}


//----------------------------------------------------------------------------------------------------------------------
Texture::~Texture()
{
	if(m_data)
		delete [] m_data;
}

//----------------------------------------------------------------------------------------------------------------------
double Texture::getFromXY(
                          const GLuint _x,
                          const GLuint _y
                         ) const
{
// make sure were in the image range
//	NGL_ASSERT(_x<=m_width && _y<=m_height);
	if (m_data !=0)
	{
		return m_data[_x*4+((_y)*m_width*4)];
	}
	else
	{
		return 0;
	}
}
//----------------------------------------------------------------------------------------------------------------------

/*! \note this is really inflexible at the moment needs to be made more generic and give more
control over the OpenGL texture types etc
Could actually be worth creating a texture manager class at some stage along the lines of the
Shader manager class, or even a generic manager framework which we could then add items to
*/
GLuint Texture::setTextureGL() const
{
  GLuint textureName;
  glGenTextures(1,&textureName);
  glActiveTexture(GL_TEXTURE0+m_multiTextureID);
  glBindTexture(GL_TEXTURE_2D,textureName);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D,0,m_format,m_width,m_height,0,m_format,GL_UNSIGNED_BYTE,m_data);
  glGenerateMipmap(GL_TEXTURE_2D);
  
  std::cout<<"texture GL set "<<textureName<<"\n";

  return textureName;
}
//----------------------------------------------------------------------------------------------------------------------

void Texture::setMultiTexture(
                              const GLint _id
                             )
{
 m_multiTextureID=_id;
}

ngl::Colour Texture::getColourFromXY(
                                    const GLuint _x,
                                    const GLuint _y
                                   ) const
{
// make sure were in the image range
//	NGL_ASSERT(_x<=m_width && _y<=m_height);
	if (m_data !=0)
	{
		int Offset=_x*4+((_y)*m_width*4);
		return ngl::Colour(m_data[Offset],m_data[Offset+1],m_data[Offset+2],m_data[Offset+3]);
	}
	else
	{
		return ngl::Colour(0,0,0,0);
	}
}


ngl::Colour Texture::getColour(
                                const ngl::Real c_uvX,
                                const ngl::Real c_uvY
                              ) const
{

  GLuint xx = c_uvX * (m_width-1);
  GLuint yy = c_uvY * (m_height-1);

 // NGL_ASSERT(xx<m_width && yy<m_height);

  if(m_data!=0)
  {
    int offset = xx * m_bpp + (yy * m_width * m_bpp );
    if(m_bpp == 4)
    {
      return ngl::Colour(m_data[offset],m_data[offset+1],m_data[offset+2],m_data[offset+3]);
    }
    else
    {
      return ngl::Colour(m_data[offset],m_data[offset+1],m_data[offset+2],1.0);
    }
  }
  else
  {
    return ngl::Colour(0,0,0,0);
  }
}


} // end namespace ngl;

//----------------------------------------------------------------------------------------------------------------------

