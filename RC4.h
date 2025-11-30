/*RC4.h
NOTE works on windows and linux distributions
This is an encryption library, largely based on the RC4 encryption library. It does however make improvements for security.
This is achieved by whitewashing the first 500 million bytes in order to maintain security and cicumvent it's current security risks.
This is done through the rc4whitewash macro. This generates the 1st million bytes, allowing us to get passed
the first couple million vulnerable bytes
*/
#ifndef RC4_H
#define RC4_H

// can change this to 250 or 100 for increased speed of program
#define MS 500 

// Explicitly exporting shared library functions
#if defined(_MSC_VER)
    // Microsoft exports
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    // GCC
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    // do nothing and pray, warn about unknown semantics
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

// Macro for easier use
#define rc4decrypt(x,y,z)     rc4encrypt(x,y,z)
#define rc4uninit(x)          free(x)
#define rc4whitewash(x,y)       for(x=0; x<(MS*1000000); x++) \
                                    (volatile uint8_t)rc4byte(y); // volatile makes GCC not optimise this, aka not see it as redundant and remove it

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <errno.h>

// following format from online
struct s_arcfour
{
    uint16_t i, j, k;
    uint16_t S[256];
};

typedef struct s_arcfour Arcfour;

EXPORT Arcfour *rc4init(uint8_t *, int8_t);
uint8_t rc4byte(Arcfour *); // produces single character of encryted text
EXPORT uint8_t *rc4encrypt(Arcfour *, uint8_t *, uint16_t); // this is a two way function using XOR can encrypt and decrypt

#endif // RC4_H