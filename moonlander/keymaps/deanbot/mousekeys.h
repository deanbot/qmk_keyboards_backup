#pragma once

#include QMK_KEYBOARD_H

typedef struct {
    bool    is_press_action;
    int     layer;
    int     state;
} tap;

void mousekey_tap (qk_tap_dance_state_t *state, void *user_data);
void mousekey_finished (qk_tap_dance_state_t *state, void *user_data);
void mousekey_reset (qk_tap_dance_state_t *state, void *user_data);
