#pragma once

#define ENABLE_DISTANCE_TRIGGER
#define TRIGGER_DISTANCE_MM 50
#define VL53L0X_INTERRUPT_PIN D5

#ifdef __cplusplus
extern "C" {
#endif
void dt_init(void);
void dt_on_triggered_user(void);
void dt_get_distance(void);

#ifdef __cplusplus
}
#endif
