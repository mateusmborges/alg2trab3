/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#include "ordenacao.h"
#include "auxlib.h"


int ordenacao(char* inFile, char* outFile){

	/* 	DECLARAÇÃO DE VARIÁVEIS 
		status = char para verificar qual é o status do arquivo	
		regrem = char para verificar qual é o status do registro
		qtdmaxreg = quantidade máxima de registros
	*/


	//cria e verifica se o arquivo inFile existe
	FILE *arqentrada = fopen(inFile, "rb");
	if(!arqentrada){
		printf("Falha no processamento do arquivo.");
		return ERR_NOTFILE;
	}
	//cria e verifica se o arquivo outFile existe
	FILE *arqsaida = fopen(outFile, "wb");
	if(!arqsaida){
		printf("Falha no processamento do arquivo.");
		return ERR_NOTFILE;
	}
	//verifica se o arquivo de entrada está consistente ou não
	fread(&status,sizeof(char),1,arqentrada);
	if(status == '0'){
		printf("Falha no processamento do arquivo.");
		return ERR_NOTCONSIST;
	}
	//verifica se o arquivo de saida está consistente ou não
	fread(&status,sizeof(char),1,arqsaida);
	if(status == '0'){
		printf("Falha no processamento do arquivo.");
		return ERR_NOTCONSIST;
	}

	fseek(arqentrada,0,SEEK_END);
	qtdmaxreg = ((ftell(arqentrada) - 16000) / 80) + 2;

	fseek(arqentrada,16000,SEEK_SET);

	//enquanto tiver arquivo pra ler
	while(arqentrada){
		fread(&regrem,sizeof(char),1,arqentrada);	//le o primeiro byte do registro para verificar se ele está removido
		//se o registro não estiver removido
		if(regrem == '-'){

		}
		//se estiver removido
		else{
			fseek(arqentrada,79,SEEK_CUR);	//pula pro proximo registro
		}
	} //acaba o while arqentrada


	return 0;
}