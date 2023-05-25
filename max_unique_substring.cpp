#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

// finds max unique sub-string starting at start and return size
unsigned find_max_unique_stubstring_from_index(const char *str, unsigned start) {
    // create a table to hold char found and initialize with 0
    char char_table[256];
    memset(char_table, 0, 256);

    // iterate and stop if char repeats, i.e. found to be in char_table 
    int end;
    for (end = start; end < strlen(str); end++) {
        if (char_table[str[end]])
            break;
        char_table[str[end]] = 1;
    }
    return (end - start);
}

// find max of unique sub-strings starting from different index
unsigned find_max_unique_substring(const char *str, unsigned *start_index, bool last_max = false) {
    unsigned len = strlen(str);
    unsigned max_size = 0, start_for_max = 0;
    for (int start = 0; start < len - 1; start++) {
        unsigned size = find_max_unique_stubstring_from_index(str, start);
        if (size + last_max> max_size) {
            max_size = size;
            start_for_max = start;
            // if the search reached end of string, no need for further search
            if (start_for_max + max_size == len)
                break;
        }
    }
    if (start_index)
        *start_index = start_for_max;
    return max_size;
}

int main() {
    char str[1000];
    cout << "Enter string: ";
    cin >> str;
    unsigned start_for_max;
    unsigned max_size = find_max_unique_substring(str, &start_for_max);
    cout << "Max unique sub-string: size=" << max_size << ": ";
    printf("%.*s\n", max_size, str + start_for_max);
    return 0;
}