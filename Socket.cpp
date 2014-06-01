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

Socket::Socket(const char* Address, std::uint16_t Port, bool Listen) : sock(0), Address(Address), Port(Port)
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        throw std::runtime_error("Error: WSAStartup Failed");
    }

    Init();

    if (Listen)
        ConnectAndListen();
    else
        Connect();
}

Socket::~Socket()
{
    shutdown(sock, SD_BOTH);
    closesocket(sock);
    WSACleanup();
    sock = 0;
}

void Socket::Init()
{
    struct sockaddr_in* sockaddr_ipv4;

    if (Address != "INADDR_ANY")
    {
        if (Address.find("https://") != std::string::npos)
        {
            Address = Address.substr(8);
        }

        if (Address.find("http://") != std::string::npos)
        {
            Address = Address.substr(7);
        }

        std::size_t Position = Address.find("/");
        if (Position != std::string::npos)
        {
            Address = Address.substr(0, Position);
        }

        struct addrinfo* it = nullptr, *result = nullptr;
        getaddrinfo(Address.c_str(), nullptr, nullptr, &result);
        for (it = result; it != nullptr; it = it->ai_next)
        {
            sockaddr_ipv4 = reinterpret_cast<sockaddr_in*>(it->ai_addr);
            Address = inet_ntoa(sockaddr_ipv4->sin_addr);
            if (Address != "0.0.0.0") break;
        }
        freeaddrinfo(result);
    }

    if ((this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        throw std::runtime_error("Error: Failed to create socket");
    }
}

void Socket::Connect()
{
    struct sockaddr_in SockAddr;
    std::memset(&SockAddr, 0, sizeof(SockAddr));
    SockAddr.sin_port = htons(Port);
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_addr.s_addr = (Address == "INADDR_ANY" ? htonl(INADDR_ANY) : inet_addr(Address.c_str()));

    if (connect(this->sock, reinterpret_cast<SOCKADDR*>(&SockAddr), sizeof(SockAddr)) == SOCKET_ERROR)
    {
        throw std::runtime_error("Error: Failed to connect socket");
    }
}

void Socket::ConnectAndListen()
{
    struct sockaddr_in SockAddr;
    std::memset(&SockAddr, 0, sizeof(SockAddr));
    SockAddr.sin_port = htons(Port);
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_addr.s_addr = (Address == "INADDR_ANY" ? htonl(INADDR_ANY) : inet_addr(Address.c_str()));

    if (bind(this->sock, reinterpret_cast<SOCKADDR*>(&SockAddr), sizeof(SockAddr)) == SOCKET_ERROR)
    {
        throw std::runtime_error("Error: Failed to bind socket");
    }

    if (listen(this->sock, SOMAXCONN) == SOCKET_ERROR)
    {
        throw std::runtime_error("Error: Failed to listen on socket");
    }

    if (connect(this->sock, reinterpret_cast<SOCKADDR*>(&SockAddr), sizeof(SockAddr)) == SOCKET_ERROR)
    {
        throw std::runtime_error("Error: Failed to connect socket");
    }
}