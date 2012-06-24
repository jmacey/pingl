#include "Text.h"
#include "VertexArrayObject.h"
#include <iostream>
#include "ShaderLib.h"
#include <boost/foreach.hpp>
#include <ft2build.h>
#include <freetype/ftglyph.h>

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
//---------------------------------------------------------------------------
namespace ngl
{

#include "Text.h"

//---------------------------------------------------------------------------
/// @brief code taken from here http://jeffreystedfast.blogspot.com/2008/06/calculating-nearest-power-of-2.html
/// @param _num the number we wish to get the nearest power from
// OpenGL needs textures to be in powers of two, this function will get the
// nearest power of two to the current value passed in
//---------------------------------------------------------------------------
unsigned int nearestPowerOfTwo (
                                 unsigned int _num
                                )
{
    unsigned int j, k;
    (j = _num & 0xFFFF0000) || (j = _num);
    (k = j & 0xFF00FF00) || (k = j);
    (j = k & 0xF0F0F0F0) || (j = k);
    (k = j & 0xCCCCCCCC) || (k = j);
    (j = k & 0xAAAAAAAA) || (j = k);
    return j << 1;
}
// end citation

//---------------------------------------------------------------------------
Text::Text(
            const std::string &_fName,
            unsigned int _h
          )
{


	FT_Library library;
	if (FT_Init_FreeType( &library ))
	{
		std::cerr<<"FT_Init_FreeType failed\n";
		exit(EXIT_FAILURE);
	}

	//The object in which Freetype holds information on a given
	//font is called a "face".
	FT_Face face;

	//This is where we load in the font information from the file.
	//Of all the places where the code might die, this is the most likely,
	//as FT_New_Face will die if the font file does not exist or is somehow broken.
	if (FT_New_Face( library, _fName.c_str(), 0, &face ))
	{
		std::cerr<<"FT_new face failed usually a problem with the font\n";
		exit(EXIT_FAILURE);
	}

	//For some twisted reason, Freetype measures font size
	//in terms of 1/64ths of pixels.  Thus, to make a font
	//h pixels high, we need to request a size of h*64.
	//(h << 6 is just a prettier way of writting h*64)
	FT_Set_Char_Size( face, _h << 6, _h << 6, 96, 96);



  // loop for all basic keyboard chars we will use space to ~
  // should really change this to unicode at some stage
  const static char startChar=' ';
  const static char endChar='~';
  // Most OpenGL cards need textures to be in powers of 2 (128x512 1024X1024 etc etc) so
  // to be safe we will conform to this and calculate the nearest power of 2 for the glyph height
  // we will do the same for each width of the font below
//  int heightPow2=nearestPowerOfTwo(fontHeight);

  // we are now going to create a texture / billboard for each font
  // they will be the same height but will possibly have different widths
  // as some of the fonts will be the same width, to save VAO space we will only create
  // a vao if we don't have one of the set width. To do this we use the has below
  std::map <int,VertexArrayObject *> widthVAO;
  for(char c=startChar; c<=endChar; ++c)
  {
    FontChar fc;
		std::cerr <<"doing char "<<c<<"\n";
		//Load the Glyph for our character.
		if(FT_Load_Glyph( face, FT_Get_Char_Index( face, c ), FT_LOAD_DEFAULT ))
		{
			std::cerr<<"FT_Load_Glyph failed\n";
		}
		//Move the face's glyph into a Glyph object.
			FT_Glyph glyph;
			if(FT_Get_Glyph( face->glyph, &glyph ))
			std::cerr<<"FT_Get_Glyph failed\n";

		//Convert the glyph to a bitmap.
		FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

		//This reference will make accessing the bitmap easier
		FT_Bitmap& bitmap=bitmap_glyph->bitmap;

	//Use our helper function to get the widths of
	//the bitmap data that we will need in order to create
	//our texture.

		float fontHeight=face->glyph->metrics.height;
		fontHeight=fontHeight/64.0;
		int width =(face->glyph->metrics.width)/64;
		int widthPow2=nearestPowerOfTwo(width);
		int height = bitmap.rows;
		int heightPow2=nearestPowerOfTwo(height);




	std::cerr<<"font height "<<fontHeight<<"\n";

		//Allocate memory for the texture data.
		GLubyte* data = new GLubyte[ 4 * widthPow2 * heightPow2];
		unsigned int index=0;
		for(int j=0; j <heightPow2;j++)
		{
			for(int i=0; i < widthPow2; i++)
			{

				data[index++]=0;
				data[index++]=0;
				data[index++]=0;
				data[index++]=
				(i>=bitmap.width || j>=bitmap.rows) ?
				0 : bitmap.buffer[i + bitmap.width*j];
			}
		}


    // now we set the texture co-ords for our quad it is a simple
    // triangle billboard with tex-cords as shown
    //  s0/t0  ---- s1,t0
    //         |\ |
    //         | \|
    //  s0,t1  ---- s1,t1
    // each quad will have the same s0 and the range s0-s1 == 0.0 -> 1.0
    ngl::Real s0=0.0;
    // we now need to scale the tex cord to it ranges from 0-1 based on the coverage
    // of the glyph and not the power of 2 texture size. This will ensure that kerns
    // / ligatures match
    ngl::Real s1=width*1.0/widthPow2;
    // t0 will always be the same
    ngl::Real t0=0.0;
    // this will scale the height so we only get coverage of the glyph as above
    ngl::Real t1=height*-1.0/heightPow2;
    // we need to store the font width for later drawing
    fc.width=width;


     // now we create the OpenGL texture ID and bind to make it active
    glGenTextures(1, &fc.textureID);
    glBindTexture(GL_TEXTURE_2D, fc.textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, widthPow2, heightPow2,
		  0, GL_RGBA, GL_UNSIGNED_BYTE, data );
		// now we have bound the data we can clear it
		delete [] data;


    // see if we have a Billboard of this width already
    if (widthVAO.find( width ) == widthVAO.end())
	  {
    	std::cerr<<"allocating vao for "<<c<<"\n";
        // this structure is used by the VAO to store the data to be uploaded
        // for drawing the quad
        struct textVertData
        {
        ngl::Real x;
        ngl::Real y;
        ngl::Real u;
        ngl::Real v;
        };
        // we are creating a billboard with two triangles so we only need the
        // 6 verts, (could use index and save some space but shouldn't be too much of an
        // issue
        textVertData d[6];
        // load values for triangle 1
        d[0].x=0;
        d[0].y=0;
        d[0].u=s0;
        d[0].v=t1;

        d[1].x=fc.width;
        d[1].y=0;
        d[1].u=s1;
        d[1].v=t1;

        d[2].x=0;
        d[2].y=fontHeight;
        d[2].u=s0;
        d[2].v=t0;
        // load values for triangle two
        d[3].x=0;
        d[3].y=0+fontHeight;
        d[3].u=s0;
        d[3].v=t0;


        d[4].x=fc.width;
        d[4].y=0;
        d[4].u=s1;
        d[4].v=t1;


        d[5].x=fc.width;
        d[5].y=fontHeight;
        d[5].u=s1;
        d[5].v=t0;


        // now we create a VAO to store the data
        ngl::VertexArrayObject *vao=ngl::VertexArrayObject::createVOA(GL_TRIANGLES);
        // bind it so we can set values
        vao->bind();
        // set the vertex data (2 for x,y 2 for u,v)
        vao->setData(6*sizeof(textVertData),d[0].x);
        // now we set the attribute pointer to be 0 (as this matches vertIn in our shader)
        vao->setVertexAttributePointer(0,2,GL_FLOAT,sizeof(textVertData),0);
        // We can now create another set of data (which will be added to the VAO)
        // in this case the UV co-ords
        // now we set this as the 2nd attribute pointer (1) to match inUV in the shader
        vao->setVertexAttributePointer(1,2,GL_FLOAT,sizeof(textVertData),2);
        // say how many indecis to be rendered
        vao->setNumIndices(6);

        // now unbind
        vao->unbind();
        // store the vao pointer for later use in the draw method
        fc.vao=vao;
        widthVAO[width]=vao;
    }
    else
    {
      fc.vao=widthVAO[width];
    }
    // finally add the element to the map, this must be the last
    // thing we do
    m_characters[c]=fc;
  }
  std::cerr<<"created "<<widthVAO.size()<<" unique billboards\n";
  // set a default colour (black) incase user forgets
  this->setColour(0,0,0);


}


//---------------------------------------------------------------------------
Text::~Text()
{
  // our dtor should clear out the textures and remove the VAO's
  typedef std::map<char,FontChar> map_t;

  BOOST_FOREACH(map_t::value_type &i, m_characters)
  {
    glDeleteTextures(1,&i.second.textureID);
    i.second.vao->removeVOA();
  }

}




//---------------------------------------------------------------------------
void Text::renderText(
                      float _x,
                      float _y,
                      const std::string &text
                     )
{
  // make sure we are in texture unit 0 as this is what the
  // shader expects
  glActiveTexture(0);
  // grab an instance of the shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  // use the built in text rendering shader
  (*shader)["nglTextShader"]->use();
  // the y pos will always be the same so set it once for each
  // string we are rendering
  shader->setRegisteredUniform1f("ypos",_y);
  // now enable blending and disable depth sorting so the font renders
  // correctly
  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // now loop for each of the char and draw our billboard
  unsigned int textLength=text.length();

  for (unsigned int i = 0; i < textLength; ++i)
  {
    // set the shader x position this will change each time
    // we render a glyph by the width of the char
    shader->setRegisteredUniform1f("xpos",_x);
    // so find the FontChar data for our current char
    char c=text[i];
    FontChar f = m_characters[c];
    // bind the pre-generated texture
    glBindTexture(GL_TEXTURE_2D, f.textureID);
    std::cerr<<"doing draw for "<<c<<" "<<f.textureID<<"\n";
    // bind the vao
    f.vao->bind();
    // draw
    f.vao->draw();
    // now unbind the vao
    f.vao->unbind();
    // finally move to the next glyph x position by incrementing
    // by the width of the char just drawn
    _x+=f.width;

  }
  // finally disable the blend and re-enable depth sort
  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);

}

