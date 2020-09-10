/// ATIVIDADE ..: AVALIA��O/PROVA (FINAL)
/// DATA .......: 28-11-2019
/// AUTOR ......: HELTON RICARDO SANTOS DA COSTA
/// CURSO ......: AN�LISE E DESENVOLVIMENTO DE SISTEMAS
/// TURMA ......: II SEMESTRE
/// PROFESSOR ..: JOSE AUGUSTO NAVARRO GARCIA MANZANO

#include <iostream>   // ENTRADA E SA�DA PADR�O
#include <cstring>    // PARA USAR strcpy() e strcmp()
#include <fstream>    // MANIPULAR ARQUIVOS
#include <conio.h>    // PARA USAR getch()
#include <ctime>      // PARA PEGAR A DATA ATUAL DO SISTEMA
#include "calendar.h" // PARA CALCULAR DIFEREN�A ENTRE DATAS
#include "manzano.h"  // LIMPAR A TELA E POSICIONAR CURSOR
using namespace std;

class Cadastro {                     // DEFINI��O DA CLASSE
   private:
      char status;                   // PARA SABER SE O CADASTRO EST� OU N�O ATIVO
      char nome[41];                 // NOME DA PESSOA
      char data[11];                 // DATA DE NASCIMENTO DA PESSOA
   public:
      void setStatus(char pstatus) { // PARA DEFINIR O STATUS
         status = pstatus;           // DEFINE O CAMPO MEMBRO COM O VALOR DO PAR�METRO
      }
      char getStatus() {             // PARA LER O STATUS
         return status;              // RETORNA O VALOR ARMAZENADO NO CAMPO MEMBRO
      }
      void setNome(char *pnome) {    // PARA DEFINIR O NOME
         strcpy(nome, pnome);        // COPIA PARA O CAMPO MEMBRO O VALOR DO PAR�METRO
      }
      char *getNome() {              // PARA LER O NOME
         return nome;                // RETORNA O VALOR ARMAZENADO NO CAMPO MEMBRO
      }
      void setData(char *pdata) {    // PARA DEFINIR A DATA
         strcpy(data, pdata);        // COPIA PARA O CAMPO MEMBRO O VALOR DO PAR�METRO
      }
      char *getData() {              // PARA LER A DATA
         return data;                // RETORNA O VALOR ARMAZENADO NO CAMPO MEMBRO
      }
};

Cadastro pessoa;                                   // INSTANCIA��O DO OBJETO pessoa
char pnome[41], pdata[11];                         // V�RIAVEIS PARA AUX�LIO DA LEITURA

void pausa(short status) {                         // PARA PAUSAR PROGRAMA E EXIBIR MENSAGEM
   if (status)                                     // PARA ESCREVER A MENSAGEM ADICIONAL
      cout << " Concluido com sucesso. ";          // MENSAGEM ADICIONAL
   cout << "Pressione <Enter> para continuar... "; // MENSAGEM PADR�O
   cin.get();                                      // SOLICITA LEITURA DE CARACTERE PARA PAUSAR EXECU��O
}

char upper(char e) {                        // TRANSFORMA CARACTERE MIN�SCULO EM MAI�SCULO
                                            // SE 97 <= CARACTERE <= 122 ENT�O ELE � MIN�SCULO\
                                            // DIMINUINDO 32 CARACTERES DELE, � RETORNADA SUA VERS�O\
                                            // MAI�SCULA CORRESPONDENTE NA TABELA ASCII
   return (97 <= e && e <= 122) ? e-32 : e;
}

