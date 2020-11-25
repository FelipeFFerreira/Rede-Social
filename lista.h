/* lista.h
 * Definição do tipo lista e definição dos protótipos das operações.
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



/* função que inicializa a lista */
void inicializar_lista(lista *);

/* função que insere um novo nó no final da lista */
void inserir_lista(lista *, lst_info);

/* função que imprime a lista */
void imprimir_lista(lista);

/* função que deleta um nó da  lista */
bool delete_lista(lista * l, lst_info);

/* função que destroi uma lista encadeada */
void lista_kill(lista * l);

/* função que procura um mebro na lista encadeada */
lista lista_find(lista l, lst_info x);

#endif

