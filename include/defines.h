#pragma once

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef float f32;
typedef float f64;
typedef int b32;
typedef char b8;

static_assert(sizeof(unsigned char) == 1);
static_assert(sizeof(unsigned short) == 2);
static_assert(sizeof(unsigned int) == 4);
static_assert(sizeof(unsigned long long) == 8);

static_assert(sizeof(char) == 1);
static_assert(sizeof(short) == 2);
static_assert(sizeof(int) == 4);
static_assert(sizeof(long long) == 8);

static_assert(sizeof(float) == 4);
static_assert(sizeof(double) == 8);

#ifndef _WIN64
#error "Compiling With 64 Bit Is Required"
#endif

#define MODE_DEBUG
