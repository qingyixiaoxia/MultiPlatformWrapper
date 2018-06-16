#ifndef MULTI_PLATFORM_SOCKET_FACTORY_H
#define MULTI_PLATFORM_SOCKET_FACTORY_H
#include "MP_Socket.h"
#include "MPCommon.h"

namespace MultiPlatformWrapper
{

class MP_SocketFactory
{
public:
	static MP_TCPSocket* createTCPSocket(MPBaseLibraryType platform);
	static MP_UDPSocket* createUDPSocket(MPBaseLibraryType platform);
};
}
#endif
