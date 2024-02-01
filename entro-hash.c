#include "entro-hash.h"

uint32_t entro_hash(const char *input, uint32_t entropy) {
  unsigned long i = 0;

  while (input[i] != 0) {
    entropy ^= (input[i] + 111111) ^ 111111;
    entropy += (~entropy ^ 1111111111) << 4;
    entropy = (entropy << 31) + (~entropy >> 1);
    entropy += entropy << 3;
    entropy ^= input[i];
    entropy += (entropy + 111111111) << 9;
    entropy += entropy << 3;
    entropy += (~entropy + entropy) << 1;
    i++;
  }

  entropy ^= (input[i] + 111111) ^ 111111;
  entropy += (~entropy ^ 1111111111) << 4;
  entropy = (entropy << 31) + (~entropy >> 1);
  entropy += entropy << 3;
  entropy ^= input[i];
  entropy += (entropy + 111111111) << 9;
  entropy += entropy << 3;
  return ((~entropy + entropy) << 1) + entropy;
}
