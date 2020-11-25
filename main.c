#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "avl.h"



int main() {

    char filename[61], usuario[61], friendname[61];
    avl_tree t = NULL;
    avl_info  user;     
    bool h;

    printf("\n<Enter FileName *there is a file filenam*: ");
    scanf(" %60[^\n]", filename);
    printf("\n<Data loaded from disk!\n");
    load_users(&t, filename);
   
    char * opcoes[NUM_OP] = { "Adicionar Novo Usuario", "Listar Todos Usuarios",
                              "Listar Amigos", "Adicionar Amigo", "Remover Usuario",
                              "Sair do Programa"
                            };
    int op;

    do {

        op = menu(opcoes);

        switch(op) {

        case ADD_USUARIO:
            printf(">Enter username: ");
            scanf(" %60[^\n]", usuario);
            strcpy(user.usuario, usuario);
            printf(">Enter full username: ");
            scanf(" %60[^\n]", usuario);
            strcpy(user.nome_completo, usuario);
            printf(">Enter the gender: ");
            scanf(" %60[^\n]", usuario);
            strcpy(&(user.sexo), usuario);
            user.amigos = NULL;
            if(add_new_user(&t, user))printf("\n<User successfully added!\n");
            else printf("\n<Failed to add, or existing user!\n");
            break;

        case LISTA_TODOS_USERS:
            list_users(t);
            break;

        case LISTAR_AMIGO:
            printf(">Enter username: ");
            scanf(" %60[^\n]", usuario);
            if(list_friends(t, usuario))printf("\n<Success\n");
            else printf("<Non-existent user error\n");
            break;
        case ADD_AMIGO: 
            printf(">Enter username: ");
            scanf(" %60[^\n]", usuario);
            printf(">Enter username friend: ");
            scanf(" %60[^\n]", friendname);
            if(add_friend(t, usuario, friendname))printf("Success operation");
            else printf("<User or friend doesn't exist in network or is already friend\n");
            break;

        case REMOVER_USER:
            printf(">Enter username: ");
            scanf(" %60[^\n]", usuario);
            if(remover_user(t, usuario)) {
                if(delete(&t, usuario, &h)) printf("\n<Success operation\n"); //remove no da arvore
            }
            else printf("<Error User or friend does not exist\n");
            break;  
            
        case SAIR:
            break;
        default:
            printf( "\n\tOpção invalida!" );
        }
    }

    while(op != SAIR);

    FILE * arq = open_arquivo();
    salva_arq(t, arq);
    printf("\n<nUploading Files\n");
    fclose(arq);


     return 0;
}

