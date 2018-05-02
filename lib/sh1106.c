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
 * along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "sh1106.h"
#include "syscfg.h"

void sh1106_set_column_address(t_send8 send8, uint8_t addr) {
  (*send8)(SH1106_SET_LOWER_COLUMN_ADDRESS(addr));
  (*send8)(SH1106_SET_HIGHER_COLUMN_ADDRESS(addr));
}

void sh1106_set_pump_voltage(t_send8 send8, enum sh1106_pump_voltage pump_voltage) {
  switch (pump_voltage) {
    case SH1106_PUMP_VOLTAGE_7_4: {
      (*send8)(SH1106_SET_PUMP_VOLTAGE_7_4);
      break;
    }
    case SH1106_PUMP_VOLTAGE_8_0: {
      (*send8)(SH1106_SET_PUMP_VOLTAGE_8_0);
      break;
    }
    case SH1106_PUMP_VOLTAGE_8_4: {
      (*send8)(SH1106_SET_PUMP_VOLTAGE_8_4);
      break;
    }
    case SH1106_PUMP_VOLTAGE_9_0: {
      (*send8)(SH1106_SET_PUMP_VOLTAGE_9_0);
      break;
    }
  }
}

void sh1106_set_display_start_line(t_send8 send8, uint8_t addr) {
  (*send8)(SH1106_SET_DISPLAY_START_LINE(addr));
}

void sh1106_set_contrast_control_register(t_send8 send8, uint8_t contrast) {
  (*send8)(SH1106_CONTRAST_CONTROL_MODE_SET);
  (*send8)(SH1106_CONTRAST_DATA_REGISTER_SET(contrast));
}

void sh1106_set_segment_re_map(t_send8 send8, enum sh1106_segment_re_map_direction segment_re_map_direction) {
  switch (segment_re_map_direction) {
    case SH1106_SEGMENT_RE_MAP_NORMAL_DIRECTION: {
      (*send8)(SH1106_SET_SEGMENT_RE_MAP_NORMAL_DIRECTION);
      break;
    }
    case SH1106_SEGMENT_RE_MAP_REVERSE_DIRECTION: {
      (*send8)(SH1106_SET_SEGMENT_RE_MAP_REVERSE_DIRECTION);
      break;
    }
  }
}

void sh1106_set_display_state(t_send8 send8, enum sh1106_display_state display_state) {
  switch (display_state) {
    case SH1106_INTERNAL_ON: {
      (*send8)(SH1106_SET_ENTIRE_DISPLAY_ON);
      break;
    }
    case SH1106_INTERNAL_OFF: {
      (*send8)(SH1106_SET_ENTIRE_DISPLAY_OFF);
      break;
    }
    case SH1106_OLED_ON: {
      (*send8)(SH1106_DISPLAY_ON_OLED);
      break;
    }
    case SH1106_OLED_OFF: {
      (*send8)(SH1106_DISPLAY_OFF_OLED);
      break;
    }
  }
}

void sh1106_set_display_direction(t_send8 send8, enum sh1106_display_direction display_direction) {
  switch (display_direction) {
    case SH1106_DISPLAY_NORMAL_DIRECTION: {
      (*send8)(SH1106_SET_NORMAL_DISPLAY_DIRECTION);
      break;
    }
    case SH1106_DISPLAY_REVERSE_DIRECTION: {
      (*send8)(SH1106_SET_REVERSE_DISPLAY_DIRECTION);
      break;
    }
  }
}

void sh1106_set_multiplex_ration(t_send8 send8, uint8_t multiplex_ratio) {
  (*send8)(SH1106_MULTIPLE_RATION_MODE_SET);
  (*send8)(SH1106_MULTIPLEX_RATION_DATA_SET(multiplex_ratio));
}

void sh1106_set_dc_dc_mode(t_send8 send8, enum sh1106_dc_dc_mode dc_dc_mode) {
  switch (dc_dc_mode) {
    case SH1106_DC_DC_DISABLE: {
      (*send8)(SH1106_DC_DC_CONTROL_MODE_SET);
      (*send8)(SH1106_DC_DC_OFF_MODE_SET);
      break;
    }
    case SH1106_DC_DC_ENABLE: {
      (*send8)(SH1106_DC_DC_CONTROL_MODE_SET);
      (*send8)(SH1106_DC_DC_ON_MODE_SET);
      break;
    }
  }
}

