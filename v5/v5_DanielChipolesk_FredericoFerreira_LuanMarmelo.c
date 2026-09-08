/*
v5

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

typedef struct
{
    char nome[MAX_CARACTERES_NOME];
    float notas[QTD_PREF];
} Pessoa;

int menu();
float validaNota();
int buscarPeloNome(int cadastrado, Pessoa pessoas[]);
Pessoa* cadastroPessoas(int cadastrado, Pessoa *pessoas, int *novoTotal, char categ[QTD_PREF][20]);
void exibirPessoas(int cadastrado, Pessoa pessoas[], char categ[QTD_PREF][20]);
float distanciaEuclidianaAB(Pessoa *pessoaA, Pessoa *pessoaB);
void comparaDuasPessoas(int cadastrado, Pessoa pessoas[]);
int acharMaisSemelhante(int cadastrado, Pessoa pessoas[]);
void exibirRankingAfinidade(int cadastrado, Pessoa pessoas[]);
void analiseDetalPref(int cadastrado, Pessoa pessoas[], char categ[QTD_PREF][20]);

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

    Pessoa *pessoas = NULL;

    int opcaoMenu;
    int cadastrado = 0;

    do
    {
        opcaoMenu = menu();

        switch (opcaoMenu)
        {
            case 1:
                pessoas = cadastroPessoas(cadastrado, pessoas, &cadastrado, categ);
                break;

            case 2:
                if (cadastrado == 0)
                {
                    printf("\nNenhuma pessoa cadastrada.\n");
                }
                else
                {
                    exibirPessoas(cadastrado, pessoas, categ);
                }
                break;

            case 3:
                if (cadastrado == 0)
                {
                    printf("\nNenhuma pessoa cadastrada.\n");
                }
                else
                {
                    int pessoa = buscarPeloNome(cadastrado, pessoas);

                    if (pessoa == -1)
                    {
                        printf("\nPessoa nao encontrada.\n");
                    }
                    else
                    {
                        printf("\nPessoa encontrada: %s\n", pessoas[pessoa].nome);
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
                    comparaDuasPessoas(cadastrado, pessoas);
                }
                break;

            case 5:
                if (cadastrado < 2)
                {
                    printf("\nE necessario ter pelo menos duas pessoas cadastradas.\n");
                }
                else
                {
                    int pessoa = acharMaisSemelhante(cadastrado, pessoas);

                    if (pessoa != -1)
                    {
                        printf("\nPessoa mais semelhante: %s\n", pessoas[pessoa].nome);
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
                    exibirRankingAfinidade(cadastrado, pessoas);
                }
                break;

            case 7:
                if (cadastrado < 2)
                {
                    printf("\nE necessario ter pelo menos duas pessoas cadastradas.\n");
                }
                else
                {
                    analiseDetalPref(cadastrado, pessoas, categ);
                }
                break;

            case 0:
                printf("\nPrograma encerrado.\n");
                break;
        }

    } while (opcaoMenu != 0);

    free(pessoas);

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

Pessoa *cadastroPessoas(int cadastrado, Pessoa *pessoas, int *novoTotal, char categ[QTD_PREF][20])
{
    int quantidade;
    int i;
    int j;
    Pessoa *novoPessoas;

    printf("\nQuantas pessoas deseja cadastrar? ");
    scanf("%d", &quantidade);

    while (quantidade < 1)
    {
        printf("Quantidade invalida. Digite uma quantidade maior que zero: ");
        scanf("%d", &quantidade);
    }

    *novoTotal = cadastrado + quantidade;

    if (pessoas == NULL)
    {
        novoPessoas = malloc(*novoTotal * sizeof(Pessoa));
    }
    else
    {
        novoPessoas = realloc(pessoas, *novoTotal * sizeof(Pessoa));
    }

    if (novoPessoas == NULL)
    {
        printf("\nErro ao alocar memoria para as pessoas.\n");
        *novoTotal = cadastrado;
        return pessoas;
    }

    pessoas = novoPessoas;

    for (i = cadastrado; i < *novoTotal; i++)
    {
        printf("\nPessoa %d\n", i + 1);
        printf("Nome: ");
        scanf(" %49s", pessoas[i].nome);

        for (j = 0; j < QTD_PREF; j++)
        {
            printf("Nota para %s (0 a 10): ", categ[j]);
            pessoas[i].notas[j] = validaNota();
        }
    }

    return pessoas;
}

void exibirPessoas(int cadastrado,
                   Pessoa pessoas[],
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
        printf("%-15s", pessoas[i].nome);

        for (j = 0; j < QTD_PREF; j++)
        {
            printf("%-13.1f", pessoas[i].notas[j]);
        }

        printf("\n");
    }
}

int buscarPeloNome(int cadastrado,
                   Pessoa pessoas[])
{
    char nomeProcurado[MAX_CARACTERES_NOME];
    int i;

    printf("\nDigite o nome da pessoa: ");
    scanf(" %49s", nomeProcurado);

    for (i = 0; i < cadastrado; i++)
    {
        if (strcasecmp(pessoas[i].nome, nomeProcurado) == 0)
        {
            return i;
        }
    }

    return -1;
}

float distanciaEuclidianaAB(Pessoa *pessoaA, Pessoa *pessoaB)
{
    float soma = 0;
    int i;

    for (i = 0; i < QTD_PREF; i++)
    {
        soma += pow(pessoaA->notas[i] - pessoaB->notas[i], 2);
    }

    return sqrt(soma);
}

void comparaDuasPessoas(int cadastrado,
                         Pessoa pessoas[])
{
    int pessoaA;
    int pessoaB;
    float distancia;

    printf("\n--- Primeira pessoa ---\n");
    pessoaA = buscarPeloNome(cadastrado, pessoas);

    if (pessoaA == -1)
    {
        printf("\nPessoa nao encontrada.\n");
        return;
    }

    printf("\n--- Segunda pessoa ---\n");
    pessoaB = buscarPeloNome(cadastrado, pessoas);

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

    distancia = distanciaEuclidianaAB(&pessoas[pessoaA], &pessoas[pessoaB]);

    printf("\nDistancia entre %s e %s: %.2f\n",
           pessoas[pessoaA].nome,
           pessoas[pessoaB].nome,
           distancia);
}

int acharMaisSemelhante(int cadastrado,
                        Pessoa pessoas[])
{
    int pessoaOrigem;
    int i;
    int pessoaMaisProxima = -1;
    float distancia;
    float menorDistancia = 0;

    pessoaOrigem = buscarPeloNome(cadastrado, pessoas);

    if (pessoaOrigem == -1)
    {
        printf("\nPessoa nao encontrada.\n");
        return -1;
    }

    for (i = 0; i < cadastrado; i++)
    {
        if (i != pessoaOrigem)
        {
            distancia = distanciaEuclidianaAB(&pessoas[pessoaOrigem], &pessoas[i]);

            if (pessoaMaisProxima == -1 || distancia < menorDistancia)
            {
                menorDistancia = distancia;
                pessoaMaisProxima = i;
            }
        }
    }

    printf("\nPessoa de referencia: %s\n", pessoas[pessoaOrigem].nome);
    printf("Pessoa mais semelhante: %s\n", pessoas[pessoaMaisProxima].nome);
    printf("Distancia: %.2f\n", menorDistancia);

    return pessoaMaisProxima;
}

void exibirRankingAfinidade(int cadastrado, Pessoa pessoas[])
{
    int pessoaOrigem;
    int i;
    int j;
    int quantidade = 0;
    Pessoa *tempPessoa;
    Pessoa **ranking;
    float *distancias;
    float tempDistancia;

    pessoaOrigem = buscarPeloNome(cadastrado, pessoas);

    if (pessoaOrigem == -1)
    {
        printf("\nPessoa nao encontrada.\n");
        return;
    }

    ranking = malloc((cadastrado - 1) * sizeof(Pessoa *));
    distancias = malloc((cadastrado - 1) * sizeof(float));

    if (ranking == NULL || distancias == NULL)
    {
        printf("\nErro ao alocar memoria para o ranking.\n");
        free(ranking);
        free(distancias);
        return;
    }

    for (i = 0; i < cadastrado; i++)
    {
        if (i != pessoaOrigem)
        {
            ranking[quantidade] = &pessoas[i];
            distancias[quantidade] = distanciaEuclidianaAB(&pessoas[pessoaOrigem], ranking[quantidade]);
            quantidade++;
        }
    }

    for (i = 0; i < quantidade - 1; i++)
    {
        for (j = i + 1; j < quantidade; j++)
        {
            if (distancias[j] < distancias[i])
            {
                tempDistancia = distancias[i];
                distancias[i] = distancias[j];
                distancias[j] = tempDistancia;

                tempPessoa = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = tempPessoa;
            }
        }
    }

    printf("\n========== RANKING DE AFINIDADE ==========\n");
    printf("Pessoa de referencia: %s\n\n", pessoas[pessoaOrigem].nome);

    for (i = 0; i < quantidade; i++)
    {
        printf("%d - %-15s Distancia: %.2f\n", i + 1, ranking[i]->nome, distancias[i]);
    }

    free(ranking);
    free(distancias);
}

void analiseDetalPref(int cadastrado,
                      Pessoa pessoas[],
                      char categ[QTD_PREF][20])
{
    int pessoaA;
    int pessoaB;
    int i;
    float diferenca;
    float menorDiferenca;

    pessoaA = buscarPeloNome(cadastrado, pessoas);

    if (pessoaA == -1)
    {
        printf("\nPessoa nao encontrada.\n");
        return;
    }

    printf("\n--- Segunda pessoa ---\n");
    pessoaB = buscarPeloNome(cadastrado, pessoas);

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
           pessoas[pessoaA].nome,
           pessoas[pessoaB].nome,
           "Diferenca");

    for (i = 0; i < QTD_PREF; i++)
    {
        diferenca = pessoas[pessoaA].notas[i]
                    - pessoas[pessoaB].notas[i];

        if (diferenca < 0)
        {
            diferenca = diferenca * -1;
        }

        printf("%-15s %-10.1f %-10.1f %-10.1f\n",
               categ[i],
               pessoas[pessoaA].notas[i],
               pessoas[pessoaB].notas[i],
               diferenca);
    }

    printf("\nDistancia Euclidiana: %.2f\n",
           distanciaEuclidianaAB(&pessoas[pessoaA], &pessoas[pessoaB]));

    menorDiferenca = pessoas[pessoaA].notas[0]
                     - pessoas[pessoaB].notas[0];

    if (menorDiferenca < 0)
    {
        menorDiferenca = menorDiferenca * -1;
    }

    for (i = 1; i < QTD_PREF; i++)
    {
        diferenca = pessoas[pessoaA].notas[i]
                    - pessoas[pessoaB].notas[i];

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
        diferenca = pessoas[pessoaA].notas[i]
                    - pessoas[pessoaB].notas[i];

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

