#include <stdio.h>
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
    if (mb->buf == NULL) {
        printf("memery buffer alloc failed, exit.\n");
        exit(-1);
    }
    memset(mb->buf, 0, len * sizeof(byte));
    mb->caps = len;
    return mb;
}

void realloc_mbuffer(mbuffer* mb, size_t len) {
    realloc(mb->buf, len * sizeof(byte));
    mb->len = len;
    mb->caps = len;
}

void free_mbuffer(mbuffer* mb) {
    if (mb != NULL) {
        if (mb->buf != NULL)
            free(mb->buf);
        free(mb);
    }
}

const char* to_str_mbuffer(mbuffer* mb) {
#define BUF mb->buf
    if (mb == NULL || BUF == NULL || mb->len == 0)
        return "";
    int str_len = mb->len * 3 + 1;
    char* str = malloc(str_len);

    char* str_sk = str;
    int i = 0;
    int cplt_r = mb->len >> 4;
    for (i = 0; i < cplt_r; i++) {
        int j = 0;
        for (j = 0; j < 16; j++) {
            sprintf(str_sk, "%02X ", BUF[(i << 4) + j]);
            str_sk += 3;
        }
        *(str_sk - 1) = '\n';
    }
    int lst_r = cplt_r << 4;
    for (i = 0; i < mb->len & 0xF; i++) {
        sprintf(str_sk, "%X", BUF[lst_r + i]);
        str_sk += 3;
    }
    *(str_sk - 1) = 0;

    str[str_len -1] = 0;
    return str;
#undef BUF
}