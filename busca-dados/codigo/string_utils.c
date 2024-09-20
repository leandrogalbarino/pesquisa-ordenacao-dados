#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *removerAspas(char *str)
{
    if (str && strlen(str) > 1 && str[0] == '"' && str[strlen(str) - 1] == '"')
    {
        str[strlen(str) - 1] = '\0'; 
        return str + 1;              
    }
    return str;
}

int compararPrimeirosDigitos(const char *atual, const char *procurado)
{

    if (atual && procurado)
    {
        return strncmp(atual, procurado, 4); 
    }
    return -1; 
}

int compararCNPJ(const char *cnpjArquivo, const char *cnpjProcurado)
{
    if (cnpjArquivo && cnpjProcurado)
    {
        return strcmp(cnpjArquivo, cnpjProcurado); 
    }
    return -1;
}

void copiarString(char *destino, const char *origem, size_t tamanho)
{
    if (destino && origem)
    {
        strncpy(destino, origem, tamanho - 1); 
        destino[tamanho - 1] = '\0'; 
    }
}
