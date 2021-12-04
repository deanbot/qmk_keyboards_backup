#pragma once

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
#endif

#ifdef MOUSEKEY_ENABLE
  #define MOUSEKEY_DELAY 0
  #define MOUSEKEY_INTERVAL 16
  #define MOUSEKEY_MOVE_DELTA 5
  #define MOUSEKEY_MAX_SPEED 5
  #define MOUSEKEY_TIME_TO_MAX 64
  #define MOUSEKEY_WHEEL_DELAY 0
  #define MOUSEKEY_WHEEL_INTERVAL 100
  #define MOUSEKEY_WHEEL_MAX_SPEED 6
  #define MOUSEKEY_WHEEL_TIME_TO_MAX 255


//   #define MOUSEKEY_INTERVAL 16
// // The default is 20. Since we made the mouse about 3 times faster with the previous setting,
// // give it more time to accelerate to max speed to retain precise control over short distances.
// #define MOUSEKEY_TIME_TO_MAX 40
// // The default is 300. Let's try and make this as low as possible while keeping the cursor responsive
// #define MOUSEKEY_DELAY 100
// // It makes sense to use the same delay for the mouseweel
// #define MOUSEKEY_WHEEL_DELAY 100
// // The default is 100
// #define MOUSEKEY_WHEEL_INTERVAL 50
// // The default is 40
// #define MOUSEKEY_WHEEL_TIME_TO_MAX 100

#endif

#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

#define TAPPING_TERM 175
#define ONESHOT_TAP_TOGGLE 5
#define ONESHOT_TIMEOUT 2085

// reduce filesize
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
