/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#include "uniao.h"
#include "auxlib.h"

int mergeindice(int indice1[][3], int indice2[][3], int indice3[][3], int max1, int max2){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i1 = acumulador para percorrer o vetor indice1
		i2 = acumulador para percorrer o vetor indice2
		i3 = acumulador para percorrer o vetor indice3
		maior = inteiro que guarda quem é maior, max1 ou max2
	*/
	int i1 = 0, i2 = 0, i3 = 0, maior;

	//ve qual é maior, max1 ou max2
	if(max1 > max2){
		maior = max1;
	}
	else{
		maior = max2;
	}

	//enquanto não acabaram os indices
	while(i3 < max1+max2){
		//se o numero de inscricao do indice 1 for menor que o nroInsc do indice 2
		if(indice1[i1][0] < indice2[i2][0]){
			//se i1 chegar a max2
			if(i1 >= max1){
				indice3[i3][0] = indice2[i2][0];//nroInsc do indice 3 recebe o nroInsc do indice 2
				indice3[i3][1] = indice2[i2][1];//guarda o rrn
				indice3[i3][2] = 2;				//coloca a origem
				//se i2 for menor que max2
				if(i2 < max2){
					i2++;						//incrementa i2
				}
				i3++;							//incrementa i3
			}
			//se i1 for menor que max1
			else{
				indice3[i3][0] = indice1[i1][0];//nroInsc do indice 3 recebe o nroInsc do indice 1
				indice3[i3][1] = indice1[i1][1];//guarda o rrn
				indice3[i3][2] = 1;				//coloca a origem
				//se i1 for menor que max1
				if(i1 < max1){
					i1++;						//incrementa i1
				}
				i3++;							//incrementa i3
			}
		}
		//nroInsc do indice 2 é menor que o nroInsc do indice 1
		else if(indice1[i1][0] > indice2[i2][0]){
			//se i2 chegar a max2
			if(i2 >= max2){
				indice3[i3][0] = indice1[i1][0];//nroInsc do indice 3 recebe o nroInsc do indice 1
				indice3[i3][1] = indice1[i1][1];//guarda o rrn
				indice3[i3][2] = 1;				//coloca a origem
				//se i1 for menor que max1
				if(i1 < max1){
					i1++;						//incrementa i1
				}
				i3++;							//incrementa i3
			}
			//se i2 for menor que max2
			else{
				indice3[i3][0] = indice2[i2][0];//nroInsc do indice 3 recebe o nroInsc do indice 2
				indice3[i3][1] = indice2[i2][1];//guarda o rrn
				indice3[i3][2] = 2;				//coloca a origem
				//se i2 for menor que max2
				if(i2 < max2){
					i2++;						//incrementa i2
				}
				i3++;							//incrementa i3
			}
		}
		//se os dois numeros de inscricao forem iguais
		else if(indice1[i1][0] == indice2[i2][0]){
			indice3[i3][0] = indice1[i1][0];//nroInsc do indice 3 recebe o nroInsc do indice 1
			indice3[i3][1] = indice1[i1][1];//guarda o rrn
			indice3[i3][2] = 1;				//coloca a origem
			//se i1 for menor que max1
			if(i1 < max1){
				i1++;						//incrementa i1
			}
			//se i2 for menor que max2
			if(i2 < max2){
				i2++;						//incrementa i2
			}
			i3++;							//incrementa i3
		}
	}
	return 1;
}

int uniao(char* entrada1, char* entrada2, char* saida){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para loops
		j = variavel para loops
		qtdmaxreg1 = inteiro para guardar a quantidade máxima de registros do arquivo de entrada 1
		qtdmaxreg2 = inteiro para guardar a quantidade máxima de registros do arquivo de entrada 2
		qtdreg3 = inteiro para guardar a quantidade de registros não removidos do arquivo de saida
		max1 = inteiro para guardar a quantidade total de registros não removidos do arquivo de entrada 1
		max2 = inteiro para guardar a quantidade total de registros não removidos do arquivo de entrada 2
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

	//matriz de inteiros para guardar o nroInscricao e o RRN do arquivo de entrada 1: indice[nroInscricao][RRNcorrespondente]
	int indice1[qtdmaxreg1][3];
	//matriz de inteiros para guardar o nroInscricao e o RRN do arquivo de entrada 2: indice[nroInscricao][RRNcorrespondente]
	int indice2[qtdmaxreg2][3];
	//matriz de inteiros para guardar o nroInscricao e o RRN do arquivo de entrada 2: indice[nroInscricao][RRNcorrespondente]
	int indice3[qtdmaxreg1+qtdmaxreg2][3];


	//limpa as matrizes indices
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

	for(i = 0; i < max2; i++){
		//printf("indice2[%d][0] = %d\n",i,indice2[i][0]);
	}

	//dá um merge nos dois indices
	mergeindice(indice1,indice2,indice3,max1,max2);

	//conta quantos registros não removidos existem e guarda em qtdreg
	for(i = 0; i < max1+max2; i++){
		if(indice3[i][0] == -1 || indice3[i][0] == 0){
			qtdreg3 = i;
			break;
		}
		qtdreg3 = max1+max2;
	}

	//copia todos os registros não removidos do arquivo de entrada para o arquivo de saida 
	for(i = 0; i < qtdreg3; i++){
		//se a origem for o arquivo 1
		if(indice3[i][2] == 1){
			reg3[i] = reg1[indice3[i][1]];		
		}
		//se a origem for o arquivo 2
		else if(indice3[i][2] == 2){
			reg3[i] = reg2[indice3[i][1]];		
		}
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
	writeallregbin(indice3,qtdreg3,reg3,arqsaida);

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