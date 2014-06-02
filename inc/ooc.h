

#ifndef __OOC_H
#define __OOC_H

	
	#define TRUE 1
	#define FALSE 0
	typedef int BOOLEAN;
	
	
	typedef void (*VFuncPtr)(void); // VirtualFunctionPointer

	typedef struct {
   
		int d, i; // d and i fields are used when multiple inheritance and virtual base classes
		VFuncPtr pFunc;
		
	} VTable;

#endif