void lerstr(char *s) {          // CORRIGE A ENTRADA PARA CARACTERES MAI�SCULOS
   char c;                      // USADA PARA CADA CARACTERE LIDO
   int pos = 0;                 // QUANTIDADE DE CARACTERES LIDOS
   do {
      c = upper(getch());       // ARMAZENA O CARACTERE LIDO NA VARI�VEL c
      if (isprint(c)) {         // SE c FOR UM CARACTERE QUE PODE SER IMPRESSO
         cout << c;             // IMPRIME c NA TELA
         *s++ = c;              // ADICIONA c NA POSIS�O ATUAL DO PONTEIRO E VAI PARA PR�XIMA POSI��O
         ++pos;                 // AUMENTA A QUANTIDADE DE CARACTERES LIDOS
      }
      else if (c == 8 && pos) { // SE c FOR A TECLA <BACKSPACE>
         cout << "\b \b";       // APAGA O CARACTERE ANTERIOR
         --pos;                 // DIMINUI A QUANTIDADE DE CARACTERES LIDOS
         --s;                   // VOLTA UMA POSI��O DO PONTEIRO
      }
   } while (c != 13);           // LER ENQUANTO O <Enter> N�O FOR ACIONADO
   *s = '\0';                   // CARACTERE DE FINALIZA��O DE UMA STRING
}

char *dataAtual(void) {                             // PARA CAPTURAR A DATA ATUAL DO SISTEMA
   short d, m, a;                                   // REFERENTES AO DIA, M�S E ANO RESPECTIVAMENTE
   static char hoje[11];                            // PARA RETORNAR UM PONTEIRO DE char
   char tmp[5];                                     // MATRIZ TEMPOR�RIA
   time_t now = time(NULL);                         // CRIA��O DO OBJETO
   tm *ltm = localtime(&now);                       // PONTEIRO DE ESTRUTURA tm
   a = ltm->tm_year+1900;                           // ACESSO AO MEMBRO ANO
   m = ltm->tm_mon+1;                               // ACESSO AO MEMBRO M�S
   d = ltm->tm_mday;                                // ACESSO AO MEMBRO DIA
   sprintf(hoje, "%02d/%02d/%04d", d, m, a);        // CONSTRU��O DE UMA STRING DE char NO MODELO DD/MM/AAAA
   return hoje;                                     // RETORNA O PONTEIRO DO VETOR DE char PARA A SUB-ROTINA CHAMADORA
}

unsigned long calcData(char *pdata) {               // CALCULAR DIFEREN�A, EM DIAS, DE DUAS DATAS
   unsigned long qntdias;                           // QUANTIDADE DE DIAS
   char hoje[11];                                   // ARMAZENA A DATA DO SISTEMA
   strcpy(hoje, dataAtual());                       // COPIA PARA hoje O RETORNO DE dataAtual()
   if (dateansi(pdata) > dateansi(hoje))            // SE A DATA INSERIDA FOR POSTERIOR � DATA ATUAL
      qntdias = 0;                                  // A IDADE DA PESSOA TEM IDADE ZERO
   else                                             // SE A DATA INSERIDA FOR ANTERIOR � DATA ATUAL
      qntdias = julianday(hoje) - julianday(pdata); // C�LCULO DA DIFEREN�A
   return qntdias;                                  // RETORNA A DIFEREN�A DAS DATAS, EM DIAS
}

void escreveSemana(char *pdata) {             // ESCREVE O DIA DA SEMANA DA DATA INFORMADA
   switch (dayweek(pdata)) {                  // dayweek RETORNA O N�MERO REFERENTE AO DIA
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
   fstream arquivo("banco.dbc", ios_base::in | ios_base::binary);             // ABERTURA DO ARQUIVO PARA LEITURA DE DADOS EM BIN�RIO
   bool acha = false;                                                         // FLAG "LEVANTADA" QUANDO O REGISTRO � ENCONTRADO
   while (not arquivo.eof() and not acha) {                                   // ENQUANTO N�O CHEGOU AO FINAL DO ARQUIVO E N�O ENCONTROU
      arquivo.read(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro)); // INSERE OS DADOS DE UM REGISTRO NO OBJETO
      if (strcmp(pesq, pessoa.getData()) == 0 and pessoa.getStatus() == '1')  // SE A DATA PROCURADA CORRESPONDE AO REGISTRO E ESSE EST� ATIVO
         acha = true;                                                         // "LEVANTA A FLAG" POIS ENCONTROU O REGISTRO
   }
   arquivo.flush();                                                           // ESVAZIA O BUFFER DE SA�DA PARA O ARQUIVO
   arquivo.close();                                                           // FECHA O ARQUIVO
   return acha;                                                               // RETORNA SE ACHOU OU N�O O REGISTRO PROCURADO
}

