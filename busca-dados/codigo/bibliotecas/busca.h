#ifndef BUSCA_H
#define BUSCA_H

#include <stdlib.h>
#include <stdio.h>
#include "empresa.h"

long obterTamanhoArquivo(FILE *arq);

Empresa *copiarDados(char *cnpj, char *nome, char *nat, char *quali, char *capital, char *porte, char *ente);

Empresa *obterDados(FILE *arq, char *cnpj, char *nome);

Empresa *loadCSV(FILE *arq, int escolha, const char *procurado);

Empresa *buscaBinaria(FILE *arq, const char *cnpjProcurado);

Empresa *buscar(char *arquivo, int escolha);

#endif 
