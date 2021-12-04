/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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
#include "oneshot.h"
#include "swapper.h"
#include "mousekeys.h"

// utilities
#define S_T(...)  LSFT_T(__VA_ARGS__)
#define C_T(...)  CTL_T(__VA_ARGS__)
#define A_T(...)  ALT_T(__VA_ARGS__)
#define G_T(...)  LGUI_T(__VA_ARGS__)

enum layer_names {
  _BASE,
  _FN,
  _NAV,
  _MOUSE,
  _SYM,
  _NUM,
  _META,
  _QWERTY
};

enum custom_keycodes {
    SEL_L = SAFE_RANGE,
    SW_PROF,
    SW_WIN,
    SW_LANG,
    OS_SHFT,
    OS_ALT,
    OS_GUI,
    OS_CTRL,
    VRSN
};

enum tap_dance_codes {
  TD_M1_MK,
  TD_M2_META
};

// tap dance
#define M2_META TD(TD_M2_META)
#define M1_MK TD(TD_M1_MK)

// define keycodes to make layers easier to read
#define O_MEH OSM(MOD_MEH)
#define O_SYM OSL(_SYM)
#define M_NAV MO(_NAV)
#define M_SYM MO(_SYM)
#define SP_MK LT(_MOUSE, KC_SPACE)
#define O_AGR OSM(MOD_RALT)

// Meta tokens
#define T_QWERTY TO(_QWERTY)
#define T_BASE TO(_BASE)
#define T_MOUSE TO(_MOUSE)
#define T_NAV TO(_NAV)
#define M_META MO(_META)
#define WAKE KC_SYSTEM_WAKE
#define SLEEP KC_SYSTEM_SLEEP
#define M_PREV KC_MEDIA_PREV_TRACK
#define M_NEXT KC_MEDIA_NEXT_TRACK
#define VOL_UP KC_AUDIO_VOL_UP
#define VOL_DOWN KC_AUDIO_VOL_DOWN
#define MUTE KC_AUDIO_MUTE
#define M_STOP KC_MEDIA_STOP
#define M_PAUSE KC_MEDIA_PLAY_PAUSE
#define BR_UP KC_BRIGHTNESS_UP
#define BR_DOWN KC_BRIGHTNESS_DOWN

// Nav tokens
#define HUD LGUI(KC_TAB)
#define REDO LCTL(KC_Y)
#define COPY LCTL(KC_C)
#define CUT LCTL(KC_X)
#define PASTE LCTL(KC_V)
#define UNDO LCTL(KC_Z)
#define ESC KC_ESCAPE
#define BS KC_BSPACE
#define DEL KC_DELETE
#define APP KC_APPLICATION
#define DEL_LINE LCTL(LSFT(KC_K))
#define CKP_0 LCTL(KC_KP_0)
#define CKP_MIN LCTL(KC_KP_MINUS)
#define CKP_PLS LCTL(KC_KP_PLUS)
#define PS KC_PSCREEN
#define SEL_HOME LSFT(KC_HOME)
#define SEL_END LSFT(KC_END)
#define SEL_WORD LSFT(KC_D)
#define FOC_0 LCTL(KC_0)
#define FOC_1 LCTL(KC_1)
#define FOC_2 LCTL(KC_2)
#define FOC_3 LCTL(KC_3)
#define TERM LCTL(KC_GRAVE)
#define SCREEN_L G(S(KC_LEFT))
#define SCREEN_R G(S(KC_RIGHT))
#define HINT LCTL(KC_SPACE)
#define RFCTR LCTL(KC_DOT)

// Mouse keycodes
#define INCOG LCTL(LSFT(KC_N))
#define RETAB LCTL(LSFT(KC_T))
#define H_RFRSH C(S(KC_R))
#define DUPT LCTL(LSFT(KC_K))
#define PREVT LCTL(KC_PGUP)
#define NEXTT LCTL(KC_PGDOWN)
#define NEWTAB LCTL(KC_T)
#define CLOSET LCTL(KC_W)
#define MLEFT KC_MS_LEFT
#define MDOWN KC_MS_DOWN
#define MUP KC_MS_UP
#define MRIGHT KC_MS_RIGHT
#define MW_UP KC_MS_WH_UP
#define MW_DOWN KC_MS_WH_DOWN
#define MW_LEFT KC_MS_WH_LEFT
#define MW_RIGHT KC_MS_WH_RIGHT
#define TOP LCTL(KC_HOME)
#define BOTTOM LCTL(KC_END)
#define MBTN3 KC_MS_BTN3
#define MBTN2 KC_MS_BTN2
#define MBTN1 KC_MS_BTN1
#define BACK LALT(KC_LEFT)
#define FWD LALT(KC_RIGHT)
#define DEVT LCTL(LSFT(KC_I))

