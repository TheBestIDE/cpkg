#pragma once

#include "ab_socket_if.h"
#include "link_layer.h"
#include "ip_layer.h"

struct cpkg_s {
    socket_id_t sock_id;
    int w_layer;
};

typedef struct cpkg_s* cpkg_t;

cpkg_t init_cpkg(int layer);
void close_cpkg(cpkg_t cpkg);
void set_promisc_cpkg(cpkg_t cpkg, char* eth_name);
void reset_promisc_cpkg(cpkg_t cpkg, char* eth_name);
eth_frame* rcv_frame_cpkg(cpkg_t cpkg);
ip_pkg* rcv_ippkg_cpkg(cpkg_t cpkg);

#define CPKG_ETH_SOCK SOCK_USE_ETH
#define CPKG_IP_SOCK SOCK_USE_IP