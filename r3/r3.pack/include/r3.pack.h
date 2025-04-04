#pragma once

#include <r3/r3.core/include/r3.defines.h>

#define R3_PACK_MAX ((1U << 8) - 1)

#define R3_PACK_METHOD(returns, name, ...) returns (*name)(__VA_ARGS__)
#define R3_PACK_API(name, ...)      \
    typedef struct name##_api {     \
        __VA_ARGS__                 \
    } name##_api                    \

#define R3_PACK_INIT(...)           \
    u8 _pack_init_impl(void) {      \
        __VA_ARGS__                 \
    }

#define R3_PACK_CLEANUP(...)            \
    u8 _pack_cleanup_impl(void) {       \
        __VA_ARGS__                     \
    }

#define R3_PACK_EXPORT(pack_api, ...)               \
    void* _pack_export_impl(void) {                 \
        static pack_api _api = { __VA_ARGS__ };     \
        return &_api;                               \
    }

typedef struct _r3_pack_api {
    void* (*load_pack)(char* name, char* path);
    void* (*get_pack)(char* name);
    u8 (*unload_pack)(char* name);
} _r3_pack_api;
extern _r3_pack_api* r3_pack;

u8 r3_init_pack(void* r3_core);
void r3_cleanup_pack(void);
