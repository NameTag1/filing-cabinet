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

std::string wstring_to_string(const std::wstring& wstr)
{
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), nullptr, 0, nullptr, nullptr);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, nullptr, nullptr);
    return strTo;
}