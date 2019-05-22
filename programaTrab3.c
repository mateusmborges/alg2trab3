/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#include "ordenacao.h"
#include "uniao.h"
#include "interseccao.h"
#include "auxlib.h"

int main(){
	
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para laços for
		func = inteiro para armazenar a funcionalidade
		arquivos = strings com os arquivos a serem lidos ou escritos
		entrada = string para armazenar a entrada lida de stdin
	*/
	int i, func;
	char arquivos[3][30], entrada[100];		

	//para printar os acentos certos
	setlocale(LC_CTYPE,"Portuguese"); 
	
	//limpa as strings arquivos
	for(i = 0; i < 3; i++){
		clearstring(arquivos[i],30);
	}

	clearstring(entrada,100);		//limpa a entrada
	fgets(entrada,100,stdin);		//pega a entrada

	//funcao para gerar strings dos arquivos
	char *token = strtok(entrada, " ");
	for(i = 0; i < 4; i++){
		if(i == 0 && token){
			func = strtol(token,NULL,10);
		}
		if(i == 1 && token){
			strcpy(arquivos[0],token);
		}
		if(i == 2 && token){
			strcpy(arquivos[1],token);
		}
		if(i == 3 && token){
			strcpy(arquivos[2],token);
		}
		token = strtok(NULL," ");	
	}

	//tira os \n e \r das strings, se tiver
	for(i = 0; i < 3; i++){
		trim(arquivos[i]);
	}

	//verificar qual é a funcionalidade escolhida
	switch(func){
		//se for a funcionalidade 2
		case 2:
			//recuperacao(readFile);
		break;
		//se for a funcionalidade 5
		case 5:
			//remocao(readFile, n);
		break;
		//se for a funcionalidade 6
		case 6:
			//insercao(readFile, n);
		break;
		//se for a funcionalidade 7
		case 7:
			//atualizacao(readFile, n);
		break;
		//se for a funcionalidade 8
		case 8:
			ordenacao(arquivos[0], arquivos[1]);
		break;
		//se for a funcionalidade 9
		case 9:
			uniao(arquivos[0], arquivos[1], arquivos[2]);
		break;
		//se for a funcionalidade 10
		case 10:
			interseccao(arquivos[0], arquivos[1], arquivos[2]);
		break;
		//caso nao exista a funcionalidade ainda
		default:
			printf("Funcionalidade %d não implementada.\n",func);
			return ERR_NOTFUNC;
	}

	return 0;
}
