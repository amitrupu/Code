#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

// finds max unique sub-string starting at start and return size
unsigned find_max_unique_stubstring(const char *str, unsigned start) {
    // create a table to hold char found and initialize with 0
    char char_table[256];
    memset(char_table, 0, 256);

    // iterate and stop if char repeats, i.e. found to be in char_table 
    int end;
    for (end = start; end < strlen(str); end++) {
        if (char_table[unsigned(str[end])])
            break;
        char_table[unsigned(str[end])] = 1;
    }
    return (end - start);
}

// find max of unique sub-strings starting from different index
unsigned find_max_unique_substring(const char *str, unsigned *start_index, bool last_max = false) {
    unsigned len = strlen(str);
    unsigned max_size = 0, start_for_max = 0;
    for (int start = 0; start < len - 1; start++) {
        unsigned size = find_max_unique_stubstring(str, start);
        if ((size + last_max) > max_size) {
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

// find max of unique sub-strings remembering earlier searches
unsigned find_max_unique_substring_fast(const char *str, unsigned *start_index, bool last_max = false) {
    unsigned len = strlen(str);
    unsigned max_size = 0, start_for_max = 0;
    // create a table to hold char found and initialize with 0
    char char_table[256];
    memset(char_table, 0, 256);

    // increment start index and find max sub-string from each start index
    for (int start = 0, end = 0; start < len - 1; start++) {
        if ((len - start) < max_size) // if remaining string is lesser than max size, no need to search further - opt 4 
            break;

        // remove char at previous start index from char_table - opt 1
        if (start > 0)
            char_table[unsigned(str[start-1])] = 0;

        // iterate and stop if char repeats, i.e. found to be in char_table 
        for (; end < strlen(str); end++) { // start checking from previous end - opt 2
            if (char_table[unsigned(str[end])])
                break;
            char_table[unsigned(str[end])] = 1;
        }
        unsigned size = end - start;

        // compare with max and update
        if ((size + last_max) > max_size) {
            max_size = size;
            start_for_max = start;
        }

        // if end reaches end of string, no need to search further - opt 3
        if (end == len)
            break;
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
    unsigned max_size = find_max_unique_substring_fast(str, &start_for_max);
    cout << "Max unique sub-string: size=" << max_size << ": ";
    printf("%.*s\n", max_size, str + start_for_max);
    return 0;
}