/* lista.h
 * Defini��o do tipo lista e defini��o dos prot�tipos das opera��es.
 *
 * Felipe F. Ferreira
 * 06/Outubro/2019
 */

#ifndef _LISTA_H
#define _LISTA_H

#include <stdbool.h>

typedef char * lst_info;

typedef struct lst_no * lista;

struct lst_no {

	lst_info dado;
	lista prox;
};



/* fun��o que inicializa a lista */
void inicializar_lista(lista *);

/* fun��o que insere um novo n� no final da lista */
void inserir_lista(lista *, lst_info);

/* fun��o que imprime a lista */
void imprimir_lista(lista);

/* fun��o que deleta um n� da  lista */
bool delete_lista(lista * l, lst_info);

/* fun��o que destroi uma lista encadeada */
void lista_kill(lista * l);

/* fun��o que procura um mebro na lista encadeada */
lista lista_find(lista l, lst_info x);

#endif

