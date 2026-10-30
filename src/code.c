#ifdef _WIN32
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"




//Definindo estruturas para facilitar a construção do código
//Estruturas para os voos
typedef struct {int dia,mes,ano;} data;
typedef struct {int h,min;} hora;

typedef struct {
  int id_a;
  int num_voo;
  char *empresa;
  char *origem;
  char *destino;
  data dpartida;
  hora hpartida;
  int qtd_passageiros;
} config_aviao;
config_aviao *aviao;

//estruturas para os passageiros
typedef struct {char *pais, *cidade, *bairro, *rua, *n, *apt;} CEP;

typedef struct {
  int codigo_u;
  char *nome;
  char id_u[12];
  CEP cep;
  char telefone[14];
  char sexo;
} config_passageiros;
config_passageiros *user;

//estrutura para passagens
typedef struct {char *val_passagem; data dcompra; int codigo_p, codigo_u_p;} PASS;

typedef struct {
  int num_voo_p;
  PASS *pass;
} config_passagens;
config_passagens *passagem;




////////////////////////////////////////////////////////        MAIN        ////////////////////////////////////////////////////////




//MAIN
int main (void){
#ifdef _WIN32
  system("chcp 65001 > nul");   //garante acentos e caracteres especiais no Windows
#endif

  //Configurando a função 'rand'
  srand (time(NULL));

  config();
  programa();
  fim();
  
  return 0;
}




void config(){
  aviao = (config_aviao*)calloc(50, sizeof(config_aviao));
  user = (config_passageiros*)calloc(100, sizeof(config_passageiros));
  passagem = (config_passagens*)calloc(50, sizeof(config_passagens));
}

//Limpa a tela de forma compatível com Windows e Linux
void limpar_tela(void){
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}




////////////////////////////////////////////////////////        MENU        ////////////////////////////////////////////////////////




//MENU
//Loop que chama cada função, a depender da escolha do usuário
int programa(){
  switch (menu()){
  
  case 1:
    voo();
    break;
    
  case 2:
    passageiros();
    break;
    
  case 3:
    passagens();
    break;
    
  case 4:
    break;
  
  case 5:
    sair();
    break;
    
  default:
    programa();  
  }  
  return 0;
}

//Imprime o menu do programa
int menu (){
  limpar_tela();
  
  //Variável que recebe o valor da resposta do usuário
  int r;
  
  char linha[100];
  FILE *mt;
  
  mt = fopen("menu.txt","r");                                       //Abrindo o arquivo no modo leitura
  if (mt==NULL) printf("Não foi possível abrir o arquivo.\n");      //conferindo se foi possível abrir
  else while (fgets(linha, 100, mt)) printf("%s", linha);           //Imprimindo o arquivo linha por linha
  fclose(mt);                                                       //Fechando o arquivo

  printf("                                ");

  scanf("%d", &r);
  
  //limpando o '\n'
  getchar();
  
  return r;
}




////////////////////////////////////////////////////////        SAIR        ////////////////////////////////////////////////////////





//SAIR
//Confirma a saída do usuário do programa
int sair(){
  limpar_tela();
  
  //Variável que recebe a resposta do usuário
  char r;
  
  printf("Você tem certeza que deseja sair?\n");
  printf("\n(digite 's' para sair, 'n' para continuar utilizando o programa...)\n(...ou 'i' se estiver indeciso!)\n\n");
  scanf("%c", &r);
  
  if (r=='i') return duvida();
  if (r=='s') return 0;
  else if (r=='n') return programa();
  else return sair();
}

//DUVIDA
//Função que ajuda o usuário a escolher se deseja ou não sair (rsrsrs)
int duvida(){
  char d, linha[100];
  FILE *dt;
  
  limpar_tela();
  
  dt = fopen ("texto_filosofico.txt", "r");                         //Abrindo o arquivo no modo leitura
  if (dt==NULL) printf("Não foi possível abrir o arquivo.\n");      //conferindo se foi possível abrir
  else while (fgets(linha, 40, dt)) printf("%s", linha);            //Imprimindo o arquivo linha por linha
  fclose(dt);                                                       //Fechando o arquivo
  
  scanf("%c", &d);
  
  if (d=='s') return 0;
  else if (d=='n')return programa();
  else return duvida();
}

//FIM
//Mensagem que aparece ao término do programa
int fim(){
  limpar_tela();

  FILE *ft;
  char linha[100];
  
  ft = fopen("despedida.txt", "r");                                 //Abrindo o arquivo no modo leitura
  if (ft==NULL) printf("Não foi possível abrir o arquivo.\n");      //conferindo se foi possível abrir
  else while (fgets(linha, 100, ft)) printf("%s", linha);           //Imprimindo o arquivo linha por linha
  fclose(ft);                                                       //Fechando o arquivo
  
  return 0;
}




////////////////////////////////////////////////////////        VOOS        ////////////////////////////////////////////////////////




