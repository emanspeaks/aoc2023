#include "utf8.h"

namespace win32api{
  #ifdef _WIN32
    #define NOMINMAX  // https://learn.microsoft.com/en-us/archive/msdn-magazine/2016/september/c-unicode-encoding-conversions-with-stl-strings-and-win32-apis#converting-from-utf-8-to-utf-16-multibytetowidechar-in-action
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
  #endif
}

// adapted from: https://github.com/MicrosoftDocs/cpp-docs/issues/1915#issuecomment-589644386
ConsoleUTF8::ConsoleUTF8() {
  #ifdef _WIN32
    m_original_cp = win32api::GetConsoleOutputCP();
    win32api::SetConsoleOutputCP(CP_UTF8);
  #endif
}

ConsoleUTF8::~ConsoleUTF8() {
  #ifdef _WIN32
    win32api::SetConsoleOutputCP(m_original_cp);
  #endif
}
