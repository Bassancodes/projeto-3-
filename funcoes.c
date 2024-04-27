#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

Contato agenda[MAX_CONTATOS];
int num_contatos = 0;

void adicionarContato() {
    if (num_contatos >= MAX_CONTATOS) {
        printf("A agenda está cheia!\n");
        return;
    }

    Contato novoContato;

    printf("Digite o nome: ");
    scanf("%s", novoContato.nome);
    printf("Digite o sobrenome: ");
    scanf("%s", novoContato.sobrenome);
    printf("Digite o email: ");
    scanf("%s", novoContato.email);
    printf("Digite o telefone: ");
    scanf("%s", novoContato.telefone);

    agenda[num_contatos++] = novoContato;
    printf("Contato adicionado com sucesso!\n");
}

void listarContatos() {
    printf("Lista de contatos:\n");
    for (int i = 0; i < num_contatos; i++) {
        printf("%d: %s %s - %s, %s\n", i + 1, agenda[i].nome, agenda[i].sobrenome, agenda[i].email, agenda[i].telefone);
    }
}

void deletarContato() {
    char telefone[15];
    printf("Digite o telefone do contato que deseja deletar: ");
    scanf("%s", telefone);

    for (int i = 0; i < num_contatos; i++) {
        if (strcmp(agenda[i].telefone, telefone) == 0) {
            for (int j = i; j < num_contatos - 1; j++) {
                agenda[j] = agenda[j + 1];
            }
            num_contatos--;
            printf("Contato deletado com sucesso!\n");
            return;
        }
    }

    printf("Contato não encontrado!\n");
}

void salvarAgenda() {
    FILE *arquivo = fopen("agenda.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fwrite(&num_contatos, sizeof(int), 1, arquivo);
    fwrite(agenda, sizeof(Contato), num_contatos, arquivo);

    fclose(arquivo);
    printf("Agenda salva com sucesso!\n");
}

void carregarAgenda() {
    FILE *arquivo = fopen("agenda.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de agenda não encontrado!\n");
        return;
    }

    fread(&num_contatos, sizeof(int), 1, arquivo);
    fread(agenda, sizeof(Contato), num_contatos, arquivo);

    fclose(arquivo);
    printf("Agenda carregada com sucesso!\n");
}
