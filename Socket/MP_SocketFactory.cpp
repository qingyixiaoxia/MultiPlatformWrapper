#include "MP_SocketFactory.h"
#include "MP_SocketLinuxImpl.h"
#include "MP_SocketWin32Impl.h"

namespace MultiPlatformWrapper
{

MP_TCPSocket* MP_SocketFactory::createTCPSocket(MPBaseLibraryType platform)
{
    switch (platform)
    {
        #if defined (LINUX)
        case MP_BASE_LIBRARY_LINUX:
			return new MP_TCPSocketLinuxImpl();
			break;
		#endif
		#if defined (WIN32)
		case MP_BASE_LIBRARY_WIN32:
			return new MP_TCPSocketWin32Impl();
			break;
		#endif

		default:
			return NULL;
    }
}

MP_UDPSocket* MP_SocketFactory::createUDPSocket(MPBaseLibraryType platform)
{
    switch (platform)
    {
        #if defined (LINUX)
        case MP_BASE_LIBRARY_LINUX:
			return new MP_UDPSocketLinuxImpl();
			break;
		#endif

        #if defined (WIN32)			
		case MP_BASE_LIBRARY_WIN32:
			return new MP_UDPSocketWin32Impl();
			break;
		#endif

		default:
			return NULL;
    }
}
}
