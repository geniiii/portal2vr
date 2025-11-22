#include <Windows.h>
#include <iostream>
#include "game.h"
#include "hooks.h"
#include "vr.h"
#include "sdk.h"

DWORD WINAPI InitL4D2VR(HMODULE hModule) {
// Release if buggy, so we'll be releasing the debug binary
#ifdef _DEBUG
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
#endif

    g_Game = new Game();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD   ul_reason_for_call,
                      LPVOID  lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) InitL4D2VR, hModule, 0, NULL);
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
