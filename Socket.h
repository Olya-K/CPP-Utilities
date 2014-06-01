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

#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdint>
#include <string>
#include <cstring>
#include <stdexcept>
#include <thread>
#include <iostream>
#include <vector>
#include <bitset>

enum
{
    OP_NONE,
    OP_ACCEPT,
    OP_READ,
    OP_WRITE
};

class Socket
{
    private:
        SOCKET sock;
        std::string Address;
        std::uint16_t Port;

        void Init();
        void Connect();
        void ConnectAndListen();

    public:
        Socket(const char* Address, std::uint16_t Port, bool Listen = false);
        ~Socket();

        SOCKET get() {return sock;}
};