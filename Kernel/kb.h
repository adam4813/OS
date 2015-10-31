#ifndef __KB_H
#define __KB_H

#include "runtime/stdint.h"
#include "runtime/terminal.h"
#include "interrupt_handler.h"

// KB command ports
#define		I86_KB_DATA_PORT			0x60
#define		I86_KB_READ_STATUS_PORT		0x64
#define		I86_KB_WRITE_COMMAND_PORT	0x64
#define		I86_KB_IRQ					33
#define		I86_KB_SCAN_CODE_COMMAND	0xF0


extern "C" {
	extern Terminal term;

	static void kb_callback(regs& r) {
		unsigned char key = __inbyte(I86_KB_DATA_PORT);
		PIC_sendEOI(I86_KB_IRQ);
		term << "Key: " << key << "\n";
	}

	void init_kb() {;
		install_irq_handler(I86_KB_IRQ, kb_callback);
		__outbyte(I86_KB_WRITE_COMMAND_PORT, I86_KB_SCAN_CODE_COMMAND);
		unsigned char status = __inbyte(I86_KB_READ_STATUS_PORT);
		term << "KB init status: " << status << "\n";
		//if (status & 0x01) {

		//}
		//unsigned char response = __inbyte(I86_KB_DATA_PORT);
	}

}
#endif