//---------------------------------------------------------------------------
void Text::setScreenSize(
                          int _w,
                          int _h
                        )
{

  float scaleX=2.0/_w;
  float scaleY=-2.0/_h;
  // in shader we do the following code to transform from
  // x,y to NDC
  // gl_Position=vec4( ((xpos+inVert.x)*scaleX)-1,((ypos+inVert.y)*scaleY)+1.0,0.0,1.0); "
  // so all we need to do is calculate the scale above and pass to shader every time the
  // screen dimensions change
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["nglTextShader"]->use();

  shader->setRegisteredUniform1f("scaleX",scaleX);
  shader->setRegisteredUniform1f("scaleY",scaleY);
}

//---------------------------------------------------------------------------
// our text shader uses the alpha of the texture to modulate visibility
// when we render the text we use this colour passed to the shader
// it is default to black but this will change it
// the shader uses the following code
// vec4 text=texture(tex,vertUV.st);
// fragColour.rgb=textColour.rgb;
// fragColour.a=text.a;

void Text::setColour(
                      const ngl::Colour &_c
                    )
{
  // get shader instance
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  // make current shader active
  (*shader)["nglTextShader"]->use();
  // set the values
  shader->setRegisteredUniform3f("textColour",_c.r(),_c.g(),_c.b());
}


//---------------------------------------------------------------------------
void Text::setColour(
                      ngl::Real _r,
                      ngl::Real _g,
                      ngl::Real _b
                    )
{

  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["nglTextShader"]->use();

  shader->setRegisteredUniform3f("textColour",_r,_g,_b);
}


} //end namespace
//---------------------------------------------------------------------------

