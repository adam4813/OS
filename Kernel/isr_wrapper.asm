bits 64

segment .text
	global isr_wrapper
	extern isr_handler
	extern irq_handler

	global _isr0
	global _isr1
	global _isr2
	global _isr3
	global _isr4
	global _isr5
	global _isr6
	global _isr7
	global _isr8
	global _isr9
	global _isr10
	global _isr11
	global _isr12
	global _isr13
	global _isr14
	global _isr15
	global _isr16
	global _isr17
	global _isr18
	global _isr19
	global _isr20
	global _isr21
	global _isr22
	global _isr23
	global _isr24
	global _isr25
	global _isr26
	global _isr27
	global _isr28
	global _isr29
	global _isr30
	global _isr31

	global _irq0
	global _irq1
	global _irq2
	global _irq3
	global _irq4
	global _irq5
	global _irq6
	global _irq7
	global _irq8
	global _irq9
	global _irq10
	global _irq11
	global _irq12
	global _irq13
	global _irq14
	global _irq15

;	0: Divide By Zero Exception
_isr0:
	;cli
	push byte 0		; A normal ISR stub that pops a dummy error code to keep a
					; uniform stack frame
	push byte 0
	jmp isr_wrapper

;	1: Debug Exception
_isr1:
	;cli
	push byte 0
	push byte 1
	jmp isr_wrapper

;	2: Non Maskable Interrupt Exception
_isr2:
	;cli
	push byte 0
	push byte 2
	jmp isr_wrapper

;	3: Breakpoint Exception
_isr3:
	;cli
	push byte 0
	push byte 3
	jmp isr_wrapper

;	4: Into Detected Overflow Exception
_isr4:
	;cli
	push byte 0
	push byte 4
	jmp isr_wrapper

;	5: Out of Bounds Exception
_isr5:
	;cli
	push byte 0
	push byte 5
	jmp isr_wrapper

;	6: Invalid Opcode Exception
_isr6:
	;cli
	push byte 0
	push byte 6

	jmp isr_wrapper

;	7: No Coprocessor Exception
_isr7:
	;cli
	push byte 0
	push byte 7
	jmp isr_wrapper

;	8: Double Fault Exception (With Error Code!)
_isr8:
	;cli
	push byte 8
	jmp isr_wrapper

;	9: Coprocessor Segment Overrun Exception
_isr9:
	;cli
	push byte 0
	push byte 9
	jmp isr_wrapper

;	10: Bad TSS Exception (With Error Code!)
_isr10:
	;cli
	push byte 10
	jmp isr_wrapper

;	11: Segment Not Present Exception (With Error Code!)
_isr11:
	;cli
	push byte 11
	jmp isr_wrapper

;	12: Stack Fault Exception (With Error Code!)
_isr12:
	;cli
	push byte 12
	jmp isr_wrapper

;	13: General Protection Fault Exception (With Error Code!)
_isr13:
	;cli
	push byte 13
	jmp isr_wrapper

;	14: Page Fault Exception (With Error Code!)
_isr14:
	;cli
	push byte 14
	jmp isr_wrapper

;	15: Unknown Interrupt Exception
_isr15:
	;cli
	push byte 0
	push byte 15
	jmp isr_wrapper

;	16: Coprocessor Fault Exception
_isr16:
	;cli
	push byte 0
	push byte 16
	jmp isr_wrapper

;	17: Alignment Check Exception
_isr17:
	;cli
	push byte 0
	push byte 17
	jmp isr_wrapper

;	18: Machine Check Exception
_isr18:
	;cli
	push byte 0
	push byte 18
	jmp isr_wrapper

;	19: Reserved
_isr19:
	;cli
	push byte 0
	push byte 19
	jmp isr_wrapper

;	20: Reserved
_isr20:
	;cli
	push byte 0
	push byte 20
	jmp isr_wrapper

;	21: Reserved
_isr21:
	;cli
	push byte 0
	push byte 21
	jmp isr_wrapper

;	22: Reserved
_isr22:
	;cli
	push byte 0
	push byte 22
	jmp isr_wrapper

