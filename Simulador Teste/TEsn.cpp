//Author Rafael Del Lama 

#include "TEsn.hpp"
#include <iostream>
#include <cmath>

using namespace std; 

//-----------------------------------------	TEsn.cpp -----------------------------------------//
/* Construtor
* inputSize é a quantidade de entradas da rede ESN
* repSize é a quantidade de neuronios na camada do repositório
* n_rec é o número de recorrencia
*/

ESN::ESN()
{}

ESN::ESN(int inputSize, int repSize, int outputSize, double spectral_radius_d, double con_density)
{
	this->inputSize = inputSize;
	this->repSize = repSize;
	this->outputSize = outputSize;
	this->spectral_radius_d = spectral_radius_d;
	this->con_density = con_density;

	Win = new double*[repSize];
	W = new double*[repSize];
	Wout = new double*[outputSize];
	outRep = new double[repSize];
	recorrence = new double[repSize];
	
	for(int i = 0; i < repSize; i++){
		Win[i] = new double[inputSize + 1]; // +1 = bias
		W[i] = new double[repSize];
	}
	
	for(int i = 0; i < outputSize; i++){
		Wout[i] = new double[repSize + 1]; // +1 = bias
	}
	
    weightInput();
}//ESN

//-----------------	~ESN -----------------//
ESN::~ESN()
{
	for(int i = 0; i < repSize; i++){
		delete Win[i];
		delete W[i];
	}
	for(int i = 0; i < outputSize; i++)
		delete Wout[i];
		
    delete Win;	
    delete W;
    delete Wout;
    delete outRep;
    delete recorrence;
}//~ESN

//-----------------	weightInput -----------------//
/* 
* Inicializa os pesos da camada de entrada e de recorrencia.
*/
void ESN::weightInput(){
}// weightInput

//-----------------	setResWeight -----------------//
/* 
* weight[] é o vetor de pesos do reservatório para a camada de saída
*/
void ESN::setResWeight (double *weight)
{	
	for(int i = 0; i < outputSize; i++)
		for(int j = 0; j < repSize + 1; j++)
			Wout[i][j] = weight[i*repSize + j];		
						
	for(int i = 0; i < repSize; i++)
		recorrence[i] = 0;
			
}//setResWeight

//-----------------	execute -----------------//
/* 
* in[] é o vetor de entrada
* return a saída da rede
*/
double* ESN::Execute (double *in)
{	
	double sum;
	for(int i = 0; i < repSize; i++){
		sum = Win[i][0];
		for(int j = 1; j < inputSize + 1; j++)
			sum += Win[i][j] * in[j-1];
		for(int j = 0; j < repSize; j++)
			sum += W[i][j] * recorrence[i];
		outRep[i] = FuncAtivacao(sum);
	}
			
	double *out = new double[outputSize];
	for(int i = 0; i < outputSize; i++){
		sum = Wout[i][0];
		for(int j = 1; j < repSize + 1; j++)
			sum += Wout[i][j] * outRep[j-1]; 
		out[i] = sum;
	}

	double *aux;
	aux = recorrence;
	recorrence = outRep;
	outRep = aux;

	return out;
}//Execute

//-----------------	FuncAtivacao -----------------//
/*
* retorna o valor da tangente hiperbolica de x
*/
double ESN::FuncAtivacao (double x)
{
	return ( (exp(x) - exp(-x)) / (exp(x) + exp(-x)));	
}//FuncAtivacao

//-----------------	getWin -----------------//
/*
* retorna a matriz Win, contendo os pesos da camada de entrada
*/
double** ESN::getWin ()
{
	return Win;
	
}//getWin

//-----------------	setWin -----------------//
/*
* define os pesos de Win, pesos da camada de entrada
*/
void ESN::setWin (double **weight)
{
	for(int i = 0; i < repSize; i++)
		for(int j = 0; j < inputSize + 1; j++)
			Win[i][j] = weight[i][j];
}//setWin

//-----------------	getW -----------------//
/*
* retorna a matriz W, contendo os pesos do repositório
*/
double** ESN::getW ()
{
	return W;
}//getW

//-----------------	setWin -----------------//
/*
* define os pesos de W, pesos do repositório
*/
void ESN::setW (double **weight)
{
	for(int i = 0; i < repSize; i++)
		for(int j = 0; j < repSize; j++)
			W[i][j] = weight[i][j];
}//setW

