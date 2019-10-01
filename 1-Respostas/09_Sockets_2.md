1. Crie dois programas em C para criar um cliente e um servidor. Faça com que o cliente envie os valores 1, 2, 3, 4, 5, 6, 7, 8, 9 e 10 para o servidor, com intervalos de 1 segundo entre cada envio. Depois de o cliente enviar o número 10, ele aguarda 1 segundo e termina a execução. O servidor escreve na tela cada valor recebido, e quando ele receber o valor 10, ele termina a execução.

```c
##Client
#include <stdio.h>
#include < stdlib.h>
#include < sys/socket.h>
#include < unistd.h>
#include < string.h>
#include < sys/un.h>


int main ( int argc, char* const argv[])
{

  int socket_id;
  char socket_name ;
	struct sockaddr name;


	socket_name = argv[1 ]; // Recebe socket name por argv[1]
	for (int i = 0; i < 11; ++i )
	{
		fprintf( stderr, "Open socket local... " );
		socket_id = socket(PF_LOCAL , SOCK_STREAM,0) ;
		fprintf(stderr, "Conect socket servidor in ederec local \"%s\"... ", socket_name);
		name.sa_family = AF_LOCAL;
		strcpy(name.sa_data, socket_name);
		connect(socket_id , &name , sizeof( name));
		fprintf(stderr, "Enviando sms ao servid... ");
		write(socket_id, &i, sizeof( i ));
		sleep(1) ;
		fprintf(stderr , "encerrando socket local... ");
		close(socket_id);
		fprintf(stderr, "Realizado!\n");
	}

	return 0;
}

##Server
#include < stdio.h>
#include < stdlib.h>
#include < signal.h>
#include < sys/socket.h>
#include < sys/un.h>
#include < unistd.h>
#include < string.h>

int socket_id;
char socket_name[50];
void end_server(void);
void sigint_handler(int signum);

int main (int argc, char* const argv[] )
{
	struct sockaddr socket_struct ;

	strcpy(socket_name, argv[1] ) ; //Recebe o socket name por argv[1]
	signal(SIGINT, sigint_handler) ;
	strcpy(socket_struct.sa_data, socket_name);
  socket_id = socket(PF_LOCAL, SOCK_STREAM, 0);
	socket_struct.sa_family = AF_LOCAL;
	bind(socket_id, &socket_struct, sizeof(socket_struct));
	listen(socket_id, 10);

	while(1)
	{
		int msg;
		struct sockaddr cliente;
		int socket_id_cliente ;
		socklen_t cliente_len ;

		fprintf(stderr, "Esperando conexao de algum cliente... ");
		socket_id_cliente = accept(socket_id, &cliente, &cliente_len);
		read(socket_id_cliente, &msg, 1) ;
		fprintf(stderr,"\n\n   Mensagem = %d\n\n", msg) ;
		if (msg == 10 )
		{
			fprintf(stderr, " Cliente solicitou encerrar o servidor.\n");
			end_server() ;
		}

		fprintf(stderr, " Encerrando a conexao do cliente... ");
		close(socket_id_cliente ) ;
		fprintf(stderr, "Feito!\n");
	}

	return 0;
}

void sigint_handler(int signum)
{
	fprintf( stderr, "\nRecebido sinal ... encerrar servidor!\n");
	end_server();
}

void end_server(void )
{
	fprintf(stderr, "Apagando \"%s\" do sistema... ", socket_name);
	unlink(socket_name ) ;
	fprintf(stderr, "realizado!\n") ;
	fprintf(stderr, "encerrar socket local... ") ;
	close( socket_id);
	fprintf( stderr, "Feito!\n");
	exit(0 ) ;
}


2. Crie dois programas em C para criar um cliente e um servidor. Execute a seguinte conversa entre cliente e servidor:


CLIENTE: Pai, qual é a verdadeira essência da sabedoria?
SERVIDOR: Não façais nada violento, praticai somente aquilo que é justo e equilibrado.
CLIENTE: Mas até uma criança de três anos sabe disso!
SERVIDOR: Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...


Neste exercício, o cliente deve escrever no terminal as mensagens enviadas e recebidas.

```c
##Cliente
#include < stdio.h>
#include < stdlib.h>
#include < sys/socket.h>
#include < sys/un.h>
#include < unistd.h>
#include < string.h>

