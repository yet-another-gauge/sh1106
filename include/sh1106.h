/**
 * This file is part of the 'Yet another gauge' project.
 *
 * Copyright (C) 2018 Ivan Dyachenko <vandyachen@gmail.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef YET_ANOTHER_GAUGE__SH1106_H
#define YET_ANOTHER_GAUGE__SH1106_H

#include <stdint.h>

/**
 * @brief TODO
 *
 * @param[in] data 8 bit data to written
 */
typedef void (*t_send8)(uint8_t data);

/**
 * @brief Set column address
 *  Specifies column address of display RAM. Divide the column address into 4 higher bits and 4 lower bits. Set each
 *  of them into successions. When the microprocessor repeats to access to the display RAM, the column address
 *  counter is incremented during each access until address 132 is accessed. The page address is not changed during
 *  this time.
 *              +----+----+----+   +----+----+----+----+----+----+----+----+
 *              | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *              +----+----+----+   +----+----+----+----+----+----+----+----+
 *  Higher bits |  0 |  1 |  0 |   |  0 |  0 |  0 |  1 | A7 | A6 | A5 | A4 |
 *              +----+----+----+   +----+----+----+----+----+----+----+----+
 *   Lower bits |  0 |  1 |  0 |   |  0 |  0 |  0 |  0 | A3 | A2 | A1 | A0 |
 *              +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  +----+----+----+----+----+----+----+----+----------------+
 *  | A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 | Column address |
 *  +----+----+----+----+----+----+----+----+----------------+
 *  |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |              0 |
 *  |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  1 |              1 |
 *  |                                                    ... |
 *  |  1 |  0 |  0 |  0 |  0 |  0 |  1 |  1 |            131 |
 *  +----+----+----+----+----+----+----+----+----------------+
 *
 * @param[in] send8 TODO
 * @param[in] addr TODO
 */
void sh1106_set_column_address(t_send8 send8, uint8_t addr);

/**
 * @brief TODO
 */
enum sh1106_pump_voltage {
    /** Pump output voltage (Vpp) 7.4 (Power on) */
            SH1106_PUMP_VOLTAGE_7_4,
    /** Pump output voltage (Vpp) 8.0 */
            SH1106_PUMP_VOLTAGE_8_0,
    /** Pump output voltage (Vpp) 8.4 */
            SH1106_PUMP_VOLTAGE_8_4,
    /** Pump output voltage (Vpp) 9.0 */
            SH1106_PUMP_VOLTAGE_9_0,
};

/**
 * @brief Set Pump voltage value: (30H~33H)
 *  Specifies output voltage (Vpp) of the internal charger pump.
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  0 |  1 |  0 |   |  0 |  0 |  1 |  1 |  0 |  0 | A1 | A0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  +----+----+---------------------------+
 *  | A1 | A0 | Pump output voltage (Vpp) |
 *  +----+----+---------------------------+
 *  |  0 |  0 |            7.4 (Power on) |
 *  |  0 |  1 |                       8.0 |
 *  |  1 |  0 |                       8.4 |
 *  |  1 |  1 |                       9.0 |
 *  +----+----+---------------------------+
 *
 * @param[in] send8 TODO
 * @param[in] pump_voltage TODO
 */
void sh1106_set_pump_voltage(t_send8 send8, enum sh1106_pump_voltage pump_voltage);

/**
 * @brief Set Display Start Line: (40H - 7FH)
 *  Specifies line address to determine the initial display line or COM0. The RAM display data becomes the top line
 *  of OLED screen. It is followed by the higher number of lines in ascending order, corresponding to the duty
 *  cycle. When this command changes the line address, the smooth scrolling or page change takes place.
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  0 |  1 |  0 |   |  0 |  1 | A5 | A4 | A3 | A2 | A1 | A0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  +----+----+----+----+----+----+--------------+
 *  | A5 | A4 | A3 | A2 | A1 | A0 | Line address |
 *  +----+----+----+----+----+----+--------------+
 *  |  0 |  0 |  0 |  0 |  0 |  0 |            0 |
 *  |  0 |  0 |  0 |  0 |  0 |  1 |            1 |
 *  |                                        ... |
 *  |  1 |  1 |  1 |  1 |  1 |  0 |           62 |
 *  |  1 |  1 |  1 |  1 |  1 |  1 |           63 |
 *  +----+----+----+----+----+----+--------------+
 *
 * @param[in] send8 TODO
 * @param[in] addr TODO
 */
