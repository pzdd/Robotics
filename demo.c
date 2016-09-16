#include <stdio.h>
#include <stdlib.h>


#include "ufrn_al5d.h"

//Posicao inicial para todos os servos
#define HOME_POS "#0P1300#1P1500#2P1500#3P1500#4P1500"
#define TIME_MOVE 300

int main()
{
	ufrn_header();

	int serial_fd;
	char *comando;
	int movimento;
	unsigned int canal;
	unsigned int posicao=0;

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

			printf("Informe o angulo\n");
			scanf("%d", &movimento);

			if(movimento < 180){
				posicao = movimento/0.09 + 500;
			}	

			sprintf(comando,"#%dP%dS%d",canal,trava(canal,posicao),TIME_MOVE);
			puts(comando);

			enviar_comando(comando,serial_fd);

			if (canal == 9) break;

		}while (canal != 9);

  	fechar_porta(serial_fd);
		printf("\nAcesso a porta serial /dev/ttyS0 finalizado\n");
	}
	printf("\nPROGRAMA DEMONSTRACAO FINALIZADO\n\n");

	return 0;
}
