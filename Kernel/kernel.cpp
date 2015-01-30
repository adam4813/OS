#include "runtime/new.h"
#include "fpsupport.h"
#include "runtime/string.h"
#include "runtime/stdint.h"
#include "runtime/terminal.h"
#include "runtime/itoa.h"
#include "interrupt_handler.h"
#include "pit.h"
#include "kb.h"

Terminal term;

extern "C" void kernel_main() {
	term.Initialize();

	// Print some info about the CPU.
	term << "Number of cores:" << *(ushort_t*)0x5012 << " running at:" << *(ushort_t*)0x5010 << " MHZ\n";

	// Print total available RAM.
	term << "Total detected RAM: " << *(int32_t*)0x5020 << " MiB\n";

	i86_idt_initialize(0x8);
	init_timer(50);
	init_kb();

	for (;;);
}
