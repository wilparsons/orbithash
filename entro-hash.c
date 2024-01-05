#include "entro-hash.h"

uint32_t entro_hash(const char *input, uint32_t entropy) {
  unsigned long i = 0;

  while (input[i] != 0) {
    entropy ^= (input[i] + 111111) ^ 111111;
    entropy += (~entropy ^ 1111111111) << 4;
    entropy -= 1111111;
    entropy = (entropy << 31) + (~entropy >> 1);
    entropy += entropy << 3;
    entropy += entropy << 3;
    entropy ^= ~entropy << 10;
    entropy ^= 111111111;
    entropy ^= entropy << 13;
    entropy += (~entropy + entropy) << 1;
    i++;
  }

  return entropy;
}
