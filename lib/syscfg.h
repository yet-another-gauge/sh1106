/*
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
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef YET_ANOTHER_GAUGE__SH1106__SYSCFG_H
#define YET_ANOTHER_GAUGE__SH1106__SYSCFG_H

/**
 * @def SH1106_SET_LOWER_COLUMN_ADDRESS(addr)
 *
 * Specifies lower column address of display RAM. Divide the column address into 4 higher bits and 4 lower bits.
 * Set each of them into successions. When the microprocessor repeats to access to the display RAM, the column address
 * counter is incremented during each access until address 132 is accessed. The page address is not changed during this
 * time.
 *
 * +----+----+----+----+----+----+----+----+----------------+
 * | A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 | Column address |
 * +----+----+----+----+----+----+----+----+----------------+
 * |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |              0 |
 * |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  1 |              1 |
 * |                                                    ... |
 * |  1 |  0 |  0 |  0 |  0 |  0 |  1 |  1 |            131 |
 * +----+----+----+----+----+----+----+----+----------------+
 *
 * Set lower column address: 0x00 - 0x0F
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  0 |  0 |  0 |  0 | A3 | A2 | A1 | A0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_SET_LOWER_COLUMN_ADDRESS(addr) (0x0F & (addr))

/**
 * @def SH1106_SET_HIGHER_COLUMN_ADDRESS(addr)
 *
 * Specifies higher column address of display RAM. Divide the column address into 4 higher bits and 4 lower bits.
 * Set each of them into successions. When the microprocessor repeats to access to the display RAM, the column address
 * counter is incremented during each access until address 132 is accessed. The page address is not changed during this
 * time.
 *
 * +----+----+----+----+----+----+----+----+----------------+
 * | A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 | Column address |
 * +----+----+----+----+----+----+----+----+----------------+
 * |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |              0 |
 * |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  1 |              1 |
 * |                                                    ... |
 * |  1 |  0 |  0 |  0 |  0 |  0 |  1 |  1 |            131 |
 * +----+----+----+----+----+----+----+----+----------------+
 *
 * Set higher column address: 0x10 - 0x0F
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  0 |  0 |  0 |  1 | A7 | A6 | A5 | A4 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_SET_HIGHER_COLUMN_ADDRESS(addr) (0x10 | ((addr) >> 4))

/**
 * @def SH1106_SET_PUMP_VOLTAGE_X_Y
 *
 * Specifies output voltage (Vpp) of the internal charger pump.
 *
 * Set pump voltage value: 0x30 - 0x33
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  0 |  0 |  1 |  1 |  0 |  0 | A1 | A0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *      +----+----+---------------------------+
 *      | A1 | A0 | Pump output voltage (Vpp) |
 *      +----+----+---------------------------+
 *      |  0 |  0 |            7.4 (Power on) |
 *      |  0 |  1 |                       8.0 |
 *      |  1 |  0 |                       8.4 |
 *      |  1 |  1 |                       9.0 |
 *      +----+----+---------------------------+
 */
#define SH1106_SET_PUMP_VOLTAGE_7_4 0x30
#define SH1106_SET_PUMP_VOLTAGE_8_0 0x31
#define SH1106_SET_PUMP_VOLTAGE_8_4 0x32
#define SH1106_SET_PUMP_VOLTAGE_9_0 0x33

/**
 * @def SH1106_SET_DISPLAY_START_LINE(addr)
 *
 * Specifies line address to determine the initial display line or COM0. The RAM display data becomes the top line of
 * OLED screen. It is followed by the higher number of lines in ascending order, corresponding to the duty cycle. When
 * this command changes the line address, the smooth scrolling or page change takes place.
 *
 * Set display start line: 0x40 - 0x7F
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  0 |  1 | A5 | A4 | A3 | A2 | A1 | A0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *      +----+----+----+----+----+----+--------------+
 *      | A5 | A4 | A3 | A2 | A1 | A0 | Line address |
 *      +----+----+----+----+----+----+--------------+
 *      |  0 |  0 |  0 |  0 |  0 |  0 |            0 |
 *      |  0 |  0 |  0 |  0 |  0 |  1 |            1 |
 *      |                                        ... |
 *      |  1 |  1 |  1 |  1 |  1 |  0 |           62 |
 *      |  1 |  1 |  1 |  1 |  1 |  1 |           63 |
 *      +----+----+----+----+----+----+--------------+
 */
