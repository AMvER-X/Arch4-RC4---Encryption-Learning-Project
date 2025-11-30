🔑 RC4 Stream Cipher Implementation
A learning-focused project written in C that provides a complete implementation of the RC4 (Rivest Cipher 4) stream cipher, demonstrating the core principles of symmetric encryption.

✨ Project Goal & Learning Outcomes
The primary goal of this project was to serve as a practical entry point into cryptography by building a working, self-contained implementation of a known stream cipher.

Symmetric Encryption Fundamentals: Hands-on understanding of how a single secret key is used for both encryption and decryption.

Stream Ciphers: Gaining proficiency in the concept of a keystream combined with plaintext via the XOR operation.

Algorithm Implementation: Mastering the two core phases of the RC4 algorithm: the Key-Scheduling Algorithm (KSA) and the Pseudo-Random Generation Algorithm (PRGA).

🚀 Project Demo and Usage
This repository includes a demonstration module that illustrates the full encryption and decryption cycle.

Usage Steps
Define Key: A secret key is defined (e.g., "MySecretKey123").

Encryption: The key is passed to the RC4 implementation to generate a keystream, which is XORed with the plaintext.

Decryption: The same key is passed again to generate the identical keystream, which is then XORed with the ciphertext, recovering the original message.
