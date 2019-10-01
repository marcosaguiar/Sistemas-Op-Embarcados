1. Quais são as vantagens e desvantagens em utilizar:

(a) fork?
```
- Vantagens: Cada filho pode executar sua própria tarefa; Cada filho tem seu espaço de memória protegido.
- Desvantagens: Ocupa um espaço maior de memória;	A comunicação tem que ser feita atrevés de pipes ou sinais.

```

(b) threads?
```
- Vantagens: Uma aplicação pode rodar várias threads, a memória é compartilhada (ocupa menos espaço) o que permite a comunicação é direta.
- Desvantagens: Risco de corrupção de dados;	Gera dependência entre programas.
```

2. Quantas threads serão criadas após as linhas de código a seguir? Quantas coexistirão? Por quê?

(a)

```C
void* funcao_thread_1(void *arg);
void* funcao_thread_2(void *arg);

int main (int argc, char** argv)
{
	pthread_t t1, t2;
	pthread_create(&t1, NULL, funcao_thread_1, NULL);
	pthread_create(&t2, NULL, funcao_thread_2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
```
```
Depois dos creates, terão 3 threads, a principal e outras duas.
```

(b)
```C
void* funcao_thread_1(void *arg);
void* funcao_thread_2(void *arg);

int main (int argc, char** argv)
{
	pthread_t t1, t2;
	pthread_create(&t1, NULL, funcao_thread_1, NULL);
	pthread_join(t1, NULL);
	pthread_create(&t2, NULL, funcao_thread_2, NULL);
	pthread_join(t2, NULL);
	return 0;
}
```
```
 Existirão duas,  em seguida, uma será finalizada, então terão outras duas e depois terá apenas a main.
```

3. Apresente as características e utilidades das seguintes funções:

(a) `pthread_setcancelstate()`
```
O estado de cancelabilidade de uma thread é determinado por essa função. Se desabilitado, o pedido de cancelamento fica na fila
até a thread ser habilitado o cancelamento. Se habilitado, o tipo do estado de cancelabilidade é determinado quando o cancelamento ocorre.

```

(b) `pthread_setcanceltype()`

```
O tipo de cancelamento da thread é determinado por essa função, podendo ser assíncrono ou deferido. Na assíncrona a thread pode
ser cancelada a qualquer momento, normamelmente de imediato. No deferido, o cancelamento será atrasado até a próxima thread chamar a
função, no caso o ponto de cancelamento.
```
(DICA: elas são relacionadas à função pthread_cancel().)
