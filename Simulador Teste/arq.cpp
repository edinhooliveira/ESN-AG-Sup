#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "ESN.hpp"

using namespace std;

/******************************************************************************\
*								Ler individuo	 							 *
\******************************************************************************/
void ler_indiv(double *indiv, int lcrom, int n)
{
	FILE *Pop_arq;
		char nome[64];
	sprintf(nome,"MelhoresIndividuos_%d.datw", n); 

	if ((Pop_arq = fopen(nome,"r"))==NULL) {
		cout<<"O arquivo de gravacao dos dados da populacao nao pode ser aberto "<<endl;
		exit(1);
	}
	int gene;
	
	for (gene = 0; gene < lcrom; gene++) {
     	fscanf(Pop_arq,"%lf", &indiv[gene]); 					// inteiro entre 0 e 1
	}
	//cout << "Indiv lido!" << endl;
	fclose(Pop_arq);	
}

/******************************************************************************\
*								Ler ESN		 							 *
\******************************************************************************/
void ler_esn(ESNbp *esn, int inputSize, int repSize, int n)
{
	FILE *ESN_arq;
	char nome[64];
	sprintf(nome,"esn_%d.dat", n); 
	
	if ((ESN_arq = fopen(nome,"r"))==NULL) {
		cout<<"O arquivo de gravacao dos dados da ESN nao pode ser aberto "<<endl;
		exit(1);
	}
	
	double **W, **Win;
	Win = new double*[repSize];
	W = new double*[repSize];
	
	for(int i = 0; i < repSize; i++){
		Win[i] = new double[inputSize + 1]; // +1 = bias
		W[i] = new double[repSize];
	}
	
	//Ler pesos camada de entrada - Win
	for(int i = 0; i < repSize; i++)
		for(int j = 0; j < inputSize + 1; j++)
			fscanf(ESN_arq,"%lf", &Win[i][j]);
	esn->setWin(Win);
			
	//Ler pesos do reservatório - W
	for(int i = 0; i < repSize; i++)
		for(int j = 0; j < repSize; j++)
			fscanf(ESN_arq,"%lf", &W[i][j]);
	esn->setW(W);
	//cout << "ESN lida!" << endl;
	fclose(ESN_arq);
}

/******************************************************************************\
*								Ler ESN - Supervisionada 							 *
\******************************************************************************/


/******************************************************************************\
*								Salvar traj	 							 *
\******************************************************************************/
void salv_traj(int **pos, int n, int ambiente, int nroEx){
//	mkdir(nameDir);

	FILE *traj_arq;
	char nome[64];

	sprintf(nome,"traj_%d.%d.dat", ambiente, nroEx); 
	traj_arq = fopen(nome, "wt");

	if(traj_arq != NULL)
	{
		for(int i = 0; i < n; i++){
			fprintf(traj_arq, "%d ",pos[0][i]);
			fprintf(traj_arq, "%d\n",pos[1][i]); 
		}
		
		int closeResult = fclose(traj_arq);
		if(closeResult != 0)
			cout << "\nErro ao fechar o arquivo traj.dat!" << endl;
	}
	else
		cout << "\nErro ao abrir o arquivo traj.dat!" << endl;
}
