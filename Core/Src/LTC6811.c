
#include "stdint.h"
#include "LTC681x.h"
#include "LTC6811.h"

/* Initialize the Register limits */
void LTC6811_init_reg_limits(uint8_t total_ic, //The number of ICs in the system
							cell_asic *ic  //A two dimensional array where data will be written
							)
{
  for (uint8_t cic=0; cic<total_ic; cic++)
  {
    ic[cic].ic_reg.cell_channels=12;
    ic[cic].ic_reg.stat_channels=4;
    ic[cic].ic_reg.aux_channels=6;
    ic[cic].ic_reg.num_cv_reg=4;
    ic[cic].ic_reg.num_gpio_reg=2;
    ic[cic].ic_reg.num_stat_reg=3;
  }
}

/*
This command will write the configuration registers of the LTC6811-1s
connected. The configuration is written in descending
order so the last device's configuration is written first.
*/
void LTC6811_wrcfg(uint8_t total_ic, //The number of ICs being written to
                   cell_asic *ic, //A two dimensional array of the configuration data that will be written
				   SPI_HandleTypeDef * hspi
                  )
{
  LTC681x_wrcfg(total_ic,ic,hspi);
}

/* Reads configuration registers of a LTC6811 */
int8_t LTC6811_rdcfg(uint8_t total_ic, //Number of ICs in the system
                     cell_asic *ic, //A two dimensional array that the function stores the read configuration data.
					 SPI_HandleTypeDef * hspi
                    )
{
  int8_t pec_error = 0;
  pec_error = LTC681x_rdcfg(total_ic,ic,hspi);
  return(pec_error);
}

/* Starts cell voltage conversion */
void LTC6811_adcv(uint8_t MD, //ADC Mode
				  uint8_t DCP, //Discharge Permit
				  uint8_t CH, //Cell Channels to be measured
				  SPI_HandleTypeDef * hspi
				  )
{
  LTC681x_adcv(MD,DCP,CH,hspi);
}

/* Start a GPIO and Vref2 Conversion */
void LTC6811_adax(uint8_t MD, //ADC Mode
				  uint8_t CHG, //GPIO Channels to be measured
				  SPI_HandleTypeDef * hspi
				  )
{
  LTC681x_adax(MD,CHG,hspi);
}

/* Start a Status ADC Conversion */
void LTC6811_adstat(uint8_t MD, //ADC Mode
				    uint8_t CHST, //Stat Channels to be measured
					SPI_HandleTypeDef * hspi
				   )
{
  LTC681x_adstat(MD,CHST,hspi);
}

/*  Starts cell voltage  and GPIO 1 &  2 conversion */
void LTC6811_adcvax(uint8_t MD, //ADC Mode
				    uint8_t DCP, //Discharge Permit
					SPI_HandleTypeDef * hspi
				    )
{
  LTC681x_adcvax(MD,DCP,hspi);
}

/* Starts cell voltage and Sum of cells conversion */
void LTC6811_adcvsc(uint8_t MD, //ADC Mode
				    uint8_t DCP, //Discharge Permit
					SPI_HandleTypeDef * hspi
				    )
{
  LTC681x_adcvsc(MD,DCP,hspi);
}

/*
The function is used to read the  parsed cell voltage codes of the LTC6811.
This function will send the requested read commands parse the data and
store the cell voltages in c_codes variable
*/
uint8_t LTC6811_rdcv(uint8_t reg, // Controls which cell voltage register is read back.
                     uint8_t total_ic, // The number of ICs in the system
                     cell_asic *ic, // Array of the parsed cell codes
					 SPI_HandleTypeDef * hspi
                    )
{
  int8_t pec_error = 0;
  pec_error = LTC681x_rdcv(reg,total_ic,ic,hspi);
  return(pec_error);
}

/*
The function is used to read the  parsed GPIO codes of the LTC6811.
This function will send the requested read commands parse the data
and store the gpio voltages in a_codes variable
*/
int8_t LTC6811_rdaux(uint8_t reg, //Determines which GPIO voltage register is read back.
                     uint8_t total_ic,//The number of ICs in the system
                     cell_asic *ic,//A two dimensional array of the gpio voltage codes.
					 SPI_HandleTypeDef * hspi
                     )
{
  int8_t pec_error = 0;
  LTC681x_rdaux(reg,total_ic,ic,hspi);
  return (pec_error);
}

