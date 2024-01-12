#include "entro-crypt.h"
#include "entro-hash.h"

void entro_crypt(const char *input, uint32_t *entropy) {
  entropy[0] = entro_hash(input, 0) + 1;
  entropy[1] = (entro_hash(input, entropy[0]) + 11) ^ entropy[0];
  entropy[2] = (entro_hash(input, entropy[1]) + 1) ^ entropy[1];
  entropy[3] = (entro_hash(input, entropy[2]) + 11) ^ entropy[2];
  entropy[4] = (entro_hash(input, entropy[3]) + 1) ^ entropy[3];
  entropy[5] = (entro_hash(input, entropy[4]) + 11) ^ entropy[4];
  entropy[6] = (entro_hash(input, entropy[5]) + 1) ^ entropy[5];
  entropy[7] = (entro_hash(input, entropy[6]) + 11) ^ entropy[6];
  entropy[0] ^= entropy[7];
  entropy[1] ^= entropy[0];
  entropy[2] ^= entropy[1];
  entropy[3] ^= entropy[2];
  entropy[4] ^= entropy[3];
  entropy[5] ^= entropy[4];
  entropy[6] ^= entropy[5];
}
