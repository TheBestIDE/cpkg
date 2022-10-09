#include <stdlib.h>
#include <string.h>

#include "ip_layer.h"

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

    return ipp;
#undef BUF
}