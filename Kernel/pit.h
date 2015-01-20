#ifndef __PIT_H
#define __PIT_H

#include "runtime/stdint.h"
#include "runtime/terminal.h"
#include "interrupt_handler.h"

// PIT command ports
#define		I86_PIT_PORT_COUNTER0		0x40
#define		I86_PIT_PORT_COUNTER1		0x41
#define		I86_PIT_PORT_COUNTER2		0x42
#define		I86_PIT_PORT_COMMAND		    0x43


// PIT command word bits
#define		I86_PIT_OCW_BINCOUNT_BINARY 	0x0	//0
#define		I86_PIT_OCW_BINCOUNT_BCD		0x1	//1
#define		I86_PIT_OCW_MODE_TERMINALCOUNT	0x0	//0000
#define		I86_PIT_OCW_MODE_ONESHOT		0x2	//0010
#define		I86_PIT_OCW_MODE_RATEGEN		0x4	//0100
#define		I86_PIT_OCW_MODE_SQUAREWAVEGEN	0x6	//0110
#define		I86_PIT_OCW_MODE_SOFTWARETRIG	0x8	//1000
#define		I86_PIT_OCW_MODE_HARDWARETRIG	0xA	//1010
#define		I86_PIT_OCW_RL_LATCH			0x0	//000000
#define		I86_PIT_OCW_RL_LSBONLY			0x10//010000
#define		I86_PIT_OCW_RL_MSBONLY			0x20//100000
#define		I86_PIT_OCW_RL_DATA				0x30//110000
#define		I86_PIT_OCW_COUNTER_0			0x0	//00000000
#define		I86_PIT_OCW_COUNTER_1			0x40//01000000
#define		I86_PIT_OCW_COUNTER_2			0x80//10000000


extern "C" {
	extern Terminal term;

	uint32_t tick = 0;

	static void timer_callback(regs& r) {
		tick++;
		term << "Tick: " << tick << "\n";
	}

	void init_timer(uint32_t frequency) {
		// Firstly, register our timer callback.
		install_irq_handler(32, timer_callback);

		// The value we send to the PIT is the value to divide it's input clock
		// (1193180 Hz) by, to get our required frequency. Important to note is
		// that the divisor must be small enough to fit into 16-bits.
		uint32_t divisor = 1193180 / frequency;

		// Send the command byte.
		__outbyte(I86_PIT_PORT_COMMAND, I86_PIT_OCW_RL_DATA | I86_PIT_OCW_MODE_SQUAREWAVEGEN);

		// Divisor has to be sent byte-wise, so split here into upper/lower bytes.
		uint8_t l = (uint8_t)(divisor & 0xFF);
		uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

		// Send the frequency divisor.
		__outbyte(0x40, l);
		__outbyte(0x40, h);
	}

}
#endif