int main ( int argc, char* const argv[])
{
	int socket_id ;
  int length ;
	struct sockaddr name;
  char *socket_name;

	socket_name = argv[1];
	char mensagem_1[] = "Pai, qual é a verdadeira essência da sabedoria? ";
  char mensagem_2[] = " Mas até uma criança de três anos sabe disso!";

  char* text;
	socket_id = socket( PF_LOCAL, SOCK_STREAM,0);
	name.sa_family = AF_LOCAL ;
	strcpy(name.sa_data, socket_name );
  connect(socket_id, &name, sizeof( name));

    printf("\n%s\n " , mensagem_1);
    length = strlen(mensagem_1) + 1 ;
	write(socket_id, mensagem_1, length ) ;
  write( socket_id, &length, sizeof(length) ) ;

	while(1)
	{   
		read(socket_id , &length , sizeof (length));
		text = (char*) malloc ( length);
		read(socket_id, text, length) ;    

		if(!strcmp (text, "Key ") )
		{
			read(socket_id, &length, sizeof (length));
			text = (char*) malloc ( length) ;
			read(socket_id, text , length) ;
			fprintf(stderr, "\n\n O cliente leu: %s.\n\n", text );
			break ;
		}
	}   

  printf("\n%s\n", mensagem_2 ) ;
	length = strlen("chave") + 1;
	write(socket_id, "key", length);
  write(socket_id, &length, sizeof( length));


  length = strlen(mensagem_2) + 1;
	write(socket_id, mensagem_2, length);
  write(socket_id, &length, sizeof(length)) ;

	while(1)
	{   
		read(socket_id, &length, sizeof (length ));
		text = (char*) malloc (length);
		read(socket_id, text, length) ;    

		if(!strcmp (text, "key") )
		{
			read(socket_id, &length, sizeof (length) );
			text = (char*) malloc (length);
			read(socket_id, text, length) ;
			fprintf(stderr, "\n\n O cliente leu: %s.\n\n", text);
			break ;
		}
	}   

	close(socket_id);
	fprintf(stderr, "Realizado!\n");
	return 0 ;
}

##Server
#include < stdio.h>
#include < stdlib.h>
#include < sys/socket.h>
#include < sys/un.h>
#include < signal.h >
#include < unistd.h>
#include < string.h>

int socket_id;
void end_server(void) ;
void sigint_handler(int signum);
void print_client_message(int client_socket) ;
char socket_name[50] ;

int main (int argc, char* const argv[] )
{
	strcpy(socket_name, argv[1]);
	struct sockaddr socket_struct ;
	socket_struct.sa_family = AF_LOCAL ;
  signal(SIGINT, sigint_handler);
	socket_id = socket(PF_LOCAL, SOCK_STREAM, 0) ;
	bind(socket_id, &socket_struct, sizeof(socket_struct));
	strcpy(socket_struct.sa_data, socket_name);

	listen(socket_id, 10) ;

	while(1)
	{
		struct sockaddr cliente ;
		int socket_id_cliente;

		socklen_t cliente_len ;

		fprintf(stderr, "Esperando conexao com algum cliente... ") ;

		socket_id_cliente = accept(socket_id, &cliente, &cliente_len ) ;
		fprintf(stderr, "Realizado!\n") ;

		fprintf(stderr, "Coletando dados enviados pelo cliente... ") ;

		print_client_message(socket_id_cliente) ;
		fprintf(stderr, "Realizado!\n");

		fprintf(stderr, "Encerrando conexao com cliente... " );
		close(socket_id_cliente);
		fprintf(stderr, "Realizado!\n") ;
	}
	return 0;
}

void sigint_handler(int signum)
{
	fprintf(stderr, "\n Sinal recebido... Encerrar servidor!\n");
	end_server();
}


void print_client_message(int client_socket)
{
	char mensagem_1[] = " Não façais nada violento, praticai somente aquilo que é justo e equilibrado.";    
	char mensagem_2[] = "Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu..." ;
	char* text;
  int length;

	read(client_socket, &length, sizeof (length)) ;
	text = (char*) malloc (length);
	read(client_socket, text, length) ;
	fprintf(stderr, "\n\nservidor leu: %s.\n\n", text) ;

	length = strlen("c") + 1;
	write(client_socket, "c", length) ;
	write(client_socket, &length, sizeof(length));

 	length = strlen(mensagem_1) + 1 ;
 	write(client_socket, mensagem_1, length);
	write(client_socket, &length, sizeof(length)) ;

	while(1)
	{   
		read(client_socket, &length, sizeof (length) );
		text = (char*) malloc (length);
		read(client_socket, text, length) ;    

		if(!strcmp (text, " c"))
		{
			read(client_socket, &length, sizeof (length));
			text = (char*) malloc (length ) ;
			read(client_socket, text, length);
			fprintf(stderr, "\n\nservidor leu: %s.\n\n", text);
			break ;
		}
	}

	length = strlen("c") + 1;
	write(client_socket, " c", length) ;
  write(client_socket, &length, sizeof(length));

 	length = strlen(mensagem_2) + 1 ;
	write(client_socket, mensagem_2, length);
  write(client_socket, &length, sizeof(length));    
  end_server() ;
}

void end_server(void)
{
	fprintf( stderr, "deletando \"%s\" do sistema...  ", socket_name ) ;
	unlink(socket_name);
	fprintf(stderr, "encerrando socket local... ") ;
	fprintf(stderr, "realizado!\n") ;
  close(socket_id );
	fprintf(stderr, "realizado!\n") ;
	exit(0) ;
}

```
