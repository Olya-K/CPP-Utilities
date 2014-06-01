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

Window::Window(LPCTSTR Title, LPCTSTR Class, DWORD dwStyleEx, DWORD dwStyle, POINT Location, int Width, int Height, HWND Parent, HMENU Menu)
{
    WNDCLASSEX WndClass =
    {
        sizeof(WNDCLASSEX), CS_DBLCLKS, Window::WindowProcedure,
        0, 0, GetModuleHandle(nullptr), LoadIcon(nullptr, IDI_APPLICATION),
        LoadCursor(nullptr, IDC_ARROW), HBRUSH(COLOR_BACKGROUND),
        nullptr, Class, LoadIcon(nullptr, IDI_APPLICATION)
    };

    if(RegisterClassEx(&WndClass))
    {
        WindowHandle = CreateWindowEx(dwStyleEx, Class, Title, dwStyle, Location.x, Location.y, Width, Height, Parent, Menu, GetModuleHandle(nullptr), this);
    }
}

LRESULT __stdcall Window::WindowProcedure(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    Window* Data = nullptr;

    switch(Msg)
    {
        case WM_NCCREATE:
            {
                CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
                Data = static_cast<Window*>(pCreate->lpCreateParams);
                SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(Data));
                break;
            }

        default:
            {
                Data = reinterpret_cast<Window*>(GetWindowLongPtr(Hwnd, GWLP_USERDATA));
                break;
            }
    }

    return Data ? Data->RealWindowProcedure(Hwnd, Msg, wParam, lParam) : DefWindowProc(Hwnd, Msg, wParam, lParam);
}

int Window::Loop()
{
    MSG Messages = {nullptr};
    ShowWindow(WindowHandle, SW_SHOW);
    while(GetMessage(&Messages, nullptr, 0, 0))
    {
        TranslateMessage(&Messages);
        DispatchMessage(&Messages);
    }
    return Messages.wParam;
}