LTO_ENABLE = yes # reduces the compiled firmware size

SRC += garyng.c tap_auto_mod.c wrapping_key.c

OLED_VARIANT ?= SSD1306_128X32
OPT_DEFS += -DUSE_$(strip $(OLED_VARIANT))