//CONFERIR VOOS
//VOO
//imprime o menu da opção 'conferir vôos'
void voo(){
  int rv;
  
  limpar_tela();
  printf("Selecione uma das opções:\n\n");
  printf("1. Cadastrar um novo vôo\n");
  printf("2. Alterar dados de um vôo\n");
  printf("3. Excluir dados de um vôo\n");
  printf("4. Conferir painel de embarque\n");
  printf("5. Retornar ao menu\n\n");
  
  scanf("%d", &rv);
  getchar();
  
  switch (rv){
    case 1:
      novo_voo();
      break;
    
    case 2:
      alterar_voo();
      break;
      
    case 3:
      excluir_voo();
      break;
      
    case 4:
      painel_embarque();
      voo();
      break;
    
    case 5:
      programa();
      break;
      
    default:
      voo();
  }
}

//INFO_VOO
//Imprime todas as informações de um voo
void info_voo(int infv){
  limpar_tela();
  printf ("'Id' do avião:          %d\n", aviao[infv].id_a);
  printf ("Número do voo:          %d\n", aviao[infv].num_voo);
  printf ("Companhia aérea:        %s\n", aviao[infv].empresa);
  printf ("Origem:                 %s\n", aviao[infv].origem);
  printf ("Destino:                %s\n", aviao[infv].destino);
  printf ("Data da viagem:         ");
  //Formatando a data
  if (aviao[infv].dpartida.dia<10) printf("0%d/", aviao[infv].dpartida.dia);
  else printf("%d/", aviao[infv].dpartida.dia);
  if (aviao[infv].dpartida.mes<10) printf("0%d/", aviao[infv].dpartida.mes);
  else printf("%d/", aviao[infv].dpartida.mes);
  if (aviao[infv].dpartida.ano<10) printf("200%d\n", aviao[infv].dpartida.ano);
  else printf("20%d\n", aviao[infv].dpartida.ano);
  printf ("Horário do embarque:    ");
  //formatando o horário
  if (aviao[infv].hpartida.h<10) printf("0%d:", aviao[infv].hpartida.h);
  else printf("%d:", aviao[infv].hpartida.h);
  if (aviao[infv].hpartida.min<10) printf("0%d\n", aviao[infv].hpartida.min);
  else printf("%d\n",aviao[infv].hpartida.min);
  printf ("Máximo de passageiros:  %d\n", aviao[infv].qtd_passageiros);
}

//PAINEL_EMBARQUE
//Imprime o 'painel de embarque'
void painel_embarque(){
  limpar_tela();
  printf("                         |             |                 |         \n");
  printf("         Destino         |   Horário   |     Empresa     |   Voo   \n");
  printf("_________________________|_____________|_________________|_________\n");
  
  int cont; //conta quantos caracteres têm nas strings 'destino' e 'empresa'
  
  for (int i=0; i<50; i++){
    if (aviao[i].id_a==0) continue;
    
    cont=0;
    //Imprimindo o destino
    int lend=strlen(aviao[i].destino);
    //conferindo se há algum carácter especial (^~´`¨) 
    for (int c=0; c<lend; c++) {
      if(aviao[i].destino[c]>='a' && aviao[i].destino[c]<='z') continue;
      if(aviao[i].destino[c]>='A' && aviao[i].destino[c]<='Z') continue;
      if(aviao[i].destino[c]==' ') continue;
      else cont++;
    }
    lend -= cont/2;
    for (int e=0; e<(25-lend+1); e++) {
      if (e==((25-lend)/2)) printf("%s", aviao[i].destino);
      else printf(" ");
    }
    
    //imprimindo o horário
    if (aviao[i].hpartida.h<10) printf("|    0%d:", aviao[i].hpartida.h);
    else printf("|    %d:", aviao[i].hpartida.h);
    if (aviao[i].hpartida.min<10) printf("0%d    |", aviao[i].hpartida.min);
    else printf("%d    |", aviao[i].hpartida.min);
    
    cont=0;
    //Imprimindo o nome da empresa
    int lenn=strlen(aviao[i].empresa);
    //conferindo se há algum carácter especial (^~´`¨) 
    for (int c=0; c<lenn; c++) {
      if(aviao[i].empresa[c]>='a' && aviao[i].empresa[c]<='z') continue;
      if(aviao[i].empresa[c]>='A' && aviao[i].empresa[c]<='Z') continue;
      if(aviao[i].empresa[c]==' ') continue;
      else cont++;
    }
    lenn -= cont/2;
    for (int e=0; e<(17-lenn+1); e++) {
      if (e==((17-lenn)/2)) printf("%s", aviao[i].empresa);
      else printf(" ");
    }
    
    //Imprimindo o Id do vôo
    printf("|   %d\n", aviao[i].num_voo);
  }
  
  int voltar;
  char resp;
  printf("\n\nPara ver mais informações sobre um voo, digite o seu número.\nPara voltar para a tela anterior, digite '1'.\n\n");
  scanf("%d", &voltar);
  getchar();
  
  if (voltar>=100 && voltar<1000){
    for (int k=0; k<50; k++) {
      if (aviao[k].num_voo==voltar){
        info_voo(k);
        printf ("\n\nPressione 'enter' para voltar a tela anterior!\n");
        scanf("%c", &resp);
        painel_embarque();
        break;
      }
      else {
        painel_embarque();
        break;
      }
    }
  }
  else if (voltar!=1) painel_embarque();
}
  
