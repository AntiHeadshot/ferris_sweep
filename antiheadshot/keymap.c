#ifdef QMK_KEYBOARD_H
#    include QMK_KEYBOARD_H
#endif

#define LAYER_STATE_8BIT

#ifndef TAP_DANCE_ENABLE
#    define TAP_DANCE_ENABLE
#endif

#include <stdbool.h>
#include <inttypes.h>
#include "quantum/process_keycode/process_tap_dance.h"
#include "quantum/keymap_extras/keymap_german.h"
#include "progmem.h"
#ifdef RGBLIGHT_LAYERS
#    include "rgblight.h"
#endif
#include "action_layer.h"
#include "print.h"

#ifndef MATRIX_ROWS
#    define MATRIX_ROWS 8
#endif
#ifndef MATRIX_COLS
#    define MATRIX_COLS 5
#endif

enum tap_dance_codes { DANCE_DOT, DANCE_KOMM, DANCE_SLASH, DANCE_QUOTE, DANCE_ESC, DANCE_TAB, DANCE_DELETE, DANCE_ARROW_LEFT, DANCE_ARROW_RIGHT, DANCE_Q, DANCE_A, DANCE_O, DANCE_U, DANCE_S, DANCE_REC };

enum layers {
    LAYER_TEXT,
    LAYER_SIGNS,
    LAYER_NUM,
    LAYER_MOVE,
    LAYER_GAME,
};

#ifdef RGBLIGHT_LAYERS
// LEDS
//  # # # # #      # # # # #
//  # # # # # 0  3 # # # # #
//  1 # # # #      # # # # 4
//        2 #      # 5

#    define COLOR_TEXT 0, 255
#    define COLOR_SIGNS 85, 255
#    define COLOR_NUM 128, 255
#    define COLOR_MOVE 191, 255
#    define DIMM , 128
#    define BRIGHT , 255

#    define COLOR_SWAP 0, 0

#    define COLOR_GAME 20, 255

// const rgblight_segment_t PROGMEM rgb_LAYER_TEXT[] = RGBLIGHT_LAYER_SEGMENTS(
//     {0,1, 0,255,255},
//     {1,1, 42,255,255},
//     {2,1, 85,255,255},
//     {3,1, 127,255,255},
//     {4,1, 170,255,255},
//     {5,1, 212,255,255}
// );
const rgblight_segment_t PROGMEM rgb_LAYER_TEXT[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, COLOR_TEXT BRIGHT}, {1, 1, HSV_OFF}, {2, 1, COLOR_MOVE DIMM}, {3, 1, COLOR_TEXT BRIGHT}, {4, 1, HSV_OFF}, {5, 1, COLOR_SIGNS DIMM});

const rgblight_segment_t PROGMEM rgb_LAYER_SIGNS[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, COLOR_SIGNS BRIGHT}, {1, 1, HSV_OFF}, {2, 1, COLOR_TEXT DIMM}, {3, 1, COLOR_SIGNS BRIGHT}, {4, 1, COLOR_MOVE DIMM}, {5, 1, COLOR_NUM DIMM});

const rgblight_segment_t PROGMEM rgb_LAYER_NUM[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, COLOR_NUM BRIGHT}, {1, 1, HSV_OFF}, {2, 1, COLOR_TEXT DIMM}, {3, 1, COLOR_NUM BRIGHT}, {4, 1, COLOR_SIGNS DIMM}, {5, 1, COLOR_MOVE DIMM});

const rgblight_segment_t PROGMEM rgb_LAYER_MOVE[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, COLOR_MOVE BRIGHT}, {1, 1, HSV_OFF}, {2, 1, COLOR_TEXT DIMM}, {3, 1, COLOR_MOVE BRIGHT}, {4, 1, COLOR_NUM DIMM}, {5, 1, COLOR_SIGNS DIMM});

