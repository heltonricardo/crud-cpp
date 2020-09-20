#include <iostream>   // ENTRADA E SAÍDA PADRÃO
#include <fstream>    // MANIPULAR ARQUIVOS
#include "cadastro.h" // CLASSE E TODAS AS SUB-ROTINAS
using namespace std;

int main(void) {
   short opcao;                                                   // ARMAZENA A OPCAO DO MENU

   fstream arquivo("banco.dbc", ios_base::in | ios_base::binary); // ABERTURA DO ARQUIVO EM MODO LEITURA BINÁRIA:

   if(arquivo.fail())                                             // SE O ARQUIVO NÃO EXISTIR
      criarArquivo();                                             // CRIA O ARQUIVO

   do {
      opcao = menu();                                             // menu() RETORNA UMA OPCAO TRATADA VALIDA
      switch(opcao) {                                             // CHAMA A SUB-ROTINA CORRESPONDENTE:
         case 1: cadastrar();     break;
         case 2: pesquisarNome(); break;
         case 3: pesquisarData(); break;
         case 4: remover();       break;
         case 5: alterar();       break;
      }
   } while (opcao);                                               // ENQUANTO A OPCAO FOR DIFERENTE DE ZERO

   arquivo.close();                                               // FECHA O ARQUIVO
   return 0;
}
