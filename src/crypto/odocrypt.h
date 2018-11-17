// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The DigiByte developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ODO_CRYPT
#define ODO_CRYPT

#include <stdint.h>

class OdoCrypt
{
public:
    const static int DIGEST_SIZE = 80;
    const static int ROUNDS = 84;
    const static int SMALL_SBOX_WIDTH = 6;
    const static int LARGE_SBOX_WIDTH = 10;
    const static int ROTATION_COUNT = 5;
    const static int WORD_BITS = 64;
    const static int DIGEST_BITS = 8*DIGEST_SIZE;
    const static int SBOX_COUNT = DIGEST_BITS / (SMALL_SBOX_WIDTH + LARGE_SBOX_WIDTH);
    const static int STATE_SIZE = DIGEST_BITS / WORD_BITS;

    OdoCrypt(uint32_t key);

    void Encrypt(char cipher[DIGEST_SIZE], const char plain[DIGEST_SIZE]) const;

    // test-only, proves that this really is a permutation function
    void Decrypt(char plain[DIGEST_SIZE], const char cipher[DIGEST_SIZE]) const;

private:
    uint8_t Sbox1[SBOX_COUNT][1 << SMALL_SBOX_WIDTH];
    uint16_t Sbox2[SBOX_COUNT][1 << LARGE_SBOX_WIDTH];
    uint64_t Pbox1[STATE_SIZE][STATE_SIZE];
    uint64_t Pbox2[STATE_SIZE][STATE_SIZE];
    int Rotations[STATE_SIZE][ROTATION_COUNT];
    uint16_t RoundKey[ROUNDS];

    // Pack/unpack bytes into internal state
    static void Unpack(uint64_t state[STATE_SIZE], const char bytes[DIGEST_SIZE]);
    static void Pack(const uint64_t state[STATE_SIZE], char bytes[DIGEST_SIZE]);

    // Pre-mix the bits.  Involution.
    static void PreMix(uint64_t state[STATE_SIZE]);

    // Non-linear substitution.
    static void ApplySboxes(
        uint64_t state[STATE_SIZE],
        const uint8_t sbox1[SBOX_COUNT][1 << SMALL_SBOX_WIDTH],
        const uint16_t sbox2[SBOX_COUNT][1 << LARGE_SBOX_WIDTH]);

    // Move bits between words.
    static void ApplyPbox(uint64_t state[STATE_SIZE], const uint64_t pbox[STATE_SIZE][STATE_SIZE]);

    // Linear mix step.
    static void ApplyRotations(uint64_t state[STATE_SIZE], const int rotations[STATE_SIZE][ROTATION_COUNT]);

    // Add round key. Involution.
    static void ApplyRoundKey(uint64_t state[STATE_SIZE], int roundKey);
};

#endif
