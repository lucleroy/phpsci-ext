//
// Created by Henrique Borba on 19/11/2018.
//

#include "alloc.h"
#include "carray.h"
#include "buffer.h"

/**
 * @return
 */
void
CArray_INCREF(CArray *target)
{
    target->refcount++;
}

/**
 * @return
 */
void
CArray_DECREF(CArray *target)
{
    target->refcount--;
}

/**
 * Alocates CArray Data Buffer based on numElements and elsize from 
 * CArray descriptor.
 **/ 
void
CArray_Data_alloc(CArray * ca)
{
    ca->data = emalloc((ca->descriptor->numElements * ca->descriptor->elsize));
}

/**
 * @param size
 * @return
 */
void *
carray_data_alloc_zeros(int num_elements, int size_element, char type)
{
    return (void*)ecalloc(num_elements, size_element);
}

/**
 * @param size
 * @return
 */
void *
carray_data_alloc(int num_elements, int size_element)
{
    return (void*)emalloc(num_elements * size_element);
}

/**
 * @param descriptor
 */
void
CArrayDescriptor_INCREF(CArrayDescriptor * descriptor)
{
    descriptor->refcount++;
}

/**
 * @param descriptor
 */
void
CArrayDescriptor_DECREF(CArrayDescriptor * descriptor)
{
    descriptor->refcount--;
}

void
CArray_Free(CArray * self)
{
    if(!self->refcount) {
        efree(self->dimensions);
        efree(self->strides);
        efree(self->descriptor->f);
        efree(self->descriptor);
        efree(self->data);
        efree(self);
    }
}

/**
 * Free CArrays owning data buffer
 */  
void
_free_data_owner(MemoryPointer * ptr)
{
    CArray * array = CArray_FromMemoryPointer(ptr);
    CArrayDescriptor_DECREF(array->descriptor);
    if(array->descriptor->refcount <= 0) {
        efree(array->descriptor->f);
        if(array->descriptor != NULL) {
            efree(array->descriptor);
        }
    }
    
    CArray_DECREF(array);
    efree(array->dimensions);
    efree(array->strides);
    if(array->refcount < 0) {
        efree(array->data);
        buffer_remove(ptr);
    }    
}

/**
 * Free CArrays that refers others CArrays
 */  
void
_free_data_ref(MemoryPointer * ptr)
{
    MemoryPointer tmp;
    
    CArray * array = CArray_FromMemoryPointer(ptr);
    
    CArray_DECREF(array);
    CArray_DECREF(array->base);
    CArrayDescriptor_DECREF(array->descriptor);
    
    if(array->descriptor->refcount <= 0) {
        efree(array->descriptor->f);
        efree(array->descriptor);
    }
    efree(array->dimensions);
    efree(array->strides);
    
    if(array->refcount < 0 && array->base->refcount < 0) {
        if(CArray_CHKFLAGS(array->base, CARRAY_ARRAY_OWNDATA)) {
            efree(array->data);
        } 
        tmp.uuid = array->base->uuid;
        buffer_remove(&tmp);
    }   
    if(array->refcount < 0){
        buffer_remove(ptr);
    }    
}

/**
 * Free CArray using MemoryPointer
 **/ 
void
CArray_Alloc_FreeFromMemoryPointer(MemoryPointer * ptr)
{
    CArray * array = CArray_FromMemoryPointer(ptr);
    if(CArray_CHKFLAGS(array, CARRAY_ARRAY_OWNDATA)){
        _free_data_owner(ptr);
    } else {
        _free_data_ref(ptr);
    }
    return;
}

CArray *
CArray_Alloc(CArrayDescriptor *descr, int nd, int* dims,
             int is_fortran, void *interfaceData)
{
    CArray * target = emalloc(sizeof(CArray));
    return CArray_NewFromDescr(target, descr, nd, dims, NULL, NULL,
                              ( is_fortran ? CARRAY_ARRAY_F_CONTIGUOUS : 0),
                              interfaceData);
}