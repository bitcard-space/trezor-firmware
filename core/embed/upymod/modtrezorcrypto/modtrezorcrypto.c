#include "py/builtin.h"
#include "py/runtime.h"
// #include <trezor_rtl.h>

static mp_obj_t ui_wait_callback = mp_const_none;

static void wrapped_ui_wait_callback(uint32_t current, uint32_t total) {
  if (mp_obj_is_callable(ui_wait_callback)) {
    mp_call_function_2_protected(ui_wait_callback, mp_obj_new_int(current),
                                 mp_obj_new_int(total));
  }
}

#include "modtrezorcrypto-bech32.h"
#include "modtrezorcrypto-bip32.h"
#ifdef USE_SECP256K1_ZKP
#include "modtrezorcrypto-bip340.h"
#endif
#include "modtrezorcrypto-bip39.h"
#include "modtrezorcrypto-blake256.h"
#include "modtrezorcrypto-blake2b.h"
#include "modtrezorcrypto-blake2s.h"
#include "modtrezorcrypto-chacha20poly1305.h"
// #include "modtrezorcrypto-crc.h"
// #include "modtrezorcrypto-curve25519.h"
// #include "modtrezorcrypto-ed25519.h"
// #if USE_THP
// #include "modtrezorcrypto-elligator2.h"
// #endif
// #include "modtrezorcrypto-groestl.h"
// #include "modtrezorcrypto-hmac.h"
// #include "modtrezorcrypto-nist256p1.h"
// #include "modtrezorcrypto-pbkdf2.h"
// #include "modtrezorcrypto-random.h"
// #include "modtrezorcrypto-ripemd160.h"
// #include "modtrezorcrypto-secp256k1.h"
// #include "modtrezorcrypto-sha1.h"
// #include "modtrezorcrypto-sha256.h"
// #include "modtrezorcrypto-sha3-256.h"
// #include "modtrezorcrypto-sha3-512.h"
// #include "modtrezorcrypto-sha512.h"
// #include "modtrezorcrypto-shamir.h"
// #include "modtrezorcrypto-slip39.h"
// #ifdef USE_OPTIGA
// #include "modtrezorcrypto-optiga.h"
// #endif
// #if !BITCOIN_ONLY
// #include "modtrezorcrypto-cardano.h"
// #include "modtrezorcrypto-monero.h"
// #include "modtrezorcrypto-nem.h"
// #endif


// info()
static mp_obj_t py_subsystem_info(void) {
    return MP_OBJ_NEW_SMALL_INT(42);
}
MP_DEFINE_CONST_FUN_OBJ_0(subsystem_info_obj, py_subsystem_info);

static const mp_rom_map_elem_t mp_module_trezorcrypto_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_trezorcrypto) },
    { MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&subsystem_info_obj) },
};

static MP_DEFINE_CONST_DICT(mp_module_trezorcrypto_globals, mp_module_trezorcrypto_globals_table);

const mp_obj_module_t mp_module_trezorcrypto = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&mp_module_trezorcrypto_globals,
};

// MP_REGISTER_MODULE(MP_QSTR_subsystem, mp_module_subsystem);

MP_REGISTER_MODULE(MP_QSTR_trezorcrypto, mp_module_trezorcrypto);

#ifdef USE_SECP256K1_ZKP
void secp256k1_default_illegal_callback_fn(const char *str, void *data) {
  (void)data;
  mp_raise_ValueError(str);
  return;
}

void secp256k1_default_error_callback_fn(const char *str, void *data) {
  (void)data;
  error_shutdown(str);
}
#endif

// #endif  // MICROPY_PY_TREZORCRYPTO
