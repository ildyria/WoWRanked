#pragma once
#include <stdint.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;


typedef struct prog_options {
	uint8 num_proc_to_use;
	bool testing;

} prog_options;