/*
Reads and parses the LTC6811 stat registers.
The function is used to read the  parsed stat codes of the LTC6811.
This function will send the requested read commands parse the data
and store the stat voltages in stat_codes variable
*/
int8_t LTC6811_rdstat(uint8_t reg, //Determines which Stat register is read back.
                      uint8_t total_ic,//The number of ICs in the system
                      cell_asic *ic, //Array of the parsed stat codes
					  SPI_HandleTypeDef * hspi
                     )
{
  int8_t pec_error = 0;
  pec_error = LTC681x_rdstat(reg,total_ic,ic,hspi);
  return (pec_error);
}

/* Sends the poll ADC command */
uint8_t LTC6811_pladc(SPI_HandleTypeDef * hspi)
{
  return(LTC681x_pladc(hspi));
}

//This function will block operation until the ADC has finished it's conversion */
uint32_t LTC6811_pollAdc(SPI_HandleTypeDef * hspi)
{
  return(LTC681x_pollAdc(hspi));
}

/*
The command clears the cell voltage registers and initializes all values to 1.
The register will read back hexadecimal 0xFF after the command is sent.
*/
void LTC6811_clrcell(SPI_HandleTypeDef * hspi)
{
  LTC681x_clrcell(hspi);
}

/*
The command clears the Auxiliary registers and initializes all values to 1.
The register will read back hexadecimal 0xFF after the command is sent.
*/
void LTC6811_clraux(SPI_HandleTypeDef * hspi)
{
  LTC681x_clraux(hspi);
}

/*
The command clears the Stat registers and initializes all values to 1.
The register will read back hexadecimal 0xFF after the command is sent.
*/
void LTC6811_clrstat(SPI_HandleTypeDef * hspi)
{
  LTC681x_clrstat(hspi);
}

/* Starts the Mux Decoder diagnostic self test */
void LTC6811_diagn(SPI_HandleTypeDef * hspi)
{
  LTC681x_diagn(hspi);
}

/* Starts cell voltage self test conversion */
void LTC6811_cvst(uint8_t MD, //ADC Mode
				  uint8_t ST, //Self Test
				  SPI_HandleTypeDef * hspi
				  )
{
  LTC681x_cvst(MD,ST,hspi);
}

/* Start an Auxiliary Register Self Test Conversion */
void LTC6811_axst(uint8_t MD, //ADC Mode
				  uint8_t ST, //Self Test
				  SPI_HandleTypeDef * hspi
				  )
{
  LTC681x_axst(MD,ST,hspi);
}

/* Start a Status Register Self Test Conversion */
void LTC6811_statst(uint8_t MD, //ADC Mode
				    uint8_t ST, //Self Test
					SPI_HandleTypeDef * hspi
				    )
{
  LTC681x_statst(MD,ST,hspi);
}

/* Starts cell voltage overlap conversion */
void LTC6811_adol(uint8_t MD, //ADC Mode
				  uint8_t DCP, //Discharge Permit
				  SPI_HandleTypeDef * hspi
				  )
{
  LTC681x_adol(MD,DCP,hspi);
}

/* Start an GPIO Redundancy test */
void LTC6811_adaxd(uint8_t MD, //ADC Mode
				   uint8_t CHG, //GPIO Channels to be measured
				   SPI_HandleTypeDef * hspi
				   )
{
  LTC681x_adaxd(MD,CHG,hspi);
}

/* Start a Status register redundancy test Conversion */
void LTC6811_adstatd(uint8_t MD, //ADC Mode
				     uint8_t CHST, //Stat Channels to be measured
					 SPI_HandleTypeDef * hspi
				    )
{
  LTC681x_adstatd(MD,CHST,hspi);
}

/* Runs the Digital Filter Self Test */
int16_t LTC6811_run_cell_adc_st(uint8_t adc_reg, // Type of register
								uint8_t total_ic,//Number of ICs in the system
								cell_asic *ic, //A two dimensional array that will store the data
								uint8_t md, //ADC Mode
								bool adcopt, //The adcopt bit in the configuration register
								SPI_HandleTypeDef * hspi
								)
{
  int16_t error = 0;
  error = LTC681x_run_cell_adc_st(adc_reg,total_ic,ic,md,adcopt,hspi);
  return(error);
}

/* Runs the ADC overlap test for the IC */
uint16_t LTC6811_run_adc_overlap(uint8_t total_ic,//Number of ICs in the system
								 cell_asic *ic, //A two dimensional array that will store the data
								 SPI_HandleTypeDef * hspi
								 )
{
  uint16_t error = 0;
  LTC681x_run_adc_overlap(total_ic, ic,hspi);
  return(error);
}

