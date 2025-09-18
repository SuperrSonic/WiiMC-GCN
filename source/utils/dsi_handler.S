/* 
 * Copyright (c) 2015-2025, Extrems' Corner.org
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <ppc-asm.h>
#define EXCEPTION_FRAME_END 728

#define SRR0_OFFSET 12
#define SRR1_OFFSET 16
#define GPR0_OFFSET 20
#define GPR1_OFFSET 24
#define GPR2_OFFSET 28
#define GPR3_OFFSET 32
#define GPR4_OFFSET 36
#define GPR5_OFFSET 40
#define GPR6_OFFSET 44
#define GPR7_OFFSET 48
#define GPR8_OFFSET 52
#define GPR9_OFFSET 56
#define GPR10_OFFSET 60
#define GPR11_OFFSET 64
#define GPR12_OFFSET 68
#define GPR13_OFFSET 72
#define GPR14_OFFSET 76
#define GPR15_OFFSET 80
#define GPR16_OFFSET 84
#define GPR17_OFFSET 88
#define GPR18_OFFSET 92
#define GPR19_OFFSET 96
#define GPR20_OFFSET 100
#define GPR21_OFFSET 104
#define GPR22_OFFSET 108
#define GPR23_OFFSET 112
#define GPR24_OFFSET 116
#define GPR25_OFFSET 120
#define GPR26_OFFSET 124
#define GPR27_OFFSET 128
#define GPR28_OFFSET 132
#define GPR29_OFFSET 136
#define GPR30_OFFSET 140
#define GPR31_OFFSET 144
#define CR_OFFSET	 180
#define LR_OFFSET	 184
#define CTR_OFFSET	 188
#define XER_OFFSET	 192
#define MSR_RI				0x00000002

	.extern vm_dsi_handler
	.extern default_exceptionhandler

FUNC_START(dsi_exceptionhandler)
	stwu        sp,-EXCEPTION_FRAME_END(sp)
	stw         r6,GPR6_OFFSET(sp)
	stw         r7,GPR7_OFFSET(sp)
	stw         r8,GPR8_OFFSET(sp)
	stw         r9,GPR9_OFFSET(sp)
	stw         r10,GPR10_OFFSET(sp)
	stw         r11,GPR11_OFFSET(sp)
	stw         r12,GPR12_OFFSET(sp)
	mfdsisr     r4
	mfmsr       r3
	ori         r3,r3,MSR_RI
	mtmsr       r3
	
	mfdsisr		r3
	mfdar		r4
	bl          vm_dsi_handler
	
	# check if it was handled correctly
	cmplwi      r3,0

	lwz         r6,GPR6_OFFSET(sp)
	lwz         r7,GPR7_OFFSET(sp)
	lwz         r8,GPR8_OFFSET(sp)
	lwz         r9,GPR9_OFFSET(sp)
	lwz         r10,GPR10_OFFSET(sp)
	lwz         r11,GPR11_OFFSET(sp)
	lwz         r12,GPR12_OFFSET(sp)

	# clear MSR_RI
	mfmsr       r3
	rlwinm      r3,r3,0,31,29
	mtmsr       r3

	bne         1f
	
	# jump to libogc's default handler
	addi        sp,sp,EXCEPTION_FRAME_END
	b           default_exceptionhandler

1:	
	lwz         r3,CR_OFFSET(sp)
	lwz         r4,LR_OFFSET(sp)
	lwz         r5,CTR_OFFSET(sp)
	lwz         r0,XER_OFFSET(sp)
	mtcr        r3
	mtlr        r4
	mtctr       r5
	mtxer       r0
	lwz         r0,GPR0_OFFSET(sp)
	lwz         r5,GPR5_OFFSET(sp)
	
	lwz         r3,SRR0_OFFSET(sp)
	lwz         r4,SRR1_OFFSET(sp)
	mtsrr0      r3
	mtsrr1      r4
	lwz         r3,GPR3_OFFSET(sp)
	lwz         r4,GPR4_OFFSET(sp)
	lwz         sp,GPR1_OFFSET(sp)
	rfi
FUNC_END(dsi_exceptionhandler)