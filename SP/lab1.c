#include<stdio.h>
#include<wchar.h>
#include<stdlib.h>

#include"HashMap.c"

#define WORD_LENGTH 30


void save_characters(const char * filename, wchar_t* arr) {
    FILE* infile = fopen(filename, "r, ccs=UTF-8");
    if (infile == NULL) 
        printf("No "); //file does not open
    for (int i = 0; ; i++) {
        wchar_t ch = fgetwc(infile);
        while (ch == '\n' || ch == ' ')
            ch = fgetwc(infile);
        if (ch == (wchar_t)EOF) {
            arr[i] = 0;
            break;
        }
        arr[i] = ch;
    }
    fclose(infile);
}


wchar_t consonants[200];
void init_consonants(const char *filename) {
    save_characters(filename, consonants);
}


wchar_t letters[200];
void init_letters(const char *filename) {
    save_characters(filename, letters);
}


int is_good_symbol(wchar_t ch) {
    int check = 0;
    for (int i = 0; letters[i]; i++) {
        if (ch == letters[i]) {
            check = 1;
            break;
        }
    }
    return check;
}


int is_consonant(wchar_t ch) {
    int check = 0;
    for (int i = 0; consonants[i]; i++) {
        if (ch == consonants[i]) {
            check = 1;
            break;
        }
    }
    return check;
}


void get_next_word(FILE* file, wchar_t* word) {
    wchar_t ch = fgetwc(file);
    while (ch != (wchar_t)EOF && !is_good_symbol(ch)) 
        ch = fgetwc(file);
    if (ch == (wchar_t)EOF) {
        word[0] = 0;
        return;
    }
    int pos = 0;
    while (1) {
        if (!is_good_symbol(ch)) {
            word[pos] = 0;
            break;
        }
        word[pos] = ch;
        pos++;
        if (pos == WORD_LENGTH - 1) {
            word[pos] = 0;
            break;
        }
        ch = fgetwc(file);
    }
}


int count_consonants(wchar_t* word) {
    int cnt = 0;
    while (*word) {
        if (is_consonant(*word))
            cnt++;
        word++;
    }
    return cnt;
}


int find_maximum_consonants(char* filename) {
    FILE* infile = fopen(filename, "r, ccs=UTF-8");
    int maxi = 0;
    wchar_t word[WORD_LENGTH];
    get_next_word(infile, word);
    while (word[0]) {
        int cnt = count_consonants(word);
        if (cnt > maxi)
            maxi = cnt;
        get_next_word(infile, word);
    }
    fclose(infile);
    return maxi;
}


int main() {
    init_consonants("./consonants.txt");
    init_letters("./letters.txt");

    //FILE* infile = fopen("./in_local.txt", "r, ccs=UTF-8");
    //FILE* outfile = fopen("./out_local.txt", "w, ccs=UTF-8");
    
    int cnt = find_maximum_consonants("./in_local.txt");
    printf("%d\n", cnt);
}