#define SH1106_SET_DISPLAY_START_LINE(addr) (0x40 | (0x3F & (addr)))

/**
 * @def SH1106_CONTRAST_CONTROL_MODE_SET
 *
 * This command is to set contrast setting of the display. The chip has 256 contrast steps from 0x00 to 0xFF. The
 * segment output current increases as the contrast step value increases. Segment output current setting:
 *      ISEG = α / 256 * IREF * scale factor
 * Where:
 *      α is contrast step;
 *      IREF is reference current equals 10μA;
 *      Scale factor = 32.
 *
 * Contrast control mode set: 0x81
 *      When this command is input, the contrast data register set command becomes enabled. Once the contrast control
 *      mode has been set, no other command except for the contrast data register command can be used. Once the contrast
 *      data set command has been used to set data into the register, then the contrast control mode is released.
 *
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  0 |  0 |  0 |  0 |  0 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_CONTRAST_CONTROL_MODE_SET 0x81

/**
 * @def SH1106_CONTRAST_DATA_REGISTER_SET(iseg)
 *
 * This command is to set contrast setting of the display. The chip has 256 contrast steps from 0x00 to 0xFF. The
 * segment output current increases as the contrast step value increases. Segment output current setting:
 *      ISEG = α / 256 * IREF * scale factor
 * Where:
 *      α is contrast step;
 *      IREF is reference current equals 10μA;
 *      Scale factor = 32.
 *
 * Contrast data register set: 0x00 - 0xFF
 *      By using this command to set eight bits of data to the contrast data register; the OLED segment output assumes
 *      one of the 256 current levels. When this command is input, the contrast control mode is released after the
 *      contrast data register has been set.
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
 * When the contrast control function is not used, set the D7 - D0 to 0b10000000.
 */
#define SH1106_CONTRAST_DATA_REGISTER_SET(iseg) (0xFF & (iseg))

/**
 * @def SH1106_SET_SEGMENT_RE_MAP_NORMAL_DIRECTION
 *
 * Change the relationship between RAM column address and segment driver. The order of segment driver output pads can
 * be reversed by software. This allows flexible IC layout during OLED module assembly. When display data is written or
 * read, the column address is incremented by 1.
 *
 * Set segment re-map normal direction: 0xA0 (POR)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  0 |  0 |  0 |  0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_SET_SEGMENT_RE_MAP_NORMAL_DIRECTION 0xA0

/**
 * @def SH1106_SET_SEGMENT_RE_MAP_REVERSE_DIRECTION
 *
 * Change the relationship between RAM column address and segment driver. The order of segment driver output pads can
 * be reversed by software. This allows flexible IC layout during OLED module assembly. When display data is written or
 * read, the column address is incremented by 1.
 *
 * Set segment re-map reverse direction: 0xA1
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  0 |  0 |  0 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_SET_SEGMENT_RE_MAP_REVERSE_DIRECTION 0xA1

/**
 * @def SH1106_SET_ENTIRE_DISPLAY_OFF
 *
 * Forcibly turns the entire display on regardless of the contents of the display data RAM. At this time, the contents
 * of the display data RAM are held. This command has priority over the normal/reverse display command.
 *
 * Set entire display off: 0xA4 (POR)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  0 |  1 |  0 |  0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_SET_ENTIRE_DISPLAY_OFF 0xA4

/**
 * @def SH1106_SET_ENTIRE_DISPLAY_ON
 *
 * Forcibly turns the entire display on regardless of the contents of the display data RAM. At this time, the contents
 * of the display data RAM are held. This command has priority over the normal/reverse display command.
 *
 * Set entire display on status: 0xA5
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  0 |  1 |  0 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_SET_ENTIRE_DISPLAY_ON 0xA5

/**
 * @def SH1106_DISPLAY_OFF_OLED
 *
 * Alternatively turns the display off: 0xAE (POR)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  1 |  1 |  1 |  0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 * When the display OFF command is executed, power saver mode will be entered.
 *
 * Sleep mode:
 *      This mode stops every operation of the OLED display system, and can reduce current consumption nearly to a
 *      static current value if no access is made from the microprocessor. The internal status in the sleep mode is
 *      as follows:
 *          1) Stops the oscillator circuit and DC-DC circuit.
 *          2) Stops the OLED drive and outputs HZ as the segment/common driver output.
 *          3) Holds the display data and operation mode provided before the start of the sleep mode.
 *          4) The MPU can access to the built-in display RAM.
 */
