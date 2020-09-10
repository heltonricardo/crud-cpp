/// ATIVIDADE ..: AVALIAÇÃO/PROVA (FINAL)
/// DATA .......: 28-11-2019
/// AUTOR ......: HELTON RICARDO SANTOS DA COSTA
/// CURSO ......: ANÁLISE E DESENVOLVIMENTO DE SISTEMAS
/// TURMA ......: II SEMESTRE
/// PROFESSOR ..: JOSE AUGUSTO NAVARRO GARCIA MANZANO

#include <iostream>   // ENTRADA E SAÍDA PADRÃO
#include <cstring>    // PARA USAR strcpy() e strcmp()
#include <fstream>    // MANIPULAR ARQUIVOS
#include <conio.h>    // PARA USAR getch()
#include <ctime>      // PARA PEGAR A DATA ATUAL DO SISTEMA
#include "calendar.h" // PARA CALCULAR DIFERENÇA ENTRE DATAS
#include "manzano.h"  // LIMPAR A TELA E POSICIONAR CURSOR
using namespace std;

class Cadastro {                     // DEFINIÇÃO DA CLASSE
   private:
      char status;                   // PARA SABER SE O CADASTRO ESTÁ OU NÃO ATIVO
      char nome[41];                 // NOME DA PESSOA
      char data[11];                 // DATA DE NASCIMENTO DA PESSOA
   public:
      void setStatus(char pstatus) { // PARA DEFINIR O STATUS
         status = pstatus;           // DEFINE O CAMPO MEMBRO COM O VALOR DO PARÂMETRO
      }
      char getStatus() {             // PARA LER O STATUS
         return status;              // RETORNA O VALOR ARMAZENADO NO CAMPO MEMBRO
      }
      void setNome(char *pnome) {    // PARA DEFINIR O NOME
         strcpy(nome, pnome);        // COPIA PARA O CAMPO MEMBRO O VALOR DO PARÂMETRO
      }
      char *getNome() {              // PARA LER O NOME
         return nome;                // RETORNA O VALOR ARMAZENADO NO CAMPO MEMBRO
      }
      void setData(char *pdata) {    // PARA DEFINIR A DATA
         strcpy(data, pdata);        // COPIA PARA O CAMPO MEMBRO O VALOR DO PARÂMETRO
      }
      char *getData() {              // PARA LER A DATA
         return data;                // RETORNA O VALOR ARMAZENADO NO CAMPO MEMBRO
      }
};

Cadastro pessoa;                                   // INSTANCIAÇÃO DO OBJETO pessoa
char pnome[41], pdata[11];                         // VÁRIAVEIS PARA AUXÍLIO DA LEITURA

void pausa(short status) {                         // PARA PAUSAR PROGRAMA E EXIBIR MENSAGEM
   if (status)                                     // PARA ESCREVER A MENSAGEM ADICIONAL
      cout << " Concluido com sucesso. ";          // MENSAGEM ADICIONAL
   cout << "Pressione <Enter> para continuar... "; // MENSAGEM PADRÃO
   cin.get();                                      // SOLICITA LEITURA DE CARACTERE PARA PAUSAR EXECUÇÃO
}

char upper(char e) {                        // TRANSFORMA CARACTERE MINÚSCULO EM MAIÚSCULO
                                            // SE 97 <= CARACTERE <= 122 ENTÃO ELE É MINÚSCULO\
                                            // DIMINUINDO 32 CARACTERES DELE, É RETORNADA SUA VERSÃO\
                                            // MAIÚSCULA CORRESPONDENTE NA TABELA ASCII
   return (97 <= e && e <= 122) ? e-32 : e;
}

