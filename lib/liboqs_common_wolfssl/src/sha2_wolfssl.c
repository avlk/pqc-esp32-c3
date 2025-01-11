/**
 * \file sha2_ossl.c
 * \brief Implementation of the OQS SHA2 API via calls to OpenSSL's SHA-2 functions
 *
 * SPDX-License-Identifier: MIT
 */

#include <oqs/oqs.h>

#include "sha2.h"

#include <wolfssl/wolfcrypt/sha256.h>
#include <wolfssl/wolfcrypt/sha512.h>

#define SHA_ERR printf

void OQS_SHA2_sha256(uint8_t *output, const uint8_t *input, size_t inplen) {
    wc_Sha256 sha;
    int ret = wc_InitSha256(&sha);
    if (ret != 0) {
        SHA_ERR("wc_InitSha256 failed\n");
        return;
    }
    ret = wc_Sha256Update(&sha, input, inplen);
    if (ret != 0) {
        SHA_ERR("wc_Sha256Update failed\n");
    } else {
        ret = wc_Sha256Final(&sha, output);
        if (ret != 0)
            SHA_ERR("wc_Sha256Final failed\n");
    }
    wc_Sha256Free(&sha); 
}

void OQS_SHA2_sha384(uint8_t *output, const uint8_t *input, size_t inplen) {
    wc_Sha384 sha;
    int ret = wc_InitSha384(&sha);
    if (ret != 0) {
        SHA_ERR("wc_InitSha384 failed\n");
        return;
    }
    ret = wc_Sha384Update(&sha, input, inplen);
    if (ret != 0) {
        SHA_ERR("wc_Sha384Update failed\n");
    } else {
        ret = wc_Sha384Final(&sha, output);
        if (ret != 0)
            SHA_ERR("wc_Sha384Final failed\n");
    }
    wc_Sha384Free(&sha); 
}

void OQS_SHA2_sha512(uint8_t *output, const uint8_t *input, size_t inplen) {
    wc_Sha512 sha;
    int ret = wc_InitSha512(&sha);
    if (ret != 0) {
        SHA_ERR("wc_InitSha512 failed\n");
        return;
    }
    ret = wc_Sha512Update(&sha, input, inplen);
    if (ret != 0) {
        SHA_ERR("wc_Sha512Update failed\n");
    } else {
        ret = wc_Sha512Final(&sha, output);
        if (ret != 0)
            SHA_ERR("wc_Sha512Final failed\n");
    }
    wc_Sha512Free(&sha);
}

#define SHA2_BLOCK_SIZE 64

void OQS_SHA2_sha256_inc_init(OQS_SHA2_sha256_ctx *state) {
	wc_Sha256 *sha = calloc(1, sizeof(wc_Sha256));
    if (!sha) {
        SHA_ERR("SHA256 calloc failed\n");
        state->ctx = NULL;
        return;
    }
    int ret = wc_InitSha256(sha);
    if (ret != 0) {
        SHA_ERR("SHA256 init failed\n");
        free(sha);
        sha = NULL;
    }
	state->ctx = sha;
}

void OQS_SHA2_sha256_inc_blocks(OQS_SHA2_sha256_ctx *state, const uint8_t *in, size_t inblocks) {
    if (!state || !state->ctx)
        return;
    wc_Sha256 *sha = (wc_Sha256 *)state->ctx;
    int ret = wc_Sha256Update(sha, in, inblocks * SHA2_BLOCK_SIZE);
    if (ret != 0) {
        SHA_ERR("wc_Sha256Update failed\n");
    }
}

void OQS_SHA2_sha256_inc_finalize(uint8_t *out, OQS_SHA2_sha256_ctx *state, const uint8_t *in, size_t inlen) {
    if (!state || !state->ctx)
        return;
    wc_Sha256 *sha = (wc_Sha256 *)state->ctx;
    int ret = wc_Sha256Update(sha, in, inlen);
    if (ret != 0) {
        SHA_ERR("wc_Sha256Update failed\n");
    }
    ret = wc_Sha256Final(sha, out);
    if (ret != 0) {
        SHA_ERR("wc_Sha256Final failed\n");
    }
    wc_Sha256Free(sha);
    free(state->ctx);
	state->ctx = NULL;
}

void OQS_SHA2_sha256_inc_ctx_release(OQS_SHA2_sha256_ctx *state) {
    if (!state || !state->ctx)
        return;
    wc_Sha256 *sha = (wc_Sha256 *)state->ctx;
    wc_Sha256Free(sha);
    free(state->ctx);
	state->ctx = NULL;
}

void OQS_SHA2_sha256_inc_ctx_clone(OQS_SHA2_sha256_ctx *dest, const OQS_SHA2_sha256_ctx *src) {
	wc_Sha256 *sha = calloc(1, sizeof(wc_Sha256));
    if (!sha) {
        SHA_ERR("SHA256 calloc failed\n");
        dest->ctx = NULL;
        return;
    }
    int ret = wc_Sha256Copy(src->ctx, sha);
    if (ret != 0) {
        SHA_ERR("wc_Sha256Copy failed\n");
    }
	dest->ctx = sha;
}

