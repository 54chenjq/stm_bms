#ifndef LTC6811_H
#define LTC6811_H

#include "stdint.h"
#include "LTC681x.h"

#define CELL 1
#define AUX 2
#define STAT 3

/*!
 Initialize the Register limits
 @return void
 */
void LTC6811_init_reg_limits(uint8_t total_ic, //!< Number of ICs in the system
							 cell_asic *ic //!< A two dimensional array that will store the data
							 );

/*!
 Write the LTC6811 configuration register
 @return void
 */
void LTC6811_wrcfg(uint8_t total_ic, //The number of ICs being written to
                   cell_asic *ic, //A two dimensional array of the configuration data that will be written
				   SPI_HandleTypeDef * hspi
                  );

/*!
 Reads configuration registers of a LTC6811
 @return int8_t, PEC Status.
  0: Data read back has matching PEC
 -1: Data read back has incorrect PEC
 */
int8_t LTC6811_rdcfg(uint8_t total_ic, //Number of ICs in the system
                     cell_asic *ic, //A two dimensional array that the function stores the read configuration data.
					 SPI_HandleTypeDef * hspi
                    );

/*!
 Starts cell voltage conversion
 @return void
 */
void LTC6811_adcv(uint8_t MD, //ADC Mode
				  uint8_t DCP, //Discharge Permit
				  uint8_t CH, //Cell Channels to be measured
				  SPI_HandleTypeDef * hspi
				  );

/*!
 Start a GPIO and Vref2 Conversion
 @return void
 */
void LTC6811_adax(uint8_t MD, //ADC Mode
				  uint8_t CHG, //GPIO Channels to be measured
				  SPI_HandleTypeDef * hspi
				  );

/*!
 Start a Status ADC Conversion
 @return void
 */
void LTC6811_adstat(uint8_t MD, //ADC Mode
				    uint8_t CHST, //Stat Channels to be measured
					SPI_HandleTypeDef * hspi
				   );

/*!
 Starts cell voltage  and GPIO 1&2 conversion
 @return void
 */
void LTC6811_adcvax(uint8_t MD, //ADC Mode
				    uint8_t DCP, //Discharge Permit
					SPI_HandleTypeDef * hspi
				    );

/*!
 Starts cell voltage and SOC conversion
 @return void
 */
void LTC6811_adcvsc(uint8_t MD, //ADC Mode
				    uint8_t DCP, //Discharge Permit
					SPI_HandleTypeDef * hspi
				    );

/*!
 Reads and parses the LTC6811 cell voltage registers.
 @return uint8_t, PEC Status.
  0: No PEC error detected
 -1: PEC error detected, retry read
 */
uint8_t LTC6811_rdcv(uint8_t reg, // Controls which cell voltage register is read back.
                     uint8_t total_ic, // The number of ICs in the system
                     cell_asic *ic, // Array of the parsed cell codes
					 SPI_HandleTypeDef * hspi
                    );

/*!
 Reads and parses the LTC6811 auxiliary registers.
 @return  int8_t, PEC Status
   0: No PEC error detected
  -1: PEC error detected, retry read
  */
int8_t LTC6811_rdaux(uint8_t reg, //Determines which GPIO voltage register is read back.
                     uint8_t total_ic,//The number of ICs in the system
                     cell_asic *ic,//A two dimensional array of the gpio voltage codes.
					 SPI_HandleTypeDef * hspi
                     );

/*!
 Reads and parses the LTC6811 stat registers.
 @return  int8_t, PEC Status
  0: No PEC error detected
 -1: PEC error detected, retry read
 */
int8_t LTC6811_rdstat(uint8_t reg, //Determines which Stat register is read back.
                      uint8_t total_ic,//The number of ICs in the system
                      cell_asic *ic, //Array of the parsed stat codes
					  SPI_HandleTypeDef * hspi
                     );

