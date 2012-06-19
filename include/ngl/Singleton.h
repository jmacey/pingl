/*
  Copyright (C) 2009 Vincent Bonnet

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
#ifndef __SINGLETON_H__
#define __SINGLETON_H__
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include <iostream>
#include <typeinfo>
#include <boost/noncopyable.hpp>

//----------------------------------------------------------------------------------------------------------------------
/// @file Singleton.h
/// @brief a simple singleton template inherited by other classes
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// \class Singleton "include/ngl/Singleton.h"
/// @brief Singleton template
/// added to NGL framework 20/04/10 by jmacey
/// \author Vincent Bonnet
/// \version 1.0
/// \date 14/03/10 Last Revision 14/03/10
//----------------------------------------------------------------------------------------------------------------------

template <class T>


class  Singleton : private boost::noncopyable
{
public:

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Get the instance
  /// \returns the unique instance
  //----------------------------------------------------------------------------------------------------------------------

	static T* instance();

protected:

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor
  //----------------------------------------------------------------------------------------------------------------------
  Singleton();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Destructor
  //----------------------------------------------------------------------------------------------------------------------
  virtual ~Singleton();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief unique instance of the singleton
  //----------------------------------------------------------------------------------------------------------------------
  static T* s_instance;
};


template<class T> T*  Singleton<T>::s_instance = 0;
//----------------------------------------------------------------------------------------------------------------------
/// @brief Constructor -------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<class T> Singleton<T>::Singleton()
{ ; }

//----------------------------------------------------------------------------------------------------------------------
/// @brief Destructor ---------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

template<class T> Singleton<T>::~Singleton()
{
    if (s_instance)
    {
	      delete s_instance;
    }
}
//----------------------------------------------------------------------------------------------------------------------
/// @brief Get instance --------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<class T> T* Singleton<T>::instance()
{

    if (s_instance == 0)
    {
      s_instance = new T();
    }
    return static_cast<T*>(s_instance);

}



} // end ngl namespace

#endif // __SINGLETON_H__
//----------------------------------------------------------------------------------------------------------------------

