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

int receiveFromServer(int client_sock, struct sockaddr_in server_addr)
{
  int server_addr_sizeof = sizeof(server_addr);
  char res[1024];
  int len_received = recvfrom(client_sock, res, sizeof(res), 0, (struct sockaddr *)&server_addr, &server_addr_sizeof);
  res[len_received] = '\0';
  printf("\nMensagem recebida do servidor: %s\n", res);
  for (int i = 0; i < 1024; i++)
    res[i] = '\0';
  return 0;
}

int sendToServer(int client_sock, char *op, char *data, struct sockaddr_in server_addr)
{
  char buffer[1024];
  memset(buffer, '\0', 1024);
  strcat(buffer, op);
  strcat(buffer, ";");
  strcat(buffer, data);
  printf("\nMensagem enviada ao servidor: %s\n", buffer);
  int a = sendto(client_sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
  receiveFromServer(client_sock, server_addr);

  return 0;
}

int options(int client_sock, char *op, struct sockaddr_in server_addr)
{
  char data[1024];
  if (strcmp(op, "1") == 0)
  {
    printf("\nDigite os dados seguindo o modelo:\n");
    printf("email;nome;sobrenome;cidade;curso-de-graduacao;ano-de-formacao;habilidade1,habilidade2,habilidade3\n");
    printf("\nDados: ");
    fflush(stdin);
    fgets(data, 1020, stdin);
    data[strcspn(data, "\n")] = 0;
  }
  else if (strcmp(op, "2") == 0)
  {
    printf("\nDigite o curso:\n");
    printf("\nCurso: ");
    fflush(stdin);
    fgets(data, 1020, stdin);
    data[strcspn(data, "\n")] = 0;
  }
  else if (strcmp(op, "3") == 0)
  {
    printf("\nDigite a habilidade:\n");
    printf("\nHabilidade: ");
    fflush(stdin);
    fgets(data, 1020, stdin);
    data[strcspn(data, "\n")] = 0;
  }
  else if (strcmp(op, "4") == 0)
  {
    printf("\nDigite o ano de conslusao:\n");
    printf("\nAno: ");
    fflush(stdin);
    fgets(data, 1020, stdin);
    data[strcspn(data, "\n")] = 0;
  }
  else if (strcmp(op, "5") == 0)
  {
    printf("\n");
  }
  else if (strcmp(op, "6") == 0)
  {
    printf("\nDigite o email do perfil que deseja ver:\n");
    printf("\nEmail: ");
    fflush(stdin);
    fgets(data, 1020, stdin);
    data[strcspn(data, "\n")] = 0;
  }
  else if (strcmp(op, "7") == 0)
  {
    printf("\nDigite o email do pefil que deseja excluir:\n");
    printf("\nEmail: ");
    fflush(stdin);
    fgets(data, 1020, stdin);
    data[strcspn(data, "\n")] = 0;
  }
  else if (strcmp(op, "8") == 0)
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
  char *ip = "127.0.0.1", option[10];
  int port = 8080, client_sock;
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

  while (1)
  {
    memset(option, '\0', sizeof(option));
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
    fflush(stdin);
    fgets(option, 10, stdin);
    option[strcspn(option, "\n")] = 0;
    if (strcmp(option, "8") == 0)
    {
      break;
    }
    else
    {
      options(client_sock, option, server_addr);
    }
  }

  close(client_sock);

  printf("\n##### SESSAO ENCERRADA #####\n");

  return 0;
}
