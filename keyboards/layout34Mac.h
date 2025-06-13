// 34 key layout w/ combos
enum layers { _MAIN, _SMBL, _NUM, _NAV };
#define SMBL MO(_SMBL)
#define NAV MO(_NAV)
#define NUM MO(_NUM)

struct KeycodeLayout {
    uint16_t dft[4][10];
    uint16_t num[4][10];
    uint16_t nav[4][10];
    uint16_t smbl[4][10];
};
 
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(T_Q):
            return TAPPING_TERM -65;
        case MT(MOD_LCTL, KC_A):
            return TAPPING_TERM + 100;
        case MT(MOD_LSFT, KC_R):
            return TAPPING_TERM + 100;
        case LT(3,KC_BSPC):
            return TAPPING_TERM -65;
        case MT(MOD_RGUI, KC_E):
            return TAPPING_TERM + 100;
        case MT(MOD_RSFT, KC_I):
            return TAPPING_TERM + 100;
        case MT(MOD_RCTL, KC_O):
            return TAPPING_TERM + 100;
        case LT(4,KC_DELETE):
            return TAPPING_TERM -65;
        default:
            return TAPPING_TERM;
    }
}

 // Define an array of keycodes
extern const struct KeycodeLayout layout;
const struct KeycodeLayout layout = {
    { // Default
        {
            TD(T_Q),      TD(T_W),      TD(T_F),      KC_P,              KC_B,            KC_J,            KC_L,           KC_U,         KC_Y,         KC_SCLN
        },
        {
            LGUI_T(KC_A), LSFT_T(KC_R), LCTL_T(KC_S), LALT_T(KC_T),      MEH_T(KC_G),     MEH_T(KC_M),     RALT_T(KC_N),  RCTL_T(KC_E),  RSFT_T(KC_I), RGUI_T(KC_O)
        },
        {
            TD(T_Z),      TD(T_X),      TD(T_C),      TD(T_D),           TD(T_V),         KC_K,            TD(T_H),        KC_COMM,      KC_DOT,       TD(T_SLASH)
        },
        {
                                                      LT(SMBL, KC_BSPC), LT(NUM, KC_SPC), LT(NAV, KC_ENT), KC_DEL
        }
    },
    { // Num
        {
            QK_BOOT,    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_P7,  KC_P8,   KC_P9,   XXXXXXX
        },
        {
            XXXXXXX,    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_P4,  KC_P5,   KC_P6,   XXXXXXX
        },
        {
            LGUI(KC_Z), LGUI(LSFT(KC_Z)), XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  KC_P1,  KC_P2,   KC_P3,  XXXXXXX
        },
        {
                                                   XXXXXXX,  XXXXXXX, KC_P0, KC_PDOT  
        }
    },
    { // Nav / FN
        {
            KC_NUM,  KC_SCRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END
        },
        {
            KC_LGUI, KC_LSFT, KC_LCTL, KC_LALT, XXXXXXX, KC_F8,   KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT
        },
        {
            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F6,   KC_F5,   KC_F10,  KC_F11,  KC_F12,  RGUI(KC_F12)
        },
        {
                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
        }
    },
    { // Symbols
        {
            KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN
        },
        {
            KC_EQL,  KC_PPLS, KC_MINUS, KC_UNDS, XXXXXXX, KC_PIPE, KC_LCBR,    KC_RCBR,    TD(T_QUOT), KC_DQT
        },
        {
            XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_TILD, TD(T_LBRC), TD(T_RBRC), TD(T_GRV),  TD(T_BSLS)
        },
        {
                                        XXXXXXX, KC_SPC,  KC_ENT, KC_DEL
        }
    }
};

const uint16_t PROGMEM combCaps[] = { MT(MOD_LSFT, KC_R), MT(MOD_RSFT, KC_I), COMBO_END};
const uint16_t PROGMEM combCAD[] = { TD(T_Q), KC_SCLN, COMBO_END};
const uint16_t PROGMEM combTab[] = { MT(MOD_LALT, KC_T), MT(MOD_RALT, KC_N), COMBO_END};
const uint16_t PROGMEM combSTab[] = { MT(MOD_LCTL, KC_S), MT(MOD_RCTL, KC_E), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combCaps, KC_CAPS),
    COMBO(combCAD, LALT(LGUI(KC_DELETE))),
    COMBO(combTab, KC_TAB),
    COMBO(combSTab, LSFT(KC_TAB)),
};