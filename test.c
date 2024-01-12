#include <stdio.h>
#include "entro-crypt.h"

int main(void) {
  const char *input = "message";
  uint32_t entropy[8];

  entro_crypt(input, entropy);
  printf("%08X%08X%08X%08X%08X%08X%08X%08X\n", entropy[0], entropy[1], entropy[2], entropy[3], entropy[4], entropy[5], entropy[6], entropy[7]);
  return 0;
}