#define SH1106_DISPLAY_OFF_OLED 0xAE

/**
 * @def SH1106_DISPLAY_ON_OLED
 *
 * Alternatively turns the display on: 0xAF
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  1 |  1 |  1 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_DISPLAY_ON_OLED 0xAF

/**
 * @def SH1106_SET_NORMAL_DISPLAY
 *
 * Reverses the display ON/OFF status without rewriting the contents of the display data RAM.
 *
 * Set normal display: 0xA6
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  0 |  1 |  1 |  0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_SET_NORMAL_DISPLAY_DIRECTION 0xA6

/**
 * @def SH1106_SET_REVERSE_DISPLAY
 *
 * Reverses the display ON/OFF status without rewriting the contents of the display data RAM.
 *
 * Set reverse display: 0xA7
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  0 |  1 |  1 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_SET_REVERSE_DISPLAY_DIRECTION 0xA7

/**
 * @def SH1106_MULTIPLE_RATION_MODE_SET
 *
 * This command switches default 64 multiplex modes to any multiplex ratio from 1 to 64. The output pads COM0-COM63
 * will be switched to corresponding common signal.
 *
 * Multiplex ration mode set: 0xA8
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  1 |  0 |  0 |  0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_MULTIPLE_RATION_MODE_SET 0xA8

/**
 * @def SH1106_MULTIPLEX_RATION_DATA_SET(ratio)
 *
 * This command switches default 64 multiplex modes to any multiplex ratio from 1 to 64. The output pads COM0-COM63
 * will be switched to corresponding common signal.
 *
 * Multiplex ration data set: 0x00 - 0x3FH
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
 *      Note: "*" stands for "Don't care"
 */
#define SH1106_MULTIPLEX_RATION_DATA_SET(ratio) (0x3F & (ratio))