// sym tokens
#define LBRACK KC_LBRACKET
#define RBRACK KC_RBRACKET

// Qmisc tokens
#define TRANS KC_TRANSPARENT

// Shared
#define __________________BLANK_5___________________        TRANS,    TRANS,    TRANS,    TRANS,    TRANS
#define ____________________NO_5____________________        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO
#define ______________MODS_L______________                  OS_GUI,   OS_ALT,   OS_CTRL,  OS_SHFT
#define ______________MODS_R______________                  OS_SHFT,  OS_CTRL,  OS_ALT,   OS_GUI

// Base layer
#define _________________COLEMAK_L1_________________        KC_Q,     KC_W,     KC_F,     KC_P,     KC_B
#define _________________COLEMAK_L2_________________        KC_A,     KC_R,     KC_S,     KC_T,     KC_G
#define _________________COLEMAK_L3_________________        KC_Z,     KC_X,     KC_C,     KC_D,     KC_V

#define _________________COLEMAK_R1_________________        KC_J,     KC_L,     KC_U,     KC_Y,     KC_QUOT
#define _________________COLEMAK_R2_________________        KC_M,     KC_N,     KC_E,     KC_I,     KC_O
#define _________________COLEMAK_R3_________________        KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SCOLON

// Nav layer
#define __________________NAV_L1____________________        T_BASE,   O_MEH,    KC_NO,    APP,      SW_LANG
#define __________________NAV_L2____________________        ______________MODS_L______________,     SW_WIN
#define __________________NAV_L3____________________        HUD,      ESC,      SCREEN_R, KC_TAB,   SW_PROF

#define __________________NAV_R1____________________        KC_PGDOWN,KC_HOME,  KC_INS,   KC_END,   TERM
#define __________________NAV_R2____________________        KC_PGUP,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT
#define __________________NAV_R3____________________        PS,       BS,       SEL_L,    DEL,      KC_CAPS

// Sym layer
#define __________________SYM_L1____________________        KC_TILD,  KC_LCBR,  LBRACK,  KC_LPRN,   KC_SCOLON
#define __________________SYM_L2____________________        KC_MINUS, KC_PLUS,  KC_EQUAL,KC_UNDS,   KC_HASH
#define __________________SYM_L3____________________        KC_ASTR,  KC_PIPE,  KC_AT,   KC_SLASH,  KC_PERC

#define __________________SYM_R1____________________        KC_CIRC,    KC_RPRN,  RBRACK,  KC_RCBR, KC_GRAVE
#define __________________SYM_R2____________________        KC_DLR,   ______________MODS_R______________
#define __________________SYM_R3____________________        TRANS,    KC_BSLASH,KC_AMPR, KC_EXLM,  KC_QUES

// Num layer
#define ___________________NUM_L1___________________        KC_7,     KC_5,     KC_3,     KC_1,     KC_9
#define ___________________NUM_L2___________________        ______________MODS_L______________,     KC_F11
#define ___________________NUM_L3___________________        KC_F7,    KC_F5,    KC_F3,    KC_F1,    KC_F9

#define ___________________NUM_R1___________________        KC_8,     KC_0,     KC_2,     KC_4,     KC_6
#define ___________________NUM_R2___________________        KC_F12,   ______________MODS_R______________
#define ___________________NUM_R3___________________        KC_F8,    KC_F10,   KC_F2,    KC_F4,    KC_F6

// Mouse layer
#define _________________MOUSE_L1___________________        CKP_PLS,  MBTN2,    MW_UP,    MBTN3,    CKP_MIN
#define _________________MOUSE_L2___________________        MLEFT,    MUP,      MDOWN,    MRIGHT,   H_RFRSH
#define _________________MOUSE_L3___________________        CKP_0,    MW_LEFT,  MW_DOWN,  MW_RIGHT, BACK

#define _________________MOUSE_R1___________________        DEVT,     PREVT,    TOP,      NEXTT,    T_BASE
#define _________________MOUSE_R2___________________        CLOSET,   ______________MODS_R______________
#define _________________MOUSE_R3___________________        FWD,      NEWTAB,   BOTTOM,   DUPT,     RETAB

