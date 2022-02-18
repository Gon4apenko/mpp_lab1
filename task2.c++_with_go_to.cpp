#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string inputString = "";
    int count2 = 0;
    int count1 = 0;
    const int IGNORED = 3;
    string currLine;
    ifstream data ("example.txt");
    if (data.is_open()){
        readLine:
        inputString += currLine + "\n";
        if(std::basic_istream::getline (data, currLine)) {
            goto readLine;
        }
        data.close();
    }
    int pagesCount = 0;
    int words = 0;
    const int LIMIT = 100;
    const int LINE_PER_PAGE = 45;
    int symbol = 0;

    wordCounter:
    if(inputString[symbol] == ' ') {
        words++;
    }
    if(inputString[symbol] == '\n') {
        count1++;
        words++;
    }
    symbol++;

    if(symbol < inputString.length()) {
        goto wordCounter;
    }

    pagesCount = count1 / LINE_PER_PAGE;
    pagesCount++;
    words++;

    string pages[pagesCount][words];
    string allWords[words];

    int size = 0;
    int count = 0;
    bool exist = false;
    int lineCount = 0;
    int row = 0;
    int column = 0;
    symbol = 0;
    int length = 0;

    getWord:

    if(lineCount == LINE_PER_PAGE) {
        row++;
        lineCount = 0;
        column = 0;
    }
    
    if(inputString[symbol] == '\n') {
        count2 = 0;
        lineCount++;
        count = 0;
        exist = false;
        checkExist:
        if(IGNORED >= length) {
            pages[row][column] = "";
            symbol++;
            goto getWord;
        }
        if(allWords[count] == pages[row][column] && count < size) {
            exist = true;
        }
        count++;
        if(count < size) {
            goto checkExist;
        }

        if(!exist && pages[row][column] != "") {
            allWords[size++] = pages[row][column];
        }
        column++;
    } else if(inputString[symbol] == ' ') {
        count2 = 0;
        if(IGNORED >= length) {
            pages[row][column] = "";
            symbol++;
            goto getWord;
        }
        count = -1;
        exist = false;
        checkExist2:
        count++;
        if(allWords[count]== pages[row][column] && count < size) {
            exist = true;
            count = size;
        }
        if(count < size) {
            goto checkExist2;
        }
        if(!exist && pages[row][column] != "") {
            allWords[size++] = pages[row][column];
        }
       column++;

    } else if(65 <= inputString[symbol] + 0 && 90 >= inputString[symbol] + 0) {

        pages[row][column] += inputString[symbol] + 32;
        length++;

    } else if (97 <= inputString[symbol] + 0 && 122 >= inputString[symbol] + 0) {

        pages[row][column] += inputString[symbol];
        length++;

    }

    symbol++;

    if(symbol < inputString.length()) {
        goto getWord;
    }
    
    count = 0;
    count2 = size;
    string pick = allWords[size-1];
    
    bubblesort:
    
    pick = allWords[size-1];
    count2 = size-2;
    
    lifting:
    
    if(count2 >= 0 && allWords[count2] > pick) {
        allWords[count2 + 1] = allWords[count2];
    } else if(count2 >= 0) {
        allWords[count2+1] = pick;
        pick = allWords[count2];
    }
    
    count2--;
    
    if(count2 >= count) {
        goto lifting;
    }
    
    if(count2 >= -1) {
       allWords[count2+1] = pick; 
    }
    
    count++;
    
    if(count < size){
        goto bubblesort;
    }

    row = 0;
    int wordNote[words][LIMIT];
    int index = 0;
    
    pickWord:
    
    count = 0;
    column = 0;

    getPage:
    
    index = 0;

    searchWord:
    
    if(pages[count][index] == allWords[row]) {
        wordNote[row][column] = count + 1;
        column++;
        goto skip;
    }

    index++;
    if(index < words) {
        goto searchWord;
    }
    skip:
    count++;

    if(count < pagesCount && column < LIMIT) {
        goto getPage;
    }
    
    if(column < LIMIT) {
        wordNote[row][column] = -1;
    }

    row++;

    if(row < size) {
        goto pickWord;
    }

    row = 0;

    printWord:
    column = 0;
    pick = "";

    printPages:
    if(wordNote[row][column] > 0 && column < LIMIT) {
        pick += to_string(wordNote[row][column]);
        if(column != 0) {
            pick += ", ";
        }
        column++;
        goto printPages;
    }

    printf("%s:%s",allWords[row].c_str(), pick.c_str());
    row++;
    if(row < size) {
        printf("\n");
        goto printWord;
    }


    return 0;
}