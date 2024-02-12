//Author Rafael Del Lama
 
//-----------------------------------------	TSimulador.hpp -----------------------------------------//

#pragma once
#include <cmath>
#include <cstdlib>

#define PI 3.14159265

class Simulador 
{
	private:
		int sensor (int dist, int ang, int gen);
		int tamX;								// tamanho do tabladoo eixo x
		int tamY;								// tamanho do tabladoo eixo y
		int posX;								// posi��o do centro do rob� no eixo x
		int posY;								// posi��o do centro do rob� no eixo y
		int ang;								// angulo da frente do rob� em rela��o ao eixo x
		int raio;								// raio do rob�
		bool dynamicEnvironment;
		int random_int(int L_range, int H_range);
		
	public:
		Simulador(int tamX, int tamY, bool dynamicEnvironment, int ambiente);
		Simulador(int tamX, int tamY, int raio, int posX, int posY, int ang, bool dynamicEnvironment);
		~Simulador();
		bool execute(int acao, int dist, int gen);
		double* readSensor(int dist, int gen);
		bool isBase();
		int getPosX();
		int getPosY();
		
};// class simulador
//-----------------------------------------	TSimulador.cpp -----------------------------------------//

//-----------------	simulador -----------------//
Simulador::Simulador(int tamX, int tamY, bool dynamicEnvironment, int ambiente){
	this->tamX = tamX;
	this->tamY = tamY;
	this->raio = 10;
	this->ang = 45*random_int(0,7);
	this->dynamicEnvironment = dynamicEnvironment;
	
	//Sortear uma posi��o inicial sem estar no obst�culo...
	int count = 0;
	do{
		if(count < 5) {
			posX = random_int(raio + 5,tamX- (raio + 5));
			posY = random_int(raio + 5,tamY-(raio + 5));
			count++;
		}
		else {
			posX = raio + 5;
			posY = raio + 5;
		}
	} while(sensor (0, ang, ambiente) != 0);
}//construtor

//-----------------	simulador -----------------//
Simulador::Simulador(int tamX, int tamY, int raio, int posX, int posY, int ang, bool dynamicEnvironment){
	this->tamX = tamX;
	this->tamY = tamY;
	this->raio = raio;
	this->posX = posX;
	this->posY = posY;
	this->ang = ang;
	this->dynamicEnvironment = dynamicEnvironment;
}//construtor


//-----------------	~simulador -----------------//
Simulador::~Simulador(){
}//destrutor

//-----------------	execute -----------------//
/*
* retuen true: mov executado com sucesso, false caso contr�rio
*/
bool Simulador::execute(int acao, int dist, int gen){
		/*	
			*A��o
		1 -- vira 45�
		2 -- vira -45�	
		3 -- vira 90�	
		4 -- anda p/ frente 10 cm 
		*/			
		switch (acao) 
		{
			case 0 : 
				/** Bloco Rotacionar 45� **/
				ang = ((int)ang + 45) % 360;
				break;
		
			case 1 :
				/** Bloco Rotacionar -45� **/
				ang = ((int)ang + 315) % 360;
				break;

			case 2 :
				/** Bloco Rotacionar 90� **/
				ang = ((int)ang + 90) % 360;
				break;

			case 3 :
				if(sensor(dist, ang, gen) == 0){
					/** Mover para frente 10cm	 M = 1	**/
					posX = posX + dist * cos(ang * PI / 180.0);
					posY = posY + dist * sin(ang * PI / 180.0);
				}
				else
					return false;
				break;
		}//switch
		
		return true;			
}// execute

//-----------------	readSensor -----------------//
double* Simulador::readSensor(int dist, int gen){
	double *sensores = new double[4];
	sensores[0] = sensor(dist, ang - 45, gen); 		// direita
	sensores[1] = sensor(dist, ang, gen);			// frontal
	sensores[2] = sensor(dist, ang + 45, gen); 		// esquerda
	if(isBase())
		sensores[3] = 1;						// cima
	else
		sensores[3] = 0;						// cima
	
	return sensores;
}//readSensor

//-----------------	sensor -----------------//
int Simulador::sensor (int dist, int ang, int ambiente){
	double anguloRad = ang * PI / 180.0;
	int distancia = dist + raio;
	int x = posX + distancia*cos(anguloRad);
	int y = posY + distancia*sin(anguloRad);
		 
	if( x >= tamX || x <= 0 || y >= tamY || y <= 0 )
		return 1;	
	
	if(dynamicEnvironment == true && ambiente > 0) {
		switch (ambiente){
			case 1 :
				if(0 <= x && x <= 55 && 52 <= y && y <= 86)
					return 1;
				if(0 <= x && x <= 55 && 126 <= y && y <= 160)
					return 1;
				break;
				
			case 2 :
				if(166 <= y && y <= 200)
					return 1;
				break;
				
			case 3 :
				if(65 <= x && x <= 120 && 122 <= y && y <= 156)
					return 1;
				break;
				
			case 4 :
				if(86 <= x && x <= 120 && 45 <= y && y <= 155)
					return 1;
				break;
				
			case 5 :
				if(86 <= x && x <= 120 && 0 <= y && y <= 55)
					return 1;
				if(0 <= x && x <= 55 && 166 <= y && y <= 200)
					return 1;
				break;
				
			case 6 :
				if(65 <= x && x <= 120 && 52 <= y && y <= 86)
					return 1;
				if(65 <= x && x <= 120 && 126 <= y && y <= 160)
					return 1;		
				break;
				
			case 7 :
				if(43 <= x && x <= 77 && 45 <= y && y <= 155)
					return 1;
				break;
				
			case 8 :
				if(65 <= x && x <= 120 && 44 <= y && y <= 78)
					return 1;
				if(0 <= x && x <= 55 && 122 <= y && y <= 156)
					return 1;
				break;
				
			case 9 :
				if(43 <= x && x <= 77 && 0 <= y && y <= 55)
					return 1;
				if(43 <= x && x <= 77 && 145 <= y && y <= 200)
					return 1;		
				break;				

			case 10 :
				if(0 <= x && x <= 50 && 70 <= y && y <= 140)
					return 1;		
				break;
					
			case 11 :
				if(70 <= x && x <= 120 && 150 <= y && y <= 200)
					return 1;
				break;
					
			case 12 :
				if(70 <= x && x <= 120 && 0 <= y && y <= 50)
					return 1;
				break;
				
			case 13 :
				if(90 <= x)
					return 1;
				break;
				
			case 14 :
				if(70 <= x && x <= 120 && 70 <= y && y <= 140)
					return 1;
				break;		
		}
	}	
	return 0;
}//sensor

//-----------------	isBase -----------------//
bool Simulador::isBase(){
	 if(posX < 30 && posY < 30)
		return true;
	 return false;
}//isBase

//-----------------	getPosX -----------------//
int Simulador::getPosX(){
	return posX;
}//getPosX

//-----------------	getPosY -----------------//
int Simulador::getPosY(){
	return posY;
}//getPosY

/******************************************************************************\
*								 Random Integer between L_range and H_range			 *
\******************************************************************************/
int Simulador::random_int(int L_range, int H_range)
{
	return(  (int) ( (rand()/(RAND_MAX+1.0))*(H_range-L_range+1)+L_range ) );  // random integer beteween [L_range and H_range]
}

