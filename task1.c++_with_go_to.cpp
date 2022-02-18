#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
int main() {
    string inputString = "";
    int count2 = 0;
    int count1 = 0;
    const int IGNORED = 3;
    string currLine;
    ifstream data ("example.txt");
    if (data.is_open()){
        readLine:
        inputString += currLine + " ";
        if(getline (data, currLine)) {
            goto readLine;
        }
        data.close();
    }
       int symbol = 0;
    int wordCount = 0;
    wordCounter:
    if(inputString[symbol++] == ' ') {
        wordCount++;
    }
    if(symbol < inputString.length()) {
        goto wordCounter;
    }

    int currWord = 0;
    symbol = 0;
    string words[wordCount];
    int currLength = 0;

    getWord:
    if(inputString[symbol] == ' ' && words[currWord] != "") {
        if(IGNORED >= currLength) {
            words[currWord] = "";
            symbol++;
            currLength = 0;
            goto getWord;
        }
        currLength = 0;
        currWord++;
    }
    if(65 <= inputString[symbol] + 0 && 90 >= inputString[symbol] + 0) {
        words[currWord] += inputString[symbol] + 32;
        currLength++;
    } else if (97 <= inputString[symbol] + 0 && 122 >= inputString[symbol] + 0) {
        words[currWord] += inputString[symbol];
        currLength++;
    }
    symbol++;
    if(symbol < inputString.length()) {
        goto getWord;
    }

    string newWords[currWord];
    int counters[currWord];
    bool exist;
    int top = 0;
    int index = 0;

    count:
    count2 = 0;
    exist = false;

    finder:
    if(count2 < top){
        if(words[count1].length() != newWords[count2].length()){
            count2++;
            goto finder;
        }
        comparator:
        if(words[count1][index] != newWords[count2][index]) {
            count2++;
            index = 0;
            goto finder;
        }
        index++;
        if(index < words[count1].length()) {
            goto comparator;
        }
        index = 0;
        exist = true;
    }
    
    if(exist) {
        counters[count2]++;
    } else {
        newWords[top] = words[count1];
        counters[top] = 1;
        top++;
    }
    count1++;
    if(count1 < currWord) {
        goto count;
    }
    const int outputListSize = top <= 25 ? top : 25;
    string topWords[outputListSize];
    int topCount[outputListSize];
    index = 0;
    
    generateTop:
    count1 = 0;
    count2 = 0;
    currWord = -1;

    getCurrMax:
    if(count2 < counters[count1]){
        count2 = counters[count1];
        currWord = count1;
    }

    count1++;

    if(count1 < top) {
        goto getCurrMax;
    }
    topWords[index] = newWords[currWord];
    topCount[index] = counters[currWord];
    counters[currWord] = -1;
    index++;
    if(index < outputListSize) {
        goto generateTop;
    }


    index = 0;
    output:
    printf("%s:%d",topWords[index].c_str(), topCount[index]);
    index++;
    if(index < outputListSize) {
        printf("\n");
        goto output;
    }
    getch();


    return 0;
}

