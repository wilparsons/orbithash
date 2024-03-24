# OrbitHash
![OrbitHash Logo](https://repository-images.githubusercontent.com/739451555/3f6a1979-8f13-4e00-9c18-6fe17db37463)

## Description
OrbitHash is a 256-bit, cryptographic hashing algorithm.

Read [this article](https://medium.com/@williamstaffordparsons/orbithash-is-a-new-256-bit-secure-hashing-algorithm-without-additive-prime-number-constants-794940fce75e) for an in-depth explanation.

## License
Copyright 2024 William Stafford Parsons

OrbitHash is protected under copyright and subject to software licensing terms in the [LICENSE file](https://github.com/williamstaffordparsons/orbithash/blob/master/LICENSE).

## Reference
#### `orbithash()`
This is the hashing function that accepts the 2 following arguments.

`input` is the null-terminated `char` string to hash.

`entropy` is an array with 8 32-bit unsigned integers. This becomes the 256-bit hash digest result.

The return value data type is `void`.

## Usage
``` c
#include "orbithash.h"

int main(void) {
  const char *input = "message";
  uint32_t entropy[8];

  orbithash(input, entropy);
  return 0;
}
```
