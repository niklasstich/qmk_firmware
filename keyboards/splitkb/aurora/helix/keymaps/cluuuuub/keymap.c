#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif


// stolen from https://gist.github.com/itspngu/9159f06153b440a754b33c6d65c5f302, adapted by me
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))

enum custom_keycodes {
	UML_A = SAFE_RANGE,
	UML_O,
	UML_U,
	UML_S,
	KX_EURO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, LCTL(KC_L), OSL(4), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC, KC_SPC, MO(1), KC_COPY, KC_PSTE, MO(2), KC_ENT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
    ),
    [1] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
        KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_NO, KC_NO, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, 
        KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_HOME, KC_END, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_CUT, KC_NO, KC_NO, KC_NO, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),
    [2] = LAYOUT(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, 
        KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, 
        KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, 
        KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    [3] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        KC_NO, KC_NO, KC_NO, KC_NO, QK_RBT, KC_NO, KC_NO, KC_F13, KC_F14, KC_F15, KC_F16, KC_DEL, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F17, KC_F18, KC_F19, KC_F20, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_F21, KC_F22, KC_F23, KC_F24, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    [4] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, KX_EURO, KC_NO, KC_NO, KC_NO, UML_U, KC_NO, UML_O, KC_NO, KC_NO, 
        KC_NO, UML_A, UML_S, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )
};


void send_altcode(uint16_t mask, keyrecord_t *record) {
	
	/* Sends the "alt code" defined in mask, i.e. send_altcode(1234) 
	holds left alt while sending KP_1, KP_2, KP_3 and KP_4 taps, 
	then releases left alt if it wasn't being held by the user. 
	
	NOTE: If your alt code starts with a 0, leave that out, else the
	mask will be treated as octal and your firmware won't compile.
	send_altcode(123) will output KP_0, KP_1, KP_2 and KP_3. */
	
	// Check & save mod state
	static uint8_t lalt_mask;
	lalt_mask = keyboard_report->mods & KC_LALT;
	
	// Split up the mask into its 4 decimals
	static uint16_t kp[4];
	kp[0] = mask / 1000;
	kp[1] = mask / 100 - kp[0] * 100;
	kp[2] = mask / 10 - kp[0] * 1000 - kp[1] * 10;
	kp[3] = mask - kp[0] * 1000 - kp[1] * 100 - kp[2] * 10;
	
	// Convert to keycodes
	
	for (uint8_t i=0; i<=3; i++) {
		switch(kp[i]) {
			case 0:
				kp[i] = KC_KP_0; break;
			case 1:
				kp[i] = KC_KP_1; break;
			case 2:
				kp[i] = KC_KP_2; break;
			case 3:
				kp[i] = KC_KP_3; break;
			case 4:
				kp[i] = KC_KP_4; break;
			case 5:
				kp[i] = KC_KP_5; break;
			case 6:
				kp[i] = KC_KP_6; break;
			case 7:
				kp[i] = KC_KP_7; break;
			case 8:
				kp[i] = KC_KP_8; break;
			case 9:
				kp[i] = KC_KP_9; break;
		}
	}
	
	// Put ALT into pressed state
	if (!lalt_mask) {
		register_code(KC_LALT);
		send_keyboard_report();
	}
	
	
	// The send_keyboard_report() spam is not pretty, but necessary.
	add_key(kp[0]);
	send_keyboard_report();
	del_key(kp[0]);
	send_keyboard_report();
	add_key(kp[1]);
	send_keyboard_report();		
	del_key(kp[1]);
	send_keyboard_report();
	add_key(kp[2]);
	send_keyboard_report();		
	del_key(kp[2]);
	send_keyboard_report();
	add_key(kp[3]);
	send_keyboard_report();
	del_key(kp[3]);
	send_keyboard_report();
	
	// If user wasn't pressing ALT, release it
	if (!lalt_mask) {
		unregister_code(KC_LALT);
	}
	
	send_keyboard_report();
}

void send_altcode_and_restore_shift(uint16_t mask, keyrecord_t *record, uint8_t shift_mask) {
    unregister_code(KC_LSFT);
    unregister_code(KC_RSFT);
    send_keyboard_report();

    send_altcode(mask, record);

    if (shift_mask &MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
    if (shift_mask &MOD_BIT(KC_RSFT)) register_code(KC_RSFT);

    send_keyboard_report();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	static uint8_t shift_mask;
	shift_mask = get_mods()&MODS_SHIFT_MASK;
	
	if (record->event.pressed) {
		switch(keycode) {
		case UML_A:
			if (shift_mask) { // We want a capital version of the German A Umlaut 'cause shift is pressed
                send_altcode_and_restore_shift(196, record, shift_mask);
			} else {
				send_altcode(228, record); // ä
			}
			return false;
			break;
		case UML_O:
			if (shift_mask) {
                send_altcode_and_restore_shift(214, record, shift_mask);
			} else {
				send_altcode(246, record); // ö
			}
			return false;
			break;
		case UML_U:
			if (shift_mask) {
                send_altcode_and_restore_shift(220, record, shift_mask);
			} else {
				send_altcode(252, record); // ü
			}
			return false;
			break;
		case UML_S:
            if(shift_mask) {
                send_altcode_and_restore_shift(7838, record, shift_mask);
            } else {
                send_altcode(223, record); // ß
            }
			return false;
			break;
		case KX_EURO:
			send_altcode(128, record); // €
			return false;
			break;
		}
	}
	
	return true;
}

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C