void lerstr(char *s) {          // CORRIGE A ENTRADA PARA CARACTERES MAIÚSCULOS
   char c;                      // USADA PARA CADA CARACTERE LIDO
   int pos = 0;                 // QUANTIDADE DE CARACTERES LIDOS
   do {
      c = upper(getch());       // ARMAZENA O CARACTERE LIDO NA VARIÁVEL c
      if (isprint(c)) {         // SE c FOR UM CARACTERE QUE PODE SER IMPRESSO
         cout << c;             // IMPRIME c NA TELA
         *s++ = c;              // ADICIONA c NA POSISÃO ATUAL DO PONTEIRO E VAI PARA PRÓXIMA POSIÇÃO
         ++pos;                 // AUMENTA A QUANTIDADE DE CARACTERES LIDOS
      }
      else if (c == 8 && pos) { // SE c FOR A TECLA <BACKSPACE>
         cout << "\b \b";       // APAGA O CARACTERE ANTERIOR
         --pos;                 // DIMINUI A QUANTIDADE DE CARACTERES LIDOS
         --s;                   // VOLTA UMA POSIÇÃO DO PONTEIRO
      }
   } while (c != 13);           // LER ENQUANTO O <Enter> NÃO FOR ACIONADO
   *s = '\0';                   // CARACTERE DE FINALIZAÇÃO DE UMA STRING
}

char *dataAtual(void) {                             // PARA CAPTURAR A DATA ATUAL DO SISTEMA
   short d, m, a;                                   // REFERENTES AO DIA, MÊS E ANO RESPECTIVAMENTE
   static char hoje[11];                            // PARA RETORNAR UM PONTEIRO DE char
   char tmp[5];                                     // MATRIZ TEMPORÁRIA
   time_t now = time(NULL);                         // CRIAÇÃO DO OBJETO
   tm *ltm = localtime(&now);                       // PONTEIRO DE ESTRUTURA tm
   a = ltm->tm_year+1900;                           // ACESSO AO MEMBRO ANO
   m = ltm->tm_mon+1;                               // ACESSO AO MEMBRO MÊS
   d = ltm->tm_mday;                                // ACESSO AO MEMBRO DIA
   sprintf(hoje, "%02d/%02d/%04d", d, m, a);        // CONSTRUÇÃO DE UMA STRING DE char NO MODELO DD/MM/AAAA
   return hoje;                                     // RETORNA O PONTEIRO DO VETOR DE char PARA A SUB-ROTINA CHAMADORA
}

unsigned long calcData(char *pdata) {               // CALCULAR DIFERENÇA, EM DIAS, DE DUAS DATAS
   unsigned long qntdias;                           // QUANTIDADE DE DIAS
   char hoje[11];                                   // ARMAZENA A DATA DO SISTEMA
   strcpy(hoje, dataAtual());                       // COPIA PARA hoje O RETORNO DE dataAtual()
   if (dateansi(pdata) > dateansi(hoje))            // SE A DATA INSERIDA FOR POSTERIOR À DATA ATUAL
      qntdias = 0;                                  // A IDADE DA PESSOA TEM IDADE ZERO
   else                                             // SE A DATA INSERIDA FOR ANTERIOR À DATA ATUAL
      qntdias = julianday(hoje) - julianday(pdata); // CÁLCULO DA DIFERENÇA
   return qntdias;                                  // RETORNA A DIFERENÇA DAS DATAS, EM DIAS
}

void escreveSemana(char *pdata) {             // ESCREVE O DIA DA SEMANA DA DATA INFORMADA
   switch (dayweek(pdata)) {                  // dayweek RETORNA O NÚMERO REFERENTE AO DIA
      case 0: cout << "sabado";        break;
      case 1: cout << "domingo";       break;
      case 2: cout << "segunda-feira"; break;
      case 3: cout << "terca-feira";   break;
      case 4: cout << "quarta-feira";  break;
      case 5: cout << "quinta-feira";  break;
      case 6: cout << "sexta-feira";   break;
   }
}

