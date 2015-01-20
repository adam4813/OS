#ifndef __NEW_H
#define __NEW_H

extern "C" {
	void* ::operator new (size_t size) { return 0; }
	void* operator new[ ] (size_t size) { return 0; }
	void ::operator delete (void* p) { }
	void operator delete[ ] (void* p) { }
}

#endif