/* Runs the redundancy self test */
int16_t LTC6811_run_adc_redundancy_st(uint8_t adc_mode, //ADC Mode
									  uint8_t adc_reg, // Type of register
									  uint8_t total_ic,//Number of ICs in the system
									  cell_asic *ic, //A two dimensional array that will store the data
									  SPI_HandleTypeDef * hspi
									  )
{
  int16_t error = 0;
  LTC681x_run_adc_redundancy_st(adc_mode,adc_reg,total_ic,ic,hspi);
  return(error);
}

/* Start an open wire Conversion */
void LTC6811_adow(uint8_t MD, //ADC Mode
				  uint8_t PUP,//Pull up/ Pull down
				  uint8_t CH, //Cell selection
				  uint8_t DCP, //Discharge Permit
				  SPI_HandleTypeDef * hspi
				  )
{
  LTC681x_adow(MD,PUP,CH,DCP,hspi);
}

/* Runs the data sheet algorithm for open wire for single cell detection */
void LTC6811_run_openwire_single(uint8_t total_ic,//Number of ICs in the system
						         cell_asic *ic, //A two dimensional array that will store the data
								 SPI_HandleTypeDef * hspi
						        )
{
  LTC681x_run_openwire_single(total_ic,ic,hspi);
}

/* Runs the data sheet algorithm for open wire for multiple cell and two consecutive cells detection */
void LTC6811_run_openwire_multi(uint8_t total_ic,//Number of ICs in the system
						         cell_asic *ic, //A two dimensional array that will store the data
								 SPI_HandleTypeDef * hspi
						        )
{
  LTC681x_run_openwire_multi(total_ic,ic,hspi);
}

/* Helper function to set discharge bit in CFG register */
void LTC6811_set_discharge(int Cell, //The cell to be discharged
						   uint8_t total_ic, //Number of ICs in the system
						   cell_asic *ic //A two dimensional array that will store the data
						   )
{
  for (int i=0; i<total_ic; i++)
  {
    if ((Cell<9)&& (Cell!=0) )
    {
      ic[i].config.tx_data[4] = ic[i].config.tx_data[4] | (1<<(Cell-1));
    }
    else if (Cell < 13)
    {
      ic[i].config.tx_data[5] = ic[i].config.tx_data[5] | (1<<(Cell-9));
    }
	else
	{
		break;
	}
  }
}

/* Clears all of the DCC bits in the configuration registers */
void LTC6811_clear_discharge(uint8_t total_ic, cell_asic *ic)
{
  LTC681x_clear_discharge(total_ic,ic);
}

/* Writes the pwm registers of a LTC6811 */
void LTC6811_wrpwm(uint8_t total_ic, //Number of ICs in the system
                   uint8_t pwmReg,  //The number of registers being written to
                   cell_asic *ic, //A two dimensional array that the function stores the data in.
				   SPI_HandleTypeDef * hspi
                  )
{
  LTC681x_wrpwm(total_ic,pwmReg,ic,hspi);
}


/* Reads pwm registers of a LTC6811 */
int8_t LTC6811_rdpwm(uint8_t total_ic, //Number of ICs in the system
                     uint8_t pwmReg,  //The number of registers being written to
                     cell_asic *ic, //A two dimensional array that the function stores the read pwm data.
					 SPI_HandleTypeDef * hspi
                    )
{
  int8_t pec_error =0;
  pec_error = LTC681x_rdpwm(total_ic,pwmReg,ic,hspi);
  return(pec_error);
}

/* Writes data in S control register the LTC6811-1s connected */
void LTC6811_wrsctrl(uint8_t total_ic, //Number of ICs in the system
                     uint8_t sctrl_reg, //The number of registers being written to
                     cell_asic *ic, //A two dimensional array of the data that will be written
					 SPI_HandleTypeDef * hspi
                    )
{
  LTC681x_wrsctrl(total_ic, sctrl_reg, ic,hspi);
}

/* Reads sctrl registers of a LTC6811 */
int8_t LTC6811_rdsctrl(uint8_t total_ic, //Number of ICs in the system
                       uint8_t sctrl_reg,//The number of registers being written to
                       cell_asic *ic, //A two dimensional array that the function stores the read data
					   SPI_HandleTypeDef * hspi
                      )
{
  int8_t pec_error =0;
  pec_error =  LTC681x_rdsctrl(total_ic, sctrl_reg,ic,hspi );
  return(pec_error);
}

