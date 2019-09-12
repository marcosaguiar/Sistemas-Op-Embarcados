1. Como se utiliza o comando `ps` para:

(a) Mostrar todos os processos rodando na máquina?

$ ps -e

(b) Mostrar os processos de um usuário?

$ ps -u (nome do usuário)

(c) Ordenar todos os processos de acordo com o uso da CPU?

$ ps --sort=-%cpu

(d) Mostrar a quanto tempo cada processo está rodando?

$ ps aux --sort=start_time

2. De onde vem o nome `fork()`?

O termo Fork vem da palavra bifurcação,

3. Quais são as vantagens e desvantagens em utilizar:

(a) `system()`?

(b) `fork()` e `exec()`?

4. É possível utilizar o `exec()` sem executar o `fork()` antes?

5. Quais são as características básicas das seguintes funções:

(a) `execp()`?

(b) `execv()`?

(c) `exece()`?

(d) `execvp()`?

(e) `execve()`?

(f) `execle()`?