/**
 * @def SH1106_DC_DC_CONTROL_MODE_SET
 *
 * This command is to control the DC-DC voltage converter. The converter will be turned on by issuing this command
 * then display ON command. The panel display must be off while issuing this command.
 *
 * DC-DC control mode set: 0xAD
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  0 |  1 |  1 |  0 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_DC_DC_CONTROL_MODE_SET 0xAD

/**
 * @def SH1106_DC_DC_OFF_MODE_SET
 *
 * +--------------+-----------------------+---------------------------+
 * | DC-DC STATUS | DISPLAY ON/OFF STATUS |               Description |
 * +--------------+-----------------------+---------------------------+
 * |            0 |                     0 |                Sleep mode |
 * +--------------+-----------------------+---------------------------+
 * |            0 |                     1 | External VPP must be used |
 * +--------------+-----------------------+---------------------------+
 * |            1 |                     0 |                Sleep mode |
 * +--------------+-----------------------+---------------------------+
 * |            1 |                     1 |   Built-in DC-DC is used, |
 * |              |                       |            Normal Display |
 * +--------------+-----------------------+---------------------------+
 *
 * DC-DC is disable: 0x8A
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  0 |  0 |  1 |  0 |  1 |  0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_DC_DC_OFF_MODE_SET 0x8A

/**
 * @def SH1106_DC_DC_ON_MODE_SET
 *
 * +--------------+-----------------------+---------------------------+
 * | DC-DC STATUS | DISPLAY ON/OFF STATUS |               Description |
 * +--------------+-----------------------+---------------------------+
 * |            0 |                     0 |                Sleep mode |
 * +--------------+-----------------------+---------------------------+
 * |            0 |                     1 | External VPP must be used |
 * +--------------+-----------------------+---------------------------+
 * |            1 |                     0 |                Sleep mode |
 * +--------------+-----------------------+---------------------------+
 * |            1 |                     1 |   Built-in DC-DC is used, |
 * |              |                       |            Normal Display |
 * +--------------+-----------------------+---------------------------+
 *
 * DC-DC will be turned on when display on: 0x8B (POR)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  0 |  0 |  1 |  0 |  1 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_DC_DC_ON_MODE_SET 0x8B

/**
 * @def SH1106_SET_PAGE_ADDRESS(addr)
 *
 * Specifies page address to load display RAM data to page address register. Any RAM data bit can be accessed when its
 * page address and column address are specified. The display remains unchanged even when the page address is changed.
 *
 * Set Page Address: 0xB0 - 0xB7
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  0 |  1 |  1 | A3 | A2 | A1 | A0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *      +----+----+----+----+--------------+
 *      | A3 | A2 | A1 | A0 | Page address |
 *      +----+----+----+----+--------------+
 *      |  0 |  0 |  0 |  0 |            0 |
 *      |  0 |  0 |  0 |  1 |            1 |
 *      |  0 |  0 |  1 |  0 |            2 |
 *      |  0 |  0 |  1 |  1 |            3 |
 *      |  0 |  1 |  0 |  0 |            4 |
 *      |  0 |  1 |  0 |  1 |            5 |
 *      |  0 |  1 |  1 |  0 |            6 |
 *      |  0 |  1 |  1 |  1 |            7 |
 *      +----+----+----+----+--------------+
 */
#define SH1106_SET_PAGE_ADDRESS(addr) (0xB0 | (0x0F & (addr)))

/**
 * @def SH1106_SET_COMMON_OUTPUT_SCAN_DIRECTION_FROM_COM0_TO_COMN
 *
 * This command sets the scan direction of the common output allowing layout flexibility in OLED module design. In
 * addition, the display will have immediate effect once this command is issued. That is, if this command is sent
 * during normal display, the graphic display will be vertically flipped.
 *
 * Set Common Output Scan Direction from COM0 to COM[N-1]: 0xC0 (POR)
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  1 |  0 |  0 |  0 |  * |  * |  * |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *      Note: "*" stands for "Don't care"
 */
#define SH1106_SET_COMMON_OUTPUT_SCAN_DIRECTION_FROM_COM0_TO_COMN 0xC0

/**
 * @def SH1106_SET_COMMON_OUTPUT_SCAN_DIRECTION_FROM_COMN_TO_COM0
 *
 * This command sets the scan direction of the common output allowing layout flexibility in OLED module design. In
 * addition, the display will have immediate effect once this command is issued. That is, if this command is sent
 * during normal display, the graphic display will be vertically flipped.
 *
 * Set Common Output Scan Direction from COM[N-1] to COM0: 0xC8
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  1 |  0 |  0 |  1 |  * |  * |  * |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *      Note: "*" stands for "Don't care"
 */
#define SH1106_SET_COMMON_OUTPUT_SCAN_DIRECTION_FROM_COMN_TO_COM0 0xC8

/**
 * @def SH1106_DISPLAY_OFFSET_MODE_SET
 *
 * This is a double byte command. The next command specifies the mapping of display start line to one of COM0-63
 * (it is assumed that COM0 is the display start line, that equals to 0). For example, to move the COM16 towards
 * the COM0 direction for 16 lines, the 6-bit data in the second byte should be given by 0b010000. To move in the
 * opposite direction by 16 lines, the 6-bit data should be given by (64-16), so the second byte should be 0b100000.
 *
 * Display Offset Mode Set: 0xD3
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  1 |  0 |  1 |  0 |  0 |  1 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_DISPLAY_OFFSET_MODE_SET 0xD3

/**
 * @def SH1106_DISPLAY_OFFSET_DATA_SET
 *
 * This is a double byte command. The next command specifies the mapping of display start line to one of COM0-63
 * (it is assumed that COM0 is the display start line, that equals to 0). For example, to move the COM16 towards
 * the COM0 direction for 16 lines, the 6-bit data in the second byte should be given by 0b010000. To move in the
 * opposite direction by 16 lines, the 6-bit data should be given by (64-16), so the second byte should be 0b100000.
 *
 * Display Offset Data Set: 0x3F
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
 *      Note: "*" stands for "Don't care"
 */
