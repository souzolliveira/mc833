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
#include <netinet/in.h>
#include <dirent.h>

#define MAX_CLIENTS 5
#define EMAIL 0
#define NAME 1
#define LASTNAME 2
#define CITY 3
#define COURSE 4
#define YEAR 5
#define SKILLS 6

// to compile: gcc server.c -o server -lws2_32
// to execute: ./server.exe

// Profile's sample:
// Email: maria_souza@gmail.com
// Name: Maria
// Last name: Souza
// Residence: Campinas
// Graduation: Ciência da Computação
// Graduation year: 2018
// Skills: Ciência dos Dados, Internet das Coisas, Computação em Nuvem

// Register a new profile using email as identifier
int newProfile(struct sockaddr_in client_sock, char data[], char res[])
{
  memset(res, '\0', 1024);
  int i = 0;
  char *p = strtok(data, ";"), *array[8];

  while (p != NULL)
  {
    array[i++] = p;
    p = strtok(NULL, ";");
  }

  char filename[104];
  strcpy(filename, array[1]);
  strcat(filename, ".txt");
  FILE *file;
  file = fopen(filename, "w");
  if (file == NULL)
  {
    strcpy(res, "Perfil salvo com sucesso!");
    return 0;
  }
  fprintf(file, array[1]);
  fprintf(file, "\n");
  fprintf(file, array[2]);
  fprintf(file, "\n");
  fprintf(file, array[3]);
  fprintf(file, "\n");
  fprintf(file, array[4]);
  fprintf(file, "\n");
  fprintf(file, array[5]);
  fprintf(file, "\n");
  fprintf(file, array[6]);
  fprintf(file, "\n");
  fprintf(file, array[7]);
  fclose(file);
  strcpy(res, "Perfil salvo com sucesso!");
  return 0;
}

// List all profiles (email and name) graduated in a given course
int listByCourse(char data[], char res[])
{
  memset(res, '\0', 1024);
  int i = 0;
  char *p = strtok(data, ";"), *array[2];
  while (p != NULL)
  {
    array[i++] = p;
    p = strtok(NULL, ";");
  }
  DIR *directory;
  struct dirent *dir;
  directory = opendir(".");
  if (directory)
  {
    while ((dir = readdir(directory)) != NULL)
    {
      if (strstr(dir->d_name, ".txt") != NULL)
      {
        FILE *file;
        char content[1024];
        char profile[1024];
        file = fopen(dir->d_name, "r");
        for (i = 0; i <= COURSE; i++)
        {
          fgets(content, 100, file);
          if (i == EMAIL)
          {
            strcpy(profile, content);
            if (profile[strlen(profile) - 1] == '\n')
            {
              profile[strlen(profile) - 1] = '\0';
            }
            strcat(profile, ";");
          }
          else if (i == NAME)
          {
            strcat(profile, content);
            if (profile[strlen(profile) - 1] == '\n')
            {
              profile[strlen(profile) - 1] = '\0';
            }
          }
          else if (i == COURSE)
          {
            if (content[strlen(content) - 1] == '\n')
            {
              content[strlen(content) - 1] = '\0';
            }
          }
        }
        if (strcmp(content, array[1]) == 0)
        {
          strcat(profile, "\n");
          strcat(res, profile);
          memset(profile, '\0', 1024);
        }
        fclose(file);
      }
    }
    closedir(directory);
  }
  return 0;
}

// List all profiles (email and name) who have a certain skill
int listBySkill(char data[], char res[])
{
  memset(res, '\0', 1024);
  int i = 0;
  char *p = strtok(data, ";"), *array[2];
  while (p != NULL)
  {
    array[i++] = p;
    p = strtok(NULL, ";");
  }
  if (array[1][strlen(array[1]) - 1] == '\n')
  {
    array[1][strlen(array[1]) - 1] = '\0';
  }
  DIR *directory;
  struct dirent *dir;
  directory = opendir(".");
  if (directory)
  {
    while ((dir = readdir(directory)) != NULL)
    {
      if (strstr(dir->d_name, ".txt") != NULL)
      {
        FILE *file;
        char content[1024];
        char profile[1024];
        file = fopen(dir->d_name, "r");
        for (i = 0; i <= SKILLS; i++)
        {
          fgets(content, 100, file);
          if (i == EMAIL)
          {
            strcpy(profile, content);
            if (profile[strlen(profile) - 1] == '\n')
            {
              profile[strlen(profile) - 1] = '\0';
            }
            strcat(profile, ";");
          }
          else if (i == NAME)
          {
            strcat(profile, content);
            if (profile[strlen(profile) - 1] == '\n')
            {
              profile[strlen(profile) - 1] = '\0';
            }
          }
        }
        if (strstr(content, array[1]))
        {
          strcat(profile, "\n");
          strcat(res, profile);
          memset(profile, '\0', 1024);
        }
        fclose(file);
      }
    }
    closedir(directory);
  }
  return 0;
}

