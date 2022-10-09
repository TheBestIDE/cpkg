/*
 * This file includes header files
 * for the abstract socket.
*/

#pragma once

#include <stdio.h>

#ifdef __linux__
    // Linux platform
    #include <sys/ioctl.h>
    #include <sys/types.h>
    #include <netinet/if_ether.h>

    #include <linux/if_packet.h>

    // ---- accept layer ----
    #define NET_LAYER_ETH PF_PACKET // link layer
    #define NET_LAYER_IP AF_INET    // ip layer

    // ---- accpet protocol ----
    // protocol in ETH link layer
    #define PROTO_ETH_ALL htons(ETH_P_ALL)  // accept all protocol package

    // protocol in ip layer
    #define PROTO_IP_ALL IPPROTO_TCP | IPPROTO_UDP | IPPROTO_ICMP
    #define PROTO_IP_ICMP IPPROTO_ICMP
    #define PROTO_IP_TCP IPPROTO_TCP
    #define PROTO_IP_UDP IPPROTO_UDP

#elif __APPLE__
    // Apple platform
    #include <sys/ioctl.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <net/if.h>
    #include <netinet/in.h>
    #include <netinet/if_ether.h>

#elif _WIN32
    // Windows 32-bits or 64-bits
    #include <winsock.h>
    
    #ifdef _WIN64
        // Windows 64-bits only
    #else
        // Windows 32-bits only

    #endif

#else
    #error No Support Platform
#endif
