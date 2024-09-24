// 4-mode-keymap*: Navigation/Numbers**, Code**, Text**, Game
//
// * has 4 default layers
// ** has an additional temporary layer
//
// TODO MCU LEDs???
// - see https://tutoduino.fr/en/tutorials/programing-in-rust-the-xiao-rp2040-board/
// - see https://docs.qmk.fm/#/feature_rgb_matrix?id=indicator-examples-1
//
// TODO for text make macro for `q` as `qu`, or `Q` as `Qu`???
//
// INFO chip apparently has a programmable RGB and other ???

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "totem.h"

// switched from US ANSI to german keycodes, as US ANSI does not have `äöüß` and US Intl. has other
// drawbacks, as e.g. `'"` each require a space to appear because they might be uses as key combos...
#include "keymap_german.h"

enum totem_layers {
    _NAV_NUM_1,
    _NAV_NUM_2,
    _CODE_1,
    _CODE_2,
    _TEXT_1,
    _TEXT_2,
    _GAME_1,
    _GAME_2,
    _LOL, // is last since should not be default layer
};

// default layer swaps are only per session/power-down
#define DF_NN_1 DF(_NAV_NUM_1)
#define DF_CO_1 DF(_CODE_1)
#define DF_TX_1 DF(_TEXT_1)
#define DF_GM_1 DF(_GAME_1)

// TODO wanted an absolute layer select, on hold L/R activate that
// INFO LT(ly, kc) can use only basic keycodes
// but not relevant?? want layer on hold or other layer on tap
//#define LT_NVNM LT(_LAYER_CONTROL, _NAV_NUM)
//#define LT_CO_1 LT(_LAYER_CONTROL, _CODE_1)
//#define LT_TX_1 LT(_LAYER_CONTROL, _TEXT_1)
//#define LT_GAME LT(_LAYER_CONTROL, _GAME)

// discontinued OS_ as of 2024-09-24, as accidental hits of oneshots require additional key press and
// then delete, while in those rare cases where e.g. layer + shift must be pressed simultaneously
// not using oneshot functionality anyway
// #define OS_LCTL OSM(MOD_LCTL)
// #define OS_LSFT OSM(MOD_LSFT)
// #define OS_NN_2 OSL(_NAV_NUM_2)
// #define OS_CO_2 OSL(_CODE_2)
// #define OS_TX_2 OSL(_TEXT_2)
#define MO_NN_2 MO(_NAV_NUM_2)
#define MO_CO_2 MO(_CODE_2)
#define MO_TX_2 MO(_TEXT_2)
#define MO_GM_2 MO(_GAME_2)

enum custom_keys {
    MA_CIRC = SAFE_RANGE,
    MA_GRV,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
   ┌─────────────────────────────────────────────────┐
   │ Layer of Layers                                 │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡         │         │         │         │         ││         │         │         │         │         │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │         │         │         │         │         ││         │ NAV/NUM │ CODE_1  │ TEXT_1  │  GAME   │    
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │         │         │         │         │         │         ││         │         │         │         │         │         │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │         │         │         ││         │         │         │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘
    TODO add macro_recording as meta??
    TODO a layer indicator would still be better...
    NOTES:
    - currently seeing no way ho to combine tap+hold for this+default
*/ 

    [_LOL] = LAYOUT(
// ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  
              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  DF_NN_1,   DF_CO_1,  DF_TX_1,  DF_GM_1,    
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,
                                  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,   XXXXXXX
    ),

/*
   ┌─────────────────────────────────────────────────┐
   │ Navigation and Number Block (Primary)           │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡  CTRL_X │  CTRL_C │  CTRL_A │  CTRL_V │   ESC   ││    +    │    -    │    _    │    .    │    /    │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │   ALT   │    ←    │    ↑    │    →    │   TAB   ││    9    │    1    │    2    │    3    │    4    │    
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │  CODE_1 │   WIN   │   HOME  │    ↓    │   END   │  CTX_M  ││    *    │    5    │    6    │    7    │    8    │  TEXT_1 │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │  CTRL   │  SHIFT  │ NVMN_2  ││    0    │  ENTER  │  BSPC   │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘
    TODO wanted WIN+1 etc. on left hand so can use mouse with right hand...
    NOTES:
    - CTRL_* aligned to Coding X+V, then CTRL_A on middle
    - numpad is designed around `123x` as home while avoiding `8` (frequent usage) on middle up (rather difficult to reach)
    - maintained consistency somewhat by pinning `_./`, though `.` is most frequent character after 123
    - numpad based on a rather limited dataset, so readjustment is likely required
    - NOT using numpad keys as numlock might interfere
*/ 

