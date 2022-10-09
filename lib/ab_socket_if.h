/*
 * This file declare interface for
 * using the abstract socket.
*/

#pragma once

#include <unistd.h>

#ifdef __linux__
    // Linux platform
    #include <sys/socket.h>
    #include <net/if.h>
    #include <netinet/in.h>
    #include <linux/if_ether.h>

    typedef int socket_id_t;
    typedef int eth_mode_t;

    // ETH mode
    #define ETH_MODE_PROMISC IFF_PROMISC    // promiscuous mode

#elif __APPLE__
    // Apple platform
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

#define SOCK_USE_ETH 0
#define SOCK_USE_IP 1

socket_id_t absocket(int sock_layer);
#define close_absocket(sock) close(sock);
size_t recv_socket(socket_id_t sock, char* buffer, size_t buf_sz);

void set_eth_mode(socket_id_t sock, char* eth_name, eth_mode_t mode);
void unset_eth_mode(socket_id_t sock, char* eth_name, eth_mode_t mode);
#define SET_ETH_PROMISC(sock, eth_name) set_eth_mode(sock, eth_name, ETH_MODE_PROMISC)
#define RESET_ETH_MODE(sock, eth_name) unset_eth_mode(sock, eth_name, ETH_MODE_PROMISC)

size_t get_sock_rcvbuf_size(socket_id_t sock);
void set_sock_rcvbuf_size(socket_id_t sock, size_t buf_sz);