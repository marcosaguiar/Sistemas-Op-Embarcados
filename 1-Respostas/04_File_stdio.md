Para todas as questões, utilize as funções da biblioteca `stdio.h` de leitura e de escrita em arquivo (`fopen()`, `fclose()`, `fwrite()`, `fread()`, dentre outras). Compile os códigos com o gcc e execute-os via terminal.

1. Crie um código em C para escrever "Ola mundo!" em um arquivo chamado 'ola_mundo.txt'.

#include <stdio.h>
int main(int argc, char const *argv[])
{
        FILE * p;
        p = fopen("ola_mundo.txt", "w+");
        fprintf(p, "Ola Mundo!\n");
        fclose(p);
        return 0;
}


2. Crie um código em C que pergunta ao usuário seu nome e sua idade, e escreve este conteúdo em um arquivo com o seu nome e extensão '.txt'. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_1':

```bash
$ ./ola_usuario_1
$ Digite o seu nome: Eu
$ Digite a sua idade: 30
$ cat Eu.txt
$ Nome: Eu
$ Idade: 30 anos
```

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])

{
        FILE * p;
        char nome[31], idade[4];
        printf("Digite seu nome: \n");
        fgets(nome, 31, stdin);
        printf("Digite a sua idade: \n");
        fgets(idade, 4, stdin);
        nome[strcspn(nome, "\n")] = 0;
        p = fopen(strcat(nome, ".txt"), "w+");
        fprintf(p, "Nome: %s\n", nome);
        fprintf(p, "Idade: %s", idade);
        fclose(p);
        return 0;
}


3. Crie um código em C que recebe o nome do usuário e e sua idade como argumentos de entrada (usando as variáveis `argc` e `*argv[]`), e escreve este conteúdo em um arquivo com o seu nome e extensão '.txt'. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_2':

```bash
$ ./ola_usuario_2 Eu 30
$ cat Eu.txt
$ Nome: Eu
$ Idade: 30 anos
```

int main(int argc, char const *argv[])
{
	FILE * p;
	char * fileName;
	fileName = malloc(sizeof(strlen(argv[1]+5)));
	strcpy(fileName,argv[1]);
	strcat(fileName,".txt");
	p = fopen(fileName,"w+");
	fprintf(fp, "Nome: %s\n",argv[1]);
	fprintf(fp, "Idade: %s\n", argv[2]);
	fclose(fp);
	free(fileName);
	return 0;
}

4. Crie uma função que retorna o tamanho de um arquivo, usando o seguinte protótipo: `int tam_arq_texto(char *nome_arquivo);` Salve esta função em um arquivo separado chamado 'bib_arqs.c'. Salve o protótipo em um arquivo chamado 'bib_arqs.h'. Compile 'bib_arqs.c' para gerar o objeto 'bib_arqs.o'.

int tam_arq_texto(char *nome_arquivo)
{
	FILE * p;
	int fileLength = 0;
	char str[1000];
	p = fopen(nome_arquivo,"r");
	if(!p)
	{
		printf("Erro ao abrir arquivo!\n");
		return 0;
	}
	while(fgets(str, 1000, fp) != NULL)
		fileLength += strlen(str);
	fclose(p);
	return fileLength;
}

5. Crie uma função que lê o conteúdo de um arquivo-texto e o guarda em uma string, usando o seguinte protótipo: `char* le_arq_texto(char *nome_arquivo);` Repare que o conteúdo do arquivo é armazenado em um vetor interno à função, e o endereço do vetor é retornado ao final. (Se você alocar este vetor dinamicamente, lembre-se de liberar a memória dele quando acabar o seu uso.) Salve esta função no mesmo arquivo da questão 4, chamado 'bib_arqs.c'. Salve o protótipo no arquivo 'bib_arqs.h'. Compile 'bib_arqs.c' novamente para gerar o objeto 'bib_arqs.o'.

char* le_arq_texto(char *nome_arquivo)
{
	FILE * p;
	char * fileData;
	int fileLength = tam_arq_texto(nome_arquivo);
	fileData = malloc(sizeof(char) * fileLength);
	p = fopen(nome_arquivo,"r");
	if(!p)
	{
		printf("Erro ao abrir arquivo!\n");
		return 0;
	}
	fgets(fileData, fileLength, p);
	fclose(p);
	free(fileData);
	return fileData;
}
6. Crie um código em C que copia a funcionalidade básica do comando `cat`: escrever o conteúdo de um arquivo-texto no terminal. Reaproveite as funções já criadas nas questões anteriores. Por exemplo, considerando que o código criado recebeu o nome de 'cat_falsificado':

```bash
$ echo Ola mundo cruel! Ola universo ingrato! > ola.txt
$ ./cat_falsificado ola.txt
$ Ola mundo cruel! Ola universo ingrato!
```

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib_arqs.h"

int main(int argc, char const *argv[])
{

	printf("%s\n", le_arq_texto(argv[1]));
	return 0;
}

7. Crie um código em C que conta a ocorrência de uma palavra-chave em um arquivo-texto, e escreve o resultado no terminal. Reaproveite as funções já criadas nas questões anteriores. Por exemplo, considerando que o código criado recebeu o nome de 'busca_e_conta':

```bash
$ echo Ola mundo cruel! Ola universo ingrato! > ola.txt
$ ./busca_e_conta Ola ola.txt
$ 'Ola' ocorre 2 vezes no arquivo 'ola.txt'.
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib_arqs.h"

int main(int argc, char const *argv[])
{
	char *str = le_arq_texto((char *) argv[2]);
	char *srch = (char *) argv[1];
	int len = strlen(srch);
	int count = 0;
	char *where = str;

	if (len)
    while ((where = strstr(where, srch))) {
        where += len;
        count++;
    }
    printf("'%s' ocorre %d vezes no arquivo %s\n", argv[1],count,argv[2]);
	return 0;
}
