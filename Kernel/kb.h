#ifndef __KB_H
#define __KB_H

#include "runtime/stdint.h"
#include "runtime/terminal.h"
#include "interrupt_handler.h"

// KB command ports
#define		I86_KB_PORT_COMMAND		0x60


extern "C" {
	extern Terminal term;

	static void kb_callback(regs& r) {
		unsigned char key = __inbyte(I86_KB_PORT_COMMAND);
		PIC_sendEOI(33);
		term << "Key: " << key << "\n";
	}

	void init_kb() {
		install_irq_handler(33, kb_callback);
	}

}
#endif
