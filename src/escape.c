#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "../headers/doubleLinkedList.h"

void clearInputBuffer() {
	while(getchar() != '\n');
}

void remove_G(lista* esc, int index) {
	doubleLinkedList_remove_node_at(esc, index);
}

bool validarEscape(lista* esc) {
	
	bool is_G_lastNode = false;
	int totalElementsList = size_doubleLinkedList(*esc);
	int index = doubleLinkedList_get_index(*esc, 'G');
	
	while(index != (totalElementsList - 1) && index >= 0) {
		remove_G(esc, index);
		totalElementsList = size_doubleLinkedList(*esc);
		index = doubleLinkedList_get_index(*esc, 'G');
	}
	
	if(doubleLinkedList_is_elem_at_list(*esc, 'G')) {
		is_G_lastNode = true;
	}
	
	return is_G_lastNode == true? false:true;
	
}

int main() {
	
	lista esc = NULL;
	unsigned totalNodes;
	char valorNodo;
	unsigned maximumAttempts = 3;
	
	printf("Ingrese total de nodos: ");
	scanf("%u", &totalNodes);
	
	while(maximumAttempts > 0) {
		
		for(unsigned i = 0; i < totalNodes; ++i) {
			clearInputBuffer();
			printf("Ingrese una 'G' o 'T': ");
			valorNodo = (char) toupper(getc(stdin));
			doubleLinkedList_insert_node(&esc, valorNodo);
		}
		printf("\n");
		if(validarEscape(&esc)) {
			printf("Escape exitoso\n\n");
		} else {
			printf("Escape fallido\n");
			maximumAttempts--;
			printf("Te quedan %d intentos\n\n", maximumAttempts);
		}
		
		if(!isEmpty_doubleLinkedList(esc)) {
			doubleLinkedList_clear_list(&esc);
		}
	}
	
	if(!isEmpty_doubleLinkedList(esc)) {
		doubleLinkedList_clear_list(&esc);
	}
	
	return 0;
}
