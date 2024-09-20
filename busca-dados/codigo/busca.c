#include <stdlib.h>
#include <stdio.h>
#include <string.h>  
#include <string.h>
#include "bibliotecas/empresa.h"
#include "bibliotecas/busca.h"
#include "bibliotecas/string_utils.h"  

long obterTamanhoArquivo(FILE *arq)
{
    fseek(arq, 0, SEEK_END);
    long tamanho = ftell(arq);
    fseek(arq, 0, SEEK_SET);
    return tamanho;
}


Empresa *copiarDados(char *cnpj, char *nome, char *nat, char *quali, char *capital, char *porte, char *ente)
{
    Empresa *empresa = (Empresa *)malloc(sizeof(Empresa));
    if (empresa == NULL)
    {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    copiarString(empresa->cnpj, cnpj, CNPJ_TAM);
    copiarString(empresa->nome, nome, NOME_TAM);
    copiarString(empresa->natureza_juridica, nat, NATJURIDICA_TAM);
    copiarString(empresa->qualificacao_responsavel, quali, QUALIFICACAO_TAM);
    copiarString(empresa->capital_social, capital, CAPITAL_TAM);
    copiarString(empresa->porte, porte, PORTE_TAM);
    copiarString(empresa->ente_federativo, ente, ENTE_FED_TAM);

    return empresa;
}


Empresa *obterDados(FILE *arq, char *cnpj, char *nome)
{
    char *natureza_juridica = removerAspas(strtok(NULL, ";"));
    char *qualificacao_responsavel = removerAspas(strtok(NULL, ";"));
    char *capital_social = removerAspas(strtok(NULL, ";"));
    char *porte = removerAspas(strtok(NULL, ";"));
    char *ente_federativo = strtok(NULL, ";");

    Empresa *empresa = copiarDados(cnpj, nome, natureza_juridica,
                                   qualificacao_responsavel, capital_social,
                                   porte, ente_federativo);
    return empresa;
}


Empresa *loadCSV(FILE *arq, int escolha, const char *procurado)
{
    Empresa *empresa = NULL;

    char linha[MAX_LINE_LENGTH];
    while (fgets(linha, sizeof(linha), arq))
    {
        char *cnpj = strtok(linha, ";");
        char *nome = strtok(NULL, ";");

        if (cnpj != NULL)
        {
            cnpj = removerAspas(cnpj);
            if (escolha == 0 && compararPrimeirosDigitos(cnpj, procurado) != 0)
            {
                continue;
            };
        }

        if (nome != NULL)
        {
            {
                nome = removerAspas(nome);
                if (escolha == 1 && strcmp(nome, procurado) != 0)
                {
                    continue;
                }
            }
        }

        if (cnpj && nome)
        {
            if (strcmp(cnpj, procurado) == 0 || strcmp(nome, procurado) == 0)
            {
                if (strcmp(cnpj, procurado) == 0 && escolha == 0)
                {
                    empresa = obterDados(arq, cnpj, nome);
                    break;
                }
                else if (strcmp(nome, procurado) == 0 && escolha == 1)
                {
                    empresa = obterDados(arq, cnpj, nome);
                    break;
                }
            }
        }
    }

    return empresa;
}

Empresa *buscaBinaria(FILE *arq, const char *cnpjProcurado)
{
    long inicio = 0;
    long fim = obterTamanhoArquivo(arq);
    char linha[MAX_LINE_LENGTH];
    long meio;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;
        fseek(arq, meio, SEEK_SET);

        if (meio != 0)
        {
            fgets(linha, sizeof(linha), arq);
        }

        if (fgets(linha, sizeof(linha), arq) == NULL)
        {
            return NULL; 
        }

        fseek(arq, -strlen(linha), SEEK_CUR);

        char *cnpj = strtok(linha, ";");
        if (cnpj)
        {
            cnpj = removerAspas(cnpj);
            int resultadoComparacao = compararCNPJ(cnpj, cnpjProcurado);

            if (resultadoComparacao == 0)
            {
                char *nome = removerAspas(strtok(NULL, ";"));
                Empresa *empresa = obterDados(arq, cnpj, nome);
                return empresa;
            }
            else if (resultadoComparacao < 0)
            {
                Empresa *empresa = loadCSV(arq, 0, cnpjProcurado);
                return empresa;
            }
            else
            {
                fim = meio - 1;
            }
        }
    }
    return NULL; 
}


Empresa *buscar(char *arquivo, int escolha)
{
    char busca[NOME_TAM];
    Empresa *empresa = NULL;

    if (escolha == 0)
    {
        printf("Digite o CNPJ para buscar: ");
    }
    else
    {
        printf("Digite o Nome para buscar: ");
    }

    if (fgets(busca, sizeof(busca), stdin) != NULL)
    {
        FILE *arq = fopen(arquivo, "r");
        if (arq == NULL)
        {
            perror("Erro ao abrir o arquivo");
            exit(EXIT_FAILURE);
        }

        busca[strcspn(busca, "\n")] = '\0';
        if (escolha == 0)
        {
            empresa = buscaBinaria(arq, busca);
        }
        else
        {
            empresa = loadCSV(arq, escolha, busca);
        }
        fclose(arq);
    }
    else
    {
        perror("Erro ao ler a entrada");
    }

    return empresa;
}



