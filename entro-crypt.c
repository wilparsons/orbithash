#include "entro-crypt.h"
#include "entro-hash.h"

void entro_crypt(const char *input, uint32_t *entropy) {
  entropy[0] = entro_hash(input, 0) + 1;
  entropy[1] = (entro_hash(input, entropy[0]) + 2) ^ entropy[0];
  entropy[2] = (entro_hash(input, entropy[1]) + 3) ^ entropy[1];
  entropy[3] = (entro_hash(input, entropy[2]) + 4) ^ entropy[2];
  entropy[4] = (entro_hash(input, entropy[3]) + 5) ^ entropy[3];
  entropy[5] = (entro_hash(input, entropy[4]) + 6) ^ entropy[4];
  entropy[6] = (entro_hash(input, entropy[5]) + 7) ^ entropy[5];
  entropy[7] = (entro_hash(input, entropy[6]) + 8) ^ entropy[6];
  entropy[0] ^= entropy[7];
  entropy[1] ^= entropy[0];
  entropy[2] ^= entropy[1];
  entropy[3] ^= entropy[2];
  entropy[4] ^= entropy[3];
  entropy[5] ^= entropy[4];
  entropy[6] ^= entropy[5];
}
