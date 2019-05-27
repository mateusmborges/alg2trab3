/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#include "interseccao.h"
#include "auxlib.h"

int matchindice(int indice1[][3], int indice2[][3], int indice3[][3], int max1, int max2){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i1 = acumulador para percorrer o vetor indice1
		i2 = acumulador para percorrer o vetor indice2
		i3 = acumulador para percorrer o vetor indice3
	*/
	int i1 = 0, i2 = 0, i3 = 0, match = 0;

	while(1){
		//se coluna 1 for igual a coluna 2
		if(indice1[i1][0] == indice2[i2][0]){
			indice3[i3][0] = indice1[i1][0];//coluna 3 recebe coluna 1
			indice3[i3][1] = indice1[i1][1];//guarda o rrn
			i1++;							//incrementa i1
			i2++;							//incrementa i2
			i3++;							//incrementa i3
			match++;
		}
		//se a coluna 1 for menor que a coluna 2
		else if(indice1[i1][0] < indice2[i2][0]){
			i1++;							//incrementa i1
		}
		else if(indice1[i1][0] > indice2[i2][0]){
			i2++;							//incrementa i2
		}
		
		//se algum dos dois indices acabaram, acaba a função
		if(i1 >= max1 && i2 >= max2){
			return match;
		}
	}
}

int interseccao(char* entrada1, char* entrada2, char* saida){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para loops
		j = variavel para loops
		qtdmaxreg1 = inteiro para guardar a quantidade máxima de registros do arquivo de entrada 1
		qtdmaxreg2 = inteiro para guardar a quantidade máxima de registros do arquivo de entrada 2
		max1 = inteiro para guardar a quantidade total de registros não removidos do arquivo de entrada 1
		max2 = inteiro para guardar a quantidade total de registros não removidos do arquivo de entrada 2
		qtdreg3 = inteiro para guardar a quantidade de registros não removidos do arquivo de saida
		menosum = constante -1
		status = char para verificar qual é o status do arquivo	
	*/
	int i, j, qtdmaxreg1 = 0, qtdmaxreg2 = 0, max1 = 0, max2 = 0, qtdreg3 = 0;
	const int menosum = -1;
	char status;

	//cria e verifica se o arquivo inFile existe
	FILE *arqentrada1 = fopen(entrada1, "rb");
	if(!arqentrada1){
		printf("Falha no processamento do arquivo.");
		return ERR_NOTFILE;
	}
	FILE *arqentrada2 = fopen(entrada2, "rb");
	if(!arqentrada2){
		printf("Falha no processamento do arquivo.");
		return ERR_NOTFILE;
	}
	//cria e verifica se o arquivo outFile existe
	FILE *arqsaida = fopen(saida, "w+b");
	if(!arqsaida){
		printf("Falha no processamento do arquivo.");
		return ERR_NOTFILE;
	}
	//verifica se o arquivo de entrada1 está consistente ou não
	fread(&status,sizeof(char),1,arqentrada1);
	if(status == '0'){
		printf("Falha no processamento do arquivo.");
		return ERR_NOTCONSIST;
	}
	//verifica se o arquivo de entrada2 está consistente ou não
	fread(&status,sizeof(char),1,arqentrada2);
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

	//verifica quantos registros tem no primeiro arquivo de entrada
	fseek(arqentrada1,0,SEEK_END);
	qtdmaxreg1 = ((ftell(arqentrada1) - 16000) / 80);
	
	//verifica quantos registros tem no segundo arquivo de entrada
	fseek(arqentrada2,0,SEEK_END);
	qtdmaxreg2 = ((ftell(arqentrada2) - 16000) / 80);

	//cria as estruturas dos registros
	struct registro reg1[qtdmaxreg1];
	struct registro reg2[qtdmaxreg2];
	struct registro reg3[qtdmaxreg1+qtdmaxreg2];

	//matriz de inteiros para guardar o nroInscricao e o RRN do arquivo de entrada 1: indice1[nroInscricao][RRNcorrespondente]
	int indice1[qtdmaxreg1][3];
	//matriz de inteiros para guardar o nroInscricao e o RRN do arquivo de entrada 2: indice2[nroInscricao][RRNcorrespondente]
	int indice2[qtdmaxreg2][3];
	//matriz de inteiros para guardar o nroInscricao e o RRN do arquivo de entrada 3 e a origem: indice3[nroInscricao][RRNcorrespondente][origem]
	int indice3[qtdmaxreg1+qtdmaxreg2][3];
	
	//limpa as matrizes dos indices 1 a 3
	for(i = 0; i < qtdmaxreg1+qtdmaxreg2; i++){
		if(i < qtdmaxreg1){
			for(j = 0; j < 3; j++){
				indice1[i][j] = -1;
			}
		}
		if(i < qtdmaxreg2){
			for(j = 0; j < 3; j++){
				indice2[i][j] = -1;
			}
		}
		for(j = 0; j < 3; j++){
			indice3[i][j] = -1;
		}
	}

	//gera os registros a partir dos arquivos de entrada
	max1 = gerarregistros(reg1,qtdmaxreg1,arqentrada1);
	max2 = gerarregistros(reg2,qtdmaxreg2,arqentrada2);

	//funcao para gerar os "indices" dos arquivos de entrada
	gerarindice(indice1,reg1,max1);
	gerarindice(indice2,reg2,max2);

	//dá um merge nos dois indices
	matchindice(indice1,indice2,indice3,max1,max2);

	//conta quantos registros não removidos existem e guarda em qtdreg
	for(i = 0; i < max1+max2; i++){
		if(indice3[i][0] == -1){
			qtdreg3 = i;
			break;
		}
		qtdreg3 = max1+max2;
	}

	//volta pro começo dos arquivos para clonar o cabeçalho
	fseek(arqentrada1,0,SEEK_SET);
	fseek(arqsaida,0,SEEK_SET);
	//copia o cabecalho do arquivo de entrada para o arquivo de saida
	clonebin(arqentrada1, arqsaida, 16000);

	//volta pro começo do cabeçalho e atualiza o status('0') e o topoPilha (-1)
	fseek(arqsaida,0,SEEK_SET);
	status = '0';
	fwrite(&status,sizeof(char),1,arqsaida);
	fwrite(&menosum,sizeof(int),1,arqsaida);

	//volta pro começo dos registros
	fseek(arqsaida,16000,SEEK_SET);

	//escreve todos os registros de volta no arquivo de saida
	writeallregbin(indice3,qtdreg3,reg1,arqsaida);

	//volta pro começo do cabeçalho e atualiza o status('1')
	fseek(arqsaida,0,SEEK_SET);
	status = '1';
	fwrite(&status,sizeof(char),1,arqsaida);

	//printa o arquivo no stdout com a função feita pelo monitor
	binarioNaTela1(arqsaida);

	fclose(arqentrada1);
	fclose(arqentrada2);
	fclose(arqsaida);

	return 0;
}