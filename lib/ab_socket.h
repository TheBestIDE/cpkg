#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
    // Linux platform
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <netinet/if_ether.h>

    #include <linux/if_ether.h>
    #include <linux/if_packet.h> 

    typedef int socket_id_t;
    typedef int eth_mode_t;

    #define ETH_PROMISC IFF_PROMISC // promiscuous mode

#elif __APPLE__
    // Apple platform
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <sys/_endian.h>
    #include <netinet/in.h>

    typedef int socket_id_t;
    typedef int eth_mode_t;

    #define ETH_PROMISC 0   // proimiscuous mode

#elif _WIN32
    // Windows 32-bits or 64-bits
    typedef int socket_id_t;
    typedef int eth_mode_t;

    #define ETH_PROMISC 0   // proimiscuous mode
    
    #ifdef _WIN64
        // Windows 64-bits only
    #else
        // Windows 32-bits only

    #endif

#else
    #error No Support Platform
#endif

int ab_socket();
