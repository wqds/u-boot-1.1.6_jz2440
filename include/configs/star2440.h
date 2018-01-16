
#ifndef __STAR2440_H
#define  __STAR2440_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_ARM920T		1	/* This is an ARM920T Core	*/
#define CONFIG_SMDK2410		1	/* on a SAMSUNG SMDK2410 Board  此处不要删除，否则会提示很多错误*/

#define	CONFIG_S3C2410		1	/* in a SAMSUNG S3C2410 SoC    此处不要改成CONFIG_S3C2440，否则会提示很多错误 */
#define CONFIG_STAR2440		1	

/* input clock of PLL */
#define CONFIG_SYS_CLK_FREQ	12000000/* the STAR2440 has 12MHz input clock */


#define USE_920T_MMU		1
#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff */

/*
 * Size of malloc() pool
 */
#define CFG_MALLOC_LEN		(CFG_ENV_SIZE + 128*1024)
#define CFG_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

/*
 * Hardware drivers
 */
#define CONFIG_DRIVER_CS8900	1	/* we have a CS8900 on-board */
#define CS8900_BASE		0x19000300
#define CS8900_BUS16		1 /* the Linux driver does accesses as shorts */

/*
 * select serial console configuration
 */
#define CONFIG_SERIAL1          1	/* we use SERIAL 1 on SMDK2410 */

/************************************************************
 * RTC
 ************************************************************/
#define	CONFIG_RTC_S3C24X0	1

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_BAUDRATE		115200

/***********************************************************
 * Command definition
 ***********************************************************/
#define CONFIG_COMMANDS \
			(CONFIG_CMD_DFL	 | \
			CFG_CMD_CACHE	 | \
			CFG_CMD_NAND	 | \
			/*CFG_CMD_EEPROM |*/ \
			/*CFG_CMD_I2C	 |*/ \
			/*CFG_CMD_USB	 |*/ \
			CFG_CMD_REGINFO  | \
			CFG_CMD_DATE	 | \
			CFG_CMD_ELF)

/* this must be included AFTER the definition of CONFIG_COMMANDS (if any) */
#include <cmd_confdefs.h>

#define CONFIG_BOOTDELAY	5
#define CONFIG_BOOTARGS    	"root=ramfs devfs=mount console=ttySA0,115200"
/*#define CONFIG_ETHADDR	08:00:3e:26:0a:5b */
#define CONFIG_NETMASK          255.255.255.0
#define CONFIG_IPADDR		192.168.3.11
#define CONFIG_SERVERIP		192.168.3.2
/*#define CONFIG_BOOTFILE	"elinos-lart" */
/*#define CONFIG_BOOTCOMMAND	"tftp; bootm" */

#if (CONFIG_COMMANDS & CFG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	115200		/* speed to run kgdb serial port */
/* what's this ? it's not used anywhere */
#define CONFIG_KGDB_SER_INDEX	1		/* which serial port to use */
#endif

/*
 * Miscellaneous configurable options
 */
#define	CFG_LONGHELP				/* undef to save memory		*/
#define	CFG_PROMPT		"STAR2440 # "	/* Monitor Command Prompt	*/
#define	CFG_CBSIZE		256		/* Console I/O Buffer Size	*/
#define	CFG_PBSIZE (CFG_CBSIZE+sizeof(CFG_PROMPT)+16) /* Print Buffer Size */
#define	CFG_MAXARGS		16		/* max number of command args	*/
#define CFG_BARGSIZE		CFG_CBSIZE	/* Boot Argument Buffer Size	*/

#define CFG_MEMTEST_START	0x30000000	/* memtest works on	*/
#define CFG_MEMTEST_END		0x33F00000	/* 63 MB in DRAM	*/

#undef  CFG_CLKS_IN_HZ		/* everything, incl board info, in Hz */

#define	CFG_LOAD_ADDR		0x33000000	/* default load address	*/

/* the PWM TImer 4 uses a counter of 15625 for 10 ms, so we need */
/* it to wrap 100 times (total 1562500) to get 1 sec. */
#define	CFG_HZ			1562500

/* valid baudrates */
#define CFG_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE	(128*1024)	/* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS	1	   /* we have 1 bank of DRAM */
#define PHYS_SDRAM_1		0x30000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x04000000 /* 64 MB */

#define PHYS_FLASH_1		0x00000000 /* Flash Bank #1 */

#define CFG_FLASH_BASE		PHYS_FLASH_1

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#if 0
#define CONFIG_AMD_LV400	1	/* uncomment this if you have a LV400 flash */
#define CONFIG_AMD_LV800	1	/* uncomment this if you have a LV800 flash */
#endif

#define CONFIG_MX_LV160 1    /* uncomment this if you have a LV160 flash */

#define CFG_MAX_FLASH_BANKS	1	/* max number of memory banks */
#ifdef CONFIG_AMD_LV800
#define PHYS_FLASH_SIZE		0x00100000 /* 1MB */
#define CFG_MAX_FLASH_SECT	(19)	/* max number of sectors on one chip */
#define CFG_ENV_ADDR		(CFG_FLASH_BASE + 0x0F0000) /* addr of environment */
#endif
#ifdef CONFIG_AMD_LV400
#define PHYS_FLASH_SIZE		0x00080000 /* 512KB */
#define CFG_MAX_FLASH_SECT	(11)	/* max number of sectors on one chip */
#define CFG_ENV_ADDR		(CFG_FLASH_BASE + 0x070000) /* addr of environment */
#endif
#ifdef CONFIG_MX_LV160
#define PHYS_FLASH_SIZE		0x00200000 /* 2MB */
#define CFG_MAX_FLASH_SECT	(35)	/* max number of sectors on one chip */
#define CFG_ENV_ADDR		(CFG_FLASH_BASE + 0x0F0000) /* addr of environment */
#endif

/* timeout values are in ticks */
#define CFG_FLASH_ERASE_TOUT	(5*CFG_HZ) /* Timeout for Flash Erase */
#define CFG_FLASH_WRITE_TOUT	(5*CFG_HZ) /* Timeout for Flash Write */

#define	CFG_ENV_IS_IN_FLASH	1
//#define     CFG_ENV_IS_IN_NAND 1

#define CFG_ENV_SIZE		0x10000	/* Total Size of Environment Sector */


/*nand*/
#define NAND_MAX_CHIPS 1
#define CFG_MAX_NAND_DEVICE 1
#define CFG_NAND_BASE 1 



#endif	/* __CONFIG_H */
