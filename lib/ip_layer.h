#pragma once
#include "mbuffer.h"

struct ip_package {
    byte version;   // 版本 4b
    byte hlen;      // 首部长度 4b, 数据报头该部分表示32位字长，故该字段在数据报头部字段基础上*4
    byte tos;       // 区分服务 8b
    unsigned short tlen;    // 总长度 16b

    unsigned short idtf;    // 标识 16b
    byte f1;   // 标志1 1b
    byte f2;   // 标志2 1b
    byte f3;   // 标志3 1b
    unsigned short offset;  // 片偏移 13b

    byte ttl;   // 生存时间 8b
    byte proto; // 协议 8b
    unsigned short checksum;    // 首部校验和 16b

    byte source_addr[4];    // 源地址 32b
    byte target_addr[4];    // 目的地址 32b

    mbuffer* options;   // 选项 0 - 40b
    mbuffer* data;      // 数据
};

typedef struct ip_package ip_pkg;