//NOVO_VOO
//ID AVIAO
void id_aviao(int i){
  limpar_tela();
  char idr;
  printf("'Id' da aeronave\n\nVocê deseja inserir um número aleatório automaticamente?\n");
  printf("(digite 's' para confirmar. Para inserir o número manualmente, digite qualquer outra tecla.)\n\n");
  scanf("%c", &idr);
  getchar();
  if (idr=='s') aviao[i].id_a=rand()%90000000 + 10000000;
  else{
    limpar_tela();
    printf("Digite o 'id' da aeronave:\n(O 'id' possui 8 números!)\n\n");
    scanf("%8d", &aviao[i].id_a);
    getchar();
    if (aviao[i].id_a<10000000) aviao[i].id_a+=10000000; 
  }
}

//NÚMERO DO VOO
void numero_voo(int i){
  limpar_tela();
  char numr;
  printf("Número do voo\n\nVocê deseja inserir um número aleatório automaticamente?\n");
  printf("(digite 's' para confirmar. Para inserir o número manualmente, digite qualquer outra tecla.)\n\n");
  scanf("%c", &numr);
  getchar();
  if (numr=='s') aviao[i].num_voo=rand()%900 + 100;
  else{
    limpar_tela();
    printf("Digite o número do voo:\n(O número do vôo possuí 3 números!)\n");
    scanf("%3d", &aviao[i].num_voo);
    getchar();
    if (aviao[i].num_voo<100) aviao[i].num_voo+=100;
  }
}

//EMPRESA (OU COMPANHIA AÉREA)
void companhia_aerea(int i){
  limpar_tela();
  char *e;
  e=malloc(100*sizeof(e));
  printf("Digite o nome da companhia aérea:\n");
  fgets(e, 100, stdin);
  int lene=strlen(e);
  if (e[lene - 1] == '\n') e[lene-1] = 0;     //limpando o '\n' da string
  aviao[i].empresa=malloc(lene * sizeof(aviao[i].empresa));
  strncpy(aviao[i].empresa, e, lene);
  free(e);
}

//ORIGEM 
void origem_voo(int i){
  limpar_tela();
  char *o;
  o=malloc(100*sizeof(o));
  printf("Digite o nome de onde o voo partiu:\n");
  fgets(o, 100, stdin);
  int leno=strlen(o);
  if (o[leno - 1] == '\n') o[leno-1] = 0;     //limpando o '\n' da string
  aviao[i].origem=malloc(leno * sizeof(aviao[i].origem));
  strncpy(aviao[i].origem, o, leno);
  free(o);
}

//DESTINO
void destino_voo(int i){
  limpar_tela();
  char *d;
  d=malloc(100*sizeof(d));
  printf("Digite o nome para onde o voo se destina:\n");
  fgets(d, 100, stdin);
  int lend=strlen(d);
  if (d[lend - 1] == '\n') d[lend-1] = 0;     //limpando o '\n' da string
  aviao[i].destino=malloc(lend * sizeof(aviao[i].destino));
  strncpy(aviao[i].destino, d, lend);
  free(d);
}

//DATA
void data_voo(int i){
  limpar_tela();
  printf("Digite a data de partida do voo, usando sempre 2 dígitos:\n");
  printf("Dia:"); scanf("%d", &aviao[i].dpartida.dia);
  printf("Mês:"); scanf("%d", &aviao[i].dpartida.mes);
  printf("Ano:"); scanf("%d", &aviao[i].dpartida.ano);
}

//HORÁRIO
void horario_voo(int i){
  limpar_tela();
  printf("Digite o horário de partida do voo, usando sempre 2 dígitos:\n");
  printf("Hora  :"); scanf("%d", &aviao[i].hpartida.h);
  printf("Minuto:"); scanf("%d", &aviao[i].hpartida.min);
}

//MÁXIMO DE PASSAGEIROS
void max_passageiros(int i){
  limpar_tela();
  int max;
  printf("Digite a quantidade de passageiros que a aeronave comporta:\n");
  scanf("%d", &max);
  aviao[i].qtd_passageiros=max;
  
  //Alocando espaço para as passagens
  passagem[i].pass = (PASS*)calloc(max, sizeof(PASS));
  passagem[i].num_voo_p = aviao[i].num_voo;
}

