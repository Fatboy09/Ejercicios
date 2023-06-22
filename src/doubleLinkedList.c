#include <stdio.h>
#include <stdlib.h>
#include "../headers/doubleLinkedList.h"


/***
 * @brief valida si la lista esta o no vacía
 * @param lst puntero de tipo nodo que representa a la DE lista
 * @returns Devuelve un valor booleano
 *
 ***/ 
int isEmpty_doubleLinkedList(lista lst) {
    return lst == NULL? TRUE:FALSE;
}

/***
 * @brief calcula el total de elementos que contiene la lista
 * @param lst puntero de tipo nodo que representa a la DE lista
 * @returns Devuelve el total elementos de una lista
 *
 ***/
int size_doubleLinkedList(lista lst) {
    if(lst == NULL)
        return 0;
    
    return 1 + size_doubleLinkedList(lst->sig);
}

/***
 * @brief reserva en memoria dinamica una estructura de tipo nodo
 * @param e tipo de dato que se guarda en la lista
 * @returns Devuelve una estructura de tipo de nodo guardado en memoria dinámica
 ***/
nodo* crear_nodo(type_data e) {
    nodo* new_nodo = (nodo*) malloc(sizeof(nodo));
    if(new_nodo == NULL) {
        fprintf(stderr,"Error. No se reservo espacio en memoria\n");
        exit(EXIT_FAILURE);
    }
    new_nodo->elem = e;
    new_nodo->sig = NULL;
    new_nodo->ant = NULL;
    return new_nodo;
}

/***
 * @brief Inserta un elemento nuevo en la lista
 * @param lst puntero doble de tipo nodo que representa a la DE lista
 * @param value representa el valor que se almacenara en la lista
 ***/
