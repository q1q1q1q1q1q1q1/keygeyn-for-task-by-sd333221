#include <Windows.h>
#include <iostream>

/*
mov eax, dword ptr ds : [445804]
imul eax, eax, 3
mov dword ptr ds : [445804] , eax
mov ecx, dword ptr ds : [445804]
add ecx, 54C563
mov dword_445804, ecx <-we'll get this
*/

int __cdecl main()
{
	const char windowName[] = "Keygen by sd333221";

	HWND hwnd = FindWindowA(NULL, windowName);
	if (!hwnd)
	{
		printf("findWindow is failed");
		return EXIT_FAILURE;
	}

	DWORD pID = 0;
	GetWindowThreadProcessId(hwnd, &pID);
	if (!pID)
	{
		printf("GetWindowthreadProcessId is failed");
		return EXIT_FAILURE;
	}

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, pID);
	if (!hProc)
	{
		printf("OpenProcess is failed: 0x%X", GetLastError());
		return EXIT_FAILURE;
	}
	UINT32 buff;
	if (!ReadProcessMemory(hProc, reinterpret_cast<void*>(0x004457F8), &buff, sizeof(buff), NULL))
	{
		printf("ReadProcessMemory is failed: 0x%X", GetLastError());
		return EXIT_FAILURE;
	}
	

	printf("Name: %u\n", buff);
	printf("Serial: %u\n", buff * 3 + 5555555);



	CloseHandle(hProc);

	return EXIT_SUCCESS;
}