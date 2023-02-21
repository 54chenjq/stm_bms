
#ifndef PARSE_TEMP_H_
#define PARSE_TEMP_H_


#include "stdlib.h"
#include "LTC681x.h"


uint8_t search_temp_range(uint16_t value, int16_t LUT[][2], uint8_t *range_min, uint8_t *range_max);

int16_t calc_temp(uint16_t ntc_voltage, int16_t LUT[][2], uint8_t LUT_size);

void parse_temp(uint8_t total_ic,cell_asic *ic);

#endif /* PARSE_TEMP_H_ */
