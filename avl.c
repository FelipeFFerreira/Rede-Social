
/* avl.c
 * Implementação das operações realizadas sobre o TAD que r
 * representa uma árvore AVL.
 *
 * Felipe F. Felipe
 * 30/Set/2019
 */

#include "avl.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void load_users(avl_tree * t, char * filename) {

    FILE * arq; // Arquivo lógico
    char palavra[10001], * token = NULL; // Nome do arquivo sobre o qual a contagem será realizada
    bool h;
    if ((arq = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo %s\n", filename);
        exit(1);
     }

    avl_tree x = NULL;
    avl_info user; 
    lista l;

    while (fscanf(arq, " %1000[^\n]s", palavra) != EOF) {
    
        inicializar_lista(&l);
        token = strtok(palavra, ";");
        strcpy(user.usuario, token);
        token = strtok(NULL, ";");
        strcpy(user.nome_completo, token);
        token = strtok(NULL, ";");
        strcpy(&(user.sexo), token);
        user.amigos = l;
       	if( fscanf(arq, " %1000[^\n]s", palavra) != EOF) {
			if((add_new_user(t, user)) == 1) { //se criado nó com dados do usuario       		
           		if(palavra[0] != ';') {
           			x = busca_usuario((*t), user.usuario);
                	int len_palavra = strlen(palavra); //tamanho da linha de amigos
                	token = strtok(palavra, ";");
                	int len = strlen(token) + 1; //tamanho da palavra do amigo capturado
                	while(len < len_palavra) {
                    	inserir_lista(&l, token);
                    	token = strtok(NULL, ";");
                    	len += (strlen(token) + 1);
                	}
                	inserir_lista(&l, token);
                	x->dado.amigos = l;
                }	
            }
        }
    }
}


bool add_new_user(avl_tree * t, avl_info x) {

	bool h, k = false;
	search_add_new_user(t, x, &h, &k);
   	return k;
}