// Meta layer
#define _________________META_L1____________________        SLEEP,    WAKE,     KC_NO,    T_BASE,   RESET
#define _________________META_L2____________________        KC_NO,    BR_UP,    BR_DOWN,  T_MOUSE,  KC_NO
#define _________________META_L3____________________        T_QWERTY, KC_NO,    KC_NO,    T_NAV,    EEP_RST

#define _________________META_R1____________________        M_PAUSE,  RGB_SPD,  RGB_SPI,  RGB_MOD,  RGB_TOG
#define _________________META_R2____________________        M_STOP,   RGB_VAD,  RGB_VAI,  RGB_HUD,  RGB_HUI
#define _________________META_R3____________________        MUTE,     M_PREV,   VOL_DOWN, VOL_UP,   M_NEXT

// Qwerty layer
#define ________________QWERTY_L1___________________        KC_Q,     KC_W,     KC_E,     KC_R,      KC_T
#define ________________QWERTY_L2___________________        KC_A,     KC_S,     KC_D,     KC_F,      KC_G
#define ________________QWERTY_L3___________________        KC_Z,     KC_X,     KC_C,     KC_V,      KC_B

#define ________________QWERTY_R1___________________        KC_Y,     KC_U,     KC_I,     KC_O,     KC_P
#define ________________QWERTY_R2___________________        KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN
#define ________________QWERTY_R3___________________        KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH

// layer tokens
#define LAYOUT_moon(...)       LAYOUT_moonlander(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_moon(
        _______, ____________________NO_5____________________,_______,         _______, ____________________NO_5____________________,_______,
        O_MEH,   _________________COLEMAK_L1_________________,_______,         _______, _________________COLEMAK_R1_________________,OSM(MOD_RALT),
        O_SYM,   _________________COLEMAK_L2_________________,_______,         _______, _________________COLEMAK_R2_________________,OSM(MOD_LALT),
        M2_META, _________________COLEMAK_L3_________________,                          _________________COLEMAK_R3_________________,OSM(MOD_LCTL),
        _______, _______, _______, O_AGR,   M_NAV,            HINT,            RFCTR,            M_SYM,   KC_LGUI, _______, _______, _______,
                                            OS_SHFT,  MBTN1,  _______,         _______, ESC,   SP_MK
    ),
    [_NAV] = LAYOUT_moon(
        _______, __________________BLANK_5___________________,_______,         _______, __________________BLANK_5___________________,_______,
        TRANS,   __________________NAV_L1____________________,_______,         _______, __________________NAV_R1____________________,TO(_BASE),
        TRANS,   __________________NAV_L2____________________,_______,         _______, __________________NAV_R2____________________,TRANS,
        TRANS,   __________________NAV_L3____________________,                          __________________NAV_R3____________________,TRANS,
        _______, _______, _______, TRANS,   TRANS,            TRANS,           TRANS,            TRANS,   TRANS,   _______, _______, _______,
                                            TRANS,   TRANS,  _______,          _______, KC_SPACE, KC_ENTER
    ),
    [_SYM] = LAYOUT_moon(
        _______, __________________BLANK_5___________________,_______,         _______, __________________BLANK_5___________________,_______,
        TRANS,   __________________SYM_L1____________________,_______,         _______, __________________SYM_R1____________________,TRANS,
        TRANS,   __________________SYM_L2____________________,_______,         _______, __________________SYM_R2____________________,TRANS,
        TRANS,   __________________SYM_L3____________________,                          __________________SYM_R3____________________,TRANS,
        _______, _______, _______, TRANS,   TRANS,            TRANS,           TRANS,            TRANS,   TRANS,   _______, _______, _______,
                                            M_META,   TRANS,  _______,         _______, TRANS,   TRANS
    ),
    [_NUM] = LAYOUT_moon(
        _______, __________________BLANK_5___________________,_______,         _______, __________________BLANK_5___________________,_______,
        TRANS,   ___________________NUM_L1___________________,_______,         _______, ___________________NUM_R1___________________,TO(_BASE),
        TRANS,   ___________________NUM_L2___________________,_______,         _______, ___________________NUM_R2___________________,TRANS,
        TRANS,   ___________________NUM_L3___________________,                          ___________________NUM_R3___________________,TRANS,
        _______, _______, _______, TRANS,   TRANS,            TRANS,           TRANS,            TRANS,   TRANS,   _______, _______, _______,
                                            TRANS,   TRANS,  _______,          _______, TRANS,   TRANS
    ),
    [_MOUSE] = LAYOUT_moon(
        _______, __________________BLANK_5___________________,_______,         _______, __________________BLANK_5___________________,_______,
        TRANS,   _________________MOUSE_L1___________________,_______,         _______, _________________MOUSE_R1___________________,TO(_BASE),
        TRANS,   _________________MOUSE_L2___________________,_______,         _______, _________________MOUSE_R2___________________,TRANS,
        TRANS,   _________________MOUSE_L3___________________,                          _________________MOUSE_R3___________________,TRANS,
        _______, _______, _______, TRANS,   MW_DOWN,          TRANS,           TRANS,            MW_DOWN, TRANS,   _______, _______, _______,
                                            MBTN1,   TRANS,   _______,         _______, TRANS,   MBTN1
    ),
    [_META] = LAYOUT_moon(
        _______, __________________BLANK_5___________________,_______,         _______, __________________BLANK_5___________________,_______,
        TRANS,   _________________META_L1____________________,_______,         _______, _________________META_R1____________________,RESET,
        TRANS,   _________________META_L2____________________,_______,         _______, _________________META_R2____________________,TRANS,
        TRANS,   _________________META_L3____________________,                          _________________META_R3____________________,TRANS,
        _______, _______, _______, TRANS,   TRANS,            TRANS,           TRANS,            TRANS,   TRANS,   _______, _______, _______,
                                            TRANS,   TRANS,   _______,         _______, TRANS,   TRANS
    ),
    [_QWERTY] = LAYOUT_moon(
        _______, __________________BLANK_5___________________,_______,        _______, __________________BLANK_5___________________,_______,
        TRANS,   ________________QWERTY_L1___________________,_______,        _______, ________________QWERTY_R1___________________,TO(_BASE),
        TRANS,   ________________QWERTY_L2___________________,_______,        _______, ________________QWERTY_R1___________________,KC_QUOT,
        TRANS,   ________________QWERTY_L3___________________,                         ________________QWERTY_R1___________________,TRANS,
        _______, _______, _______, TRANS,   TRANS,            TRANS,          TRANS,            TRANS,   TRANS,   _______, _______, _______,
                                            TRANS,   TRANS,   _______,        _______, TRANS,   TRANS
    )
};