void OQS_SHA2_sha384_inc_init(OQS_SHA2_sha384_ctx *state) {
	wc_Sha384 *sha = calloc(1, sizeof(wc_Sha384));
    if (!sha) {
        SHA_ERR("SHA384 calloc failed\n");
        state->ctx = NULL;
        return;
    }
    int ret = wc_InitSha384(sha);
    if (ret != 0) {
        SHA_ERR("SHA384 init failed\n");
        free(sha);
        sha = NULL;
    }
	state->ctx = sha;
}

void OQS_SHA2_sha384_inc_blocks(OQS_SHA2_sha384_ctx *state, const uint8_t *in, size_t inblocks) {
    if (!state || !state->ctx)
        return;
    wc_Sha384 *sha = (wc_Sha384 *)state->ctx;
    int ret = wc_Sha384Update(sha, in, inblocks * 2 * SHA2_BLOCK_SIZE);
    if (ret != 0) {
        SHA_ERR("wc_Sha384Update failed\n");
    }
}

void OQS_SHA2_sha384_inc_finalize(uint8_t *out, OQS_SHA2_sha384_ctx *state, const uint8_t *in, size_t inlen) {
    if (!state || !state->ctx)
        return;
    wc_Sha384 *sha = (wc_Sha384 *)state->ctx;
    int ret = wc_Sha384Update(sha, in, inlen);
    if (ret != 0) {
        SHA_ERR("wc_Sha384Update failed\n");
    }
    ret = wc_Sha384Final(sha, out);
    if (ret != 0) {
        SHA_ERR("wc_Sha384Final failed\n");
    }
    wc_Sha384Free(sha);
    free(state->ctx);
	state->ctx = NULL;
}

void OQS_SHA2_sha384_inc_ctx_release(OQS_SHA2_sha384_ctx *state) {
    if (!state || !state->ctx)
        return;
    wc_Sha384 *sha = (wc_Sha384 *)state->ctx;
    wc_Sha384Free(sha);
    free(state->ctx);
	state->ctx = NULL;
}

void OQS_SHA2_sha384_inc_ctx_clone(OQS_SHA2_sha384_ctx *dest, const OQS_SHA2_sha384_ctx *src) {
	wc_Sha384 *sha = calloc(1, sizeof(wc_Sha384));
    if (!sha) {
        SHA_ERR("SHA384 clone failed\n");
        dest->ctx = NULL;
        return;
    }
    int ret = wc_Sha384Copy(src->ctx, sha);
    if (ret != 0) {
        SHA_ERR("wc_Sha384Copy failed\n");
    }
	dest->ctx = sha;
}

void OQS_SHA2_sha512_inc_init(OQS_SHA2_sha512_ctx *state) {
	wc_Sha512 *sha = calloc(1, sizeof(wc_Sha512));
    if (!sha) {
        SHA_ERR("SHA512 calloc failed\n");
        state->ctx = NULL;
        return;
    }
    int ret = wc_InitSha512(sha);
    if (ret != 0) {
        SHA_ERR("SHA512 init failed\n");
        free(sha);
        sha = NULL;
    }
	state->ctx = sha;
}

void OQS_SHA2_sha512_inc_blocks(OQS_SHA2_sha512_ctx *state, const uint8_t *in, size_t inblocks) {
    if (!state || !state->ctx)
        return;
    wc_Sha512 *sha = (wc_Sha512 *)state->ctx;
    int ret = wc_Sha512Update(sha, in, inblocks * 2 * SHA2_BLOCK_SIZE);
    if (ret != 0) {
        SHA_ERR("wc_Sha512Update failed\n");
    }
}

void OQS_SHA2_sha512_inc_finalize(uint8_t *out, OQS_SHA2_sha512_ctx *state, const uint8_t *in, size_t inlen) {
    if (!state || !state->ctx)
        return;
    wc_Sha512 *sha = (wc_Sha512 *)state->ctx;
    int ret = wc_Sha512Update(sha, in, inlen);
    if (ret != 0) {
        SHA_ERR("wc_Sha512Update failed\n");
    }
    ret = wc_Sha512Final(sha, out);
    if (ret != 0) {
        SHA_ERR("wc_Sha512Final failed\n");
    }
    wc_Sha512Free(sha);
    free(state->ctx);
	state->ctx = NULL;
}

void OQS_SHA2_sha512_inc_ctx_release(OQS_SHA2_sha512_ctx *state) {
    if (!state || !state->ctx)
        return;
    wc_Sha512 *sha = (wc_Sha512 *)state->ctx;
    wc_Sha512Free(sha);
    free(state->ctx);
	state->ctx = NULL;
}

void OQS_SHA2_sha512_inc_ctx_clone(OQS_SHA2_sha512_ctx *dest, const OQS_SHA2_sha512_ctx *src) {
	wc_Sha512 *sha = calloc(1, sizeof(wc_Sha512));
    if (!sha) {
        SHA_ERR("SHA512 calloc failed\n");
        dest->ctx = NULL;
        return;
    }
    int ret = wc_Sha512Copy(src->ctx, sha);
    if (ret != 0) {
        SHA_ERR("wc_Sha512Copy failed\n");
    }
	dest->ctx = sha;
}