void escreveIdade(unsigned long qnt) {                              // ESCREVE IDADE EM DIA(S), MES(ES) E ANO(S)
   int d, m, a;                                                     // REFERENTES AO DIA, M�S E ANO RESPECTIVAMENTE
   a = qnt / 365;                                                   // CAPTURA A QUANTIDADE DE ANOS
   qnt %= 365;                                                      // DESCONTA A QUANTIDADE DE ANOS
   m = qnt / 30;                                                    // CAPTURA A QUANTIDADE DE MESES
   qnt %= 30;                                                       // DESCONTA A QUANTIDADE DE MESES
   cout << a << " ano(s) " << m << " mes(es) " << qnt << " dia(s)"; // O VALOR QUE SOBRA EM qnt REPRESENTA A QUANTIDADE DE DIAS
}

void excluirPessoa(int pos) {                                                    // "EXCLUI" UM REGISTRO
   /// NA REALIDADE O REGISTRO N�O � EXCLU�DO, APENAS TEM O STATUS ALTERADO:
   pessoa.setStatus('0');                                                        // O CARACTERE '0' INDICA QUE EST� INATIVO
   fstream arquivo("banco.dbc",ios_base::in | ios_base::out | ios_base::binary); // ABERTURA DO ARQUIVO PARA LEITURA E ESCRITA DE DADOS EM BIN�RIO
   arquivo.seekp(pos * sizeof(pessoa));                                          // POSICIONA O PONTEIRO NA POSICAO DO REGISTRO SOLICITADO
   arquivo.write(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro));      // GRAVA OS DADOS NO ARQUIVO NA POSI��O SELECIONADA
   arquivo.flush();                                                              // ESVAZIA O BUFFER DE SA�DA PARA O ARQUIVO
   arquivo.close();                                                              // FECHA O ARQUIVO
}

bool buscaNome(char *pesq) {                                                  // INFORMA DE EXISTE UM NOME PESQUISADO
   fstream arquivo("banco.dbc", ios_base::in | ios_base::binary);             // ABERTURA DO ARQUIVO PARA LEITURA DE DADOS EM BIN�RIO
   bool acha = false;                                                         // FLAG "LEVANTADA" QUANDO O REGISTRO � ENCONTRADO
   while (not arquivo.eof() and not acha) {                                   // ENQUANTO N�O CHEGOU AO FINAL DO ARQUIVO E N�O ENCONTROU
      arquivo.read(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro)); // INSERE OS DADOS DE UM REGISTRO NO OBJETO
      if (strcmp(pesq, pessoa.getNome()) == 0 and pessoa.getStatus() == '1')  // SE O NOME PROCURADO CORRESPONDE AO REGISTRO E ESSE EST� ATIVO
         acha = true;                                                         // "LEVANTA A FLAG" POIS ENCONTROU O REGISTRO
   }
   arquivo.flush();                                                           // ESVAZIA O BUFFER DE SA�DA PARA O ARQUIVO
   arquivo.close();                                                           // FECHA O ARQUIVO
   return acha;                                                               // RETORNA SE ACHOU OU N�O O REGISTRO PROCURADO
}

