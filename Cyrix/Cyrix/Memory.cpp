#pragma once
#include "Memory.h"

uintptr_t Memory::External::GetModuleBase(const wchar_t* modName)
{
    Memory::ProcessInfo info;
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, info.PID);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32W modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32FirstW(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32NextW(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

uintptr_t Memory::External::FinalAddress(uintptr_t ptr, std::vector<unsigned int> offsets)
{
    Memory::ProcessInfo info;
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(info.hHand, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }
    return addr;
}

void Memory::External::GatherProcessInfo()
{
    Memory::ProcessInfo info;
    info.hWnd = FindWindowA(0, "Call of Duty®: Black Ops II - Zombies");
    info.PID; GetWindowThreadProcessId(info.hWnd, &info.PID);
    info.hHand = OpenProcess(PROCESS_ALL_ACCESS, true, info.PID);
    info.moduleBase = this->GetModuleBase(L"plutonium-bootstrapper-win32.exe");
}

DWORD Memory::External::GetProcId(const wchar_t* procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32W procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32FirstW(hSnap, &procEntry))
        {
            do
            {
                if (!_wcsicmp(procEntry.szExeFile, procName))
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32NextW(hSnap, &procEntry));

        }
    }
    CloseHandle(hSnap);
    return procId;
}