//Cria um novo vôo usando a estrutura 'config_aviao'
void novo_voo(){
  for (int i=0; i<50; i++) {
    if (aviao[i].id_a==0){
    
      //ID AVIÃO
      id_aviao(i);

      //NÚMERO DO VOO
      numero_voo(i);
      
      //EMPRESA (OU COMPANHIA AÉREA)
      companhia_aerea(i);
      
      //ORIGEM
      origem_voo(i);
      
      //DESTINO
      destino_voo(i);
      
      //DATA
      data_voo(i);
      
      //HORÁRIO
      horario_voo(i);
      
      //MÁXIMO DE PASSAGEIROS
      max_passageiros(i);
      
      break;
    }
    else if (i==49) {
      char lock;
      limpar_tela();
      printf("Limite de voos atingido!\n(Pressione 'enter' para voltar)\n");
      scanf("%c", &lock);
    }
  }
  voo();
}

//ALTERAR_VOO
//Cria um menu para escolher o que se deseja alterar
void menu_alterar(int i){
  limpar_tela();
  info_voo(i);
  printf("\n\nQual informação você deseja alterar? Selecione uma das opções a baixo:\n\n");
  printf ("0. 'Id' do avião\n");
  printf ("1. Número do voo\n");
  printf ("2. Companhia aérea\n");
  printf ("3. Origem\n");
  printf ("4. Destino\n");
  printf ("5. Data da viagem\n");
  printf ("6. Horário do embarque\n");
  printf ("7. Máximo de passageiros\n");
  printf ("8. Alterar outro voo\n");
  printf ("9. Voltar para o menu de voos\n\n");
  int r;
  scanf("%d", &r);
  getchar();
  switch(r){
    case 0:
      id_aviao(i);
      menu_alterar(i);
      break;
      
    case 1:
      numero_voo(i);
      menu_alterar(i);
      break;
    
    case 2:
      companhia_aerea(i);
      menu_alterar(i);
      break;
    
    case 3:
      origem_voo(i);
      menu_alterar(i);
      break;
      
    case 4:
      destino_voo(i);
      menu_alterar(i);
      break;
      
    case 5:
      data_voo(i);
      menu_alterar(i);
      break;
      
    case 6:
      horario_voo(i);
      menu_alterar(i);
      break;
      
    case 7:
      max_passageiros(i);
      menu_alterar(i);
      break;
      
    case 8:
      alterar_voo();
      break;
      
    case 9:
      voo();
      break;
      
    default:
      menu_alterar(i);   
  }
}

//Altera dados que já estavam armazenados em 'aviao[]'
void alterar_voo(){
  limpar_tela();
  int numv;
  printf("Digite o número do voo que você deseja alterar os dados:\n(Para voltar ao menu, digite '1')\n");
  scanf ("%d", &numv);
  getchar();
  if (numv==1) voo();
  else{
      for (int i=0; i<50; i++){
      if (aviao[i].num_voo==numv){
        menu_alterar(i);
        break;
      }
      else if (i==49) {
        char lock;
        limpar_tela();
        printf("O número não corresponde a nenhum voo!\n(Pressione 'enter' para continuar)\n");
        scanf("%c", &lock);
        alterar_voo();
      }
    }
  }
}

//EXCLUIR_VOO
//Passa todos os dados de um voo para 0
void excluir_voo(){
  limpar_tela();
  int numv;
  printf("Digite o número do voo que você deseja excluir os dados:\n(Para voltar ao menu, digite '1')\n\n");
  scanf ("%d", &numv);
  getchar();
  if (numv==1) voo();
  else{
      for (int i=0; i<50; i++){
      if (aviao[i].num_voo==numv){
        info_voo(i);
        char resp;
        printf("\n\nVocê tem certeza que deseja excluir os dados desse voo?\n\n");
        printf("Digite 's' para confirmar. Os dados não poderão ser recuperados.\n");
        printf("Digite qualquer outra tecla para voltar a tela anterior.\n\n");
        scanf("%c", &resp);
        
        if (resp=='s'){
          aviao[i].id_a = 0;
          aviao[i].num_voo = 0;
          aviao[i].empresa = "\0";
          aviao[i].origem = "\0";
          aviao[i].destino = "\0";
          aviao[i].dpartida.dia = 0;
          aviao[i].dpartida.mes = 0;
          aviao[i].dpartida.ano = 0;
          aviao[i].hpartida.h = 0;
          aviao[i].hpartida.min = 0;
          aviao[i].qtd_passageiros = 0;
          
          voo();
          break;
        }
        
        else{
          excluir_voo();  
          break;
        }
        
      }
      else if (i==49) {
        char lock;
        limpar_tela();
        printf("O número não corresponde a nenhum voo!\n(Pressione 'enter' para voltar a tela anterior)\n");
        scanf("%c", &lock);
        excluir_voo();
      }
    }
  }
}




/////////////////////////////////////////////////////        PASSAGEIROS        ////////////////////////////////////////////////////



