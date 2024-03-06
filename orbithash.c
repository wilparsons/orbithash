#include "orbithash.h"

void orbithash(const char *input, uint32_t *entropy) {
  uint32_t state[8];
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

  state[0] = entropy[0];
  state[1] = entropy[1];
  state[2] = entropy[2];
  state[3] = entropy[3];
  state[4] = entropy[4];
  state[5] = entropy[5];
  state[6] = entropy[6];
  state[7] = entropy[7];
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

  state[0] += entropy[0];
  state[1] += entropy[1];
  state[2] += entropy[2];
  state[3] += entropy[3];
  state[4] += entropy[4];
  state[5] += entropy[5];
  state[6] += entropy[6];
  state[7] += entropy[7];
  entropy[0] += (entropy[6] ^ entropy[7]) << 10;
  entropy[1] ^= (entropy[0] + entropy[7]) << 9;
  entropy[2] += (entropy[0] ^ entropy[1]) << 8;
  entropy[3] ^= (entropy[1] + entropy[2]) << 7;
  entropy[4] += (entropy[2] ^ entropy[3]) << 6;
  entropy[5] ^= (entropy[3] + entropy[4]) << 5;
  entropy[6] += (entropy[4] ^ entropy[5]) << 4;
  entropy[7] ^= (entropy[5] + entropy[6]) << 3;
  entropy[0] += entropy[7] ^ state[0];
  entropy[1] ^= entropy[0] ^ state[1];
  entropy[2] += entropy[1] ^ state[2];
  entropy[3] ^= entropy[2] ^ state[3];
  entropy[4] += entropy[3] ^ state[4];
  entropy[5] ^= entropy[4] ^ state[5];
  entropy[6] += entropy[5] ^ state[6];
  entropy[7] ^= entropy[6] ^ state[7];
  entropy[6] += ((entropy[(entropy[6] ^ state[0]) & 7] + (entropy[6] ^ state[1]) + state[2]) >> 10) + (entropy[7] ^ state[3]);
  entropy[5] += ((entropy[(entropy[5] ^ state[1]) & 7] + (entropy[5] ^ state[2]) + state[3]) >> 9) + (entropy[6] ^ state[4]);
  entropy[4] += ((entropy[(entropy[4] ^ state[2]) & 7] + (entropy[4] ^ state[3]) + state[4]) >> 8) + (entropy[5] ^ state[5]);
  entropy[3] += ((entropy[(entropy[3] ^ state[3]) & 7] + (entropy[3] ^ state[4]) + state[5]) >> 7) + (entropy[4] ^ state[6]);
  entropy[2] += ((entropy[(entropy[2] ^ state[4]) & 7] + (entropy[2] ^ state[5]) + state[6]) >> 6) + (entropy[3] ^ state[7]);
  entropy[1] += ((entropy[(entropy[1] ^ state[5]) & 7] + (entropy[1] ^ state[6]) + state[7]) >> 5) + (entropy[2] ^ state[0]);
  entropy[0] += ((entropy[(entropy[0] ^ state[6]) & 7] + (entropy[0] ^ state[7]) + state[0]) >> 4) + (entropy[1] ^ state[1]);
  entropy[7] += (((state[1] ^ state[2] ^ state[3]) << 16) | ((state[4] ^ state[5] ^ state[6]) >> 16)) + state[7];
}
