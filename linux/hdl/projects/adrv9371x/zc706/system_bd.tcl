set dac_fifo_address_width 10

source $ad_hdl_dir/projects/common/zc706/zc706_system_bd.tcl

# Load the verified XC7Z100 PS7 configuration of this board.
source ps7_xc7z100_config.tcl

# The XC7Z100-ADRV9371 board does not expose the ZC706 I2C interface.
delete_bd_objs [get_bd_cells axi_iic_main] [get_bd_intf_ports iic_main]
ad_connect sys_concat_intc/In14 GND

source $ad_hdl_dir/projects/adrv9371x/zc706/xc7z100_plddr3_dacfifo_bd.tcl
source $ad_hdl_dir/projects/scripts/adi_pd.tcl

set mem_init_sys_path [get_env_param ADI_PROJECT_DIR ""]mem_init_sys.txt;

#system ID
ad_ip_parameter axi_sysid_0 CONFIG.ROM_ADDR_BITS 9
ad_ip_parameter rom_sys_0 CONFIG.PATH_TO_FILE "[pwd]/$mem_init_sys_path"
ad_ip_parameter rom_sys_0 CONFIG.ROM_ADDR_BITS 9

sysid_gen_sys_init_file

ad_ip_parameter sys_ps7 CONFIG.PCW_FPGA2_PERIPHERAL_FREQMHZ 200

source ../common/adrv9371x_bd.tcl