//PASSAGEIROS
void passageiros(){
  int r;
  
  limpar_tela();
  printf("Selecione uma das opções:\n\n");
  printf("1. Cadastrar um novo passageiro\n");
  printf("2. Alterar dados de um passageiro\n");
  printf("3. Excluir dados de um passageiro\n");
  printf("4. Consultar todos os passageiros\n");
  printf("5. Retornar ao menu\n\n");
  
  scanf("%d", &r);
  getchar();
  
  switch (r){
    case 1:
      novo_usuario();
      break;
    
    case 2:
      alterar_usuario();
      break;
      
    case 3:
      excluir_usuario();
      break;
      
    case 4:
      todos_usuarios();
      passageiros();
      break;
    
    case 5:
      programa();
      break;
      
    default:
      passageiros();
  }
}


void info_usuario(int infu){
  printf ("Código:                 %d\n", user[infu].codigo_u);
  printf ("Nome:                   %s\n", user[infu].nome);
  //formatando 'id'
  printf ("'Id':                   ");
  for (int i=0; i<11; i++){
    if(i<3) printf("%c", user[infu].id_u[i]);
    if(i==3) printf(".");
    if(i>2 && i<6) printf("%c", user[infu].id_u[i]);
    if (i==6) printf(".");
    if (i>5 && i<9) printf("%c", user[infu].id_u[i]);
    if (i==9) printf("-");
    if (i>8) printf("%c", user[infu].id_u[i]);
  }
  printf ("\nEndereço:               %s, %s, %s, Rua %s, %s, %s\n", user[infu].cep.pais, user[infu].cep.cidade, user[infu].cep.bairro, user[infu].cep.rua, user[infu].cep.n, user[infu].cep.apt);
  //formatando o telefone
  printf ("Telefone:               +");
  for (int i=0; i<13; i++){
    if (i<2) printf("%c", user[infu].telefone[i]);
    if (i==2)printf(" (");
    if (i>1 && i<4) printf("%c", user[infu].telefone[i]);
    if (i==4)printf(") ");
    if (i>3 && i<9)printf("%c", user[infu].telefone[i]);
    if (i==9)printf("-");
    if (i>8) printf("%c", user[infu].telefone[i]);
  }
  printf ("\nSexo                    ");
  if (user[infu].sexo=='m') printf("Masculino\n");
  if (user[infu].sexo=='f') printf("Feminino\n");
}

//NOVO_USUARIO
//CÓDIGO DO USUÁRIO
void codigo_usuario(int i){
  limpar_tela();
  char r;
  printf("Código do passageiro\n\nVocê deseja inserir um número aleatório automaticamente?\n");
  printf("(digite 's' para confirmar. Para inserir o número manualmente, digite qualquer outra tecla.)\n\n");
  scanf("%c", &r);
  getchar();
  if (r=='s') user[i].codigo_u=rand()%900 + 100;
  else{
    limpar_tela();
    printf("Digite o código do passageiro:\n(O código possui 3 números!)\n\n");
    scanf("%3d", &user[i].codigo_u);
    getchar();
    if (user[i].codigo_u<100) user[i].codigo_u+=100; 
  }
}

//NOME DO USUÁRIO
void nome_usuario(int i){
  limpar_tela();
  char *n;
  n=malloc(100*sizeof(n));
  printf("Digite o nome do passageiro:\n");
  fgets(n, 100, stdin);
  int lenn=strlen(n);
  if (n[lenn - 1] == '\n') n[lenn-1] = 0;     //limpando o '\n' da string
  user[i].nome=malloc(lenn * sizeof(user[i].nome));
  strncpy(user[i].nome, n, lenn);
  free(n);
}

//ID DO USUÁRIO
void id_usuario(int i){
  limpar_tela();
  char r;
  printf("'Id' do passageiro\n\nVocê deseja inserir um número aleatório automaticamente?\n");
  printf("(digite 's' para confirmar. Para inserir o número manualmente, digite qualquer outra tecla.)\n\n");
  scanf("%c", &r);
  getchar();
  if (r=='s') snprintf(user[i].id_u, sizeof(user[i].id_u), "%lld", (long long)(rand() % 90000000000LL + 10000000000LL));
  else{
    limpar_tela();
    printf("Digite o 'id' do passageiro:\n(O 'id' possui 11 números!)\n\n");
    scanf("%11s", user[i].id_u);
    getchar();
    int lenidu=strlen(user[i].id_u);
    for (int j=lenidu; j<11; j++) strcat(user[i].id_u, "0");
  }
}

