/* AD9528 data structure initialization file */

/**
* \page Disclaimer Legal Disclaimer
* Copyright 2015-2017 Analog Devices Inc.
* Released under the AD9371 API license, for more information see the "LICENSE.txt" file in this zip file.
*
*/


#include <stdint.h>
#include "common.h"
#include "t_ad9528.h"

static spiSettings_t clockSpiSettings =
{
     2,         /* chip select Index */
     0,         /* Write bit polarity */
     1,         /* 16bit instruction word */
     1,         /* MSB first */
     0,         /* Clock phase */
     0,         /* Clock polarity */
     0,         /* uint8_t enSpiStreaming */
     1,         /* uint8_t autoIncAddrUp */
     1,         /* uint8_t fourWireMode */
     25000000   /* spiClkFreq_Hz */   
};

ad9528pll1Settings_t clockPll1Settings =
{
    30720000,
    1,
    3,
    0,
    1,
    0,
    122880000,
    2,
    4
};

ad9528pll2Settings_t clockPll2Settings =
{
    3,
    10,
    30
};

ad9528outputSettings_t clockOutputSettings =
{
    53237,
    {0,0,0,2,0,0,0,0,0,0,0,0,2,0},
    {0,0,0,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,2,0,0,0,0,0,0,0,0,0,0},
    {10,10,10,10,10,10,10,10,10,10,10,10,10,10},
    {122880000, 122880000, 122880000, 122880000, 122880000, 122880000, 122880000, 122880000, 122880000, 122880000, 122880000, 122880000, 122880000, 122880000}
};

ad9528sysrefSettings_t clockSysrefSettings =
{
   0,
   2,
   0,
   0,
   0,
   0,
   512
};

ad9528Device_t clockAD9528_ =
{
    &clockSpiSettings,
    &clockPll1Settings,
    &clockPll2Settings,
    &clockOutputSettings,
    &clockSysrefSettings
};
