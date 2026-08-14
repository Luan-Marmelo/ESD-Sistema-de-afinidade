#include <stdio.h>
#define MAX_PESSOAS 5

int menu(){
    int opcao;
    
    printf("========================================\n");
    printf("-------- SISTEMA DE AFINIDADES --------\n");
    printf("========================================\n");
    printf("1 - Cadastrar pessoas\n");
    printf("2 - Exibir pessoas e preferências\n");
    printf("3 - Buscar pessoa pelo nome\n");
    printf("4 - Comparar duas pessoas\n");
    printf("5 - Encontrar pessoa mais semelhante\n");
    printf("6 - Exibir ranking de afinidade\n");
    printf("7 - Analisar preferência de duas pessoas\n");
    printf("0 - Encerrar\n");
    scanf("%d", &opcao);
    
    while(opcao > 7 || opcao < 0){
        printf("Opção inválida! Tente novamente.\n");
        scanf("%d", &opcao);
    }

    return opcao;
}

void cadastroPessoas(char nome[MAX_PESSOAS][50], float notas[MAX_PESSOAS][6], char categ[6][20]){
    int i, j;
    for (i=0; i< MAX_PESSOAS; i++){
        printf("Digite o nome da pessoa %d: \n", i+1);
        scanf(" %s", nome[i]);
        for (j=0; j<6; j++){
            printf("Digite a nota para %s; \n", categ[j] );
            scanf(" %f", &notas[i][j]);
            if(notas[i][j] < 0 || notas[i][j] > 10){
                printf("Nota inválida. Digite novamente: \n");
                j--;
            }
        }
    }
}

void exibirPessoas(char nome[MAX_PESSOAS][50], float notas[MAX_PESSOAS][6], char categ[6][20]){
    int i, j;
    printf("===================================================================\n");
    printf("%-12s %6.3s %6.3s %6.3s %6.3s %6.3s %6.3s\n", "NOME", categ[0], categ[1], categ[2], categ[3], categ[4], categ[5]);
    printf("===================================================================\n");
    for(i=0; i<MAX_PESSOAS; i++){
        printf("%-15s ", nome[i]);
        for(j=0; j<6; j++){
            printf("%-6.1f ", notas[i][j]);
        }
        printf("\n");
    }
    printf("===================================================================\n");
}



int main()
{
    char categ[6][20] = {"Musica", "Cinema", "Jogos", "Esportes", "Leitura", "Programação"};
    char nome[MAX_PESSOAS][50] = {};
    float notas[MAX_PESSOAS][6];
    int opcaoMenu;

    opcaoMenu = menu();
    while(opcaoMenu != 0){
        switch(opcaoMenu){
            case 1:
                cadastroPessoas(nome, notas, categ);
                break;
            case 2:
                exibirPessoas(nome, notas, categ);
                break;
            case 3:
                // Função buscar pessoa pelo nome
                break;
            case 4:
                // Função comparar duas pessoas
                break;
            case 5:
                // Função encontrar pessoa mais semelhante
                break;
            case 6:
                // Função exibir ranking de afinidade
                break;
            case 7:
                //função analisar preferência de duas pessoas
                break;
        }
        opcaoMenu = menu();
    }
    
    printf("Encerrando...\n");

    return 0;
}    