#ifndef __STRING_H
#define __STRING_H

extern "C" {
	unsigned char *memcpy(unsigned char *dest, const unsigned char *src, unsigned int count);
	unsigned char *memset(unsigned char *dest, unsigned char val, unsigned int count);
	unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned int count);
	unsigned int strlen(const char *str);
}

#endif
