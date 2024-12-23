#include "py/builtin.h"
#include "py/runtime.h"
#include <trezor_rtl.h>

#include "modtrezorcrypto-bech32.h"

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
