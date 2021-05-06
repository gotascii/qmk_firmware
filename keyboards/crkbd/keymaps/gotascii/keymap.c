#include QMK_KEYBOARD_H
#include "keycodes.h"

#include "print.h"
/* print("string\n"): Print a simple string. */
/* uprintf("%s string\n", var): Print a formatted string */

#ifdef OLED_DRIVER_ENABLE
#    include "oled.c"
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    include "rgb.c"
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     TD_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, ADJ_QUOT,
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT, ALT_Z,   KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_GRV,
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LGUI, LOW_SPC, RAI_EQ,     RAI_ENT, LOW_SPC, RGUI_T(KC_BSPC)
                                      //|--------------------------|  |--------------------------|


  ),

  [_LOWER] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_PGUP,                      KC_MINS, KC_LEFT, KC_UP,   KC_RIGHT,KC_PLUS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, XXXXXXX, KC_LBRC, KC_RBRC, KC_PGDOWN,                    KC_UNDS, KC_HOME, KC_DOWN, KC_END,  KC_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______, _______,    _______, LOW_DEL, _______
                                      //|--------------------------|  |--------------------------|
  ),

  [_RAISE] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_HASH, KC_DLR, KC_ANGL, KC_ANGR, XXXXXXX,                      XXXXXXX, KC_AMPR, KC_PIPE, KC_EXLM, KC_ASTR, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, XXXXXXX,                      XXXXXXX, KC_UNDS, KC_EQL,  KC_ANGL, KC_ANGR, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, XXXXXXX,                      XXXXXXX, KC_MINS, KC_PLUS, XXXXXXX, KC_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //|--------------------------|  |--------------------------|
  ),

  [_ADJUST] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     XXXXXXX, CK_RST,  CK_DOWN, CK_UP,   CK_TOGG, RGB_TOG,                       MU_TOG, KC_F12,  KC_F7,   KC_F8,   KC_F9,   XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD,                       MU_MOD, KC_F11,  KC_F4,   KC_F5,   KC_F6,   XXXXXXX,  \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGBRST,                        AU_TOG, KC_F10,  KC_F1,   KC_F2,   KC_F3,   RESET, \
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         RGB_UND,  _______, _______,    _______, KC_VOLD, KC_VOLU \
                                      //|--------------------------|  |--------------------------|
  )
};
// clang-format off

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
layer_state_t layer_state_set_user(layer_state_t state) {
    /* For any layer other than default, save current RGB state and switch to layer-based RGB */
    if (layer_state_cmp(state, 0)) {
        restore_rgb_config();
    } else {
        uint8_t layer = get_highest_layer(state);
        if (layer_state_cmp(layer_state, 0)) save_rgb_config();
        rgb_by_layer(layer);
    }
    return state;
}
#endif

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSFT:
            return 1;
        case KC_LGUI:
            return 1;
				case TD_ESC:
						return 180;
        default:
            return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_DRIVER_ENABLE
    if (record->event.pressed) {
        oled_timer = timer_read();
        add_keylog(keycode);
    }
#endif

    switch (keycode) {
			  case KC_P:
					if (get_mods() & MOD_BIT(KC_LSFT)) {
						if (get_mods() & MOD_BIT(KC_LGUI)) {
							if (record->event.pressed) {
									register_code(KC_LBRC);
							} else {
									unregister_code(KC_LBRC);
							}
							return false;
						}
					}
					return true;
				case KC_EQL:
					if (get_mods() & MOD_BIT(KC_LSFT)) {
						if (get_mods() & MOD_BIT(KC_LGUI)) {
							if (record->event.pressed) {
									register_code(KC_RBRC);
							} else {
									unregister_code(KC_RBRC);
							}
							return false;
						}
					}
					return true;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        case RGB_MOD:
        case RGB_TOG:
        case RGB_HUI:
        case RGB_HUD:
        case RGB_SAI:
        case RGB_SAD:
        case RGB_VAI:
        case RGB_VAD:
        case RGB_SPI:
        case RGB_SPD:
            /* Override layer-based RGB and resume RGB effect to be able to preview changes */
            if (record->event.pressed) {
                restore_rgb_config();
                process_rgb(keycode, record);
                save_rgb_config();
            }
            return false;
        case RGBRST:
            if (record->event.pressed) {
#    ifdef RGBLIGHT_ENABLE
                eeconfig_update_rgblight_default();
                rgblight_enable();
#    elif RGB_MATRIX_ENABLE
                eeconfig_update_rgb_matrix_default();
                rgb_matrix_enable();
								rgb_matrix_layer_helper(HSV_CORAL, LED_FLAG_UNDERGLOW);
#    endif
                save_rgb_config();
            }
            return false;

#endif
    }
    return true;
}

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    /* if (state->count == 1) { */
    /*     if (state->interrupted || !state->pressed) return TD_SINGLE_TAP; */
    /*     else return TD_SINGLE_HOLD; */
    /* } else if (state->count == 2) { */
    /*     if (state->interrupted) return TD_DOUBLE_SINGLE_TAP; */
    /*     else if (state->pressed) return TD_DOUBLE_HOLD; */
    /*     else return TD_DOUBLE_TAP; */
    /* } */

    /* if (state->count == 3) { */
    /*     if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP; */
    /*     else return TD_TRIPLE_HOLD; */
    /* } else return TD_UNKNOWN; */

		if (state->count == 1) {
				if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
				else return TD_SINGLE_HOLD;
		} else if (state->count >= 2) {
				if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
				else if (state->pressed) return TD_DOUBLE_HOLD;
				else return TD_DOUBLE_TAP;
		} else return TD_UNKNOWN;
}
			
static td_tap_t esc_tap_state = {
		.is_press_action = true,
		.state = TD_NONE
};

void td_esc_tap(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 2) {
	  tap_code(KC_TAB); register_code(KC_TAB);
	} else if (state->count > 2) {
		unregister_code(KC_TAB); register_code(KC_TAB);
	}
}

void td_esc_finished(qk_tap_dance_state_t *state, void *user_data) {
		esc_tap_state.state = cur_dance(state);
		switch (esc_tap_state.state) {
				case TD_SINGLE_TAP:
					register_code(KC_TAB);
					break;
				case TD_SINGLE_HOLD:
					register_code(KC_ESC);
					break;
				default: break;
		}
}

void td_esc_reset(qk_tap_dance_state_t *state, void *user_data) {
		switch (esc_tap_state.state) {
				case TD_SINGLE_TAP:
					unregister_code(KC_TAB);
					break;
				case TD_SINGLE_HOLD:
					unregister_code(KC_ESC);
					break;
				case TD_DOUBLE_TAP:
					unregister_code(KC_TAB);
					break;
				case TD_DOUBLE_HOLD:
					unregister_code(KC_TAB);
					break;
				default: break;
		}
		esc_tap_state.state = TD_NONE;
}

// Put TD configs in this array,
// then use TD(array_index) as the KC
// Possible TD configs are:
//
// ACTION_TAP_DANCE_DOUBLE(kc1, kc2):
// kc1 when tapped, kc2 when double tapped
// kc1 when single hold, kc2 when double hold
//
// ACTION_TAP_DANCE_FN(fn)
// void fn(qk_tap_dance_state_t *state, void *user_data)
// Calls fn with the final tap count
//
// ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn)
qk_tap_dance_action_t tap_dance_actions[] = {
		[TDA_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(td_esc_tap, td_esc_finished, td_esc_reset)
};

