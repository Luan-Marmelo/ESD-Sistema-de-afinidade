#include <stdio.h>

void menu(){
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
}





int main()
{
    menu();

    return 0;
}