/**  © 2014, Olga K. All Rights Reserved.
  *
  *  This file is part of the CPPUtilities Library.
  *  CPPUtilities is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  CPPUtilities is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with CPPUtilities.  If not, see <http://www.gnu.org/licenses/>.
  */

#include <windows.h>
#include <cstdint>

/** @brief Structure for holding memory-map information.
 *
 */
typedef struct
{
    void* hFileMap; ///Handle to the memory mapped file.
    void* pData;    ///Pointer to the beginning of the memory mapped region.
    size_t size;    ///Total size of the memory map.
} MemoryMap;


/** @brief Memory-maps a file to allow communication between processes or fast reading of the specified file.
 *
 * @param info MemoryMap* A pointer to a MemoryMap structure that will contain the mapped information upon success.
 * @param MapName const char* Name/Location of the file to map.
 * @param size unsigned int Size of the memory region to be mapped.
 * @return extern void* A pointer to the beginning of the memory mapped region.
 *
 */
extern void* CreateMemoryMap(MemoryMap* info, const char* MapName, unsigned int size);


/** @brief Opens an already mapped file for reading and writing.
 *
 * @param info MemoryMap* Pointer to a MemoryMap structure that will contain the mapped information upon success.
 * @param MapName const char* Name/Location of the file to be opened and mapped.
 * @param size unsigned int Size of the memory region to be mapped.
 * @return extern void* A pointer to the beginning of the memory mapped region.
 *
 */
extern void* OpenMemoryMap(MemoryMap* info, const char* MapName, unsigned int size);


/** @brief Closes a memory mapped file and un-maps the memory regions.
 *
 * @param data MemoryMap* Pointer to a MemoryMap structure that contains the mapped information.
 * @return extern void
 *
 */
extern void CloseMap(MemoryMap* data);
