/* 
v2 
Daniel Chipolesk 
Frederico Ferreira
Luan Marmelo
*/
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

//CONSTANTES
#define MAX_CARACTERES_NOME 25
#define QTD_PREF 6

//CABEÇALHOS DAS FUNÇÕES
int menu(void);

float validaNota(void);

int buscarPeloNome(int cadastrado, char **nomes);

int cadastroPessoas(int cadastrado, char ***nome, float ***notas, char categ[QTD_PREF][20]);

void exibirPessoas(int cadastrado, char **nome, float **notas, char categ[QTD_PREF][20]);

float distanciaEuclidianaAB(int pessoaA, int pessoaB, float **notas);

void comparaDuasPessoas(int cadastrado, char **nome, float **notas);

void analiseDetalPref(int cadastrado, char **nome, float **notas, char categ[QTD_PREF][20]);

float **calcularMatrizDistancias(int cadastrado, char **nome, float **notas);

float obterDistancia(int pessoaA, int pessoaB, float **matrizDistancias);

float acharMaisSemelhante(int cadastrado, char **nome, float **matrizDistancias);

void executarMaisSemelhante(int cadastrado, char **nome, float **notas);

void executarRanking(int cadastrado, char **nome, float **notas);

void exibirRankingAfinidade(int cadastrado, char **nome, float **matrizDistancias);

void liberarMatrizDistancias(float **matrizDistancias, int cadastrado);

int main(void)
{
    char categ[QTD_PREF][20] = {"Musica", "Cinema", "Jogos", "Esportes", "Leitura", "Programacao"};
    
    char **nome = NULL; // o primeiro * string nome e o segundo * para posição dos demais nomes
    float **notas = NULL; // o primeiro * para a posição nome e o segundo para a notas
    
    int opcaoMenu;
    int cadastrado = 0;
    
    do{
        opcaoMenu = menu();
        switch(opcaoMenu){
            case 1:
                cadastrado = cadastroPessoas(cadastrado, &nome, &notas, categ); //& o realloc poderá alterar o endereço dos ponteirso 
                break;
                
            case 2:
                exibirPessoas(cadastrado, nome, notas, categ);
                break;
                
            case 3:
                buscarPeloNome(cadastrado, nome);
                break;
                
            case 4:
                comparaDuasPessoas(cadastrado, nome, notas);
                break;
                
            case 5:
                executarMaisSemelhante(cadastrado, nome, notas);
                break;
                
            case 6:
                executarRanking(cadastrado, nome, notas);
                break;
                
            case 7:
                analiseDetalPref(cadastrado, nome, notas, categ);
                break;
                
            case 0:
                printf("Encerrando o programa...\n");
                break;
        }
    } while(opcaoMenu != 0);

    for (int i = 0; i < cadastrado; i++)
    {
        free(nome[i]);
        free(notas[i]);
    }
    
    free(nome);
    free(notas);
    
    return 0;
}

