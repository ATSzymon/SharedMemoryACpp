// SharedMemoryC++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <stdio.h>

int data = 60000;
HANDLE handle;
int * p;

//! https://docs.microsoft.com/en-us/windows/win32/memory/creating-named-shared-memory

bool startShare()
{
    try {


        handle = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(data), L"14"); //create memory mapped file 

        p = (int *)MapViewOfFile(handle,    // create stream to memory mapped file(handle)
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            sizeof(data)); 

        return true;
    }
    catch (...) {
        std::cout << "Unable to createFile mapping";
        return false;
    }
}


int main()
{
    if (startShare())
    {

        
        while (1)
        {

        CopyMemory((p),&data,sizeof(data)); // copy data to handle thru stream p
        }
        
        UnmapViewOfFile(p);
        CloseHandle(handle); // close shared memory
    }
}

