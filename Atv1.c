#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura do produto
typedef struct{
    int codigo;
    char descricao[50];
    int quantidade;
    float valor;
} Produto;

// Definindo a estrutura da lista de estoque
typedef struct{
    Produto *produtos;
    int tamanho;
} Estoque;

// Funcao para inicializar o estoque
void inicializarEstoque(Estoque *estoque){
    estoque->produtos = NULL;
    estoque->tamanho = 0;
}

// Funcao para adicionar um novo produto ao estoque
void adicionarProduto(Estoque *estoque){
    Produto novoProduto;

    printf("Informe o codigo do produto:\n");
    scanf("%d", &novoProduto.codigo);
    printf("Informe a descricao do produto: ");
    scanf(" %[^\n]", novoProduto.descricao);
    printf("Informe a quantidade do produto: ");
    scanf("%d", &novoProduto.quantidade);
    printf("Informe o valor do produto: ");
    scanf("%f", &novoProduto.valor);

    estoque->tamanho++;
    estoque->produtos = realloc(estoque->produtos, estoque->tamanho * sizeof(Produto));
    estoque->produtos[estoque->tamanho - 1] = novoProduto;

    printf("Produto cadastrado com sucesso!\n");
}

// Funcao para imprimir o relatório de produtos
void imprimirRelatorio(Estoque *estoque){
    printf("Relatorio de Produtos:\n");
    for (int i = 0; i < estoque->tamanho; i++) {
        printf("Codigo: %d\n", estoque->produtos[i].codigo);
        printf("Descricao: %s\n", estoque->produtos[i].descricao);
        printf("Quantidade: %d\n", estoque->produtos[i].quantidade);
        printf("Valor: R$%.2f\n", estoque->produtos[i].valor);
        printf("\n\n");
    }
}

// Funcao para pesquisar um produto pelo codigo
void pesquisarProduto(Estoque *estoque){
    int codigo;
    printf("Informe o codigo do produto a ser pesquisado: ");
    scanf("%d", &codigo);

    for (int i = 0; i < estoque->tamanho; i++){
        if (estoque->produtos[i].codigo == codigo){
            printf("Produto encontrado:\n");
            printf("Codigo: %d\n", estoque->produtos[i].codigo);
            printf("Descricao: %s\n", estoque->produtos[i].descricao);
            printf("Quantidade: %d\n", estoque->produtos[i].quantidade);
            printf("Valor: R$%.2f\n", estoque->produtos[i].valor);
            return;
        }
    }

    printf("Produto nao encontrado.\n");
}

// Funcao para remover um produto do estoque
void removerProduto(Estoque *estoque){
    int codigo;
    printf("Informe o codigo do produto a ser removido: ");
    scanf("%d", &codigo);

    for (int i = 0; i < estoque->tamanho; i++){
        if (estoque->produtos[i].codigo == codigo){
            // Remove o produto da lista
            for (int j = i; j < estoque->tamanho - 1; j++){
                estoque->produtos[j] = estoque->produtos[j + 1];
            }
            estoque->tamanho--;
            estoque->produtos = realloc(estoque->produtos, estoque->tamanho * sizeof(Produto));
            printf("Produto removido com sucesso!\n");
            return;
        }
    }

    printf("Produto nao encontrado.\n");
}

// Funcao para liberar a memória alocada para o estoque
void liberarEstoque(Estoque *estoque){
    free(estoque->produtos);
    estoque->tamanho = 0;
}

// Funcao principal (menu)
int main(){
    Estoque estoque;
    inicializarEstoque(&estoque);

    int opcao;

    do{
        printf("\nMenu:\n");
        printf("1. Adicionar Produto.\n");
        printf("2. Imprimir Relatorio.\n");
        printf("3. Pesquisar Produto.\n");
        printf("4. Remover Produto.\n");
        printf("0. Sair.\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                adicionarProduto(&estoque);
                break;
            case 2:
                imprimirRelatorio(&estoque);
                break;
            case 3:
                pesquisarProduto(&estoque);
                break;
            case 4:
                removerProduto(&estoque);
                break;
            case 0:
                printf("Saindo do programa. Ate mais!\n");
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
    liberarEstoque(&estoque);
    return 0;
}