    [_NAV_NUM_1] = LAYOUT(
// ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              C(DE_X),  C(DE_C),  C(DE_A),  C(DE_V),  KC_ESC,    DE_PLUS,  DE_MINS,  DE_UNDS,  DE_DOT,   DE_SLSH,  
              KC_LALT,  KC_LEFT,  KC_UP,    KC_RGHT,  KC_TAB,    DE_9,     DE_1,     DE_2,     DE_3,     DE_4,    
    DF_CO_1,  KC_LGUI,  KC_HOME,  KC_DOWN,  KC_END,   KC_APP,    DE_ASTR,  DE_5,     DE_6,     DE_7,     DE_8,     DF_TX_1,
                                  KC_LCTL,  KC_LSFT,  MO_NN_2,   DE_0,     KC_ENT,   KC_BSPC
    ),

/*
   ┌─────────────────────────────────────────────────┐
   │ Navigation and Number Block (Secondary)         │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡         │         │  SCROLL │  INSERT │         ││    ←    │   F9    │   F10   │   F11   │   F12   │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │         │         │   PG↑   │  PAUSE  │         ││    ▸    │   F1    │   F2    │   F3    │   F4    │    
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │         │         │         │   PG↓   │  PRINT  │         ││    →    │   F5    │   F6    │   F7    │   F8    │         │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │         │         │    ▼    ││   SPC   │   TAB   │   DEL   │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘
    
    NOTES:
*/ 

    [_NAV_NUM_2] = LAYOUT(
// ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              XXXXXXX,  XXXXXXX,  KC_SCRL,  KC_INS,   XXXXXXX,   KC_MPRV,  KC_F9,    KC_F10,   KC_F11,   KC_F12,
              XXXXXXX,  XXXXXXX,  KC_PGUP,  KC_PAUS,  XXXXXXX,   KC_MPLY,  KC_F1,    KC_F2,    KC_F3,    KC_F4,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PGDN,  KC_PSCR,  XXXXXXX,   KC_MNXT,  KC_F5,    KC_F6,    KC_F7,    KC_F8,    XXXXXXX,
                                  XXXXXXX,  XXXXXXX,  _______,   KC_SPC,   KC_TAB,   KC_DEL
    ),

/*

   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌─────────────────────────────────────────────────┐
   │ Code Input (Primary)                            │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡    X    │    H    │    W    │    V    │    )    ││    (    │    :    │    _    │    .    │    /    │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │    S    │    N    │    R    │    T    │    M    ││    Y    │    C    │    E    │    I    │    A    │    
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │ NVNM_1  │    P    │    F    │    L    │    D    │    B    ││    G    │    U    │    O    │    ,    │    ;    │   GAME  │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │   CTRL  │  SHIFT  │  CODE_2 ││  SPACE  │  ENTER  │   BSPC  │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘
    NOTES:
    - fusion-style, based mainly on a personal and practical mixed Rust and Unreal-C++ sample
    - fixed SNRT**CEIA (the most common letters) and most others as inspired by Ec0vid_Flow layout
    - preferring lower to upper row as per physical characteristics (i.e. mainly moved `ou` down)
    - aligned to a full text layout (see below _TEXT) for key consistency
*/ 

