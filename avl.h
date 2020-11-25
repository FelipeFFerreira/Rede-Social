/* avl.h
 * Definição do TAD para representar uma árvore AVL e protótipo
 * de suas operações.
 *
 * Felipe F. Ferreira
 * 06/Outubro/2019
 */

#ifndef _AVL_H
#define _AVL_H

#include "avl.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*Definiçoes de menu da Rede Social*/
#define ADD_USUARIO	         1
#define LISTA_TODOS_USERS    2
#define LISTAR_AMIGO         3
#define ADD_AMIGO			 4
#define REMOVER_USER         5
#define SAIR                 6
#define NUM_OP               6

// Definição da estrutura de dados
typedef struct { 
    char usuario[21]; // nome de usuário
    char nome_completo[51]; // nome completo
    char sexo;
    lista amigos; // lista encadeada ordenada dos amigos
}avl_info;

typedef struct avl_no * avl_tree;

struct avl_no {
    avl_info dado;
    avl_tree esq;
    avl_tree dir;
    int bal; // balanceamento do nó
};

/*
* Função responsavel pa nova rede, apoś modificações
*/
void salva_arq(avl_tree t, FILE * arq);

/*
 * Faz uma rotação para a esquerda na árvore AVL t.
 */
void rotacao_esq(avl_tree *);

 /*
 *	Deleta um nó da arvore avl
 */
bool delete(avl_tree * t, char * x, bool * h);

/*
 * Faz o balanceamento da árvore AVL t após uma remoção
 * em sua subárvore esquerda e sinaliza se houve uma
 * dimuição da altura dessa subárvore através de h.
 */
void balance_esq(avl_tree * t, bool * h);

/*
 * Faz o balanceamento da árvore AVL t após uma remoção
 * em sua subárvore direita e sinaliza se houve uma
 * dimuição da altura dessa subárvore através de h.
 */
void balance_dir(avl_tree *, bool *);

/*
 * Devolve um ponteiro para o nó que contém o menor
 * valor na árvore AVL t e sinaliza através de h se
 * houve uma diminuição da altura de t.
 */
avl_tree get_min(avl_tree * t, bool * h);


void load_users(avl_tree * t, char * filename);

 /*
 *	Adicionar um novo usuario, á um nó dá arvore,
 *	com seus respectivos dados cadastrais, devolve
 *	true se a op for bem sucedida
 */
bool add_new_user(avl_tree * , avl_info);

 /*
 *	Função dá arv avl, responsavel por reoganizar os nós
 *	da árvore apoś ser inserido um novo usuario na rede
 */
void search_add_new_user(avl_tree * t, avl_info x, bool * h, bool * k);

 /*
 *	Função responsavel por todos os usuarios
 *	cadastrados na rede.
 */
void list_users(avl_tree t);
 
 /*
 *	Função responsavel por lista todos os amigos de um usuario
 *	cadastrados na rede.
 */
bool list_friends(avl_tree, char *);
 
/*
*	Função responsavel por adicionar um novo amigo há um membro na rede
*   p/ ser sucedida, tanto o amigo e o usuario devem existir na rede,
*  a função adiciona os dois membros respectivamente em sua lista de amigos.
* 	cadastrados na rede.
*/
bool add_friend(avl_tree, char *, char *);

 /*
*	Função responsavel por buscar um determinado usuario na rede
 */
avl_tree busca_usuario(avl_tree , char * x);

/*
*	Função responsavel por remover um membro na rede, o membro removido
*   é automaticamente removido da lista de todos os amigos que tenha esse membro como amigo.
*/
bool remover_user(avl_tree t , char * user);

/*
*	Função responsavel por mostrar todas as funções disponiveis no programa
*/
int menu(char * opcao[NUM_OP]);

/*
* Função responsavel pela abertura de arquivo da rede, no qual
  contem todos os dados e respectivos amigos cadastrados
*/
FILE *open_arquivo();

#endif