bool buscaData(char *pesq) {                                                  // INFORMA DE EXISTE UMA DATA PESQUISADA
   fstream arquivo("banco.dbc", ios_base::in | ios_base::binary);             // ABERTURA DO ARQUIVO PARA LEITURA DE DADOS EM BINÁRIO
   bool acha = false;                                                         // FLAG "LEVANTADA" QUANDO O REGISTRO É ENCONTRADO
   while (not arquivo.eof() and not acha) {                                   // ENQUANTO NÃO CHEGOU AO FINAL DO ARQUIVO E NÃO ENCONTROU
      arquivo.read(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro)); // INSERE OS DADOS DE UM REGISTRO NO OBJETO
      if (strcmp(pesq, pessoa.getData()) == 0 and pessoa.getStatus() == '1')  // SE A DATA PROCURADA CORRESPONDE AO REGISTRO E ESSE ESTÁ ATIVO
         acha = true;                                                         // "LEVANTA A FLAG" POIS ENCONTROU O REGISTRO
   }
   arquivo.flush();                                                           // ESVAZIA O BUFFER DE SAÍDA PARA O ARQUIVO
   arquivo.close();                                                           // FECHA O ARQUIVO
   return acha;                                                               // RETORNA SE ACHOU OU NÃO O REGISTRO PROCURADO
}

void escreveIdade(unsigned long qnt) {                              // ESCREVE IDADE EM DIA(S), MES(ES) E ANO(S)
   int d, m, a;                                                     // REFERENTES AO DIA, MÊS E ANO RESPECTIVAMENTE
   a = qnt / 365;                                                   // CAPTURA A QUANTIDADE DE ANOS
   qnt %= 365;                                                      // DESCONTA A QUANTIDADE DE ANOS
   m = qnt / 30;                                                    // CAPTURA A QUANTIDADE DE MESES
   qnt %= 30;                                                       // DESCONTA A QUANTIDADE DE MESES
   cout << a << " ano(s) " << m << " mes(es) " << qnt << " dia(s)"; // O VALOR QUE SOBRA EM qnt REPRESENTA A QUANTIDADE DE DIAS
}

void excluirPessoa(int pos) {                                                    // "EXCLUI" UM REGISTRO
   /// NA REALIDADE O REGISTRO NÃO É EXCLUÍDO, APENAS TEM O STATUS ALTERADO:
   pessoa.setStatus('0');                                                        // O CARACTERE '0' INDICA QUE ESTÁ INATIVO
   fstream arquivo("banco.dbc",ios_base::in | ios_base::out | ios_base::binary); // ABERTURA DO ARQUIVO PARA LEITURA E ESCRITA DE DADOS EM BINÁRIO
   arquivo.seekp(pos * sizeof(pessoa));                                          // POSICIONA O PONTEIRO NA POSICAO DO REGISTRO SOLICITADO
   arquivo.write(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro));      // GRAVA OS DADOS NO ARQUIVO NA POSIÇÃO SELECIONADA
   arquivo.flush();                                                              // ESVAZIA O BUFFER DE SAÍDA PARA O ARQUIVO
   arquivo.close();                                                              // FECHA O ARQUIVO
}

bool buscaNome(char *pesq) {                                                  // INFORMA DE EXISTE UM NOME PESQUISADO
   fstream arquivo("banco.dbc", ios_base::in | ios_base::binary);             // ABERTURA DO ARQUIVO PARA LEITURA DE DADOS EM BINÁRIO
   bool acha = false;                                                         // FLAG "LEVANTADA" QUANDO O REGISTRO É ENCONTRADO
   while (not arquivo.eof() and not acha) {                                   // ENQUANTO NÃO CHEGOU AO FINAL DO ARQUIVO E NÃO ENCONTROU
      arquivo.read(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro)); // INSERE OS DADOS DE UM REGISTRO NO OBJETO
      if (strcmp(pesq, pessoa.getNome()) == 0 and pessoa.getStatus() == '1')  // SE O NOME PROCURADO CORRESPONDE AO REGISTRO E ESSE ESTÁ ATIVO
         acha = true;                                                         // "LEVANTA A FLAG" POIS ENCONTROU O REGISTRO
   }
   arquivo.flush();                                                           // ESVAZIA O BUFFER DE SAÍDA PARA O ARQUIVO
   arquivo.close();                                                           // FECHA O ARQUIVO
   return acha;                                                               // RETORNA SE ACHOU OU NÃO O REGISTRO PROCURADO
}

