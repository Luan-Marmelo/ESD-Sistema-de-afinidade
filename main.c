/* 
v1 
Daniel Chipolesk 
Frederico Ferreira
Luan Marmelo
*/
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <float.h>

//CONSTANTES
#define MAX_PESSOAS 5
#define MAX_CARACTERES_NOME 25
#define QTD_PREF 6

//CABEÇALHOS DAS FUNÇÕES
int menu();
int buscarPeloNome(char nomes[MAX_PESSOAS][MAX_CARACTERES_NOME]);
void cadastroPessoas(char nome[MAX_PESSOAS][MAX_CARACTERES_NOME], float notas[MAX_PESSOAS][QTD_PREF], char categ[QTD_PREF][20]);
void exibirPessoas(char nome[MAX_PESSOAS][MAX_CARACTERES_NOME], float notas[MAX_PESSOAS][QTD_PREF], char categ[QTD_PREF][20]);
void analiseDetalPref(char nome[MAX_PESSOAS][MAX_CARACTERES_NOME], float notas[MAX_PESSOAS][QTD_PREF], char categ[QTD_PREF][20]);

float distanciaEuclidianaAB(int pessoaA, int pessoaB, float notas[MAX_PESSOAS][QTD_PREF]);
void comparaDuasPessoas(char nome[MAX_PESSOAS][MAX_CARACTERES_NOME], float notas[MAX_PESSOAS][QTD_PREF]);
void calcularMatrizDistancias(char nome[MAX_PESSOAS][MAX_CARACTERES_NOME], float notas[MAX_PESSOAS][QTD_PREF], float matrizDistancias[MAX_PESSOAS][MAX_PESSOAS]);
void acharMaisSemelhantes(char nome[MAX_PESSOAS][MAX_CARACTERES_NOME], float notas[MAX_PESSOAS][QTD_PREF], float matrizDistancias[MAX_PESSOAS][MAX_PESSOAS]);

int main()
{
    char categ[QTD_PREF][20] = {"Musica", "Cinema", "Jogos", "Esportes", "Leitura", "Programacao"};

    char nome[MAX_PESSOAS][MAX_CARACTERES_NOME] = {"Ana", "Bruno", "Carla", "Diego", "Eduardo"};

    float notas[MAX_PESSOAS][QTD_PREF] = {
        {8.5, 7.0, 9.0, 6.5, 8.0, 7.5},
        {6.0, 8.5, 7.0, 9.0, 6.5, 8.0},
        {9.0, 6.5, 8.0, 7.5, 8.5, 7.0},
        {7.5, 8.0, 6.5, 9.0, 7.0, 8.5},
        {8.0, 7.5, 9.0, 6.5, 8.5, 7.0}
    };

    float matrizDistancias[MAX_PESSOAS][MAX_PESSOAS];

    int opcaoMenu;

    do{
        opcaoMenu = menu();
        switch(opcaoMenu){
            case 1:
                cadastroPessoas(nome, notas, categ);
                break;
            case 2:
                exibirPessoas(nome, notas, categ);
                break;
            case 3:
                printf("\n %d\n", buscarPeloNome(nome));
                break;
            case 4:
                comparaDuasPessoas(nome, notas);
                break;
            case 5:
                acharMaisSemelhantes(nome, notas, matrizDistancias);
                break;
            case 6:
                // Função exibir ranking de afinidade
                break;
            case 7:
                analiseDetalPref(nome, notas, categ);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
        }
    } while(opcaoMenu != 0);
    
    return 0;
}

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

int buscarPeloNome(char nomes[MAX_PESSOAS][MAX_CARACTERES_NOME]){
    char nomeProcurado[MAX_CARACTERES_NOME];
    printf("\nDIGITE O NOME QUE DESEJA BUSCAR: ");
    scanf(" %s", nomeProcurado);
    
    for(int i = 0; i<MAX_PESSOAS; i++){
        if(strcasecmp(nomeProcurado, nomes[i]) == 0){
            printf("\nNOME: %s - ENCONTRADO COM SUCESSO!\n", nomeProcurado);
            return i;
        }
    }    
    
    printf("\nNOME: %s -  NÃO ENCONTRADO!\n", nomeProcurado);
    return -1;
}

void cadastroPessoas(char nome[MAX_PESSOAS][MAX_CARACTERES_NOME], float notas[MAX_PESSOAS][QTD_PREF], char categ[QTD_PREF][20]){
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
    printf("Pressione ENTER para retornar ao menu.\n");
    while(getchar() != '\n');
    getchar();
}

void exibirPessoas(char nome[MAX_PESSOAS][MAX_CARACTERES_NOME], float notas[MAX_PESSOAS][QTD_PREF], char categ[QTD_PREF][20]){
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
    printf("Pressione ENTER para retornar ao menu.\n");
    while(getchar() != '\n');
    getchar();
}

float distanciaEuclidianaAB(int pessoaA, int pessoaB, float notas[MAX_PESSOAS][QTD_PREF]) {
    
    float somaAB = 0;
    
    for (int i = 0; i < QTD_PREF; i++)
    {
        somaAB += pow(notas[pessoaA][i] - notas[pessoaB][i], 2);
    }
   return sqrt(somaAB);
}

