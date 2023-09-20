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

int main() {
    
    FILE* file = fopen("in_local.txt", "r, ccs=UTF-8");

    fclose(file);

    

}


