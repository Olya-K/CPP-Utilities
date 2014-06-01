/**  © 2014, Olga K. All Rights Reserved.
  *
  *  This file is part of the CPPUtilities Library.
  *  CPPUtilities is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  CPPUtilities is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with CPPUtilities.  If not, see <http://www.gnu.org/licenses/>.
  */

#include <windows.h>
#include <string>

/** @brief A class for creating WinAPI GUI windows easily.
 *
 */
class Window
{
    public:
        Window(LPCTSTR Title, LPCTSTR Class, DWORD dwStyleEx = 0, DWORD dwStyle = WS_OVERLAPPEDWINDOW,
                 POINT Location = {CW_USEDEFAULT, CW_USEDEFAULT}, int Width = CW_USEDEFAULT,
                 int Height = CW_USEDEFAULT, HWND Parent = HWND_DESKTOP, HMENU Menu = nullptr);

        int Loop();
		
	protected:
		virtual LRESULT RealWindowProcedure(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam) = 0;

    private:
        HWND WindowHandle;
        static LRESULT __stdcall WindowProcedure(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
};