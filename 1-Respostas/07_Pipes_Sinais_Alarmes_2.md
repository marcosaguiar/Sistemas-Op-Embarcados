1. Crie um programa em C que cria um processo-filho e um pipe de comunicação. Faça com que o processo-pai envie os valores 1, 2, 3, 4, 5, 6, 7, 8, 9 e 10 para o processo-filho, com intervalos de 1 segundo entre cada envio. Depois de o processo-pai enviar o número 10, ele aguarda 1 segundo e termina a execução. O processo-filho escreve na tela cada valor recebido, e quando ele receber o valor 10, ele termina a execução.

```c
#include <stdio.h>	//biblioteca Entrada/Saída
#include <stdlib.h> //biblioteca de propósito geral padrão
#include <string.h> //funções para manipular strings
#include <signal.h> //contém protótipos para funções_definições para receber e manipular sinais.
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int pid; //PID do processo filho
	int fd[2];//descritores do pipe (escrita ou leitura).
	int i;

	pipe(fd); //cria o pipe
	pid = fork(); //cria o processo

	//processo filho
	if(pid==0)
	{
		sleep(11);
		for(int n=1; n<=10, n++)
		{
			read(fd[0], &i,sizeof(int)); //le a informação no pipe
			printf("Valor lido: %s\n", i); //imprime o valor recebido
		}
	}
	//processo pai
	else
	{
		for(int n=1; n<=10, n++)
		{
			write(fd[1], &n,sizeof(n)); //escreve a informação no pipe
			sleep(1) //aguarda 1s
		}
	}
	return 0;
}
```

2. Crie um programa em C que cria um processo-filho e um pipe de comunicação. Utilize o pipe para executar a seguinte conversa entre processos:

```
FILHO: Pai, qual é a verdadeira essência da sabedoria?
PAI: Não façais nada violento, praticai somente aquilo que é justo e equilibrado.
FILHO: Mas até uma criança de três anos sabe disso!
PAI: Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...
```

Neste exercício, quem recebe a mensagem via pipe é quem as escreve no terminal.

```c
#include <stdio.h>	//biblioteca Entrada/Saída
#include <stdlib.h> //biblioteca de propósito geral padrão
#include <string.h> //funções para manipular strings
#include <signal.h> //contém protótipos para funções_definições para receber e manipular sinais.
#include <unistd.h>
#include <sys/wait.h>

#define N 100

int main()
{
	int pid; //PID do processo filho
	int fd[2]; //descritores do pipe (escrita ou leitura).

	pipe(fd); //cria o pipe
	pid = fork(); //cria o processo

	//processo filho
	if(pid==0)
	{
		char buffer_filho[N], msg_filho[N];
		sprintf(msg_filho, "Pai, qual é a verdadeira essência da sabedoria?");
		write(fd[1], msg_filho, N);
		sleep(1);
		read(fd[0], buffer_filho, N);
		printf("PAI: %s\n", buffer_filho);
		sprintf(msg_filho, "Mas até uma criança de três anos sabe disso!");
		write(fd[1], msg_filho, N);
		sleep(1);
		read(fd[0], buffer_filho, N);
		printf("PAI: %s\n", buffer_filho);
	}
	//processo pai
	else
	{
		char buffer_pai[N], msg_pai[N];
		read(fd[0], buffer_pai, N);
		printf("FILHO: %s\n", buffer_pai);
		sprintf(msg_pai, "Não façais nada violento, praticai somente aquilo que é justo e equilibrado.");
		write(fd[1], msg_pai, N);
		sleep(1);
		read(fd[0], buffer_pai, N);
		printf("FILHO: %s\n", buffer_pai);
		sprintf(msg_pai, "Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...");
		write(fd[1], msg_pai, N);
		wait(NULL);
	}
	return 0;
}

```

3. Crie um programa em C que cria dois processos-filhos e um pipe de comunicação. Utilize o pipe para executar a seguinte conversa entre processos:

```
FILHO1: Quando o vento passa, é a bandeira que se move.
FILHO2: Não, é o vento que se move.
PAI: Os dois se enganam. É a mente dos senhores que se move.
```

Neste exercício, quem recebe a mensagem via pipe é quem as escreve no terminal.

```c
#include <stdio.h>	//biblioteca Entrada/Saída
#include <stdlib.h> //biblioteca de propósito geral padrão
#include <string.h> //funções para manipular strings
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
	int pid_filho1; //PID do processo filho1
	int pid_filho2; //PID do processo filho2
	int fd[2]; //descritores do pipe (escrita ou leitura).

    char m1[100]= "Quando o vento passa, é a bandeira que se move.";
    char m2[100]= "Não, é o vento que se move.";
	char m3[100]= "Os dois se enganam. É a mente dos senhores que se move.";

	pipe(fd); //cria o pipe
	pid_filho1 = fork(); //cria o processo

		//processo filho1
		if (pid_filho1 == 0)
		{
			sleep(1);
        	read(fd[0],m1,100);
        	printf("%s",m1);
        	write(fd[1],m2,100);
        	sleep(1);
		}
		else //não faz nada
		{

    pid_filho2 = fork();
        //processo filho2
        if(pid_filho2 == 0)
        {
            write(fd[1],m1,100);
            sleep(1);
            read(fd[0],m2,100);
            printf("%s",m2);
            sleep(1);
            write(fd[1],m3,100);
            sleep(1);
        }
        //processo pai
		else
		{
			sleep(2);
            read(fd[0],m3,100);
            printf("%s",m3);
            sleep(1);
		}
	}
	return 0;
}

```

4. Crie um programa em C que cria um processo-filho e um pipe de comunicação. O processo-filho deverá pedir o nome do usuário, envia-lo para o pai via pipe, e o pai deverá escrever o nome do usuário no terminal.

```c
#include <stdio.h>	//biblioteca Entrada/Saída
#include <stdlib.h> //biblioteca de propósito geral padrão
#include <string.h> //funções para manipular strings
#include <signal.h> //contém protótipos para funções_definições para receber e manipular sinais.
#include <unistd.h>
#include <sys/wait.h>

//função principal
int main()
{
	int pid; //PID do processo filho
	int fd[2];//especificar o pipe que estão usando (escrita ou leitura).
	char nome[100];

	pipe(fd); //cria o pipe
	pid = fork(); //cria o processo

	//processo filho
	if(pid==0)
	{
		printf("Informe seu nome: %s/n", nome);
		write(fd[1], nome, sizeof(nome));		
	}
	//processo pai
	else
	{
		read(fd[0], nome, 100);
		printf("O nome informado foi: %s/n", nome);
	}
	return 0;
}
```

5. Utilize o sinal de alarme para chamar a cada segundo o comando `ps` ordenando todos os processos de acordo com o uso da CPU. Ou seja, seu código atualizará a lista de processos a cada segundo. Além disso, o código deverá tratar o sinal do CTRL-C, escrevendo "Processo terminado!" na tela antes de terminar a execução do processo.
