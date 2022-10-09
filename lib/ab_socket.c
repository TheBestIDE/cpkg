#include "ab_socket.h"

socket_id_t ab_socket() {
    socket_id_t socketid = -1;
    #ifdef __linux__
    socketid = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    #elif __APPLE__

    #elif _WIN32

    #endif

    return socketid;
}

void set_eth_mode(socket_id_t sock, char* eth_name, eth_mode_t mode) {
    #ifdef __linux__
    struct ifreq ethreq;
    strncpy(ethreq.ifr_name, eth_name, IFNAMSIZ)
    ethreq.ifr_flags = |= ETH_PROMISC;
    ioctl(sock, SIOCGIFFLAGS, ethreq);
    #endif
}

size_t recv_socket(socket_id_t sock, char* buffer, size_t buf_sz, size_t buf_st) {
    size_t len = 0;
    #ifdef __linux__
    len = recvfrom(sock, buffer, buf_sz, buf_st, NULL, NULL);
    #endif

    return len;
}