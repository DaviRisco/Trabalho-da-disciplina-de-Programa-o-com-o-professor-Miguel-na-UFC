#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "./funcoes.h"

int main(int narg, char *argv[]) {

  int n, i = 0, j = 0, k = 0, h = 0, c = 0, p;
  int* v;
  int* total;
  int* tempo_rodada;
  int** m;
  char** lista_nomes;
  char** ordem_jogadores;
  char** lista_categorias;
  char* categoria;
  char* lista_letras;
  char letra;


  srand(time(NULL));
  
  // n = número de jogadores
  // i, j, k, h, p são variáveis
  
  do{
    printf("Digite a quantidades de jogadores(>=2 e <=10): ");
    scanf("%d", &n);
    if(n < 2 || n > 10){
      printf("Quantidade de jogadores invalida \n");
    }
  }while(n < 2 || n > 10);
  
  lista_nomes = lista_de_jogadores(n);
  while ((getchar()) != '\n'); //Limpa o buffer dos scanf anteriores.

  v = (int*)malloc(n*sizeof(int));
  lista_letras = (char*)malloc(5*sizeof(int));
  m = aloca_m(n);
  tempo_rodada = aloca_total(n);
  total = aloca_total(n);

  //RODADAS
  for(i = 0; i < 5; i++){

    //Escolhe a letra da rodada sem repetição.
    letra = letra_aleatoria();
    lista_letras[i] = letra;
    for(j = 0; j < i; j++){
      while(lista_letras[j] == letra){
        letra = letra_aleatoria();
        lista_letras[i] = letra;
      }
    }

    printf("A letra desta rodada é: %c \n", letra);
    
    //Escolhe a categoria da rodada sem repetição.
    categoria = categoria_aleatoria();    
    lista_categorias[i] = categoria;
    for(j = 0; j < i; j++){
      while(strcmp(lista_categorias[j], lista_categorias[i]) == 0){
        categoria = categoria_aleatoria();    
        lista_categorias[i] = categoria;
      }
    }
    printf("A categoria da rodada é: %s \n", categoria);

    ordem_jogadores = jogador_aleatorio(lista_nomes, n);
    
    printf("Essa é a ordem dos jogadores: \n");
    for(j = 0; j < n; j++){
      printf("Jogador %d: %s\n", j+1, ordem_jogadores[j]);
    }
    limpa_rodada();
    tempo_jogada(n, v, tempo_rodada, ordem_jogadores, lista_nomes, letra, categoria);
    pontuacao(i, v, n, m, ordem_jogadores, lista_nomes, total);
    
    if(i == 4){ 
      p = ganhador(total, tempo_rodada, n);
      printf("O ganhador é %s", lista_nomes[p]);
    }
  }
  
  //Libera as memórias do que foi alocado.

  for(i = 0; i < n; i++){
    liberar_memoria(lista_nomes[i]);
  } 
  liberar_memoria(lista_nomes);

  for(i = 0; i < n; i++){
    liberar_memoria(ordem_jogadores[i]);
  }
  liberar_memoria(ordem_jogadores);
  
  liberar_memoria(v);
  liberar_memoria(lista_letras);
  liberar_memoria(tempo_rodada);
  printf("\n");
  
  return EXIT_SUCCESS;
}