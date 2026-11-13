/***************************************************include file****************************************/
#include "common.h"
#include "parameters.h"
#include "ad9528.h"
#include "mykonos.h"
#include "t_mykonos_gpio.h"
#include "jesd_core.h"
#include "jesd_phy.h"
#include "rf_config.h"
#include "change_rfpll.h"

uint32_t jesd_phy_addr = XPAR_JESD204_PHY_0_BASEADDR;			//JESD PHY
uint32_t axi_lite_addr = XPAR_UP_AXI_0_BASEADDR;				//up_axi addr

//EMIO config
extern struct no_os_gpio_desc	*gpio_ad9528_sysref_req;
extern struct no_os_gpio_desc	*gpio_ad9371_tx1_enable;
extern struct no_os_gpio_desc	*gpio_ad9371_tx2_enable;
extern struct no_os_gpio_desc	*gpio_ad9371_rx1_enable;
extern struct no_os_gpio_desc	*gpio_ad9371_rx2_enable;

//Devcie
extern ad9528Device_t clockAD9528;
extern mykonosDevice_t mykDevice;


//jesd core define
jesd_core_array jesd_array;


int main(void)
{
	//Status define
	ADI_ERR 		error;
	ad9528Device_t *AD9528_device = &clockAD9528;
	mykonosErr_t	mykError;
	const char *errorString;
	errorString = (const char*) malloc(sizeof(char) * 200);

	//static Define param
	jesd_core tx_jesd;
	jesd_core rx_jesd;

	//JESD Core Config
	tx_jesd.base_address = XPAR_JESD204_2_BASEADDR;		//BASEADDR
	tx_jesd.rx_tx_n = 0;					//TX Flag
	tx_jesd.scramble_enable = 1;
	tx_jesd.octets_per_frame = 2;			// F = 2
	tx_jesd.frames_per_multiframe = 32;		// K = 32
	tx_jesd.subclass_mode = 1;				//subclass 1

	rx_jesd.base_address = XPAR_JESD204_1_BASEADDR;		//BASEADDR
	rx_jesd.rx_tx_n = 1;					//RX Flag
	rx_jesd.scramble_enable = 1;			//
	rx_jesd.octets_per_frame = 4;			// F = 4
	rx_jesd.frames_per_multiframe = 32;		// K = 32
	rx_jesd.subclass_mode = 1;				//subclass 1

	jesd_array.tx_jesd = tx_jesd;
	jesd_array.rx_jesd = rx_jesd;
	jesd_array.orx_jesd = rx_jesd;
	jesd_array.orx_jesd.octets_per_frame = 2;	// F = 2
	jesd_array.orx_jesd.base_address=XPAR_JESD204_0_BASEADDR;

	//Cache Disable
	Xil_ICacheDisable();
	Xil_DCacheDisable();

	//platform & gpio init
	 platform_init();

	//GPIO Config output
	AXI_REG_WRITE(axi_lite_addr, 73 * 4, 0x7FFFF);		//rf1_gpio_t
	AXI_REG_WRITE(axi_lite_addr, 75 * 4, 0);			//rf1_gpio_o

	//AD9528 config
	AD9528_resetDevice(AD9528_device);
	error = AD9528_initDeviceDataStruct(AD9528_device,AD9528_device->pll1Settings->vcxo_Frequency_Hz,AD9528_device->pll1Settings->refA_Frequency_Hz,AD9528_device->outputSettings->outFrequency_Hz[1]);
	error = AD9528_initialize(AD9528_device);
	if (error != ADIERR_OK)
		xil_printf("WARNING: AD9528_initialize() issues. Possible cause: REF_CLK not connected.\n");
	else
		xil_printf("AD9528_initialize successful!\n");

	//request SYSREF
	no_os_gpio_direction_output(gpio_ad9528_sysref_req, 1);
	//AD9371 & JESD204B Init

	mykError = ad9371_initial(&mykDevice, jesd_array,jesd_phy_addr);
	if (mykError != MYKONOS_ERR_OK) {
		errorString = getMykonosErrorMessage(mykError);
		printf("%s", errorString);
	} else
		printf("FMC_AD9371 config successful!\n");
	//Stop SYSREF
	no_os_gpio_direction_output(gpio_ad9528_sysref_req, 0);


	//Change LO
	uint64_t tx_freq=1500e6;
	uint64_t rx_freq=1500e6;
	change_rfpll(mykDevice, TX_PLL, tx_freq);
	MYKONOS_getRfPllFrequency(&mykDevice , TX_PLL,&tx_freq);
	printf("tx_lo_freq=%lluHz\n", tx_freq);
	change_rfpll(mykDevice, RX_PLL, rx_freq);
	MYKONOS_getRfPllFrequency(&mykDevice , RX_PLL,&rx_freq);
	printf("rx_lo_freq=%lluHz\n", rx_freq);

	//Set RF TX & RX
	MYKONOS_setTx1Attenuation(&mykDevice,0);
	MYKONOS_setTx2Attenuation(&mykDevice,0);		//10db Atten
	MYKONOS_setRx1ManualGain(&mykDevice, 8+195);
	MYKONOS_setRx2ManualGain(&mykDevice, 8+195);


	while(1){

	}
}
