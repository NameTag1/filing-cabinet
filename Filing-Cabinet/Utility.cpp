#include "Utility.h"

#include <windows.h>
#include <shobjidl.h>  // IFileOpenDialog
#include <string>

std::wstring OpenFileDialog()
{
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) return L"";

    IFileOpenDialog* pFileOpen = nullptr;
    hr = CoCreateInstance(
        CLSID_FileOpenDialog,
        nullptr,
        CLSCTX_ALL,
        IID_PPV_ARGS(&pFileOpen)
    );

    if (FAILED(hr))
    {
        CoUninitialize();
        return L"";
    }

    // Show the dialog
    hr = pFileOpen->Show(nullptr);
    if (SUCCEEDED(hr))
    {
        IShellItem* pItem = nullptr;
        hr = pFileOpen->GetResult(&pItem);

        if (SUCCEEDED(hr))
        {
            PWSTR filePath = nullptr;
            pItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

            std::wstring result(filePath);

            CoTaskMemFree(filePath);
            pItem->Release();
            pFileOpen->Release();
            CoUninitialize();

            return result;
        }
    }

    pFileOpen->Release();
    CoUninitialize();
    return L"";
}