/*************************************************************/
/*       UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE         */
/*   DEPARTAMENTO DE ENGENHARIA DE COMPUTAÇÃO E AUTOMAÇÃO    */
/*							     */
/*   DRIVER DO BRAÇO ROBÓTICO LYNX AL5D PARA A PORTA SERIAL  */
/*							     */
/*   DESENVOLVEDORES:					     */
/*	- ENG. M.SC. DESNES AUGUSTO NUNES DO ROSÁRIO	     */
/*	- ENG. DANILO CHAVES DE SOUSA ICHIHARA		     */
/*************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "ufrn_al5d.h"

//Posicao inicial para todos os servos
#define HOME_POS "#0P1640#1P1468#2P1672#3P2500#4P1500T2000"
#define PI 3.14159265
#define px 0
#define py 0

void PEGA(){
	int serial_fd;
	char *comando;

	serial_fd = abrir_porta();
	comando = (char*) malloc(sizeof(char)*BUFSIZE);
	
	memset(comando, 0, BUFSIZE);
	sprintf(comando,"#%dP%dT1000",4,trava(4,1930));
	if(enviar_comando(comando,serial_fd)!=-1)
	{
	        printf("\nEnviando de comando com teste\n");
	}
	else
	{
	        printf("Problema no envio do comando\nAbortando o programa...");
	        return -1;
	}	
}

void SOLTA(){
	int serial_fd;
	char *comando;

	serial_fd = abrir_porta();
	comando = (char*) malloc(sizeof(char)*BUFSIZE);
	
	memset(comando, 0, BUFSIZE);
	sprintf(comando,"#%dP%dT1000",4,trava(4,1000));
	if(enviar_comando(comando,serial_fd)!=-1)
	{
	        printf("\nEnviando de comando com teste\n");
	}
	else
	{
	        printf("Problema no envio do comando\nAbortando o programa...");
	        return -1;
	}
}

void MOVE(float X0, float Y0, float Z0, float FI){
	int serial_fd;
	char *comando;

	serial_fd = abrir_porta();
	comando = (char*) malloc(sizeof(char)*BUFSIZE);
	
	memset(comando, 0, BUFSIZE);
			
		unsigned int pos1=1640, pos2=1468, pos3=1672, pos4=1500, pos5=1500;
		float SenseBasAux = 1640;
                float SenseShlAux = 1468;
                float SenseElbAux = 1672;
                float SenseWriAux = 2500;
                float SenseGriAux = 1500;
                float Pul1 = 1500;
                float Pul2 = 1500;
                float Pul3 = 1500;
                float Pul4 = 1500;
                float Pul5 = 1500;
		
                int h=7,L3=15,L4=19,L5=7;
                float R, X4, Z4, C3, S3, T21, T22, T31, T32, T41, T42, T1, t1,t2,t3,t4,alfa,beta;

                
                printf("\nx  = %f",X0);     
		printf("\ny  = %f",Y0);
                printf("\nz  = %f",Z0);
                printf("\nfi = %f",FI);
                
                R = sqrt(pow(X0,2) + pow(Y0,2));
		X4 = R-L5*cos(FI*PI/180);
		Z4 = Z0 - h - L5*sin(FI*PI/180);

		C3 = (pow(X4,2) + pow(Z4,2) - pow(L4,2) - pow(L3,2))/(2*L4*L3);
		S3 = sqrt(1-pow(C3,2));

		alfa = atan2(L4*S3,L3+L4*C3);
		beta = atan2(Z4,X4);
		t3 = atan2(S3,C3)*180/PI;
		t2 = (beta-alfa)*180/PI;
		T41 = FI - t2 - t3;

		T32 = atan2(-S3,C3)*180/PI;
		T22 = (atan2(Z4,X4) + atan2(-L2*S3,L1+L2*C3))*180/PI;
		T42 = FI - T22 + T32;

		T1 = atan2(Y0,X0)*180/PI;
			
		if(T1 >= 0 && T21 >= 0 && T31 >= 0 && T41 >= -90 && T1 <= 180 && T21 <= 180 && T31 <= 180 && T41 <= 90){
			t1=T1;
			t2=T21;
			t3=T31;
			t4=T41;
		}
		else if(T1 >= 0 && T22 >= 0 && T32 >= 0 && T42 >= -90 && T1 <= 180 && T22 <= 180 && T32 <= 180 && T42 <= 90){
			t1=T1;
			t2=T22;
			t3=T32;
			t4=T42;
		}
		else{
			printf("\nSEM SOLUCAO!\n");	
		}
			
		Pul1 = (t1/0.09)+500;
               	Pul2 = (t2/0.09)+500;
               	Pul3 = (t3/0.09)+500;
               	Pul4 = (t4/0.09)+500;
		
		printf("\n\nBASE     -> LARGURA DO PULSO: %d \t | ANGULO: %f \n",(int)Pul1,t1);
                printf("OMBRO    -> LARGURA DO PULSO: %d \t | ANGULO: %f \n",(int)Pul2,t2);
                printf("COTOVELO -> LARGURA DO PULSO: %d \t | ANGULO: %f \n",(int)Pul3,t3);
                printf("PUNHO    -> LARGURA DO PULSO: %d \t | ANGULO: %f \n",(int)Pul4,t4);
                printf("GARRA    -> LARGURA DO PULSO: %d \t              \n",(int)Pul5);
                        
                pos1 = Pul1 + SenseBasAux - 1500;
                pos2 = Pul2 + SenseShlAux - 1500;
                pos3 = Pul3 + SenseElbAux - 1500;
                pos4 = Pul4 + SenseWriAux - 1500;
                pos5 = Pul5;
                                                
                sprintf(comando,"#%dP%d#%dP%d#%dP%d#%dP%dT2000",0,trava(0,pos1),1,pos2,2,pos3,3,trava(3,pos4),4,trava(4,pos5));
			
	        if(enviar_comando(comando,serial_fd)!=-1)
		{
		        printf("\nEnviando de comando com teste\n");
		}
		else
	        {
		        printf("Problema no envio do comando\nAbortando o programa...");
		        return -1;
	        }
			
	        memset(comando, 0, BUFSIZE);
}

int main()
{
	ufrn_header();

	int serial_fd;
	char *comando;

	// INICIO DO PROGRAMA DEMO //

	printf("PROGRAMA DEMONSTRACAO INICIADO\n\n");

	serial_fd = abrir_porta();

	if(serial_fd == -1)
	{
		printf("Erro abrindo a porta serial /dev/ttyS0\nAbortando o programa...");
		return -1;
	}
	else
	{
		printf("Porta serial /dev/ttyS0 aberta com sucesso\n");

		if(configurar_porta(serial_fd) == -1)
		{
		    printf("Erro inicializando a porta\n");
		    close(serial_fd);
		    return -1;
		}

		comando = (char*) malloc(sizeof(char)*BUFSIZE);

		//////////////////////
		// PRIMEIRO COMANDO //
		//////////////////////
		printf("\nPRIMEIRO COMANDO - POSICAL INICIAL\n");

		sprintf(comando,"%s",HOME_POS);

		//Escrevendo com teste de escrita
		if(enviar_comando(comando,serial_fd)!=-1)
		{
			printf("Enviando de comando com teste de envio: %s\n",HOME_POS);
		}
		else
		{
			printf("Problema no envio do comando\nAbortando o programa...");
			return -1;
		}

		//printf("Pressione enter para continuar...");
		//getchar();
		
		/////////////////////
		// SEGUNDO COMANDO //
		/////////////////////
		
		system("clear");
		
		printf("MENU:\n\n0-SAIR\n1-REPOUSO\n2-PEGA\n3-MOVE\n4-SOLTA\n\n");
		
		char e = getchar();
		float Xi,Yi,Zi;
		do{
			if(e == '1'){
				MOVE(2.38,16.95,2.9,0);	
			}
			if(e == '2'){
				PEGA();
			}
			if(e == '3'){
				printf("\n\nDigite o valor de x:");
                		scanf ("%f",&Xi);
               			printf("\nDigite o valor de y:");
                		scanf ("%f",&Yi);
                		printf("\nDigite o valor de z:");
                		scanf ("%f",&Zi);
                		//printf("\nDigite o valor do angulo que a garra forma com a base:");
                		//scanf ("%f",&FI);
                		MOVE(Xi,Yi,Zi,0);
			}
			if(e == '4'){
				SOLTA();
			}
			memset(comando, 0, BUFSIZE);
			
			system("clear");
		
			printf("MENU:\n\n0-SAIR\n1-REPOUSO\n2-PEGA\n3-MOVE\n4-SOLTA\n\n");
			e = getchar();
			
		}while(e != '0');
                             
		// FIM DO PROGRAMA DEMO //
	        fechar_porta(serial_fd);
		printf("\nAcesso a porta serial /dev/ttyS0 finalizado\n");

    	}

	printf("\nPROGRAMA FINALIZADO\n\n");

	return 0;
}