int encontraPosicao(char *pesq) {                                              // RETORNA A POSI��O DO REGISTRO NO ARQUIVO
   fstream arquivo("banco.dbc", ios_base::in | ios_base::binary);              // ABERTURA DO ARQUIVO PARA LEITURA DE DADOS EM BIN�RIO
   unsigned int pos = -1, contador = 0;                                        // POSI��O DO REGISTRO PROCURADO E QUANTIDADE DE REGISTROS NO ARQUIVO
   bool acha = false;                                                          // FLAG "LEVANTADA" QUANDO O REGISTRO � ENCONTRADO
   while (not arquivo.eof() and not acha) {                                    // ENQUANTO N�O CHEGOU AO FINAL DO ARQUIVO E N�O ENCONTROU
      arquivo.read(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro));  // INSERE OS DADOS DE UM REGISTRO NO OBJETO
      if (strcmp(pesq, pessoa.getNome()) == 0 and pessoa.getStatus() == '1') { // SE O NOME PROCURADO CORRESPONDE AO REGISTRO E ESSE EST� ATIVO
         acha = true;                                                          // "LEVANTA A FLAG" POIS ENCONTROU O REGISTRO
         pos = contador;                                                       // ARMAZENA A POSICAO DO REGISTRO
      }
      contador++;                                                              // INCREMENTA A QUANTIDADE DE REGISTROS
   }
   arquivo.flush();                                                            // ESVAZIA O BUFFER DE SA�DA PARA O ARQUIVO
   arquivo.close();                                                            // FECHA O ARQUIVO
   return pos;                                                                 // RETORNA A POSI��O NA QUAL O REGISTRO EST� LOCALIZADO
}

void alteraData(int pos) {                                                        // ALTERA DATA DE UM REGISTRO
    cin.getline(pdata, sizeof(pdata));                                            // ENTRADA DA DATA DE NASCIMENTO
    pessoa.setData(pdata);                                                        // DEFINE O ATRIBUTO DATA NO OBJETO
    fstream arquivo("banco.dbc",ios_base::in | ios_base::out | ios_base::binary); // ABERTURA DO ARQUIVO PARA LEITURA E ESCRITA DE DADOS EM BIN�RIO
    arquivo.seekp(pos * sizeof(pessoa));                                          // POSICIONA O PONTEIRO NA POSICAO DO REGISTRO SOLICITADO
    arquivo.write(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro));      // GRAVA OS DADOS NO ARQUIVO NA POSI��O SELECIONADA
    arquivo.flush();                                                              // ESVAZIA O BUFFER DE SA�DA PARA O ARQUIVO
    arquivo.close();                                                              // FECHA O ARQUIVO
}

void alteraNome(int pos) {                                                        // ALTERA O NOME DE UM REGISTRO
    lerstr(pnome);                                                                // ENTRADA FORMATADA PARA CARACTERES MAI�SCULOS
    pessoa.setNome(pnome);                                                        // DEFINE O ATRIBUTO NOME NO OBJETO
    fstream arquivo("banco.dbc",ios_base::in | ios_base::out | ios_base::binary); // ABERTURA DO ARQUIVO PARA LEITURA E ESCRITA DE DADOS EM BIN�RIO
    arquivo.seekp(pos * sizeof(pessoa));                                          // POSICIONA O PONTEIRO NA POSICAO DO REGISTRO SOLICITADO
    arquivo.write(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro));      // GRAVA OS DADOS NO ARQUIVO NA POSI��O SELECIONADA
    arquivo.flush();                                                              // ESVAZIA O BUFFER DE SA�DA PARA O ARQUIVO
    arquivo.close();                                                              // FECHA O ARQUIVO
}

void criarArquivo(void) {                                        // CRIA O ARQUIVO CASO ESSE N�O EXISTA
    fstream arquivo;                                             // OBJETO PARA MANIPULAR O ARQUIVO
    arquivo.open("banco.dbc", ios_base::out | ios_base::binary); // CRIA��O DO ARQUIVO PARA ESCRITA DE DADOS EM BIN�RIO
    arquivo.close();                                             // FECHA O ARQUIVO
}