#define SH1106_DISPLAY_OFFSET_DATA_SET(offset) (0x3F & (offset))

/**
 * @def SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_MODE_SET
 *
 * This command is used to set the frequency of the internal display clocks (DCLKs). It is defined as the divide ratio
 * (value from 1 to 16) used to divide the oscillator frequency. POR is 1. Frame frequency is determined by divide
 * ratio, number of display clocks per row, MUX ratio and oscillator frequency.
 *
 * Divide Ratio/Oscillator Frequency Mode Set: 0xD5
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  1 |  0 |  1 |  0 |  1 |  0 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_MODE_SET 0xD5

/**
 * @def SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(ratio, freq)
 *
 * This command is used to set the frequency of the internal display clocks (DCLKs). It is defined as the divide ratio
 * (value from 1 to 16) used to divide the oscillator frequency. POR is 1. Frame frequency is determined by divide
 * ratio, number of display clocks per row, MUX ratio and oscillator frequency.
 *
 * Divide Ratio/Oscillator Frequency Data Set: 0x00 - 0x3F
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   | A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 * A3 - A0 defines the divide ration of the display clocks (DCLK).
 * Divide Ration = A[3:0] + 1.
 *      +----+----+----+----+---------------+
 *      | A3 | A2 | A1 | A0 | Divide Ration |
 *      +----+----+----+----+---------------+
 *      |  0 |  0 |  0 |  0 |       1 (POR) |
 *      |                               ... |
 *      |  1 |  1 |  1 |  1 |            16 |
 *      +----+----+----+----+---------------+
 *
 * A7 - A4 sets the oscillator frequency.
 * Oscillator frequency increase with the value of A[7:4] and vice versa.
 *      +----+----+----+----+----------------------+
 *      |    |    |    |    | Oscillator Frequency |
 *      | A7 | A6 | A5 | A4 |              of ƒOSC |
 *      +----+----+----+----+----------------------+
 *      |  0 |  0 |  0 |  0 |                 -25% |
 *      |  0 |  0 |  0 |  1 |                 -20% |
 *      |  0 |  0 |  1 |  0 |                 -15% |
 *      |  0 |  0 |  1 |  1 |                 -10% |
 *      |  0 |  1 |  0 |  0 |                  -5% |
 *      |  0 |  1 |  0 |  1 |           ƒOSC (POR) |
 *      |  0 |  1 |  1 |  0 |                  +5% |
 *      |  0 |  1 |  1 |  1 |                 +10% |
 *      |  1 |  0 |  0 |  0 |                 +15% |
 *      |  1 |  0 |  0 |  1 |                 +20% |
 *      |  1 |  0 |  1 |  0 |                 +25% |
 *      |  1 |  0 |  1 |  1 |                 +30% |
 *      |  1 |  1 |  0 |  0 |                 +35% |
 *      |  1 |  1 |  0 |  1 |                 +40% |
 *      |  1 |  1 |  1 |  0 |                 +45% |
 *      |  1 |  1 |  1 |  1 |                 +50% |
 *      +----+----+----+----+----------------------+
 */
#define SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(ratio, freq) ((0xF0 & ((freq) << 4)) | (0x0F & ((ratio) - 1)))