void sh1106_set_display_start_line(t_send8 send8, uint8_t addr);

/**
 * @brief Set Contrast Control Register: (Double Bytes Command)
 *  This command is to set contrast setting of the display. The chip has 256 contrast steps from 00 to FF.
 *  The segment output current increases as the contrast step value increases.
 *  Segment output current setting: ISEG = α/256 X IREF X scale factor
 *  Where: α is contrast step; IREF is reference current equals 10μA; Scale factor = 32.
 *
 *  The Contrast Control Mode Set: (81H)
 *      When this command is input, the contrast data register set command becomes enabled. Once the contrast
 *      control mode has been set, no other command except for the contrast data register command can be used. Once
 *      the contrast data set command has been used to set data into the register, then the contrast control mode is
 *      released.
 *
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  0 |  0 |  0 |  0 |  0 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  Contrast Data Register Set: (00H - FFH)
 *      By using this command to set eight bits of data to the contrast data register; the OLED segment output
 *      assumes one of the 256 current levels. When this command is input, the contrast control mode is released
 *      after the contrast data register has been set.
 *
 *      +----+----+----+   +----+----+----+----+----+----+----+----+-------+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |  ISEG |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+-------+
 *      |  0 |  1 |  0 |   |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 | Small |
 *      |  0 |  1 |  0 |   |  0 |  0 |  0 |  0 |  0 |  0 |  1 |  0 |       |
 *      |  0 |  1 |  0 |   |  0 |  0 |  0 |  0 |  0 |  0 |  1 |  1 |       |
 *      |  0 |  1 |  0 |   |                                           ... |
 *      |  0 |  1 |  0 |   |  1 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |   POR |
 *      |  0 |  1 |  0 |   |                                           ... |
 *      |  0 |  1 |  0 |   |  1 |  1 |  1 |  1 |  1 |  1 |  1 |  0 |       |
 *      |  0 |  1 |  0 |   |  1 |  1 |  1 |  1 |  1 |  1 |  1 |  1 | Large |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+-------+
 *
 *      When the contrast control function is not used, set the D7 - D0 to 10000000.
 *
 * @param[in] send8 TODO
 * @param[in] contrast TODO
 */
void sh1106_set_contrast_control_register(t_send8 send8, uint8_t contrast);

/**
 * @brief TODO
 */
enum sh1106_segment_direction {
    /** The right rotates (normal direction). (POR) */
            SH1106_SEGMENT_NORMAL_DIRECTION,
    /** The left rotates (reverse direction). */
            SH1106_SEGMENT_REVERSE_DIRECTION,
};

/**
 * @brief Set Segment Re-map: (A0H - A1H)
 *  Change the relationship between RAM column address and segment driver. The order of segment driver output pads
 *  can be reversed by software. This allows flexible IC layout during OLED module assembly.
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+-----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 |  D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+-----+
 *  |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  0 |  0 |  0 | ADC |
 *  +----+----+----+   +----+----+----+----+----+----+----+-----+
 *
 *  When ADC = "L", the right rotates (normal direction). (POR)
 *  When ADC = "H", the left rotates (reverse direction).
 *
 * @param[in] send8 TODO
 * @param[in] segment_direction TODO
 */
void sh1106_set_segment_re_map(t_send8 send8, enum sh1106_segment_direction segment_direction);

/**
 * @brief TODO
 */
enum sh1106_display_state {
    /** The normal display status is provided. (POR) */
            SH1106_INTERNAL_ON,
    /** The entire display ON status is provided. */
            SH1106_INTERNAL_OFF,
    /**  Display OFF OLED. (POR) */
            SH1106_OLED_ON,
    /** Display ON OLED. */
            SH1106_OLED_OFF,
};

