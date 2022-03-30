#include "funcoes.h"

char **lista_de_jogadores(int n){
  int i = 0, k = 0, h = 0;

  char *nome;
  char **lista_nomes;

  lista_nomes = (char**)malloc(n*sizeof(char*));
  for(i = 0; i < n; i++){
    lista_nomes[i] = (char*)malloc(13*sizeof(char));
  }

  i = 0;

  nome = (char*)malloc(n*sizeof(char));
  do{
    printf("Digite o %d° jogador:", i+1);
    scanf("%s", nome);
    i++;
    k = strlen(nome);
    while(k < 1 || k > 12){
      printf("Numero de letras tem que ser maior do que 1 e menor que 12 \n");
      printf("Digite o %d° jogador:", i);
      scanf("%s", nome);
      k = strlen(nome);
    }
    strcpy(lista_nomes[h], nome);
    h++;
  }while(i < n);

  return lista_nomes;
}

char letra_aleatoria(){
  int inferior = 65, superior = 90;
  char letra;
  
  letra = (rand() % (superior - inferior + 1) + inferior);

  //65 e 90: Codigos da tabela ASCII referentes do alfabeto de A à Z.
  
  return letra;
}


void liberar_memoria(void *mem){
  free(mem);
  //Função de liberar memoria.
}

char *categoria_aleatoria(){
  char *categoria[5];
  int i;
  
  categoria[0] = "Nomes de pessoas";
  categoria[1] = "Nomes de cidade";
  categoria[2] = "Nomes de animais";
  categoria[3] = "Nomes de comida";
  categoria[4] = "Profissões";
  
  i = rand() % 5;

  return categoria[i];
  //Escolhe uma categoria aleatória.
}

char **jogador_aleatorio(char **lista_nomes, int n){
  int i, j, sorteado;
  char **ordem_sorteados;
  char *aux;

  ordem_sorteados = (char**)malloc(n*sizeof(char*));
  for(i = 0; i < n; i++){
    ordem_sorteados[i] = (char*)malloc(13*sizeof(char));
  }

  for(i = 0; i < n; i++){
    strcpy(ordem_sorteados[i], lista_nomes[i]);
  }
  //Embaralha a ordem de jogadores.
  for(i = n - 1; i > 0; i--){
    j = rand() % (i + 1);
    aux = ordem_sorteados[i];
    ordem_sorteados[i] = ordem_sorteados[j];
    ordem_sorteados[j] = aux;
  }
    
  return ordem_sorteados;
  //retorna a ordem dos jogadores da rodada.
}

void tempo_jogada(int n, int* v, int* tempo_rodada, char** ordem_jogadores, char** lista_nomes, char letra, char* categoria){
  
  int tempo = 8+(2*n);
  int cont, cont2, maior;
  int *c;
  int tempo_total;
  int i, j = 0, tamanho;
  char primeira_letra;
  char *palavra;
  char *palavra_repetida;
  char **respostas;
  char **respostas_ordenadas;
  struct timeval tempo_inicio, tempo_final;

  respostas = (char**)malloc(n*sizeof(char*));
  for(i = 0; i < n; i++){
    respostas[i] = (char*)malloc(n*sizeof(char));
  }
  
  respostas_ordenadas = (char**)malloc(n*sizeof(char*));
  for(i = 0; i < n; i++){
    respostas_ordenadas[i] = (char*)malloc(n*sizeof(char));
  }

  palavra_repetida = (char*)malloc(n*sizeof(char));
  c = (int*)malloc(n*sizeof(int));

  for(i = 0; i < n; i++){
    printf("%s, digite sua resposta em ate %ds:", ordem_jogadores[i], tempo);
    
    gettimeofday(&tempo_inicio, NULL);
    limpa_fgets(respostas[i]);
    palavra = respostas[i];
    primeira_letra = palavra[0];
    nome_de_pessoa(palavra, categoria);
    tamanho = strlen(respostas[i]); 
    tempo_total = tempo_final.tv_sec - tempo_inicio.tv_sec;   
  
    do{
      if(tamanho > 30){
        printf("Você extrapolou o número permitido de caracteres(30) \n");
        printf("%s, digite sua resposta em ate %ds:", ordem_jogadores[i], tempo);
        limpa_fgets(respostas[i]);
        palavra = respostas[i];
        primeira_letra = palavra[0];
        nome_de_pessoa(palavra, categoria);
        tamanho = strlen(respostas[i]); 
      }else if(letra != primeira_letra && primeira_letra != letra + 32){
        printf("É necessario ter a mesma letra \n");
        printf("%s, digite sua resposta em até %ds:", ordem_jogadores[i], tempo);
        limpa_fgets(respostas[i]);
        palavra = respostas[i];
        primeira_letra = palavra[0];
        nome_de_pessoa(palavra, categoria);
        tamanho = strlen(respostas[i]);       
      }
      
    }while((tamanho > 30 && tempo_total < tempo) || (letra != primeira_letra && primeira_letra != letra + 32));
    gettimeofday(&tempo_final, NULL);
    tempo_total = tempo_final.tv_sec - tempo_inicio.tv_sec;
    system("clear");
    if(tempo_total > tempo){
      respostas[i] = "\0";
      tamanho = 1;
      printf("%s, Você excedeu seu tempo e sua resposta foi desconsiderada \n", ordem_jogadores[i]);
    }

    tempo = tempo - 2;
    
    //Ordena o resultado da rodada de acordo com lista_nomes.
    
    if(strcmp(lista_nomes[i], ordem_jogadores[i]) == 0){
      v[i] = tamanho - 1;
      tempo_rodada[i] += tempo_total;   
      strcpy(respostas_ordenadas[i],respostas[i]);
    }

    if(strcmp(lista_nomes[i], ordem_jogadores[i]) != 0){
      for(j = 0; j < n; j++){
        if(strcmp(lista_nomes[j], ordem_jogadores[i]) == 0){
          v[j] = tamanho - 1;
          tempo_rodada[i] += tempo_total;
          strcpy(respostas_ordenadas[j],respostas[i]);  
        }
      }
    }
  }
  
  
  for(i = 0; i < n; i++){
    cont = 1;
    // Divide o escore se as palavras forem iguais.
    for(j = 0; j < i; j++){
      if((strcmp(respostas_ordenadas[j], respostas_ordenadas[i]) == 0) && j != i){
        cont += 1; 
        palavra_repetida = respostas_ordenadas[i];
      }
    }
    //Vetor que guarda o número de vezes que tem uma palvra repetida.
    if(cont <= 1){
      c[i] = 0;
    }else{
      c[i] = cont;
    }
  }

  maior = 0;
  for(i = 0; i < n; i++){
    if(c[i] > maior){
      maior = c[i];
    }
  }

  for(i = 0; i < n; i++){
    if(c[i] <= maior && (strcmp(respostas_ordenadas[i], palavra_repetida) == 0)){
      c[i] = maior;
    }
  }

  for(i = 0; i < n; i++){
    if(c[i] != 0 && (strcmp(respostas_ordenadas[i], palavra_repetida) == 0)){
      tamanho = strlen(respostas_ordenadas[i]);
      tamanho = tamanho - 1; //remove o valor do caractere nulo
      if((tamanho % c[i]) != 0){
        tamanho = (tamanho/c[i]) + 1;
      }else{
        tamanho = tamanho/c[i];
      } 
      v[i] = tamanho;
    }
  }

  printf("Jogadas realizadas:\n");
  for(i = 0; i < n; i++){
    printf("%s: %s", ordem_jogadores[i], respostas[i]);
  }
  printf("\n");
  //Essa função pega as respostas dos jogadores, calcula o tempo de resposta, calcula o tamanho da palavra de todas as respostas e preenche alguns vetores que serão usados depois.
}

