/*
  Copyright (C) 2012 Jon Macey

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
#ifndef MOUSE_H__
#define MOUSE_H__
//----------------------------------------------------------------------------------------------------------------------
/// @file Vec4.h
/// @brief a simple 4D vector class
//----------------------------------------------------------------------------------------------------------------------


#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <fcntl.h>
namespace ngl
{
class Mouse
{
	public :
		/// @brief mouse ctor
		/// @param[in] _w the screen width
		/// @param[in] _h the screen height

		Mouse(int _w, int _h);
		/// @brief dtor
		~Mouse();
		/// @brief get the mouse x,y position
		/// @param[out] _x the x position relative to screen dimensions
		/// @param[out] _y the y position relative to screen dimensions
		void getXY(int &_x, int &_y);
		/// @brief get the left mouse button state
		/// @returns true if pressed
		inline bool getLeft(){updateButtons(); return m_left;}
		/// @brief get the Right mouse button state
		/// @returns true if pressed
		inline bool getRight(){updateButtons(); return m_right;}
		/// @brief get the Middle mouse button state
		/// @returns true if pressed
		inline bool getMiddle(){updateButtons(); return m_middle;}

	private :

	/// @brief file pointer to the mouse, opened by the ctor closed by the dtor
	int m_mouse;
	/// @brief the current window width
	int m_width;
	/// @brief the current window height
	int m_height;
	/// @brief method to update the mouse button state, called when getButton methods called
	void updateButtons();
	/// @brief the left mouse button state
	bool m_left;
	/// @brief the right mouse button state
	bool m_right;
	/// @brief the middle mouse button state
	bool m_middle;


};
} // end namespace

#endif