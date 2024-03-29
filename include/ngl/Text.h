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
#ifndef __TEXT_H__
#define __TEXT_H__


//----------------------------------------------------------------------------------------------------------------------
/// @file Text.h
/// @brief Basic text rendering for OpenGL 3.x
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/10/11 Initial version
/// @todo support unicode ASCII is so 1980's ;-0
/// This class will generate billboard textures and VertexArrayObjects
/// for each of the font glyphs, this means we need a valid OpenGL context before
/// using this class, therefore it should be constructed in initalizeGL or after.
/// Note for efficiency once the font has been created we can only change the colour, if you
/// need different sizes / emphasis you will need to create a new Text object with the
/// desired size / emphasis. This is accelerated as much as possible but text rendering will sometimes be slow
/// as we bind a new texture for each char being drawn
/// for more details look at the blog post here
/// http://jonmacey.blogspot.com/2011/10/text-rendering-using-opengl-32.html
//----------------------------------------------------------------------------------------------------------------------
// must include types.h first for ngl::Real and GLEW if required

#include "Types.h"
#include "Colour.h"
#include "VertexArrayObject.h"
#include "Vec2.h"
#include <map>




namespace ngl
{

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a structure to hold the font char texture id
  /// and the vao. The vao for each font will be a different size
  /// need to investigate is a scale would be quicker / more efficient
  /// than storing multiple billboards (some will be the same size)
  //----------------------------------------------------------------------------------------------------------------------
  struct FontChar
  {
    int width; /// @brief the width of the font
    GLuint textureID; /// @brief the texture id of the font billboard
    ngl::VertexArrayObject *vao; /// a vao for the font
  };

class  Text
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor passing in font name and height
  /// @param [in] _fName the name of the font
  /// @param [in] _h the height of the fonts
  //----------------------------------------------------------------------------------------------------------------------
  Text(
        const std::string &_fName,
        unsigned int _h
      );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor will clean / remove textures and VAO's for the class
  //----------------------------------------------------------------------------------------------------------------------
  ~Text();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief render the text to the screen at _x,_y where 0,0 is top left of the screen
  /// all positioning is relative to the screen size set with the setScreenSize method so it is important that
  /// changes in screen size are updated. These value will be sent to the nglTextShader to be rendered (see source )
  /// @note font quad is drawn as 0,0 being bottom left so if we draw at 0,0 the font will not be visible, we need
  /// to add the offset of the font height to any y value (i.e. a 16pt font drawn at 0,16 will appear at top right of the screen)
  /// @param[in] _x the x position of the text in screen space
  /// @param[in] _y the y position of the text in screen space
  /// @param[in] _text the text to draw (this is limited to ASCII chars ' '->'~' at present but unicode will be done soon
  //----------------------------------------------------------------------------------------------------------------------
  void renderText(
                  float _x,
                  float _y,
                  const std::string &_text
                  ) ;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the size of the screen to scale our font to fit correctly
  /// this basically creates the orthographic projection needed for x/y assuming that the
  /// openGL window has 0,0 at the center and we use NDC co-ordinates -1 -> 1 in X and Y
  /// we then get x=(x*xScale)+xtran y=(y*yScale)+ytrans; to place the text in screen space
  /// @param[in] _w the current width of the screen
  /// @param[in] _h the current height of the screen
  //----------------------------------------------------------------------------------------------------------------------
  void setScreenSize(
                      int _w,
                      int _h
                    );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the colour of the font from an ngl::Colour
  /// @param[in] _c the colour to set for the font (alpha is overridden by the texture)
  //----------------------------------------------------------------------------------------------------------------------
  void setColour(
                  const ngl::Colour &_c
                );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the colour of the font from three floats as a convenience method
  /// @param[in] _r the red component of the colour for the font
  /// @param[in] _g the green component of the colour for the font
  /// @param[in] _b the blue component of the colour for the font
  //----------------------------------------------------------------------------------------------------------------------
  void setColour(
                  ngl::Real _r,
                  ngl::Real _g,
                  ngl::Real _b
                );
private:
  /// @brief a map to store our FontChar data looked up by the char we want
  /// to render
  std::map <char,FontChar> m_characters;




};

}

#endif






//----------------------------------------------------------------------------------------------------------------------
