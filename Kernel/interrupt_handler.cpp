#include "interrupt_handler.h"
#include "runtime/stdint.h"
#include "runtime/terminal.h"
#include "runtime/itoa.h"

extern "C" {

#define ICW1 0x11
#define ICW4 0x01

	void irq_remap(uint8_t pic1, uint8_t pic2) {
		/* send ICW1 */
		__outbyte(PIC1_CMD, ICW1);
		__outbyte(PIC2_CMD, ICW1);

		/* send ICW2 */
		__outbyte(PIC1_DATA, pic1);
		__outbyte(PIC2_DATA, pic2);

		/* send ICW3 */
		__outbyte(PIC1_DATA, 4);
		__outbyte(PIC2_DATA, 2);

		/* send ICW4 */
		__outbyte(PIC1_DATA, ICW4);
		__outbyte(PIC2_DATA, ICW4);

		/* disable all IRQs */
		__outbyte(PIC1_DATA, 0x0);
		__outbyte(PIC2_DATA, 0x0);
	}

	void irq_set_mask(unsigned char IRQline) {
		uint16_t port;
		uint8_t value;

		if (IRQline < 8) {
			port = PIC1_DATA;
		}
		else {
			port = PIC2_DATA;
			IRQline -= 8;
		}
		value = __inbyte(port) | (1 << IRQline);
		__outbyte(port, value);
	}

	void irq_clear_mask(unsigned char IRQline) {
		uint16_t port;
		uint8_t value;

		if (IRQline < 8) {
			port = PIC1_DATA;
		}
		else {
			port = PIC2_DATA;
			IRQline -= 8;
		}
		value = __inbyte(port) & ~(1 << IRQline);
		__outbyte(port, value);
	}

	int install_irq_gate(uint32_t i, IRQ_GATE irq) {
		if (i > I86_MAX_INTERRUPTS) {
			return 0;
		}

		if (!irq) {
			return 0;
		}

		//! get base address of interrupt handler
		uint64_t uiBase = (uint64_t)&(*irq);

		//! store base address into idt
		_idt[i].baseLo = uiBase & 0xffff;
		_idt[i].baseMid = (uiBase >> 16) & 0xffff;
		_idt[i].baseHi = (uiBase >> 32) & 0xffff;
		_idt[i].reserved = 0;
		_idt[i].flags = I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32 | I86_IDT_DESC_RING3;
		_idt[i].sel = 0x8;

		return	0;
	}
	IRQ_HANLDER hanlders[256] = { 0 };

	int install_irq_handler(uint32_t i, IRQ_HANLDER hanlder) {
		if (i > I86_MAX_INTERRUPTS) {
			return 0;
		}

		if (!hanlder) {
			return 0;
		}

		hanlders[i] = hanlder;

		return	0;
	}

	//! initialize idt
	int i86_idt_initialize(uint16_t codeSel) {

		//! set up idtr for processor
		_idtr.limit = sizeof(struct idt_descriptor) * I86_MAX_INTERRUPTS - 1;
		_idtr.base = (uint64_t)&_idt[0];

		memset((unsigned char*)&_idt[0], 0, sizeof(idt_descriptor)* I86_MAX_INTERRUPTS - 1);

		irq_remap(0x20, 0x28);

		//! null out the idt
		install_irq_gate(0, _isr0);
		install_irq_gate(1, _isr1);
		install_irq_gate(2, _isr2);
		install_irq_gate(3, _isr3);
		install_irq_gate(4, _isr4);
		install_irq_gate(5, _isr5);
		install_irq_gate(6, _isr6);
		install_irq_gate(7, _isr7);
		install_irq_gate(8, _isr8);
		install_irq_gate(9, _isr9);
		install_irq_gate(10, _isr10);
		install_irq_gate(11, _isr11);
		install_irq_gate(12, _isr12);
		install_irq_gate(13, _isr13);
		install_irq_gate(14, _isr14);
		install_irq_gate(15, _isr15);
		install_irq_gate(16, _isr16);
		install_irq_gate(17, _isr17);
		install_irq_gate(18, _isr18);
		install_irq_gate(19, _isr19);
		install_irq_gate(20, _isr20);
		install_irq_gate(21, _isr21);
		install_irq_gate(22, _isr22);
		install_irq_gate(23, _isr23);
		install_irq_gate(24, _isr24);
		install_irq_gate(25, _isr25);
		install_irq_gate(26, _isr26);
		install_irq_gate(27, _isr27);
		install_irq_gate(28, _isr28);
		install_irq_gate(29, _isr29);
		install_irq_gate(30, _isr30);
		install_irq_gate(31, _isr31);
		install_irq_gate(32, _irq0);
		install_irq_gate(33, _irq1);
		install_irq_gate(34, _irq2);
		install_irq_gate(35, _irq3);
		install_irq_gate(36, _irq4);
		install_irq_gate(37, _irq5);
		install_irq_gate(38, _irq6);
		install_irq_gate(39, _irq7);
		install_irq_gate(40, _irq8);
		install_irq_gate(41, _irq9);
		install_irq_gate(42, _irq10);
		install_irq_gate(43, _irq11);
		install_irq_gate(44, _irq12);
		install_irq_gate(45, _irq13);
		install_irq_gate(46, _irq14);
		install_irq_gate(47, _irq15);

		//! register default handlers
		for (unsigned int i = 48; i < I86_MAX_INTERRUPTS; i++)
			install_irq_gate(i, isr_wrapper);

		//! install our idt
		__lidt(&_idtr);
		_enable();

		irq_clear_mask(0);
		irq_clear_mask(1);
		__outbyte(0x60, 0xF4);

		return 0;
	}

	/* This is a simple string array. It contains the message that
	*  corresponds to each and every exception. We get the correct
	*  message by accessing like:
	*  exception_message[interrupt_number] */
	char *exception_messages[] =
	{
		"Division By Zero",
		"Debug",
		"Non Maskable Interrupt",
		"Breakpoint",
		"Into Detected Overflow",
		"Out of Bounds",
		"Invalid Opcode",
		"No Coprocessor",
		"Double Fault",
		"Coprocessor Segment Overrun",
		"Bad TSS",
		"Segment Not Present",
		"Stack Fault",
		"General Protection Fault",
		"Page Fault",
		"Unknown Interrupt",
		"Coprocessor Fault",
		"Alignment Check",
		"Machine Check",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved"
	};

	void isr_handler(regs* r) {
		term << "Default ISR for: " << r->int_no;
		/* Is this a fault whose number is from 0 to 31? */
		if (r->int_no < 32) {
			/* Display the description for the Exception that occurred.
			*  In this tutorial, we will simply halt the system using an
			*  infinite loop */
			term << " " << exception_messages[r->int_no] << " Exception. System Halted!\n";
			for (;;);
		}
	}

	void irq_handler(regs* r) {
		// Spurious IRQ check on line 7.
		if (r->int_no == 39) {
			uint16_t isr = pic_get_isr();
			if (!(isr & 0x7)) {
				return;
			}
		}
		// Spurious IRQ check on line 15.
		if (r->int_no == 47) {
			uint16_t isr = pic_get_isr();
			if (!(isr & 0xF)) {
				return;
			}
		}
		if (hanlders[r->int_no] != 0) {
			(hanlders[r->int_no])(*r);
		}
		else {
			term << "Default IRQ for: " << r->int_no << "\n";
			/*term << "RAX: " << r->rax << " RCX: " << r->rcx <<  " R8: " << r->r8 << " R9: " << r->r9 << " R10: " << r->r10 << " R11: " << r->r11 << "\n";*/
		}
		PIC_sendEOI(r->int_no);
	}

	void PIC_sendEOI(unsigned char irq) {
		if ((irq - 32) >= 8) {
			__outbyte(PIC2_CMD, PIC_EOI);
		}

		__outbyte(PIC1_CMD, PIC_EOI);
	}

	static uint16_t __pic_get_irq_reg(int ocw3) {
		/* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
		* represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
		__outbyte(PIC1_CMD, ocw3);
		__outbyte(PIC2_CMD, ocw3);
		return (__inbyte(PIC2_CMD) << 8) | __inbyte(PIC1_CMD);
	}

	/* Returns the combined value of the cascaded PICs irq request register */
	uint16_t pic_get_irr(void) {
		return __pic_get_irq_reg(PIC_READ_IRR);
	}

	/* Returns the combined value of the cascaded PICs in-service register */
	uint16_t pic_get_isr(void) {
		return __pic_get_irq_reg(PIC_READ_ISR);
	}
}
