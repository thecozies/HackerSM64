#ifndef __PROFILING_H__
#define __PROFILING_H__

#include <ultra64.h>
#include "macros.h"

#define PROFILING_BUFFER_SIZE 64

enum ProfilerTime {
    PROFILER_TIME_FPS,
    PROFILER_TIME_CONTROLLERS,
    PROFILER_TIME_LEVEL_SCRIPT,
    PROFILER_TIME_TERRAIN,
    PROFILER_TIME_OBJECTS,
    PROFILER_TIME_GFX,
    PROFILER_TIME_TOTAL,
    PROFILER_TIME_TMEM,
    PROFILER_TIME_PIPE,
    PROFILER_TIME_CMD,
    PROFILER_TIME_RSP_GFX,
    PROFILER_TIME_RSP_AUDIO,
    PROFILER_TIME_COUNT,
};

enum ProfilerRSPTime {
    PROFILER_RSP_GFX,
    PROFILER_RSP_AUDIO,
    PROFILER_RSP_COUNT
};

void fast_profiler_update(enum ProfilerTime which);
void fast_profiler_print_times();
void fast_profiler_frame_setup();
void fast_profiler_rsp_started(enum ProfilerRSPTime which);
void fast_profiler_rsp_completed(enum ProfilerRSPTime which);
void fast_profiler_rsp_resumed();
// See profiling.c to see why fast_profiler_rsp_yielded isn't its own function
static ALWAYS_INLINE void fast_profiler_rsp_yielded() {
    fast_profiler_rsp_resumed();
}

#endif