int encontraPosicao(char *pesq) {                                              // RETORNA A POSIÇÃO DO REGISTRO NO ARQUIVO
   fstream arquivo("banco.dbc", ios_base::in | ios_base::binary);              // ABERTURA DO ARQUIVO PARA LEITURA DE DADOS EM BINÁRIO
   unsigned int pos = -1, contador = 0;                                        // POSIÇÃO DO REGISTRO PROCURADO E QUANTIDADE DE REGISTROS NO ARQUIVO
   bool acha = false;                                                          // FLAG "LEVANTADA" QUANDO O REGISTRO É ENCONTRADO
   while (not arquivo.eof() and not acha) {                                    // ENQUANTO NÃO CHEGOU AO FINAL DO ARQUIVO E NÃO ENCONTROU
      arquivo.read(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro));  // INSERE OS DADOS DE UM REGISTRO NO OBJETO
      if (strcmp(pesq, pessoa.getNome()) == 0 and pessoa.getStatus() == '1') { // SE O NOME PROCURADO CORRESPONDE AO REGISTRO E ESSE ESTÁ ATIVO
         acha = true;                                                          // "LEVANTA A FLAG" POIS ENCONTROU O REGISTRO
         pos = contador;                                                       // ARMAZENA A POSICAO DO REGISTRO
      }
      contador++;                                                              // INCREMENTA A QUANTIDADE DE REGISTROS
   }
   arquivo.flush();                                                            // ESVAZIA O BUFFER DE SAÍDA PARA O ARQUIVO
   arquivo.close();                                                            // FECHA O ARQUIVO
   return pos;                                                                 // RETORNA A POSIÇÃO NA QUAL O REGISTRO ESTÁ LOCALIZADO
}

void alteraData(int pos) {                                                        // ALTERA DATA DE UM REGISTRO
    cin.getline(pdata, sizeof(pdata));                                            // ENTRADA DA DATA DE NASCIMENTO
    pessoa.setData(pdata);                                                        // DEFINE O ATRIBUTO DATA NO OBJETO
    fstream arquivo("banco.dbc",ios_base::in | ios_base::out | ios_base::binary); // ABERTURA DO ARQUIVO PARA LEITURA E ESCRITA DE DADOS EM BINÁRIO
    arquivo.seekp(pos * sizeof(pessoa));                                          // POSICIONA O PONTEIRO NA POSICAO DO REGISTRO SOLICITADO
    arquivo.write(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro));      // GRAVA OS DADOS NO ARQUIVO NA POSIÇÃO SELECIONADA
    arquivo.flush();                                                              // ESVAZIA O BUFFER DE SAÍDA PARA O ARQUIVO
    arquivo.close();                                                              // FECHA O ARQUIVO
}

void alteraNome(int pos) {                                                        // ALTERA O NOME DE UM REGISTRO
    lerstr(pnome);                                                                // ENTRADA FORMATADA PARA CARACTERES MAIÚSCULOS
    pessoa.setNome(pnome);                                                        // DEFINE O ATRIBUTO NOME NO OBJETO
    fstream arquivo("banco.dbc",ios_base::in | ios_base::out | ios_base::binary); // ABERTURA DO ARQUIVO PARA LEITURA E ESCRITA DE DADOS EM BINÁRIO
    arquivo.seekp(pos * sizeof(pessoa));                                          // POSICIONA O PONTEIRO NA POSICAO DO REGISTRO SOLICITADO
    arquivo.write(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro));      // GRAVA OS DADOS NO ARQUIVO NA POSIÇÃO SELECIONADA
    arquivo.flush();                                                              // ESVAZIA O BUFFER DE SAÍDA PARA O ARQUIVO
    arquivo.close();                                                              // FECHA O ARQUIVO
}

