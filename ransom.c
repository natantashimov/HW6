#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
   int count;
   char *name;
   struct node *next;
};
struct node *head1 = NULL;
struct node *head2 = NULL;

void checkMagazine(int magazine_count, char **magazine, int note_count,
				   char **note);
void magazine_histogram(char **magazine, int magazine_count);
void push1(int count,char *name);
void push2(int count,char *name);
void note_histogram(char **note,int note_count);
bool compare ();
bool check(struct node *node1,struct node *node2 );
char* readline();
char** split_string(char*);
void free_list(struct node *head);




void checkMagazine(int magazine_count, char **magazine, int note_count,
		 	 	    char **note) {

	magazine_histogram(magazine ,magazine_count);
	note_histogram(note, note_count);
	if (compare ()){
		printf("Yes");
	}
	else{
		printf("No");
	}
	free_list(head1);
	free_list(head2);
}


/* this function adding a node to the linked list of the magazine hisogram*/
void push1(int count,char *name){

	struct node *magazine_node = (struct node*) malloc(sizeof(struct node));
	if(magazine_node != NULL){
		magazine_node->count = count;
		magazine_node->name  = name;
		magazine_node->next  = head1;
		head1 = magazine_node;
	}
}
/* this function adding a node to the linked list of the note hisogram*/
void push2(int count,char *name){

	struct node *note_node = (struct node*) malloc(sizeof(struct node));
	if(note_node != NULL){
		note_node->count = count;
		note_node->name  = name;
		note_node->next  = head2;
		head2 = note_node;
	}

}

/* this function creates a linked list for the magazine.
 * every node will have values of word from the magazine,
 * and the number of times that word is showed in the magazine*/
void magazine_histogram(char **magazine,int magazine_count){

	int name_count=0;
	for (int i=0;i<magazine_count;i++){

		for (int j=0;j<magazine_count;j++){

			if (strcmp (magazine[i],magazine[j])==false){

				name_count++;
			}
		}
		push1( name_count ,magazine[i] );
		name_count=0;
	}
}
/* this function creates a linked list for the note.
 * every node will have values of word from the note,
 * and the number of times that word is showed in the note*/
void note_histogram(char **note,int note_count){

	int name_count=0;
	for (int i=0;i<note_count;i++){

		for (int j=0;j<note_count;j++){

			if (strcmp (note[i],note[j])==false){

				name_count++;
			}
		}
        push2(name_count ,note[i] );
        name_count=0;
	}
}

bool compare (){

	struct node* temp1=head1 ;
	struct node* temp2=head2 ;

    while (temp2 != NULL){

    	if (!(check(temp1,temp2))){

    		return false ;
    	}
    	temp2 = temp2->next;
    	temp1=head1;
    }
    return true;
}

bool check(struct node *temp1,struct node *temp2 ){

	while (temp1 != NULL){

		if (!strcmp(temp1->name,temp2->name)){

			if(temp1->count >= temp2->count){

                return true;
			} else{

                return false;
			}
		} else{

                temp1 = temp1->next;
		}
	}
	return false;
}

void free_list(struct node *head){

    struct node *tmp;
    while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }
    int note_count = n;
    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

