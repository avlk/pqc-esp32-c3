Import("env")
import os
import shutil
import subprocess

liboqs_public_headers = [
    "oqs.h",
    "common/common.h",
    "common/rand/rand.h",
    "kem/kem.h",
    "sig/sig.h",
    "kem/bike/kem_bike.h",
    "kem/frodokem/kem_frodokem.h",
    "kem/ntruprime/kem_ntruprime.h",
    "kem/classic_mceliece/kem_classic_mceliece.h",
    "kem/hqc/kem_hqc.h",
    "kem/kyber/kem_kyber.h",
    "kem/ml_kem/kem_ml_kem.h",
    "sig/dilithium/sig_dilithium.h",
    "sig/ml_dsa/sig_ml_dsa.h",
    "sig/falcon/sig_falcon.h",
    "sig/sphincs/sig_sphincs.h",
    ]

liboqs_internal_headers = [
    "common/aes/aes.h",
    "common/rand/rand_nist.h",
    "common/sha2/sha2.h",
    "common/sha3/sha3.h",
    "common/sha3/sha3x4.h",
]


install_dir="install/inc/oqs"

def install_oqs_headers():
    print("Installing OQS headers into ", install_dir)
    try:
        os.makedirs(install_dir)
    except os.error as err:
        pass

    headers = []
    headers.extend(liboqs_public_headers)
    headers.extend(liboqs_internal_headers)

    for src in headers:
        shutil.copy("lib/liboqs/src/"+src, install_dir)

    shutil.copy("oqsconfig.in.h", install_dir + "/oqsconfig.h")
    shutil.copy("liboqs-library.json", "lib/liboqs/library.json")


install_oqs_headers()