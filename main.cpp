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

#include <vector>
#include <iostream>
#include <stdexcept>

#include "MemoryMap.h"
#include "MemoryMapAllocator.h"

int main()
{
    /** Sender **/
    MemoryMap data = {0};
    if (!CreateMemoryMap(&data, "MapName", 1024))
    {
        if (!OpenMemoryMap(&data, "MapName", 1024))
        {
            throw std::runtime_error("Cannot map memory.");
        }
    }

    std::vector<int, CAllocator<int>> shared_sender_vector(CAllocator<int>(data.pData, data.size));
    shared_sender_vector.push_back(10);

    for (int i = 0; i < 10; ++i)
    {
        shared_sender_vector.push_back(i + 1);
    }



    /** Receiver **/
    MemoryMap data2 = {0};
    if (!CreateMemoryMap(&data2, "MapName", 1024))
    {
        if (!OpenMemoryMap(&data2, "MapName", 1024))
        {
            throw std::runtime_error("Cannot map memory.");
        }
    }


    int* offset = static_cast<int*>(data2.pData);
    std::vector<int, CAllocator<int>> shared_receiver_vector(CAllocator<int>(++offset, data2.size));
    shared_receiver_vector.reserve(*(--offset));

    for (int i = 0; i < 10; ++i)
    {
        std::cout<<shared_receiver_vector[i]<<" ";
    }

    CloseMap(&data);
    CloseMap(&data2);
}
