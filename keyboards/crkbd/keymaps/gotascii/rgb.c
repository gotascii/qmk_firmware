#pragma once

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
rgblight_config_t        RGB_current_config;
#endif

#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;
rgb_config_t        RGB_current_config;
#endif

extern led_config_t g_led_config;
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t led_type) {
		HSV hsv = {hue, sat, val};
		if (hsv.v > rgb_matrix_config.hsv.v) {
				hsv.v = rgb_matrix_config.hsv.v;
		}

		RGB rgb = hsv_to_rgb(hsv);
		for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
				if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
						rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
				}
		}
}

void save_rgb_config(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_config.enable = rgblight_config.enable;
    RGB_current_config.mode   = rgblight_get_mode();
    RGB_current_config.speed  = rgblight_get_speed();
    RGB_current_config.hue    = rgblight_get_hue();
    RGB_current_config.sat    = rgblight_get_sat();
    RGB_current_config.val    = rgblight_get_val();
#elif RGB_MATRIX_ENABLE
    RGB_current_config.enable = rgb_matrix_config.enable;
    RGB_current_config.mode   = rgb_matrix_get_mode();
    RGB_current_config.speed  = rgb_matrix_config.speed;
    RGB_current_config.hsv    = rgb_matrix_config.hsv;
#endif
}

void restore_rgb_config(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_set_speed_noeeprom(RGB_current_config.speed);
    if (rgblight_config.mode != RGB_current_config.mode) {
        rgblight_mode_noeeprom(RGB_current_config.mode);
    }
    if ((RGB_current_config.hue != rgblight_config.hue) || (RGB_current_config.sat != rgblight_config.sat) || (RGB_current_config.val != rgblight_config.val)) {
        rgblight_sethsv_noeeprom(RGB_current_config.hue, RGB_current_config.sat, RGB_current_config.val);
    }
    if (rgblight_config.enable) {
        rgblight_enable_noeeprom();
    } else {
        rgblight_disable_noeeprom();
    }
#elif RGB_MATRIX_ENABLE
    rgb_matrix_config.speed = RGB_current_config.speed;
    if (rgb_matrix_config.mode != RGB_current_config.mode) {
        rgb_matrix_mode_noeeprom(RGB_current_config.mode);
    }
    if ((RGB_current_config.hsv.h != rgb_matrix_config.hsv.h) || (RGB_current_config.hsv.s != rgb_matrix_config.hsv.s) || (RGB_current_config.hsv.v != rgb_matrix_config.hsv.v)) {
        rgb_matrix_sethsv_noeeprom(RGB_current_config.hsv.h, RGB_current_config.hsv.s, RGB_current_config.hsv.v);
    }
    if (rgb_matrix_config.enable) {
        rgb_matrix_enable_noeeprom();
				rgb_matrix_layer_helper(HSV_CORAL, LED_FLAG_UNDERGLOW);
    } else {
        rgb_matrix_disable_noeeprom();
    }
#endif
}

void rgb_by_layer(int layer) {
#ifdef RGBLIGHT_ENABLE
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#elif RGB_MATRIX_ENABLE
 /* rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR); */
		/* print("1\n"); */
/* rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE); */
#endif

    switch (layer) {
        case _ADJUST:
						rgb_matrix_layer_helper(HSV_RED, LED_FLAG_UNDERGLOW);
					/* rgblight_sethsv_noeeprom(9, 255, 255); */
            break;
        case _RAISE:
						rgb_matrix_layer_helper(HSV_WHITE, LED_FLAG_UNDERGLOW);
            /* rgblight_sethsv_noeeprom(HSV_CYAN); */
            break;
        case _LOWER:
						rgb_matrix_layer_helper(HSV_WHITE, LED_FLAG_UNDERGLOW);
            /* rgblight_sethsv_noeeprom(HSV_MAGENTA); */
            break;
        default:
						rgb_matrix_layer_helper(HSV_RED, LED_FLAG_UNDERGLOW);
            /* rgblight_sethsv_noeeprom(HSV_RED); */
    }
}
