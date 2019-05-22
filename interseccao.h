/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#ifndef INTERSECCAO_H
#define INTERSECCAO_H

#include <stdio.h>

/*
	int matchindice:
		Função para o fazer o match de dois indices em um indice só.
	int indice1[][2]:
		matriz N x 2 chamada de indice1. 
		primeiro campo é o nroInscricao e segundo é o RRN correspondente
	int indice2[][2]:
		matriz N x 2 chamada de indice2
		primeiro campo é o nroInscricao e segundo é o RRN correspondente
	int indice3[][2]:
		matriz N x 2 chamada de indice3, indice com o resultado do match
		primeiro campo é o nroInscricao, segundo é o RRN correspondente do indice 1
	int max1:
		tamanho máximo do indice1
	int max2:
		tamanho máximo do indice2
*/
int matchindice(int indice1[][3], int indice2[][3], int indice3[][3], int max1, int max2);

/*
	int interseccao:
		Função para realizar a funcionalidade 10 do trabalho 3.
	char* entrada1:
		string com o nome do primeiro arquivo de entrada a ser aberto
	char* entrada2:
		string com o nome do segundo arquivo de entrada a ser aberto
	char* saida:
		string com o nome do arquivo de saida a ser feito

*/
int interseccao(char* entrada1, char* entrada2, char* saida);

#endif