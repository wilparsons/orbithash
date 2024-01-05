#include <stdio.h>
#include "entro-crypt.h"

int main(void) {
  const char *input = "message";
  uint32_t digest[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  entro_crypt(input, digest);
  printf("%08X%08X%08X%08X%08X%08X%08X%08X\n", digest[0], digest[1], digest[2], digest[3], digest[4], digest[5], digest[6], digest[7]);
  return 0;
}
