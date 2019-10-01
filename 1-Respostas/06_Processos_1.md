1. Como se utiliza o comando `ps` para:

(a) Mostrar todos os processos rodando na máquina?
```
$ ps -e
```

(b) Mostrar os processos de um usuário?
```
$ ps -u (nome do usuário)
```

(c) Ordenar todos os processos de acordo com o uso da CPU?
```
$ ps --sort=-%cpu
```

(d) Mostrar a quanto tempo cada processo está rodando?
```
$ ps aux --sort=start_time
```

2. De onde vem o nome `fork()`?
```
O termo Fork vem da palavra bifurcação.
```

3. Quais são as vantagens e desvantagens em utilizar:

(a) `system()`?
```
Essa função permite executar comandos e processos dentro de um programa. Como desvantagem , apresenta vulnerabilidade a falhas devido a dependência do sistema.
```

(b) `fork()` e `exec()`?
```
A função exec permite a substituição do processo pai por um novo processo e a função fork permite criar uma cópia do processo pai.
```

4. É possível utilizar o `exec()` sem executar o `fork()` antes?
```
É possível sim, mas se perde o processo pai.
```

5. Quais são as características básicas das seguintes funções:

(a) `execp()`?
```
Ela permite executar um programa no lugar atual.
```

(b) `execv()`?
```
Ela permite que a lista de argumentos do novo processo seja nula.
```

(c) `exece()`?
```
Ela permite usar o argumento adicional no novo processo.
```

(d) `execvp()`?
```
Permite uma lista de argumentos nula e procura do programa no current path.
```

(e) `execve()`?
```
Essa função permite procurar o programa no current path e argumento adicional.
```

(f) `execle()`?
```
Essa função permiti usar argumento adicional e var agrs.
```