/**
 * @def SH1106_PRE_CHARGE_PERIOD_MODE_SET
 *
 * Set dis-charge/pre-charge period (double bytes command). This command is used to set the duration of the pre-charge
 * period. The interval is counted in number of DCLK. POR is 2 DCLKs.
 *
 *  Pre-charge period mode set: 0xD9
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  1 |  0 |  1 |  1 |  0 |  0 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_PRE_CHARGE_PERIOD_MODE_SET 0xD9

/**
 * @def SH1106_DIS_CHARGE_PRE_CHARGE_PERIOD_DATA_SET(pre, dis)
 *
 * Set dis-charge/pre-charge period (double bytes command). This command is used to set the duration of the pre-charge
 * period. The interval is counted in number of DCLK. POR is 2 DCLKs.
 *
 * Dis-charge/Pre-charge period data set: 0x00 - 0xFF
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   | A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *      Pre-charge period adjust: 0xA3 - 0xA0
 *          +----+----+----+----+-------------------+
 *          | A3 | A2 | A1 | A0 | Pre-charge period |
 *          +----+----+----+----+-------------------+
 *          |  0 |  0 |  0 |  0 |           INVALID |
 *          |  0 |  0 |  0 |  1 |           1 DCLKs |
 *          |  0 |  0 |  1 |  0 |     2 DCLKs (POR) |
 *          |                                   ... |
 *          |  1 |  1 |  1 |  0 |          14 DCLKs |
 *          |  1 |  1 |  1 |  1 |          15 DCLKs |
 *          +----+----+----+----+-------------------+
 *
 *      Dis-charge period adjust: 0xA7 - 0xA4
 *          +----+----+----+----+-------------------+
 *          | A3 | A2 | A1 | A0 | Dis-charge period |
 *          +----+----+----+----+-------------------+
 *          |  0 |  0 |  0 |  0 |           INVALID |
 *          |  0 |  0 |  0 |  1 |           1 DCLKs |
 *          |  0 |  0 |  1 |  0 |     2 DCLKs (POR) |
 *          |                                   ... |
 *          |  1 |  1 |  1 |  0 |          14 DCLKs |
 *          |  1 |  1 |  1 |  1 |          15 DCLKs |
 *          +----+----+----+----+-------------------+
 */
#define SH1106_DIS_CHARGE_PRE_CHARGE_PERIOD_DATA_SET(pre, dis) ((0xF0 & ((dis) << 4)) | (0x0F & (pre)))

/**
 * @def SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_MODE_SET
 *
 * Set common pads hardware configuration (double bytes command). This command is to set the common signals pad
 * configuration (sequential or alternative) to match the OLED panel hardware layout.
 *
 * Common Pads Hardware Configuration Mode Set: 0xDA
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  1 |  0 |  1 |  1 |  0 |  1 |  0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_MODE_SET 0xDA

/**
 * @def SH1106_SEQUENTIAL_MODE_SET
 *
 * Set common pads hardware configuration (double bytes command). This command is to set the common signals pad
 * configuration (sequential or alternative) to match the OLED panel hardware layout.
 *
 * +----------------+------------------+------------------+
 * | COM31,30 - 1,0 | SEG0,1 - 130,131 | COM32,33 - 62,63 |
 * +----------------+------------------+------------------+
 *
 * Sequential Mode Set: 0x02
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  0 |  0 |  0 |  0 |  0 |  0 |  1 |  0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_SEQUENTIAL_MODE_SET 0x02

/**
 * @def SH1106_ALTERNATIVE_MODE_SET
 *
 * Set common pads hardware configuration (double bytes command). This command is to set the common signals pad
 * configuration (sequential or alternative) to match the OLED panel hardware layout.
 *
 * +----------------+------------------+------------------+
 * | COM62,60 - 2,0 | SEG0,1 - 130,131 |   COM1,3 - 61,63 |
 * +----------------+------------------+------------------+
 *
 * Alternative Mode Set: 0x12
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 *  |  0 |  1 |  0 |   |  0 |  0 |  0 |  1 |  0 |  0 |  1 |  0 |
 *  +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_ALTERNATIVE_MODE_SET 0x12

/**
 * @def SH1106_VCOM_DESELECT_LEVEL_MODE_SET
 *
 * This command is to set the common pad output voltage level at deselect stage.
 *
 * VCOM = β X VREF = (0.430 + A[7:0] X 0.006415) X VREF
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
 * VCOM Deselect Level Mode Set: 0xDB
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   |  1 |  1 |  0 |  1 |  1 |  0 |  1 |  1 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_VCOM_DESELECT_LEVEL_MODE_SET 0xDB

/**
 * @def SH1106_VCOM_DESELECT_LEVEL_DATA_SET(data)
 *
 * This command is to set the common pad output voltage level at deselect stage.
 *
 * VCOM = β X VREF = (0.430 + A[7:0] X 0.006415) X VREF
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
 * VCOM Deselect Level Data Set: 0x00 - 0xFF
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 *      |  0 |  1 |  0 |   | A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 |
 *      +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_VCOM_DESELECT_LEVEL_DATA_SET(data) (0xFF & (data))

/**
 * @def SH1106_READ_MODIFY_WRITE
 *
 * A pair of Read-Modify-Write and End commands must always be used. Once read-modify-write is issued, column address
 * is not incremental by read display data command but incremental by write display data command only. It continues
 * until End command is issued. When the End is issued, column address returns to the address when read-modify-write is
 * issued. This can reduce the microprocessor load when data of a specific display area is repeatedly changed during
 * cursor blinking or others.
 *
 * +----+----+----+   +----+----+----+----+----+----+----+----+
 * | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 * +----+----+----+   +----+----+----+----+----+----+----+----+
 * |  0 |  1 |  0 |   |  1 |  1 |  1 |  0 |  0 |  0 |  0 |  0 |
 * +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 * Cursor display sequence:
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
 */