//ENDEREÇO DO USUÁRIO
void endereco_usuario(int i){
  limpar_tela();
  char *e;
  e=malloc(100*sizeof(e));
  printf("Digite o endereço do passageiro:\n");
  
  printf("País  : "); 
  fgets(e, 100, stdin);
  int lene=strlen(e);
  if (e[lene - 1] == '\n') e[lene-1] = 0;     //limpando o '\n' da string
  user[i].cep.pais=malloc(lene * sizeof(user[i].cep.pais));
  strncpy(user[i].cep.pais, e, lene);
  
  printf("Cidade: "); 
  fgets(e, 100, stdin);
  lene=strlen(e);
  if (e[lene - 1] == '\n') e[lene-1] = 0;     //limpando o '\n' da string
  user[i].cep.cidade=malloc(lene * sizeof(user[i].cep.cidade));
  strncpy(user[i].cep.cidade, e, lene);
  
  printf("Bairro: ");
  fgets(e, 100, stdin);
  lene=strlen(e);
  if (e[lene - 1] == '\n') e[lene-1] = 0;     //limpando o '\n' da string
  user[i].cep.bairro=malloc(lene * sizeof(user[i].cep.bairro));
  strncpy(user[i].cep.bairro, e, lene);
  
  printf("Rua   : "); 
  fgets(e, 100, stdin);
  lene=strlen(e);
  if (e[lene - 1] == '\n') e[lene-1] = 0;     //limpando o '\n' da string
  user[i].cep.rua=malloc(lene * sizeof(user[i].cep.rua));
  strncpy(user[i].cep.rua, e, lene);
  
  printf("Número: "); 
  fgets(e, 100, stdin);
  lene=strlen(e);
  if (e[lene - 1] == '\n') e[lene-1] = 0;     //limpando o '\n' da string
  user[i].cep.n=malloc(lene * sizeof(user[i].cep.n));
  strncpy(user[i].cep.n, e, lene);
    
  printf("\nApartamento: \n(se for casa, digite apenas -)\n"); 
  fgets(e, 100, stdin);
  lene=strlen(e);
  if (e[lene - 1] == '\n') e[lene-1] = 0;     //limpando o '\n' da string
  user[i].cep.apt=malloc(lene * sizeof(user[i].cep.apt));
  strncpy(user[i].cep.apt, e, lene);
  free(e);
}

//TELEFONE DO USUÁRIO
void telefone_usuario(int i){
  limpar_tela();
  char r;
  printf("Número de telefone do passageiro\n\nVocê deseja inserir um número aleatório automaticamente?\n");
  printf("(digite 's' para confirmar. Para inserir o número manualmente, digite qualquer outra tecla.)\n\n");
  scanf("%c", &r);
  if (r=='s') snprintf(user[i].telefone, sizeof(user[i].telefone), "%lld", (long long)(rand() % 9000000000000LL + 1000000000000LL));
  else{
    limpar_tela();
    printf("Digite o telefone do passageiro:\n(Insira apenas números. Coloque o código do país e o DDD!)\n\n");
    scanf("%13s", user[i].telefone);
  }
}

//SEXO DO USUÁRIO
void sexo_usuario(int i){
  limpar_tela();
  char r;
  printf("Digite o sexo do passageiro:\n");
  printf("(digite 'f' se for 'feminino' e 'm' se for masculino.)\n\n");
  scanf("%c", &r);
  if (r=='f' || r=='m') user[i].sexo=r;
  else sexo_usuario(i);
}

//Cria um novo usuário usando a estrutura 'config_passageiros'
void novo_usuario(){
  for (int i=0; i<100; i++) {
    if (user[i].codigo_u==0){
    
      //CÓDIGO DO USUÁRIO
      codigo_usuario(i);

      //NOME DO USUÁRIO
      nome_usuario(i);
      
      //ID DO USUÁRIO
      id_usuario(i);
      
      //ENDEREÇO
      endereco_usuario(i);
      
      //TELEFONE
      telefone_usuario(i);
      
      //SEXO
      sexo_usuario(i);
      
      break;
    }
    else if (i==99) {
      char lock;
      limpar_tela();
      printf("Limite de passageiros atingido!\n(Pressione 'enter' para voltar)\n");
      scanf("%c", &lock);
    }
  }
  passageiros();
}

//ALTERAR_USUÁRIO
//Cria um menu para escolher o que se deseja alterar
void menu_alterar_u(int i){
  limpar_tela();
  info_usuario(i);
  printf("\n\nQual informação você deseja alterar? Selecione uma das opções a baixo:\n\n");
  printf ("0. Código\n");
  printf ("1. Nome\n");
  printf ("2. 'Id'\n");
  printf ("3. Endereço\n");
  printf ("4. Telefone\n");
  printf ("5. Sexo\n");
  printf ("6. Alterar outro passageiro\n");
  printf ("7. Voltar para o menu de passageiros\n\n");
  int r;
  scanf("%d", &r);
  getchar();
  switch(r){
    case 0:
      codigo_usuario(i);
      menu_alterar_u(i);
      break;
      
    case 1:
      nome_usuario(i);
      menu_alterar_u(i);
      break;
    
    case 2:
      id_usuario(i);
      menu_alterar_u(i);
      break;
    
    case 3:
      endereco_usuario(i);
      menu_alterar_u(i);
      break;
      
    case 4:
      telefone_usuario(i);
      menu_alterar_u(i);
      break;
      
    case 5:
      sexo_usuario(i);
      menu_alterar_u(i);
      break;
      
    case 6:
      alterar_usuario();
      break;
      
    case 7:
      passageiros();
      break;
      
    default:
      menu_alterar_u(i);   
  }
}