/**
 * @brief Set Entire Display OFF/ON: (A4H - A5H)
 *  Forcibly turns the entire display on regardless of the contents of the display data RAM. At this time, the
 *  contents of the display data RAM are held. This command has priority over the normal/reverse display command.
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  0 |  1 |  0 |  D |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  When D = "L", the normal display status is provided. (POR)
 *  When D = "H", the entire display ON status is provided.
 *
 * @brief Display OFF/ON: (AEH - AFH)
 *  Alternatively turns the display on and off.
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  1 |  1 |  1 |  D |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  When D = “L”, Display OFF OLED. (POR)
 *  When D = “H”, Display ON OLED.
 *
 *  When the display OFF command is executed, power saver mode will be entered.
 *
 *  Sleep mode:
 *      This mode stops every operation of the OLED display system, and can reduce current consumption nearly to a
 *      static current value if no access is made from the microprocessor. The internal status in the sleep mode is
 *      as follows:
 *          1) Stops the oscillator circuit and DC-DC circuit.
 *          2) Stops the OLED drive and outputs HZ as the segment/common driver output.
 *          3) Holds the display data and operation mode provided before the start of the sleep mode.
 *          4) The MPU can access to the built-in display RAM.
 *
 * @param[in] send8 TODO
 * @param[in] display_state TODO
 */
void sh1106_set_display_state(t_send8 send8, enum sh1106_display_state display_state);

enum sh1106_display_direction {
    /** The RAM data is high, being OLED ON potential (normal display). (POR) */
            SH1106_DISPLAY_NORMAL_DIRECTION,
    /** The RAM data is low, being OLED ON potential (reverse display). */
            SH1106_DISPLAY_REVERSE_DIRECTION,
};

/**
 * @brief Set Normal/Reverse Display: (A6H - A7H)
 *  Reverses the display ON/OFF status without rewriting the contents of the display data RAM.
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  0 |  1 |  1 |  D |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  When D = "L", the RAM data is high, being OLED ON potential (normal display). (POR)
 *  When D = "H", the RAM data is low, being OLED ON potential (reverse display).
 *
 * @param[in] send8 TODO
 * @param[in] display_direction TODO
 */
void sh1106_set_display_direction(t_send8 send8, enum sh1106_display_direction display_direction);

/**
 * @brief Set Multiplex Ration: (Double Bytes Command)
 *  This command switches default 64 multiplex modes to any multiplex ratio from 1 to 64. The output pads COM0-COM63
 *  will be switched to corresponding common signal.
 *
 *  Multiplex Ration Mode Set: (A8H)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  1 |  0 |  0 |  0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  Multiplex Ration Data Set: (00H - 3FH)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+-----------------+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | Multiplex Ratio |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+-----------------+
 *      |  0 |  1 |  0 |   |  * |  * |  0 |  0 |  0 |  0 |  0 |  0 |               1 |
 *      |  0 |  1 |  0 |   |  * |  * |  0 |  0 |  0 |  0 |  1 |  0 |               2 |
 *      |  0 |  1 |  0 |   |  * |  * |  0 |  0 |  0 |  0 |  1 |  1 |               3 |
 *      |  0 |  1 |  0 |   |                                                     ... |
 *      |  0 |  1 |  0 |   |  * |  * |  1 |  1 |  1 |  1 |  1 |  0 |              63 |
 *      |  0 |  1 |  0 |   |  * |  * |  1 |  1 |  1 |  1 |  1 |  1 |        64 (POR) |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+-----------------+
 *
 * @param[in] send8
 * @param[in] multiplex_ratio TODO
 */
void sh1106_set_multiplex_ration(t_send8 send8, uint8_t multiplex_ratio);

/**
 * @brief TODO
 */
enum sh1106_dc_dc_mode {
    /** DC-DC is disable. */
            SH1106_DC_DC_ENABLE,
    /** DC-DC will be turned on when display on. (POR) */
            SH1106_DC_DC_DISABLE,
};

/**
 * @brief Set DC-DC OFF/ON: (Double Bytes Command)
 *  This command is to control the DC-DC voltage converter. The converter will be turned on by issuing this command
 *  then display ON command. The panel display must be off while issuing this command.
 *
 *  DC-DC Control Mode Set: (ADH)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  1 |  1 |  0 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  DC-DC ON/OFF Mode Set: (8AH - 8BH)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  0 |  0 |  1 |  0 |  1 |  D |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *          When D = "L", DC-DC is disable.
 *          When D = "H", DC-DC will be turned on when display on. (POR)
 *
 *  +--------------+-----------------------+---------------------------+
 *  | DC-DC STATUS | DISPLAY ON/OFF STATUS |               Description |
 *  +--------------+-----------------------+---------------------------+
 *  |            0 |                     0 |                Sleep mode |
 *  +--------------+-----------------------+---------------------------+
 *  |            0 |                     1 | External VPP must be used |
 *  +--------------+-----------------------+---------------------------+
 *  |            1 |                     0 |                Sleep mode |
 *  +--------------+-----------------------+---------------------------+
 *  |            1 |                     1 |   Built-in DC-DC is used, |
 *  |              |                       |            Normal Display |
 *  +--------------+-----------------------+---------------------------+
 *
 *
 * @param[in] send8 TODO
 * @param[in] dc_dc_mode TODO
 */
