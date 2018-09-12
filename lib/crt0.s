
	.equ	SRAM_BASE,	0x20000000
	.equ	SRAM_SIZE,	0x400
	.equ	STACKPTR,	SRAM_BASE+SRAM_SIZE

.thumb
.syntax unified
.cpu cortex-m0
.section "vectors"

@vector table cortex-m0 standard
	.long	STACKPTR		@ 0x0000: stackpointer (top of ram)
	.long	_start+1		@ 0x0004: reset	
	.long	nmi_handler+1		@ 0x0008: NMI
	.long	hf_handler+1		@ 0x000C: Hardfault
	.long	0			@ 0x0010
	.long	0			@ 0x0014
	.long	0			@ 0x0018
	.long	0			@ 0x001C
	.long	0			@ 0x0020
	.long	0			@ 0x0024
	.long	0			@ 0x0028
	.long	svc_handler+1		@ 0x002C: SVC
	.long	0			@ 0x0030
	.long	0			@ 0x0034
	.long	pendsv_handler+1	@ 0x0038: PendSV
	.long	systick_handler+1	@ 0x003C: systick

@ SWM050 specific IRQs
	.long	TMRSE0_handler+1	@ 0x0040: TMRSE0
	.long	TMRSE1_handler+1	@ 0x0044: TMRSE1
	.long	WDT_handler+1		@ 0x0048: WDT
	.long	ACMP_handler+1		@ 0x004C: ACMP
	.long	GPIO0_handler+1		@ 0x0050: GPIO0
	.long	GPIO1_handler+1		@ 0x0054: GPIO1
	.long	GPIO2_handler+1		@ 0x0058: GPIO2
	.long	GPIO3_handler+1		@ 0x005C: GPIO3
	.long	GPIO4_handler+1		@ 0x0060: GPIO4
	.long	GPIO5_handler+1		@ 0x0064: GPIO5
	.long	GPIO6_handler+1		@ 0x0068: GPIO6
	.long	GPIO7_handler+1		@ 0x006C: GPIO7
	.long	GPIO8_handler+1		@ 0x0070: GPIO8
	.long	GPIO9_handler+1		@ 0x0074: GPIO9
	.long	0			@ 0x0078
	.long	0			@ 0x007C

.section "protection"
	.long	0xFFFFFFFF		@ 0 = SWD enabled, ISP enabled
@ 	.long	0xABCD1234 		@ 0xABCD1234 = SWD are GPIO, but SWD can be enabled through ISP
@	.long	0xD1C2B3A4		@ 0xD1C2B3A4 = no SWD, no ISP

@ startup code and standard isr are here
.thumb_func
.section "crt0"

@ load the main function
@ TODO: setup stackpointer
@ TODO: empty bss
@ TODO: copy var
_start:	
	ldr	r0, =end_rom		@ copy preinitialized vars to ram
	ldr	r1, =start_ram
	ldr	r2, =data_size
	cmp	r2, #0			@ do we have something to copy?
	beq	initbss	
copy:	
	ldrb	r4, [r0]
	adds	r0, r0, #1	
	strb	r4, [r1]	
	adds	r1, r1, #1
	subs	r2, r2, #1
	bne	copy
initbss:				@ zero bss section
	ldr	r0, =sbss
	ldr	r2, =bss_size
	cmp	r2, #0			@ anything to zero out?
	beq	startmain
	movs	r4, #0
zero:
	strb	r4, [r0]
	adds	r0, r0, #1
	subs	r2, r2, #1
	bne	zero
startmain:				@ jump to main
	ldr	r0, =main+1
	bx	r0
	b	.

@ NMI handler
.weak nmi_handler
nmi_handler:
	b	.

@ hardfault handler
.weak hf_handler
hf_handler:
	b	.

@ svc handler
.weak svc_handler
svc_handler:
	b	.

@ pendsv handler
.weak pendsv_handler
pendsv_handler:
	b	.

@ systick handler
.weak systick_handler
systick_handler:
	b 	.

@ TMRSE0 handler
.weak TMRSE0_handler
TMRSE0_handler:
	b	.

@ TMRSE1 handler
.weak TMRSE1_handler
TMRSE1_handler:
	b	.

@ WDT handler
.weak WDT_handler
WDT_handler:
	b	.

@ ACMP handler
.weak ACMP_handler
ACMP_handler:
	b	.

@ GPIO0 handler
.weak GPIO0_handler
GPIO0_handler:
	b	.

@ GPIO1 handler
.weak GPIO1_handler
GPIO1_handler:
	b	.

@ GPIO2 handler
.weak GPIO2_handler
GPIO2_handler:
	b	.

@ GPIO3 handler
.weak GPIO3_handler
GPIO3_handler:
	b	.

@ GPIO4 handler
.weak GPIO4_handler
GPIO4_handler:
	b	.

@ GPIO5 handler
.weak GPIO5_handler
GPIO5_handler:
	b	.

@ GPIO6 handler
.weak GPIO6_handler
GPIO6_handler:
	b	.

@ GPIO7 handler
.weak GPIO7_handler
GPIO7_handler:
	b	.

@ GPIO8 handler
.weak GPIO8_handler
GPIO8_handler:
	b	.

@ GPIO9 handler
.weak GPIO9_handler
GPIO9_handler:
	b	.