/*!
 Sends the poll ADC command
 @returns uint8_t, 1 byte read back after a pladc command. If the byte is not 0xFF ADC conversion has completed
*/
uint8_t LTC6811_pladc(SPI_HandleTypeDef * hspi);

/*!
 This function will block operation until the ADC has finished it's conversion
  @returns uint32_t, the approximate time it took for the ADC function to complete.
  */
uint32_t LTC6811_pollAdc(SPI_HandleTypeDef * hspi);

/*!
 Clears the LTC6811 cell voltage registers
 @return void
 */
void LTC6811_clrcell(SPI_HandleTypeDef * hspi);

/*!
 Clears the LTC6811 Auxiliary registers
 @return void
 */
void LTC6811_clraux(SPI_HandleTypeDef * hspi);

/*!
 Clears the LTC6811 Stat registers
 @return void
 */
void LTC6811_clrstat(SPI_HandleTypeDef * hspi);

/*!
 Starts the Mux Decoder diagnostic self test
  Running this command will start the Mux Decoder Diagnostic Self Test.
  This test takes roughly 1ms to complete. The MUXFAIL bit will be updated.
  The bit will be set to 1 for a failure and 0 if the test has been passed.
 @return void
 */
void LTC6811_diagn(SPI_HandleTypeDef * hspi);

/*!
 Starts cell voltage self test conversion
 @return void
 */
void LTC6811_cvst(uint8_t MD, //ADC Mode
				  uint8_t ST, //Self Test
				  SPI_HandleTypeDef * hspi
				  );

/*!
 Start an Auxiliary Register Self Test Conversion
  @return void
 */
void LTC6811_axst(uint8_t MD, //ADC Mode
				  uint8_t ST, //Self Test
				  SPI_HandleTypeDef * hspi
				  );

/*!
 Start a Status Register Self Test Conversion
 @return void
 */
void LTC6811_statst(uint8_t MD, //ADC Mode
				    uint8_t ST, //Self Test
					SPI_HandleTypeDef * hspi
				    );


/*!
 Starts cell voltage overlap conversion
 @return void
 */
void LTC6811_adol(uint8_t MD, //ADC Mode
				  uint8_t DCP, //Discharge Permit
				  SPI_HandleTypeDef * hspi
				  );

/*!
 Start an GPIO Redundancy test
 @return void
 */
void LTC6811_adaxd(uint8_t MD, //ADC Mode
				   uint8_t CHG, //GPIO Channels to be measured
				   SPI_HandleTypeDef * hspi
				   );

/*!
 Start a Status register redundancy test Conversion
 @return void
 */
void LTC6811_adstatd(uint8_t MD, //ADC Mode
				     uint8_t CHST, //Stat Channels to be measured
					 SPI_HandleTypeDef * hspi
				    );

/*!
  Helper function that runs the ADC Self Tests
  @return int16_t, error
  Number of errors detected
  */
int16_t LTC6811_run_cell_adc_st(uint8_t adc_reg, // Type of register
								uint8_t total_ic,//Number of ICs in the system
								cell_asic *ic, //A two dimensional array that will store the data
								uint8_t md, //ADC Mode
								bool adcopt, //The adcopt bit in the configuration register
								SPI_HandleTypeDef * hspi
								);

/*!
 Helper Function that runs the ADC Overlap test
  @return uint16_t, error
  0: Pass
 -1: False, Error detected
 */
uint16_t LTC6811_run_adc_overlap(uint8_t total_ic,//Number of ICs in the system
								 cell_asic *ic, //A two dimensional array that will store the data
								 SPI_HandleTypeDef * hspi
								 );

/*!
 Helper function that runs the ADC Digital Redundancy commands and checks output for errors
 @return int16_t, error
 */
int16_t LTC6811_run_adc_redundancy_st(uint8_t adc_mode, //ADC Mode
									  uint8_t adc_reg, // Type of register
									  uint8_t total_ic,//Number of ICs in the system
									  cell_asic *ic, //A two dimensional array that will store the data
									  SPI_HandleTypeDef * hspi
									  );

