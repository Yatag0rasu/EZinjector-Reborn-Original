#include <Windows.h>
#include <iostream>
#include "memory.hpp"
#include <string>

using namespace std;

char namedll[32];

char process_name[32];

Injector inj;

DWORD pid;

DWORD getModuleBaseAddress(DWORD pid, const char* name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(MODULEENTRY32);
	do
	{
		if (!strcmp(mEntry.szModule, name))
		{
			CloseHandle(snapshot);
			return (DWORD)mEntry.modBaseAddr;
		}
	} while (Module32Next(snapshot, &mEntry));
}

bool DoesFileExist(const char* name) {
	if (FILE* file = fopen(name, "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");

void bypass()
{
	// Restore original NtOpenFile from external process
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 5, NULL);
	} 
	else
	{
		cout << "Unable to bypass.\n";
	}
}

void Backup()
{
	if (ntOpenFile) {
		//So, when I patching first 5 bytes I need to backup them to 0? (I think)
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 0, NULL);
	}
	else
	{
		cout << "Unable to backup :(\n";
		Sleep(2000);
		exit(-1);
	}
}

int main()
{
	SetConsoleTitle("EZinjector Reborn for CS:GO v1.1 by Yatagarasu");
	
	cout << "EZinjector Reborn Original +++ \n\nVisit ezcheats.ru / ezcheats.com\n Owner: Yatagarasu / Xvorost\n\n" << endl;

	inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive");

	cout << "Waiting for start CS:GO ..." << endl;

	for (;; Sleep(50))
	{
		if (inj.hwndproc == 0)
			inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive");
		if (inj.hwndproc != 0)
			break;
	}

	GetWindowThreadProcessId(inj.hwndproc, &pid);
	inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	system("cls");

	cout << "EZinjector Reborn Original +++ \n\nVisit ezcheats.ru / ezcheats.com\n Owner: Yatagarasu / Xvorost\n\n" << endl;

	inj.clientDLL = getModuleBaseAddress(pid, "client.dll");

	inj.engineDLL = getModuleBaseAddress(pid, "engine.dll");

	cout << "Loading ..." << endl;

	for (;; Sleep(500))
	{
		if (inj.clientDLL == 0)
			inj.clientDLL = getModuleBaseAddress(pid, "client.dll");
		if (inj.clientDLL != 0)
			break;
	}

	for (;; Sleep(500))
	{
		if (inj.engineDLL == 0)
			inj.engineDLL = getModuleBaseAddress(pid, "engine.dll");
		if (inj.engineDLL != 0)
			break;
	}
	
	system("cls");

	cout << "EZinjector Reborn Original +++ \n\nVisit ezcheats.ru / ezcheats.com\n Owner: Yatagarasu / Xvorost\n\n" << endl;

	cout << "Enter dll name:" << endl;

	scanf_s("%s", namedll);
	

	if (DoesFileExist(namedll)) {
		bypass();

			if (inj.inject(pid, namedll)) 
			{
				cout << "Injection successful! You can close this window.\n\n" << endl;
					Backup();
					Sleep(5000);
					exit(0);
			}
			else
			{
				cout << "Injection failed, try run as Administrator.\n\n" << endl;
					Backup();
					system("pause");
			}

	}
	else
	{
		cout << "Cannot find : " << namedll <<"\n";
		system("pause");
	}

	return 0;
}
