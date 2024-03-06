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
  entropy[6] += ((entropy[(state[0] ^ entropy[6]) & 7] + (state[1] ^ entropy[6]) + state[2]) >> 10) + (state[3] ^ entropy[7]);
  entropy[5] += ((entropy[(state[1] ^ entropy[5]) & 7] + (state[2] ^ entropy[5]) + state[3]) >> 9) + (state[4] ^ entropy[6]);
  entropy[4] += ((entropy[(state[2] ^ entropy[4]) & 7] + (state[3] ^ entropy[4]) + state[4]) >> 8) + (state[5] ^ entropy[5]);
  entropy[3] += ((entropy[(state[3] ^ entropy[3]) & 7] + (state[4] ^ entropy[3]) + state[5]) >> 7) + (state[6] ^ entropy[4]);
  entropy[2] += ((entropy[(state[4] ^ entropy[2]) & 7] + (state[5] ^ entropy[2]) + state[6]) >> 6) + (state[7] ^ entropy[3]);
  entropy[1] += ((entropy[(state[5] ^ entropy[1]) & 7] + (state[6] ^ entropy[1]) + state[7]) >> 5) + (state[0] ^ entropy[2]);
  entropy[0] += ((entropy[(state[6] ^ entropy[0]) & 7] + (state[7] ^ entropy[0]) + state[0]) >> 4) + (state[1] ^ entropy[1]);
  entropy[7] += (((state[1] ^ state[2] ^ state[3]) << 16) | ((state[4] ^ state[5] ^ state[6]) >> 16)) + state[7];
}
