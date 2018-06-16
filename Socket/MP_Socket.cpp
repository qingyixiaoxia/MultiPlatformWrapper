#include "MP_Socket.h"
#if defined (WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

namespace MultiPlatformWrapper
{
bool MP_Socket::initEnviroment()
{
#if defined (WIN32)
	WORD wVersionRequested = MAKEWORD(1,1);
    WSADATA wsaData; 
	if (::WSAStartup(wVersionRequested,&wsaData) != 0)
	{
		return false;
	}
	return true;

#elif defined (LINUX)
    // Nothing todo 

#endif
    return true;
}

bool MP_Socket::terminateEnviroment()
{
#if defined (WIN32)
    WSACleanup();
    return true;

#elif defined (LINUX)
    // Nothing todo 

#endif

    return true;
}
}
