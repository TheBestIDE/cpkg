#include "ab_socket.h"
#include "ab_socket_if.h"

/// @brief Create a abstract socket object from different kernal for receiving all data package.
/// @return socket id
socket_id_t absocket() {
    socket_id_t socketid = -1;
    #ifdef __linux__
    socketid = socket(NET_LAYER_ETH, SOCK_RAW, PROTO_ETH_ALL);

    #elif __APPLE__
    socketid = socket(NET_LAYER_ETH, SOCK_RAW, PROTO_ETH_ALL);

    #elif _WIN32

    #endif

    return socketid;
}

/// @brief Set eth mode.
/// @param sock socket id
/// @param eth_name network interface(eth) name
/// @param mode eth mode
void set_eth_mode(socket_id_t sock, char* eth_name, eth_mode_t mode) {
    #ifdef __linux__
    struct ifreq ethreq;
    strncpy(ethreq.ifr_name, eth_name, IFNAMSIZ);
    ethreq.ifr_flags |= mode;
    ioctl(sock, SIOCSIFFLAGS, &ethreq);

    #elif __APPLE__
    perror("Not support for MacOS.\n");
    #endif
}

/// @brief Unset eth mode.
/// @param sock socket id
/// @param eth_name network interface(eth) name
/// @param mode eth mode
void unset_eth_mode(socket_id_t sock, char* eth_name, eth_mode_t mode) {
    #ifdef __linux__
    struct ifreq ethreq;
    strncpy(ethreq.ifr_name, eth_name, IFNAMSIZ);
    ioctl(sock, SIOCGIFFLAGS, &ethreq);
    ethreq.ifr_flags &= ~mode;
    ioctl(sock, SIOCSIFFLAGS, &ethreq);

    #elif __APPLE__
    perror("Not support for MacOS.\n");
    #endif
}

/// @brief Get socket size of receive buffer
/// @param sock socket id
/// @return buffer size
size_t get_sock_rcvbuf_size(socket_id_t sock) {
    size_t len = 0;
    #ifdef __linux__
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &len, sizeof(size_t));

    #endif

    return len;
}

/// @brief Set socket size of receive buffer
/// @param sock socket id
/// @param buf_sz buffer size
void set_sock_rcvbuf_size(socket_id_t sock, size_t buf_sz) {
    #ifdef __linux__
    setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &buf_sz, sizeof(size_t));
    #endif
}

/// @brief Receive bytes from socket.
/// @param sock socket id
/// @param buffer buffer to save bytes
/// @param buf_sz buffer max size
/// @return number of received bytes
size_t recv_socket(socket_id_t sock, char* buffer, size_t buf_sz) {
    size_t len = 0;
    #ifdef __linux__
    len = recvfrom(sock, buffer, buf_sz, 0, NULL, NULL);
    #endif

    return len;
}