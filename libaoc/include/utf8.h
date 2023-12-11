#pragma once

#ifdef _WIN32
  #define NOMINMAX  // https://learn.microsoft.com/en-us/archive/msdn-magazine/2016/september/c-unicode-encoding-conversions-with-stl-strings-and-win32-apis#converting-from-utf-8-to-utf-16-multibytetowidechar-in-action
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#else
  #define UINT unsigned int
#endif

// adapted from: https://github.com/MicrosoftDocs/cpp-docs/issues/1915#issuecomment-589644386
class ConsoleUTF8 {
  public:
    ConsoleUTF8() {
      #ifdef _WIN32
        original_cp = ::GetConsoleOutputCP();
        ::SetConsoleOutputCP(CP_UTF8);
      #endif
    }

    ~ConsoleUTF8() {
      #ifdef _WIN32
        ::SetConsoleOutputCP(original_cp);
      #endif
    }

  private:
    UINT original_cp;
};
