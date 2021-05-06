#pragma once

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
	QWERTY = SAFE_RANGE,
	LOWER,
	RAISE,
	ADJUST,
	RGBRST,
	RGB_UND
};

#define KC_ANGL LSFT(KC_COMM)
#define KC_ANGR LSFT(KC_DOT)

#define SFT_GRV MT(MOD_RSFT, KC_GRV)
#define ALT_Z MT(MOD_LALT, KC_Z)

#define LOW_SPC LT(_LOWER, KC_SPC)
#define LOW_DEL LT(_LOWER, KC_DEL)

#define RAI_EQ LT(_RAISE, KC_EQL)
#define RAI_ENT LT(_RAISE, KC_ENT)

#define ADJ_QUOT LT(_ADJUST, KC_QUOT)

#define TD_ESC TD(TDA_ESC)

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
		TDA_ESC
};

td_state_t cur_dance(qk_tap_dance_state_t *state);

void td_esc_finished(qk_tap_dance_state_t *state, void *user_data);
void td_esc_reset(qk_tap_dance_state_t *state, void *user_data);
