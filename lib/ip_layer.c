#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ip_layer.h"

#define PROTO_ARRY_NUM 90
static const char* ip_hp[PROTO_ARRY_NUM] = { NULL };

ip_pkg* anlys_package(mbuffer* package) {
    if (package->len < 20)
        return NULL;
    ip_pkg* ipp = malloc(sizeof(ip_pkg));

#define BUF package->buf

    ipp->version = BUF[0] >> 4;
    ipp->hlen = (BUF[0] & 0xF) << 2;
    ipp->tos = BUF[1];
    ipp->tlen = (BUF[2] << 8) | BUF[3];

    ipp->idtf = (BUF[4] << 8) | BUF[5];
    ipp->f1 = (BUF[6] >> 7) & 0x1;
    ipp->f2 = (BUF[6] >> 6) & 0x1;
    ipp->f3 = (BUF[6] >> 5) & 0x1;
    ipp->offset = (BUF[6] & 0x1F) << 8 | BUF[7];

    ipp->ttl = BUF[8];
    ipp->proto = BUF[9];
    ipp->checksum = (BUF[10] << 8) | BUF[11];

    memcpy(ipp->source_addr, BUF + 12, 4);
    memcpy(ipp->target_addr, BUF + 16, 4);

    byte opt_len = ipp->hlen - 20u;
    ipp->options = NULL;
    if (opt_len != 0) {
        ipp->options = init_size_mbuffer(opt_len);
        memcpy(ipp->options->buf, BUF + 20, opt_len);
    }
    ipp->data = init_size_mbuffer(package->len - ipp->hlen);
    memcpy(ipp->data->buf, BUF + ipp->hlen, package->len - ipp->hlen);
    ipp->data->len = package->len - ipp->hlen;
    return ipp;
#undef BUF
}

void free_ip_pkg(ip_pkg* pkg) {
    if (pkg != NULL) {
        if (pkg->options != NULL)
            free_mbuffer(pkg->options);
        if (pkg->data != NULL)
            free_mbuffer(pkg->data);
        free(pkg);
    }
}

void init_proto_arry() {
    ip_hp[1] = "ICMP";
    ip_hp[2] = "IGMP";
    ip_hp[4] = "IP";
    ip_hp[6] = "TCP";
    ip_hp[8] = "EGP";
    ip_hp[9] = "IGP";
    ip_hp[17] = "UDP";
    ip_hp[41] = "IPv6";
    ip_hp[50] = "ESP";
    ip_hp[89]= "OSPF";
}

const char* get_ip_header_proto(byte proto) {
    const char* proto_str = NULL;
    static char is_init = 0;
    if (!is_init) {
        init_proto_arry();
        is_init = 1;
    }

    if (proto < PROTO_ARRY_NUM)
        proto_str = ip_hp[proto];
    
    return proto_str == NULL ? "Unknow" : proto_str;
}