    [_CODE_1] = LAYOUT(
// ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              DE_X,     DE_H,     DE_W,     DE_V,     DE_RPRN,   DE_LPRN,  DE_COLN,  DE_UNDS,  DE_DOT,   DE_SLSH,  
              DE_S,     DE_N,     DE_R,     DE_T,     DE_M,      DE_Y,     DE_C,     DE_E,     DE_I,     DE_A,  
    DF_NN_1,  DE_P,     DE_F,     DE_L,     DE_D,     DE_B,      DE_G,     DE_U,     DE_O,     DE_COMM,  DE_SCLN,  DF_GM_1,
                                  KC_LCTL,  KC_LSFT,  MO_CO_2,   KC_SPC,   KC_ENT,   KC_BSPC
    ),

 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ Code Input (Secondary)                          │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡         │    %    │    @    │    $    │    K    ││    Z    │    "    │    '    │    ~    │    Q    │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │    }    │    >    │    -    │    ?    │    &    ││    *    │    !    │    =    │    <    │    {    │    
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │         │    ^    │    ]    │    +    │    #    │         ││    `    │    \    │    |    │    [    │    J    │  TEXT_1 │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │    ▼    │    ▼    │    ▼    ││    ▼    │   TAB   │   DEL   │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘
    NOTES:
    - inherited `KY"'QJ` from _CODE_2
    - mirrored `{}[]<>?!&*` where pairing `!=`
    - used `{}\|` above text `aous`, as those can be discarded for _TEXT_2 in favour of `äöüß`
    - not coupled to NUM anymore, as is basically impossible to achieve key consistency _and_ a reasonable NUM layout
    - ^` are "alive" (a space is automatically added)
    - rest is generated, with minor manual adjustments
*/ 

    [_CODE_2] = LAYOUT( // INFO not sure, but LAYER key might be required to be transparent for upper layer to work properly
// ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              XXXXXXX,  DE_PERC,  DE_AT,    DE_DLR,   DE_K,      DE_Z,     DE_DQUO,  DE_QUOT,  DE_TILD,  DE_Q,
              DE_RCBR,  DE_RABK,  DE_MINS,  DE_QUES,  DE_AMPR,   DE_ASTR,  DE_EXLM,  DE_EQL,   DE_LABK,  DE_LCBR,  
    XXXXXXX,  MA_CIRC,  DE_RBRC,  DE_PLUS,  DE_HASH,  XXXXXXX,   MA_GRV,   DE_BSLS,  DE_PIPE,  DE_LBRC,  DE_J,     DF_TX_1,
                                  _______,  _______,  _______,   _______,  KC_TAB,   KC_DEL
    ),
 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ Text Input (Primary)                            │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡    X    │    H    │    W    │    V    │    K    ││    Z    │    "    │    '    │    .    │    Q    │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │    S    │    N    │    R    │    T    │    M    ││    Y    │    C    │    E    │    I    │    A    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │   GAME  │    P    │    F    │    L    │    D    │    B    ││    G    │    U    │    O    │    ,    │    J    │ NVNM_1  │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │   CTRL  │  SHIFT  │  TEXT_2 ││  SPACE  │  ENTER  │   BSPC  │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘
    NOTES:
    - 
*/ 

    [_TEXT_1] = LAYOUT(
// ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              DE_X,     DE_H,     DE_W,     DE_V,     DE_K,      DE_Z,     DE_DQUO,  DE_QUOT,  DE_DOT,   DE_Q,
              DE_S,     DE_N,     DE_R,     DE_T,     DE_M,      DE_Y,     DE_C,     DE_E,     DE_I,     DE_A,
    DF_GM_1,  DE_P,     DE_F,     DE_L,     DE_D,     DE_B,      DE_G,     DE_U,     DE_O,     DE_COMM,  DE_J,  DF_NN_1, 
                                  KC_LCTL,  KC_LSFT,  MO_TX_2,   KC_SPC,   KC_ENT,   KC_BSPC
    ),
 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ Text Input (Secondary)                          │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡    °    │    %    │    @    │    €    │    )    ││    (    │    :    │    _    │    ~    │    /    │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │    ß    │    >    │    -    │    ?    │    &    ││    *    │    !    │    =    │    <    │    Ä    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │  CODE_1 │    ^    │    ]    │    +    │    #    │    ´    ││    `    │    Ü    │    Ö    │    [    │    ;    │         │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │    ▼    │    ▼    │    ▼    ││    ▼    │   TAB   │   DEL   │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘
    NOTES:
    - umlaut above bases (obviously), else from coding positions
    - removed (compared with _CODE_2) due to lack of expected usage: {}\|$
    - added: ´°€
    - TODO ndash??? bullet? postponed due to suboptimal compatibility, esp. _across_ operating systems
*/ 

    [_TEXT_2] = LAYOUT(
// ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              DE_DEG,   DE_PERC,  DE_AT,    DE_EURO,  DE_RPRN,   DE_LPRN,  DE_COLN,  DE_UNDS,  DE_TILD,  DE_SLSH,
              DE_SS,    DE_RABK,  DE_MINS,  DE_QUES,  DE_AMPR,   DE_ASTR,  DE_EXLM,  DE_EQL,   DE_LABK,  DE_ADIA,  
    DF_CO_1,  DE_CIRC,  DE_RBRC,  DE_PLUS,  DE_HASH,  DE_ACUT,   DE_GRV,   DE_UDIA,  DE_ODIA,  DE_LBRC,  DE_SCLN,  XXXXXXX,
                                  _______,  _______,  _______,   _______,  KC_TAB,   KC_DEL
    ),
/*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ Game, Media and Function Keys                   │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡   TAB   │    Q    │    X    │    E    │    R    ││    ←    │   F9    │   F10   │   F11   │   F12   │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │  SHIFT  │    A    │    W    │    D    │    F    ││    ▸    │   F1    │   F2    │   F3    │   F4    │   
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │  TEXT_1 │   CTRL  │    Y    │    S    │    C    │    V    ││    →    │   F5    │   F6    │   F7    │   F8    │  CODE_1 │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │   ALT   │  SPACE  │  GAME_2 ││   ESC   │  ENTER  │   DEL   │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘
    NOTES:
    - swapped WS down to be more comfortable
*/ 

    [_GAME_1] = LAYOUT(
// ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_TAB,   DE_Q,     DE_X,     DE_E,     DE_R,      KC_MPRV,  KC_F9,    KC_F10,   KC_F11,   KC_F12,   
              KC_LSFT,  DE_A,     DE_W,     DE_D,     DE_F,      KC_MPLY,  KC_F1,    KC_F2,    KC_F3,    KC_F4,
    DF_TX_1,  KC_LCTL,  DE_Y,     DE_S,     DE_C,     DE_V,      KC_MNXT,  KC_F5,    KC_F6,    KC_F7,    KC_F8,    DF_CO_1,
                                  KC_LALT,  KC_SPC,   MO_GM_2,   KC_ESC,   KC_ENT,   KC_DEL  
    ),
/*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ Game (Secondary)                                │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡         │    H    │         │         │    K    ││    +    │    -    │         │         │         │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │         │    N    │         │    T    │    M    ││    9    │    1    │    2    │    3    │    4    │   
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │         │    P    │         │    L    │         │    B    ││         │    5    │    6    │    7    │    8    │         │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │   CTRL  │  SHIFT  │    ▼    ││    0    │         │         │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘
    NOTES:
    - missing: i, g, u, o, j
*/ 

    [_GAME_2] = LAYOUT(
// ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              XXXXXXX,  DE_H,     XXXXXXX,  XXXXXXX,  DE_K,      DE_PLUS,  DE_MINS,  XXXXXXX,  XXXXXXX,  XXXXXXX,   
              XXXXXXX,  DE_N,     XXXXXXX,  DE_T,     DE_M,      DE_9,     DE_1,     DE_2,     DE_3,     DE_4,
    XXXXXXX,  DE_P,     XXXXXXX,  DE_L,     XXXXXXX,  DE_B,      XXXXXXX,  DE_5,     DE_6,     DE_7,     DE_8,     XXXXXXX,
                                  KC_LCTL,  KC_LSFT,  _______,   DE_0,     XXXXXXX,   XXXXXXX  
    )
};

// TODO could just use post_process_record_user appending a space, if can recognize if LAYER == _CODE_2 ~~
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        switch (keycode) {
        case MA_CIRC:
            tap_code16(DE_CIRC);
            tap_code16(KC_SPC);
            return false;
        case MA_GRV:
            tap_code16(DE_GRV);
            tap_code16(KC_SPC);
            return false;
        }
    }
    
    return true;
}