//Altera dados que já estavam armazenados em 'aviao[]'
void alterar_usuario(){
  limpar_tela();
  int numu;
  printf("Digite o número do passageiro que você deseja alterar os dados:\n(Para voltar ao menu, digite '1')\n");
  scanf ("%d", &numu);
  getchar();
  if (numu==1) passageiros();
  else{
      for (int i=0; i<100; i++){
      if (user[i].codigo_u==numu){
        menu_alterar_u(i);
        break;
      }
      else if (i==99) {
        char lock;
        limpar_tela();
        printf("O número não corresponde a nenhum passageiro!\n(Pressione 'enter' para continuar)\n");
        scanf("%c", &lock);
        alterar_usuario();
      }
    }
  }
}

void excluir_usuario(){
  limpar_tela();
  int codigo;
  printf("Digite o código do passageiro você deseja excluir os dados:\n(Para voltar ao menu, digite '1')\n\n");
  scanf ("%d", &codigo);
  getchar();
  if (codigo==1) passageiros();
  else{
      for (int i=0; i<100; i++){
      if (user[i].codigo_u==codigo){
        info_usuario(i);
        char r;
        printf("\n\nVocê tem certeza que deseja excluir os dados desse passageiro?\n\n");
        printf("Digite 's' para confirmar. Os dados não poderão ser recuperados.\n");
        printf("Digite qualquer outra tecla para voltar a tela anterior.\n\n");
        scanf("%c", &r);
        
        if (r=='s'){
          user[i].codigo_u = 0;
          user[i].nome = "\0";
          user[i].id_u[0] = '\0';
          user[i].cep.pais = "\0";
          user[i].cep.cidade = "\0";
          user[i].cep.bairro = "\0";
          user[i].cep.rua = "\0";
          user[i].cep.n = "\0";
          user[i].cep.apt = "\0";
          user[i].telefone[0] = '\0';
          user[i].sexo = '\0';
          
          printf("\n");
          passageiros();
          break;
        }
        
        else{
          excluir_usuario();  
          break;
        }
        
      }
      else if (i==99) {
        char lock;
        limpar_tela();
        printf("O número não corresponde a nenhum voo!\n(Pressione 'enter' para voltar a tela anterior)\n");
        scanf("%c", &lock);
        excluir_usuario();
      }
    }
  }
}

void todos_usuarios(){
  limpar_tela();
  printf("Lista de todos os passageiros cadastrados no sistema:\n\n");
  
  for (int i=0; i<100; i++){
    if (user[i].codigo_u == 0) continue;
    else{
    info_usuario(i);
    printf("\n\n");
    }
  }
  
  char lock;
  printf("\nDigite qualquer tecla para voltar a tela anterior!\n");
  scanf("%c", &lock);
}




/////////////////////////////////////////////////////        PASSAGENS        //////////////////////////////////////////////////////




//PASSAGENS
void passagens(){
  int r;
  
  limpar_tela();
  printf("Selecione uma das opções:\n\n");
  printf("1. Computar uma nova passagem\n");
  printf("2. Alterar dados de uma passagem\n");
  printf("3. Excluir uma passagem\n");
  printf("4. Consultar todas as passagens\n");
  printf("5. Retornar ao menu\n\n");
  
  scanf("%d", &r);
  getchar();
  
  switch (r){
    case 1:
      nova_passagem();
      break;
    
    case 2:
      //alterar_passagem();
      break;
      
    case 3:
      //excluir_passagem();
      break;
      
    case 4:
      //todas_passagens();
      break;
    
    case 5:
      programa();
      break;
      
    default:
      passagens();
  }
}

//NOVA_PASSAGEM
//QUANTIDADE DE PASSAGENS
int quantidade_passagens(int i, int ip){
  limpar_tela();
  int max=(aviao[i].qtd_passageiros-ip), qp;
  printf ("Quantas passagens para o voo %d com destino a %s você deseja computar?\n", passagem[i].num_voo_p, aviao[i].destino);
  printf ("(Há %d lugares disponíveis ainda nesse voo!)\n", max);
  scanf ("%d", &qp);
  getchar();
  if (qp>max) {
    char lock;
    printf ("O voo não possui essa quantidade de espaço suficiente!\n");
    printf ("(Pressione qualquer tecla para inserir a quantidade novamente)");
    scanf ("%c", &lock);
    return quantidade_passagens(i, ip);
  }
  return qp;
}