/*!
 Start an open wire Conversion
 @return void
 */
void LTC6811_adow(uint8_t MD, //ADC Mode
				  uint8_t PUP,//Pull up/ Pull down
				  uint8_t CH, //Cell selection
				  uint8_t DCP, //Discharge Permit
				  SPI_HandleTypeDef * hspi
				  );

/*!
 Helper function that runs the data sheet open wire algorithm for single cell detection
 @return void
 */
void LTC6811_run_openwire_single(uint8_t total_ic,//Number of ICs in the system
						         cell_asic *ic, //A two dimensional array that will store the data
								 SPI_HandleTypeDef * hspi
						        );

/*!
 Helper function that runs open wire for multiple cell and two consecutive cells detection
 @return void
 */
void LTC6811_run_openwire_multi(uint8_t total_ic,//Number of ICs in the system
						         cell_asic *ic, //A two dimensional array that will store the data
								 SPI_HandleTypeDef * hspi
						        );

/*!
 Helper function to set discharge bit in CFG register
 @return void  */
void LTC6811_set_discharge(int Cell, //!< The cell to be discharged
                           uint8_t total_ic, //!< Number of ICs in the system
                           cell_asic *ic //!< A two dimensional array that will store the data
						   );

/*!
 Clears all of the DCC bits in the configuration registers
 @return void
 */
void LTC6811_clear_discharge(uint8_t total_ic, //!< Number of ICs in the daisy chain
							 cell_asic *ic //!< A two dimensional array that will store the data
					        );

/*!
 Write the LTC6811 PWM register
 @return void
 */
void LTC6811_wrpwm(uint8_t total_ic, //Number of ICs in the system
                   uint8_t pwmReg,  //The number of registers being written to
                   cell_asic *ic, //A two dimensional array that the function stores the data in.
				   SPI_HandleTypeDef * hspi
                  );

/*!
 Reads pwm registers of a LTC6811 daisy chain
 @return int8_t, PEC Status.
  0: Data read back has matching PEC
 -1: Data read back has incorrect PEC
 */
int8_t LTC6811_rdpwm(uint8_t total_ic, //Number of ICs in the system
                     uint8_t pwmReg,  //The number of registers being written to
                     cell_asic *ic, //A two dimensional array that the function stores the read pwm data.
					 SPI_HandleTypeDef * hspi
                    );

/*!
 Write the LTC6811 Sctrl register
 @return void
 */
void LTC6811_wrsctrl(uint8_t total_ic, //Number of ICs in the system
                     uint8_t sctrl_reg, //The number of registers being written to
                     cell_asic *ic, //A two dimensional array of the data that will be written
					 SPI_HandleTypeDef * hspi
                    );

/*!
 Reads sctrl registers of a LTC6811 daisy chain
  @return int8_t, PEC Status.
   0: Data read back has matching PEC
  -1: Data read back has incorrect PEC
  */
int8_t LTC6811_rdsctrl(uint8_t total_ic, //Number of ICs in the system
                       uint8_t sctrl_reg,//The number of registers being written to
                       cell_asic *ic, //A two dimensional array that the function stores the read data
					   SPI_HandleTypeDef * hspi
                      );

/*!
 Start Sctrl data communication
  This command will start the sctrl pulse communication over the spins
 @return void
 */
void LTC6811_stsctrl(SPI_HandleTypeDef * hspi);

/*!
 Clears the LTC6811 Sctrl registers
 @return void
 */
void LTC6811_clrsctrl(SPI_HandleTypeDef * hspi);

/*!
 Writes to the LTC6811 COMM register
 @return void
 */
void LTC6811_wrcomm(uint8_t total_ic, //The number of ICs being written to
                    cell_asic *ic, //A two dimensional array of the comm data that will be written
					SPI_HandleTypeDef * hspi
                   );

