#ifndef __TERMINAL_H
#define __TERMINAL_H

#include "stdint.h"
#include "string.h"
#include "runtime/itoa.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

class Terminal {
public:
	enum vga_color {
		COLOR_BLACK = 0,
		COLOR_BLUE = 1,
		COLOR_GREEN = 2,
		COLOR_CYAN = 3,
		COLOR_RED = 4,
		COLOR_MAGENTA = 5,
		COLOR_BROWN = 6,
		COLOR_LIGHT_GREY = 7,
		COLOR_DARK_GREY = 8,
		COLOR_LIGHT_BLUE = 9,
		COLOR_LIGHT_GREEN = 10,
		COLOR_LIGHT_CYAN = 11,
		COLOR_LIGHT_RED = 12,
		COLOR_LIGHT_MAGENTA = 13,
		COLOR_LIGHT_BROWN = 14,
		COLOR_WHITE = 15,
	};

	uint8_t make_color(enum vga_color fg, enum vga_color bg) {
		return (uint8_t)(fg | bg << 4);
	}

	uint16_t make_vgaentry(char c, uint8_t color) {
		uint16_t c16 = (uint16_t)c;
		uint16_t color16 = color;
		return (uint16_t)(c16 | color16 << 8);
	}

	void Initialize() {
		this->terminal_row = 0;
		this->terminal_column = 0;
		this->terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
		this->terminal_buffer = (uint16_t*)0xB8000;
		for (size_t y = 0; y < VGA_HEIGHT; y++) {
			for (size_t x = 0; x < VGA_WIDTH; x++) {
				const size_t index = y * VGA_WIDTH + x;
				this->terminal_buffer[index] = make_vgaentry(' ', terminal_color);
			}
		}
	}

	void SetColor(uint8_t color) {
		this->terminal_color = color;
	}

	// Set the character at the specified position and don't advance the cursor.
	void SetChar(char c, uint8_t color, size_t x, size_t y) {
		const size_t index = y * VGA_WIDTH + x;
		this->terminal_buffer[index] = make_vgaentry(c, color);
	}

	// Moves the entire screen up 1 scan line.
	void ScanUp() {
		for (size_t y = 1; y < VGA_HEIGHT; y++) {
			for (size_t x = 0; x < VGA_WIDTH; x++) {
				const size_t index = y * VGA_WIDTH + x;
				this->terminal_buffer[index - VGA_WIDTH] = this->terminal_buffer[index];
			}
		}
	}

	// Put at character at the current cursor (terminal row, column) and advance it.
	void PutChar(char c) {
		if (c == '\n') {
			if (++terminal_row == VGA_HEIGHT) {
				terminal_row = VGA_HEIGHT - 1;
				ScanUp();
			}
			terminal_column = 0;
			return;
		}
		SetChar(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT) {
				terminal_row = VGA_HEIGHT - 1;
				ScanUp();
			}
		}
	}

	// Loop over a null terminated string and call PutChar() for each character.
	void WriteString(const char* data) {
		size_t datalen = strlen(data);
		for (size_t i = 0; i < datalen; i++) {
			PutChar(data[i]);
		}
	}

	friend Terminal& operator <<(Terminal& term, const char* data) {
		term.WriteString(data);
		return term;
	}
	
	friend Terminal& operator <<(Terminal& term, const uint64_t data) {
		char buf[32];

		itoa(data, buf, 10);
		term.WriteString(buf);
		return term;
	}

private:
	size_t terminal_row;
	size_t terminal_column;
	uint8_t terminal_color;
	uint16_t* terminal_buffer;
};
#endif
