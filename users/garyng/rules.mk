LTO_ENABLE = yes # reduces the compiled firmware size

SRC += VL53L0X.cpp garyng.c tap_auto_mod.c wrapping_key.c
QUANTUM_LIB_SRC += i2c_master.c

OLED_VARIANT ?= SSD1306_128X32
OPT_DEFS += -DUSE_$(strip $(OLED_VARIANT))