const rgblight_segment_t PROGMEM rgb_LAYER_GAME[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, COLOR_GAME BRIGHT}, {1, 1, HSV_OFF}, {2, 1, HSV_OFF}, {3, 1, COLOR_GAME BRIGHT}, {4, 1, COLOR_TEXT DIMM}, {5, 1, COLOR_SIGNS DIMM});

const rgblight_segment_t *const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(rgb_LAYER_TEXT, rgb_LAYER_SIGNS, rgb_LAYER_NUM, rgb_LAYER_MOVE, rgb_LAYER_GAME);
#endif

void keyboard_post_init_user(void) {
    #ifdef CONSOLE_ENABLE
    // Customise these values to desired behaviour
    debug_enable = true;
    debug_matrix = true;
    // debug_keyboard=true;
    // debug_mouse=true;
    #endif

#ifdef RGBLIGHT_LAYERS
    // Enable the LED layers
    rgblight_layers = rgb_layers;

    rgblight_set_layer_state(LAYER_TEXT, true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(LAYER_TEXT, layer_state_cmp(state, LAYER_TEXT));
    rgblight_set_layer_state(LAYER_SIGNS, layer_state_cmp(state, LAYER_SIGNS));
    rgblight_set_layer_state(LAYER_NUM, layer_state_cmp(state, LAYER_NUM));
    rgblight_set_layer_state(LAYER_MOVE, layer_state_cmp(state, LAYER_MOVE));
    rgblight_set_layer_state(LAYER_GAME, layer_state_cmp(state, LAYER_GAME));

    return state;
#endif
}

#define ___ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //   [LAYER_TEXT] = {
    //     {DE_Y,   DE_C,     DE_L,     DE_M,    DE_K},
    //     {DE_I,    MT(DE_SS, DE_S),    LCTL_T(DE_R),    LALT_T(DE_T),    DE_G},
    //     {MT(DE_AT, DE_Q),   DE_V,  DE_W,   DE_D,  DE_J},
    //                                 {LT(LAYER_MOVE,KC_SPACE), OSM(MOD_LSFT), ___,___,___},

    //     {DE_Z,   DE_F,   MT(DE_UDIA, DE_U),   TD(DANCE_SLASH),  KC_BSPC},
    //     {DE_P,   RALT_T(DE_N),   RCTL_T(DE_E),  MT(DE_ADIA, DE_A),  MT(DE_ODIA, DE_O)},
    //     {DE_B,   DE_H,   TD(DANCE_KOMM),   TD(DANCE_DOT),   DE_X},
    //     {OSM(MOD_RCTL), TO(LAYER_SIGNS),___,___,___}
    //   },

    [LAYER_TEXT] = {{TD(DANCE_Q), DE_W, DE_E, DE_R, DE_T},
                    {TD(DANCE_A), TD(DANCE_S), LCTL_T(DE_D), LALT_T(DE_F), DE_G},
                    {DE_Y, DE_X, DE_C, DE_V, DE_B},
                    {LT(LAYER_MOVE, KC_SPACE), OSM(MOD_LSFT), ___, ___, ___},

                    {DE_Z, TD(DANCE_U), DE_I, TD(DANCE_O), DE_P},
                    {
                        DE_H,
                        RALT_T(DE_J),
                        RCTL_T(DE_K),
                        DE_L,
                    },
                    {DE_N, DE_M, TD(DANCE_DOT), TD(DANCE_KOMM), DE_MINS},
                    {OSM(MOD_RCTL), TO(LAYER_SIGNS), ___, ___, ___}},

    [LAYER_SIGNS] = {{KC_ESCAPE, DE_AT, LSFT(DE_3), ___, DE_PERC},
                     {KC_TAB, DE_EQL, LALT(DE_RBRC), LALT(LSFT(DE_RBRC)), TD(DANCE_QUOTE)},
                     {DE_TILD, ___, LALT(DE_LBRC), LALT(LSFT(DE_LBRC)), DE_DQUO},
                     {TO(LAYER_TEXT), OSM(MOD_LSFT), ___, ___, ___},

                     {DE_CIRC, DE_AMPR, DE_ASTR, DE_SCLN, KC_BACKSPACE},
                     {___, LSFT(DE_LBRC), LSFT(DE_RBRC), ___, KC_ENTER},
                     {DE_LBRC, DE_LPRN, DE_RPRN, DE_RBRC, TO(LAYER_MOVE)},
                     {KC_RALT, TO(LAYER_NUM), ___, ___, ___}},

    [LAYER_NUM] = {{KC_ESCAPE, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, LSFT(DE_MINS)},
                   {KC_TAB, KC_TRANSPARENT, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, LSFT(DE_EQL)},
                   {RESET, KC_KP_ASTERISK, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, ___},
                   {TO(LAYER_TEXT), KC_KP_DOT, ___, ___, ___},

                   {DE_MINS, MT(KC_F7, DE_7), MT(KC_F8, DE_8), MT(KC_F9, DE_9), KC_TRANSPARENT},
                   {DE_EQL, MT(KC_F4, DE_4), MT(KC_F5, DE_5), MT(KC_F6, DE_6), KC_ENTER},
                   {___, MT(KC_F1, DE_1), MT(KC_F2, DE_2), MT(KC_F3, DE_3), TO(LAYER_SIGNS)},
                   {DE_0, TO(LAYER_MOVE), ___, ___, ___}},

    [LAYER_MOVE] = {{TD(DANCE_ESC), KC_MS_WH_LEFT, KC_MS_UP, KC_MS_WH_RIGHT, DM_PLY1},
                    {KC_MS_BTN1, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, MT(MOD_LGUI, KC_DEL)},
                    {TD(DANCE_REC), KC_MS_BTN2, KC_MS_WH_UP, KC_MS_WH_DOWN, KC_TRANSPARENT},
                    {TO(LAYER_TEXT), KC_MS_BTN1, ___, ___, ___},

                    {LGUI(DE_LBRC), LCTL(LSFT(KC_TAB)), RCTL(KC_TAB), LGUI(DE_RBRC), KC_TRANSPARENT},
                    {TD(DANCE_ARROW_LEFT), MT(MOD_RGUI, KC_DOWN), MT(MOD_RALT, KC_UP), TD(DANCE_ARROW_RIGHT), KC_ENTER},
                    {KC_MS_BTN1, KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, TO(LAYER_NUM)},
                    {KC_RALT, TO(LAYER_SIGNS), ___, ___, ___}},
    [LAYER_GAME] = {{TD(DANCE_ESC), KC_MS_WH_LEFT, KC_MS_UP, KC_MS_WH_RIGHT, DM_PLY1},
                    {TD(DANCE_TAB), KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, MT(MOD_LGUI, KC_DEL)},
                    {MT(DM_REC1, DM_RSTP), KC_MS_BTN2, KC_MS_WH_UP, KC_MS_WH_DOWN, KC_TRANSPARENT},
                    {TO(LAYER_TEXT), KC_TRANSPARENT, ___, ___, ___},

                    {LGUI(DE_LBRC), LCTL(LSFT(KC_TAB)), RCTL(KC_TAB), LGUI(DE_RBRC), KC_TRANSPARENT},
                    {TD(DANCE_ARROW_LEFT), MT(MOD_RGUI, KC_DOWN), MT(MOD_RALT, KC_UP), TD(DANCE_ARROW_RIGHT), KC_ENTER},
                    {KC_MS_BTN1, KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, TO(LAYER_NUM)},
                    {KC_RALT, TO(LAYER_SIGNS), ___, ___, ___}}};

