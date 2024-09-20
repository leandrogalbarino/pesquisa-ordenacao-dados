#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bibliotecas/string_utils.h"
#include "bibliotecas/empresa.h"
#include "bibliotecas/busca.h"

void mostrarDados(Empresa *dados, int escolha)
{
    if (dados != NULL)
    {
        printf("CNPJ: %s\n", dados->cnpj);
        printf("RAZAO SOCIAL: %s\n", dados->nome);
        printf("NATUREZA JURIDICA: %s\n", dados->natureza_juridica);
        printf("QUALIFICAÇÃO DO RESPONSAVEL: %s\n", dados->qualificacao_responsavel);
        printf("CAPITAL SOCIAL DA EMPRESA: %s\n", dados->capital_social);
        printf("PORTE DA EMPRESA: %s\n", dados->porte);
        printf("ENTE FEDERATIVO RESPONSAVEL: %s\n", dados->ente_federativo);
    }
    else
    {
        if (escolha == 0)
            printf("CNPJ nao encontrado!\n");
        else
            printf("Nome nao encontrado!\n");
    }
}

int interface()
{
    char arquivo[] = "Empresas0/K3241.K03200Y0.D40713.EMPRECSV";
    Empresa *dados;
    int escolha;
    int sair = 0;
    do
    {
        do
        {
            printf("Escolha uma opcao:\n");
            printf("0 - Buscar por CNPJ\n");
            printf("1 - Buscar por Nome\n");
            printf("2 - Cancelar\n");
            scanf("%d", &escolha);
            getchar();
            if (escolha < 0 || escolha > 2)
            {
                printf("Opcao invalida!\n\n");
            }
        } while (escolha < 0 || escolha > 2);

        if (escolha == 0 || escolha == 1)
        {
            dados = buscar(arquivo, escolha);
            mostrarDados(dados, escolha);
        }
        else
        {
            sair = 1;
            printf("Acao cancelada!\n");
        }
    } while (!sair);
}

int main()
{
    interface();
    return 0;
}
