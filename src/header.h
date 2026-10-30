//Inicializando as funções
//(As funções aparecem nessa ordem no programa)

  //Funções iniciais
  void config();
  int programa();
  int menu();
  
  //funções finais
  int sair();
  int duvida();
  int fim();
  
  //funções relacionadas ao voo/avião
  int voo();
  void info_voo(int infv);
  void painel_embarque();
  void id_aviao(int i);//funções para criar um voo
  void numero_voo(int i);
  void companhia_aerea(int i);
  void origem_voo(int i);
  void destino_voo(int i);
  void data_voo(int i);
  void horario_voo(int i);
  void max_passageiros(int i);
  void novo_voo();
  void menu_alterar(int i);//funções para alteração de dados 
  void alterar_voo();
  void excluir_voo();//função para excluir voos
  
  //funções relacionadas aos passageiros
  int passageiros();
  void info_usuario(int infu);
  void codigo_usuario(int i);//funções para criar um novo usuário
  void nome_usuario(int i);
  void id_usuario(int i);
  void endereço_usuario(int i);
  void telefone_usuario(int i);
  void sexo_usuario(int i);
  void novo_usuario();
  void menu_alterar_u(int i);//funções para alteração de dados 
  void alterar_usuario();
  void excluir_usuario();
  void todos_usuarios();
  
  //funções relacionadas as passagens
  int passagens();
  int quantidade_passagens(int i, int ip);//funções para computar uma nova passagem
  void codigo_passagem(int i, int ip);
  void dono_passagem(int i, int ip);
  void valor_passagem(int i, int ip);
  void data_compra(int i, int ip);
  void nova_passagem();
  
