#include <iostream>
#include <windows.h>
using namespace std;

#if defined _WIN32 || defined _WIN64
void position(int LINHA, int COLUNA) {
   if (COLUNA >= 1 and COLUNA <= 80 and LINHA >= 1 and LINHA <= 24) {
      HANDLE TELA;
      COORD POS;
      TELA = GetStdHandle(STD_OUTPUT_HANDLE);
      POS.X = COLUNA - 1;
      POS.Y = LINHA - 1;
      SetConsoleCursorPosition(TELA, POS);
   }
}
void limpa(void) {
   HANDLE TELA;
   DWORD ESCRITA = 0;
   COORD POS;
   TELA = GetStdHandle(STD_OUTPUT_HANDLE);
   POS.X = 0;
   POS.Y = 0;
   FillConsoleOutputCharacter(TELA, 32, 100 * 100, POS, &ESCRITA);
   position(2, 1);
}
#else
void position(int LINHA, int COLUNA) {
   if (COLUNA >= 1 && COLUNA <= 80 && LINHA >= 1 && LINHA <= 24)
      cout << "\033[" << LINHA << ";" << COLUNA << "H";
}
void limpa(void) {
   cout << "\033[2J";
   position(2, 1);
}
#endif
