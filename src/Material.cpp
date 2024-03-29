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
#include <fstream>
#include "ShaderLib.h"
#include "Material.h"
//----------------------------------------------------------------------------------------------------------------------
/// @file Material.cpp
/// @brief implementation files for Material class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{


//----------------------------------------------------------------------------------------------------------------------
void Material :: setDefault()
{
	m_transparency = 0.0;
	m_specularExponent = 1.0;
	m_surfaceRoughness = 0.0;
	m_ambient.set(0.1f,0.1f,0.1f);
	m_diffuse.set(0.8f,0.8f,0.8f);
	m_specular.set(0,0,0);
	m_emissive.set(0,0,0);
}
//----------------------------------------------------------------------------------------------------------------------
Material::Material(
                   const STDMAT _mat
                  )
{
m_specularExponent = s_materials[_mat][9];
m_ambient.set(s_materials[_mat][0],s_materials[_mat][1],s_materials[_mat][2]);
m_diffuse.set(s_materials[_mat][3],s_materials[_mat][4],s_materials[_mat][5]);
m_specular.set(s_materials[_mat][6],s_materials[_mat][7],s_materials[_mat][8]);
m_emissive.set(0,0,0);
m_specularExponent = s_materials[_mat][9];
}

//----------------------------------------------------------------------------------------------------------------------
void Material :: change(
                        const STDMAT _mat
                       )
{
m_specularExponent = s_materials[_mat][9];
m_ambient.set(s_materials[_mat][0],s_materials[_mat][1],s_materials[_mat][2]);
m_diffuse.set(s_materials[_mat][3],s_materials[_mat][4],s_materials[_mat][5]);
m_specular.set(s_materials[_mat][6],s_materials[_mat][7],s_materials[_mat][8]);
m_emissive.set(0,0,0);
}

//----------------------------------------------------------------------------------------------------------------------
Material::Material(
                   const int _mat
                  )
{
m_specularExponent = s_materials[_mat][9];
m_ambient.set(s_materials[_mat][0],s_materials[_mat][1],s_materials[_mat][2]);
m_diffuse.set(s_materials[_mat][3],s_materials[_mat][4],s_materials[_mat][5]);
m_specular.set(s_materials[_mat][6],s_materials[_mat][7],s_materials[_mat][8]);
m_emissive.set(0,0,0);
}

//----------------------------------------------------------------------------------------------------------------------
void Material :: set(
                     const Material &_m
                    )
{
m_transparency = _m.m_transparency;
m_specularExponent = _m.m_specularExponent;
m_surfaceRoughness = _m.m_surfaceRoughness;
m_ambient.set(_m.m_ambient);
m_diffuse.set(_m.m_diffuse);
m_specular.set(_m.m_specular);
m_emissive.set(_m.m_emissive);
}



//----------------------------------------------------------------------------------------------------------------------
Material::Material(
                   const std::string &_fName
                  )
{
std::ifstream FileIn;
FileIn.open(_fName.c_str(),std::ios::in);

if (!FileIn.is_open())
{
	std::cout << "File : "<< _fName <<" Not found Exiting "<<std::endl;
	exit(EXIT_FAILURE);
}

FileIn>>m_ambient;
FileIn>>m_diffuse;
FileIn>>m_specular;
FileIn>>m_emissive;

FileIn.close();
}

//----------------------------------------------------------------------------------------------------------------------
void Material::load(const std::string &_fname)
{
/// @todo write some code to get this to load .mtl files
std::cout<<"Load of "<<_fname <<" not yet implemented\n";
}


void Material::loadToShader(
                            std::string _uniformName
                           )const
{

  ShaderLib *shader=ngl::ShaderLib::instance();
  /*
  so if we use one of our standard shaders for NGL we can load these values
  /// struct Material
  /// {
  ///  vec4 ambient;
  ///  vec4 diffuse;
  ///  vec4 specular;
  ///  float shininess;
  /// };
  */


  shader->setShaderParam4f(_uniformName+".ambient",m_ambient.m_r,m_ambient.m_g,m_ambient.m_b,m_ambient.m_a);
  shader->setShaderParam4f(_uniformName+".diffuse",m_diffuse.m_r,m_diffuse.m_g,m_diffuse.m_b,m_diffuse.m_a);
  shader->setShaderParam4f(_uniformName+".specular",m_specular.m_r,m_specular.m_g,m_specular.m_b,m_specular.m_a);
  shader->setShaderParam1f(_uniformName+".shininess", m_specularExponent);

 // std::cout<<"block id = "<<blockID<<"\n";

}



} // end ngl namespace