void nome_de_pessoa(char *palavra, char* categoria){
  if(!strcmp(categoria,"Nomes de pessoas")){
    palavra = strchr(palavra, 32);
    if(palavra != NULL){
      *palavra = '\n';
      *(palavra + 1) = '\0';
    }
  }
  //Checa se a categoria da rodada é 'nome de pessoas' e remove o segundo nome, a partir da leitura do espaço(ASCII 32).
}

void limpa_rodada(){
  int enter;
  printf("Aperte ENTER para começar a rodada");
  getchar();
  system("clear");
  //Limpa a tela apos a rodada jogada.
}

void limpa_fgets(char* resposta){
  int i;
  if (fgets(resposta, 33, stdin)) {
    if (strchr(resposta, '\n') == NULL){
      while ((i = getchar()) != '\n') {
        if (i < 0){
          exit(EXIT_FAILURE); 
        }
      }
    }
  }
  //Recebe a palavra pelo fgets, e se ela for maior que 30 caracteres, o resto é jogado fora.
} 

int** aloca_m(int n){
  int **m, i;
  m = (int**)malloc(5*sizeof(int*));
  for(i = 0; i < 5; i++){
    m[i] = (int*)malloc(n*sizeof(int));
  }

  return m;
  //Aloca uma matriz .
}

int* aloca_total(int n){
  int *total;
  total = (int*)calloc(n, sizeof(int));

  return total;
  //Aloca um vetor que tem todos os elementos iguais a zero.
}

void pontuacao(int i, int *v, int n, int** m, char** ordem_jogadores, char** lista_nomes, int* total){ 
  int j, k, r, aux, aux2;
  
  for(j = 0; j < n; j++){
    m[i][j] = v[j];
  }

  for(j = 0; j < n; j++){
    total[j] += m[i][j];
  }

  printf("Tabela de escores\nRodada %d:\n", i + 1);

  for(j = 0; j < n; j++){
    printf("%s: %d\n", lista_nomes[j], v[j]);
  }

  if(i == 4){
    printf("Total final: \n");
  }else{
    printf("Total parcial :\n");
  }

  for(j = 0; j < n; j++){
    printf("%s: %d\n", lista_nomes[j], total[j]);
  }

  printf("\n");
  //Essa função calcula a pontuação dos jogadores.
}

int ganhador(int* total, int* tempo_rodada, int n){
  int maior, menor, i, j, k, cont = 1, menor_tempo = 100;
 
  maior = -1;
  menor = 200;

  for(i = 0; i < n; i++){
    if(total[i] > maior){
      maior = total[i];
      k = i;
    }
  }

  for(i = 0; i < n; i++){
    if(total[i] == maior){
      cont += 1;
    }
  }

  if(cont >= 2){
    for(i = 0; i < n; i++){
      if(total[i] == maior && tempo_rodada[i] < menor_tempo){
        menor_tempo = tempo_rodada[i];
        k = i;
      }
    }
  }

  return k;
  //Essa finção indica em que posição está o ganhador do jogo.
}