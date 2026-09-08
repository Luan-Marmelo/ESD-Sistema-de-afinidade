/*
v2

Daniel Chipolesk
Frederico Ferreira
Luan Marmelo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#define MAX_CARACTERES_NOME 50
#define QTD_PREF 6

int menu();
float validaNota();
int buscarPeloNome(int cadastrado, char **nome);
int cadastroPessoas(int cadastrado, char ***nome, float ***notas, char categ[QTD_PREF][20]);
void exibirPessoas(int cadastrado, char **nome, float **notas, char categ[QTD_PREF][20]);
float distanciaEuclidianaAB(int pessoaA, int pessoaB, float **notas);
void comparaDuasPessoas(int cadastrado, char **nome, float **notas);
int acharMaisSemelhante(int cadastrado, char **nome, float **notas);
void exibirRankingAfinidade(int cadastrado, char **nome, float **notas);
void analiseDetalPref(int cadastrado, char **nome, float **notas, char categ[QTD_PREF][20]);

int main()
{
    char categ[QTD_PREF][20] = {
        "Musica",
        "Cinema",
        "Jogos",
        "Esportes",
        "Leitura",
        "Programacao"
    };

    char **nome = NULL;
    float **notas = NULL;

    int opcaoMenu;
    int cadastrado = 0;

    do
    {
        opcaoMenu = menu();

        switch (opcaoMenu)
        {
            case 1:
                cadastrado = cadastroPessoas(cadastrado, &nome, &notas, categ);
                break;

            case 2:
                if (cadastrado == 0)
                {
                    printf("\nNenhuma pessoa cadastrada.\n");
                }
                else
                {
                    exibirPessoas(cadastrado, nome, notas, categ);
                }
                break;

            case 3:
                if (cadastrado == 0)
                {
                    printf("\nNenhuma pessoa cadastrada.\n");
                }
                else
                {
                    int pessoa = buscarPeloNome(cadastrado, nome);

                    if (pessoa == -1)
                    {
                        printf("\nPessoa nao encontrada.\n");
                    }
                    else
                    {
                        printf("\nPessoa encontrada: %s\n", nome[pessoa]);
                    }
                }
                break;

            case 4:
                if (cadastrado < 2)
                {
                    printf("\nE necessario ter pelo menos duas pessoas cadastradas.\n");
                }
                else
                {
                    comparaDuasPessoas(cadastrado, nome, notas);
                }
                break;

            case 5:
                if (cadastrado < 2)
                {
                    printf("\nE necessario ter pelo menos duas pessoas cadastradas.\n");
                }
                else
                {
                    int pessoa = acharMaisSemelhante(cadastrado, nome, notas);

                    if (pessoa != -1)
                    {
                        printf("\nPessoa mais semelhante: %s\n", nome[pessoa]);
                    }
                }
                break;

            case 6:
                if (cadastrado < 2)
                {
                    printf("\nE necessario ter pelo menos duas pessoas cadastradas.\n");
                }
                else
                {
                    exibirRankingAfinidade(cadastrado, nome, notas);
                }
                break;

            case 7:
                if (cadastrado < 2)
                {
                    printf("\nE necessario ter pelo menos duas pessoas cadastradas.\n");
                }
                else
                {
                    analiseDetalPref(cadastrado, nome, notas, categ);
                }
                break;

            case 0:
                printf("\nPrograma encerrado.\n");
                break;
        }

    } while (opcaoMenu != 0);

    free(nome);
    free(notas);

    return 0;
}

int menu()
{
    int opcao;

    do
    {
        printf("\n========== SISTEMA DE RECOMENDACAO ==========\n");
        printf("1 - Cadastrar pessoas\n");
        printf("2 - Exibir pessoas e preferencias\n");
        printf("3 - Buscar pessoa pelo nome\n");
        printf("4 - Comparar duas pessoas\n");
        printf("5 - Encontrar pessoa mais semelhante\n");
        printf("6 - Exibir ranking de afinidade\n");
        printf("7 - Analisar preferencias de duas pessoas\n");
        printf("0 - Encerrar\n");
        printf("=============================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao < 0 || opcao > 7)
        {
            printf("\nOpcao invalida.\n");
        }

    } while (opcao < 0 || opcao > 7);

    return opcao;
}

float validaNota()
{
    float nota;

    scanf("%f", &nota);

    while (nota < 0 || nota > 10)
    {
        printf("Nota invalida. Digite uma nota entre 0 e 10: ");
        scanf("%f", &nota);
    }

    return nota;
}

int cadastroPessoas(int cadastrado,
                    char ***nome,
                    float ***notas,
                    char categ[QTD_PREF][20])
{
    int quantidade;
    int i;
    int j;
    int novaQuantidade;

    char **novoNome;
    float **novasNotas;

    printf("\nQuantas pessoas deseja cadastrar? ");
    scanf("%d", &quantidade);

    while (quantidade < 1)
    {
        printf("Quantidade invalida. Digite uma quantidade maior que zero: ");
        scanf("%d", &quantidade);
    }

    novaQuantidade = cadastrado + quantidade;

    novoNome = realloc(*nome, novaQuantidade * sizeof(*novoNome));

    if (novoNome == NULL)
    {
        printf("\nErro ao aumentar a memoria para os nomes.\n");
        return cadastrado;
    }

    *nome = novoNome;

    if (cadastrado == 0)
    {
        novasNotas = malloc(novaQuantidade * sizeof(float *));
    }
    else
    {
        novasNotas = realloc(*notas, novaQuantidade * sizeof(float *));
    }

    if (novasNotas == NULL)
    {
        printf("\nErro ao aumentar a memoria para as notas.\n");
        return cadastrado;
    }

    *notas = novasNotas;

    for (i = cadastrado; i < novaQuantidade; i++)
    {
        (*nome)[i] = malloc(MAX_CARACTERES_NOME * sizeof(char));

        if ((*nome)[i] == NULL)
        {
            printf("\nErro ao alocar memoria para o nome da pessoa %d.\n", i + 1);

            for (j = cadastrado; j < i; j++)
            {
                free((*nome)[j]);
                (*nome)[j] = NULL;
            }

            return cadastrado;
        }
    }

    for (i = cadastrado; i < novaQuantidade; i++)
    {
        (*notas)[i] = malloc(QTD_PREF * sizeof(float));

        if ((*notas)[i] == NULL)
        {
            printf("\nErro ao alocar memoria para as notas da pessoa %d.\n", i + 1);

            for (j = cadastrado; j < i; j++)
            {
                free((*notas)[j]);
                (*notas)[j] = NULL;
            }

            for (j = cadastrado; j < novaQuantidade; j++)
            {
                free((*nome)[j]);
                (*nome)[j] = NULL;
            }

            return cadastrado;
        }
    }

    for (i = cadastrado; i < novaQuantidade; i++)
    {
        printf("\nPessoa %d\n", i + 1);
        printf("Nome: ");
        scanf(" %49s", (*nome)[i]);

        for (j = 0; j < QTD_PREF; j++)
        {
            printf("Nota para %s (0 a 10): ", categ[j]);
            (*notas)[i][j] = validaNota();
        }
    }

    return novaQuantidade;
}

void exibirPessoas(int cadastrado,
                   char **nome,
                   float **notas,
                   char categ[QTD_PREF][20])
{
    int i;
    int j;

    printf("\n================ PESSOAS ================\n");
    printf("%-15s", "Nome");

    for (j = 0; j < QTD_PREF; j++)
    {
        printf("%-13s", categ[j]);
    }

    printf("\n");

    for (i = 0; i < cadastrado; i++)
    {
        printf("%-15s", nome[i]);

        for (j = 0; j < QTD_PREF; j++)
        {
            printf("%-13.1f", notas[i][j]);
        }

        printf("\n");
    }
}

int buscarPeloNome(int cadastrado,
                   char **nome)
{
    char nomeProcurado[MAX_CARACTERES_NOME];
    int i;

    printf("\nDigite o nome da pessoa: ");
    scanf(" %49s", nomeProcurado);

    for (i = 0; i < cadastrado; i++)
    {
        if (strcasecmp(nome[i], nomeProcurado) == 0)
        {
            return i;
        }
    }

    return -1;
}

float distanciaEuclidianaAB(int pessoaA,
                            int pessoaB,
                            float **notas)
{
    float soma = 0;
    int i;

    for (i = 0; i < QTD_PREF; i++)
    {
        soma += pow(notas[pessoaA][i]
                    - notas[pessoaB][i], 2);
    }

    return sqrt(soma);
}

void comparaDuasPessoas(int cadastrado,
                         char **nome,
                         float **notas)
{
    int pessoaA;
    int pessoaB;
    float distancia;

    printf("\n--- Primeira pessoa ---\n");
    pessoaA = buscarPeloNome(cadastrado, nome);

    if (pessoaA == -1)
    {
        printf("\nPessoa nao encontrada.\n");
        return;
    }

    printf("\n--- Segunda pessoa ---\n");
    pessoaB = buscarPeloNome(cadastrado, nome);

    if (pessoaB == -1)
    {
        printf("\nPessoa nao encontrada.\n");
        return;
    }

    if (pessoaA == pessoaB)
    {
        printf("\nNao e possivel comparar uma pessoa com ela mesma.\n");
        return;
    }

    distancia = distanciaEuclidianaAB(pessoaA, pessoaB, notas);

    printf("\nDistancia entre %s e %s: %.2f\n",
           nome[pessoaA],
           nome[pessoaB],
           distancia);
}

int acharMaisSemelhante(int cadastrado,
                        char **nome,
                        float **notas)
{
    int pessoaOrigem;
    int i;
    int pessoaMaisProxima = -1;
    float distancia;
    float menorDistancia = 0;

    pessoaOrigem = buscarPeloNome(cadastrado, nome);

    if (pessoaOrigem == -1)
    {
        printf("\nPessoa nao encontrada.\n");
        return -1;
    }

    for (i = 0; i < cadastrado; i++)
    {
        if (i != pessoaOrigem)
        {
            distancia = distanciaEuclidianaAB(pessoaOrigem, i, notas);

            if (pessoaMaisProxima == -1 || distancia < menorDistancia)
            {
                menorDistancia = distancia;
                pessoaMaisProxima = i;
            }
        }
    }

    printf("\nPessoa de referencia: %s\n", nome[pessoaOrigem]);
    printf("Pessoa mais semelhante: %s\n", nome[pessoaMaisProxima]);
    printf("Distancia: %.2f\n", menorDistancia);

    return pessoaMaisProxima;
}

void exibirRankingAfinidade(int cadastrado,
                            char **nome,
                            float **notas)
{
    int pessoaOrigem;
    int i;
    int j;
    int temp;
    int quantidade = 0;

    int *auxIndices;
    float *auxDistancias;
    float aux;

    pessoaOrigem = buscarPeloNome(cadastrado, nome);

    if (pessoaOrigem == -1)
    {
        printf("\nPessoa nao encontrada.\n");
        return;
    }

    auxIndices = malloc((cadastrado - 1) * sizeof(int));
    auxDistancias = malloc((cadastrado - 1) * sizeof(float));

    if (auxIndices == NULL || auxDistancias == NULL)
    {
        printf("\nErro ao alocar memoria para o ranking.\n");
        free(auxIndices);
        free(auxDistancias);
        return;
    }

    for (i = 0; i < cadastrado; i++)
    {
        if (i != pessoaOrigem)
        {
            auxIndices[quantidade] = i;
            auxDistancias[quantidade] = distanciaEuclidianaAB(pessoaOrigem, i, notas);
            quantidade++;
        }
    }

    for (i = 0; i < quantidade - 1; i++)
    {
        for (j = i + 1; j < quantidade; j++)
        {
            if (auxDistancias[j] < auxDistancias[i])
            {
                aux = auxDistancias[i];
                auxDistancias[i] = auxDistancias[j];
                auxDistancias[j] = aux;

                temp = auxIndices[i];
                auxIndices[i] = auxIndices[j];
                auxIndices[j] = temp;
            }
        }
    }

    printf("\n========== RANKING DE AFINIDADE ==========\n");
    printf("Pessoa de referencia: %s\n\n", nome[pessoaOrigem]);

    for (i = 0; i < quantidade; i++)
    {
        printf("%d - %-15s Distancia: %.2f\n",
               i + 1,
               nome[auxIndices[i]],
               auxDistancias[i]);
    }

    free(auxIndices);
    free(auxDistancias);
}

void analiseDetalPref(int cadastrado,
                      char **nome,
                      float **notas,
                      char categ[QTD_PREF][20])
{
    int pessoaA;
    int pessoaB;
    int i;
    float diferenca;
    float menorDiferenca;

    pessoaA = buscarPeloNome(cadastrado, nome);

    if (pessoaA == -1)
    {
        printf("\nPessoa nao encontrada.\n");
        return;
    }

    printf("\n--- Segunda pessoa ---\n");
    pessoaB = buscarPeloNome(cadastrado, nome);

    if (pessoaB == -1)
    {
        printf("\nPessoa nao encontrada.\n");
        return;
    }

    if (pessoaA == pessoaB)
    {
        printf("\nNao e possivel analisar uma pessoa com ela mesma.\n");
        return;
    }

    printf("\n===== ANALISE DE PREFERENCIAS =====\n");
    printf("%-15s %-10s %-10s %-10s\n",
           "Preferencia",
           nome[pessoaA],
           nome[pessoaB],
           "Diferenca");

    for (i = 0; i < QTD_PREF; i++)
    {
        diferenca = notas[pessoaA][i]
                    - notas[pessoaB][i];

        if (diferenca < 0)
        {
            diferenca = diferenca * -1;
        }

        printf("%-15s %-10.1f %-10.1f %-10.1f\n",
               categ[i],
               notas[pessoaA][i],
               notas[pessoaB][i],
               diferenca);
    }

    printf("\nDistancia Euclidiana: %.2f\n",
           distanciaEuclidianaAB(pessoaA, pessoaB, notas));

    menorDiferenca = notas[pessoaA][0]
                     - notas[pessoaB][0];

    if (menorDiferenca < 0)
    {
        menorDiferenca = menorDiferenca * -1;
    }

    for (i = 1; i < QTD_PREF; i++)
    {
        diferenca = notas[pessoaA][i]
                    - notas[pessoaB][i];

        if (diferenca < 0)
        {
            diferenca = diferenca * -1;
        }

        if (diferenca < menorDiferenca)
        {
            menorDiferenca = diferenca;
        }
    }

    printf("\nPreferencia(s) com maior afinidade:\n");

    for (i = 0; i < QTD_PREF; i++)
    {
        diferenca = notas[pessoaA][i]
                    - notas[pessoaB][i];

        if (diferenca < 0)
        {
            diferenca = diferenca * -1;
        }

        if (diferenca == menorDiferenca)
        {
            printf("- %s (diferenca: %.1f)\n",
                   categ[i],
                   diferenca);
        }
    }
}
