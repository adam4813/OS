#ifndef __INTERRUPT_HANDLER_H
#define __INTERRUPT_HANDLER_H

#include <intrin.h>
#include "runtime/stdint.h"
#include "runtime/terminal.h"

//! i86 defines 256 possible interrupt handlers (0-255)
#define I86_MAX_INTERRUPTS		256

//! must be in the format 0D110, where D is descriptor type
#define I86_IDT_DESC_BIT16		0x06	//00000110
#define I86_IDT_DESC_BIT32		0x0E	//00001110
#define I86_IDT_DESC_RING1		0x40	//01000000
#define I86_IDT_DESC_RING2		0x20	//00100000
#define I86_IDT_DESC_RING3		0x60	//01100000
#define I86_IDT_DESC_PRESENT	0x80	//10000000

extern "C" {

	extern Terminal term;

#ifdef _MSC_VER
#pragma pack (push, 1)
#endif

	//! interrupt descriptor
	struct idt_descriptor {
		uint16_t		baseLo; //! bits 0-16 of interrupt routine (ir) address
		uint16_t		sel; //! code selector in gdt
		uint8_t			reserved; //! reserved, shold be 0
		uint8_t			flags; //! bit flags. Set with flags above
		uint16_t		baseMid; //! bits 16-32 of ir address
		uint32_t		baseHi; //! bits 16-32 of ir address
		uint32_t		reserved2; //! bits 16-32 of ir address
	};

	//! describes the structure for the processors idtr register
	struct idtr {
		uint16_t		limit; //! size of the interrupt descriptor table (idt)
		uint64_t		base; //! base address of idt
	};

#ifdef _MSC_VER
#pragma pack (pop, 1)
#endif
	void  _isr0();
	void  _isr1();
	void  _isr2();
	void  _isr3();
	void  _isr4();
	void  _isr5();
	void  _isr6();
	void  _isr7();
	void  _isr8();
	void  _isr9();
	void  _isr10();
	void  _isr11();
	void  _isr12();
	void  _isr13();
	void  _isr14();
	void  _isr15();
	void  _isr16();
	void  _isr17();
	void  _isr18();
	void  _isr19();
	void  _isr20();
	void  _isr21();
	void  _isr22();
	void  _isr23();
	void  _isr24();
	void  _isr25();
	void  _isr26();
	void  _isr27();
	void  _isr28();
	void  _isr29();
	void  _isr30();
	void  _isr31();

	void _irq0();
	void _irq1();
	void _irq2();
	void _irq3();
	void _irq4();
	void _irq5();
	void _irq6();
	void _irq7();
	void _irq8();
	void _irq9();
	void _irq10();
	void _irq11();
	void _irq12();
	void _irq13();
	void _irq14();
	void _irq15();

	/* This defines what the stack looks like after an ISR was running */
	struct regs {
		long double xmm5[2], xmm4[2], xmm3[2], xmm2[2], xmm1[2], xmm0[2];
		uint64_t r11, r10, r9, r8, rdx, rcx, rax;
		uint64_t int_no, err_code;    /* our 'push byte #' and ecodes do this */
	};

	void install_idt(idtr*);
	//! interrupt descriptor table
	static struct idt_descriptor _idt[I86_MAX_INTERRUPTS];

	//! idtr structure used to help define the cpu's idtr register
	static struct idtr _idtr;

	typedef void(*IRQ_GATE)(void);
	int install_irq_gate(uint32_t i, IRQ_GATE irq);

	typedef void(*IRQ_HANLDER)(regs& r);
	int install_irq_handler(uint32_t i, IRQ_HANLDER handler);
	
	//! initialize idt
	int i86_idt_initialize(uint16_t codeSel);

	void isr_wrapper(void);
	void irq_wrapper(void);

	void isr_handler(regs* r);
	void irq_handler(regs* r);
}

#endif
