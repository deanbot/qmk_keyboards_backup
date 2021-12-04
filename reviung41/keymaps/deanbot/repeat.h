#pragma once

#include "quantum.h"
#include <stdint.h>
#include "tmk_core/common/action.h"

uint16_t last_key;
uint16_t last_mods;

bool process_repeat_last_key(
    uint16_t keycode,
    keyrecord_t *record,
    uint16_t expected_keycode,
    uint16_t optional_layer_code);