void criarArquivo(void) {                                        // CRIA O ARQUIVO CASO ESSE NÃO EXISTA
    fstream arquivo;                                             // OBJETO PARA MANIPULAR O ARQUIVO
    arquivo.open("banco.dbc", ios_base::out | ios_base::binary); // CRIAÇÃO DO ARQUIVO PARA ESCRITA DE DADOS EM BINÁRIO
    arquivo.close();                                             // FECHA O ARQUIVO
}

short menu(void) {                                                     // MENU PRINCIPAL COM TODAS AS OPÇÕES
   short opcao;                                                        // ARMAZENA A OPCAO DO MENU
   do {
      limpa();                                                         // LIMPA A TELA E POSICIONA O CURSOR
      cout << " Menu Principal\n\n\n";
      cout << " [1] - Cadastrar registro.\n\n";
      cout << " [2] - Pesquisar registro por nome.\n\n";
      cout << " [3] - Pesquisar registro por data de nascimento.\n\n";
      cout << " [4] - Remover registro.\n\n";
      cout << " [5] - Alterar registro.\n\n";
      cout << " [0] - Sair.\n\n";
      cout << " Entre a opcao desejada: ";
      cin >> opcao;                                                    // LEITURA DA OPÇÃO DESEJADA
      cin.ignore(80, '\n');                                            // LIMPA BUFFER DO TECLADO
   } while (opcao < 0 or 5 < opcao);                                   // EVITA OPCÃO INEXISTENTE
   return opcao;                                                       // RETORNA O NÚMERO DA OPÇÃO
}

void cadastrar(void) {                                                           // INSERE UM NOVO CADASTRO NO ARQUIVO
   limpa();                                                                      // LIMPA A TELA E POSICIONA O CURSOR
   cout << " Cadastrar registro\n\n\n";
   cout << " Entre com o nome:\n ";
   lerstr(pnome);                                                                // ENTRADA FORMATADA PARA CARACTERES MAIÚSCULOS
   cout << "\n\n";
   cout << " Entre com a data de nascimento (DD/MM/AAAA):\n ";
   cin.getline(pdata, sizeof(pdata));                                            // ENTRADA DA DATA DE NASCIMENTO
   pessoa.setStatus('1');                                                        // DEFINE O ATRIBUTO STATUS COMO ATIVO
   pessoa.setNome(pnome);                                                        // DEFINE O ATRIBUTO NOME NO OBJETO
   pessoa.setData(pdata);                                                        // DEFINE O ATRIBUTO DATA NO OBJETO
   fstream arquivo;                                                              // OBJETO PARA MANIPULAR ARQUIVO
   arquivo.open("banco.dbc", ios_base::out | ios_base::app |  ios_base::binary); // ABERTURA DO ARQUIVO PARA ADIÇÃO DE DADOS EM BINÁRIO
   arquivo.seekp(0, ios::end);                                                   // POSICIONA O PONTEIRO NO FINAL DO ARQUIVO
   arquivo.write(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro));      // GRAVA OS DADOS NO ARQUIVO NA POSIÇÃO SELECIONADA
   arquivo.flush();                                                              // ESVAZIA O BUFFER DE SAÍDA PARA O ARQUIVO
   arquivo.close();                                                              // FECHA O ARQUIVO
   cout << "\n\n";
   pausa(1);                                                                     // PAUSA COM MENSAGEM ADICIONAL
}