void sh1106_set_page_address(t_send8 send8, uint8_t page_addr) {
  (*send8)(SH1106_SET_PAGE_ADDRESS(page_addr));
}

void sh1106_set_common_output_scan_direction(t_send8 send8,
                                             enum sh1106_common_output_scan_direction common_output_scan_direction) {
  switch (common_output_scan_direction) {
    case SH1106_COMMON_OUTPUT_SCAN_NORMAL_DIRECTION: {
      (*send8)(SH1106_SET_COMMON_OUTPUT_SCAN_DIRECTION_FROM_COM0_TO_COMN);
      break;
    }
    case SH1106_COMMON_OUTPUT_SCAN_DIRECTION_VERTICALLY_FLIPPED: {
      (*send8)(SH1106_SET_COMMON_OUTPUT_SCAN_DIRECTION_FROM_COMN_TO_COM0);
      break;
    }
  }
}

void sh1106_set_display_offset(t_send8 send8, uint8_t display_offset) {
  (*send8)(SH1106_DISPLAY_OFFSET_MODE_SET);
  (*send8)(SH1106_DISPLAY_OFFSET_DATA_SET(display_offset));
}

void sh1106_set_display_clock_divide_ratio_oscillator_frequency(t_send8 send8,
                                                                uint8_t clock_divide_ration,
                                                                enum sh1106_oscillator_frequency oscillator_frequency) {
  (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_MODE_SET);
  switch (oscillator_frequency) {
    case SH1106_OSCILLATOR_FREQUENCY_MINUS_25_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00000000));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_MINUS_20_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00000001));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_MINUS_15_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00000010));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_MINUS_10_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00000011));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_MINUS_5_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00000100));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_POR: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00000101));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_PLUS_5_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00000110));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_PLUS_10_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00000111));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_PLUS_15_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00001000));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_PLUS_20_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00001001));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_PLUS_25_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00001010));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_PLUS_30_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00001011));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_PLUS_35_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00001100));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_PLUS_40_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00001101));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_PLUS_45_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00001110));
      break;
    }
    case SH1106_OSCILLATOR_FREQUENCY_PLUS_50_PERCENT: {
      (*send8)(SH1106_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_DATA_SET(clock_divide_ration, 0b00001111));
      break;
    }
  }
}

void sh1106_set_dis_charge_pre_charge_period(t_send8 send8, uint8_t pre_charge_period, uint8_t dis_charge_period) {
  (*send8)(SH1106_PRE_CHARGE_PERIOD_MODE_SET);
  (*send8)(SH1106_DIS_CHARGE_PRE_CHARGE_PERIOD_DATA_SET(pre_charge_period, dis_charge_period));
}

void sh1106_set_common_pads_hardware_configuration(t_send8 send8,
                                                   enum sh1106_common_signals_pad_configuration common_signals_pad_configuration) {
  switch (common_signals_pad_configuration) {
    case SH1106_COMMON_SIGNALS_PAD_CONFIGURATION_SEQUENTIAL: {
      (*send8)(SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_MODE_SET);
      (*send8)(SH1106_SEQUENTIAL_MODE_SET);
      break;
    }
    case SH1106_COMMON_SIGNALS_PAD_CONFIGURATION_ALTERNATIVE: {
      (*send8)(SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_MODE_SET);
      (*send8)(SH1106_ALTERNATIVE_MODE_SET);
      break;
    }
  }
}

void sh1106_set_vcom_deselect_level(t_send8 send8, uint8_t deselect_level) {
  (*send8)(SH1106_VCOM_DESELECT_LEVEL_MODE_SET);
  (*send8)(SH1106_VCOM_DESELECT_LEVEL_DATA_SET(deselect_level));
}

void sh1106_read_modify_write(t_send8 send8) {
  (*send8)(SH1106_READ_MODIFY_WRITE);
}

void sh1106_end(t_send8 send8) {
  (*send8)(SH1106_END);
}

void sh1106_nop(t_send8 send8) {
  (*send8)(SH1106_NOP);
}

void sh1106_write_display_data(t_send8 send8, uint8_t data) {
  (*send8)(SH1106_WRITE_DISPLAY_DATA(data));
}
