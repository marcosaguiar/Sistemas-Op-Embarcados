1. Crie um código em C para gerar três processos-filho usando o `fork()`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main( int argc, char const *argv[] ) {
  pid_t child_pid=1 ;

  for ( size_t i = 0 ; i < 3 ; i++) {
    if (child_pid != 0 ){
      printf("PID criador : %d\n",(int) getpid());
      printf(" Processo filho criado\n");
      child_pid = fork();
    } else {
      printf(" processo filho fazendo nada !\n");
    }
  }
  return 0;
}
```

2. Crie um código em C que recebe o nome de diversos comandos pelos argumentos de entrada (`argc` e `*argv[]`), e executa cada um sequencialmente usando `system()`. Por exemplo, considerando que o código criado recebeu o nome de 'serial_system', e que ele foi executado na pasta '/Sistemas_Embarcados/Code/06_Processos', que contem diversos arquivos:

```bash
$ ./serial_system pwd echo ls echo cal
$ ~/Sistemas_Embarcados/Code/06_Processos
$
$ Ex1.c    Ex2b.c   Ex4.c   Ex6.c
$ Ex2a.c   Ex3.c    Ex5.c   serial_system
$
$     Março 2017
$ Do Se Te Qu Qu Se Sá
$           1  2  3  4
$  5  6  7  8  9 10 11
$ 12 13 14 15 16 17 18
$ 19 20 21 22 23 24 25
$ 26 27 28 29 30 31
```
```c
#include <stdio.h>
#include <sys/signal.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int main( int argc, const char * argv[]) {
    int n ;
    char entrada[20];
	for( n = 1; n < argc; n ++) {
		strcpy (entrada, argv[n]) ;
		system( entrada );
	}
}
```

3. Crie um código em C que recebe o nome de diversos comandos pelos argumentos de entrada (`argc` e `*argv[]`), e executa cada um usando `fork()` e `exec()`.

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main( int argc, const char *argv[] ) {
	int i ;
	char * lista[2] = { NULL, NULL};
	for( i=1 ; i<argc; i++ ) {
        lista[0] = ( char* )argv[i] ;
        execvp( lista[0], lista);
    }
	return 0;
}
```

4. Crie um código em C que gera três processos-filho usando o `fork()`, e que cada processo-filho chama a seguinte função uma vez:

```C
int v_global = 0; // Variavel global para este exemplo
void Incrementa_Variavel_Global(pid_t id_atual)
{
	v_global++;
	printf("ID do processo que executou esta funcao = %d\n", id_atual);
	printf("v_global = %d\n", v_global);
}
```
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/signal.h>

int v_global = 0; // variavel global para esse exemplo
void Incrementa_Variavel_Global(pid_t id_atual ) {
	v_global++;
	printf("ID do processo que executou essa funcao = %d\n", id_atual) ;
	printf("v_global = %d\n", v_global );
}

int main(void) {
    int pid_filho_1, pid_filho_2, pid_filho_3,  pid_pai;
    printf("Pid pai antes do primeiro Fork() -  %d\n", getpid()) ;
    pid_filho_1 = fork() ;

    if (pid_filho_1 == 0 ) {
		Incrementa_Variavel_Global( getpid() );
	} else {
		sleep(1);
		pid_filho_2 = fork();

		if (pid_filho_2 == 0) {
				Incrementa_Variavel_Global(getpid() );
		} else {
            sleep(1);
            pid_filho_3 = fork() ;

		    if (pid_filho_3 == 0) {
			    Incrementa_Variavel_Global( getpid());
		    } else {
			    sleep(1);
			    printf(" Pid pai  depois do terceiro Fork(), o terceiro filho já criado -  %d\n", getpid());
		    }
	    }
	}
    return 0;
}
```
(Repare que a função `Incrementa_Variavel_Global()` recebe como entrada o ID do processo que a chamou.) Responda: a variável global `v_global` foi compartilhada por todos os processos-filho, ou cada processo enxergou um valor diferente para esta variável?

```
 Cada processo enxergou uma variável diferente para esta variável.
```

5. Repita a questão anterior, mas desta vez faça com que o processo-pai também chame a função `Incrementa_Variavel_Global()`. Responda: a variável global `v_global` foi compartilhada por todos os processos-filho e o processo-pai, ou cada processo enxergou um valor diferente para esta variável?

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/signal.h>
#include <unistd.h>

int v_global = 0; // Variavel global para este exemplo

void Incrementa_Variavel_Global(pid_t id_atual ) {
	v_global++;
	printf(" ID do processo que executou esta funcao = %d\n", id_atual);
	printf("v_global = %d\n ", v_global);
}

int main(void) {
    int pid_filho_1, pid_filho_2, pid_filho_3,  pid_pai;
    printf("Pid pai antes do primeiro Fork() -  %d\n", getpid()) ;
    pid_filho_1 = fork();

    if (pid_filho_1 == 0) {
		Incrementa_Variavel_Global( getpid() );
	} else {
		Incrementa_Variavel_Global(getpid() );

		sleep( 1);
		pid_filho_2 = fork() ;

		if ( pid_filho_2 == 0) {
			Incrementa_Variavel_Global(getpid() );
		} else {
			sleep(1);
			Incrementa_Variavel_Global( getpid() );
			pid_filho_3 = fork() ;
			if ( pid_filho_3 == 0){
				Incrementa_Variavel_Global(getpid());
			} else {
				sleep(1) ;
				Incrementa_Variavel_Global(getpid() );
				printf(" Pid pai apos o terceiro Fork() , terceiro filho já criado-  %d\n", getpid() ) ;
			}
		}
	}
   return 0 ;
}
```