int menu(void){
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
int buscarPeloNome(int cadastrado, char **nomes){
    char nomeProcurado[MAX_CARACTERES_NOME];
    printf("\nDIGITE O NOME QUE DESEJA BUSCAR: ");
    scanf(" %24s", nomeProcurado);
    
    for(int i = 0; i < cadastrado; i++){
        if(strcasecmp(nomeProcurado, nomes[i]) == 0){
            printf("\nNOME: %s - ENCONTRADO COM SUCESSO!\n", nomeProcurado);
            return i;
        }
    }    
    
    printf("\nNOME: %s -  NÃO ENCONTRADO!\n", nomeProcurado);
    return -1;
}

float validaNota(void){
    float nota;
    scanf(" %f", &nota);

    while(nota < 0 || nota > 10){
        printf("Nota inválida. A nota precisa estar entre 0 e 10. Digite novamente: \n");
        scanf(" %f", &nota);
    }

    return nota;

}

int cadastroPessoas(int cadastrado, char ***nome, float ***notas, char categ[QTD_PREF][20])
{
    int qtdNova;

    printf("Quantas novas pessoas deseja cadastrar? \n");
    scanf(" %d", &qtdNova);

    while(qtdNova < 1){
        printf("Quantidade inválida. Digite um número maior que zero: \n");
        scanf("%d", &qtdNova);
    }

    int novoTotal = cadastrado + qtdNova;
    
    char **tempNome = realloc(*nome, novoTotal * sizeof(char *)); //é utilizada a variável temporárai para evitar sobrescrição caso a realocação falhe.
    
    if (tempNome == NULL) {
        printf("Erro ao alocar memória para os nomes.\n");
        return cadastrado; //retorna a função o mesmo número de pessoas cadastradas sem alterar
    }
    
    *nome = tempNome;
    
    float **tempNotas = realloc(*notas, novoTotal * sizeof(float *));
    
    if (tempNotas == NULL) {
        printf("Erro ao alocar memória para notas.\n");
        return cadastrado;
    }
    
    *notas = tempNotas;
    
    for (int i = cadastrado; i < novoTotal; i++){
        
        (*nome)[i] = malloc(MAX_CARACTERES_NOME * sizeof(char)); //OBS: o primeiro realloc é para o vetor ponteiro nomes
        (*notas)[i] = malloc(QTD_PREF * sizeof(float));
        
        if((*nome)[i] == NULL || (*notas)[i] == NULL) {
            printf("Erro ao alocar memória.\n");
            
            free((*nome)[i]);
            free((*notas)[i]);
            
            for(int j = cadastrado; j < i; j++)
            {
                free((*nome)[j]);
                free((*notas)[j]);
            }
            
            return cadastrado;
        }
        
        printf("Digite o nome da pessoa %d: \n", i + 1);
        scanf(" %24s", (*nome)[i]);
        
        for (int j = 0; j < QTD_PREF; j++){
            printf("Digite a nota para %s: \n", categ[j] );
            (*notas)[i][j] = validaNota();
        }
    }

    printf("\nCadastro realizado com sucesso!\n");

    return novoTotal;
}

float obterDistancia(int pessoaA, int pessoaB, float **matrizDistancias)
{
    if (pessoaA == pessoaB)
    {
        return 0;
    }
    
    if (pessoaA < pessoaB)
    {
        return matrizDistancias[pessoaA][pessoaB - pessoaA - 1];
    } else {
        return matrizDistancias[pessoaB][pessoaA - pessoaB - 1];
    }
}

void exibirPessoas(int cadastrado, char **nome, float **notas, char categ[QTD_PREF][20]){
    int i, j;
    printf("===================================================================\n");
    printf("%-12s %6.3s %6.3s %6.3s %6.3s %6.3s %6.3s\n", "NOME", categ[0], categ[1], categ[2], categ[3], categ[4], categ[5]);
    printf("===================================================================\n");
    for(i = 0; i < cadastrado; i++){
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

float distanciaEuclidianaAB(int pessoaA, int pessoaB, float **notas) {
    
    float somaAB = 0;
    
    for (int i = 0; i < QTD_PREF; i++)
    {
        somaAB += pow(notas[pessoaA][i] - notas[pessoaB][i], 2);
    }
   return sqrt(somaAB);
}

void comparaDuasPessoas(int cadastrado, char **nome, float **notas){
    
    int pessoaA;
    int pessoaB;
    float distanciaAB;
    
    if (cadastrado < 2) {
        printf("\nÉ necessario cadastrar pelo menos duas pessoas.\n");
        return;
    }
    
    pessoaA = buscarPeloNome(cadastrado, nome);
    
    if (pessoaA == -1){
        return;
    }
    
    pessoaB = buscarPeloNome(cadastrado, nome);
    
    if (pessoaB == -1) {
        return;
    }
    
    distanciaAB = distanciaEuclidianaAB(pessoaA, pessoaB, notas);
    
    printf("\n\nA distância entre %s e %s é: %.2f\n\n\n",
            nome[pessoaA],
            nome[pessoaB],
            distanciaAB);
}

float **calcularMatrizDistancias(int cadastrado, char **nome, float **notas)
{
    float **matrizDistancias;
    
    matrizDistancias = malloc(cadastrado * sizeof(float *));
    
    if(matrizDistancias == NULL){
        printf("Erro ao alocar matriz de distâncias.\n");
        return NULL;
    }

    for (int i = 0; i < cadastrado; i++)
    {
        int tamanhoLinha = cadastrado - i - 1;
        
        if(tamanhoLinha > 0)
        {
            matrizDistancias[i] = malloc(tamanhoLinha * sizeof(float));
            
            if (matrizDistancias[i] == NULL)
            {
                printf("Erro ao alocar matriz de distâncias.\n");
                
                for(int j = 0; j < i; j++){
                    free(matrizDistancias[j]);
                }
                
                free(matrizDistancias);
                
                return NULL;
            }
        } else {
            matrizDistancias[i] = NULL;
        }
    }
        
    for (int i = 0; i < cadastrado; i++) // calculator somente os necessarios
        {
            for (int j = i + 1; j < cadastrado; j++)
            {
                matrizDistancias[i][j - i - 1] = distanciaEuclidianaAB(i, j, notas);
            }
        }
    
    printf("\n\n     MATRIZ DE DISTANCIAS EUCLIDIANAS\n\n");
    
    for (int i = 0; i < cadastrado; i++)
    {
        for (int j = i + 1; j < cadastrado; j++)
        {
            printf("%s x %s = %.2f\n", nome[i], nome[j], matrizDistancias[i][j - i - 1]);
        }
    }
    
    return matrizDistancias;
}

float acharMaisSemelhante(int cadastrado, char **nome, float **matrizDistancias)
{
    if (cadastrado < 2)
    {
        printf("É necessario cadastrar pelo menos duas pessoas.\n");
        return -1;
    }
    
    int pessoaOrigem = buscarPeloNome(cadastrado, nome);
    
    if(pessoaOrigem == -1)
    {
        return -1;
    }
    
    float menorDistancia = FLT_MAX;
    int pessoaMaisProxima = -1;
    
    for(int i = 0; i < cadastrado; i++)
    {
        if (i != pessoaOrigem)
        {
            float distancia = obterDistancia(pessoaOrigem, i, matrizDistancias);
            
            if(distancia < menorDistancia)
            {
                menorDistancia = distancia;
                pessoaMaisProxima = i;
            }
        }
    }

    printf("\n\nPESSOA MAIS SEMELHANTE COM %s É: %s\n", nome[pessoaOrigem], nome[pessoaMaisProxima]);
    printf("\nDistância: %.2f\n\n", menorDistancia);
    printf("Pressione ENTER para retornar ao menu.\n");
    while(getchar() != '\n');
    getchar();

    return menorDistancia;
}

void executarMaisSemelhante(int cadastrado, char **nome, float **notas)
{
    if (cadastrado < 2)
    {
        printf("É necessario cadastrar pelo menos duas pessoas.\n");
        return;
    }
    
    float **matrizDistancias = calcularMatrizDistancias(cadastrado, nome, notas);
    
    if (matrizDistancias == NULL)
    {
        return;
    }
    
    acharMaisSemelhante(cadastrado, nome, matrizDistancias);
    
    liberarMatrizDistancias(matrizDistancias, cadastrado);
}

void analiseDetalPref(int cadastrado, char **nome, float **notas, char categ[QTD_PREF][20]){
    int i, p1, p2;
    float vDiferenca[QTD_PREF];

    if (cadastrado < 2) {
        printf("Necessário cadastrar pelo menos duas pessoas para analisar preferências.\n");
        return;
    }

    printf("===================================================================\n");
    printf("ANALISE DETALHADA DE PREFERÊNCIAS\n");
    printf("===================================================================\n");
    printf("\n");
    p1 = buscarPeloNome(cadastrado, nome);
    p2 = buscarPeloNome(cadastrado, nome);
    if (p1 == -1 || p2 == -1) {
        printf("Erro ao buscar pessoas.\n");
        return;
    }
    
    if (p1 == p2)
    {
        printf("Escolha duas pessoas diferentes.\n");
        return;
    }

    printf("===================================================================\n");
    printf("Analise detalhada de preferências entre %s e %s\n", nome[p1], nome[p2]);
    printf("===================================================================\n");
    printf("\n");
    printf("%-12s %-12s %-12s %-12s\n", "Preferencia", nome[p1], nome[p2], "Diferença");
    printf("-------------------------------------------------------------------\n");

    for(i=0; i<QTD_PREF; i++){
        if(notas[p1][i] - notas[p2][i] < 0){
            vDiferenca[i] = (notas[p1][i] - notas[p2][i]) * -1;
        } else {
            vDiferenca[i] = notas[p1][i] - notas[p2][i];
        }
        

        printf("%-12s %-12.1f %-12.1f %-12.1f\n", categ[i], notas[p1][i], notas[p2][i], vDiferenca[i]);
    }

    printf("--------------------------------------------------------------------\n");
    printf("\n");
    
    printf("Distancia euclidiana entre %s e %s: %.2f\n", nome[p1], nome[p2], distanciaEuclidianaAB(p1, p2, notas));

    printf("Preferencias mais semelhantes:\n");

    
    float valorMaisSemelhante = vDiferenca[0];

    for(i=0; i<QTD_PREF; i++){
        if(vDiferenca[i] < valorMaisSemelhante){
            valorMaisSemelhante = vDiferenca[i];
        } 
    };

    for(i=0; i<QTD_PREF; i++){
        if(vDiferenca[i] == valorMaisSemelhante){
            printf("%s\n", categ[i]);
        }
    }
    printf("Pressione ENTER para retornar ao menu.\n");
    while(getchar() != '\n');
    getchar();

}

void liberarMatrizDistancias(float **matrizDistancias, int cadastrado)
{
    if(matrizDistancias == NULL)
    {
        return;
    }
    
    for (int i = 0; i < cadastrado; i++)
    {
        free(matrizDistancias[i]);
    }
    
    free(matrizDistancias);
}

void exibirRankingAfinidade(int cadastrado, char **nome, float **matrizDistancias)
{
    if(cadastrado < 2)
    {
        printf("É necessario cadastrar pelo menos duas pessoas.\n");
        return;
    }
    
    int pessoaOrigem = buscarPeloNome(cadastrado, nome);
    
    if(pessoaOrigem == -1)
    {
        return;
    }
    
    int qtdComparacoes = cadastrado - 1;
    
    float *auxDistancias = malloc(qtdComparacoes * sizeof(float));
    
    int *auxIndices = malloc(qtdComparacoes * sizeof(int));
    
    if(auxDistancias == NULL || auxIndices == NULL)
    {
        printf("Erro ao alocar memória para o ranking.\n");
        
        free(auxDistancias);
        free(auxIndices);
        
        return;
    }
    
    int j = 0;
    
    for(int i = 0; i < cadastrado; i++)
    {
        if(i != pessoaOrigem)
        {
            auxIndices[j] = i;
            
            auxDistancias[j] = obterDistancia(pessoaOrigem, i, matrizDistancias);
            
            j++;
        }
    }
    
    for (int i = 0; i < qtdComparacoes - 1; i++)
    {
        for (int j = i + 1; j < qtdComparacoes; j++)
        {
            if (auxDistancias[i] > auxDistancias[j])
            {
                float tempDistancia = auxDistancias[i];
                auxDistancias[i] = auxDistancias[j];
                auxDistancias[j] = tempDistancia;
                
                int tempIndice = auxIndices[i];
                auxIndices[i] = auxIndices[j];
                auxIndices[j] = tempIndice;
            }
        }
    }
    
    printf("\n=======================================\n");
    printf("PERFIS MAIS PRÓXIMOS DE %s\n", nome[pessoaOrigem]);
    printf("=========================================\n");
    
    for (int i = 0; i < qtdComparacoes; i++)
    {
        printf("%d - %s -------- %.2f\n", i + 1, nome[auxIndices[i]], auxDistancias[i]);
    }
    
    free(auxDistancias);
    free(auxIndices);
    
    printf("\nPressione ENTER para retornar ao menu.\n");
    while(getchar() != '\n');
    getchar();
}

void executarRanking(int cadastrado, char **nome, float **notas)
{
    if (cadastrado < 2)
    {
        printf("É necessario cadastrar pelo menos duas pessoas.\n");
        return;
    }
    
    float **matrizDistancias = calcularMatrizDistancias(cadastrado, nome, notas);
    
    if (matrizDistancias == NULL)
    {
        return;
    }
    
    exibirRankingAfinidade(cadastrado, nome, matrizDistancias);
    
    liberarMatrizDistancias(matrizDistancias, cadastrado);
}
