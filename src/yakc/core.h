#pragma once
//------------------------------------------------------------------------------
/**
    @file yakc/core.h
    @brief yakc core definitions
*/
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

namespace YAKC {

typedef unsigned char ubyte;
typedef signed char byte;
typedef unsigned short uword;
typedef signed short word;

struct ext_funcs {
    void (*assertmsg_func)(const char* cond, const char* msg, const char* file, int line, const char* func) = nullptr;
    void* (*malloc_func)(size_t) = nullptr;
    void (*free_func)(void*) = nullptr;
};

/// jump table for externally provided functions
extern struct ext_funcs func;
/// helper to clear a chunk of memory
extern void clear(void* ptr, int num_bytes);
/// helper to fill a chunk of memory with random noise
extern void fill_random(void* ptr, int num_bytes);

/// sound callback functions
struct sound_funcs {
    /// userdata field
    void* userdata = nullptr;
    /// start or update sound
    void (*sound)(void* userdata, uint64_t cycle_count, int channel, int hz) = nullptr;
    /// stop sound
    void (*stop)(void* userdata, uint64_t cycle_count, int channel) = nullptr;
    /// set volume
    void (*volume)(void* userdata, uint64_t cycle_count, int vol) = nullptr;
};

#define YAKC_MALLOC(s) func.malloc_func(s)
#define YAKC_FREE(p) func.free_func(p)

#if __clang_analyzer__
#include <assert.h>
#define YAKC_ASSERT(cond) assert(cond)
#else
#if !(__GNUC__ || __GNUC__)
// on Visual Studio, replace __PRETTY_FUNCTION__ with __FUNCSIG__
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#define YAKC_ASSERT(cond) do { if(!(cond)) { func.assertmsg_func(#cond,nullptr,__FILE__,__LINE__,__PRETTY_FUNCTION__); abort(); } } while(0)
#endif

enum class device {
    kc85_2   = (1<<0),
    kc85_3   = (1<<1),
    kc85_4   = (1<<2),
    z1013_01 = (1<<3),
    z1013_16 = (1<<5),
    z1013_64 = (1<<6),
    z9001    = (1<<7),
    kc87     = (1<<8),
    none = 0,
    any_kc85 = (kc85_2|kc85_3|kc85_4),
    any_z1013 = (z1013_01|z1013_16|z1013_64),
    any_z9001 = (z9001|kc87)
};

enum class os_rom {
    caos_hc900,
    caos_2_2,
    caos_3_1,
    caos_3_4,
    caos_4_1,
    caos_4_2,
    z1013_mon202,
    z1013_mon_a2,
    z9001_os_1_2,
    kc87_os_2,
    none,
};

} // namespace YAKC
