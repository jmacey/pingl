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
#include "Mouse.h"
namespace ngl
{
Mouse::Mouse(int _w, int _h)
{
	m_width=_w;
	m_height=_h;
	m_left=0;
	m_right=0;
	m_middle=0;

	m_mouse= open("/dev/input/mouse0",O_RDONLY|O_NONBLOCK);
	if(m_mouse == 0)
	{
		std::cerr<<"error opening mouse \n";
		exit(EXIT_FAILURE);
	}
}

Mouse::~Mouse()
{
	// release the mouse
	close(m_mouse);

}


void Mouse::updateButtons()
{
	struct {char buttons, dx, dy;  } m;
	if (m_mouse>=0)
	{
		while (1)
		{

			int bytes = read(m_mouse, &m, sizeof m);
			if (bytes < (int)sizeof m)
			{
				m_left=((m.buttons>>0)&1);
				m_right=((m.buttons>>1)&1);
				m_middle=((m.buttons>>2)&1);
				//for(int i=8;i>=0;i--){  int bit=((m.buttons>>i)&1);  std::cout<<bit;}std::cout<<std::endl;
				//std::cout<<"mouse "<<m_left<<" "<<m_right<<" "<<m_middle<<"\n";
				break;
			}
			read(m_mouse, &m, 1); // Try to sync up again

		}
	}
}

// this is taken from one of the demos I will eventually re-write it to
// work using an even model
void Mouse::getXY(int &_x, int &_y)
{
	static int x=m_width, y=m_height;
	const int XSIGN = 1<<4, YSIGN = 1<<5;
	if (m_mouse>=0)
	{
		struct {char buttons, dx, dy; } m;
		while (1)
		{
			int bytes = read(m_mouse, &m, sizeof m);

			if (bytes < (int)sizeof m) goto _exit;
			if (m.buttons&8)
			{
				break; // This bit should always be set
			}
			read(m_mouse, &m, 1); // Try to sync up again
		}



	x+=m.dx;
	y+=m.dy;
	if (m.buttons&XSIGN)
		x-=256;
	if (m.buttons&YSIGN)
		y-=256;
	if (x<0) x=0;
	if (y<0) y=0;
	if (x>m_width) x=m_width;
	if (y>m_height) y=m_height;
	}

	_exit:
	if (x) _x = x;
	if (y) _y = y;
}

}// end namespace