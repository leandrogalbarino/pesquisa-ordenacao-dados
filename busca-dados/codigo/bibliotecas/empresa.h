#ifndef EMPRESA_H
#define EMPRESA_H

#define CNPJ_TAM 15
#define NOME_TAM 255
#define MAX_LINE_LENGTH 1024
#define NATJURIDICA_TAM 5
#define QUALIFICACAO_TAM 3
#define CAPITAL_TAM 21
#define ENTE_FED_TAM 6
#define PORTE_TAM 3
#define BLOCO_TAM 4096

#include <stdlib.h>
#include <stdio.h>

typedef struct Empresa
{
    char cnpj[CNPJ_TAM];
    char nome[NOME_TAM];
    char natureza_juridica[NATJURIDICA_TAM];
    char qualificacao_responsavel[QUALIFICACAO_TAM];
    char capital_social[CAPITAL_TAM];
    char porte[PORTE_TAM];
    char ente_federativo[ENTE_FED_TAM];
} Empresa;


#endif 