void pesquisarData(void) {                                                       // PESQUISA POR DATA E EXIBE O REGISTRO
   limpa();                                                                      // LIMPA A TELA E POSICIONA O CURSOR
   cout << " Pesquisar registro por data\n\n\n\n";
   cout << " Entre com a data de nascimento (DD/MM/AAAA): ";
   cin.getline(pdata, sizeof(pdata));                                            // ENTRADA DA DATA DE NASCIMENTO
   cout << "\n";
   if (buscaData(pdata)) {                                                       // SE ENCONTROU O REGISTRO
      /// NESSE MOMENTO OS DADOS CORRETOS ESTÃO NOS ATRIBUTOS DO OBJETO
      cout << " Nome .........................: " << pessoa.getNome() << "\n\n"; // ESCREVE O NOME NA TELA
      cout << " Dia da semana do nascimento ..: ";
      escreveSemana(pessoa.getData());                                           // ESCREVE O DIA DA SEMANA DA DATA
      cout << "\n\n";
      cout << " Data atual do sistema ........: " << dataAtual() << " (";        // ESCREVE A DATA ATUAL DO SISTEMA
      escreveSemana(dataAtual());                                                // ESCREVE O DIA DA SEMANA DA DATA
      cout << ")\n\n";
      cout << " Idade ........................: ";
      escreveIdade(calcData(pessoa.getData()));                                  // ESCREVE IDADE EM DIA(S), MES(ES) E ANO(S)
      cout << "\n\n\n\n ";
   }
   else                                                                          // SE NÃO ENCONTROU O REGISTRO
      cout << endl << "\n Registro nao encontrado. ";
   pausa(0);                                                                     // PAUSA SEM MENSAGEM ADICIONAL
}

void pesquisarNome(void) {                                               // PESQUISA POR NOME E EXIBE O REGISTRO
   limpa();                                                              // LIMPA A TELA E POSICIONA O CURSOR
   cout << " Pesquisar registro por nome\n\n\n\n";
   cout << " Entre com o nome .......: ";
   lerstr(pnome);                                                        // ENTRADA FORMATADA PARA CARACTERES MAIÚSCULOS
   cout << "\n\n";
   if (buscaNome(pnome)) {                                               // SE ENCONTROU O REGISTRO
      /// NESSE MOMENTO OS DADOS CORRETOS ESTÃO NOS ATRIBUTOS DO OBJETO
      cout << " Data de nascimento .....: " << pessoa.getData() << " ("; // ESCREVE A DATA DE NASCIMENTO
      escreveSemana(pessoa.getData());                                   // ESCREVE O DIA DA SEMANA DA DATA
      cout << ")\n\n";
      cout << " Data atual do sistema ..: " << dataAtual() << " (";      // ESCREVE A DATA ATUAL DO SISTEMA
      escreveSemana(dataAtual());                                        // ESCREVE O DIA DA SEMANA DA DATA
      cout << ")\n\n";
      cout << " Idade ..................: ";
      escreveIdade(calcData(pessoa.getData()));                          // ESCREVE IDADE EM DIA(S), MES(ES) E ANO(S)
      cout << "\n\n\n\n ";
   }
   else                                                                  // SE NÃO ENCONTROU O REGISTRO
      cout << "\n\n Registro nao encontrado. ";
   pausa(0);                                                             // PAUSA SEM MENSAGEM ADICIONAL
}

