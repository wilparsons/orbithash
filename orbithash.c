#include "orbithash.h"

void orbithash(const char *input, uint32_t *entropy) {
  uint32_t salt[7];
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
    entropy[i] = entropy[i - 1] + 1111111111;
    entropy[i] += (entropy[i] + 111111111) << 9;
  }

  salt[0] = entropy[0];
  salt[1] = entropy[1];
  salt[2] = entropy[2];
  salt[3] = entropy[3];
  salt[4] = entropy[4];
  salt[5] = entropy[5];
  salt[6] = entropy[6];
  salt[7] = entropy[7];
  i = 0;

  while (input[i] != 0) {
    entropy[i & 7] += input[i] + entropy[(i + 1) & 7];
    entropy[i & 7] += (entropy[i & 7] + 1111111111) << 9;
    i++;
  }

  while (i < 7) {
    entropy[i] += entropy[i + 1] + 1111111111;
    entropy[i] += (entropy[i] + 111111111) << 9;
    i++;
  }

  salt[0] += entropy[0];
  salt[1] += entropy[1];
  salt[2] += entropy[2];
  salt[3] += entropy[3];
  salt[4] += entropy[4];
  salt[5] += entropy[5];
  salt[6] += entropy[6];
  salt[7] += entropy[7];
  entropy[0] += (entropy[6] ^ entropy[7]) << 10;
  entropy[1] ^= (entropy[0] + entropy[7]) << 9;
  entropy[2] += (entropy[0] ^ entropy[1]) << 8;
  entropy[3] ^= (entropy[1] + entropy[2]) << 7;
  entropy[4] += (entropy[2] ^ entropy[3]) << 6;
  entropy[5] ^= (entropy[3] + entropy[4]) << 5;
  entropy[6] += (entropy[4] ^ entropy[5]) << 4;
  entropy[7] ^= (entropy[5] + entropy[6]) << 3;
  entropy[0] += entropy[7] ^ salt[0];
  entropy[1] ^= entropy[0] ^ salt[1];
  entropy[2] += entropy[1] ^ salt[2];
  entropy[3] ^= entropy[2] ^ salt[3];
  entropy[4] += entropy[3] ^ salt[4];
  entropy[5] ^= entropy[4] ^ salt[5];
  entropy[6] += entropy[5] ^ salt[6];
  entropy[7] ^= entropy[6] ^ salt[7];
  entropy[6] += ((entropy[(salt[0] ^ entropy[6]) & 7] + (salt[1] ^ entropy[6]) + salt[2]) >> 10) + (salt[3] ^ entropy[7]);
  entropy[5] += ((entropy[(salt[1] ^ entropy[5]) & 7] + (salt[2] ^ entropy[5]) + salt[3]) >> 9) + (salt[4] ^ entropy[6]);
  entropy[4] += ((entropy[(salt[2] ^ entropy[4]) & 7] + (salt[3] ^ entropy[4]) + salt[4]) >> 8) + (salt[5] ^ entropy[5]);
  entropy[3] += ((entropy[(salt[3] ^ entropy[3]) & 7] + (salt[4] ^ entropy[3]) + salt[5]) >> 7) + (salt[6] ^ entropy[4]);
  entropy[2] += ((entropy[(salt[4] ^ entropy[2]) & 7] + (salt[5] ^ entropy[2]) + salt[6]) >> 6) + (salt[7] ^ entropy[3]);
  entropy[1] += ((entropy[(salt[5] ^ entropy[1]) & 7] + (salt[6] ^ entropy[1]) + salt[7]) >> 5) + (salt[0] ^ entropy[2]);
  entropy[0] += ((entropy[(salt[6] ^ entropy[0]) & 7] + (salt[7] ^ entropy[0]) + salt[0]) >> 4) + (salt[1] ^ entropy[1]);
  entropy[7] += ((salt[1] ^ salt[2] ^ salt[3]) << 16) | ((salt[4] ^ salt[5] ^ salt[6]) >> 16) + salt[7];
}
