# My KB Paradise V60 Type R Layout with support for HID rgb control

## Sending HID packages to control lighting
The HID feature report id should be left at 0.  
Bytes: r, g, b, l  
RGB being the value for the underglow and the l being the level of the backlight.  
A backlight value of 0 is full brightness and a value of 3 turns it off  

### Build
To build this keymap, simply run `make v60_type_r:dotjulia`.
