#include <iostream>
#include <tlhelp32.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <Windows.h>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <direct.h>
#include <ShlObj_core.h>
#include <Wininet.h>
#pragma comment(lib, "wininet.lib")

#include "MinHook/include/MinHook.h"

namespace Bypass
{
	void terminate_process(uintptr_t proc_id)
	{
		const auto explorer = OpenProcess(PROCESS_TERMINATE, false, proc_id);
		TerminateProcess(explorer, 1);
		CloseHandle(explorer);
	}


	uintptr_t get_main_roblox()
	{
		HWND hw = FindWindowA(NULL, "Roblox");
		DWORD proc_id;
		GetWindowThreadProcessId(reinterpret_cast<HWND>(hw), reinterpret_cast<LPDWORD>(&proc_id));
		return proc_id;
	}


	DWORD get_procid_by_name(const char* processName)
	{
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (Process32First(snapshot, &entry) == TRUE)
		{
			while (Process32Next(snapshot, &entry) == TRUE)
			{
				if (_stricmp(entry.szExeFile, processName) == 0)
				{
					CloseHandle(snapshot);
					return entry.th32ProcessID;
				}
			}
		}

		CloseHandle(snapshot);
		return 0;
	}

	DWORD main_robloxid;

	void catch_process(DWORD processID)
	{
		TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE, processID);

		if (NULL != hProcess)
		{
			HMODULE hMod;
			DWORD cbNeeded;

			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
				&cbNeeded))
			{
				GetModuleBaseName(hProcess, hMod, szProcessName,
					sizeof(szProcessName) / sizeof(TCHAR));

				std::string processName(szProcessName);

				if (processName == "RobloxPlayerBeta.exe")
				{
					if (main_robloxid == processID)
					{
						//ok
					}
					else
					{
						terminate_process(processID);
					}
				}

				CloseHandle(hProcess);
			}
		}
	}
	void bypass()
	{
		main_robloxid = get_main_roblox();

		while (true)
		{
			Sleep(5000);
			DWORD aProcesses[1024], cbNeeded, cProcesses;
			unsigned int i;

			if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
			{
				return;
			}

			cProcesses = cbNeeded / sizeof(DWORD);

			for (i = 0; i < cProcesses; i++)
			{
				if (aProcesses[i] != 0)
				{
					catch_process(aProcesses[i]);
				}
			}
		}
	}


	void bypass_thread()
	{
		HWND hw;
		hw = FindWindowA(NULL, "Roblox");
		if (hw != NULL)
		{
			std::thread(bypass).detach();
		}
		else
		{
			while (hw == NULL)
			{
				hw = FindWindowA(NULL, "Roblox");

				if (hw != NULL)
				{
					std::thread(bypass).detach();
					break;
				}
			}
		}
	}
}


namespace Hooks
{
	int MessageBoxA_c;

	int WINAPI MessageBoxA_r(
		_In_opt_ HWND hWnd,
		_In_opt_ LPCSTR lpText,
		_In_opt_ LPCSTR lpCaption,
		_In_ UINT uType)
	{
		MH_DisableHook(&MessageBoxA);

		if (strcmp(reinterpret_cast<const char*>(lpText), "An unexpected error occurred and Roblox needs to quit.  We're sorry!") == 0)
		{
			int MessageBoxReturn = MessageBoxA(hWnd, "Sorry, but Vertikon got crashed!", "Vertikon", uType);
			return MessageBoxReturn;
		}
		int MessageBoxReturn = MessageBoxA(hWnd, lpText, lpCaption, uType);
		MH_EnableHook(&MessageBoxA);
		return MessageBoxReturn;
	}


	void messagebox_hook()
	{
		MH_Initialize();
		MH_CreateHook(&MessageBoxA, &MessageBoxA_r, reinterpret_cast<LPVOID*>(MessageBoxA_c));
		MH_EnableHook(&MessageBoxA);
	}
}