void sh1106_set_dc_dc_mode(t_send8 send8, enum sh1106_dc_dc_mode dc_dc_mode);

/**
 * @brief Set Page Address: (B0H - B7H)
 *  Specifies page address to load display RAM data to page address register. Any RAM data bit can be accessed when
 *  its page address and column address are specified. The display remains unchanged even when the page address is
 *  changed.
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  0 |  1 |  0 |   |  1 |  0 |  1 |  1 | A3 | A2 | A1 | A0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  +----+----+----+----+--------------+
 *  | A3 | A2 | A1 | A0 | Page address |
 *  +----+----+----+----+--------------+
 *  |  0 |  0 |  0 |  0 |            0 |
 *  |  0 |  0 |  0 |  1 |            1 |
 *  |  0 |  0 |  1 |  0 |            2 |
 *  |  0 |  0 |  1 |  1 |            3 |
 *  |  0 |  1 |  0 |  0 |            4 |
 *  |  0 |  1 |  0 |  1 |            5 |
 *  |  0 |  1 |  1 |  0 |            6 |
 *  |  0 |  1 |  1 |  1 |            7 |
 *  +----+----+----+----+--------------+
 *
 * @param[in] send8 TODO
 * @param[in] page_addr TODO
 */
void sh1106_set_page_address(t_send8 send8, uint8_t page_addr);

/**
 * @brief TODO
 */
enum sh1106_common_output_scan_direction {
    /** Scan from COM0 to COM [N -1]. (POR) */
            SH1106_COMMON_OUTPUT_SCAN_NORMAL_DIRECTION,
    /** Scan from COM [N -1] to COM0. */
            SH1106_COMMON_OUTPUT_SCAM_VERTICALLY_FLIPPED,
};

/**
 * @brief Set Common Output Scan Direction: (C0H - C8H)
 *  This command sets the scan direction of the common output allowing layout flexibility in OLED module design. In
 *  addition, the display will have immediate effect once this command is issued. That is, if this command is sent
 *  during normal display, the graphic display will be vertically flipped.
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  0 |  1 |  0 |   |  1 |  1 |  0 |  0 |  D |  * |  * |  * |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  When D = "L", Scan from COM0 to COM [N -1]. (POR)
 *  When D = "H", Scan from COM [N -1] to COM0.
 *
 * @param[in] send8 TODO
 * @param[in] common_output_scan_direction TODO
 */
void sh1106_set_common_output_scan_direction(t_send8 send8,
                                             enum sh1106_common_output_scan_direction common_output_scan_direction);

/**
 * @brief Set Display Offset: (Double Bytes Command)
 *  This is a double byte command. The next command specifies the mapping of display start line to one of COM0-63
 *  (it is assumed that COM0 is the display start line, that equals to 0). For example, to move the COM16 towards
 *  the COM0 direction for 16 lines, the 6-bit data in the second byte should be given by 010000. To move in the
 *  opposite direction by 16 lines, the 6-bit data should be given by (64-16), so the second byte should be 100000.
 *
 *  Display Offset Mode Set: (D3H)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  1 |  0 |  1 |  0 |  0 |  1 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  Display Offset Data Set: (00H~3FH)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+---------+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |    COMx |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+---------+
 *      |  0 |  1 |  0 |   |  * |  * |  0 |  0 |  0 |  0 |  0 |  0 | 0 (POR) |
 *      |  0 |  1 |  0 |   |  * |  * |  0 |  0 |  0 |  0 |  1 |  0 |       1 |
 *      |  0 |  1 |  0 |   |  * |  * |  0 |  0 |  0 |  0 |  1 |  1 |       2 |
 *      |  0 |  1 |  0 |   |                                             ... |
 *      |  0 |  1 |  0 |   |  * |  * |  1 |  1 |  1 |  1 |  1 |  0 |      62 |
 *      |  0 |  1 |  0 |   |  * |  * |  1 |  1 |  1 |  1 |  1 |  1 |      63 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+---------+
 *
 * @param[in] send8 TODO
 * @param[in] display_offset TODO
 */