/*
Start Sctrl data communication
This command will start the sctrl pulse communication over the spins
*/
void LTC6811_stsctrl(SPI_HandleTypeDef * hspi)
{
  LTC681x_stsctrl(hspi);
}

/*
The command clears the Sctrl registers and initializes
all values to 0. The register will read back hexadecimal 0x00
after the command is sent.
 */
void LTC6811_clrsctrl(SPI_HandleTypeDef * hspi)
{
  LTC681x_clrsctrl(hspi);
}

/* Writes the COMM registers of a LTC6811 */
void LTC6811_wrcomm(uint8_t total_ic, //The number of ICs being written to
                    cell_asic *ic, //A two dimensional array of the comm data that will be written
					SPI_HandleTypeDef * hspi
                   )
{
  LTC681x_wrcomm(total_ic,ic,hspi);
}

/* Reads COMM registers of a LTC6811 */
int8_t LTC6811_rdcomm(uint8_t total_ic, //Number of ICs in the system
                      cell_asic *ic, //A two dimensional array that the function stores the read comm data.
					  SPI_HandleTypeDef * hspi
                     )
{
  int8_t pec_error = 0;
  LTC681x_rdcomm(total_ic, ic,hspi);
  return(pec_error);
}

/* Shifts data in COMM register out over LTC6811 SPI/I2C port */
void LTC6811_stcomm(uint8_t len,SPI_HandleTypeDef * hspi)
{
  LTC681x_stcomm(len,hspi); // length of data to be transmitted
}

/* Helper function that increments PEC counters */
void LTC6811_check_pec(uint8_t total_ic,//Number of ICs in the system
					   uint8_t reg, // Type of register
					   cell_asic *ic//A two dimensional array that will store the data
					   )
{
  LTC681x_check_pec(total_ic,reg,ic);
}

/* Helper Function to reset PEC counters */
void LTC6811_reset_crc_count(uint8_t total_ic, //Number of ICs in the system
							 cell_asic *ic //A two dimensional array that will store the data
							 )
{
  LTC681x_reset_crc_count(total_ic,ic);
}

/* Helper function to initialize CFG variables.*/
void LTC6811_init_cfg(uint8_t total_ic, //Number of ICs in the system
					  cell_asic *ic //A two dimensional array that will store the data
					  )
{
  LTC681x_init_cfg(total_ic,ic);
}

/* Helper function to set CFGR variable */
void LTC6811_set_cfgr(uint8_t nIC, //current IC
                      cell_asic *ic,//a two dimensional array that will store the data
					  bool refon, // The REFON bit
					  bool adcopt, // The ADCOPT bit
					  bool gpio[5],// The GPIO bit
					  bool dcc[12],// The DCC bit
					  bool dcto[4],// The Dcto bit
					  uint16_t uv, // The UV bit
					  uint16_t  ov // The OV bit
					  )
{
  LTC681x_set_cfgr(nIC ,ic,refon,adcopt,gpio,dcc,dcto, uv, ov);
}

/* Helper function to set the REFON bit */
void LTC6811_set_cfgr_refon(uint8_t nIC, cell_asic *ic, bool refon)
{
  LTC681x_set_cfgr_refon(nIC,ic,refon);
}

/* Helper function to set the adcopt bit */
void LTC6811_set_cfgr_adcopt(uint8_t nIC, cell_asic *ic, bool adcopt)
{
  LTC681x_set_cfgr_adcopt(nIC,ic,adcopt);
}

/* Helper function to set GPIO bits */
void LTC6811_set_cfgr_gpio(uint8_t nIC, cell_asic *ic,bool gpio[5])
{
  LTC681x_set_cfgr_gpio(nIC,ic,gpio);
}

/* Helper function to control discharge */
void LTC6811_set_cfgr_dis(uint8_t nIC, cell_asic *ic,bool dcc[12])
{
  LTC681x_set_cfgr_dis(nIC,ic,dcc);
}

/* Helper function to control discharge */
void LTC6811_set_cfgr_dcto(uint8_t nIC, cell_asic *ic,bool dcto[4])
{
  LTC681x_set_cfgr_dcto(nIC, ic,dcto);
}

/* Helper Function to set uv value in CFG register */
void LTC6811_set_cfgr_uv(uint8_t nIC, cell_asic *ic,uint16_t uv)
{
  LTC681x_set_cfgr_uv(nIC, ic, uv);
}

/* Helper function to set OV value in CFG register */
void LTC6811_set_cfgr_ov(uint8_t nIC, cell_asic *ic,uint16_t ov)
{
  LTC681x_set_cfgr_ov( nIC, ic, ov);
}