short menu(void) {                                                     // MENU PRINCIPAL COM TODAS AS OP��ES
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
      cin >> opcao;                                                    // LEITURA DA OP��O DESEJADA
      cin.ignore(80, '\n');                                            // LIMPA BUFFER DO TECLADO
   } while (opcao < 0 or 5 < opcao);                                   // EVITA OPC�O INEXISTENTE
   return opcao;                                                       // RETORNA O N�MERO DA OP��O
}

void cadastrar(void) {                                                           // INSERE UM NOVO CADASTRO NO ARQUIVO
   limpa();                                                                      // LIMPA A TELA E POSICIONA O CURSOR
   cout << " Cadastrar registro\n\n\n";
   cout << " Entre com o nome:\n ";
   lerstr(pnome);                                                                // ENTRADA FORMATADA PARA CARACTERES MAI�SCULOS
   cout << "\n\n";
   cout << " Entre com a data de nascimento (DD/MM/AAAA):\n ";
   cin.getline(pdata, sizeof(pdata));                                            // ENTRADA DA DATA DE NASCIMENTO
   pessoa.setStatus('1');                                                        // DEFINE O ATRIBUTO STATUS COMO ATIVO
   pessoa.setNome(pnome);                                                        // DEFINE O ATRIBUTO NOME NO OBJETO
   pessoa.setData(pdata);                                                        // DEFINE O ATRIBUTO DATA NO OBJETO
   fstream arquivo;                                                              // OBJETO PARA MANIPULAR ARQUIVO
   arquivo.open("banco.dbc", ios_base::out | ios_base::app |  ios_base::binary); // ABERTURA DO ARQUIVO PARA ADI��O DE DADOS EM BIN�RIO
   arquivo.seekp(0, ios::end);                                                   // POSICIONA O PONTEIRO NO FINAL DO ARQUIVO
   arquivo.write(reinterpret_cast<char*>(&pessoa), sizeof(class Cadastro));      // GRAVA OS DADOS NO ARQUIVO NA POSI��O SELECIONADA
   arquivo.flush();                                                              // ESVAZIA O BUFFER DE SA�DA PARA O ARQUIVO
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
      /// NESSE MOMENTO OS DADOS CORRETOS EST�O NOS ATRIBUTOS DO OBJETO
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
   else                                                                          // SE N�O ENCONTROU O REGISTRO
      cout << endl << "\n Registro nao encontrado. ";
   pausa(0);                                                                     // PAUSA SEM MENSAGEM ADICIONAL
}