void sh1106_set_display_offset(t_send8 send8, uint8_t display_offset);

/**
 * @brief TODO
 */
enum sh1106_oscillator_frequency {
    /** Oscillator Frequency of ƒOSC -25% */
            SH1106_OSCILLATOR_FREQUENCY_MINUS_25_PERCENT,
    /** Oscillator Frequency of ƒOSC -20% */
            SH1106_OSCILLATOR_FREQUENCY_MINUS_20_PERCENT,
    /** Oscillator Frequency of ƒOSC -15% */
            SH1106_OSCILLATOR_FREQUENCY_MINUS_15_PERCENT,
    /** Oscillator Frequency of ƒOSC -10% */
            SH1106_OSCILLATOR_FREQUENCY_MINUS_10_PERCENT,
    /** Oscillator Frequency of ƒOSC -5% */
            SH1106_OSCILLATOR_FREQUENCY_MINUS_5_PERCENT,
    /** Oscillator Frequency of ƒOSC POR */
            SH1106_OSCILLATOR_FREQUENCY_POR,
    /** Oscillator Frequency of ƒOSC +5% */
            SH1106_OSCILLATOR_FREQUENCY_PLUS_5_PERCENT,
    /** Oscillator Frequency of ƒOSC +10% */
            SH1106_OSCILLATOR_FREQUENCY_PLUS_10_PERCENT,
    /** Oscillator Frequency of ƒOSC +15% */
            SH1106_OSCILLATOR_FREQUENCY_PLUS_15_PERCENT,
    /** Oscillator Frequency of ƒOSC +20% */
            SH1106_OSCILLATOR_FREQUENCY_PLUS_20_PERCENT,
    /** Oscillator Frequency of ƒOSC +25% */
            SH1106_OSCILLATOR_FREQUENCY_PLUS_25_PERCENT,
    /** Oscillator Frequency of ƒOSC +30% */
            SH1106_OSCILLATOR_FREQUENCY_PLUS_30_PERCENT,
    /** Oscillator Frequency of ƒOSC +35% */
            SH1106_OSCILLATOR_FREQUENCY_PLUS_35_PERCENT,
    /** Oscillator Frequency of ƒOSC +40% */
            SH1106_OSCILLATOR_FREQUENCY_PLUS_40_PERCENT,
    /** Oscillator Frequency of ƒOSC +45% */
            SH1106_OSCILLATOR_FREQUENCY_PLUS_45_PERCENT,
    /** Oscillator Frequency of ƒOSC +50% */
            SH1106_OSCILLATOR_FREQUENCY_PLUS_50_PERCENT,
};

