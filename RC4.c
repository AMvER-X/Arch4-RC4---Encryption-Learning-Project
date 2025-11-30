/*RC4.c

Implementation of RC4.h
*/

#include "RC4.h"

// needs a universal assert macro, which prints the error number and message, because assert_perror is limited to linux
#define ASSERT_WITH_ERRNO(condition) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Assertion failed: %s\n", #condition); \
            fprintf(stderr, "Error code: %d\n", errno); \
            perror("Error in program"); \
            assert(condition); \
        } \
    } while (0)

EXPORT Arcfour *rc4init(uint8_t *key, int8_t sizeK)
{
    Arcfour *p;
    uint8_t temp1 = 0;
    uint32_t n = 0;

    p = malloc(sizeof(Arcfour)); //needs memory to run otherwise pointless to run
    ASSERT_WITH_ERRNO(p);


    // initialise to 0
    for(uint16_t x = 0; x < 256; x++)
        p->S[x] = 0;
    p->i=p->j=p->k=0;


    // step 1
    for(p->i = 0; p->i < 256; p->i++)
    {
        p->S[p->i] = p->i;
    }
    

    // step 2
    for(p->i = 0; p->i < 256; p->i++)
    {       
        p->j = (p->j + p->S[p->i] + key[p->i % sizeK]) % 256;
        temp1 = p->S[p->i];
        p->S[p->i] = p->S[p->j];
        p->S[p->j] = temp1;
    }
    p->i=p->j=0;
    rc4whitewash(n, p);
    return p;
}

// This code returns one byte of the cypher text at a time, usually implemented as a loop but for this project the loop through the cyphertext for enxryption will be implemented 
// in the function bellow. Can be seen as helper function.
uint8_t rc4byte(Arcfour *p)
{
    

    uint16_t tmp1=0;
    p->i = (p->i + 1) % 256;
    p->j = (p->j + p->S[p->i]) % 256;

    tmp1 = p->S[p->i];
    p->S[p->i] = p->S[p->j];
    p->S[p->j] = tmp1;

    tmp1 = (p->S[p->i] + p->S[p->j]) % 256;
    p->k = p->S[tmp1];

    return p->k;
}

// Function to be called for encrypting text
EXPORT uint8_t *rc4encrypt(Arcfour *p, uint8_t *clrTxt, uint16_t size)
{
    uint8_t *cipherText;
    uint16_t x;

    cipherText = malloc(size + 1);
    if (!cipherText)
     ASSERT_WITH_ERRNO(errno);

    for (x = 0; x < size; x++)
    {
        cipherText[x] = clrTxt[x] ^ rc4byte(p);
    }
    return cipherText;
}