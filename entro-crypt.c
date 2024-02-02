#include "entro-crypt.h"
#include "entro-hash.h"

void entro_crypt(const char *input, uint32_t *entropy) {
  char auxiliary[4];
  unsigned long i = 0;

  entropy[0] = 0;

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
          auxiliary[3] = 0;
        } else {
          auxiliary[2] = 0;
        }
      } else {
        auxiliary[1] = 0;
      }
    } else {
      auxiliary[0] = 0;
    }

    i++;
    entropy[i] = entro_hash(auxiliary, entropy[i - 1]);
  }

  while (i != 7) {
    i++;
    entropy[i] = entro_hash("", entropy[i - 1]);
  }

  i = 0;

  while (input[i] != 0) {
    auxiliary[0] = input[i];

    if (input[i + 1] != 0) {
      auxiliary[1] = input[i + 1];

      if (input[i + 2] != 0) {
        auxiliary[2] = input[i + 2];
        auxiliary[3] = 0;
      } else {
        auxiliary[2] = 0;
      }
    } else {
      auxiliary[1] = 0;
    }

    entropy[i & 7] += entro_hash(auxiliary, entropy[(i + 2) & 7]) ^ entropy[(i + 1) & 7];
    i++;
  }

  entropy[0] ^= entropy[7];
  entropy[1] ^= entropy[0];
  entropy[2] ^= entropy[1];
  entropy[3] ^= entropy[2];
  entropy[4] ^= entropy[3];
  entropy[5] ^= entropy[4];
  entropy[6] ^= entropy[5];
  entropy[7] ^= entropy[6];
}