;	23: Reserved
_isr23:
	;cli
	push byte 0
	push byte 23
	jmp isr_wrapper

;	24: Reserved
_isr24:
	;cli
	push byte 0
	push byte 24
	jmp isr_wrapper

;	25: Reserved
_isr25:
	;cli
	push byte 0
	push byte 25
	jmp isr_wrapper

;	26: Reserved
_isr26:
	;cli
	push byte 0
	push byte 26
	jmp isr_wrapper

;	27: Reserved
_isr27:
	;cli
	push byte 0
	push byte 27
	jmp isr_wrapper

;	28: Reserved
_isr28:
	;cli
	push byte 0
	push byte 28
	jmp isr_wrapper

;	29: Reserved
_isr29:
	;cli
	push byte 0
	push byte 29
	jmp isr_wrapper

;	30: Reserved
_isr30:
	;cli
	push byte 0
	push byte 30
	jmp isr_wrapper

;	31: Reserved
_isr31:
	;cli
	push byte 0
	push byte 31
	jmp isr_wrapper

; 32: IRQ0
_irq0:
	;cli
	push byte 0
	push byte 32
	jmp irq_wrapper

_irq1:
	;cli
	push byte 0
	push byte 33
	jmp irq_wrapper

_irq2:
	;cli
	push byte 0
	push byte 34
	jmp irq_wrapper;

_irq3:
	;cli
	push byte 0
	push byte 35
	jmp irq_wrapper;

_irq4:
	;cli
	push byte 0
	push byte 36
	jmp irq_wrapper;

_irq5:
	;cli
	push byte 0
	push byte 37
	jmp irq_wrapper;

_irq6:
	;cli
	push byte 0
	push byte 38
	jmp irq_wrapper;

_irq7:
	;cli
	push byte 0
	push byte 39
	jmp irq_wrapper;

_irq8:
	;cli
	push byte 0
	push byte 40
	jmp irq_wrapper

_irq9:
	;cli
	push byte 0
	push byte 41
	jmp irq_wrapper

_irq10:
	;cli
	push byte 0
	push byte 42
	jmp irq_wrapper

_irq11:
	;cli
	push byte 0
	push byte 43
	jmp irq_wrapper

_irq12:
	;cli
	push byte 0
	push byte 44
	jmp irq_wrapper

_irq13:
	;cli
	push byte 0
	push byte 45
	jmp irq_wrapper

_irq14:
	;cli
	push byte 0
	push byte 46
	jmp irq_wrapper

_irq15:
	;cli
	push byte 0
	push byte 47
	jmp irq_wrapper

isr_wrapper:
	sub rsp, 16 * 6 + 8 * 7 + 32		;allocate room for 7 general regs,
										;6 xmm, and 32 bytes for visual c++ regsiter spill
	mov [rsp + 32 + 96 + 8 * 6], rax	;save current rax
	mov [rsp + 32 + 96 + 8 * 5], rcx	;save current rcx
	mov [rsp + 32 + 96 + 8 * 4], rdx	;save current rdx
	mov [rsp + 32 + 96 + 8 * 3], r8		;save current r8
	mov [rsp + 32 + 96 + 8 * 2], r9		;save current r9
	mov [rsp + 32 + 96 + 8], r10		;save current r10
	mov [rsp + 32 + 96], r11			;save current r11

	movdqa [rsp + 32 + 16 * 5], xmm0	;save current xmm0
	movdqa [rsp + 32 + 16 * 4], xmm1	;save current xmm1
	movdqa [rsp + 32 + 16 * 3], xmm2	;save current xmm2
	movdqa [rsp + 32 + 16 * 2], xmm3	;save current xmm3
	movdqa [rsp + 32 + 16], xmm4		;save current xmm4
	movdqa [rsp + 32], xmm5				;save current xmm5

	lea rcx, [rsp + 32]
	mov rbp, rsp
	and rsp, ~0xF
	call isr_handler
	mov rsp, rbp
	
	movdqa xmm5, [rsp + 32]				;restore current xmm5
	movdqa xmm4, [rsp + 32 + 16]		;restore current xmm4
	movdqa xmm3, [rsp + 32 + 16 * 2]	;restore current xmm3
	movdqa xmm2, [rsp + 32 + 16 * 3]	;restore current xmm2
	movdqa xmm1, [rsp + 32 + 16 * 4]	;restore current xmm1
	movdqa xmm0, [rsp + 32 + 16 * 5]	;restore current xmm0
	
	mov r11, [rsp + 32 + 96]			;restore current r11
	mov r10, [rsp + 32 + 96 + 8]		;restore current r10
	mov r9,	[rsp + 32 + 96 + 8 * 2]		;restore current r9
	mov r8,	[rsp + 32 + 96 + 8 * 3]		;restore current r8
	mov rdx, [rsp + 32 + 96 + 8 * 4]	;restore current rdx
	mov rcx, [rsp + 32 + 96 + 8 * 5]	;restore current rcx
	mov rax, [rsp + 32 + 96 + 8 * 6]	;restore current rax

	add rsp, 16 * 6 + 8 * 7 + 32 + 16	;allocate room for 7 general regs, 6 xmm,
										;and 32 bytes for visual c++ regsiter spill and
										;the 2 extra data stores in the irq/isr stub

	iretq

