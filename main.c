#include <stdio.h>
#include <stdlib.h>
#include "cpkg_api.h"

void prt_ip_pkg(ip_pkg* ippkg) {
    printf("------ IP数据包开始 ------\n");
    printf("版本:%u, 首部长度:%u, 区分服务:%u, 总长度:%u\n",
            ippkg->version, ippkg->hlen, ippkg->tos, ippkg->tlen);
    printf("标识:%u, 标志%u %u %u, 片偏移:%u\n",
            ippkg->idtf, ippkg->f1, ippkg->f2, ippkg->f3, ippkg->offset);
    printf("生存时间:%u, 协议:%u(%s)\n",
            ippkg->ttl, ippkg->proto, get_ip_header_proto(ippkg->proto));
    printf("源地址:%u.%u.%u.%u\n目的地址:%u.%u.%u.%u\n",
            ippkg->source_addr[0], ippkg->source_addr[1], ippkg->source_addr[2], ippkg->source_addr[3],
            ippkg->target_addr[0], ippkg->target_addr[1], ippkg->target_addr[2], ippkg->target_addr[3]);
    const char* dat_str = to_str_mbuffer(ippkg->data);
    // printf("数据部分:\n%s\n", dat_str);
    printf("------ IP数据包结束 ------\n\n");
}

int main(int args, char* argv[]) {
    if (args > 2) {
        printf("Too many arguments.\n");
        return -1;
    }

    int loop = atoi(argv[1]);
    if (loop == 0) {
        printf("Accept argument type int, but get(%s).\n", argv[1]);
        return -1;
    }

    // init cpkg
    cpkg_t cpkg = init_cpkg(CPKG_ETH_SOCK);

    int i = 0;
    for (i = 0; i < loop; i++) {
        ip_pkg* ippkg = rcv_ippkg_cpkg(cpkg);
        prt_ip_pkg(ippkg);
        free_ip_pkg(ippkg);
    }

    close_cpkg(cpkg);
    return 0;
}