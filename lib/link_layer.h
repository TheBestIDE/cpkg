#pragma once
#include "mbuffer.h"

struct ethernet_frame {
    byte target_addr[6];
    byte source_addr[6];
    unsigned short pattern; // two bytes
    mbuffer* data;
};

typedef struct ethernet_frame eth_frame;

#define ETH_ADD_LEN 18  // additional length in eth frame = 6+6+2+4
#define ETH_PATTERN_IP 0x0800

eth_frame* anlys_frame(mbuffer* frame);
