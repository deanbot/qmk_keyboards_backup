#include "mousekeys.h"

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    TRIPLE_TAP,
    TRIPLE_HOLD,
    IGNORE_TAP,
    SHIFTED_ON_INITAL,
    MORE_TAPS
};

void tap_key(uint16_t keycode)
{
  register_code  (keycode);
  unregister_code(keycode);
}

static tap mtap_state = {
  .is_press_action = true,
  .state = 0,
  .layer = -1
};

void mousekey_tap (qk_tap_dance_state_t *state, void *user_data) {
  if (user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    mtap_state.layer = pair->kc2;
  }
}

void mousekey_finished (qk_tap_dance_state_t *state, void *user_data) {
  uint16_t mouse_key = KC_MS_BTN1;
  int layer = -1;

  if (user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    mouse_key = pair->kc1;
    layer = pair->kc2;
  }

  uint8_t st = SINGLE_TAP;

  if (state->count == 1) {
      if (!state->pressed) {
        st = SINGLE_TAP;
      } else {
        st = SINGLE_HOLD;
      }
  } else if (state->count == 2) {
      if (state->pressed) {
          st = DOUBLE_HOLD;
      } else {
          st = DOUBLE_TAP;
      }
  } if (state->count == 3) {
      st = DOUBLE_SINGLE_TAP;
  }

  mtap_state.state = st;
  switch (mtap_state.state) {
    case SINGLE_HOLD: layer_on(layer); break;
    case SINGLE_TAP: tap_key(mouse_key); break;
    case DOUBLE_SINGLE_TAP: break;
    case DOUBLE_HOLD: register_code(mouse_key); break;
    case DOUBLE_TAP: tap_key(mouse_key); tap_key(mouse_key); break;
  }
}

void mousekey_reset (qk_tap_dance_state_t *state, void *user_data) {
  uint16_t mouse_key = KC_MS_BTN1;
  int layer = -1;

  if (user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    mouse_key = pair->kc1;
    layer = pair->kc2;
  }

  switch (mtap_state.state) {
    case SINGLE_HOLD: layer_off(layer); break;
    case TRIPLE_TAP:
    case DOUBLE_HOLD: unregister_code(mouse_key); break;
  }
  mtap_state.state = 0;
}