irq_wrapper:
	sub rsp, 16 * 6 + 8 * 7 + 32		;allocate room for 7 general regs,
										;6 xmm, and 32 bytes for visual c++ regsiter spill
	mov [rsp + 32 + 96 + 8 * 6], rax	;save current rax
	mov [rsp + 32 + 96 + 8 * 5], rcx	;save current rcx
	mov [rsp + 32 + 96 + 8 * 4], rdx	;save current rdx
	mov [rsp + 32 + 96 + 8 * 3], r8		;save current r8
	mov [rsp + 32 + 96 + 8 * 2], r9		;save current r9
	mov [rsp + 32 + 96 + 8], r10		;save current r10
	mov [rsp + 32 + 96], r11			;save current r11

	movdqa [rsp + 32 + 16 * 5], xmm0	;save current xmm0
	movdqa [rsp + 32 + 16 * 4], xmm1	;save current xmm1
	movdqa [rsp + 32 + 16 * 3], xmm2	;save current xmm2
	movdqa [rsp + 32 + 16 * 2], xmm3	;save current xmm3
	movdqa [rsp + 32 + 16], xmm4		;save current xmm4
	movdqa [rsp + 32], xmm5				;save current xmm5

	lea rcx, [rsp + 32]
	mov rbp, rsp
	and rsp, ~0xF
	call irq_handler
	mov rsp, rbp
	
	movdqa xmm5, [rsp + 32]				;restore current xmm5
	movdqa xmm4, [rsp + 32 + 16]		;restore current xmm4
	movdqa xmm3, [rsp + 32 + 16 * 2]	;restore current xmm3
	movdqa xmm2, [rsp + 32 + 16 * 3]	;restore current xmm2
	movdqa xmm1, [rsp + 32 + 16 * 4]	;restore current xmm1
	movdqa xmm0, [rsp + 32 + 16 * 5]	;restore current xmm0
	
	mov r11, [rsp + 32 + 96]			;restore current r11
	mov r10, [rsp + 32 + 96 + 8]		;restore current r10
	mov r9,	[rsp + 32 + 96 + 8 * 2]		;restore current r9
	mov r8,	[rsp + 32 + 96 + 8 * 3]		;restore current r8
	mov rdx, [rsp + 32 + 96 + 8 * 4]	;restore current rdx
	mov rcx, [rsp + 32 + 96 + 8 * 5]	;restore current rcx
	mov rax, [rsp + 32 + 96 + 8 * 6]	;restore current rax

	add rsp, 16 * 6 + 8 * 7 + 32 + 16	;allocate room for 7 general regs, 6 xmm,
										;and 32 bytes for visual c++ regsiter spill and
										;the 2 extra data stores in the irq/isr stub

	iretq