// List all profiles (email, name and course) graduated in a given year
int listByConclusionYear(char data[], char res[])
{
  memset(res, '\0', 1024);
  int i = 0;
  char *p = strtok(data, ";"), *array[2];
  while (p != NULL)
  {
    array[i++] = p;
    p = strtok(NULL, ";");
  }
  DIR *directory;
  struct dirent *dir;
  directory = opendir(".");
  if (directory)
  {
    while ((dir = readdir(directory)) != NULL)
    {
      if (strstr(dir->d_name, ".txt") != NULL)
      {
        FILE *file;
        char content[1024];
        char profile[1024];
        file = fopen(dir->d_name, "r");
        for (i = 0; i <= YEAR; i++)
        {
          fgets(content, 100, file);
          if (i == EMAIL)
          {
            strcpy(profile, content);
            if (profile[strlen(profile) - 1] == '\n')
            {
              profile[strlen(profile) - 1] = '\0';
            }
            strcat(profile, ";");
          }
          else if (i == NAME)
          {
            strcat(profile, content);
            if (profile[strlen(profile) - 1] == '\n')
            {
              profile[strlen(profile) - 1] = '\0';
            }
            strcat(profile, ";");
          }
          else if (i == COURSE)
          {
            strcat(profile, content);
            if (profile[strlen(profile) - 1] == '\n')
            {
              profile[strlen(profile) - 1] = '\0';
            }
          }
          else if (i == YEAR)
          {
            if (content[strlen(content) - 1] == '\n')
            {
              content[strlen(content) - 1] = '\0';
            }
          }
        }
        if (strcmp(content, array[1]) == 0)
        {
          strcat(profile, "\n");
          strcat(res, profile);
          memset(profile, '\0', 1024);
        }
        fclose(file);
      }
    }
    closedir(directory);
  }
  return 0;
}

// List all information from all profiles
int listAll(char res[])
{
  memset(res, '\0', 1024);
  int i = 0;
  DIR *directory;
  struct dirent *dir;
  directory = opendir(".");
  if (directory)
  {
    while ((dir = readdir(directory)) != NULL)
    {
      if (strstr(dir->d_name, ".txt") != NULL)
      {
        FILE *file;
        char content[1024];
        char profile[1024];
        file = fopen(dir->d_name, "r");
        for (i = 0; i <= SKILLS; i++)
        {
          fgets(content, 100, file);
          strcat(profile, content);
          if (profile[strlen(profile) - 1] == '\n')
          {
            profile[strlen(profile) - 1] = '\0';
          }
          if (i != SKILLS)
          {
            strcat(profile, ";");
          }
        }
        strcat(profile, "\n");
        strcat(res, profile);
        memset(profile, '\0', 1024);
        fclose(file);
      }
    }
    closedir(directory);
  }
  return 0;
}

// Given a profile's email, return their information
int getProfile(char data[], char res[])
{
  memset(res, '\0', 1024);
  int i = 0;
  char *p = strtok(data, ";"), *array[2];

  while (p != NULL)
  {
    array[i++] = p;
    p = strtok(NULL, ";");
  }
  if (array[1][strlen(array[1]) - 1] == '\n')
  {
    array[1][strlen(array[1]) - 1] = '\0';
  }
  char content[1024];
  char profile[1024];
  char filename[104];
  FILE *file;
  strcpy(filename, array[1]);
  strcat(filename, ".txt");
  file = fopen(filename, "r");
  for (i = 0; i <= SKILLS; i++)
  {
    fgets(content, 100, file);
    if (content[strlen(content) - 1] == '\n')
    {
      content[strlen(content) - 1] = '\0';
    }
    strcat(profile, content);
    if (i != SKILLS)
    {
      strcat(profile, ";");
    }
  }
  strcat(res, profile);
  memset(profile, '\0', 1024);
  fclose(file);
  return 0;
}

// Removing a profile from its identifier (email)
int removeProfile(char data[], char res[])
{
  memset(res, '\0', 1024);
  int i = 0;
  char *p = strtok(data, ";"), *array[2];

  while (p != NULL)
  {
    array[i++] = p;
    p = strtok(NULL, ";");
  }
  char filename[104];
  strcpy(filename, array[1]);
  strcat(filename, ".txt");
  int delete = remove(filename);
  if (delete == 0)
  {
    strcpy(res, "Perfil apagado com sucesso!");
    return 0;
  }
  strcpy(res, "Perfil não encontrado!");
  return 0;
}

int main()
{
  int port = 8080, server_sock, n;
  struct sockaddr_in server_addr;

  server_sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_sock < 0)
  {
    perror("ERRO AO CRIAR SERVER SOCKET");
    exit(1);
  }

  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  n = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (n < 0)
  {
    perror("ERRO AO FAZER BIND DE SOCKET ID A ESTRUTURA DE SOCKET");
    exit(1);
  }

  struct sockaddr_in client_addr;
  socklen_t addr_size = sizeof(client_addr);
  char buffer[1024], res[1024];
  int client_sizeof = sizeof(client_addr);
  while (1)
  {
    memset(buffer, '\0', 1024);
    memset(res, '\0', 1024);
    int req = recvfrom(server_sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_sizeof);
    if (req > 0)
    {
      printf("\nMensagem recebida do cliente: %s\n", buffer);
      if (strlen(buffer) != 0)
      {
        if (buffer[0] == '1')
          newProfile(client_addr, buffer, res);
        else if (buffer[0] == '2')
          listByCourse(buffer, res);
        else if (buffer[0] == '3')
          listBySkill(buffer, res);
        else if (buffer[0] == '4')
          listByConclusionYear(buffer, res);
        else if (buffer[0] == '5')
          listAll(res);
        else if (buffer[0] == '6')
          getProfile(buffer, res);
        else if (buffer[0] == '7')
          removeProfile(buffer, res);
      }
    }
    int resp = sendto(server_sock, res, strlen(res), 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
    if (resp > 0)
    {
      printf("\nMensagem enviada ao cliente: %s\n", res);
      memset(buffer, '\0', 1024);
      memset(res, '\0', 1024);
    }
  }

  close(server_sock);

  printf("\n##### SESSAO ENCERRADA #####\n");

  return 0;
}