#define SH1106_READ_MODIFY_WRITE 0xE0

/**
 * @def SH1106_END
 *
 * Cancels Read-Modify-Write mode and returns column address to the original address (when Read-Modify-Write is issued)
 *
 * +----+----+----+   +----+----+----+----+----+----+----+----+
 * | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 * +----+----+----+   +----+----+----+----+----+----+----+----+
 * |  0 |  1 |  0 |   |  1 |  1 |  1 |  0 |  1 |  1 |  1 |  0 |
 * +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 *                           +----->----->----->----->----->----->----->--+ Return
 *                           |                                            |
 *                -----x  x--+--x  x-----x  x-----x  x-----x  x- ---x  x--+--x  x-----x  x-----
 * Column address       X    N   X   N+1  X   N+2  X   N+3  X   N+m  X    N   X        X
 *                -----x| x-----x  x-----x  x-----x  x-----x  x- ---x  x-----x| x-----x  x-----
 *                      |                                                     |
 *                      +----- Read-Modify-Write                              +----- End
 *                             mode is selected
 */
#define SH1106_END 0xEE

/**
 * @def SH1106_NOP
 *
 * Non-Operation Command.
 *
 * +----+----+----+   +----+----+----+----+----+----+----+----+
 * | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 * +----+----+----+   +----+----+----+----+----+----+----+----+
 * |  0 |  1 |  0 |   |  1 |  1 |  1 |  0 |  0 |  0 |  1 |  1 |
 * +----+----+----+   +----+----+----+----+----+----+----+----+
 *
 * @param[in] send8 TODO
 */
#define SH1106_NOP 0xE3

/**
 * @def SH1106_WRITE_DISPLAY_DATA(data)
 *
 * Write 8-bit data in display RAM. As the column address is incremental by 1 automatically after each write, the
 * microprocessor can continue to write data of multiple words.
 *
 * +----+----+----+   +----+----+----+----+----+----+----+----+
 * | A0 | RD | WR |   | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 * +----+----+----+   +----+----+----+----+----+----+----+----+
 * |  1 |  1 |  0 |   |                        Write RAM data |
 * +----+----+----+   +----+----+----+----+----+----+----+----+
 */
#define SH1106_WRITE_DISPLAY_DATA(data) (0xFF & (data))

#endif // YET_ANOTHER_GAUGE__SH1106__SYSCFG_H
