#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
// Defina o tamanho máximo para as strings de categoria, descrição e estado
#define MAX_CATEGORIA 100
#define MAX_DESCRICAO 300
#define MAX_ESTADO 50

typedef struct {
    int prioridade;
    char categoria[MAX_CATEGORIA];
    char descricao[MAX_DESCRICAO];
    char estado[MAX_ESTADO];  // Novo campo para o estado da tarefa
} Tarefa;

typedef struct {
    Tarefa tarefas[100];
    int qtd;
} ListaDeTarefas;

ListaDeTarefas lt;



void menu(){
    int opcao;
    lt.qtd = 0;
// essa funcao apredi estudando no semestre passado para nossa prova, a funcao
  // DO WHILE serve para repetir o menu toda vez q a pessoa escolher uma opcao
  // certa, caso contrário mesmo que a condição existente no WHILE seja falsa
  // (se for falsa, vai rodar só uma vez e termina).
    do {
        printMenu();
        scanf("%d", &opcao);
 // aplica a funcao escolhida pelo usuario
        switch (opcao) {
            case 1:
                cadastrarTarefa();
                break;
            case 2:
                deletarTarefa();
                break;
            case 3:
                listarTarefas();
                break;
          case 4:
                alterarTarefa();
                break;
          case 5:
                exportar();
                break;
          case 6:
            
                if (salvarTarefas() == 0) {
                    printf("Erro ao salvar as tarefas em arquivo.\n");
                }
                printf("Saindo do programa. Tarefas salvas em arquivo.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 6); // a condicao para o DO WHILE falado a cima
}
// funcao para rodar o menu 
void printMenu() {
    printf("\nMenu:\n");
    printf("1. Cadastrar Tarefa\n");
    printf("2. Deletar Tarefa\n");
    printf("3. Listar Tarefas\n");
    printf("4. Altarar Tarefa\n");
    printf("5. Exportar\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
}
void abrearquivo(){
    char arquivo[] = "tarefas.bin";

    //carrega tarefas do arquivo
    if (carregarTarefas(&lt, arquivo) == 0) {
        printf("Criando um novo arquivo de tarefas.\n");
    }
}
// Função para cadastrar uma nova tarefa
int cadastrarTarefa() {
    if (lt.qtd < 100) {
        Tarefa tarefa;
        printf("Prioridade (0-10): ");
        scanf("%d", &tarefa.prioridade);

        printf("Categoria (até %d letras): ", MAX_CATEGORIA - 1);
        scanf(" %[^\n]", tarefa.categoria);

        printf("Descrição (até %d letras): ", MAX_DESCRICAO - 1);
        scanf(" %[^\n]", tarefa.descricao);

        printf("Estado (até %d letras): ", MAX_ESTADO - 1);
        scanf(" %[^\n]", tarefa.estado);

        lt.tarefas[lt.qtd] = tarefa;
        lt.qtd++;
        printf("Tarefa cadastrada com sucesso!\n");
        return 1;
    } else {
        printf("Limite máximo de tarefas atingido!\n");
        return 0;
    }
}


// Função para deletar uma tarefa, na funcao ela age de acordo com o valor iniformado
//pelo usuario, conferindo se existe a tarefa na lista ou nao, caso esteja a tarefa e apagada com sucesso.
int deletarTarefa() {
    if (lt.qtd > 0) {
        int index;
        printf("Informe o índice da tarefa a ser deletada (1-%d): ", lt.qtd);
        scanf("%d", &index);
        if (index >= 1 && index <= lt.qtd) {
            for (int i = index - 1; i < lt.qtd - 1; i++) {
                lt.tarefas[i] = lt.tarefas[i + 1];
            }
            lt.qtd--;
            printf("Tarefa deletada com sucesso!\n");
            return 1;
        } else {
            printf("Índice inválido!\n");
            return 0;
        }
    } else {
        printf("Não há tarefas cadastradas.\n");
        return 0;
    }
}
int listarTarefas() {
    if (lt.qtd > 0) {
        printf("Listagem de Tarefas:\n");

        for (int i = 0; i < lt.qtd; i++) {
            printf("Tarefa #%d\n", i + 1);
            printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
            printf("Categoria: %s\n", lt.tarefas[i].categoria);
            printf("Descrição: %s\n", lt.tarefas[i].descricao);
            printf("Estado: %s\n\n", lt.tarefas[i].estado);
        }
        return 1;
    } else {
        printf("Não há tarefas cadastradas.\n");
        return 0;
    }
}



// Função para salvar tarefas em um arquivo binário
int salvarTarefas(char *arquivo) {
    FILE *file = fopen(arquivo, "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    // Escrever a quantidade de tarefas
    fwrite(&lt.qtd, sizeof(int), 1, file);

    // Escrever as tarefas
    fwrite(lt.tarefas, sizeof(Tarefa), lt.qtd, file);

    fclose(file);
    printf("Tarefas salvas com sucesso!\n");
    return 1;
}

// Função para carregar tarefas de um arquivo binário
int carregarTarefas(char *arquivo) {
    FILE *file = fopen(arquivo, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    // Ler a quantidade de tarefas
    fread(&lt.qtd, sizeof(int), 1, file);

    // Ler as tarefas
    fread(lt.tarefas, sizeof(Tarefa), lt.qtd, file);

    fclose(file);
    printf("Tarefas carregadas com sucesso!\n");
    return 1;
}
void exportarPorPrioridade() {
  int prioridade;
  printf("Informe a prioridade desejada (0-10): ");
  scanf("%d", &prioridade);

  char arquivo[100];
  sprintf(arquivo, "tarefas_prioridade_%d.txt", prioridade);

  FILE *file = fopen(arquivo, "w");
  if (file == NULL) {
      perror("Erro ao criar o arquivo");
      return;
  }

  for (int i = 0; i < lt.qtd; i++) {
      if (lt.tarefas[i].prioridade == prioridade) {
          fprintf(file, "%d, %s, %s, %s, %s\n", lt.tarefas[i].prioridade, lt.tarefas[i].categoria, lt.tarefas[i].estado, lt.tarefas[i].descricao);
      }
  }

  fclose(file);
  printf("Tarefas exportadas com sucesso para %s!\n", arquivo);
}
void alterarTarefa() {
    if (lt.qtd > 0) {
        int index;
        printf("Informe o índice da tarefa a ser alterada (1-%d): ", lt.qtd);
        scanf("%d", &index);
        if (index >= 1 && index <= lt.qtd) {
            Tarefa tarefa;
            printf("Prioridade (0-10): ");
            scanf("%d", &tarefa.prioridade);

            printf("Categoria (até 100 letras): ");
            scanf(" %[^\n]", tarefa.categoria);

            printf("Descrição (até 300 letras): ");
            scanf(" %[^\n]", tarefa.descricao);

            lt.tarefas[index - 1] = tarefa;
            printf("Tarefa alterada com sucesso!\n");
        } else {
            printf("Índice inválido!\n");
        }
    } else {
        printf("Não há tarefas cadastradas.\n");
    }
}
void filtrarPorPrioridade() {
    int prioridade;
    printf("Informe a prioridade desejada (0-10): ");
    scanf("%d", &prioridade);

    printf("Tarefas com prioridade %d:\n", prioridade);

    for (int i = 0; i < lt.qtd; i++) {
        if (lt.tarefas[i].prioridade == prioridade) {
            printf("Categoria: %s\n", lt.tarefas[i].categoria);
            printf("Descrição: %s\n\n", lt.tarefas[i].descricao);
        }
    }
}
void filtrarPorEstado() {
    char estado[100];
    printf("Informe o estado desejado:");
    scanf(" %[^\n]", estado);

    printf("Tarefas com estado %s:\n", estado);

    for (int i = 0; i < lt.qtd; i++) {
        if (strcmp(lt.tarefas[i].estado, estado) == 0) {
            printf("Categoria: %s\n", lt.tarefas[i].categoria);
            printf("Descrição: %s\n\n", lt.tarefas[i].descricao);
        }
    }
}
void filtrarPorCategoria() {
    char categoria[100];
    printf("Informe a categoria desejada: ");
    scanf(" %[^\n]", categoria);

    printf("Tarefas com categoria %s e ordenadas por prioridade:\n", categoria);

    // Ordenar tarefas por prioridade

    for (int i = 0; i < lt.qtd; i++) {
        if (strcmp(lt.tarefas[i].categoria, categoria) == 0) {
            printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
            printf("Descrição: %s\n\n", lt.tarefas[i].descricao);
        }
    }
}
void filtrarPorPrioridadeECategoria() {
    int prioridade;
    char categoria[100];

    printf("Informe a prioridade desejada (0-10): ");
    scanf("%d", &prioridade);

    printf("Informe a categoria desejada: ");
    scanf(" %[^\n]", categoria);

    printf("Tarefas com prioridade %d e categoria %s:\n", prioridade, categoria);

    for (int i = 0; i < lt.qtd; i++) {
        if (lt.tarefas[i].prioridade == prioridade && strcmp(lt.tarefas[i].categoria, categoria) == 0) {
            printf("Descrição: %s\n\n", lt.tarefas[i].descricao);
        }
    }
}


void exportarPorCategoria() {
    char categoria[100];
    printf("Informe a categoria desejada: ");
    scanf(" %[^\n]", categoria);

    char arquivo[100];
    sprintf(arquivo, "tarefas_categoria_%s.txt", categoria);

    FILE *file = fopen(arquivo, "w");
    if (file == NULL) {
        perror("Erro ao criar o arquivo");
        return;
    }

    // Ordenar tarefas por prioridade
  
    for (int i = 0; i < lt.qtd; i++) {
        if (strcmp(lt.tarefas[i].categoria, categoria) == 0) {
            fprintf(file, "%d, %s, %s, %s\n", lt.tarefas[i].prioridade, lt.tarefas[i].categoria, lt.tarefas[i].estado, lt.tarefas[i].descricao);
        }
    }

    fclose(file);
    printf("Tarefas exportadas com sucesso para %s!\n", arquivo);
}
void exportarPorPrioridadeECategoria() {
    int prioridade;
    char categoria[100];

    printf("Informe a prioridade desejada (0-10): ");
    scanf("%d", &prioridade);

    printf("Informe a categoria desejada: ");
    scanf(" %[^\n]", categoria);

    char arquivo[100];
    sprintf(arquivo, "tarefas_prioridade_%d_categoria_%s.txt", prioridade, categoria);

    FILE *file = fopen(arquivo, "w");
    if (file == NULL) {
        perror("Erro ao criar o arquivo");
        return;
    }

    for (int i = 0; i < lt.qtd; i++) {
        if (lt.tarefas[i].prioridade == prioridade && strcmp(lt.tarefas[i].categoria, categoria) == 0) {
            fprintf(file, "%d, %s, %s, %s\n", lt.tarefas[i].prioridade, lt.tarefas[i].categoria, lt.tarefas[i].estado, lt.tarefas[i].descricao);
        }
    }

    fclose(file);
    printf("Tarefas exportadas com sucesso para %s!\n", arquivo);
}

void printexportar(){

  printf("7. Por Categoria \n");
  printf("8. Por Prioridade\n");
  printf("9. Por Categoria e Prioridade\n");
  printf("Qual opcao voce deseja exportar");
}
void exportar(){
  int opcaoo;
  printexportar();
  scanf("%d", &opcaoo);
  if (opcaoo == 7) { exportarPorCategoria();}

  if (opcaoo == 8) {exportarPorPrioridade();}
  if (opcaoo == 9) {exportarPorPrioridadeECategoria();}       
}






