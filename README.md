[![Build Status](https://travis-ci.org/yet-another-gauge/sh1106.svg?branch=master)](https://travis-ci.org/yet-another-gauge/sh1106)

# Datasheets and user manuals

* [SH1106, 132 X 64 Dot Matrix OLED/PLED, Segment/Common Driver with Controller](https://www.waveshare.com/w/upload/5/5e/SH1106.pdf)

# Getting started

### CMake

```cmake
# CMakeLists.txt

...
add_executable(<target>
  $<TARGET_OBJECTS:sh1106>
  ...)
  
...
target_include_directories(<target> PUBLIC
        $<TARGET_PROPERTY:sh1106,INTERFACE_INCLUDE_DIRECTORIES>
        ...)

...
```

# Example

### [LibOpenCM3](http://libopencm3.org/)
```c
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/gpio.h>

/**
 * Command Description
 *  1. Power On and Initialization.
 *      1.1. When the built-in DC-DC pump power is being used immediately after turning on the power:
 *          +-----------------------+-----------------------+
 *          |               VDD1 - VSS is off               |
 *          |               VDD2 - VSS is off               |
 *          +-----------------------+-----------------------+
 *                                  |
 *          +-----------------------+-----------------------+
 *          |  Turn on the VDD1 - VSS and VDD2 - VSS power  |
 *          |           keeping the RES pin = "L"           |
 *          |                   (> 10us)                    |
 *          +-----------------------+-----------------------+
 *                                  |
 *          +-----------------------+-----------------------+
 *          |         When the power is stabilized          |
 *          +-----------------------+-----------------------+
 *                                  |
 */
 
void sh1106_init(sh1106_send8_cmd_t send8_cmd) {

  /**
   *                                |
   *        +-----------------------+-----------------------+
   *        |    Release the reset state (RES pin = "H")    |
   *        |                    (> 2us)                    |
   *        +-----------------------+-----------------------+
   *                                |
   */

  gpio_set(PORT_RES, PIN_RES);

  /**
   *                                |
   *        +-----------------------+-----------------------+
   *        |          Initialized state (Default)          |
   *        +-----------------------+-----------------------+
   *                                |
   *        +-----------------------+-----------------------+
   *        | Function setup by command input (User setup): |
   *        |    (6) Segment Re-map (ADC) selection         |
   *        |   (17) COM Sequential / Alternative Mode      |
   *        |        selection                              |
   *        |   (13) COM Output Scan Direction selection    |
   *        |    (9) Multiplex Ration Mode selection        |
   *        |   (15) Display Divide Ratio / Oscillator      |
   *        |        Frequency Mode selection               |
   *        +-----------------------+-----------------------+
   *                                |
   */

  sh1106_set_segment_re_map(send8_cmd, SH1106_SEGMENT_RE_MAP_REVERSE_DIRECTION);
  sh1106_set_common_pads_hardware_configuration(send8_cmd, SH1106_COMMON_SIGNALS_PAD_CONFIGURATION_ALTERNATIVE);
  sh1106_set_common_output_scan_direction(send8_cmd, SH1106_COMMON_OUTPUT_SCAN_NORMAL_DIRECTION);
  sh1106_set_multiplex_ration(send8_cmd, 0x3F);
  sh1106_set_display_clock_divide_ratio_oscillator_frequency(send8_cmd, 1, SH1106_OSCILLATOR_FREQUENCY_POR);

  /**
   *                                |
   *        +-----------------------+-----------------------+
   *        | Function setup by command input (User setup): |
   *        |   (18) VCOM Deselect Level set                |
   *        |    (5) Contrast set                           |
   *        |    (3) Vpp value set (suggested from Factory) |
   *        +-----------------------+-----------------------+
   *                                |
   */

  sh1106_set_vcom_deselect_level(send8_cmd, 0x35);
  sh1106_set_contrast_control_register(send8_cmd, 0xFF);
  sh1106_set_pump_voltage(send8_cmd, SH1106_PUMP_VOLTAGE_7_4);

  /**
   *                                |
   *        +-----------------------+-----------------------+
   *        | Function setup by command input (User setup): |
   *        |   Clear internal RAM to "00H"                 |
   *        +-----------------------+-----------------------+
   *                                |
   *        +-----------------------+-----------------------+
   *        | Function setup by command input (User setup): |
   *        |   (10) DC-DC Control set: "ADH"               |
   *        |        Built-in DC-DC turn on: "8BH" (POR)    |
   *        +-----------------------+-----------------------+
   *                                |
   */

  sh1106_set_dc_dc_mode(send8_cmd, SH1106_DC_DC_ENABLE);

  /**
   *                                |
   *        +-----------------------+-----------------------+
   *        | When the DC-DC Power (Vpp) is stabilized.     |
   *        | Typically, 100ms delay is recommended to wait.|
   *        +-----------------------+-----------------------+
   *                                |
   *        +-----------------------+-----------------------+
   *        | Function setup by command input (User setup): |
   *        |   (11) Display ON set: "AFH"                  |
   *        +-----------------------+-----------------------+
   *                                |
   */

  sh1106_set_display_state(send8_cmd, SH1106_OLED_ON);

  /**
   *                                |
   *        +-----------------------+-----------------------+
   *        | Typically, 150ms delay is recommended to wait.|
   *        +-----------------------+-----------------------+
   *                                |
   *        +-----------------------+-----------------------+
   *        | Function setup by command input (User setup): |
   *        |    (4) Display Start Line set                 |
   *        |   (12) Page Address set                       |
   *        |   (1, 2) Column Address set                   |
   *        +-----------------------+-----------------------+
   *                                |
   */

  sh1106_set_display_start_line(send8_cmd, 0);
  sh1106_set_page_address(send8_cmd, 0);
  sh1106_set_column_address(send8_cmd, 0);

  /**
   *                                |
   *        +-----------------------+-----------------------+
   *        |               Display Data Send               |
   *        +-----------------------+-----------------------+
   */
}

// ...

static void sh1106_spi_send8_cmd(uint8_t cmd) {
  gpio_clear(..., ...); // The data/command control pad
  spi_send8(SH1106_SPI, cmd);
}

static void sh1106_spi_send8_data(uint8_t data) {
  gpio_set(..., ...); // The data/command control pad
  spi_send8(SH1106_SPI, data);
}

int main(void) {
  // ...
  
  sh1106_init(spi_send8_cmd);
  
  // ...
}

```

# API

### [Set column address](https://github.com/yet-another-gauge/sh1106/wiki/API#set-column-address) 
Specifies column address of display RAM. When the microprocessor repeats to access to the display RAM, the column address counter is incremented during each access until address 132 is accessed. The page address is not changed during this time.
```c
void sh1106_set_column_address(const sh1106_send8_cmd_t send8_cmd, uint8_t column_addr);
```
### [Set pump voltage value](https://github.com/yet-another-gauge/sh1106/wiki/API#set-pump-voltage-value) 
Specifies output voltage (`Vpp`) of the internal charger pump.
```c
void sh1106_set_pump_voltage(const sh1106_send8_cmd_t send8_cmd, enum sh1106_pump_voltage pump_voltage);
```
### [Set display start line](https://github.com/yet-another-gauge/sh1106/wiki/API#set-display-start-line) 
Specifies line address to determine the initial display line or COM0. The RAM display data becomes the top line of OLED screen. It is followed by the higher number of lines in ascending order, corresponding to the duty cycle. When this command changes the line address, the smooth scrolling or page change takes place.
```c
void sh1106_set_display_start_line(const sh1106_send8_cmd_t send8_cmd, uint8_t line_addr);
```
### [Set contrast control register](https://github.com/yet-another-gauge/sh1106/wiki/API#set-contrast-control-register) 
This command is to set contrast setting of the display. The chip has 256 contrast steps from `0x00` to `0xFF`. The segment output current increases as the contrast step value increases. Segment output current setting:  
```c
ISEG = contrast_step / 256 * IREF * scale_factor = contrast_step / 256 * 10 * 32
```
```c
void sh1106_set_contrast_control_register(const sh1106_send8_cmd_t send8_cmd, uint8_t contrast);
```
### [Set segment re-map](https://github.com/yet-another-gauge/sh1106/wiki/API#set-segment-re-map) 
Change the relationship between RAM column address and segment driver. The order of segment driver output pads can be reversed by software. This allows flexible IC layout during OLED module assembly. When display data is written or read, the column address is incremented by 1.
```c
void sh1106_set_segment_re_map(const sh1106_send8_cmd_t send8_cmd, enum sh1106_segment_re_map_direction segment_re_map_direction);
```
### [Set entire display OFF/ON](https://github.com/yet-another-gauge/sh1106/wiki/API#set-entire-display-offon) 
Forcibly turns the entire display on regardless of the contents of the display data RAM. At this time, the contents of the display data RAM are held. This command has priority over the normal/reverse display command.
```c
void sh1106_set_display_state(const sh1106_send8_cmd_t send8_cmd, enum sh1106_display_state display_state);
```
### [Display OFF/ON OLED](https://github.com/yet-another-gauge/sh1106/wiki/API#display-offon-oled) 
Alternatively turns the display ON and OFF. When the display OFF command is executed, power saver mode will be entered.
```c
void sh1106_set_display_state(const sh1106_send8_cmd_t send8_cmd, enum sh1106_display_state display_state);
```
### [Set normal/reverse display](https://github.com/yet-another-gauge/sh1106/wiki/API#set-normalreverse-display) 
Reverses the display ON/OFF status without rewriting the contents of the display data RAM. 
```c
void sh1106_set_display_direction(const sh1106_send8_cmd_t send8_cmd, enum sh1106_display_direction display_direction);
```
### [Set multiplex ration](https://github.com/yet-another-gauge/sh1106/wiki/API#set-multiplex-ration) 
This command switches default 64 multiplex modes to any multiplex ratio from 1 to 64. The output pads COM0-COM63 will be switched to corresponding common signal.
```c
void sh1106_set_multiplex_ration(const sh1106_send8_cmd_t send8_cmd, uint8_t multiplex_ratio);
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
void sh1106_set_dc_dc_mode(const sh1106_send8_cmd_t send8_cmd, enum sh1106_dc_dc_mode dc_dc_mode);
```
### [Set page address](https://github.com/yet-another-gauge/sh1106/wiki/API#set-page-address) 
Specifies page address to load display RAM data to page address register. Any RAM data bit can be accessed when its page address and column address are specified. The display remains unchanged even when the page address is changed.
```c
void sh1106_set_page_address(const sh1106_send8_cmd_t send8_cmd, uint8_t page_addr);
```
### [Set common output scan direction](https://github.com/yet-another-gauge/sh1106/wiki/API#set-common-output-scan-direction) 
This command sets the scan direction of the common output allowing layout flexibility in OLED module design. In addition, the display will have immediate effect once this command is issued. That is, if this command is sent during normal display, the graphic display will be vertically flipped.
```c
void sh1106_set_common_output_scan_direction(const sh1106_send8_cmd_t send8_cmd, enum sh1106_common_output_scan_direction common_output_scan_direction);
```
### [Set display offset](https://github.com/yet-another-gauge/sh1106/wiki/API#set-display-offset) 
This command specifies the mapping of display start line to one of COM0-63 (it is assumed that COM0 is the display start line, that equals to 0). For example, to move the COM16 towards the COM0 direction for 16 lines, the 6-bit data in the second byte should be given by `0b010000`. To move in the opposite direction by 16 lines, the 6-bit data should be given by (64-16), so the second byte should be `0b100000`.
```c
void sh1106_set_display_offset(const sh1106_send8_cmd_t send8_cmd, uint8_t display_offset);
```
### [Set display clock divide ratio/oscillator frequency](https://github.com/yet-another-gauge/sh1106/wiki/API#set-display-clock-divide-ratiooscillator-frequency) 
This command is used to set the frequency of the internal display clocks (DCLKs). It is defined as the divide ratio (value from 1 to 16) used to divide the oscillator frequency. POR is 1. Frame frequency is determined by divide ratio, number of display clocks per row, MUX ratio and oscillator frequency.
```c
void sh1106_set_display_clock_divide_ratio_oscillator_frequency(const sh1106_send8_cmd_t send8_cmd, uint8_t clock_divide_ration, enum sh1106_oscillator_frequency oscillator_frequency);
```
### [Set dis-charge/pre-charge period](https://github.com/yet-another-gauge/sh1106/wiki/API#set-dis-chargepre-charge-period) 
This command is used to set the duration of the pre-charge period. The interval is counted in number of DCLK. POR is 2 DCLKs.
```c
void sh1106_set_dis_charge_pre_charge_period(const sh1106_send8_cmd_t send8_cmd, uint8_t pre_charge_period, uint8_t dis_charge_period);
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
void sh1106_set_common_pads_hardware_configuration(const sh1106_send8_cmd_t send8_cmd, enum sh1106_common_signals_pad_configuration common_signals_pad_configuration);
```
### [Set VCOM deselect level](https://github.com/yet-another-gauge/sh1106/wiki/API#set-vcom-deselect-level) 
This command is to set the common pad output voltage level at deselect stage.

  | deselect_level | β       | deselect_level | β       |
  | :------------: | :-----: | :------------: | :-----: |
  | 0x00           | 0.430   | 0x20           | 0.63528 |
  | 0x01           | 0.43642 | 0x21           | 0.6417  |
  | 0x02           | 0.44283 | 0x22           | 0.64811 |
  | 0x03           | 0.44925 | 0x23           | 0.65453 |
  | 0x04           | 0.45566 | 0x24           | 0.66094 |
  | 0x05           | 0.46208 | 0x25           | 0.66735 |
  | 0x06           | 0.46849 | 0x26           | 0.67377 |
  | 0x07           | 0.47491 | 0x27           | 0.68019 |
  | 0x08           | 0.48132 | 0x28           | 0.6866  |
  | 0x09           | 0.48774 | 0x29           | 0.69302 |
  | 0x0A           | 0.49415 | 0x2A           | 0.69943 |
  | 0x0B           | 0.50057 | 0x2B           | 0.70585 |
  | 0x0C           | 0.50698 | 0x2C           | 0.71226 |
  | 0x0D           | 0.5134  | 0x2D           | 0.71868 |
  | 0x0E           | 0.51981 | 0x2E           | 0.72509 |
  | 0x0F           | 0.52623 | 0x2F           | 0.73151 |
  | 0x10           | 0.53264 | 0x30           | 0.73791 |
  | 0x11           | 0.53906 | 0x31           | 0.74434 |
  | 0x12           | 0.54547 | 0x32           | 0.75075 |
  | 0x13           | 0.55189 | 0x33           | 0.75717 |
  | 0x14           | 0.5583  | 0x34           | 0.76358 |
  | 0x15           | 0.56472 | **0x35**       | **0.770 (POR)** |
  | 0x16           | 0.57113 | 0x36           | 0.77641 |
  | 0x17           | 0.57755 | 0x37           | 0.78283 |
  | 0x18           | 0.58396 | 0x38           | 0.78924 |
  | 0x19           | 0.59038 | 0x39           | 0.79566 |
  | 0x1A           | 0.59679 | 0x3A           | 0.80207 |
  | 0x1B           | 0.60321 | 0x3B           | 0.80848 |
  | 0x1C           | 0.60962 | 0x3C           | 0.8149  |
  | 0x1D           | 0.61604 | 0x3D           | 0.82132 |
  | 0x1E           | 0.62245 | 0x3E           | 0.82773 |
  | 0x1F           | 0.62887 | 0x3F           | 0.83415 |
  |                |         | 0x40 - 0xFF    | 1       |

```c
Vcom = β * Vref = (0.430 + deselect_level * 0.006415) * Vref
```
```c
void sh1106_set_vcom_deselect_level(const sh1106_send8_cmd_t send8_cmd, uint8_t deselect_level);
```
### [Read-Modify-Write](https://github.com/yet-another-gauge/sh1106/wiki/API#read-modify-write) 
A pair of Read-Modify-Write and End commands must always be used. Once read-modify-write is issued, column address is not incremental by read display data command but incremental by write display data command only. It continues until End command is issued. When the End is issued, column address returns to the address when read-modify-write is issued. This can reduce the microprocessor load when data of a specific display area is repeatedly changed during cursor blinking or others.
```c
void sh1106_read_modify_write(const sh1106_send8_cmd_t send8_cmd);
```
### [End](https://github.com/yet-another-gauge/sh1106/wiki/API#end) 
Cancels Read-Modify-Write mode and returns column address to the original address (when Read-Modify-Write is issued).
```c
void sh1106_end(const sh1106_send8_cmd_t send8_cmd);
```
### [NOP](https://github.com/yet-another-gauge/sh1106/wiki/API#nop) 
Non-Operation Command.
```c
void sh1106_nop(const sh1106_send8_cmd_t send8_cmd);
```
### [Write display data](https://github.com/yet-another-gauge/sh1106/wiki/API#write-display-data) 
Write 8-bit data in display RAM. As the column address is incremental by 1 automatically after each write, the microprocessor can continue to write data of multiple words.
```c
void sh1106_write_display_data(const sh1106_send8_data_t send8_data, uint8_t data);
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
