#ifndef BLADE_WIN32UTILS_H_
#define BLADE_WIN32UTILS_H_

#include <Windows.h>

template<typename T>
void SetWindowLongPointer(HWND handle, int index, T* val)
{
	SetWindowLongPtr(handle, index, reinterpret_cast<LONG_PTR>(val));
}

template<typename T>
T* GetWindowLongPointer(HWND handle, int index)
{
	return reinterpret_cast<T*>(GetWindowLongPtr(handle, index));
}

#endif //BLADE_WIN32UTILS_H_
