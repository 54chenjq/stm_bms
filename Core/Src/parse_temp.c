

#ifndef done

#include "parse_temp.h"


#define LUT_SIZE	32

static int16_t temp_tbl_sram[32][2] = {
	{22962, 0},
	{22401, 2},
	{21819, 4},
	{21218, 6},
	{20599, 8},
	{19966, 10},
	{19319, 12},
	{18663, 14},
	{18000, 16},
	{17332, 18},
	{16662, 20},
	{15994, 22},
	{15330, 24},
	{14672, 26},
	{14023, 28},
	{13385, 30},
	{12760, 32},
	{12150, 34},
	{11556, 36},
	{10980, 38},
	{10423, 40},
	{9885, 42},
	{9367, 44},
	{8870, 46},
	{8394, 48},
	{7939, 50},
	{7505, 52},
	{7091, 54},
	{6697, 56},
	{6323, 58},
	{5969, 60},
	{5633, 62}
};

/*!
	Recursively looks for indexes of smallest range of values between
	which value parameter falls within.

	@param value
	@param LUT[][2]		Lookup table
	@param range_min	Pointer to value of the start of LUT range indexes
	@param range_max	Pointer to value of the end of LUT range indexes

	@return 0 on exit
*/

uint8_t search_temp_range(uint16_t value,
						  int16_t LUT[][2],
						  uint8_t *range_min,
						  uint8_t *range_max
						  )
{
	if (*range_min + 1 != *range_max)
	{
		{
			uint8_t lower_range_min = *range_min;
			uint8_t lower_range_max = *range_min + ((*range_max - *range_min)>>1);
			uint8_t higher_range_min = lower_range_max + 1;
			uint8_t higher_range_max = *range_max;
			if ((value <= LUT[lower_range_min][0])&&(value >= LUT[lower_range_max][0]))
			{
				*range_min = lower_range_min;
				*range_max = lower_range_max;
				search_temp_range(value, LUT, range_min, range_max);
			}
			else if ((value <= LUT[higher_range_min][0])&&(value >= LUT[higher_range_max][0]))
			{
				*range_min = higher_range_min;
				*range_max = higher_range_max;
				search_temp_range(value, LUT, range_min, range_max);
			}
			else
			{
				*range_min = lower_range_max;
				*range_max = higher_range_min;
			}
		}
	}
	return 0;
}


/*!
	Calculates the temperature from thermistor voltage using lookup table. Linear equations
	are used for approximation.

	@param ntc_voltage	Voltage across thermistor
	@param LUT[][2]		Lookup table
	@param LUT_size		Lookup table's outermost dimension size. Must be 2^n number.

	@return degrees C
*/
int16_t calc_temp(uint16_t ntc_voltage,
				  int16_t LUT[][2],
				  uint8_t LUT_size
				  )
{
	uint8_t range_min = 0;
	uint8_t range_max = LUT_size - 1;
	search_temp_range(ntc_voltage, LUT, &range_min, &range_max);


	int16_t x0 = LUT[range_min][0];
	int16_t x1 = LUT[range_max][0];
	int32_t y0 = LUT[range_min][1] * 1048576; /*2^20 == 1048576*/
	int32_t y1 = LUT[range_max][1] * 1048576;


	/*Linear equation formula: y = mx + b*/
	int32_t m = (y1 - y0)/(x1 - x0);
	int32_t b = y0 - (m * x0);
	int16_t temperature = (m * ntc_voltage + b) / (10486); /*(2^20 / 100) == 1048576*/
	return temperature;
}



/*!
	Parse raw auxiliary voltage values from measurement boards, set according status flags,
	and update values in temperature array.

	@param total_ic				Number of measurement boards connected
	@param aux_codes			Array of auxiliary reading from measurement boards
	@param temp_codes			Array of temperature values
	@param ext_status_flags		BMS extended status flag byte
	@param LUT					Lookup table of size 2^n by 2

	@return void
*/
void parse_temp(uint8_t total_ic,cell_asic *ic)
{

	uint16_t temp_c[total_ic][6];

	for(uint8_t i = 0; i < total_ic; i++){

		for (uint8_t j = 0; j < 6; i++){    //todo change for LTC6813

			temp_c[i][j] = calc_temp(ic[i].aux.a_codes[j], temp_tbl_sram, LUT_SIZE);
		}

	}

/*

	for (uint8_t i = 0; i<total_ic; i++)
	{
		for (uint8_t j = 0; j<5; j++)
		{
			temp_data[i][j].temp = calc_temp(temp_data[i][j].raw, temp_tbl_sram, LUT_SIZE);
		}
	}*/
}
#endif