/**
 * @brief Set Display Clock Divide Ratio/Oscillator Frequency: (Double Bytes Command)
 *  This command is used to set the frequency of the internal display clocks (DCLKs). It is defined as the divide
 *  ratio (Value from 1 to 16) used to divide the oscillator frequency. POR is 1. Frame frequency is determined by
 *  divide ratio, number of display clocks per row, MUX ratio and oscillator frequency.
 *
 *  Divide Ratio/Oscillator Frequency Mode Set: (D5H)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  1 |  0 |  1 |  0 |  1 |  0 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  Divide Ratio/Oscillator Frequency Data Set: (00H - 3FH)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   | A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *      A3 - A0 defines the divide ration of the display clocks (DCLK). Divide Ration = A[3:0]+1.
 *          +----+----+----+----+---------------+
 *          | A3 | A2 | A1 | A0 | Divide Ration |
 *          +----+----+----+----+---------------+
 *          |  0 |  0 |  0 |  0 |       1 (POR) |
 *          |                               ... |
 *          |  1 |  1 |  1 |  1 |            16 |
 *          +----+----+----+----+---------------+
 *
 *      A7 - A4 sets the oscillator frequency. Oscillator frequency increase with the value of A[7:4] and vice versa.
 *          +----+----+----+----+----------------------+
 *          |    |    |    |    | Oscillator Frequency |
 *          | A7 | A6 | A5 | A4 |              of ƒOSC |
 *          +----+----+----+----+----------------------+
 *          |  0 |  0 |  0 |  0 |                 -25% |
 *          |  0 |  0 |  0 |  1 |                 -20% |
 *          |  0 |  0 |  1 |  0 |                 -15% |
 *          |  0 |  0 |  1 |  1 |                 -10% |
 *          |  0 |  1 |  0 |  0 |                  -5% |
 *          |  0 |  1 |  0 |  1 |           ƒOSC (POR) |
 *          |  0 |  1 |  1 |  0 |                  +5% |
 *          |  0 |  1 |  1 |  1 |                 +10% |
 *          |  1 |  0 |  0 |  0 |                 +15% |
 *          |  1 |  0 |  0 |  1 |                 +20% |
 *          |  1 |  0 |  1 |  0 |                 +25% |
 *          |  1 |  0 |  1 |  1 |                 +30% |
 *          |  1 |  1 |  0 |  0 |                 +35% |
 *          |  1 |  1 |  0 |  1 |                 +40% |
 *          |  1 |  1 |  1 |  0 |                 +45% |
 *          |  1 |  1 |  1 |  1 |                 +50% |
 *          +----+----+----+----+----------------------+
 *
 *
 * @param[in] send8 TODO
 * @param[in] clock_divide_ration TODO
 * @param[in] oscillator_frequency TODO
 */
void sh1106_set_display_clock_divide_ratio_oscillator_frequency(t_send8 send8,
                                                                uint8_t clock_divide_ration,
                                                                enum sh1106_oscillator_frequency oscillator_frequency);

/**
 * @brief Set Dis-charge/Pre-charge Period: (Double Bytes Command)
 *  This command is used to set the duration of the pre-charge period. The interval is counted in number of DCLK.
 *  POR is 2 DCLKs.
 *
 *  Pre-charge Period Mode Set: (D9H)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  1 |  0 |  1 |  1 |  0 |  0 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  Dis-charge/Pre-charge Period Data Set: (00H - FFH)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   | A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *      Pre-charge Period Adjust: (A3 - A0)
 *          +----+----+----+----+-------------------+
 *          | A3 | A2 | A1 | A0 | Pre-charge Period |
 *          +----+----+----+----+-------------------+
 *          |  0 |  0 |  0 |  0 |           INVALID |
 *          |  0 |  0 |  0 |  1 |           1 DCLKs |
 *          |  0 |  0 |  1 |  0 |     2 DCLKs (POR) |
 *          |                                   ... |
 *          |  1 |  1 |  1 |  0 |          14 DCLKs |
 *          |  1 |  1 |  1 |  1 |          15 DCLKs |
 *          +----+----+----+----+-------------------+
 *
 *      Dis-charge Period Adjust: (A7 - A4)
 *          +----+----+----+----+-------------------+
 *          | A3 | A2 | A1 | A0 | Dis-charge Period |
 *          +----+----+----+----+-------------------+
 *          |  0 |  0 |  0 |  0 |           INVALID |
 *          |  0 |  0 |  0 |  1 |           1 DCLKs |
 *          |  0 |  0 |  1 |  0 |     2 DCLKs (POR) |
 *          |                                   ... |
 *          |  1 |  1 |  1 |  0 |          14 DCLKs |
 *          |  1 |  1 |  1 |  1 |          15 DCLKs |
 *          +----+----+----+----+-------------------+
 *
 * @param[in] send8 TODO
 * @param[in] pre_charge_period TODO
 * @param[in] dis_charge_period TODO
 */
void sh1106_set_dis_charge_pre_charge_period(t_send8 send8, uint8_t pre_charge_period, uint8_t dis_charge_period);

/**
 * @brief TODO
 */
enum sh1106_common_signals_pad_configuration {
    /** Sequential */
            SH1106_COMMON_SIGNALS_PAD_CONFIGURATION_SEQUENTIAL,
    /** Alternative. (POR) */
            SH1106_COMMON_SIGNALS_PAD_CONFIGURATION_ALTERNATIVE,
};