void doubleLinkedList_insert_node(lista* lst, type_data value) {
    nodo* new_nodo = crear_nodo(value);
    if(isEmpty_doubleLinkedList(*lst)) {
        *lst = new_nodo;
    } else {
        lista aux = *lst;
        while(aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = new_nodo;
        new_nodo->ant = aux;
    }
}

/***
 * @brief Inserta un elemento nuevo al inicio de la lista
 * @param lst puntero doble de tipo nodo que representa a la DE lista
 * @param value representa el valor que se almacenara en la lista
 ***/
void doubleLinkedList_insert_at_begin(lista* lst,type_data value) {
    nodo* new_nodo = crear_nodo(value);
    if(isEmpty_doubleLinkedList(*lst)) {
        *lst = new_nodo;
        return;
    }
    lista aux = *lst;
    new_nodo->sig = aux;
    aux->ant = new_nodo;
    *lst = new_nodo;
}

/***
 * @brief Inserta un elemento nuevo en la lista en la posicion en el que se desea insertar
 * @param lst puntero doble de tipo nodo que representa a la DE lista
 * @param pos representa el indice de la posición de la lista, es un valor entero cuyo rango esta entre 0 hasta el total de elementos - 1
 * @param value representa el valor que se almacenara en la lista
 ***/
void doubleLinkedList_insert_node_at(lista* lst,int pos, type_data value) {
    if(isEmpty_doubleLinkedList(*lst)) {
        fprintf(stderr,"List is empty\n");
        return;
    }
    int tam = size_doubleLinkedList(*lst);
    if((pos >= tam) || (pos < 0)) {
        fprintf(stderr,"Error. Index out of range\n");
        return;
    }
    int index = 0;
    if(pos == 0){
        /*new_nodo->sig = aux;
        *lst = new_nodo;*/
        doubleLinkedList_insert_at_begin(lst,value);
    }
    else if(pos == (tam - 1)) {
        doubleLinkedList_insert_node(lst,value);
    } else {
        nodo* new_nodo = crear_nodo(value);
        lista aux = *lst;
        while(index < (pos - 1)) {
            ++index;
            aux = aux->sig;
        }
        new_nodo->sig = aux->sig;
        new_nodo->ant = aux;
        aux->sig = new_nodo;
    }
}

/***
 * @brief Elimina el primer elemento de la lista
 * @param lst puntero doble de tipo nodo que representa a la DE lista
 ***/
type_data doubleLinkedList_remove_node(lista* lst) {
    type_data value = -1;
    if(isEmpty_doubleLinkedList(*lst)) {
        fprintf(stderr,"Error. List is empty\n");
    } else {
        lista aux = *lst;
        value = aux->elem;
        aux->sig->ant = NULL;
        *lst = aux->sig;
        free(aux);
    }
    return value;
}

/***
 * @brief Elimina el último elemento de la lista
 * @param lst puntero doble de tipo nodo que representa a la DE lista
 ***/
type_data doubleLinkedList_remove_last_node(lista* lst) {
    type_data value = -1;
    if(isEmpty_doubleLinkedList(*lst)) {
        fprintf(stderr,"Error. List is empty\n");
    } else {
        lista aux = *lst;
        lista aux2 = NULL;
        int indice;
        int pos = size_doubleLinkedList(*lst) - 1;
        for(indice = 0; indice < pos - 1; ++indice) {
            aux = aux->sig;
        }
        aux2 = aux->sig;
        aux->sig = NULL;
        value = aux2->elem;
        free(aux2);
    }
    return value;
}

/***
 * @brief Elimina un elemento ubicada en una posición valida de la lista
 * @param lst puntero doble de tipo nodo que representa a la DE lista
 * @param pos representa el indice de la posición de la lista, es un valor entero cuyo rango esta entre 0 hasta el total de elementos - 1
 ***/
type_data doubleLinkedList_remove_node_at(lista* lst,int pos) {
    type_data value = -1;
    if(isEmpty_doubleLinkedList(*lst)) {
        fprintf(stderr,"Error. List is empty\n");
    } else {
        int lpos = size_doubleLinkedList(*lst) - 1;
        if((pos < 0) || (pos > lpos)) {
            fprintf(stderr,"Error. Index out of range\n");
        }
        else {
            if(pos == 0) {
                value = doubleLinkedList_remove_node(lst);
            }
            else if(pos == lpos) {
                value = doubleLinkedList_remove_last_node(lst);
            } else {
                lista aux = *lst;
                lista aux2 = NULL;
                int indice;
                for(indice = 0; indice < pos - 1; ++indice) {
                    aux = aux->sig;
                }
                aux2 = aux->sig;
                aux->sig = aux2->sig;
                aux2->sig->ant = aux;
                value = aux2->elem;
                free(aux2);
            }
        }
    }
    return value;
}

/***
 * @brief Obtiene el nodo que se ubica en la posición de la lista
 * @param lst puntero de tipo nodo que representa a la DE lista
 * @param pos representa el indice de la posición de la lista, es un valor entero cuyo rango esta entre 0 hasta el total de elementos - 1
 * @returns regresa el valor del dato
 ***/
type_data doubleLinkedList_get_element_at(lista lst, int pos) {
    type_data value = -1;
    if(isEmpty_doubleLinkedList(lst)) {
        fprintf(stderr,"Error. List is empty\n");
    } else {
        int lpos = size_doubleLinkedList(lst) - 1;
        if((pos < 0) || (pos > lpos)) {
            fprintf(stderr,"Error. Index out of range\n");
        } else {
            for(int i = 0; i < pos; ++i) {
                lst = lst->sig;
            }
            value = lst->elem;
        }
    }
    return value;
}

/***
 * @brief valida si el dato existe dentro de la lista
 * @param lst puntero de tipo nodo que representa a la DE lista
 * @param value representa el dato a buscar dentro de la lista
 * @returns retorna 1 o 0 dependiendo del resultado del proceso
 ***/
int doubleLinkedList_is_elem_at_list(lista lst, type_data value) {
    if(isEmpty_doubleLinkedList(lst)) {
        fprintf(stderr,"Error. List is empty\n");
        return -1;
    }
    int flag = FALSE;
    while(lst != NULL) {
        if(lst->elem == value) {
            flag = TRUE;
            break;
        }
        lst = lst->sig;
    }
    return flag;
}

/***
 * @brief Obtiene el valor del index en el que se encuentra el dato dentro de la lista
 * @param lst puntero de tipo nodo que representa a la DE lista
 * @param value representa el dato a buscar dentro de la lista
 * @returns regresa un valor numerico que representa el index en que se encontro el dato en la lista
 * el rango es de 0 a total de elementos - 1, en caso contrario retorna -1 indicando que el dato no existe en la lista
 ***/
int doubleLinkedList_get_index(lista lst, type_data value) {
	
    if(isEmpty_doubleLinkedList(lst)) {
        fprintf(stderr,"Error. List is empty\n");
        return -1;
    }
    int index = 0;
    int flag = FALSE;
    while(lst != NULL) {
        if(lst->elem == value) {
            flag = TRUE;
            break;
        }
        lst = lst->sig;
        index++;
    }
    return flag == 1? index:-1;
}

/***
 * @brief imprime en consola el valor del dato
 * @param x representa el dato a imprimir su valor
 ***/
void print_data_doubleLinkedList(type_data x) {
    printf("%c ", x);
}

/***
 * @brief imprime en consola los datos de la lista
 * @param lst puntero de tipo nodo que representa a la DE lista
 ***/
void print_doubleLinkedList(lista lst) {
    printf("[ ");
    while(lst != NULL) {
        print_data_doubleLinkedList(lst->elem);
        lst = lst->sig;
    }
    printf("]\n");
}

/***
 * @brief imprime en consola los datos de la lista asi como la información de la localidad de memoria en que apuntan los nodos
 * @param lst puntero de tipo nodo que representa a la DE lista
 ***/
void print_doubleLinkedListReference(lista list) {
    if(list == NULL)
        return;
    printf("%p <- %c [%p]-> %p\n",(void*)list->ant,list->elem,(void*)list,(void*)list->sig);
    print_doubleLinkedListReference(list->sig);
}

/***
 * @brief limpia todo el contenido de la lista
 * @param lst puntero doble de tipo nodo que representa a la DE lista
 ***/
void doubleLinkedList_clear_list(lista* list) {
    if(isEmpty_doubleLinkedList(*list))
        return;
    int size = size_doubleLinkedList(*list);
    if(size == 1) {
        free(*list);
        *list = NULL;
        return;
    }
    doubleLinkedList_remove_node(list);
    doubleLinkedList_clear_list(list);
}
