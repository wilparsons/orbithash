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

    if (input[i] != 0) {
      if (input[i + 1] != 0) {
        entropy[i] += input[i - 1];
        entropy[i] += (entropy[i] + 111111111) << 9;
        entropy[i] += input[i];
        entropy[i] += (entropy[i] + 111111111) << 9;
        entropy[i] += input[i + 1];
        entropy[i] += ((entropy[i] + 111111111) << 9) + 1;
        entropy[i] += (entropy[i] + 111111111) << 9;
      } else {
        entropy[i] += input[i - 1];
        entropy[i] += (entropy[i] + 111111111) << 9;
        entropy[i] += input[i];
        entropy[i] += ((entropy[i] + 111111111) << 9) + 1;
        entropy[i] += (entropy[i] + 111111111) << 9;
      }
    } else {
      entropy[i] += input[i - 1];
      entropy[i] += ((entropy[i] + 111111111) << 9) + 1;
      entropy[i] += (entropy[i] + 111111111) << 9;
    }
  }

  while (i != 7) {
    i++;
    entropy[i] = entropy[i - 1] + 1111111111;
    entropy[i] += (entropy[i] + 111111111) << 9;
  }

  i = 0;

  while (input[i] != 0) {
    copied_entropy = entropy[(i + 1) & 7];

    if (input[i + 1] != 0) {
      if (input[i + 2] != 0) {
        copied_entropy += input[i];
        copied_entropy += (copied_entropy + 111111111) << 9;
        copied_entropy += input[i + 1];
        copied_entropy += (copied_entropy + 111111111) << 9;
        copied_entropy += input[i + 2];
        copied_entropy += ((copied_entropy + 111111111) << 9) + 1;
        copied_entropy += (copied_entropy + 111111111) << 9;
      } else {
        copied_entropy += input[i];
        copied_entropy += (copied_entropy + 111111111) << 9;
        copied_entropy += input[i + 1];
        copied_entropy += ((copied_entropy + 111111111) << 9) + 1;
        copied_entropy += (copied_entropy + 111111111) << 9;
      }
    } else {
      copied_entropy += input[i];
      copied_entropy += ((copied_entropy + 111111111) << 9) + 1;
      copied_entropy += (copied_entropy + 111111111) << 9;
    }

    entropy[i & 7] += copied_entropy;
    i++;
  }

  entropy[0] += entropy[7];
  entropy[1] ^= entropy[0] + entropy[6];
  entropy[2] += entropy[1] ^ entropy[5];
  entropy[3] ^= entropy[2] + entropy[1];
  entropy[4] += entropy[3] << 1;
  entropy[5] ^= entropy[4] + entropy[3];
  entropy[6] += entropy[5] ^ entropy[4];
  entropy[7] ^= entropy[6] + entropy[5];
  entropy[6] += entropy[7] << 11;
  entropy[5] += entropy[6] >> 10;
  entropy[4] += entropy[5] << 9;
  entropy[3] += entropy[4] >> 7;
  entropy[2] += entropy[3] << 5;
  entropy[1] += entropy[2] >> 4;
  entropy[0] += entropy[7] << 3;
  entropy[7] += entropy[0] >> 6;
}
