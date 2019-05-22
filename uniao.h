/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#ifndef UNIAO_H
#define UNIAO_H

#include <stdio.h>

/*
	int mergeindice:
		Função para o fazer o merge de dois indices em um indice só.
	int indice1[][2]:
		matriz N x 2 chamada de indice1. 
		primeiro campo é o nroInscricao e segundo é o RRN correspondente
	int indice2[][2]:
		matriz N x 2 chamada de indice2
		primeiro campo é o nroInscricao e segundo é o RRN correspondente
	int indice3[][3]:
		matriz N x 3 chamada de indice3, indice com o resultado do merge
		primeiro campo é o nroInscricao, segundo é o RRN correspondente e terceiro é a origem
	int max1:
		tamanho máximo do indice1
	int max2:
		tamanho máximo do indice2
*/
int mergeindice(int indice1[][3], int indice2[][3], int indice3[][3], int max1, int max2);


/*
	int uniao:
		Função para realizar a funcionalidade 9 do trabalho 3.
	char* entrada1:
		string com o nome do primeiro arquivo de entrada a ser aberto
	char* entrada2:
		string com o nome do segundo arquivo de entrada a ser aberto
	char* saida:
		string com o nome do arquivo de saida a ser feito

*/
int uniao(char* entrada1, char* entrada2, char* saida);

#endif