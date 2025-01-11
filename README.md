# Post-Quantum Embedded Cryptography for ESP32-C3

This is a test project created with [liboqs](https://github.com/open-quantum-safe/liboqs) and [WolfSSL](https://github.com/wolfSSL/wolfssl) libraries and based on [PlatformIO](https://platformio.org) framework.

It runs WolfSSL benchmarks on a very cheap ESP32-C3 RISC-V MCU @160MHz - one can order an evaluation board for 1-2 dollars.

The point of this benchmark is to see how feasible it is to use Quantum-Safe algorithms in embedded environments. 

# Usage 

## Building and running

1. Get the [PlatformIO IDE extension](https://platformio.org/platformio-ide) for VSCode.

2. Clone the source code with submodules:
```
git clone --recurse-submodules https://github.com/avlk/pqc-esp32-c3.git
```

3. Run Build and then Upload to the device.

## Build options

It builds a full benchmark test with KYBER, FALCON, ML-DSA and SPHINCS, as well as traditional crypto algorithms. LIBOQS is binded with WolfSSL to use HW-optimized SHA256, which speeds up SPHINCS-*-SHA2 a lot. CPU optimization is `-O2`. 

To build without HW acceleration of PQC algorithms, replace `liboqs_common_wolfssl` with `liboqs_common` in `liboqs-library.json`.

## Results

Resulting binary is more than 1Mb in size, as it contains all algorythm species along with the test cases and basic BSP of ESP32-C3. It was not my target to create a smallest build though.

### Running with HW acceleration

AES, SHA, HMAC tests were omitted here for clarity.

```
RSA     1024  key gen         2 ops took 1.030 sec, avg 515.000 ms, 1.942 ops/sec
RSA     2048  key gen         1 ops took 7.160 sec, avg 7160.000 ms, 0.140 ops/sec
RSA     2048   public         6 ops took 1.340 sec, avg 223.333 ms, 4.478 ops/sec
RSA     2048  private         4 ops took 1.130 sec, avg 282.500 ms, 3.540 ops/sec
DH      2048  key gen         4 ops took 1.030 sec, avg 257.500 ms, 3.883 ops/sec
DH      2048    agree        48 ops took 1.020 sec, avg 21.250 ms, 47.059 ops/sec
KYBER512    128  key gen        10 ops took 1.060 sec, avg 106.000 ms, 9.434 ops/sec
KYBER512    128    encap         8 ops took 1.070 sec, avg 133.750 ms, 7.477 ops/sec
KYBER512    128    decap        10 ops took 1.080 sec, avg 108.000 ms, 9.259 ops/sec
KYBER768    192  key gen         6 ops took 1.020 sec, avg 170.000 ms, 5.882 ops/sec
KYBER768    192    encap         6 ops took 1.290 sec, avg 215.000 ms, 4.651 ops/sec
KYBER768    192    decap         6 ops took 1.070 sec, avg 178.333 ms, 5.607 ops/sec
KYBER1024   256  key gen         4 ops took 1.100 sec, avg 275.000 ms, 3.636 ops/sec
KYBER1024   256    encap         4 ops took 1.330 sec, avg 332.500 ms, 3.008 ops/sec
KYBER1024   256    decap         4 ops took 1.140 sec, avg 285.000 ms, 3.509 ops/sec
ECC   [      SECP256R1]   256  key gen         4 ops took 1.710 sec, avg 427.500 ms, 2.339 ops/sec
ECDHE [      SECP256R1]   256    agree         4 ops took 1.700 sec, avg 425.000 ms, 2.353 ops/sec
ECDSA [      SECP256R1]   256     sign         4 ops took 1.710 sec, avg 427.500 ms, 2.339 ops/sec
ECDSA [      SECP256R1]   256   verify         4 ops took 1.160 sec, avg 290.000 ms, 3.448 ops/sec
CURVE  25519  key gen         3 ops took 1.130 sec, avg 376.667 ms, 2.655 ops/sec
CURVE  25519    agree         4 ops took 1.510 sec, avg 377.500 ms, 2.649 ops/sec
ED     25519  key gen        73 ops took 1.000 sec, avg 13.699 ms, 73.000 ops/sec
ED     25519     sign        62 ops took 1.010 sec, avg 16.290 ms, 61.386 ops/sec
ED     25519   verify        40 ops took 1.030 sec, avg 25.750 ms, 38.835 ops/sec
FALCON     1     sign         2 ops took 1.000 sec, avg 500.000 ms, 2.000 ops/sec
FALCON     1   verify        18 ops took 1.120 sec, avg 62.222 ms, 16.071 ops/sec
FALCON     5     sign         2 ops took 2.120 sec, avg 1060.000 ms, 0.943 ops/sec
FALCON     5   verify        10 ops took 1.000 sec, avg 100.000 ms, 10.000 ops/sec
ML-DSA    44  key gen         4 ops took 1.600 sec, avg 400.000 ms, 2.500 ops/sec
ML-DSA    44     sign         2 ops took 1.020 sec, avg 510.000 ms, 1.961 ops/sec
ML-DSA    44   verify         4 ops took 1.610 sec, avg 402.500 ms, 2.484 ops/sec
ML-DSA    65  key gen         2 ops took 1.450 sec, avg 725.000 ms, 1.379 ops/sec
ML-DSA    65     sign         2 ops took 1.780 sec, avg 890.000 ms, 1.124 ops/sec
ML-DSA    65   verify         2 ops took 1.380 sec, avg 690.000 ms, 1.449 ops/sec
ML-DSA    87  key gen         2 ops took 2.510 sec, avg 1255.000 ms, 0.797 ops/sec
ML-DSA    87     sign         2 ops took 4.510 sec, avg 2255.000 ms, 0.443 ops/sec
ML-DSA    87   verify         2 ops took 2.440 sec, avg 1220.000 ms, 0.820 ops/sec
SPHINCS-FAST-SHA2     1     sign         2 ops took 26.390 sec, avg 13195.000 ms, 0.076 ops/sec
SPHINCS-FAST-SHA2     1   verify         2 ops took 1.970 sec, avg 985.000 ms, 1.015 ops/sec
SPHINCS-FAST-SHA2     3     sign         2 ops took 121.200 sec, avg 60600.000 ms, 0.017 ops/sec
SPHINCS-FAST-SHA2     3   verify         2 ops took 6.840 sec, avg 3420.000 ms, 0.292 ops/sec
SPHINCS-FAST-SHA2     5     sign         2 ops took 308.650 sec, avg 154325.000 ms, 0.006 ops/sec
SPHINCS-FAST-SHA2     5   verify         2 ops took 7.820 sec, avg 3910.000 ms, 0.256 ops/sec
SPHINCS-SMALL-SHA2     1     sign         2 ops took 695.290 sec, avg 347645.000 ms, 0.003 ops/sec
SPHINCS-SMALL-SHA2     1   verify         4 ops took 1.330 sec, avg 332.500 ms, 3.008 ops/sec
SPHINCS-SMALL-SHA2     3     sign         2 ops took 3975.360 sec, avg 1987680.000 ms, 0.001 ops/sec
SPHINCS-SMALL-SHA2     3   verify         2 ops took 3.680 sec, avg 1840.000 ms, 0.543 ops/sec
SPHINCS-SMALL-SHA2     5     sign         2 ops took 3615.680 sec, avg 1807840.000 ms, 0.001 ops/sec
SPHINCS-SMALL-SHA2     5   verify         2 ops took 4.600 sec, avg 2300.000 ms, 0.435 ops/sec
SPHINCS-FAST-SHAKE     1     sign         2 ops took 825.670 sec, avg 412835.000 ms, 0.002 ops/sec
SPHINCS-FAST-SHAKE     1   verify         2 ops took 49.770 sec, avg 24885.000 ms, 0.040 ops/sec
SPHINCS-FAST-SHAKE     3     sign         2 ops took 1334.630 sec, avg 667315.000 ms, 0.001 ops/sec
SPHINCS-FAST-SHAKE     3   verify         2 ops took 71.290 sec, avg 35645.000 ms, 0.028 ops/sec
SPHINCS-FAST-SHAKE     5     sign         2 ops took 2738.490 sec, avg 1369245.000 ms, 0.001 ops/sec
SPHINCS-FAST-SHAKE     5   verify         2 ops took 74.710 sec, avg 37355.000 ms, 0.027 ops/sec
```

### Running with no SHA256 HW acceleration

```
RSA     1024  key gen         1 ops took 1.160 sec, avg 1160.000 ms, 0.862 ops/sec
RSA     2048  key gen         1 ops took 7.170 sec, avg 7170.000 ms, 0.139 ops/sec
RSA     2048   public         6 ops took 1.340 sec, avg 223.333 ms, 4.478 ops/sec
RSA     2048  private         4 ops took 1.140 sec, avg 285.000 ms, 3.509 ops/sec
DH      2048  key gen         4 ops took 1.040 sec, avg 260.000 ms, 3.846 ops/sec
DH      2048    agree        48 ops took 1.010 sec, avg 21.042 ms, 47.525 ops/sec
KYBER512    128  key gen        10 ops took 1.060 sec, avg 106.000 ms, 9.434 ops/sec
KYBER512    128    encap         8 ops took 1.070 sec, avg 133.750 ms, 7.477 ops/sec
KYBER512    128    decap        10 ops took 1.080 sec, avg 108.000 ms, 9.259 ops/sec
KYBER768    192  key gen         6 ops took 1.010 sec, avg 168.333 ms, 5.941 ops/sec
KYBER768    192    encap         6 ops took 1.290 sec, avg 215.000 ms, 4.651 ops/sec
KYBER768    192    decap         6 ops took 1.080 sec, avg 180.000 ms, 5.556 ops/sec
KYBER1024   256  key gen         4 ops took 1.080 sec, avg 270.000 ms, 3.704 ops/sec
KYBER1024   256    encap         4 ops took 1.310 sec, avg 327.500 ms, 3.053 ops/sec
KYBER1024   256    decap         4 ops took 1.120 sec, avg 280.000 ms, 3.571 ops/sec
ECC   [      SECP256R1]   256  key gen         4 ops took 1.710 sec, avg 427.500 ms, 2.339 ops/sec
ECDHE [      SECP256R1]   256    agree         4 ops took 1.710 sec, avg 427.500 ms, 2.339 ops/sec
ECDSA [      SECP256R1]   256     sign         4 ops took 1.730 sec, avg 432.500 ms, 2.312 ops/sec
ECDSA [      SECP256R1]   256   verify         4 ops took 1.160 sec, avg 290.000 ms, 3.448 ops/sec
CURVE  25519  key gen         3 ops took 1.040 sec, avg 346.667 ms, 2.885 ops/sec
CURVE  25519    agree         4 ops took 1.390 sec, avg 347.500 ms, 2.878 ops/sec
ED     25519  key gen        73 ops took 1.000 sec, avg 13.699 ms, 73.000 ops/sec
ED     25519     sign        62 ops took 1.010 sec, avg 16.290 ms, 61.386 ops/sec
ED     25519   verify        38 ops took 1.000 sec, avg 26.316 ms, 38.000 ops/sec
FALCON     1     sign         2 ops took 1.010 sec, avg 505.000 ms, 1.980 ops/sec
FALCON     1   verify        18 ops took 1.110 sec, avg 61.667 ms, 16.216 ops/sec
FALCON     5     sign         2 ops took 2.120 sec, avg 1060.000 ms, 0.943 ops/sec
FALCON     5   verify        10 ops took 1.010 sec, avg 101.000 ms, 9.901 ops/sec
ML-DSA    44  key gen         4 ops took 1.610 sec, avg 402.500 ms, 2.484 ops/sec
ML-DSA    44     sign         2 ops took 1.020 sec, avg 510.000 ms, 1.961 ops/sec
ML-DSA    44   verify         4 ops took 1.600 sec, avg 400.000 ms, 2.500 ops/sec
ML-DSA    65  key gen         2 ops took 1.450 sec, avg 725.000 ms, 1.379 ops/sec
ML-DSA    65     sign         2 ops took 2.470 sec, avg 1235.000 ms, 0.810 ops/sec
ML-DSA    65   verify         2 ops took 1.380 sec, avg 690.000 ms, 1.449 ops/sec
ML-DSA    87  key gen         2 ops took 2.500 sec, avg 1250.000 ms, 0.800 ops/sec
ML-DSA    87     sign         2 ops took 3.360 sec, avg 1680.000 ms, 0.595 ops/sec
ML-DSA    87   verify         2 ops took 2.430 sec, avg 1215.000 ms, 0.823 ops/sec
SPHINCS-FAST-SHA2     1     sign         2 ops took 13.970 sec, avg 6985.000 ms, 0.143 ops/sec
SPHINCS-FAST-SHA2     1   verify         4 ops took 1.670 sec, avg 417.500 ms, 2.395 ops/sec
SPHINCS-FAST-SHA2     3     sign         2 ops took 27.590 sec, avg 13795.000 ms, 0.072 ops/sec
SPHINCS-FAST-SHA2     3   verify         2 ops took 1.310 sec, avg 655.000 ms, 1.527 ops/sec
SPHINCS-FAST-SHA2     5     sign         2 ops took 56.740 sec, avg 28370.000 ms, 0.035 ops/sec
SPHINCS-FAST-SHA2     5   verify         2 ops took 1.340 sec, avg 670.000 ms, 1.493 ops/sec
SPHINCS-SMALL-SHA2     1     sign         2 ops took 286.220 sec, avg 143110.000 ms, 0.007 ops/sec
SPHINCS-SMALL-SHA2     1   verify         8 ops took 1.140 sec, avg 142.500 ms, 7.018 ops/sec
SPHINCS-SMALL-SHA2     3     sign         2 ops took 653.600 sec, avg 326800.000 ms, 0.003 ops/sec
SPHINCS-SMALL-SHA2     3   verify         6 ops took 1.430 sec, avg 238.333 ms, 4.196 ops/sec
SPHINCS-SMALL-SHA2     5     sign         2 ops took 630.910 sec, avg 315455.000 ms, 0.003 ops/sec
SPHINCS-SMALL-SHA2     5   verify         4 ops took 1.410 sec, avg 352.500 ms, 2.837 ops/sec
SPHINCS-FAST-SHAKE     1     sign         2 ops took 824.270 sec, avg 412135.000 ms, 0.002 ops/sec
SPHINCS-FAST-SHAKE     1   verify         2 ops took 50.040 sec, avg 25020.000 ms, 0.040 ops/sec
SPHINCS-FAST-SHAKE     3     sign         2 ops took 1332.240 sec, avg 666120.000 ms, 0.002 ops/sec
SPHINCS-FAST-SHAKE     3   verify         2 ops took 70.570 sec, avg 35285.000 ms, 0.028 ops/sec
SPHINCS-FAST-SHAKE     5     sign         2 ops took 2731.210 sec, avg 1365605.000 ms, 0.001 ops/sec
SPHINCS-FAST-SHAKE     5   verify         2 ops took 73.580 sec, avg 36790.000 ms, 0.027 ops/sec
```

### SPHINCS performance

SPHINCS+ implementation is generally very slow, especially when signing. SMALL variants are much slower than FAST, and SHAKE are much slower than SHA2, even when SHA2 is not HW-accelerated. 

It looks like SHA256 variant of SPHINCS+ is the only practical configuration for ESP32-C3 and many other microcontrollers that do not sport a SHA3 HW accelerator.

I had to tweak WolfSSL benchmark to run SHA2 variant, as it only used SHAKE by default.

# License

This repository includes the following source code:

- **liboqs** library included as a submodule, licensed under [MIT license](https://github.com/open-quantum-safe/liboqs/blob/main/LICENSE.txt) in general, but **liboqs** includes some third party libraries or modules that are licensed differently - see the source of the library.

- **WolfSSL** [library for PlatformIO](https://registry.platformio.org/libraries/wolfssl/wolfssl) which is directly copied into the source tree to allow for modifications, and is licensed under GPL-2.0.

Everything else is under GPL-2.0 license.