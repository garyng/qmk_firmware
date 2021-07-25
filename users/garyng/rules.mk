LTO_ENABLE = yes # reduces the compiled firmware size

SRC += garyng.cpp tap_auto_mod.c wrapping_key.c

OLED_VARIANT ?= SSD1306_128X32
OPT_DEFS += -DUSE_$(strip $(OLED_VARIANT))

DISTANCE_TRIGGER_ENABLE ?= no
ifdef DISTANCE_TRIGGER_ENABLE
    ifeq ($(strip $(DISTANCE_TRIGGER_ENABLE)), yes)
        OPT_DEFS += -DDISTANCE_TRIGGER_ENABLE
		SRC += VL53L0X.cpp distance_trigger.cpp
		QUANTUM_LIB_SRC += i2c_master.c
	endif
endif

ifdef OLED_DRIVER_ENABLE
	SRC += oled.c
endif