#ifdef SWAP_HANDS_ENABLE
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {{{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}}, {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}}, {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}}, {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}}, {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}}, {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}}, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}}, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}}};
#endif

extern bool g_suspend_state;
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode  = KC_NO;
uint8_t  last_modifier = 0;

typedef struct {
    bool    is_press_action;
    uint8_t step;
} tap;

enum { SINGLE_TAP = 1, SINGLE_HOLD, DOUBLE_TAP, DOUBLE_HOLD, DOUBLE_SINGLE_TAP, MORE_TAPS };

static tap dance_state = {.is_press_action = true, .step = 0};

void bootmagic_lite(void) {
    matrix_scan();
    wait_ms(DEBOUNCE * 2);
    matrix_scan();

    if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
        // Jump to bootloader.
        print("Jump to bootloader.");
        bootloader_jump();
    }
}

void dance_default_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            dance_state.step = SINGLE_TAP;
        else
            dance_state.step = SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted)
            dance_state.step = DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            dance_state.step = DOUBLE_HOLD;
        else
            dance_state.step = DOUBLE_TAP;
    } else
        dance_state.step = MORE_TAPS;
}

void on_dance_default(qk_tap_dance_state_t *state, uint16_t key) {
    if (state->count == 3) {
        tap_code16(key);
        tap_code16(key);
        tap_code16(key);
    }
    if (state->count > 3) {
        tap_code16(key);
    }
}

