USER_NAME := antiheadshot

#CONSOLE_ENABLE = yes

BOOTMAGIC_ENABLE = yes
TAP_DANCE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
SWAP_HANDS_ENABLE = yes

ifneq ($(strip $(CONSOLE_ENABLE)), yes)
  # Include my fancy rgb functions source here
  RGBLIGHT_ENABLE = yes
endif

UNICODE_ENABLE = no
LTO_ENABLE = yes