/**
 * @brief Set Common pads hardware configuration: (Double Bytes Command)
 *  This command is to set the common signals pad configuration (sequential or alternative) to match the OLED panel
 *  hardware layout.
 *
 *  Common Pads Hardware Configuration Mode Set: (DAH)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  1 |  0 |  1 |  1 |  0 |  1 |  0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  Sequential/Alternative Mode Set: (02H - 12H)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  0 |  0 |  0 |  D |  0 |  0 |  1 |  0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *      When D = "L", Sequential.
 *          +------------------+--------------------+--------------------+
 *          | COM31, 30 - 1, 0 | SEG0, 1 - 130, 131 | COM32, 33 - 62, 63 |
 *          +------------------+--------------------+--------------------+
 *
 *      When D = "H", Alternative. (POR)
 *          +------------------+--------------------+--------------------+
 *          | COM62, 60 - 2, 0 | SEG0, 1 - 130, 131 |   COM1, 3 - 61, 63 |
 *          +------------------+--------------------+--------------------+
 *
 * @param[in] send8 TODO
 * @param[in] common_signals_pad_configuration TODO
 */
void sh1106_set_common_pads_hardware_configuration(t_send8 send8,
                                                   enum sh1106_common_signals_pad_configuration common_signals_pad_configuration);

/**
 * @brief Set VCOM Deselect Level: (Double Bytes Command)
 *  This command is to set the common pad output voltage level at deselect stage.
 *
 *  VCOM Deselect Level Mode Set: (DBH)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  1 |  0 |  1 |  1 |  0 |  1 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  VCOM Deselect Level Data Set: (00H - FFH)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   | A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  VCOM = β X VREF = (0.430 + A[7:0] X 0.006415) X VREF
 *      +-----------+-------+-----------+-------------+
 *      |    A[7:0] |     β |    A[7:0] |           β |
 *      +-----------+-------+-----------+-------------+
 *      |       00H | 0.430 |       20H |             |
 *      |       01H |       |       21H |             |
 *      |       02H |       |       22H |             |
 *      |       03H |       |       23H |             |
 *      |       04H |       |       24H |             |
 *      |       05H |       |       25H |             |
 *      |       06H |       |       26H |             |
 *      |       07H |       |       27H |             |
 *      |       08H |       |       28H |             |
 *      |       09H |       |       29H |             |
 *      |       0AH |       |       2AH |             |
 *      |       0BH |       |       2BH |             |
 *      |       0CH |       |       2CH |             |
 *      |       0DH |       |       2DH |             |
 *      |       0EH |       |       2EH |             |
 *      |       0FH |       |       2FH |             |
 *      |       10H |       |       30H |             |
 *      |       11H |       |       31H |             |
 *      |       12H |       |       32H |             |
 *      |       13H |       |       33H |             |
 *      |       14H |       |       34H |             |
 *      |       15H |       |       35H | 0.770 (POR) |
 *      |       16H |       |       36H |             |
 *      |       17H |       |       37H |             |
 *      |       18H |       |       38H |             |
 *      |       19H |       |       39H |             |
 *      |       1AH |       |       3AH |             |
 *      |       1BH |       |       3BH |             |
 *      |       1CH |       |       3CH |             |
 *      |       1DH |       |       3DH |             |
 *      |       1EH |       |       3EH |             |
 *      |       1FH |       |       3FH |             |
 *      +-----------+-------+-----------+-------------+
 *      | 40H - FFH |     1 |           |             |
 *      +-----------+-------+-----------+-------------+
 *
 * @param[in] send8 TODO
 * @param[in] deselect_level TODO
 */
void sh1106_set_vcom_deselect_level(t_send8 send8, uint8_t deselect_level);

