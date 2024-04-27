#include <stdio.h> 

#include "funcoes.h" 

int main() { // Função principal do programa.
    int opcao; // Declaração da variável para armazenar a opção escolhida pelo usuário.

    do { // Loop para exibir o menu e executar as opções até que o usuário escolha sair.
        printf("\nSelecione uma opção:\n"); // Exibe o menu de opções para o usuário.
        printf("1. Adicionar contato\n"); // Opção para adicionar um novo contato.
        printf("2. Listar contatos\n"); // Opção para listar todos os contatos.
        printf("3. Deletar contato\n"); // Opção para deletar um contato existente.
        printf("4. Salvar agenda\n"); // Opção para salvar a lista de contatos em um arquivo.
        printf("5. Carregar agenda\n"); // Opção para carregar a lista de contatos de um arquivo.
        printf("0. Sair\n"); // Opção para sair do programa.
        printf("Opção: "); // Solicita ao usuário que escolha uma opção.
        scanf("%d", &opcao); // Lê a opção escolhida pelo usuário e armazena na variável 'opcao'.

        switch (opcao) { // Inicia um switch para executar a função correspondente à opção escolhida.
            case 1: // Caso a opção escolhida seja 1 (Adicionar contato).
                adicionarContato(); // Chama a função para adicionar um novo contato.
                break; // Sai do switch.
            case 2: // Caso a opção escolhida seja 2 (Listar contatos).
                listarContatos(); // Chama a função para listar todos os contatos.
                break; // Sai do switch.
            case 3: // Caso a opção escolhida seja 3 (Deletar contato).
                deletarContato(); // Chama a função para deletar um contato existente.
                break; // Sai do switch.
            case 4: // Caso a opção escolhida seja 4 (Salvar agenda).
                salvarAgenda(); // Chama a função para salvar a lista de contatos em um arquivo.
                break; // Sai do switch.
            case 5: // Caso a opção escolhida seja 5 (Carregar agenda).
                carregarAgenda(); // Chama a função para carregar a lista de contatos de um arquivo.
                break; // Sai do switch.
            case 0: // Caso a opção escolhida seja 0 (Sair).
                printf("Saindo...\n"); // Exibe uma mensagem informando que o programa está saindo.
                break; // Sai do switch.
            default: // Caso a opção escolhida não corresponda a nenhuma das opções anteriores.
                printf("Opção inválida!\n"); // Informa ao usuário que a opção escolhida é inválida.
        }
    } while (opcao != 0); // Repete o loop enquanto a opção escolhida pelo usuário for diferente de 0 (Sair).

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso.
}
