#include<stdio.h>


int is_good_symbol(wchar_t a) {
    // Apostroph 39 in UTF-8
    if (a == 38)
        return 1;
    // Big english letters 65 - 90 in UTF-8
    if (a >= 65 && a <= 90) 
        return 1;
    // Small english letters 97 - 122 in UTF-8
    if (a >= 97 && a <= 122)
        return 1;
    // Big and small cyrrilic letters 1040 - 1103 in UTF-8
    if (a >= 1040 && a <= 1103)
        return 1;
    // Big cyrrilic letters (І Ї) 1030 - 1031 in UTF-8
    if (a == 1030 || a == 1031)
        return 1;
    // Small cyrrilic letters (і ї) 1110 - 1111 in UTF-8
    if (a == 1110 || a == 1111)
        return 1;
    return 0;
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
    FILE* file = fopen("in_local.txt", "r, ccs=UTF-8");

    wchar_t word[31];

    int it = 0;

    while (1) {
        
    }
}