// via https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum
bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case M_SYM:
        case M_NAV:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case M_SYM:
        case M_NAV:
        case KC_LSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_GUI:
            return true;
        default:
            return false;
    }
}

bool sw_win_active = false;
bool sw_lang_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // via https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum
    // single key alt tab and shift alt for layers
    update_swapper(
        &sw_win_active, KC_LALT, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LSHIFT, KC_LALT, SW_LANG,
        keycode, record
    );

    // via https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum
    // one shot implementation w/o timers
    update_oneshot(
        &os_shft_state, KC_LSHIFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_gui_state, KC_LGUI, OS_GUI,
        keycode, record
    );

    switch (keycode) {
    /*
    // hijack an unused keycode to do mod- and layer-taps with cooler taps than just basic keycodes
    case C_A_CAPS:

        // caps on double tap
        if (record->tap.count == 2 && !record->event.pressed) {
            tap_key(KC_CAPS);
        } else if (record->tap.count > 0) {
            // osm ctrl on tap
            if (record->event.pressed) {
                set_oneshot_mods(MOD_LCTL);
            }

            // alt on hold
            return false;
        }
        break; */

    // select line
    case SEL_L:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_HOME) SS_DELAY(100) SS_LSFT(SS_TAP(X_END)));
        }
        break;

    // tab to first profile in edge
    case SW_PROF:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_LALT) SS_DELAY(100) SS_LSFT(SS_TAP(X_TAB)) SS_DELAY(100) SS_TAP(X_SPACE) SS_DELAY(100) SS_TAP(X_TAB));
        }
        break;
    }
    return true;
}

#define ACTION_TAP_DANCE_MOUSE_LAYER(kc1, layer) \
  { .fn = {mousekey_tap, mousekey_finished, mousekey_reset}, .user_data = (void *)&((qk_tap_dance_pair_t){kc1, layer}),  }

qk_tap_dance_action_t tap_dance_actions[] = {
  //[D_FN_TASK_VIEW] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_fn, dance_fn_finished, dance_fn_reset),
  [TD_M1_MK] = ACTION_TAP_DANCE_MOUSE_LAYER(KC_MS_BTN1, _MOUSE),
  [TD_M2_META] = ACTION_TAP_DANCE_MOUSE_LAYER(KC_MS_BTN2, _META),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}
