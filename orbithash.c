#include "orbithash.h"

void orbithash(const char *input, uint32_t *entropy) {
  uint32_t salt;
  unsigned long i = 0;

  entropy[0] = 1111111111;

  while (
    i != 7 &&
    input[i] != 0
  ) {
    i++;
    entropy[i] = input[i - 1] + entropy[i - 1];
    entropy[i] += (entropy[i] + 111111111) << 9;
  }

  while (i != 7) {
    i++;
    entropy[i] = entropy[i - 1] + 1;
    entropy[i] += (entropy[i] + 111111111) << 9;
  }

  i = 0;

  while (input[i] != 0) {
    entropy[i & 7] = input[i] + entropy[(i + 1) & 7];
    entropy[i & 7] += (entropy[i & 7] + 1111111111) << 9;
    i++;
  }

  while (i < 7) {
    entropy[i] += entropy[i + 1] + 1;
    entropy[i] += (entropy[i] + 111111111) << 9;
    i++;
  }

  salt = entropy[i & 7];
  entropy[0] += (entropy[7] + entropy[3]) << 9;
  entropy[1] ^= (entropy[0] + entropy[6]) << 8;
  entropy[2] += (entropy[1] + entropy[5]) << 7;
  entropy[3] ^= (entropy[2] + entropy[1]) << 6;
  entropy[4] += (entropy[3] + entropy[7]) << 5;
  entropy[5] ^= (entropy[4] + entropy[3]) << 4;
  entropy[6] += (entropy[5] + entropy[4]) << 3;
  entropy[7] ^= (entropy[6] + entropy[5]) << 2;
  entropy[6] += ((entropy[(input[0] + entropy[6] + i) & 7] + (entropy[7] ^ i) + salt + i) >> 9) + entropy[5] + salt + i;
  entropy[5] += ((entropy[(input[0] + entropy[5] + i) & 7] + (entropy[6] ^ i) + salt + i) >> 8) + entropy[4] + salt + i;
  entropy[4] += ((entropy[(input[0] + entropy[4] + i) & 7] + (entropy[5] ^ i) + salt + i) >> 7) + entropy[3] + salt + i;
  entropy[3] += ((entropy[(input[0] + entropy[3] + i) & 7] + (entropy[4] ^ i) + salt + i) >> 6) + entropy[2] + salt + i;
  entropy[2] += ((entropy[(salt + i) & 7] + (entropy[3] ^ i) + salt + i) >> 5) + entropy[1] + salt + i;
  entropy[1] += ((entropy[(input[0] + salt + i) & 7] + (entropy[2] ^ i) + salt + i) >> 4) + entropy[0] + salt + i;
  entropy[0] += ((entropy[(input[0] + salt) & 7] + (entropy[7] ^ i) + salt + i) >> 3) + entropy[1] + salt + i;
  entropy[7] += ((entropy[(input[0] + i) & 7] + (entropy[0] ^ i) + salt + i) >> 2) + entropy[2] + salt + i;
}