void dance_default_finished_withDoubleTap(uint16_t key, uint16_t alternateKey, uint16_t doubleTap) {
    switch (dance_state.step) {
        case SINGLE_TAP:
            register_code16(key);
            break;
        case SINGLE_HOLD:
            register_code16(alternateKey);
            break;
        case DOUBLE_TAP:
            if (doubleTap)
                register_code16(doubleTap);
            else {
                register_code16(key);
                register_code16(key);
            }
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(key);
            register_code16(key);
    }
}
void dance_default_finished(uint16_t key, uint16_t alternateKey) { dance_default_finished_withDoubleTap(key, alternateKey, 0); }

void dance_default_reset_withDoubleTap(uint16_t key, uint16_t alternateKey, uint16_t doubleTap) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP:
        case DOUBLE_SINGLE_TAP:
            unregister_code16(key);
            break;
        case SINGLE_HOLD:
            unregister_code16(alternateKey);
            break;
        case DOUBLE_TAP:
            if (doubleTap)
                unregister_code16(doubleTap);
            else
                unregister_code16(key);
            break;
    }
    dance_state.step = 0;
}
void dance_default_reset(uint16_t key, uint16_t alternateKey) { dance_default_reset_withDoubleTap(key, alternateKey, 0); }

void on_dance_komm(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, DE_COMM); }

void dance_komm_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(DE_COMM, DE_MINS);
}

void dance_komm_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(DE_COMM, DE_MINS); }

void on_dance_SLASH(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, DE_SLSH); }

void dance_SLASH_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(DE_SLSH, (S(DE_MINS)));
}

void dance_SLASH_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(DE_SLSH, S(DE_MINS)); }

void on_dance_dot(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, DE_DOT); }

void dance_dot_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(DE_DOT, DE_EXLM);
}

void dance_dot_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(DE_DOT, DE_EXLM); }

void on_dance_QUOTE(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, DE_QUOT); }

void dance_QUOTE_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished_withDoubleTap(DE_QUOT, DE_DQUO, DE_GRV);
}

void dance_QUOTE_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset_withDoubleTap(DE_QUOT, DE_DQUO, DE_GRV); }

void on_dance_ESC(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, KC_ESCAPE); }

void dance_ESC_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(KC_ESCAPE, LALT(KC_F4));
}

void dance_ESC_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(KC_ESCAPE, LALT(KC_F4)); }

void on_dance_TAB(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, KC_TAB); }

void dance_TAB_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(KC_TAB, LGUI(KC_TAB));
}

void dance_TAB_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(KC_TAB, LGUI(KC_TAB)); }

void on_dance_DELETE(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, KC_DELETE); }

void dance_DELETE_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(KC_DELETE, LCTL(DE_D));
}

