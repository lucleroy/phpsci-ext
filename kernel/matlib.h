#ifndef PHPSCI_EXT_MATLIB_H
#define PHPSCI_EXT_MATLIB_H

#include "carray.h"

CArray * CArray_Zeros(int * shape, int nd, char * type, char * order, MemoryPointer * rtn_ptr);

#endif //PHPSCI_EXT_MATLIB_H