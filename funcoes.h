#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_CONTATOS 255 // Define o tamanho máximo da agenda de contatos.

typedef struct { // Define a estrutura de dados para armazenar informações de contato.
    char nome[50];
    char sobrenome[50];
    char email[100];
    char telefone[15];
} Contato;

extern Contato agenda[MAX_CONTATOS]; // Declara um array externo de contatos com tamanho MAX_CONTATOS.
extern int num_contatos; // Declara uma variável externa para armazenar o número de contatos atualmente na agenda.

void adicionarContato(); // Protótipo da função para adicionar um novo contato.
void listarContatos(); // Protótipo da função para listar todos os contatos.
void deletarContato(); // Protótipo da função para deletar um contato existente.
void salvarAgenda(); // Protótipo da função para salvar a lista de contatos em um arquivo.
void carregarAgenda(); // Protótipo da função para carregar a lista de contatos de um arquivo.

#endif