/**
 * @brief Read-Modify-Write: (E0H)
 *  A pair of Read-Modify-Write and End commands must always be used. Once read-modify-write is issued, column address
 *  is not incremental by read display data command but incremental by write display data command only. It continues
 *  until End command is issued. When the End is issued, column address returns to the address when read-modify-write is
 *  issued. This can reduce the microprocessor load when data of a specific display area is repeatedly changed during
 *  cursor blinking or others.
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  0 |  1 |  0 |   |  1 |  1 |  1 |  0 |  0 |  0 |  0 |  0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *  Cursor display sequence:
 *
 *            +----------+----------+
 *            |    Set Page Address |
 *            +----------+----------+
 *                       |
 *            +----------+----------+
 *            |  Set Column Address |
 *            +----------+----------+
 *                       |
 *                       +<---------------+
 *                       |                |
 *            +----------+----------+     |
 *            |   Read-Modify-Write |     |
 *            +----------+----------+     |
 *                       |                |
 *      +--------------->+                |
 *      |                |                |
 *      |     +----------+----------+     |
 *      |     |          Dummy Read |     |
 *      |     +----------+----------+     |
 *      |                |                |
 *      |     +----------+----------+     |
 *      No    |           Read Data |     |     ---->+
 *      |     +----------+----------+     |          |
 *      |                |                |     Data process
 *      |     +----------+----------+     |          |
 *      |     |          Write Data |     |     <----+
 *      |     +----------+----------+     |
 *      |                |                |
 *      |     +----------+----------+     |
 *      +<----+          Completed? |     |
 *            +----------+----------+     |
 *                       |                |
 *                       Yes              |
 *                       |                |
 *            +----------+----------+     |
 *            |                 End |     |
 *            +----------+----------+     |
 *                       |                |
 *                       +--------------->+
 *                       |
 *
 * @param[in] send8 TODO
 */
void sh1106_read_modify_write(t_send8 send8);

/**
 * @brief End: (EEH)
 *  Cancels Read-Modify-Write mode and returns column address to the original address (when Read-Modify-Write is issued)
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  0 |  1 |  0 |   |  1 |  1 |  1 |  0 |  1 |  1 |  1 |  0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *                            +----->----->----->----->----->----->----->--+ Return
 *                            |                                            |
 *                 -----x  x--+--x  x-----x  x-----x  x-----x  x- ---x  x--+--x  x-----x  x-----
 *  Column address       X    N   X   N+1  X   N+2  X   N+3  X   N+m  X    N   X        X
 *                 -----x| x-----x  x-----x  x-----x  x-----x  x- ---x  x-----x| x-----x  x-----
 *                       |                                                     |
 *                       +----- Read-Modify-Write                              +----- End
 *                              mode is selected
 * @param[in] send8 TODO
 */
void sh1106_end(t_send8 send8);

/**
 * @brief NOP: (E3H)
 *  Non-Operation Command.
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  0 |  1 |  0 |   |  1 |  1 |  1 |  0 |  0 |  0 |  1 |  1 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *
 * @param[in] send8 TODO
 */
void sh1106_nop(t_send8 send8);

/**
 * @brief Write Display Data
 *  Write 8-bit data in display RAM. As the column address is incremental by 1 automatically after each write, the
 *  microprocessor can continue to write data of multiple words.
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  1 |  1 |  0 |   |                        Write RAM data |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 * @param[in] send8 TODO
 * @param[in] data TODO
 */
void sh1106_write_display_data(t_send8 send8, uint8_t data);

/**
 * @brief Read Status
 *
 *  +----+----+----+   +------+--------+----+----+----+----+----+----+
 *  | A0 | RD | WR |   |   D7 |     D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +------+--------+----+----+----+----+----+----+
 *  |  0 |  0 |  1 |   | BUSY | ON/OFF |  * |  * |  * |  0 |  0 |  0 |
 *  +----+----+----+   +------+--------+----+----+----+----+----+----+
 *
 *  BUSY:   When high, the SH1106 is busy due to internal operation or reset. Any command is rejected until BUSY goes
 *          low. The busy check is not required if enough time is provided for each cycle.
 *
 *  ON/OFF: Indicates whether the display is on or off. When goes low the display turns on. When goes high, the display
 *          turns off. This is the opposite of Display ON/OFF command.
 */
// TODO

/**
 * @brief Read Display Data
 *  Reads 8-bit data from display RAM area specified by column address and page address. As the column address is
 *  increment by 1 automatically after each write, the microprocessor can continue to read data of multiple words. A
 *  single dummy read is required immediately after column address being setup. Refer to the display RAM section of
 *  FUNCTIONAL DESCRIPTION for details. Note that no display data can be read via the serial interface.
 *
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  1 |  0 |  1 |   |                         Read RAM data |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 */
// TODO

/**
 * @brief TODO
 *
 * @param[in] send8 TODO
 */
void sh1106_init(t_send8 send8);

#endif // YET_ANOTHER_GAUGE__SH1106_H
