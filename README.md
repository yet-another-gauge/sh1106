# Datasheets and user manuals

* [SH1106, 132 X 64 Dot Matrix OLED/PLED, Segment/Common Driver with Controller](https://www.waveshare.com/w/upload/5/5e/SH1106.pdf)

# API

### [Set column address](https://github.com/yet-another-gauge/sh1106/wiki/API#set-column-address) 
Specifies column address of display RAM. When the microprocessor repeats to access to the display RAM, the column address counter is incremented during each access until address 132 is accessed. The page address is not changed during this time.
```c
void sh1106_set_column_address(t_send8 send8, uint8_t column_addr);
```
### [Set pump voltage value](https://github.com/yet-another-gauge/sh1106/wiki/API#set-pump-voltage-value) 
Specifies output voltage (`Vpp`) of the internal charger pump.
```c
void sh1106_set_pump_voltage(t_send8 send8, enum sh1106_pump_voltage pump_voltage);
```
### [Set display start line](https://github.com/yet-another-gauge/sh1106/wiki/API#set-display-start-line) 
Specifies line address to determine the initial display line or COM0. The RAM display data becomes the top line of OLED screen. It is followed by the higher number of lines in ascending order, corresponding to the duty cycle. When this command changes the line address, the smooth scrolling or page change takes place.
```c
void sh1106_set_display_start_line(t_send8 send8, uint8_t line_addr);
```
### [Set contrast control register](https://github.com/yet-another-gauge/sh1106/wiki/API#set-contrast-control-register) 
This command is to set contrast setting of the display. The chip has 256 contrast steps from `0x00` to `0xFF`. The segment output current increases as the contrast step value increases. Segment output current setting:  
```c
ISEG = contrast_step / 256 * IREF * scale_factor = contrast_step / 256 * 10 * 32
```
```c
void sh1106_set_contrast_control_register(t_send8 send8, uint8_t contrast);
```
### [Set segment re-map](https://github.com/yet-another-gauge/sh1106/wiki/API#set-segment-re-map) 
Change the relationship between RAM column address and segment driver. The order of segment driver output pads can be reversed by software. This allows flexible IC layout during OLED module assembly. When display data is written or read, the column address is incremented by 1.
```c
void sh1106_set_segment_re_map(t_send8 send8, enum sh1106_segment_re_map_direction segment_re_map_direction);
```
### [Set entire display OFF/ON](https://github.com/yet-another-gauge/sh1106/wiki/API#set-entire-display-offon) 
Forcibly turns the entire display on regardless of the contents of the display data RAM. At this time, the contents of the display data RAM are held. This command has priority over the normal/reverse display command.
```c
void sh1106_set_display_state(t_send8 send8, enum sh1106_display_state display_state);
```
### [Display OFF/ON OLED](https://github.com/yet-another-gauge/sh1106/wiki/API#display-offon-oled) 
Alternatively turns the display ON and OFF. When the display OFF command is executed, power saver mode will be entered.
```c
void sh1106_set_display_state(t_send8 send8, enum sh1106_display_state display_state);
```
### [Set normal/reverse display](https://github.com/yet-another-gauge/sh1106/wiki/API#set-normalreverse-display) 
Reverses the display ON/OFF status without rewriting the contents of the display data RAM. 
```c
void sh1106_set_display_direction(t_send8 send8, enum sh1106_display_direction display_direction);
```
### [Set multiplex ration](https://github.com/yet-another-gauge/sh1106/wiki/API#set-multiplex-ration) 
This command switches default 64 multiplex modes to any multiplex ratio from 1 to 64. The output pads COM0-COM63 will be switched to corresponding common signal.
```c
void sh1106_set_multiplex_ration(t_send8 send8, uint8_t multiplex_ratio);
```
### [Set DC-DC OFF/ON](https://github.com/yet-another-gauge/sh1106/wiki/API#set-dc-dc-offon) 
This command is to control the DC-DC voltage converter. The converter will be turned on by issuing this command then display ON command. The panel display must be OFF while issuing this command.

  | DC-DC STATUS | DISPLAY ON/OFF STATUS | Description                            |
  | :----------: | :-------------------: | :------------------------------------: |
  | 0            | 0                     | Sleep mode                             |
  | 0            | 1                     | External VPP must be used              |
  | 1            | 0                     | Sleep mode                             |
  | 1            | 1                     | Built-in DC-DC is used, Normal Display |

```c
void sh1106_set_dc_dc_mode(t_send8 send8, enum sh1106_dc_dc_mode dc_dc_mode);
```
### [Set page address](https://github.com/yet-another-gauge/sh1106/wiki/API#set-page-address) 
Specifies page address to load display RAM data to page address register. Any RAM data bit can be accessed when its page address and column address are specified. The display remains unchanged even when the page address is changed.
```c
void sh1106_set_page_address(t_send8 send8, uint8_t page_addr);
```
### [Set common output scan direction](https://github.com/yet-another-gauge/sh1106/wiki/API#set-common-output-scan-direction) 
This command sets the scan direction of the common output allowing layout flexibility in OLED module design. In addition, the display will have immediate effect once this command is issued. That is, if this command is sent during normal display, the graphic display will be vertically flipped.
```c
void sh1106_set_common_output_scan_direction(t_send8 send8, enum sh1106_common_output_scan_direction common_output_scan_direction);
```
### [Set display offset](https://github.com/yet-another-gauge/sh1106/wiki/API#set-display-offset) 
This command specifies the mapping of display start line to one of COM0-63 (it is assumed that COM0 is the display start line, that equals to 0). For example, to move the COM16 towards the COM0 direction for 16 lines, the 6-bit data in the second byte should be given by `0b010000`. To move in the opposite direction by 16 lines, the 6-bit data should be given by (64-16), so the second byte should be `0b100000`.
```c
void sh1106_set_display_offset(t_send8 send8, uint8_t display_offset);
```
### [Set display clock divide ratio/oscillator frequency](https://github.com/yet-another-gauge/sh1106/wiki/API#set-display-clock-divide-ratiooscillator-frequency) 
This command is used to set the frequency of the internal display clocks (DCLKs). It is defined as the divide ratio (value from 1 to 16) used to divide the oscillator frequency. POR is 1. Frame frequency is determined by divide ratio, number of display clocks per row, MUX ratio and oscillator frequency.
```c
void sh1106_set_display_clock_divide_ratio_oscillator_frequency(t_send8 send8, uint8_t clock_divide_ration, enum sh1106_oscillator_frequency oscillator_frequency);
```
### [Set dis-charge/pre-charge period](https://github.com/yet-another-gauge/sh1106/wiki/API#set-dis-chargepre-charge-period) 
This command is used to set the duration of the pre-charge period. The interval is counted in number of DCLK. POR is 2 DCLKs.
```c
void sh1106_set_dis_charge_pre_charge_period(t_send8 send8, uint8_t pre_charge_period, uint8_t dis_charge_period);
```
### [Set common pads hardware configuration](https://github.com/yet-another-gauge/sh1106/wiki/API#set-common-pads-hardware-configuration) 
This command is to set the common signals pad configuration (sequential or alternative) to match the OLED panel hardware layout.
    
Sequential:
    
  | COM31,30 - 1,0 | SEG0,1 - 130,131 | COM32,33 - 62,63 |
  | :------------: | :--------------: | :--------------: |
    
Alternative (POR):
    
  | COM62,60 - 2,0 | SEG0,1 - 130,131 | COM1,3 - 61,63 |
  | :------------: | :--------------: | :------------: |

```c
void sh1106_set_common_pads_hardware_configuration(t_send8 send8, enum sh1106_common_signals_pad_configuration common_signals_pad_configuration);
```
### [Set VCOM deselect level](https://github.com/yet-another-gauge/sh1106/wiki/API#set-vcom-deselect-level) 
This command is to set the common pad output voltage level at deselect stage.

  | deselect_level | β       | deselect_level | β           | deselect_level | β           | deselect_level | β           |
  | :------------: | :-----: | :------------: | :---------: | :------------: | :---------: | :------------: | :---------: |
  | 0x00           | 0.430   | 0x10           |             | 0x20           |             | 0x30           |             |
  | 0x01           |         | 0x11           |             | 0x21           |             | 0x31           |             |
  | 0x02           |         | 0x12           |             | 0x22           |             | 0x32           |             |
  | 0x03           |         | 0x13           |             | 0x23           |             | 0x33           |             |
  | 0x04           |         | 0x14           |             | 0x24           |             | 0x34           |             |
  | 0x05           |         | 0x15           |             | 0x25           |             | 0x35           | 0.770 (POR) |
  | 0x06           |         | 0x16           |             | 0x26           |             | 0x36           |             |
  | 0x07           |         | 0x17           |             | 0x27           |             | 0x37           |             |
  | 0x08           |         | 0x18           |             | 0x28           |             | 0x38           |             |
  | 0x09           |         | 0x19           |             | 0x29           |             | 0x39           |             |
  | 0x0A           |         | 0x1A           |             | 0x2A           |             | 0x3A           |             |
  | 0x0B           |         | 0x1B           |             | 0x2B           |             | 0x3B           |             |
  | 0x0C           |         | 0x1C           |             | 0x2C           |             | 0x3C           |             |
  | 0x0D           |         | 0x1D           |             | 0x2D           |             | 0x3D           |             |
  | 0x0E           |         | 0x1E           |             | 0x2E           |             | 0x3E           |             |
  | 0x0F           |         | 0x1F           |             | 0x2F           |             | 0x3F           |             |
  |                |         |                |             |                |             | 0x40 - 0xFF    | 1           |

```c
Vcom = β * Vref = (0.430 + deselect_level * 0.006415) * Vref
```
```c
void sh1106_set_vcom_deselect_level(t_send8 send8, uint8_t deselect_level);
```
### [Read-Modify-Write](https://github.com/yet-another-gauge/sh1106/wiki/API#read-modify-write) 
A pair of Read-Modify-Write and End commands must always be used. Once read-modify-write is issued, column address is not incremental by read display data command but incremental by write display data command only. It continues until End command is issued. When the End is issued, column address returns to the address when read-modify-write is issued. This can reduce the microprocessor load when data of a specific display area is repeatedly changed during cursor blinking or others.
```c
void sh1106_read_modify_write(t_send8 send8);
```
### [End](https://github.com/yet-another-gauge/sh1106/wiki/API#end) 
Cancels Read-Modify-Write mode and returns column address to the original address (when Read-Modify-Write is issued).
```c
void sh1106_end(t_send8 send8);
```
### [NOP](https://github.com/yet-another-gauge/sh1106/wiki/API#nop) 
Non-Operation Command.
```c
void sh1106_nop(t_send8 send8);
```
### [Write display data](https://github.com/yet-another-gauge/sh1106/wiki/API#write-display-data) 
Write 8-bit data in display RAM. As the column address is incremental by 1 automatically after each write, the microprocessor can continue to write data of multiple words.
```c
void sh1106_write_display_data(t_send8 send8, uint8_t data);
```
### [Read status](https://github.com/yet-another-gauge/sh1106/wiki/API#read-status) 
```c
// todo
```
### [Read display data](https://github.com/yet-another-gauge/sh1106/wiki/API#read-display-data) 
```c
// todo
```

# See Also

* [T-Rex runner](https://github.com/yet-another-gauge/t-rex-runner)

# License

Copyright (C) 2018 Ivan Dyachenko <vandyachen@gmail.com>

This library is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this library. If not, see <http://www.gnu.org/licenses/>.
