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

void* CreateMemoryMap(MemoryMap* info, const char* MapName, unsigned int size)
{
	info->hFileMap = NULL;
	info->pData = NULL;
	info->size = 0;

	if ((info->hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, size, MapName)) == NULL)
	{
		return NULL;
	}

	if ((info->pData = MapViewOfFile(info->hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, size)) == NULL)
	{
		CloseHandle(info->hFileMap);
		return NULL;
	}

	info->size = size;
	return info->pData;
}

void* OpenMemoryMap(MemoryMap* info, const char* MapName, unsigned int size)
{
	info->hFileMap = NULL;
	info->pData = NULL;
	info->size = 0;

	if ((info->hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, MapName)) == NULL)
	{
		return NULL;
	}

	if ((info->pData = MapViewOfFile(info->hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, size)) == NULL)
	{
		CloseHandle(info->hFileMap);
		return NULL;
	}

	info->size = size;
	return info->pData;
}

void CloseMap(MemoryMap* data)
{
    UnmapViewOfFile(data->pData);
    CloseHandle(data->hFileMap);

    data->hFileMap = NULL;
    data->pData = NULL;
    data->size = NULL;
}
