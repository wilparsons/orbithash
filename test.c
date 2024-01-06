#include <stdio.h>
#include "entro-crypt.h"

int main(void) {
  const char *input_1 = "message_1";
  const char *input_2 = "message_2";
  uint32_t entropy[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  entro_crypt(input_1, entropy);
  entro_crypt(input_2, entropy);
  printf("%08X%08X%08X%08X%08X%08X%08X%08X\n", entropy[0], entropy[1], entropy[2], entropy[3], entropy[4], entropy[5], entropy[6], entropy[7]);
  return 0;
}
