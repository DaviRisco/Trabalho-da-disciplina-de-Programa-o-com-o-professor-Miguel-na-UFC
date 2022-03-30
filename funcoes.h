#ifndef funcoes_h
#define funcoes_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

char **lista_de_jogadores(int);
char letra_aleatoria();
char *categoria_aleatoria();
char **jogador_aleatorio(char **, int);
void tempo_jogada(int, int*, int*, char **, char**, char, char*);
void liberar_memoria(void *);
void nome_de_pessoa(char*, char*);
void limpa_rodada();
void limpa_fgets(char*);
void pontuacao(int, int*, int, int**, char**, char**, int*);
int** aloca_m(int);
int* aloca_total(int);
int ganhador(int*, int*, int);

#endif