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
#define HOME_POS "#0P1500#1P1500#2P1500#3P1500#4P1500"

int main()
{
	ufrn_header();

	int serial_fd;
	char *comando;
	unsigned int movimento;
	unsigned int canal;
	unsigned int posicao=1500;

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
		//printf("\nPRIMEIRO COMANDO - POSICAL INICIAL\n");

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

		printf("Pressione enter para continuar...");
		getchar();

		do{
			memset(comando, 0, BUFSIZE);
			printf("\nInforme o canal de 0 a 4\n");
			scanf("%d", &canal);

			printf("O canal utilizado %d", canal);

			printf("\nInforme o movimento (5 6 7 8)\n");

			//movimento = getchar();
			scanf("%d", &movimento);

			switch (movimento) {
				case 5:
					posicao = posicao + 200;
					break;
				case 6:
					posicao = posicao + 200;
					break;
				case 7:
					posicao = posicao - 200;
					break;
				case 8:
					posicao = posicao - 300;
					break;
				default:
					printf("Informe um movimento válido(5 6 7 8).")
			}

			sprintf(comando,"#%dP%d",canal,trava(canal,posicao));
			puts(comando);

			enviar_comando(comando,serial_fd);

			printf("Pressione enter para continuar...");
			getchar();

			if (canal == 9) break;

		}while (canal != 9);

  	fechar_porta(serial_fd);
		printf("\nAcesso a porta serial /dev/ttyS0 finalizado\n");
	}
	printf("\nPROGRAMA DEMONSTRACAO FINALIZADO\n\n");

	return 0;
}