void dance_DELETE_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(KC_DELETE, LCTL(DE_D)); }

void on_dance_arrow_left(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, KC_LEFT); }

void dance_arrow_left_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(KC_LEFT, C(KC_LEFT));
}

void dance_arrow_left_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(KC_LEFT, C(KC_LEFT)); }

void on_dance_arrow_right(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, KC_RIGHT); }

void dance_arrow_right_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(KC_RIGHT, C(KC_RIGHT));
}

void dance_arrow_right_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(KC_RIGHT, C(KC_RIGHT)); }

void on_DANCE_Q(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, DE_Q); }

void DANCE_Q_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(DE_Q, DE_AT);
}

void DANCE_Q_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(DE_Q, DE_AT); }

void on_DANCE_A(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, DE_A); }

void DANCE_A_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(DE_A, DE_ADIA);
}

void DANCE_A_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(DE_A, DE_ADIA); }

void on_DANCE_O(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, DE_O); }

void DANCE_O_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(DE_O, DE_ODIA);
}

void DANCE_O_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(DE_O, DE_ODIA); }

void on_DANCE_U(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, DE_U); }

void DANCE_U_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(DE_U, DE_UDIA);
}

void DANCE_U_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(DE_U, DE_UDIA); }

void on_DANCE_S(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, DE_S); }

void DANCE_S_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(DE_S, DE_SS);
}

void DANCE_S_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(DE_S, DE_SS); }

void on_DANCE_REC(qk_tap_dance_state_t *state, void *user_data) { on_dance_default(state, DM_RSTP); }

void DANCE_REC_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_default_dance_step(state);
    dance_default_finished(DM_RSTP, DM_REC1);
}

void DANCE_REC_reset(qk_tap_dance_state_t *state, void *user_data) { dance_default_reset(DM_RSTP, DM_REC1); }

qk_tap_dance_action_t tap_dance_actions[] = {[DANCE_DOT]         = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_dot, dance_dot_finished, dance_dot_reset),
                                             [DANCE_KOMM]        = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_komm, dance_komm_finished, dance_komm_reset),
                                             [DANCE_SLASH]       = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_SLASH, dance_SLASH_finished, dance_SLASH_reset),
                                             [DANCE_QUOTE]       = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_QUOTE, dance_QUOTE_finished, dance_QUOTE_reset),
                                             [DANCE_ESC]         = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_ESC, dance_ESC_finished, dance_ESC_reset),
                                             [DANCE_TAB]         = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_TAB, dance_TAB_finished, dance_TAB_reset),
                                             [DANCE_DELETE]      = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_DELETE, dance_DELETE_finished, dance_DELETE_reset),
                                             [DANCE_ARROW_LEFT]  = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_arrow_left, dance_arrow_left_finished, dance_arrow_left_reset),
                                             [DANCE_ARROW_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_arrow_right, dance_arrow_right_finished, dance_arrow_right_reset),
                                             [DANCE_Q]           = ACTION_TAP_DANCE_FN_ADVANCED(on_DANCE_Q, DANCE_Q_finished, DANCE_Q_reset),
                                             [DANCE_A]           = ACTION_TAP_DANCE_FN_ADVANCED(on_DANCE_A, DANCE_A_finished, DANCE_A_reset),
                                             [DANCE_O]           = ACTION_TAP_DANCE_FN_ADVANCED(on_DANCE_O, DANCE_O_finished, DANCE_O_reset),
                                             [DANCE_U]           = ACTION_TAP_DANCE_FN_ADVANCED(on_DANCE_U, DANCE_U_finished, DANCE_U_reset),
                                             [DANCE_S]           = ACTION_TAP_DANCE_FN_ADVANCED(on_DANCE_S, DANCE_S_finished, DANCE_S_reset),
                                             [DANCE_REC]         = ACTION_TAP_DANCE_FN_ADVANCED(on_DANCE_REC, DANCE_REC_finished, DANCE_REC_reset)};