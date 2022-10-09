#include <stdio.h>
#include <stdlib.h>

#include "cpkg_api.h"
#include "mbuffer.h"

#define BUF_SIZ 1600
#define SOCK_BUF_SIZ 1 << 21

cpkg_t init_cpkg(int layer) {
    cpkg_t cpkg = malloc(sizeof(struct cpkg_s));
    cpkg->sock_id = absocket(layer);
    set_sock_rcvbuf_size(cpkg->sock_id, SOCK_BUF_SIZ);
    return cpkg;
}

void close_cpkg(cpkg_t cpkg) {
    close_absocket(cpkg->sock_id);
}

void set_promisc_cpkg(cpkg_t cpkg, char* eth_name) {
    SET_ETH_PROMISC(cpkg, eth_name);
}

void reset_promisc_cpkg(cpkg_t cpkg, char* eth_name) {
    RESET_ETH_MODE(cpkg, eth_name);
}

eth_frame* rcv_frame_cpkg(cpkg_t cpkg) {
    if (cpkg->w_layer != CPKG_ETH_SOCK) {
        perror("cpkg object is not work in eth layer.\n");
        return NULL;
    }

    char* buf = malloc(BUF_SIZ * sizeof(char));
    size_t dat_sz = recv_socket(cpkg->sock_id, buf, BUF_SIZ);
    mbuffer* mbuf = malloc(sizeof(mbuffer));
    mbuf->caps = BUF_SIZ;
    mbuf->len = dat_sz;
    mbuf->buf = buf;
    eth_frame* ef = anlys_frame(mbuf);
    free_mbuffer(mbuf);
    return ef;
}

ip_pkg* rcv_ippkg_cpkg(cpkg_t cpkg) {
    char* buf = malloc(BUF_SIZ * sizeof(char));
    size_t dat_sz = recv_socket(cpkg->sock_id, buf, BUF_SIZ);
    mbuffer* mbuf = malloc(sizeof(mbuffer));
    mbuf->caps = BUF_SIZ;
    mbuf->len = dat_sz;
    mbuf->buf = buf;

    if (cpkg->w_layer == CPKG_ETH_SOCK) {
        eth_frame* ef = anlys_frame(mbuf);
        free_mbuffer(mbuf);
        mbuf = ef->data;
        free(ef);
    }

    ip_pkg* pkg = anlys_package(mbuf);
    free_mbuffer(mbuf);
    return pkg;
}