/*!
 Reads comm registers of a LTC6811 daisy chain
  @return int8_t, PEC Status.
  0: Data read back has matching PEC
 -1: Data read back has incorrect PEC
 */
int8_t LTC6811_rdcomm(uint8_t total_ic, //Number of ICs in the system
                      cell_asic *ic, //A two dimensional array that the function stores the read comm data.
					  SPI_HandleTypeDef * hspi
                     );

/*!
 Issues a stcomm command and clocks data out of the COMM register
 @return void
 */
void LTC6811_stcomm(uint8_t len, //!< Length of data to be transmitted
					SPI_HandleTypeDef * hspi
					);

/*!
 Helper Function that counts overall PEC errors and register/IC PEC errors
 @return void
 */
void LTC6811_check_pec(uint8_t total_ic,//!< Number of ICs in the system
                       uint8_t reg, //!< Type of register
                       cell_asic *ic //!< A two dimensional array that will store the data
					   );

/*!
 Helper Function that resets the PEC error counters
 @return void
 */
void LTC6811_reset_crc_count(uint8_t total_ic, //!< Number of ICs in the system
                             cell_asic *ic //!< A two dimensional array that will store the data
							 );

/*!
 Helper Function to initialize the CFGR data structures
 @return void
 */
void LTC6811_init_cfg(uint8_t total_ic, //!< Number of ICs in the system
                      cell_asic *ic //!< A two dimensional array that will store the data
					  );

/*!
 Helper function to set appropriate bits in CFGR register based on bit function
 @return void
 */
void LTC6811_set_cfgr(uint8_t nIC, //!< Current IC
                      cell_asic *ic,//!< A two dimensional array that will store the data
					  bool refon, //!< The REFON bit
					  bool adcopt, //!< The ADCOPT bit
					  bool gpio[5],//!< The GPIO bits
					  bool dcc[12],//!< The DCC bits
					  bool dcto[4],//!< The Dcto bits
					  uint16_t uv, //!< The UV value
					  uint16_t  ov //!< The OV value
					  );

/*!
 Helper function to turn the refon bit HIGH or LOW
 @return void
 */
void LTC6811_set_cfgr_refon(uint8_t nIC, //!< Current IC
                            cell_asic *ic, //!< A two dimensional array that will store the data
                            bool refon //!< The REFON bit
							);

/*!
 Helper function to turn the ADCOPT bit HIGH or LOW
 @return void
 */
void LTC6811_set_cfgr_adcopt(uint8_t nIC,  //!< Current IC
                             cell_asic *ic, //!< A two dimensional array that will store the data
                             bool adcopt //!< The ADCOPT bit
 							 );

/*!
 Helper function to turn the GPIO bits HIGH or LOW
 @return void
 */
void LTC6811_set_cfgr_gpio(uint8_t nIC, //!< Current IC
                           cell_asic *ic, //!< A two dimensional array that will store the data
                           bool gpio[] //!< The GPIO bits
						  );

/*!
 Helper function to turn the DCC bits HIGH or LOW
 @return void
 */
void LTC6811_set_cfgr_dis(uint8_t nIC, //!< Current IC
                          cell_asic *ic, //!< A two dimensional array that will store the data
                          bool dcc[] //!< The DCC bits
						  );

/*!
 Helper function to set uv field in CFGRA register
 @return void
 */
void LTC6811_set_cfgr_uv(uint8_t nIC, //!< Current IC
                         cell_asic *ic, //!< A two dimensional array that will store the data
                         uint16_t uv  //!< The UV value
						);
/*!
 Helper function to set ov field in CFGRA register
 @return void
 */
void LTC6811_set_cfgr_ov(uint8_t nIC, //!< Current IC
                         cell_asic *ic, //!< A two dimensional array that will store the data
                         uint16_t ov //!< The OV value
						);

#endif
