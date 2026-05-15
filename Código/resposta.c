#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadlista.h"

typedef struct {
    char id[128];
    char nome[128];
} t_membro;

typedef struct {
    char id[128];
    char titulo[128];
    char descricao[128];
} t_projeto;

typedef struct {
    char id_membro[128];
    char id_projeto[128];
} t_relacao;

Lista load_projetos(char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)return NULL;

    Lista lst = newLista();
    char id[256], titulo[256], descricao[256];
    while (fscanf(fp, "%[^,], %[^,],  %[^\r\n]\r\n", id, titulo, descricao)== 3) {
        t_projeto *p = malloc(sizeof(t_projeto));
        strcpy(p->id, id);
        strcpy(p->titulo, titulo);
        strcpy(p->descricao, descricao);
        appendLista(lst, p);
    }
    fclose(fp);
    return lst;
}

Lista load_membros(char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) return NULL;

    Lista lst = newLista();
    char id[128], nome[128];
    while (fscanf(fp, "%[^,],  %[^\r\n]\r\n", id, nome)== 2) {
        t_membro *m = malloc(sizeof(t_membro));
        strcpy(m->id, id);
        strcpy(m->nome, nome);
        appendLista(lst, m);
    }
    fclose(fp);
    return lst;
}

Lista load_relacoes(char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) return NULL;

    Lista lst = newLista();
    char id_membros[256], id_projeto[256];
    while (fscanf(fp, "%[^,],  %[^\r\n]\r\n",id_membros,id_projeto)== 2) {
        t_relacao *r = malloc(sizeof(t_relacao));
        strcpy(r-> id_membro, id_membros);
        strcpy(r->id_projeto, id_projeto);
        appendLista(lst, r);
    }
    fclose(fp);
    return lst;
}

Lista membros_projeto(char *id_proj, Lista lst_relacoes, Lista lst_membros) {
    Lista resultado = newLista();
    for (int i = 0; i < lenLista(lst_relacoes); i++) {
        t_relacao *r = getElem(lst_relacoes, i);
        if (strcmp(r->id_projeto, id_proj) == 0) {
            for (int j = 0; j < lenLista(lst_membros); j++) {
                t_membro *m = getElem(lst_membros, j);
                if (strcmp(m->id, r->id_membro) == 0) {
                    appendLista(resultado, m);
                }
            }
        }
    }
    return resultado;
}

Lista projetos_membro(char *id_mem, Lista lst_relacoes, Lista lst_projetos) {
    Lista resultado = newLista();
    for (int i = 0; i < lenLista(lst_relacoes); i++) {
        t_relacao *r = getElem(lst_relacoes, i);
        if (strcmp(r->id_membro, id_mem) == 0) {
            for (int j = 0; j < lenLista(lst_projetos); j++) {
                t_projeto *p = getElem(lst_projetos, j);
                if (strcmp(p->id, r->id_projeto) == 0) {
                    appendLista(resultado, p);
                }
            }
        }
    }
    return resultado;
}

int main() {
    Lista lst_membros = load_membros("bdmembros.txt");
    Lista lst_projetos = load_projetos("bdprojetos.txt");
    Lista lst_relacoes = load_relacoes("bdrelacoes.txt");

    int op;
    char entrada[128];

        printf("\nMENU APP LISTA\n");
        printf("\n =====================\n");
        printf("1 - Membros de 1 Projeto\n");
        printf("2 - Projetos de 1 Membro\n");
        printf("3 - Sair\n");
        printf("Escolha 1 Opcao: ");
        printf("\n =====================\n");
        scanf("%d", &op);

    while (op != 3){
        if (op == 1) {
            printf("Digite o ID do membro: ");
            scanf("%s",entrada);
            Lista res = projetos_membro(entrada, lst_relacoes, lst_projetos);
            for (int i = 0; i < lenLista(res); i++) {
                t_projeto *p = getElem(res, i);
                printf("%s\n", p->titulo);
            }
        } else if (op == 2) {
            printf("Digite o ID do projeto: ");
            scanf("%s",entrada);
            Lista res = membros_projeto(entrada, lst_relacoes, lst_membros);
            for (int i = 0; i < lenLista(res); i++) {
                t_membro *m = getElem(res, i);
                printf("%s\n", m->nome);
            }
        }

        printf("\nMENU APP LISTA\n");
        printf("\n =====================\n");
        printf("1 - Membros de 1 Projeto\n");
        printf("2 - Projetos de 1 Membro\n");
        printf("3 - Sair\n");
        printf("Escolha 1 Opcao: ");
        printf("\n =====================\n");
        scanf("%d", &op);
    }

    return 0;
}
