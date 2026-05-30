#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include "gpio.h"
#include "helix.h"


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
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, LCTL(KC_L), OSL(4), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, MO(4), KC_SPC, MO(1), KC_COPY, KC_PSTE, MO(2), KC_ENT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
    ),
    [1] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
        KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_NO, KC_NO, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, 
        KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_HOME, KC_END, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),
    [2] = LAYOUT(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, 
        KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, 
        KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        KC_NO, KC_NO, KC_NO, KC_NO, QK_RBT, KC_NO, KC_NO, KC_F13, KC_F14, KC_F15, KC_F16, KC_DEL, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F17, KC_F18, KC_F19, KC_F20, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_F21, KC_F22, KC_F23, KC_F24, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [4] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, KX_EURO, KC_NO, KC_NO, KC_NO, UML_U, KC_NO, UML_O, KC_NO, KC_NO, 
        KC_NO, UML_A, UML_S, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

void keyboard_pre_init_user(void) {
	gpio_set_pin_output(24);
	gpio_write_pin_high(24);
}

static os_variant_t os;

void setup_linux_unicode(void) {
	set_unicode_input_mode(UNICODE_MODE_LINUX);
}

bool process_detected_host_os_user(os_variant_t detected_os) {
	os = detected_os;
	if(os == OS_LINUX) {
		setup_linux_unicode();
	}
	return true;
}

char* get_os_text(void) {
	switch (os) {
		case OS_LINUX: return "lin";
		case OS_WINDOWS: return "win";
		case OS_MACOS: return "mac";
		case OS_IOS: return "ios";
		case OS_UNSURE:
		default: return "unkwn";
	}
}


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

void send_altcode_with_shift_handling(uint16_t unshifted, uint16_t shifted, keyrecord_t *record, uint8_t shift_mask) {
	if(shift_mask) {
		send_altcode_and_restore_shift(shifted, record, shift_mask);
	} else {
		send_altcode(unshifted, record);
	}
}

void send_unicode(uint16_t codepoint) {
	register_unicode(codepoint);
}

void send_unicode_with_shift_handling(uint16_t unshifted, uint16_t shifted, keyrecord_t *record, uint8_t shift_mask) {
	if(shift_mask) {
		send_unicode(shifted);
	} else {
		send_unicode(unshifted);
	}
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	static uint8_t shift_mask;
	shift_mask = get_mods()&MODS_SHIFT_MASK;
	if (record->event.pressed) {
		uint16_t shifted;
		uint16_t unshifted;
		if(keycode < UML_A || keycode > KX_EURO) return true;
		switch(keycode) {
		case UML_A:
			unshifted = 228;
			shifted = 196;
			break;
		case UML_O:
			unshifted = 246;
			shifted = 214;
			break;
		case UML_U:
			unshifted = 252;
			shifted = 220;
			break;
		case UML_S:
			unshifted = 223;
			shifted = 7838;
			break;
		case KX_EURO:
			if(os == OS_LINUX) {
				send_unicode(8364);
			} else if (os == OS_WINDOWS) {
				send_altcode(128, record); // €
			}
			return false;
		}

		if(os == OS_LINUX) {
			send_unicode_with_shift_handling(unshifted, shifted, record, shift_mask);
			return false;
		} else if (os == OS_WINDOWS) {
			send_altcode_with_shift_handling(unshifted, shifted, record, shift_mask);
			return false;
		}
	}
	
	return true;
}

void render_text(char *text) {
    oled_write_P(PSTR(text), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Renders the current keyboard state (layers and mods)
        render_logo();
        render_text(get_os_text());
        oled_advance_page(true);
        // render_layer_state();
        // oled_advance_page(false);
        // render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
        // render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
        // render_kb_LED_state();
    } else {
        // clang-format off
        static const char PROGMEM aurora_art[] = {
            0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x08, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40,
            0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x80,
            0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x80, 0x00, 0xf0, 0x00, 0x00, 0xc0,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x81, 0x00, 0xc0, 0x00, 0xfe, 0x00, 0xfc, 0x00, 0xff, 0x20, 0xff, 0xf0, 0x0f, 0xf0, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0xf8, 0x00, 0x00, 0xf8,
            0xff, 0x10, 0xff, 0x84, 0xff, 0x60, 0xff, 0x36, 0xff, 0x0f, 0xff, 0x3f, 0x00, 0x5f, 0x00, 0x05,
            0x80, 0x00, 0x80, 0x00, 0xc0, 0x38, 0x00, 0xec, 0xf0, 0x00, 0xfb, 0x80, 0xff, 0xf0, 0xff, 0xef,
            0xff, 0xe8, 0xff, 0x03, 0xff, 0x0c, 0xff, 0x00, 0xff, 0x00, 0x03, 0x00, 0x00, 0xf8, 0x00, 0x80,
            0xff, 0x20, 0xff, 0xd0, 0xff, 0xe0, 0xfe, 0xf8, 0xff, 0xfc, 0xff, 0xff, 0x0f, 0xff, 0x01, 0x3f,
            0xff, 0x00, 0x0f, 0x00, 0x01, 0x00, 0x03, 0x00, 0xfe, 0x80, 0xfe, 0x00, 0xc0, 0xff, 0xc4, 0xfb,
            0xff, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0x07, 0xff, 0x03, 0x3f, 0x00, 0x0f, 0xc0, 0x00,
            0x00, 0x00, 0xb8, 0x00, 0xff, 0x40, 0xbe, 0xf0, 0xff, 0xf1, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff,
            0x1f, 0xff, 0x67, 0x00, 0xef, 0x00, 0x1f, 0x00, 0x00, 0x07, 0x00, 0x00, 0xe0, 0x00, 0xff, 0xf0,
            0xff, 0x88, 0xff, 0xc4, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x7f, 0x0f, 0xff,
            0x00, 0x07, 0xfe, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xc0, 0x3f, 0xf8, 0xe7, 0xff,
            0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0x1f, 0x3f, 0x01, 0xff, 0x0b, 0x00, 0xff, 0x00, 0x00, 0x05,
            0x00, 0x00, 0x00, 0xe0, 0x00, 0xf8, 0x60, 0x80, 0xfe, 0xe3, 0xfc, 0xff, 0x1e, 0xff, 0xff, 0x23,
            0xff, 0x09, 0xff, 0x20, 0x00, 0x3f, 0x02, 0x00, 0x00, 0x0f, 0x00, 0x40, 0x00, 0xc0, 0x00, 0xfc,
            0xe0, 0xfc, 0xf0, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0x0f, 0xff, 0x07, 0x1f, 0x00, 0x01, 0x0f, 0x00,
            0x0f, 0x00, 0x81, 0x70, 0x0c, 0xf0, 0x80, 0x00, 0x00, 0xe4, 0xf8, 0xe6, 0x70, 0x3f, 0xcf, 0xff,
            0x1f, 0xff, 0x48, 0xff, 0x0f, 0x00, 0x07, 0x00, 0x00, 0x43, 0x60, 0xf8, 0xf0, 0xfe, 0x38, 0xfe,
            0x00, 0xfc, 0x03, 0x00, 0xc8, 0x72, 0xcf, 0xfc, 0x00, 0x03, 0x0f, 0x01, 0xe0, 0x1c, 0xe0, 0x03,
            0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x06, 0xf9, 0x00, 0x03, 0x00, 0x07,
            0xff, 0x00, 0x10, 0x12, 0xc9, 0xf0, 0xcf, 0xb4, 0x7f, 0x80, 0xe0, 0x1e, 0x01, 0x40, 0x65, 0x5e,
            0xe0, 0x00, 0x00, 0xf0, 0x0c, 0xf0, 0x00, 0x80, 0x7e, 0x01, 0x80, 0x93, 0xfc, 0xc0, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x89, 0x18, 0x2c, 0x46, 0x00, 0x07, 0x21, 0x10, 0x10, 0x80, 0x09, 0x13,
            0x31, 0xbf, 0xff, 0x00, 0x08, 0x1a, 0xf7, 0x0f, 0x00, 0x00, 0x44, 0x45, 0x34, 0xbf, 0xb8, 0x00,
            0x10, 0xf0, 0x08, 0xf4, 0x18, 0x11, 0xfc, 0x18, 0xfb, 0x0e, 0x10, 0xf8, 0x04, 0xf8, 0x10, 0x20,
            0x18, 0x09, 0xff, 0x0c, 0xea, 0x1f, 0x28, 0x60, 0x30, 0xf8, 0x20, 0xc0, 0x42, 0x33, 0x21, 0x00
        };
        // clang-format on
        oled_write_raw_P(aurora_art, sizeof(aurora_art));
    }
    return false;
}


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // 0 is left-half encoder,
    // 1 is right-half encoder
    if (index == 1) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 0) {
        // Page up/Page down
        if (clockwise) {
            tap_code(MS_WHLD);
        } else {
            tap_code(MS_WHLU);
        }
    }
    return false;
}
#endif

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C


