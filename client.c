/**
 * MC833
 * ALUNO: EMANUEL DE SOUZA OLIVEIRA
 * RA: 170442
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// to compile: gcc client.c -o client -lws2_32
// to execute: ./client.exe

int receiveFromServer(int client_sock, char buffer[1024], int op, struct sockaddr_in server_addr)
{
  int server_addr_sizeof = sizeof(server_addr);
  char res[1024];
  recvfrom(client_sock, res, sizeof(res), 0, (struct sockaddr *)&server_addr, &server_addr_sizeof);
  printf("\nMensagem recebida do servidor: %s\n", res);
  return 0;
}

int sendToServer(int client_sock, int op, char *data, struct sockaddr_in server_addr)
{
  if (data[strlen(data) - 1] == '\n')
  {
    data[strlen(data) - 1] = '\0';
  }
  char buffer[1024];

  snprintf(buffer, sizeof(buffer), "%d", op);
  strcat(buffer, ";");
  strcat(buffer, data);
  printf("\nMensagem enviada ao servidor: %s\n", buffer);
  int a = sendto(client_sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
  receiveFromServer(client_sock, buffer, op, server_addr);

  return 0;
}

int options(int client_sock, int op, struct sockaddr_in server_addr)
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
    printf("\nEncerrando...\n");
    return 0;
  }
  else
  {
    printf("\nOpcao invalida\n");
    return 0;
  }
  sendToServer(client_sock, op, data, server_addr);
  return 0;
}

int main()
{
  char *ip = "127.0.0.1";
  int port = 8080, client_sock, option = 0;
  struct sockaddr_in server_addr;
  socklen_t addr_size;

  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(ip);

  client_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (client_sock < 0)
  {
    perror("ERRO AO CONECTAR NO SOCKET");
    exit(1);
  }

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
    options(client_sock, option, server_addr);
  }

  close(client_sock);

  printf("\n##### SESSAO ENCERRADA #####\n");

  return 0;
}
