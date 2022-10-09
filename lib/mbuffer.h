#pragma once
#include <stddef.h>

typedef unsigned char byte; 

struct member_buffer {
    size_t len;
    size_t caps;
    byte* buf;
};

typedef struct member_buffer mbuffer;

mbuffer* init_mbuffer();
mbuffer* init_size_mbuffer(size_t len);
void realloc_mbuffer(mbuffer* mb, size_t len);