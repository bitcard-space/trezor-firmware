/*
 * This file is part of the Trezor project, https://trezor.io/
 *
 * Copyright (c) SatoshiLabs
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "py/objstr.h"
#include "string.h"
#include "memzero.h"
#include "sha2.h"

/// package: trezorcrypto.__init__

/// class sha256:
///     """
///     SHA256 context.
///     """
///     block_size: int
///     digest_size: int
typedef struct _mp_obj_Sha256_t {
  mp_obj_base_t base;
  SHA256_CTX ctx;
} mp_obj_Sha256_t;

STATIC mp_obj_t mod_trezorcrypto_Sha256_update(mp_obj_t self, mp_obj_t data);

/// def __init__(self, __data: AnyStr | None = None) -> None:
///     """
///     Creates a hash context object.
///     """
STATIC mp_obj_t mod_trezorcrypto_Sha256_make_new(const mp_obj_type_t *type,
                                                 size_t n_args, size_t n_kw,
                                                 const mp_obj_t *args) {
  mp_arg_check_num(n_args, n_kw, 0, 1, false);
  mp_obj_Sha256_t *o = ((mp_obj_Sha256_t *)(m_malloc_with_finaliser(sizeof(mp_obj_Sha256_t))));
  o->base.type = type;
  sha256_Init(&(o->ctx));
  // constructor called with bytes/str as first parameter
  if (n_args == 1) {
    mod_trezorcrypto_Sha256_update(MP_OBJ_FROM_PTR(o), args[0]);
  }
  return MP_OBJ_FROM_PTR(o);
}

/// def update(self, __data: AnyStr) -> None:
///     """
///     Update the hash context with hashed data.
///     """
STATIC mp_obj_t mod_trezorcrypto_Sha256_update(mp_obj_t self, mp_obj_t data) {
  mp_obj_Sha256_t *o = MP_OBJ_TO_PTR(self);
  mp_buffer_info_t msg = {0};
  mp_get_buffer_raise(data, &msg, MP_BUFFER_READ);
  if (msg.len > 0) {
    sha256_Update(&(o->ctx), msg.buf, msg.len);
  }
  return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_trezorcrypto_Sha256_update_obj,
                                 mod_trezorcrypto_Sha256_update);

/// def digest(self) -> bytes:
///     """
///     Returns the digest of hashed data.
///     """
STATIC mp_obj_t mod_trezorcrypto_Sha256_digest(mp_obj_t self) {
  mp_obj_Sha256_t *o = MP_OBJ_TO_PTR(self);
  vstr_t hash = {0};
  vstr_init_len(&hash, SHA256_DIGEST_LENGTH);
  SHA256_CTX ctx = {0};
  memcpy(&ctx, &(o->ctx), sizeof(SHA256_CTX));
  sha256_Final(&ctx, (uint8_t *)hash.buf);
  memzero(&ctx, sizeof(SHA256_CTX));
  return mp_obj_new_str_from_vstr(&hash);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_trezorcrypto_Sha256_digest_obj,
                                 mod_trezorcrypto_Sha256_digest);

STATIC mp_obj_t mod_trezorcrypto_Sha256___del__(mp_obj_t self) {
  mp_obj_Sha256_t *o = MP_OBJ_TO_PTR(self);
  memzero(&(o->ctx), sizeof(SHA256_CTX));
  return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_trezorcrypto_Sha256___del___obj,
                                 mod_trezorcrypto_Sha256___del__);

STATIC const mp_rom_map_elem_t mod_trezorcrypto_Sha256_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_update),
     MP_ROM_PTR(&mod_trezorcrypto_Sha256_update_obj)},
    {MP_ROM_QSTR(MP_QSTR_digest),
     MP_ROM_PTR(&mod_trezorcrypto_Sha256_digest_obj)},
    {MP_ROM_QSTR(MP_QSTR___del__),
     MP_ROM_PTR(&mod_trezorcrypto_Sha256___del___obj)},
    {MP_ROM_QSTR(MP_QSTR_block_size), MP_ROM_INT(SHA256_BLOCK_LENGTH)},
    {MP_ROM_QSTR(MP_QSTR_digest_size), MP_ROM_INT(SHA256_DIGEST_LENGTH)},
};
STATIC MP_DEFINE_CONST_DICT(mod_trezorcrypto_Sha256_locals_dict,
                            mod_trezorcrypto_Sha256_locals_dict_table);

static MP_DEFINE_CONST_OBJ_TYPE(
    mod_trezorcrypto_Sha256_type,
    MP_QSTR_Sha256,
    MP_TYPE_FLAG_NONE,
    make_new, mod_trezorcrypto_Sha256_make_new,
    locals_dict, &mod_trezorcrypto_Sha256_locals_dict
);
