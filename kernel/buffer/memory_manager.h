/*
  +----------------------------------------------------------------------+
  | PHPSci CArray                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 2018 PHPSci Team                                       |
  +----------------------------------------------------------------------+
  | Licensed under the Apache License, Version 2.0 (the "License");      |
  | you may not use this file except in compliance with the License.     |
  | You may obtain a copy of the License at                              |
  |                                                                      |
  |     http://www.apache.org/licenses/LICENSE-2.0                       |
  |                                                                      |
  | Unless required by applicable law or agreed to in writing, software  |
  | distributed under the License is distributed on an "AS IS" BASIS,    |
  | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
  | implied.                                                             |
  | See the License for the specific language governing permissions and  |
  | limitations under the License.                                       |
  +----------------------------------------------------------------------+
  | Authors: Henrique Borba <henrique.borba.dev@gmail.com>               |
  +----------------------------------------------------------------------+
*/

#ifndef PHPSCI_EXT_MEMORY_MANAGER_H
#define PHPSCI_EXT_MEMORY_MANAGER_H
#define UNINITIALIZED -1

#include "../carray/carray.h"

/**
 * MemoryStack : The memory buffer of CArrays
 */
struct MemoryStack {
    CArray * buffer;
    int size;
    int capacity;
    size_t bsize;
    int last_deleted_uuid;
} MemoryStack;

/**
 * PHPSCI_MAIN_MEM_STACK : Global memory stack of CArrays. CArrays are always visible
 * within the runtime.
 *
 * @todo Check if this is bad
 */
extern struct MemoryStack PHPSCI_MAIN_MEM_STACK;


void add_to_stack(MemoryPointer * ptr, CArray array, size_t size);
void buffer_to_capacity(int new_capacity, size_t size);
void stack_init();


#endif //PHPSCI_EXT_MEMORY_MANAGER_H
