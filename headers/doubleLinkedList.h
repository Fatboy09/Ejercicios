#ifndef DLL_H_INCLUDED
#define DLL_H_INCLUDED

#define TRUE 1
#define FALSE 0

typedef char type_data;

typedef struct nodo {
    type_data elem;
    struct nodo* sig;
    struct nodo* ant;
}nodo;

typedef nodo* lista;

int isEmpty_doubleLinkedList(lista list);
int size_doubleLinkedList(lista list);
void doubleLinkedList_insert_node(lista* list,type_data e);
void doubleLinkedList_insert_node_at(lista* list,int index,type_data e);
void doubleLinkedList_insert_at_begin(lista* list,type_data e);
type_data doubleLinkedList_remove_node_at(lista* list, int index);
type_data doubleLinkedList_remove_node(lista* list);
type_data doubleLinkedList_remove_last_node(lista* list);
void doubleLinkedList_clear_list(lista* list);
int doubleLinkedList_is_elem_at_list(lista list,type_data e);
int doubleLinkedList_get_index(lista list,type_data e);
type_data doubleLinkedList_get_element_at(lista list,int index);
void print_doubleLinkedList(lista list);
void print_doubleLinkedListReference(lista list);

#endif // DOUBLE LINKED LIST_H_INCLUDED
