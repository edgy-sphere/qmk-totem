```
                                                       ▀▀▀▀▀     ▀▀▀▀▀          ▀▀█▀▀
                                                       ▄▀▀▀▄  ▄  ▄▀▀▀▄  ▄  ▄▀▀▀▄  █  ▄▀▀▀▄
                                                       █   █  █  █   █  █  █   █  █  █   █
                                                        ▀▀▀   █   ▀▀▀   █   ▀▀▀   ▀   ▀▀▀
                                                              █      ▄▄▄█▄▄▄    █   █  
                                                              ▀      █  █  █     █▄█
                                                            ▀▀▀▀▀    █  █  █      ▀
                                                                     ▀  ▀  ▀
▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
       
```
# TOTEM split keyboard

TOTEM is 34 keys column-staggered split keyboard made by @geigeigeist. It uses the Seeed XIAO RP2040.

You can use this command to compile the firmware
`qmk compile -kb totem -km default`


## My Notes

This uses `#define EE_HANDS` to determine handedness of split keyboard.
The EEPROM flag can only be set via `-bl uf2-split-left` (or `-right`) which can only be an argument for `qmk flash` not `qmk compile` and the former requires a connected flashable device _which then cannot be used to flash the other half!!!!_
- well, not working... does not recogniz device and cannot set as arg?? docs dont dwell on this at all???
- but can CTRL+C, uf2 file is built as per compile~
- original totem did not set `SPLIT_KEYBOARD = yes` in `rules.mk` ????

OR can use `make totem:default:uf2-split-right ; mv .build/totem_default.uf2 .build/totem_default_right.uf2` and `make totem:default:uf2-split-left ; mv .build/totem_default.uf2 .build/totem_default_left.uf2`???