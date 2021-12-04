BOOTLOADER = atmel-dfu

TAP_DANCE_ENABLE = yes
MOUSEKEY_ENABLE = yes
RGBLIGHT_ENABLE = yes
COMBO_ENABLE = yes

# reduce filesize
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
EXTRAFLAGS += -flto

SRC += mousekeys.c
SRC += swapper.c
SRC += oneshot.c
SRC += repeat.c
SRC += capsword.c
