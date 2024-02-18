#include "orbithash.h"
#include "quakehash.h"

void orbithash(const char *input, uint32_t *entropy) {
  char auxiliary[5];
  unsigned long i = 0;

  entropy[0] = 1111111111;

  while (
    i != 7 &&
    input[i] != 0
  ) {
    if (input[i] != 0) {
      auxiliary[0] = input[i];

      if (input[i + 1] != 0) {
        auxiliary[1] = input[i + 1];

        if (input[i + 2] != 0) {
          auxiliary[2] = input[i + 2];
          auxiliary[3] = 1;
          auxiliary[4] = 0;
        } else {
          auxiliary[2] = 1;
          auxiliary[3] = 0;
        }
      } else {
        auxiliary[1] = 1;
        auxiliary[2] = 0;
      }
    } else {
      auxiliary[0] = 1;
      auxiliary[1] = 0;
    }

    i++;
    entropy[i] = quakehash(auxiliary, entropy[i - 1]);
  }

  if (i != 7) {
    auxiliary[0] = 1;
    auxiliary[1] = 0;

    while (i != 7) {
      i++;
      entropy[i] = quakehash(auxiliary, entropy[i - 1]);
    }
  }

  i = 0;

  while (input[i] != 0) {
    auxiliary[0] = input[i];

    if (input[i + 1] != 0) {
      auxiliary[1] = input[i + 1];

      if (input[i + 2] != 0) {
        auxiliary[2] = input[i + 2];
        auxiliary[3] = 1;
        auxiliary[4] = 0;
      } else {
        auxiliary[2] = 1;
        auxiliary[3] = 0;
      }
    } else {
      auxiliary[1] = 1;
      auxiliary[2] = 0;
    }

    entropy[i & 7] += quakehash(auxiliary, entropy[(i + 1) & 7]);
    i++;
  }

  entropy[0] += entropy[7];
  entropy[1] += entropy[0];
  entropy[2] += entropy[1];
  entropy[3] += entropy[2];
  entropy[4] += entropy[3];
  entropy[5] += entropy[4];
  entropy[6] += entropy[5];
  entropy[7] += entropy[6];
}
