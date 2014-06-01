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

#include <cstdint>

/** @brief A custom allocator for storing STL containers directly in a memory-map.
 *
 */
template<typename T>
class CAllocator
{
    private:
        size_t size;
        void* data = nullptr;

    public:
        typedef T* pointer;
        typedef const T* const_pointer;

        typedef T& reference;
        typedef const T& const_reference;

        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        typedef T value_type;


        CAllocator() {}
        CAllocator(void* data_ptr, size_type max_size) noexcept : size(max_size), data(data_ptr) {};

        template<typename U>
        CAllocator(const CAllocator<U>& other) noexcept {};

        CAllocator(const CAllocator &other) : size(other.size), data(other.data) {}

        template<typename U>
        struct rebind {typedef CAllocator<U> other;};

        pointer allocate(size_type n, const void* hint = 0) {return static_cast<pointer>(data);}
        void deallocate(void* ptr, size_type n) {}
        size_type max_size() const {return size / sizeof(T);}
};

template <typename T, typename U>
inline bool operator == (const CAllocator<T>&, const CAllocator<U>&) {return true;}

template <typename T, typename U>
inline bool operator != (const CAllocator<T>& a, const CAllocator<U>& b) {return !(a == b);}
