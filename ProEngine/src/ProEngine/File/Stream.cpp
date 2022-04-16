#include "Propch.h"
#include "Stream.h"

namespace Pro {

	Stream::Stream(std::string path)
	{
        TCHAR buffer[4096] = TEXT("");
        GetFullPathName((LPCWSTR)path.c_str(), 512, buffer, nullptr);

        HANDLE file = CreateFile(TEXT("C:\\Users\\alvar\\Desktop\\yo\\proyectos\\ProEngine\\SandBox\\assets\\Models\\city.fbx"), GENERIC_READ, 0, nullptr, OPEN_EXISTING, 0, nullptr);

        if (!file)
            throw std::runtime_error("Failed to open file " + path);

        HANDLE map = CreateFileMapping(file, nullptr, PAGE_READONLY, 0, 0, nullptr);
        if (!map) {
            CloseHandle(file);
            throw std::runtime_error("Failed to create file mapping " + path);
        }

        data = (char*)MapViewOfFile(map, FILE_MAP_READ, 0, 0, 0);
        if (!data) {
            CloseHandle(map);
            CloseHandle(file);
            throw std::runtime_error("Failed to memory map file " + path);
        }

        size = GetFileSize(file, NULL);
	}

    size_t Stream::Tell()
    {
        return cursor;
    }

}