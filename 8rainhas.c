#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct timeval inicio, final;
void srand(unsigned int seed);

void apaga_tabuleiro(int (*tabuleiro)[8]){
	int i, j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			tabuleiro[i][j] = 0;
		}
	}
}

int verifica_diagonal_principal(int (*tabuleiro)[8]){
	//função responsável por verificar a diagonal principal
	int i, j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if((i==j)&&(tabuleiro[i][j]==1)){
				return 0;
			}
		}
	}
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if((i+j==7)&&(tabuleiro[i][j]==1)){
				return 0;
			}
		}
	}
	return 1;
}

int verifica_quantidade_rainhas(int (*tabuleiro)[8]){
	int i, j;
	int cont=0;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if((tabuleiro[i][j]==1)){
				cont++;
			}
		}
	}
	if(cont==8){
		return cont; //posso acabar o programa
	}
	return cont;
}

int verifica_linhas(int (*tabuleiro)[8], int linha){
	//verificando a linha
	int j;
	for(j=0;j<8;j++){
		if(tabuleiro[linha][j] == 1){ //quer dizer que tem rainha ali
			return 1;
		}
	}
	return 0;
}

int verifica_colunas(int (*tabuleiro)[8], int coluna){
	//verificando coluna
	int i;
	for(i=0;i<8;i++){
		if(tabuleiro[i][coluna] == 1){
			return 1;
		}
	}
	return 0;
}

int verifica_diagonal_esquerda(int (*tabuleiro)[8], int linha, int coluna){
	int i, j;
	while((linha>0)||(coluna>0)){ //aqui andarei pra diagonal esquerda
		linha--;
		coluna--;
	}
	i = linha;
	j = coluna;
	while((i<7)&&(j<7)){
		if(tabuleiro[i][j] == 1){
			return 0;
		}
		i=i+1;
		j=j+1;
	}
	return 1;

}
int verifica_diagonal_direita(int (*tabuleiro)[8], int linha, int coluna){
	int i, j;
	while((linha>0)||(coluna<7)){ //aqui andarei pra diagonal esquerda
		linha--;
		coluna++;
	}
	i = linha;
	j = coluna;
	while((i<7)&&(j>0)){
		if(tabuleiro[i][j] == 1){
			return 0;
		}
		i=i+1;
		j=j-1;
	}
	return 1;

}
void imprime(int (*tabuleiro)[8]){
	int i, j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			printf("%d", tabuleiro[i][j]);
		}
		printf("\n");
	}
}
void verifica(int (*tabuleiro)[8]){
	int linha;// coluna;
	int aux, coluna, aux_anterior=0, cont=0;
	int i, j;
	time_t t;
	srand(time(&t)); 
	while(1){
		linha = rand() % 8;//vai gerar um número aleatório de 0 ~ 7
		coluna = rand() % 8;
		aux = verifica_linhas(tabuleiro, linha);
		if(aux==0){ //quer dizer que eu não tenho rainhas naquela linha
			aux = verifica_colunas(tabuleiro, coluna);
			if(aux==0){
				if(((linha==0)&&(coluna==0))||((linha==7)&&(coluna==7))){
					aux = verifica_diagonal_principal(tabuleiro);
					if(aux==1){ //quer dizer que está livre a diagonal principal
						tabuleiro[linha][coluna] = 1; //aloquei uma nova rainha
					}
				}
				else{
					aux =  verifica_diagonal_esquerda(tabuleiro, linha, coluna);
					if(aux == 1){
						aux = verifica_diagonal_direita(tabuleiro, linha, coluna);
						if(aux == 1){
							tabuleiro[linha][coluna] = 1; //aloquei uma nova rainha
						}
					}
				}
			}
		}
		aux = verifica_quantidade_rainhas(tabuleiro);
		if(aux==8){ //acabou, tenho 8 rainhas alocadas
			imprime(tabuleiro);
			break;
		}
		else if(aux_anterior==aux){
			cont++;
			if(cont==100){
				apaga_tabuleiro(tabuleiro);
			}
		}
		else{
			cont=0;
		}
		aux_anterior = aux;
	}
	
}

int main(){
	int tmili;//função de tempo
	gettimeofday(&inicio, NULL);//função de tempo
	int tabuleiro[8][8];
	//apaga_tabuleiro(tabuleiro);
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			tabuleiro[i][j] = 0;
		}
	}
	verifica(tabuleiro);
	gettimeofday(&final, NULL);//função de tempo
	tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);//função de tempo
	printf("\ntempo decorrido: %d ms\n", tmili); //função de tempo
	return 0;
	
}
