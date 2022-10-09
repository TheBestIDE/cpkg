#include <stdlib.h>
#include <string.h>
#include "link_layer.h"

/// @brief analysis bytes of data frame to struct frame
/// @param frame 
/// @return 
eth_frame* anlys_frame(mbuffer* frame) {
    // MAC Frame size >= 64 bytes
    if (frame->len < 64)
        return NULL;

    eth_frame* eframe = malloc(sizeof(eth_frame));
    eframe->data = init_size_mbuffer(frame->len - ETH_ADD_LEN);

    // target address 6B
    memcpy(eframe->target_addr, frame->buf, 6);
    // source address 6B
    memcpy(eframe->source_addr, frame->buf + 6, 6);
    // pattern 2B
    eframe->pattern = frame->buf[12] << 8;
    eframe->pattern |= frame->buf[13];

    // data from 15B ~ -4B, the last 4B is FCS
    memcpy(eframe->data->buf, frame->buf + 14, frame->len - ETH_ADD_LEN);
    eframe->data->len = frame->len - ETH_ADD_LEN;

    return eframe;
}

void free_eth_frame(eth_frame* frame) {
    if (frame != NULL) {
        if (frame->data != NULL)
            free_mbuffer(frame->data);
        free(frame);
    }
}