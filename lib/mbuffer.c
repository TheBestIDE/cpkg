#include <stdlib.h>
#include <string.h>
#include "mbuffer.h"

mbuffer* init_mbuffer() {
    init_size_mbuffer(32);
}

mbuffer* init_size_mbuffer(size_t len) {
    mbuffer* mb = malloc(sizeof(mbuffer));
    mb->len = 0;
    mb->buf = malloc(len * sizeof(byte));
    memset(mb->buf, 0, len);
    mb->caps = len;
}

void realloc_mbuffer(mbuffer* mb, size_t len) {
    realloc(mb->buf, len * sizeof(byte));
    mb->len = len;
    mb->caps = len;
}