#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
char *removerAspas(char *str);

int compararPrimeirosDigitos(const char *atual, const char *procurado);

int compararCNPJ(const char *cnpjArquivo, const char *cnpjProcurado);

void copiarString(char *destino, const char *origem, size_t tamanho);

#endif 