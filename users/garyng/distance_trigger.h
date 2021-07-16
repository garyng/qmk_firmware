#pragma once

#ifndef TRIGGER_DISTANCE_MM
#define TRIGGER_DISTANCE_MM 50
#endif

#ifndef VL53L0X_INTERRUPT_PIN
#define VL53L0X_INTERRUPT_PIN D5
#endif

#ifdef __cplusplus
extern "C" {
#endif
void dt_init(void);
void dt_on_triggered_user(void);
void dt_get_distance(void);
void dt_render_oled_user(void);
#ifdef __cplusplus
}
#endif