void search_add_new_user(avl_tree * t, avl_info x, bool * h, bool * k) {

    if (*t == NULL) {
        if ((*t = (avl_tree) malloc(sizeof(struct avl_no))) == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }

        *h = true;
    
        (*t)->dado = x;
       // (*t)->dado.amigos = x.amigos;
        (*t)->esq = (*t)->dir = NULL;
        (*t)->bal = 0;
        *k = true;
        //printf("No criaro com sucess\n");
    }
    else if (strcasecmp(x.usuario,(*t)->dado.usuario) < 0) { // Inserir a esquerda
        search_add_new_user(&(*t)->esq, x, h, k);
        if (*h) { // O ramo esquerdo cresceu
            switch ((*t)->bal) {
                case 1: (*t)->bal = 0;
                        *h = false;
                        break;
                case 0: (*t)->bal = -1;
                        break;
                case -1:
                    // Rebalanceamento
                    if ((*t)->esq->bal == -1) { //Rotação simples p/ direita
                        rotacao_dir(t);
                        (*t)->dir->bal = 0; //Ajusta o fator de balanceamento
                    }
                    else { // Rotação dupla para direita
                        rotacao_esq(&(*t)->esq);
                        rotacao_dir(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                    }
                    *h = false;
                    (*t)->bal = 0;
                    break;
            } // fim do switch
        }
    } // fim do if
    else if (strcasecmp(x.usuario,(*t)->dado.usuario) > 0) { // Inserir a direita
        search_add_new_user(&(*t)->dir, x, h, k);
        if (*h) { // O ramo direito cresceu
            switch ((*t)->bal) {
                case -1: (*t)->bal = 0;
                         *h = false;
                         break;
                case 0 : (*t)->bal = 1;
                         break;
                case 1: // Rebalanceamento
                    if ((*t)->dir->bal == 1) { // Rotação simples p/ esquerda
                        rotacao_esq(t);
                        // Ajusta o fator de balanceamento
                        (*t)->esq->bal = 0;
                    }
                    else { // Rotação dupla para esquerda
                        rotacao_dir(&(*t)->dir);
                        rotacao_esq(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                    } // fim do else
                    *h = false;
                    (*t)->bal = 0;
                    break;
            } // fim do switch
        }
    } // fim do if
    else { // a chave já está na árvore
        *k = false;
        //printf("NO já existente\n");
    }

} // fim de add_new_user


bool delete(avl_tree * t, char * x, bool * h) {
    avl_tree p;
    bool result;
    if (*t == NULL) // A chave não se encontra na árvore
        return false;
    else if (strcasecmp(x, (*t)->dado.usuario) == 0) { // a chave está neste nó
        p = *t;
        if ((*t)->esq == NULL) { // nó folha ou somente com subárvore direita
            *t = p->dir;
            *h = true;
        }
        else if ((*t)->dir == NULL) { // nó com uma única subárvore esquerda
            *t = p->esq;
            *h = true;
        }
        else { // nó com duas subávores
            p = get_min(&(*t)->dir, h);
            (*t)->dado = p->dado;
            if(*h) balance_dir(t, h);
        }
        free(p);
        return true;
    }
    else if (strcasecmp(x,(*t)->dado.usuario) < 0) {
        result = delete(&(*t)->esq, x, h);
        if (*h) balance_esq(t, h);
        return result;
    }
    else {
        result = delete(&(*t)->dir, x, h);
        if (*h) balance_dir(t, h);
        return result;
    }
} // fim do delete



avl_tree get_min(avl_tree * t, bool * h) {
    avl_tree q;
    if ((*t)->esq != NULL) {
        q = get_min(&((*t)->esq),h);
        if (*h) balance_esq(t, h);
        return q;
    }
    else {
        *h = true;
        q = *t;
        *t = (*t)->dir;
        return q;
    }
}


void balance_dir(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case 1: (*t)->bal = 0;
                break;
        case 0: (*t)->bal = -1;
                *h = false;
                break;
        case -1: // rebalanceamento
                p1 = (*t)->esq;
                b1 = p1->bal;
                if (b1 <= 0) { // rotação simples
                    (*t)->esq = p1->dir;
                    p1->dir = *t;
                    if (b1 == 0) {
                        (*t)->bal = -1;
                        p1->bal = 1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotação dupla
                    p2 = p1->dir;
                    b2 = p2->bal;
                    p1->dir = p2->esq;
                    p2->esq = p1;
                    p1->esq = p2->dir;
                    p2->dir = *t;
                    if(b2 == -1) (*t)->bal = 1;
                    else (*t)->bal = 0;
                    if(b2 == 1) p1->bal = -1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    } // fim do switch
}

void balance_esq(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case -1: (*t)->bal = 0;
                 break;
        case 0: (*t)->bal = 1;
                *h = false;
                break;
        case 1: // rebalanceamento
                p1 = (*t)->dir;
                b1 = p1->bal;
                if (b1 >= 0) { // rotação simples
                    (*t)->dir = p1->esq;
                    p1->esq = *t;
                    if (b1 == 0) {
                        (*t)->bal = 1;
                        p1->bal = -1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotação dupla
                    p2 = p1->esq;
                    b2 = p2->bal;
                    p1->esq = p2->dir;
                    p2->dir = p1;
                    p1->dir = p2->esq;
                    p2->esq = *t;
                    if (b2 == 1) (*t)->bal = -1;
                    else (*t)->bal = 0;
                    if (b2 == -1) p1->bal = 1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    } // fim do switch
}



// Rotaçao para a esquerda
void rotacao_esq(avl_tree * t) {
    avl_tree p;
    p = (*t)->dir;
    (*t)->dir = p->esq;
    p->esq = *t;
    *t = p;
}

// Rotação para a direita
void rotacao_dir(avl_tree * t) {
    avl_tree p;
    p = (*t)->esq;
    (*t)->esq = p->dir;
    p->dir = *t;
    *t = p;
}

void salva_arq(avl_tree t, FILE * arq)
{ 
    if (t != NULL) {
        salva_arq(t->esq, arq);

        fprintf(arq, "%s;%s;%c\n", t->dado.usuario, t->dado.nome_completo, t->dado.sexo);
        if(t->dado.amigos != NULL) {
            while (t->dado.amigos != NULL) {
                fprintf(arq, "%s;", t->dado.amigos->dado);
                t->dado.amigos = t->dado.amigos->prox;
            }
            fprintf(arq, "\n");
        }
        else fprintf(arq, "%c\n", ';');

        salva_arq(t->dir, arq);
    }
}

bool remover_user(avl_tree t, char * user)
{
    avl_tree x = busca_usuario(t, user);  //Retorna endereço do usuario na arv
    //printf("\nUser: %s\n", x->dado.usuario);
    char amigo[61];  

    if(x != NULL) { //se existir 
        
        bool h, i;
        lista l = x->dado.amigos, p; //endereço da lista de amigos do usuario
        p = l;

        if(l != NULL) { // se existir algum amigo
            while (l != NULL) {
                //printf("1 amigo %s,", l->dado);
                avl_tree y = busca_usuario(t, l->dado); //endereço do amigo na arv
                //printf("\nCOnf.amigo %s\n", y->dado.usuario);
                //printf("Primeiro nome do amg de %s : %s\n", y->dado.usuario, y->dado.amigos->dado);
                if( delete_lista(&(y->dado.amigos), user))printf("<Sucess delet %s of %s\n", user, y->dado.usuario);

                //else printf(" Falha ao deletar\n");
                //printf("Primeiro nome do amg de %s : %s\n", y->dado.usuario, y->dado.amigos->dado);

                    l = l->prox;
                }
                lista_kill(&p);
                return 1;
            }
           
            return 1;
       }
    return 0;
 }
    

void list_users(avl_tree t) {
    if (t != NULL) {
        list_users(t->esq);
        printf("> USUARIO: [%-10s]\tNOME: [ %-20s]\tSEXO: [%c]\n", t->dado.usuario, t->dado.nome_completo, t->dado.sexo);
        //imprimir_lista(t->dado.amigos);
        list_users(t->dir);
    }
}

bool add_friend(avl_tree t, char * user, char * friendname)
{
	avl_tree x = busca_usuario(t, user);  //Endereço do usuario na arv
	avl_tree y = busca_usuario(t, friendname); //Endereço do amigo na arv
 
    if((x != NULL) && (y != NULL)) {
	   lista l = lista_find(x->dado.amigos, friendname); //verifica se usuario já não o amigo adicionado
       if( (strcmp(user, friendname) !=  0)  && (l == NULL)) { //Se não for o propropio user e user n ter frind em comum
			inserir_lista(&(x->dado.amigos), friendname);  //Lista de amigo do usuario
            inserir_lista(&(y->dado.amigos), user);  //lista de amigo do amigo        
			return 1;
		}

		else return 0;
	}
	 return 0;
}



bool list_friends(avl_tree t, char * user)
{
    /* Realiza uma busca pelo usuario na ABB t */
    avl_tree x = busca_usuario(t, user);


    if(x != NULL) { // Se o usuario existir na rede
        printf("\n<Friends %s: \n\n", user);
        lista l; //ponteiro p/ lista de amigos do usuario
        l = x->dado.amigos; //endereço da lista de amigos do usuario
        
        while (l != NULL) {
            avl_tree y = busca_usuario(t, l->dado);
            printf("<USUARIO: [%-10s]\tNOME: [ %-20s]\tSEXO: [%c]\n", y->dado.usuario, y->dado.nome_completo, y->dado.sexo);
            l = l->prox;
        }
        return 1;
    }     
	else 
		printf("\n<User with no friends availablen");
		return 0;
}


/* Realiza uma busca pelo valor x na ABB t */
avl_tree busca_usuario(avl_tree t, char * x)
{
    if (t == NULL)
        return NULL;
    else
        if (strcmp(t->dado.usuario, x) == 0) return t;
        else
            if (strcmp(x, t->dado.usuario) < 0) return busca_usuario(t->esq, x);
            else return busca_usuario(t->dir, x);
}


int menu(char * opcao[NUM_OP])
{
    int i, op;
    printf("\n\n*************************************************\n\t* * * [ MENU PRINCIPAL ] * * *\n*************************************************\n\n");
    for(i = 0; i < NUM_OP; i++) {
        printf("%-20s\t\tOP:%d\n", opcao[i], i + 1);
    }
    printf("\n[SELECIONE UMA OP]: ");
    scanf(" %d", &op);
    return op;
}

FILE *open_arquivo() {

    FILE * arq; // Arquivo lógico     
    if ((arq = fopen("filename", "w")) == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo %s\n", "filename");
     }

    return arq;
}