void comparaDuasPessoas(char nome[MAX_PESSOAS][MAX_CARACTERES_NOME], float notas[MAX_PESSOAS][QTD_PREF]){
    
    int pessoaA;
    int pessoaB;
    float distanciaAB;
    
    pessoaA = buscarPeloNome(nome);
    pessoaB = buscarPeloNome(nome);
    
    distanciaAB = distanciaEuclidianaAB(pessoaA, pessoaB, notas);
    
    printf("\n\nA distância entre %s e %s é: %.2f\n\n\n",
            nome[pessoaA],
            nome[pessoaB],
            distanciaAB);
}

void calcularMatrizDistancias(
                    char nome[MAX_PESSOAS][MAX_CARACTERES_NOME],
                    float notas[MAX_PESSOAS][QTD_PREF],
                    float matrizDistancias[MAX_PESSOAS][MAX_PESSOAS]) {

    for (int i = 0; i < MAX_PESSOAS; i++)
    {
        for (int j = 0; j < MAX_PESSOAS; j++)
        {
            matrizDistancias[i][j] = distanciaEuclidianaAB(i, j, notas);
        }
    }
    
    printf("\n\n     MATRIZ DE DISTANCIAS EUCLIDIANAS\n\n");
    
    printf("%-12s", "");
    
    for (int j = 0; j < MAX_PESSOAS; j++)
    {
        printf("%12s", nome[j]);
    }
    
    printf("\n");
    
    for (int i = 0; i < MAX_PESSOAS; i++)
    {
        printf("%-12s", nome[i]);
        
        for (int j = 0; j < MAX_PESSOAS; j++)
        {
            printf("%12.2f", matrizDistancias[i][j]);
        }
        
        printf("\n"); 
    }
}

void acharMaisSemelhantes(
        char nome[MAX_PESSOAS][MAX_CARACTERES_NOME],
        float notas[MAX_PESSOAS][QTD_PREF],
        float matrizDistancias[MAX_PESSOAS][MAX_PESSOAS])
{
    calcularMatrizDistancias(nome, notas, matrizDistancias);
    
    float menorDistancia = FLT_MAX;
    
    int pessoaA = 0;
    int pessoaB = 0;
    
    for (int i = 0; i < MAX_PESSOAS; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (menorDistancia >= matrizDistancias[i][j])
            {
                menorDistancia = matrizDistancias[i][j];
                
                pessoaA = i;
                pessoaB = j;
            }
        }
    }
    
    printf("\n\nPESSOAS MAIS SEMELHANTES SÃO:\n");
    printf("%s e %s", nome[pessoaA], nome[pessoaB]);
    printf("\nDistãncia: %.2f\n\n", menorDistancia);
}

void analiseDetalPref(char nome[MAX_PESSOAS][MAX_CARACTERES_NOME], float notas[MAX_PESSOAS][QTD_PREF], char categ[QTD_PREF][20]){
    int i, j, p1, p2;
    float vDiferenca[6];

    printf("===================================================================\n");
    printf("ANALISE DETALHADA DE PREFERÊNCIAS\n");
    printf("===================================================================\n");
    printf("\n");
    printf("Digite o número das duas pessoas que deseja analisar (1 a 5): \n");
    scanf("%d %d", &p1, &p2);

    printf("===================================================================\n");
    printf("Analise detalhada de preferências entre %s e %s\n", nome[p1-1], nome[p2-1]);
    printf("===================================================================\n");
    printf("\n");
    printf("%-12s %-12s %-12s %-12s\n", "Preferencia", nome[p1-1], nome[p2-1], "Diferença");
    printf("-------------------------------------------------------------------\n");

    for(i=0; i<6; i++){
        if(notas[p1-1][i] - notas[p2-1][i] < 0){
            vDiferenca[i] = (notas[p1-1][i] - notas[p2-1][i]) * -1;
        } else {
            vDiferenca[i] = notas[p1-1][i] - notas[p2-1][i];
        }
        

        printf("%-12s %-12.1f %-12.1f %-12.1f\n", categ[i], notas[p1-1][i], notas[p2-1][i], vDiferenca[i]);
    }

    printf("--------------------------------------------------------------------\n");
    printf("\n");
    //Necessita-se implementar a função distanciaEuclidiana para calcular a distância entre as duas pessoas
    //printf("Distancia euclidiana entre %s e %s: %.2f\n", nome[p1-1], nome[p2-1], distanciaEuclidiana(notas, p1-1, p2-1));

    printf("Preferencias mais semelhantes:\n");

    
    float valorMaisSemelhante = vDiferenca[0];

    for(i=0; i<6; i++){
        if(vDiferenca[i] < valorMaisSemelhante){
            valorMaisSemelhante = vDiferenca[i];
        } 
    };

    for(i=0; i<6; i++){
        if(vDiferenca[i] == valorMaisSemelhante){
            printf("%s\n", categ[i]);
        }
    }
    printf("Pressione ENTER para retornar ao menu.\n");
    while(getchar() != '\n');
    getchar();

}




    
