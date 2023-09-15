#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <Psapi.h>
#include <string>

namespace Memory {
    class ProcessInfo {
    public:
        static inline HANDLE hHand = nullptr;
        static inline HWND hWnd = nullptr;
        static inline DWORD PID = 0;
        static inline uintptr_t moduleBase = 0x0;
        static inline int ResX = 0, ResY = 0;
    };

    class External {
    public:
        ProcessInfo Info;
        void GatherProcessInfo();
        DWORD GetProcId(const wchar_t* procName);
        uintptr_t GetModuleBase(const wchar_t* modName);
        uintptr_t FinalAddress(uintptr_t ptr, std::vector<unsigned int> offsets);
        template<typename T> T RPM(uintptr_t address) {
            T buffer;
            ReadProcessMemory(Info.hHand, (LPVOID)address, &buffer, sizeof(buffer), nullptr);

            return buffer;
        }
        template<typename T> T WPM(uintptr_t address, int val) {
            T buffer = (T)val;
            WriteProcessMemory(Info.hHand, (LPVOID)address, &buffer, sizeof(buffer), nullptr);

            return buffer;
        }
    };

    class Internal {
    public:
        template<typename T> T RPM(uintptr_t address) {
            return *(T*)(address);
        }
        template<typename T> T WPM(uintptr_t address, int val) {
            *(T*)address = (T)val;
            return *(T*)address;
        }
    };
}

namespace CScreen {
    struct Info {
    public:
        static inline int x = 0;
        static inline int y = 0;
    };
}
