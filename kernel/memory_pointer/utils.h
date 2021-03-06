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

#ifndef PHPSCI_EXT_UTILS_H
#define PHPSCI_EXT_UTILS_H
#include "../buffer/memory_manager.h"

int carray_shapecmp(MemoryPointer * ptr_a, MemoryPointer * ptr_b);
int GET_DIM(MemoryPointer * ptr);
int IS_0D(MemoryPointer * ptr);
int IS_1D(MemoryPointer * ptr);
int IS_2D(MemoryPointer * ptr);
int IS_SQUARE(MemoryPointer * ptr);
#endif //PHPSCI_EXT_UTILS_H
