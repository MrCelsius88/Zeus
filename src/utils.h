/* date = October 5th 2022 1:30 pm */
#ifndef UTILS_H
#define UTILS_H

// NOTE(Cel): Typedefs
#include <stdint.h>
typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

#ifdef HANDMADE_MATH

// NOTE(Cel): Get rid of the prefix
typedef hmm_vec2 Vec2, V2;
typedef hmm_vec3 Vec3, V3;
typedef hmm_vec4 Vec4, V4;
typedef hmm_mat4 Mat4, M4;
typedef hmm_quaternion Quaternion;

#endif

#define Stringify_(s) #s
#define Stringify(s) Stringify_(s)

#define Glue_(a,b) a##b
#define Glue(a,b) Glue_(a,b)

#define ArrayCount(a) (sizeof(a) / sizeof(*(a)))

// NOTE(Cel): Refactored so that we can use this macro on pointers
// rather than assuming it is being used on an array with known
// length.
#define ForEach(array, elementCount, type, var) for (type* var = array; (var - array) < elementCount; var++) 

#define Min(a,b) (((a)<(b))?(a):(b))
#define Max(a,b) (((a)>(b))?(a):(b))
#define Clamp(a,x,b) (((x)<(a))?(a):\
((b)<(x))?(b):(x))
#define CLAMP_UPPER(a, b) MIN(a, b)
#define CLAMP_LOWER(a, b) MAX(a, b)
#define SIGN(x) (((x) > 0) - ((x) < 0))
#define SQUARE(a) ((a) * (a))

// https://github.com/bigrando420/thomas/blob/main/sauce/th_dump.h
#define PRINT_STRING(str) printf(str);
#define LOG(str, ...) { char output[256] = {0}; sprintf(output, str"\n", __VA_ARGS__); PRINT_STRING(output); }

#define PRINT_STRING_ERR(str) fprintf(stderr, str);
#define LOGERR(str, ...) { char output[256] = {0}; sprintf(output, str"\n", __VA_ARGS__); PRINT_STRING_ERR(output); }

#define global static
#define persist static
#define func static

// NOTE(Cel): Memory related functions
#include <string.h>
#define MemoryZero(p,z) memset((p), 0, (z))
#define MemoryZeroStruct(p) MemoryZero((p), sizeof(*(p)))
#define MemoryZeroArray(a) MemoryZero((a), sizeof(a))
#define MemoryZeroTyped(p,c) MemoryZero((p), sizeof(*(p))*(c))

#define MemoryMatch(a,b,z) (memcmp((a), (b), (z)) == 0)

#define MemoryCopy(d,s,z) memmove((d), (s), (z))
#define MemoryCopyStruct(d,s) MemoryCopy((d), (s), \
Min(sizeof(*(d)),sizeof(*(s))))
#define MemoryCopyArray(d,s) MemoryCopy((d),(s),Min(sizeof(s),sizeof(d)))
#define MemoryCopyTyped(d,s,c) MemoryCopy((d),(s), \
Min(sizeof(*(d)),sizeof(*(s)))*(c))

// NOTE(Cel): Color macros taken/"inspired" by 
// https://github.com/raysan5/raylib/blob/master/src/raylib.h

// NO COLOR PALLETE WAS IN MIND WHEN MAKING COLORS
// I just looked up the color RGB on google so obviously
// custom colors would need to be made to match a pallete

#ifndef HANDMADE_MATH
#error Need new color representation outside of handmade math!
#else

#define LIGHTGRAY  HMM_Vec4(211, 211, 211, 255)
#define GRAY       HMM_Vec4(128, 128, 128, 255)
#define DARKGRAY   HMM_Vec4(169, 169, 169, 255)
#define YELLOW     HMM_Vec4(255, 255, 0, 255)
#define GOLD       HMM_Vec4(255, 215, 0, 255)
#define ORANGE     HMM_Vec4(255, 165, 0, 255)
#define PINK       HMM_Vec4(255, 192, 203, 255)
#define RED        HMM_Vec4(255, 0, 0, 255)
#define MAROON     HMM_Vec4(128, 0, 0, 255)
#define GREEN      HMM_Vec4(0, 255, 0, 255)
#define LIME       HMM_Vec4(50, 205, 50, 255)
#define DARKGREEN  HMM_Vec4(0, 100, 0, 255)
#define SKYBLUE    HMM_Vec4(135, 206, 235, 255)
#define BLUE       HMM_Vec4(0, 0, 255, 255)
#define DARKBLUE   HMM_Vec4(0, 0, 139, 255)
#define VIOLET     HMM_Vec4(127, 0, 255, 255)
#define DARKPURPLE HMM_Vec4(48, 25, 52, 255)
#define BEIGE      HMM_Vec4(245, 245, 220, 255)
#define BROWN      HMM_Vec4(150, 75, 0, 255)
#define DARKBROWN  HMM_Vec4(92, 64, 51, 255)
#define WHITE      HMM_Vec4(255, 255, 255, 255)
#define BLACK      HMM_Vec4(0, 0, 0, 255)
#define BLANK      HMM_Vec4(0, 0, 0, 0)
#define MAGENTA    HMM_Vec4(255, 0, 255, 255)

#endif

func inline bool
PowerOfTwo(uintptr_t x) { return (x & (x - 1)) == 0; }

#endif //UTILS_H