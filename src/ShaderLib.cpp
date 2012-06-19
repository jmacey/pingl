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
#include <cstdlib>
#include "ShaderLib.h"
#include "TextShaders.h"
#include "ColourShaders.h"


//----------------------------------------------------------------------------------------------------------------------
/// @file ShaderLib.cpp
/// @brief implementation files for ShaderLibrary and manager class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{


//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setShaderParamFromMatrix(
                                            const std::string &_paramName,
                                            ngl::Mat4 _p1
                                           )
{
  (*this)[m_currentShader]->setUniformMatrix4fv(_paramName.c_str(),1,GL_FALSE,_p1.openGL());
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setRegisteredUniformFromMatrix(
                                                const std::string &_registeredUniformName,
                                                ngl::Mat4 _p1
                                               )
{
  (*this)[m_currentShader]->setRegisteredUniformMatrix4fv(_registeredUniformName,1,GL_FALSE,_p1.openGL());
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setShaderParamFromMat3x3(
                                            const std::string &_paramName,
                                            ngl::Mat3 _p1
                                           )
{
  (*this)[m_currentShader]->setUniformMatrix3fv(_paramName.c_str(),1,GL_FALSE,_p1.openGL());
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setRegisteredUniformFromMat3x3(
                                              const std::string &_paramName,
                                              ngl::Mat3 _p1
                                             )
{
  (*this)[m_currentShader]->setRegisteredUniformMatrix3fv(_paramName,1,GL_FALSE,_p1.openGL());
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setShaderParamFromVector(
																							const std::string &_paramName,
																							ngl::Vec4 _p1
																						 )
{

	(*this)[m_currentShader]->setUniform4fv(_paramName.c_str(),1,_p1.openGL());

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setRegisteredUniformVector(
                                              const std::string &_paramName,
                                              ngl::Vec4 _p1
                                             )
{
  (*this)[m_currentShader]->setRegisteredUniform4f(_paramName,_p1.m_x,_p1.m_y,_p1.m_z,_p1.m_w);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setShaderParamFromColour(
                                              const std::string &_paramName,
                                              ngl::Colour _p1
                                             )
{

  (*this)[m_currentShader]->setUniform4fv(_paramName.c_str(),1,_p1.openGL());

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setRegisteredUniformFromColour(
                                              const std::string &_paramName,
                                              ngl::Colour _p1
                                             )
{
  (*this)[m_currentShader]->setRegisteredUniform4f(_paramName,_p1.m_r,_p1.m_g,_p1.m_b,_p1.m_a);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setRegisteredUniformVec3(
                                              const std::string &_paramName,
                                              ngl::Vec3 _p1
                                             )
{
  (*this)[m_currentShader]->setRegisteredUniform3f(_paramName,_p1.m_x,_p1.m_y,_p1.m_z);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setRegisteredUniformVec2(
                                              const std::string &_paramName,
                                              ngl::Vec2 _p1
                                             )
{
  (*this)[m_currentShader]->setRegisteredUniform2f(_paramName,_p1.m_x,_p1.m_y);
}




//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setShaderParam4f(
                                  const std::string &_paramName,
                                  float _p1,
                                  float _p2,
                                  float _p3,
                                  float _p4

                                  )
{
	(*this)[m_currentShader]->setUniform4f(_paramName.c_str(),_p1,_p2,_p3,_p4);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setRegisteredUniform4f(
                                        const std::string &_paramName,
                                        float _p1,
                                        float _p2,
                                        float _p3,
                                        float _p4

                                        )
{
  (*this)[m_currentShader]->setRegisteredUniform4f(_paramName,_p1,_p2,_p3,_p4);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setShaderParam3f(
                                      const std::string &_paramName,
                                      float _p1,
                                      float _p2,
                                      float _p3
                                    )
{
	(*this)[m_currentShader]->setUniform3f(_paramName.c_str(),_p1,_p2,_p3);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setRegisteredUniform3f(
                                        const std::string &_paramName,
                                        float _p1,
                                        float _p2,
                                        float _p3
                                        )
{
  (*this)[m_currentShader]->setRegisteredUniform3f(_paramName,_p1,_p2,_p3);
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setShaderParam2f(
                                      const std::string &_paramName,
                                      float _p1,
                                      float _p2
                                    )
{
	(*this)[m_currentShader]->setUniform2f(_paramName.c_str(),_p1,_p2);

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setRegisteredUniform2f(
                                        const std::string &_paramName,
                                        float _p1,
                                        float _p2
                                        )
{
  (*this)[m_currentShader]->setRegisteredUniform2f(_paramName,_p1,_p2);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setShaderParam1i(
                                      const std::string &_paramName,
                                      int _p1
                                    )
{
	(*this)[m_currentShader]->setUniform1i(_paramName.c_str(),_p1);

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setRegisteredUniform1i(
                                      const std::string &_paramName,
                                      int _p1
                                      )
{
  (*this)[m_currentShader]->setRegisteredUniform1i(_paramName,_p1);
}



//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setShaderParam1f(
                                      const std::string &_paramName,
                                      float _p1
                                    )
{
	(*this)[m_currentShader]->setUniform1f(_paramName.c_str(),_p1);

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::setRegisteredUniform1f(
                                      const std::string &_paramName,
                                      float _p1
                                      )
{
  (*this)[m_currentShader]->setRegisteredUniform1f(_paramName,_p1);
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::loadShader(
                               const std::string &_shaderName,
                               const std::string &_vert,
                               const std::string &_frag,
                               const std::string &_geo,
                               const bool _exitOnError
                              )
{
  // must add code to do this next version
  createShaderProgram(_shaderName);

  attachShader(_shaderName+"Vertex",VERTEX);
  attachShader(_shaderName+"Fragment",FRAGMENT);
  loadShaderSource(_shaderName+"Vertex",_vert);
  loadShaderSource(_shaderName+"Fragment",_frag);

  compileShader(_shaderName+"Vertex");
  compileShader(_shaderName+"Fragment");
  attachShaderToProgram(_shaderName,_shaderName+"Vertex");
  attachShaderToProgram(_shaderName,_shaderName+"Fragment");
	if( _geo !="")
	{
    attachShader(_shaderName+"Geo",GEOMETRY);
		loadShaderSource(_shaderName+"Geo",_vert);
		compileShader(_shaderName+"Geo");
		attachShaderToProgram(_shaderName,_shaderName+"Geo");
	}

  linkProgramObject(_shaderName);
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::reset()
{
	std::cerr<<"Closing down shader manager\n";

  std::map <std::string,ShaderProgram *>::iterator pbegin=m_shaderPrograms.begin();
  std::map <std::string,ShaderProgram *>::iterator pend=m_shaderPrograms.end();
  // delete each of the shader programs first (this will clear the maps in Program)
  // but not delete the shaders
  while(pbegin != pend)
  {
    delete pbegin->second;
    ++pbegin;
  }
  // now we delete all of the shaders
  std::map <std::string,Shader *>::iterator sbegin=m_shaders.begin();;
  std::map <std::string,Shader *>::iterator send=m_shaders.end();;

  while(sbegin != send)
  {
    delete sbegin->second;
    ++sbegin;
  }

}


//----------------------------------------------------------------------------------------------------------------------
GLint ShaderLib::getAttribLocation(
                                        const std::string &_shaderName,
                                        const std::string &_paramName
                                       )
{

  GLint attrib=0;

  // get an iterator to the shaders
  std::map <std::string, ShaderProgram * >::const_iterator shader=m_shaderPrograms.find(_shaderName);
  // make sure we have a valid shader
	if(shader!=m_shaderPrograms.end())
  {
    // grab the pointer to the shader and call compile
    attrib=glGetAttribLocation((long) shader->second->getID(),_paramName.c_str());
  }
	else
	{
		std::cerr <<"Warning trying to get attrib "<<_paramName<<" from "<<_shaderName<<" but not found\n";
	}

  return attrib;

}



//----------------------------------------------------------------------------------------------------------------------
ShaderLib::ShaderLib()
{
//std::cout<<"Shader Manager ctor\n";
 m_debugState=true;
 m_numShaders=0;
 m_nullProgram = new ShaderProgram("NULL");
 m_currentShader="NULL";
 loadTextShaders();
 loadColourShaders();
}
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::attachShader(
                                  std::string _name,
                                  SHADERTYPE _type
                                )
{
  m_shaders[_name]= new Shader(_name,_type);
  std::cout<<"just attached "<<_name<<" "<<m_shaders[_name]->getShaderHandle()<<"\n";
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::compileShader(
																	 std::string _name
																	)
{
  // get an iterator to the shaders
  std::map <std::string, Shader * >::const_iterator shader=m_shaders.find(_name);
  // make sure we have a valid shader
	if(shader!=m_shaders.end())
  {
    // grab the pointer to the shader and call compile
    shader->second->compile();
  }
  else {std::cerr<<"Warning shader not know in compile "<<_name.c_str();}

}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::createShaderProgram(
																				 std::string _name
																			  )
{
 std::cerr<<"creating empty ShaderProgram "<<_name.c_str()<<"\n";
 m_shaderPrograms[_name]= new ShaderProgram(_name);
}
//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::attachShaderToProgram(
																					 std::string _program,
																					 std::string _shader
																					)

{

  // get an iterator to the shader and program
  std::map <std::string, Shader * >::const_iterator shader=m_shaders.find(_shader);
  std::map <std::string, ShaderProgram * >::const_iterator program=m_shaderPrograms.find(_program);

  // make sure we have a valid shader and program
	if(shader!=m_shaders.end() && program !=m_shaderPrograms.end())
  {
    // now attach the shader to the program
    program->second->attatchShader(shader->second);
    // now increment the shader ref count so we know if how many references
    shader->second->incrementRefCount();

    if (m_debugState == true)
    {
      std::cerr<<_shader.c_str()<<" attached to program "<<_program.c_str()<<"\n";
    }
  }
  else {std::cerr<<"Warning cant attach "<<_shader.c_str() <<" to "<<_program.c_str()<<"\n";}
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::loadShaderSource(
																			std::string _shaderName,
																			std::string _sourceFile
																		 )
{
  std::map <std::string, Shader * >::const_iterator shader=m_shaders.find(_shaderName);
  // make sure we have a valid shader and program
	if(shader!=m_shaders.end() )
  {
    shader->second->load(_sourceFile);
  }
  else {std::cerr<<"Warning shader not know in loadShaderSource "<<_shaderName.c_str();}

}



//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::loadShaderSourceFromString(const std::string &_shaderName,
																						const char  **_string
																						)
{
  std::map <std::string, Shader * >::const_iterator shader=m_shaders.find(_shaderName);
  // make sure we have a valid shader and program
  if(shader!=m_shaders.end() )
  {
    shader->second->loadFromString(std::string(*_string));
  }
  else {std::cerr<<"Warning shader not know in loadShaderSource "<<_shaderName.c_str();}

}


//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::linkProgramObject(
																			 std::string _name
																			)
{

  std::map <std::string, ShaderProgram * >::const_iterator program=m_shaderPrograms.find(_name);
  // make sure we have a valid  program
	if(program!=m_shaderPrograms.end() )
  {
    std::cerr<<"Linking "<<_name.c_str()<<"\n";
    program->second->link();
  }
  else {std::cerr<<"Warning Program not known in link "<<_name.c_str();}

}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::use(
												 std::string _name
												)
{
  std::map <std::string, ShaderProgram * >::const_iterator program=m_shaderPrograms.find(_name);
  // make sure we have a valid  program
	if(program!=m_shaderPrograms.end() )
  {
    //std::cerr<<"Shader manager Use\n";
		m_currentShader=_name;
    program->second->use();
  }
  else
  {
    std::cerr<<"Warning Program not know in use "<<_name.c_str();
		m_currentShader="NULL";
    glUseProgram(0);
  }

}


//----------------------------------------------------------------------------------------------------------------------
GLuint ShaderLib::getProgramID(
																		std::string _name
																	 )
{
  std::map <std::string, ShaderProgram * >::const_iterator program=m_shaderPrograms.find(_name);
  // make sure we have a valid  program
	if(program!=m_shaderPrograms.end() )
  {
    return program->second->getID();
  }
  else
  {
    std::cerr<<"Warning Program not know in use "<<_name.c_str();
    return -1;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::registerUniform(
                                 std::string _shaderName,
                                 std::string _uniformName
                               )
{
  std::map <std::string, ShaderProgram * >::const_iterator program=m_shaderPrograms.find(_shaderName);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
     program->second->registerUniform(_uniformName);
  }
  else
  {
    std::cerr<<"Warning Program not know in registerUniform "<<_shaderName<<" "<<_uniformName<<"\n";
  }
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::autoRegisterUniforms(
                                      std::string _shaderName
                                    )
{
  std::map <std::string, ShaderProgram * >::const_iterator program=m_shaderPrograms.find(_shaderName);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
     program->second->autoRegisterUniforms();
  }
  else
  {
    std::cerr<<"Warning Program not know in registerUniform "<<_shaderName<<"\n";
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderLib::bindAttribute(
																	 std::string _programName,
																	 GLuint _index,
																	 std::string _attribName
																  )
{
  std::map <std::string, ShaderProgram * >::const_iterator program=m_shaderPrograms.find(_programName);
  // make sure we have a valid  program
	if(program!=m_shaderPrograms.end() )
  {
    program->second->bindAttribute(_index,_attribName);
  }
  else {std::cerr<<"Warning Program not know in bindAttribute "<<_programName.c_str();}
}


//----------------------------------------------------------------------------------------------------------------------
void ceckGLError(
                  const std::string  &_file,
                  const int _line
                )
{

  NGLCheckGLError(_file,_line);

}


//----------------------------------------------------------------------------------------------------------------------
ShaderProgram * ShaderLib::operator[](
																					 const std::string &_name
																					)
{
  std::map <std::string, ShaderProgram * >::const_iterator program=m_shaderPrograms.find(_name);
  // make sure we have a valid  program
	if(program!=m_shaderPrograms.end() )
  {
		m_currentShader=_name;
		return  program->second;
  }
  else
  {
    std::cerr<<"Warning Program not know in [] "<<_name.c_str();
    std::cerr<<"returning a null program and hoping for the best\n";
    return m_nullProgram;
  }
}


//----------------------------------------------------------------------------------------------------------------------
ShaderProgram * ShaderLib::operator[](
																					const char *_name
																					)
{
  std::map <std::string, ShaderProgram * >::const_iterator program=m_shaderPrograms.find(_name);
  // make sure we have a valid  program
	if(program!=m_shaderPrograms.end() )
  {
		m_currentShader=_name;

    return  program->second;
  }
  else
  {
    std::cerr<<"Warning Program not know in [] "<<_name;
    std::cerr<<"returning a null program and hoping for the best\n";
    return m_nullProgram;
  }
}


void ShaderLib::useNullProgram()
{
	m_currentShader="NULL";
  m_nullProgram->use();
}


GLuint ShaderLib::getUniformBlockIndex(
                                        const std::string &_uniformBlockName
                                      ) const
{


  GLint id=0;

  // get an iterator to the shaders
  std::map <std::string, ShaderProgram * >::const_iterator shader=m_shaderPrograms.find(m_currentShader);
  // make sure we have a valid shader
  if(shader!=m_shaderPrograms.end())
  {
    // grab the pointer to the shader and call compile
    id=shader->second->getUniformBlockIndex(_uniformBlockName);
  }
  else
  {
    std::cerr <<"Can't find id for uniform block " << _uniformBlockName <<"\n";
  }

  return id;
}

void ShaderLib::loadTextShaders()
{

  createShaderProgram("nglTextShader");

  attachShader("nglTextVertex",VERTEX);
  attachShader("nglTextFragment",FRAGMENT);

  loadShaderSourceFromString("nglTextVertex",textVertexShader);
  loadShaderSourceFromString("nglTextFragment",textFragmentShader);

  compileShader("nglTextVertex");
  compileShader("nglTextFragment");


  attachShaderToProgram("nglTextShader","nglTextVertex");
  attachShaderToProgram("nglTextShader","nglTextFragment");

  bindAttribute("nglTextShader",0,"inVert");
  bindAttribute("nglTextShader",1,"inUV");

  linkProgramObject("nglTextShader");
  use("nglTextShader");
  autoRegisterUniforms("nglTextShader");

  use("NULL");
}


void ShaderLib::loadColourShaders()
{

  createShaderProgram("nglColourShader");

  attachShader("nglColourVertex",VERTEX);
  attachShader("nglColourFragment",FRAGMENT);

  loadShaderSourceFromString("nglColourVertex",colourVertexShader);
  loadShaderSourceFromString("nglColourFragment",colourFragmentShader);

  compileShader("nglColourVertex");
  compileShader("nglColourFragment");


  attachShaderToProgram("nglColourShader","nglColourVertex");
  attachShaderToProgram("nglColourShader","nglColourFragment");

  bindAttribute("nglColourShader",0,"inVert");

  linkProgramObject("nglColourShader");
  use("nglColourShader");
  autoRegisterUniforms("nglColourShader");
  use("NULL");
}



void ShaderLib::printRegisteredUniforms(std::string _shader) const
{
  std::map <std::string, ShaderProgram * >::const_iterator program=m_shaderPrograms.find(_shader);
  // make sure we have a valid  program
  if(program!=m_shaderPrograms.end() )
  {
    program->second->printRegisteredUniforms();
  }
}


} // end ngl namespace



//----------------------------------------------------------------------------------------------------------------------

