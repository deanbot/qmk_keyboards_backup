#include "repeat.h"

uint16_t last_key = 0;
uint16_t last_mods = 0;

bool process_repeat_last_key(
    uint16_t keycode,
    keyrecord_t *record,
    uint16_t expected_keycode,
    uint16_t optional_layer_code)
{
  if (record->event.pressed)
  {
    if (keycode == expected_keycode)
    {
      if (last_mods != 0)
      {
        register_mods(last_mods);
      }
      tap_code(last_key);
      if (last_mods != 0)
      {
        unregister_mods(last_mods);
      }

      return false;
    }
    else
    {
      if (optional_layer_code != keycode) {
        last_key = keycode;
        last_mods = get_mods();
      }

      return true;
    }
  }
  return true;
}
