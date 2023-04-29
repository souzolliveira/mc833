#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <winsock2.h>
#include <WS2tcpip.h>

// to compile: gcc client.c -o client -lws2_32
// to execute: ./client.exe

int sendToServer(int sock, int op, char *data)
{
  if (data[strlen(data) - 1] == '\n')
  {
    data[strlen(data) - 1] = '\0';
  }
  char buffer[1024], res[1024];

  itoa(op, buffer, 10);
  strcat(buffer, ";");
  strcat(buffer, data);
  printf("\nMensagem enviada ao servidor: %s\n", buffer);
  send(sock, buffer, strlen(buffer), 0);

  recv(sock, res, sizeof(res), 0);
  printf("\nMensagem recebida do servidor: %s\n", res);

  return 0;
}

int options(int sock, int op)
{
  char data[1024];
  if (op == 1)
  {
    printf("\nDigite os dados seguindo o modelo:\n");
    printf("email;nome;sobrenome;cidade;curso-de-graduacao;ano-de-formacao;habilidade1,habilidade2,habilidade3\n");
    printf("\nDados: ");
    fgets(data, 1020, stdin);
  }
  else if (op == 2)
  {
    printf("\nDigite o curso:\n");
    printf("\nCurso: ");
    fgets(data, 1020, stdin);
  }
  else if (op == 3)
  {
    printf("\nDigite a habilidade:\n");
    printf("\nHabilidade: ");
    fgets(data, 1020, stdin);
  }
  else if (op == 4)
  {
    printf("\nDigite o ano de conslusao:\n");
    printf("\nAno: ");
    fgets(data, 1020, stdin);
  }
  else if (op == 5)
  {
    printf("\n");
  }
  else if (op == 6)
  {
    printf("\nDigite o email do perfil que deseja ver:\n");
    printf("\nEmail: ");
    fgets(data, 1020, stdin);
  }
  else if (op == 7)
  {
    printf("\nDigite o email do pefil que deseja excluir:\n");
    printf("\nEmail: ");
    fgets(data, 1020, stdin);
  }
  else if (op == 8)
  {
    // send(sock, "8", 1, 0);
    printf("\nEncerrando...\n");
    return 0;
  }
  else
  {
    printf("\nOpcao invalida\n");
    return 0;
  }
  sendToServer(sock, op, data);
  return 0;
}

int main()
{
  char *ip = "127.0.0.1";
  int port = 8080, sock, option = 0;
  struct sockaddr_in addr;
  socklen_t addr_size;

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr(ip);

  WSADATA Data;
  WSAStartup(MAKEWORD(2, 2), &Data);
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    perror("ERRO AO CONECTAR NO SOCKET");
    exit(1);
  }

  connect(sock, (struct sockaddr *)&addr, sizeof(addr));
  printf("##### SESSAO INICIADA #####\n");

  while (option != 8)
  {
    printf("\nEscolha uma das opcoes:\n");
    printf("1- Novo perfil;\n");
    printf("2- Listar alunos por curso;\n");
    printf("3- Listar alunos por habilidade;\n");
    printf("4- Listar alunos por ano de conclusao;\n");
    printf("5- Listar todos alunos;\n");
    printf("6- Ver perfil;\n");
    printf("7- Remover perfil;\n");
    printf("8- Encerrar.\n\n");
    printf("Opcao: ");
    scanf("%d", &option);
    fflush(stdin);
    options(sock, option);
  }

  close(sock);
  printf("\n##### SESSAO ENCERRADA #####\n");

  return 0;
}
