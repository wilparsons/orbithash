# OrbitHash
![OrbitHash Logo](https://repository-images.githubusercontent.com/739451555/4b3214f2-3c69-44ae-9ab2-c6c6b21440b6)

## Description
OrbitHash is a 256-bit, cryptographic hashing algorithm.

Read [this article](https://medium.com/@wilparsons/orbithash-is-a-new-256-bit-secure-hashing-algorithm-without-additive-prime-number-constants-794940fce75e) for an in-depth explanation.

## Usage
``` c
#include <stdio.h>
#include "orbithash.h"

int main(void) {
  const char *input = "message";
  uint32_t entropy[8];

  orbithash(input, entropy);
  printf("%08x%08x%08x%08x%08x%08x%08x%08x\n", entropy[0], entropy[1], entropy[2], entropy[3], entropy[4], entropy[5], entropy[6], entropy[7]);
  return 0;
}
```

## Reference
#### `orbithash()`
This is the hashing function that accepts the 2 following arguments.

`input` is the null-terminated `char` string to hash.

`entropy` is an array with 8 32-bit unsigned integers. This becomes the 256-bit hash digest result.

The return value data type is `void`.

## Support
OrbitHash was designed and developed by [Wil Parsons](https://wilparsons.com/).

I'm available for freelance work to extend, modifify or implement OrbitHash and other algorithms.