void pesquisarNome(void) {                                               // PESQUISA POR NOME E EXIBE O REGISTRO
   limpa();                                                              // LIMPA A TELA E POSICIONA O CURSOR
   cout << " Pesquisar registro por nome\n\n\n\n";
   cout << " Entre com o nome .......: ";
   lerstr(pnome);                                                        // ENTRADA FORMATADA PARA CARACTERES MAI�SCULOS
   cout << "\n\n";
   if (buscaNome(pnome)) {                                               // SE ENCONTROU O REGISTRO
      /// NESSE MOMENTO OS DADOS CORRETOS EST�O NOS ATRIBUTOS DO OBJETO
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
   else                                                                  // SE N�O ENCONTROU O REGISTRO
      cout << "\n\n Registro nao encontrado. ";
   pausa(0);                                                             // PAUSA SEM MENSAGEM ADICIONAL
}

void remover(void) {                                                           // REMOVE UM REGISTRO
   limpa();                                                                    // LIMPA A TELA E POSICIONA O CURSOR
   char opcao;                                                                 // ARMAZENA A OPCAO DO MENU
   cout << " Remover registro\n\n\n\n";
   cout << " Entre com o nome .......: ";
   lerstr(pnome);                                                              // ENTRADA FORMATADA PARA CARACTERES MAI�SCULOS
   cout << "\n\n";
   if (buscaNome(pnome)) {                                                     // SE ENCONTROU O REGISTRO
      cout << " Data de nascimento .....: " << pessoa.getData() << "\n\n\n\n"; // ESCREVE A DATA DE NASCIMENTO
      cout << " Remover cadastro [S]im ou [N]ao: ";
      cin >> opcao;                                                            // LEITURA DA OP��O DESEJADA
      cin.ignore(80, '\n');                                                    // LIMPA BUFFER DO TECLADO
      if (opcao == 'S' or opcao == 's') {                                      // SE FOR [S/s]IM
         excluirPessoa(encontraPosicao(pnome));                                // CHAMADA DA SUB-ROTINA PARA EXCLUS�O
         cout << "\n\n\n Cadastro removido. ";
      }
      else                                                                     // SE FOR QUALQUER OUTRO CARACTERE
         cout << "\n\n\n Cadastro nao removido. ";
   }
   else                                                                        // SE N�O ENCONTROU O REGISTRO
      cout << "\n\n Registro nao encontrado. ";
   pausa(0);                                                                   // PAUSA SEM MENSAGEM ADICIONAL
}

void alterar(void) {                                                   // MENU DE ALTERA��O DE NOME OU DATA COM EXIBI��O DE REGISTRO
   short opcao;                                                        // ARMAZENA A OPCAO DO MENU
   string selecao;                                                     // PARA PERSONALIZA��O DE TEXTO NO MENU
   do {
      limpa();                                                         // LIMPA A TELA E POSICIONA O CURSOR
      cout << " Alterar registro\n\n\n";
      cout << " Selecione a opcao:\n\n";
      cout << " [1] - Alterar nome.\n\n";
      cout << " [2] - Alterar data de nascimento.\n\n\n";
      cout << " Entre a opcao desejada: ";
      cin >> opcao;                                                     // LEITURA DA OP��O DESEJADA
      cin.ignore(80, '\n');                                             // LIMPA BUFFER DO TECLADO
   } while (opcao != 1 and opcao != 2);                                 // EVITA OPC�O INEXISTENTE
   if (opcao == 1) selecao = "nome";                                    // PERSONALIZA OP��O PARA ALTERA��O DE NOME
   else selecao = "data";                                               // PERSONALIZA OP��O PARA ALTERA��O DE DATA
   limpa();                                                             // LIMPA A TELA E POSICIONA O CURSOR
   cout << " Alterar " << selecao << " do registro\n\n\n";
   cout << endl;
   cout << " Entre com o nome:\n ";
   lerstr(pnome);                                                       // ENTRADA FORMATADA PARA CARACTERES MAI�SCULOS
   cout << "\n\n";
   if (buscaNome(pnome)) {                                              // SE ENCONTROU O REGISTRO
      /// NESSE MOMENTO OS DADOS CORRETOS EST�O NOS ATRIBUTOS DO OBJETO
      if (opcao == 1) {                                                 // SE FOI SOLICITADA A ALTERA��O DE NOME
         cout << " Data de nascimento:\n ";
         cout << pessoa.getData() << "\n\n";                            // EXIBE A DATA DE NASCIMENTO
         cout << " Entre o novo nome:\n ";
         alteraNome(encontraPosicao(pnome));                            // EFETUA A ALTERA��O DO NOME
      } else {                                                          // SE FOI SOLICITADA A ALTERA��O DE NOME
         cout << " Data de nascimento cadastrada:\n ";
         cout << pessoa.getData() << "\n\n";                            // EXIBE A DATA DE NASCIMENTO
         cout << " Entre a nova data de nascimento:\n ";
         alteraData(encontraPosicao(pnome));                            // EFETUA A ALTERA��O DA DATA
      }
      cout << "\n\n\n\n";
      pausa(1);                                                         // PAUSA COM MENSAGEM ADICIONAL
   }
   else {                                                               // SE N�O ENCONTROU O REGISTRO
      cout << endl << "\n Registro nao encontrado. ";
      pausa(0);                                                         // PAUSA SEM MENSAGEM ADICIONAL
   }
}
