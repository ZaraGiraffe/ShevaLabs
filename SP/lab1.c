#include<stdio.h>



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



void get_next_word(FILE* file, wchar_t* word, int word_length) {
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
        if (pos == word_length - 1) {
            word[pos] = 0;
            break;
        }
        ch = fgetwc(file);
    }
}


int main() {
    init_consonants("./consonants.txt");
    init_letters("./letters.txt");

    //FILE* infile = fopen("./letters.txt", "r, ccs=UTF-8");
    //FILE* outfile = fopen("./letters.txt", "r, ccs=UTF-8");
    
}

