#include "includes/filaOrdenada.h"
#include <time.h>
#include <string.h>

void initList(List *list){
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
}

void insert(List *list, Object x){
	Pointer new;
	new = (Pointer)malloc(sizeof(Pointer));
	new->element = x;

	if(isEmpty(list)){
		list->first = new;
		list->last = new;
		new->prev = NULL;
		list->size++; // increase the size
		printf("## Object {%i} inserted in the 1st pos\n", new->element.key);
	} else {
		if(search(list, x.key)){ // verify if there isnt another object with the same value
			printf("## Object {%i} is already listed\n", x.key);
		} else {
			Pointer aux = list->first;
			if(list->last->element.key < x.key){
				aux = list->last;
				aux->next = new;
				new->prev = aux;
				list->last = new;
				list->size++; // increase the size
				printf("## Object {%i} inserted in the last position\n", new->element.key);
			} else if(list->first->element.key > x.key){
				new->next = aux;
				new->prev = aux->prev;
				aux->prev = new;
				list->first = new;
				list->size++; // increase the size
				printf("## Object {%i} inserted in the 1st pos and pushed object {%i} to 2nd pos\n", new->element.key, list->first->next->element.key);
			} else {
				while(aux->next != NULL && x.key > aux->next->element.key){
					aux = aux->next;
				}
				new->next = aux->next;
				aux->next->prev = new;
				new->prev = aux;
				aux->next = new;
				list->size++;
				printf("## Object {%i} inserted\n", new->element.key);
			}
		}
	}
}

void printList(List *list){
	Pointer aux = list->first;
	printf("\n{ ");
	for(aux = list->first; aux->next != NULL; aux = aux->next){
		printf("%i ", aux->element.key);
	}
	printf("%i ", aux->element.key);
	printf("}\n");
}

void printReverse(List *list){
	Pointer aux;
	printf("\n{ ");
	for(aux = list->last; aux->prev != NULL; aux = aux->prev){
		printf("%i ", aux->element.key);
	}
	printf("%i ", aux->element.key);
	printf("}\n");
}

void destroyList(List *list){
	Pointer aux;
	Pointer remove;
	for(aux = list->first; aux->next != NULL; aux = aux->next){
		remove = aux;
		aux = aux->next;
		free(remove);
	}
	printf("## MEMORY CLEAR ##\n");
}

bool isEmpty(List *list){
	return (list->size==0) ? true : false;
}

bool search(List *list, int key){
	if(isEmpty(list))	return false;
	if(list->size==1){
		if(list->first->element.key == key){
			return true;
		} else {
			return false;
		}
	} else {
		Pointer aux = list->first;
		while(aux->next != NULL && key > aux->element.key){
			aux = aux->next;
		}
		if(aux->element.key == key){
			return true;
		} else {
			return false;
		}
	}
}

// bool searchFaster(List *list, int key){
//
// }

int size(List *list){
	return list->size; // returns size of the list
}

void removeElement(List *list, int key, Object *item){
	if(isEmpty(list) || list->first->element.key > key){
		// if the list is empty or first object is bigger than the passed key, the key isnt listed
		item = NULL;
		printf("## The List is Empty or the object isnt listed!!\n");
	} else {
		if(key == list->first->element.key){
			removeFirst(list, item);
		} else {
			if(search(list, key)){
				Pointer aux;
				for(aux = list->first->next; aux->next->element.key != key; aux = aux->next);
					if(aux->next->next == NULL){
						removeLast(list, item);
					} else {
						Pointer remove = aux->next;
						aux->next = remove->next;
						*item = remove->element;
						list->size = list->size-1;
						printf("Removed object {%i}, resting %i elements", remove->element.key, list->size);
						free(remove); // free memory of aux remove
					}
			} else {
				printf("## Object isn't listed\n");
			}
		}
	}
}

void removeFirst(List *list, Object *item){
	Pointer aux = list->first; // makes a pointer to point to the first object of the list
	*item = aux->element;	// make the object passed by parameter receive the element of aux pointer
	list->first = aux->next;	// make the first object receive next object of aux pointer
	list->size--; // reduce the list size
	printf("## Removed 1st object with value { %i }\n", aux->element.key);
	free(aux); // free memory
}

void removeLast(List *list, Object *item){
	Pointer aux = list->last->prev;
	Pointer remove = list->last;
	*item = remove->element;
	printf("## Removed last object with value { %i }\n", (*item).key);
	aux->next = NULL; // make aux pointer next receive null
	list->last = aux; // make list last receive the aux pointer
	free(remove); // free memory
	list->size--; // reduce the list size
}

Object first(List *list){
	return list->first->element; // return the first listed object
}

Object last(List *list){
	return list->last->element; // return the last listed object
}

bool write(FILE *arq, List *list, char mode){ // write the list into the file according to the modus operand
	if(mode == 'd' || mode == 'D'){
		Pointer aux;
		fprintf(arq, "Tamanho = %i\n", size(list));
		fprintf(arq, "Lista = { ");
		for(aux = list->last; aux->prev != NULL; aux = aux->prev){
			// make a aux pointer receive the last object of the list and writes it in the file
			fprintf(arq, "%i ", aux->element.key);
		}
		fprintf(arq, "%i }\n", aux->element.key);
		printf("## OUTPUT FILE WRITED SUCCESSFULLY ##\n");
	} else {
		Pointer aux = list->first;
		fprintf(arq, "Tamanho = %i\n", size(list));
		fprintf(arq, "Lista = { ");
		for(aux = list->first; aux->next != NULL; aux = aux->next){
			// make a aux pointer receive the first object of the list and writes it in the file
			fprintf(arq, "%i ", aux->element.key);
		}
		fprintf(arq, "%i }\n", aux->element.key);
		printf("## OUTPUT FILE WRITED SUCCESSFULLY ##\n");
	}
}

int main(int argc, char *argv[2]) {
	char mode, lixo;
	int data;
	List list;
	Object ob;
	Object item;

	if(argc < 3){ // veirify if the user included the input file and output file name as parameters
		printf("## Error obtaining files names, please use ./PROGRAMNAME inputFileName.txt outputFileName.txt");
	} else {
		initList(&list);
		FILE *arqin = NULL;
		FILE *arqout = NULL;

		arqin = fopen(argv[1], "r");
		arqout = fopen(argv[2], "w");

		if(arqin == NULL || arqout == NULL){
			printf("Erro ao abrir os arquivos!");
			exit(1);
		}

		if(!fscanf(arqin,"%c", &mode) && (mode != 'd' || mode != 'c')){ // verify if the user put a correct modus operand (C to crescent, D to decrescent)
			printf("## Error obtainig modus operand");
		} else {
			while(!feof(arqin)){
				fscanf(arqin, "%i%c", &data, &lixo);
				ob.key = data;
				insert(&list, ob);
			}
			write(arqout, &list, mode);

			fclose(arqin);
			fclose(arqout);

			destroyList(&list);
		}
	}
	return 0;
}
