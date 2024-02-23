#include "quakehash.h"

uint32_t quakehash(const char *input, uint32_t entropy) {
  unsigned long i = 0;

  while (input[i] != 0) {
    entropy += input[i];
    entropy += (entropy + 111111111) << 9;
    entropy += entropy << 5;
    entropy += ((entropy << 3) + entropy) << 24;
    entropy ^= entropy >> 16;
    i++;
  }

  return entropy;
}
