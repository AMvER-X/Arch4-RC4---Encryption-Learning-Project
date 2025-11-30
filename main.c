#include "RC4.h"

#define F fflush(stdout) // Flushes stdoutput buffer does not print text something is loaded

int main(void); // No arguments

// Output function to output 2 characters at a time in hex format
void printbin(uint8_t *input, uint16_t size)
{
    uint16_t i; // works better with size 16 bits
    uint8_t *p;

    assert(size > 0);

    for (i = 0, p=input; i < size; i++, p++)
    {
        printf("%.02x", *p); // Print each byte in hex format

        // Add a space after every two bytes (4 hex characters)
        if ((i + 1) % 2 == 0 && (i + 1) != size)
        {
            printf(" ");
        }
    }

    printf("\n");

    return;
}


// This serves as an example of use (not apart of production)
int main()
{
    Arcfour *rc4;
    uint16_t sizeKey, sizeText;
    uint8_t *key, *source, *encryped, *decrypted;

    /*8 BITS -> 2048 BITS according to standard being used*/
    key = "X9w3LqA6TbR7Yp2K"; // Example is 128 bits in hex 
    sizeKey = strlen(key);

    source = "Shall I compare thee to a summer's day?"; 
    sizeText = strlen(source);
    
    printf("Initializing encryption..."); F;
    rc4 = rc4init((uint8_t *)key, sizeKey);
    
    if (!rc4) 
    {
        perror("malloc");
        return -1;
    }
    printf("Done\n");

    // order matters to display content before encrypting
    printf("'%s'\n ->", source);
    encryped = rc4encrypt(rc4, (unit8_t *)source, sizeText);
    printbin(encryped, sizeText);

    // Need to uninitialise rc4 struct each time for proper encryption
    rc4uninit(rc4);

    // Needs to be reinitialised
    printf("Initializing encryption..."); F;
    rc4 = rc4init((uint8_t *)key, sizeKey);
    if (!rc4) 
    {
        perror("malloc");
        return -1;
    }
    printf("Done\n");
    
    // order change need to decrypt 1st
    decrypted = rc4decrypt(rc4, encryped, sizeText);
    printf("    -> '%s'\n", decrypted);

    rc4uninit(rc4);

    return 0;
}