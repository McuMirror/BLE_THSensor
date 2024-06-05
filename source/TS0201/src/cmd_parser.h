#pragma once 

// A complete list of interface commands for different devices.
// Not all commands are supported by a specific device (!)
enum {
	CMD_ID_DEV_ID 	= 0x00, // Get dev id, version, services
	CMD_ID_DNAME    = 0x01, // Get/Set device name, "\0" - default: ATC_xxxx
	CMD_ID_GDEVS 	= 0x02, // Get address devises
	CMD_ID_I2C_SCAN = 0x03, // I2C scan
	CMD_ID_I2C_UTR	= 0x04, // Universal I2C/SMBUS read-write
	CMD_ID_SEN_ID	= 0x05,	// Get sensor ID
	CMD_ID_FLASH_ID	= 0x06,	// Get Flash JEDEC ID
	CMD_ID_DEV_MAC	= 0x10, // Get/Set MAC [+RandMAC], [size][mac[6][randmac[2]]]
	CMD_ID_MI_DNAME = 0x11, // Get/Set Mi key: DevNameId, [size]["\0"+miDevName]
	CMD_ID_MI_TBIND = 0x12, // Get/Set Mi keys: Token & Bind, [size][keys]
	CMD_ID_MI_CFG   = 0x13, // Mi cfg data, [size][data]
	CMD_ID_MI_KDEL  = 0x14, // Mi marked as deleted keys, [size][data]
	CMD_ID_MI_KALL  = 0x15, // Get all mi keys
	CMD_ID_MI_REST  = 0x16, // Restore prev mi token & bindkeys
	CMD_ID_MI_CLR	= 0x17, // Delete all mi keys
	CMD_ID_BKEY		= 0x18, // Get/Set beacon bindkey in EEP
	CMD_ID_COMFORT  = 0x20, // Get/Set comfort parameters
	CMD_ID_EXTDATA  = 0x22, // Get/Set show ext. data
	CMD_ID_UTC_TIME = 0x23, // Get/Set utc time (if USE_CLOCK = 1)
	CMD_ID_TADJUST  = 0x24, // Get/Set adjust time clock delta (in 1/16 us for 1 sec)
	CMD_ID_CFS  	= 0x25, // Get/Set sensor config
	CMD_ID_CFS_DEF 	= 0x26, // Get/Set default sensor config
	CMD_ID_MEASURE  = 0x33, // Start/stop notify measures in connection mode
	CMD_ID_LOGGER   = 0x35, // Read memory measures
	CMD_ID_CLRLOG	= 0x36, // Clear memory measures
	CMD_ID_RDS      = 0x40, // Get/Set Reed switch config (DIY devices)
	CMD_ID_TRG      = 0x44, // Get/Set trg and Reed switch data config
	CMD_ID_TRG_OUT  = 0x45, // Get/Set trg out, Send Reed switch and trg data
	CMD_ID_HXC      = 0x49, // Get/Set HX71X config
	CMD_ID_CFG      = 0x55,	// Get/Set device config
	CMD_ID_CFG_DEF  = 0x56,	// Set default device config
	CMD_ID_LCD_DUMP = 0x60, // Get/Set lcd buf
	CMD_ID_LCD_FLG  = 0x61, // Start/Stop notify lcd dump and ...
	CMD_ID_PINCODE  = 0x70, // Set new PinCode 0..999999
	CMD_ID_MTU		= 0x71, // Request MTU Size Exchange (23..255)
	CMD_ID_REBOOT	= 0x72, // Set Reboot on disconnect
	CMD_ID_SET_OTA	= 0x73, // Extension BigOTA: Get/set address and size OTA, erase sectors

	// Debug commands (unsupported in different versions!):

	CMD_ID_OTAC		= 0xD1,	// OTA clear
	CMD_ID_WRFB		= 0xD3,	// Write Flash
	CMD_ID_RDFB		= 0xD4,	// Read Flash Block
	CMD_ID_ERFB		= 0xD5,	// Erase Flash Sector
	CMD_ID_CHGB		= 0xD7,	// Change boot
	CMD_ID_EEP_RW	= 0xDC,	// Get/set EEP
	CMD_ID_LR_RESET = 0xDD,	// Reset Long Range
	CMD_ID_DEBUG    = 0xDE	// Test/Debug

} CMD_ID_KEYS;

// supported services by the device
typedef struct _dev_services_t{
	uint32_t ota: 			1;	//0 OTA
	uint32_t ota_ext:		1;	//1 OTA extension
	uint32_t pincode:		1;	//2 pin-code
	uint32_t bindkey: 		1;	//3 bindkey
	uint32_t history: 		1;	//4 history
	uint32_t screen: 		1;	//5 screen
	uint32_t long_range:	1;	//6 LE Long Range
	uint32_t ths:			1;	//7 T & H sensor
	uint32_t rds:			1;	//8 Reed switch sensor
	uint32_t key:			1;	//9 key
	uint32_t out_pins:		1;	//10 Output pins
	uint32_t inp_pins:		1;	//11 Input pins
	uint32_t time_adj:		1;	//12
	uint32_t hard_rtc:		1;	//13
	uint32_t reserved:		18;
} dev_services_t;


// CMD_ID_DEV_ID
typedef struct _dev_id_t{
	uint8_t pid;			// packet identifier = CMD_ID_DEVID
	uint8_t revision;		// protocol version/revision
	uint16_t hw_version;	// hardware version
	uint16_t sw_version;	// software version (BCD)
	uint16_t dev_spec_data;	// device-specific data
	uint32_t services;		// supported services by the device
} dev_id_t, * pdev_id_t;

#if USE_EXT_OTA  // Compatible BigOTA
	void clear_ota_area(void);
#endif

void cmd_parser(void * p);