//CÓDIGO DA PASSAGEM
void codigo_passagem(int i, int ip){
  limpar_tela();
  char r;
  printf("Código da passagem\n\nVocê deseja inserir um número aleatório automaticamente?\n");
  printf("(digite 's' para confirmar. Para inserir o número manualmente, digite qualquer outra tecla.)\n\n");
  scanf("%c", &r);
  if (r=='s') passagem[i].pass[ip].codigo_p=rand()%900 + 100;
  else{
    limpar_tela();
    printf("Digite o código da passagem:\n(O código possui 3 números!)\n\n");
    scanf("%3d", &passagem[i].pass[ip].codigo_p);
    getchar();
    if (passagem[i].pass[ip].codigo_p<100) passagem[i].pass[ip].codigo_p+=100; 
  }
}

//ID DO USUÁRIO DA PASSAGEM
void dono_passagem(int i, int ip){
  int cp;
  limpar_tela();
  printf("Essa passagem está no nome de qual passageiro?\n");
  printf("(Insira o código do passageiro)\n");
  scanf("%d", &cp);
  getchar();
  
  for(int k=0; k<100; k++){ 
    if (user[k].codigo_u==cp) {
      passagem[i].pass[ip].codigo_u_p=cp;
      break;
    }
    else if (k==99){
      limpar_tela();
      char r;
      printf("Esse passageiro não consta no sistema!\n");
      printf("Deseja ver a lista de passageiros existentes?\n");
      printf("(Digite 's' para confirmar. Se quiser tentar outro código, digite outra tecla.)\n\n");
      scanf("%c", &r);
      getchar();
      
      if (r=='s') todos_usuarios();
      dono_passagem(i, ip);
    }
  }
}

//VALOR DA PASSAGEM
void valor_passagem(int i, int ip){
  limpar_tela();
  char *v;
  v=malloc(50*sizeof(v));
  printf("Digite o valor que foi pago na passagem:\n");
  printf("R$ ");
  fgets(v, 50, stdin);
  int lenv=strlen(v);
  if (v[lenv - 1] == '\n') v[lenv-1] = 0;     //limpando o '\n' da string
  passagem[i].pass[ip].val_passagem=malloc(lenv * sizeof(passagem[i].pass[ip].val_passagem));
  strncpy(passagem[i].pass[ip].val_passagem, v, lenv);
  free(v);
}

//DATA DA COMPRA
void data_compra(int i, int ip){
  limpar_tela();
  printf("Digite a data da compra das passagens, usando sempre 2 dígitos:\n");
  printf("Dia:"); scanf("%d", &passagem[i].pass[ip].dcompra.dia);
  printf("Mês:"); scanf("%d", &passagem[i].pass[ip].dcompra.mes);
  printf("Ano:"); scanf("%d", &passagem[i].pass[ip].dcompra.ano);
  getchar();
}

//Cria uma nova passagem usando os dados de config_passagens
void nova_passagem(){
  int nv, qp;
  limpar_tela();
  printf("Digite o número do voo correspondente a passagem que você deseja computar:\n");
  printf("(Antes de prosseguir, tenha certeza que há voos e passageiros cadastrados!)\n");
  printf("(Para voltar ao menu anterior, digite '1')\n\n");
  scanf("%d", &nv);
  getchar();
  
  if (nv==1) passagens();
  else{
    for (int i=0; i<50; i++) {
      if (passagem[i].num_voo_p==nv){
        for (int ip=0; ip<aviao[i].qtd_passageiros; ip++){
          if(passagem[i].pass[ip].codigo_p==0){
            
            //QUANTIDADE DE PASSAGENS
            qp = quantidade_passagens(i, ip);
            
            for (int k=0; k<qp; k++, ip++){
              //CÓDIGO DA PASSAGEM
              codigo_passagem(i, ip);
              
              //ID DO USUÁRIO DA PASSAGEM
              dono_passagem(i, ip);
            
              //VALOR DA PASSAGEM
              valor_passagem(i, ip);
              
              //DATA DA COMPRA
              data_compra(i, ip);
              
              break;
            }
          }
          else {
            char lock;
            printf ("Você deve ter caído em algum golpe, esse voo já está cheio!\n");
            printf ("Entre em contato com a delegacia de crimes virtuais da sua região!\n");
            printf ("(Pressione qualquer tecla para voltar ao menu anterior)\n\n");
            scanf ("%c", &lock);
            break;
          }
        }
      }
      
      else if (i==49) {
        char lock;
        limpar_tela();
        printf("Voo não encontrado!\n");
        printf("Deseja ver o painel de embarque?\n");
        printf("(Digite 's' para confirmar. Digite outra tecla para voltar a tela anterior.)\n\n");
        scanf("%c", &lock);
        if (lock=='s') painel_embarque();
      }
    }
    passagens();
  }
}


/*
  typedef struct {char *val_passagem; data dcompra; int codigo_p, codigo_u_p;} PASS;

  typedef struct {
    int num_voo_p;
    PASS *pass;
  } config_passagens;
  config_passagem *passagem;
*/

