# Mykonos ARM firmware header (not included)

`rf_config.c` includes `Mykonos_M3.h`, the AD9371 (Mykonos) ARM processor firmware (ARM firmware 5.1.1, used with Mykonos API 1.5.1.3565).

Analog Devices distributes this firmware under the *AD937X Software License Agreement (20180301-AD937X-CTSLA)*, which allows it to be distributed only as object code inside a product. It is therefore not stored in this repository. Download it from Analog Devices and place it in this folder before building.

**Use the same version this design was tested with.** The file is on the `2018_R1` release branch of Analog Devices' no-OS repository:

- <https://github.com/analogdevicesinc/no-OS/blob/2018_R1/ad9371/sw/Mykonos_M3.h>

```sh
curl -LO https://raw.githubusercontent.com/analogdevicesinc/no-OS/2018_R1/ad9371/sw/Mykonos_M3.h
```

Check the download (it must match exactly):

```
a9056953f65975b4e0d58e977b7fb8b86775e0ad3d90b497e1d8a9ad38a5b406  Mykonos_M3.h
```

Later no-OS branches (`2018_R2` and newer) ship ARM firmware 5.2, which needs the matching Mykonos API 1.5.2 and has not been tested with this design.

The prebuilt application `.elf` in the Releases already contains this firmware in object-code form.
