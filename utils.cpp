#include <utils.h>
HWND _WORKERW = nullptr;

inline BOOL CALLBACK EnumWindowsProc(_In_ HWND tophandle, _In_ LPARAM topparamhandle)
{
    HWND defview = FindWindowEx(tophandle, 0, L"SHELLDLL_DefView", nullptr);
    if (defview != nullptr)
    {
        _WORKERW = FindWindowEx(0, tophandle, L"WorkerW", 0);
    }
    return true;
}



HWND Utils::GetWorkerW(){
    int result;
    HWND windowHandle = FindWindow(L"Progman", nullptr);
    //使用 0x3e8 命令分割出两个 WorkerW
    SendMessageTimeout(windowHandle, 0x052c, 0 ,0, SMTO_NORMAL, 0x3e8,(PDWORD_PTR)&result);
    //遍历窗体获得窗口句柄
    EnumWindows(EnumWindowsProc,(LPARAM)nullptr);
    // 显示WorkerW
    ShowWindow(_WORKERW,SW_HIDE);
    return windowHandle;
}
