#include <iostream>
#include <cstring>
using namespace std;
void swap(char *str, int i, int j) {
    char t = str[i];
    str[i] = str[j];
    str[j] = t;
}
void moveWord(char *str, int start, int stop, int to) {
    // scenario: start and stop is < to
    int from = start;
    while (to < start) {
        swap(str, to++, from);
        if (from == stop)
            from = start;
        else
            from++;
    }
    // to == start, bubble sort
    while (from > start && from <= stop) {
        for (int j = from; j > to; j--)
            swap(str, j, j-1);
        to++;
        from++;
    }
    // scenario: to > stop
    if (to > stop+1)
        moveWord(str, stop+1, to-1, start);
}
bool compareWord(char *word1, char *word2) {
    while (*word2 != 0 && *word2 != 0
            && *word2 != ' ' && *word2 != ' ') {
        if (*word1 < *word2)
            return true;
        else if (*word1 > *word2)
            return false;
        word1++;
        word2++;
    }
    if (*word2 != ' ')
        return true;
    return false;
}
int findWord(char *str, int i) {
    while (str[i] != 0 && str[i] == ' ')
        i++;
    return i;
}
int findSpace(char *str, int i) {
    while (str[i] != 0 && str[i] != ' ')
        i++;
    return i;
}
void sortWords(char *str) {
    int word1Start = findWord(str, 0);
    while (word1Start >= 0 && str[word1Start] != 0) {
        int word1Stop = findSpace(str, word1Start);
        if (str[word1Stop] == 0)
            word1Stop--;
        else {
            int word2Start = findWord(str, word1Stop);
            while (word2Start != 0 && str[word2Start] != 0) {
                int word2Stop = findSpace(str, word2Start);
                int word3Start = 0;
                if (str[word2Stop] == 0)
                    word2Stop--;
                else {
                    word3Start = findWord(str, word2Stop);
                }
                if (compareWord(str+word2Start, str+word1Start))
                    moveWord(str, word2Start, word2Stop, word1Start);
                word2Start = word3Start;
                word1Stop = findSpace(str, word1Start);
                if (str[word1Stop] == 0)
                    word1Stop--;
            }
        }
        word1Stop = findSpace(str, word1Stop); 
        if (str[word1Stop] == 0)
            word1Start = -1;     
        else
            word1Start = findWord(str, word1Stop+1); 
    }
}

int main() {
#if 0
    char str[1000] = "i am Amit Roy Hello World ";
    // moveWord(str, 14, 19, 5);
    // moveWord(str, 5, 9, 20);
#endif
    cout << "Enter string: ";
    string str;
    getline(cin, str);
    char buffer[1000];
    strcpy(buffer, str.c_str());
    sortWords(buffer);
    cout << buffer << endl;
    return 0;
}