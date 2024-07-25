#pragma once

// adapted from: https://github.com/MicrosoftDocs/cpp-docs/issues/1915#issuecomment-589644386
class ConsoleUTF8 {
  public:
    ConsoleUTF8();
    ~ConsoleUTF8();

  private:
    unsigned int m_original_cp;
};
