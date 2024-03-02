#include "orbithash.h"

void orbithash(const char *input, uint32_t *entropy) {
  uint32_t copied_entropy;
  unsigned long i = 0;

  entropy[0] = 1111111111;

  while (
    i != 7 &&
    input[i] != 0
  ) {
    i++;
    entropy[i] = entropy[i - 1];
    entropy[i] += input[i - 1];
    entropy[i] += ((entropy[i] + 111111111) << 9) + 1;
    entropy[i] += (entropy[i] + 111111111) << 9;
  }

  while (i != 7) {
    i++;
    entropy[i] = entropy[i - 1] + 1111111111;
    entropy[i] += (entropy[i] + 111111111) << 9;
  }

  i = 0;

  while (input[i] != 0) {
    copied_entropy = entropy[(i + 1) & 7];
    copied_entropy += input[i];
    copied_entropy += ((copied_entropy + 1111111111) << 9) + 1;
    copied_entropy += (copied_entropy + 111111111) << 9;
    entropy[i & 7] += copied_entropy;
    i++;
  }

  while (i != 7) {
    i++;
    entropy[i] = entropy[i - 1] + 1111111111;
    entropy[i] += (entropy[i] + 111111111) << 9;
  }

  entropy[0] += (entropy[7] + i) << 1;
  entropy[1] ^= entropy[0] + entropy[6];
  entropy[2] += entropy[1] ^ entropy[5];
  entropy[3] ^= entropy[2] + entropy[1];
  entropy[4] += (entropy[3] + i) << 1;
  entropy[5] ^= entropy[4] + entropy[3];
  entropy[6] += entropy[5] ^ entropy[4];
  entropy[7] ^= entropy[6] + entropy[5];
  entropy[6] += (entropy[7] + i) << 11;
  entropy[5] += (entropy[6] + i) >> 10;
  entropy[4] += (entropy[5] + i) << 9;
  entropy[3] += (entropy[4] + i) >> 7;
  entropy[2] += (entropy[3] + i) << 5;
  entropy[1] += (entropy[2] + i) >> 4;
  entropy[0] += (entropy[7] + i) << 3;
  entropy[7] += (entropy[0] + i) >> 6;
}
