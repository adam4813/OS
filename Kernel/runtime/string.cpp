#include "string.h"

//unsigned char *memcpy(unsigned char *dest, const unsigned char *src, unsigned int count) {
//	unsigned char *dp = dest;
//	const unsigned char *sp = src;
//	while (count--) {
//		*dp++ = *sp++;
//	}
//	return dest;
//}
//
//void *memset(void *dest, unsigned char val, unsigned int count) {
//	unsigned int *dp =(unsigned int*)dest;
//	while (count--) {
//		*dp++ = val;
//	}
//	return dest;
//}
//
//unsigned char *memset(unsigned char *dest, unsigned char val, unsigned int count) {
//	unsigned char *dp = dest;
//	while (count--) {
//		*dp++ = val;
//	}
//	return dest;
//}
//
//unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned int count) {
//	unsigned short *dp = dest;
//	while (count--) {
//		*dp++ = val;
//	}
//	return dest;
//}
//
//unsigned int strlen(const char *str) {
//	const char* ptr = str;
//	unsigned int count = 0;
//	while (*ptr++ != '\0') {
//		count++;
//	}
//
//	return count;
//}