void remover(void) {                                                           // REMOVE UM REGISTRO
   limpa();                                                                    // LIMPA A TELA E POSICIONA O CURSOR
   char opcao;                                                                 // ARMAZENA A OPCAO DO MENU
   cout << " Remover registro\n\n\n\n";
   cout << " Entre com o nome .......: ";
   lerstr(pnome);                                                              // ENTRADA FORMATADA PARA CARACTERES MAIÚSCULOS
   cout << "\n\n";
   if (buscaNome(pnome)) {                                                     // SE ENCONTROU O REGISTRO
      cout << " Data de nascimento .....: " << pessoa.getData() << "\n\n\n\n"; // ESCREVE A DATA DE NASCIMENTO
      cout << " Remover cadastro [S]im ou [N]ao: ";
      cin >> opcao;                                                            // LEITURA DA OPÇÃO DESEJADA
      cin.ignore(80, '\n');                                                    // LIMPA BUFFER DO TECLADO
      if (opcao == 'S' or opcao == 's') {                                      // SE FOR [S/s]IM
         excluirPessoa(encontraPosicao(pnome));                                // CHAMADA DA SUB-ROTINA PARA EXCLUSÃO
         cout << "\n\n\n Cadastro removido. ";
      }
      else                                                                     // SE FOR QUALQUER OUTRO CARACTERE
         cout << "\n\n\n Cadastro nao removido. ";
   }
   else                                                                        // SE NÃO ENCONTROU O REGISTRO
      cout << "\n\n Registro nao encontrado. ";
   pausa(0);                                                                   // PAUSA SEM MENSAGEM ADICIONAL
}

void alterar(void) {                                                   // MENU DE ALTERAÇÃO DE NOME OU DATA COM EXIBIÇÃO DE REGISTRO
   short opcao;                                                        // ARMAZENA A OPCAO DO MENU
   string selecao;                                                     // PARA PERSONALIZAÇÃO DE TEXTO NO MENU
   do {
      limpa();                                                         // LIMPA A TELA E POSICIONA O CURSOR
      cout << " Alterar registro\n\n\n";
      cout << " Selecione a opcao:\n\n";
      cout << " [1] - Alterar nome.\n\n";
      cout << " [2] - Alterar data de nascimento.\n\n\n";
      cout << " Entre a opcao desejada: ";
      cin >> opcao;                                                     // LEITURA DA OPÇÃO DESEJADA
      cin.ignore(80, '\n');                                             // LIMPA BUFFER DO TECLADO
   } while (opcao != 1 and opcao != 2);                                 // EVITA OPCÃO INEXISTENTE
   if (opcao == 1) selecao = "nome";                                    // PERSONALIZA OPÇÃO PARA ALTERAÇÃO DE NOME
   else selecao = "data";                                               // PERSONALIZA OPÇÃO PARA ALTERAÇÃO DE DATA
   limpa();                                                             // LIMPA A TELA E POSICIONA O CURSOR
   cout << " Alterar " << selecao << " do registro\n\n\n";
   cout << endl;
   cout << " Entre com o nome:\n ";
   lerstr(pnome);                                                       // ENTRADA FORMATADA PARA CARACTERES MAIÚSCULOS
   cout << "\n\n";
   if (buscaNome(pnome)) {                                              // SE ENCONTROU O REGISTRO
      /// NESSE MOMENTO OS DADOS CORRETOS ESTÃO NOS ATRIBUTOS DO OBJETO
      if (opcao == 1) {                                                 // SE FOI SOLICITADA A ALTERAÇÃO DE NOME
         cout << " Data de nascimento:\n ";
         cout << pessoa.getData() << "\n\n";                            // EXIBE A DATA DE NASCIMENTO
         cout << " Entre o novo nome:\n ";
         alteraNome(encontraPosicao(pnome));                            // EFETUA A ALTERAÇÃO DO NOME
      } else {                                                          // SE FOI SOLICITADA A ALTERAÇÃO DE NOME
         cout << " Data de nascimento cadastrada:\n ";
         cout << pessoa.getData() << "\n\n";                            // EXIBE A DATA DE NASCIMENTO
         cout << " Entre a nova data de nascimento:\n ";
         alteraData(encontraPosicao(pnome));                            // EFETUA A ALTERAÇÃO DA DATA
      }
      cout << "\n\n\n\n";
      pausa(1);                                                         // PAUSA COM MENSAGEM ADICIONAL
   }
   else {                                                               // SE NÃO ENCONTROU O REGISTRO
      cout << endl << "\n Registro nao encontrado. ";
      pausa(0);                                                         // PAUSA SEM MENSAGEM ADICIONAL
   }
}
