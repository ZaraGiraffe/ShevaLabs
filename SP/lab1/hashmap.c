#ifndef HASHMAP_C
#define HASHMAP_C

#include<stdio.h>
#include<stdlib.h>

#define SIZE 10000


struct Node {
    struct Node* next;
    wchar_t* word;
};


struct HashMap {
    struct Node* array[SIZE];
};


void init_hashmap(struct HashMap* hashmap) {
    for (int i = 0; i < SIZE; i++)
        hashmap->array[i] = NULL;
}


int hash_djb2(const wchar_t* word) {
    unsigned int hash_num = 5381;
    int c = 0;
    while(*word) {
        c = *word;
        hash_num = (hash_num << 5) + hash_num + c; 
        word++;
    }
    return hash_num % SIZE;
}


void add_word_to_hashmap(struct HashMap* hashmap, const wchar_t* word) {
    int pos = hash_djb2(word);
    struct Node* new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->next = NULL;
    wchar_t* new_word = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(word) + 1));
    wcscpy(new_word, word);
    new_node->word = new_word;
    struct Node* now = hashmap->array[pos];
    if (now == NULL) {
        hashmap->array[pos] = new_node;
        return;
    }
    while (now->next != NULL) 
        now = now->next;
    now->next = new_node;
}


int is_in_hashmap(const struct HashMap* hashmap, const wchar_t* word) {
    int pos = hash_djb2(word);
    struct Node* node = hashmap->array[pos];
    if (node == NULL)
        return 0;
    while (node != NULL) {
        if (!wcscmp(word, node->word)) 
            return 1;
        node = node->next;
    }
    return 0;
}

#endif