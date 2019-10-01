1. Quantos pipes serão criados após as linhas de código a seguir? Por quê?

(a)
```C
int pid;
int fd[2];
pipe(fd);
pid = fork();
```
```
Somente 1, por que é originado do fork().
```

(b)
```C
int pid;
int fd[2];
pid = fork();
pipe(fd);
```
```
Dois, sendo um no processo filho e outro no processo pai.
```

2. Apresente mais cinco sinais importantes do ambiente Unix, além do `SIGSEGV`, `SIGUSR1`, `SIGUSR2`, `SIGALRM` e `SIGINT`. Quais são suas características e utilidades?

```
SIGQUIT (é um sinal enviado aos processos da linha de comando quando a tecla de abandono do teclado é acionada)
SIGINT ( é um sinal emitido aos processos do terminal quando teclas de interrupção são acionadas)
SIGTRAP ( é um sianl enviado depois de uma instrução nos casos em que gerar traces dos processos)
SIGHUP: ( é um sinal emitido aos processo associados a uma linha de comando, quando este se desconecta)
SIGILL: ( é um sinal emitido quando é detectada uma instrução ilegal)
```

3. Considere o código a seguir:

```C
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void tratamento_alarme(int sig)
{
	system("date");
	alarm(1);
}

int main()
{
	signal(SIGALRM, tratamento_alarme);
	alarm(1);
	printf("Aperte CTRL+C para acabar:\n");
	while(1);
	return 0;
}
```

Sabendo que a função `alarm()` tem como entrada a quantidade de segundos para terminar a contagem, quão precisos são os alarmes criados neste código? De onde vem a imprecisão? Este é um método confiável para desenvolver aplicações em tempo real?

```
A precisão dos alarmes criados nesse código é questionável quando se trata de sua utilização para aplicações de tempo real,
pois dependerá da operação à ser realizada. A imprecisão deles existe devido ao sistema operacional realizar vários
processos de forma alternada, tornando difícil determinar, exatamente, o tempo de execução dos processos.
```
