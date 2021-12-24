/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2018 Samsung Electronics
 * Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * Configuation settings for the Exynos5433 TM2 board.
 */

#ifndef __SAMSUNG_TM2_H
#define __SAMSUNG_TM2_H

#include <asm/arch/cpu.h>
#include <linux/sizes.h>

/* High Level Configuration Options */
#define CONFIG_SAMSUNG			/* in a SAMSUNG core */
#define CONFIG_EXYNOS5433		/* Exynos5433 Family */
#define CONFIG_S5P

/* Timer input clock frequency */
#define COUNTER_FREQUENCY		24000000

/* SD/MMC configuration */
#define CONFIG_BOUNCE_BUFFER

/* THOR */
#define CONFIG_G_DNL_THOR_VENDOR_NUM	CONFIG_USB_GADGET_VENDOR_NUM
#define CONFIG_G_DNL_THOR_PRODUCT_NUM	0x685D

/* required to avoid build break */
#define CONFIG_G_DNL_UMS_VENDOR_NUM	CONFIG_USB_GADGET_VENDOR_NUM
#define CONFIG_G_DNL_UMS_PRODUCT_NUM	0xA4A5

#define PHYS_SDRAM_1			0x20000000
#define PHYS_SDRAM_1_SIZE		0xbf700000

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1
#define CONFIG_SYS_INIT_SP_ADDR	(CONFIG_SYS_SDRAM_BASE + 0x7fff0)
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x80000)

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(80 << 20)
#define CONFIG_SYS_BOOTM_LEN		(130 << 20)

/* Initial environment variables */
#define CONFIG_BOOTCOMMAND		"run modedetect"
#define CONFIG_EXTRA_ENV_SETTINGS	"dfu_alt_info=kernel part 0 9 offset 0x400;rootfs part 0 18;system-data part 0 19;user part 0 21\0" \
					"modedetect=if gpio input gpa21 || itest.l *0x105c080c == 0x12345671; then run download; else run bootkernel; fi; reset\0" \
					"fdt_high=0xffffffffffffffff\0" \
					"bootargs=console=ttySAC1,115200 earlycon=exynos4210,0x14C20000 ess_setup=0x26000000 loglevel=7 root=/dev/mmcblk0p18 rootfstype=ext4 rootwait\0" \
					"bootkernel=echo Booting kernel; run boarddetect; run loadkernel; bootm 0x30080000#$board\0" \
					"boarddetect=if itest.l *0x138000b4 == 0x0063f9ff; then setenv board tm2e; elif itest.l *0x138000b4 == 0x0059f9ff; then setenv board tm2; else setenv board unknown; fi; echo Detected $board board\0" \
					"loadkernel=part start mmc 0 9 kernel_sect; part size mmc 0 9 kernel_size; mmc read 0x30000000 $kernel_sect $kernel_size\0" \
					"muicsetusb=i2c dev 0; i2c mw 25 c 9; i2c mw 25 d 3b; i2c mw 25 e 05; i2c mw 25 16 10\0" \
					"displayimg=unzip 200d0000 67000000; mw.l 138000b4 0059f9ff; mw.l 138001a0 67e10000; mw.l 13800200 00001680; mw.l 13801410 1; mw.l 13802040 e0000018; sleep 1; mw.l 13802040 e0000008\0" \
					"download=echo Thor mode enabled; run muicsetusb; run displayimg; mw.l 0x105c080c 0; thor 0 mmc 0\0"

#define CONFIG_ENV_SIZE			0x1000

#endif /* __SAMSUNG_TM2_H */
