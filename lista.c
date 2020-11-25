
/* lista.c
 * Implementação das operações sobre uma lista encadeada circular
 *
 * Felipe. Ferreira
 * 06/Outubro/2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>
#include <stdbool.h>


/* Inicializa a lista no estado vazio */
void inicializar_lista(lista * l)
{
	*l = NULL;
}

/* Insere o elemento x no final da lista l */
void inserir_lista(lista * l, lst_info val)
{
    lista n;
    if ((n = (lista) malloc(sizeof(struct lst_no))) == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria!\n");
        exit(1);
    }

    char * p =(char *) malloc(strlen(val) * sizeof(float));
    strcpy(p, val);
    n->dado = p;

    if (*l == NULL || val <= (*l)->dado) { //testando se a lista ta vazia ou se o val pe menor igual ao 1º no da lista
       n->prox = *l;
       *l = n;
    }
    else {
        lista p = *l;
        while (p->prox != NULL && val > p->prox->dado) { //testando se val é o maior e se o valor é maior que o primeiro
            p = p->prox;
        }
        n->prox = p->prox;
        p->prox = n;
    }
}


void imprimir_lista(lista l)
{ 
	
    printf("[ ");
    while (l != NULL) {
        printf("%s,", l->dado);
        l = l->prox;
    }
    printf("\b ]\n");
}


bool delete_lista(lista * l, lst_info x)
{
    if ((*l == NULL || strcmp(x, (*l)->dado)) < 0) { //testando se a lista está vazia ou se o x é menor que o 1º elemento
        return false;
    }
    else {
        lista p = *l;
        if (strcmp(x, (*l)->dado) == 0) { //testando se x é igual ao primeiro elemento
            *l = p->prox; //poderia ser *l = (*l)->prox
            free(p);
            return true;
        }
        else {
            while (p->prox != NULL && strcmp(x, p->prox->dado) > 0) { //acha a posição (testa se x é maior que o
                p = p->prox;
            }
            if (p->prox != NULL && strcmp(x, p->prox->dado) == 0) {
                lista n = p->prox;
                p->prox = n->prox;
                free(n);
                return true;
            }
        }
        return false;
    }
}


void lista_kill(lista * l)
{
	lista p;
	while (*l != NULL) {
		p = *l;
		*l = (*l)->prox;
		free(p);
	}
}


lista lista_find(lista l, lst_info x)
{
    while (l != NULL && strcmp(x, l->dado) > 0) {
        l = l->prox;
    }
    if (l != NULL && strcmp(x, l->dado) == 0) {
        return l;
    }
    return NULL;
}