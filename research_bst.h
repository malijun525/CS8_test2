#ifndef RESEARCH
#define RESEARCH

#include "bst.h"

const size_t LETTERS = 26, MOST = 10;

class research
{
public:
    typedef ostream& (research::*fptr1)(ostream&);
    research();
    ~research();
    research(const research& other);
    research& operator=(const research& other);

    void loadfile(bst<string>& tree, char *filename);
    ostream& saveToFile(ostream& out);
    ostream& showMenu(ostream& out);

private:
    size_t wordsCount, parasCount, sentencesCount, linesCount, syllablesCount, readingLevel, time;
    size_t *alphabet, *tenMostWords;
    bst<string> tree;
    char* fileName;
    char* text;
    fptr1 whatToDo[7];

    void traceText();
    void checkSentence(char* c);
    void checkParas(char* c);
    void checkWord(char* c);
    void checkSyllable(char* c);

    void insertWord();


    ostream& saveSummaryPage(ostream& out);
    ostream& saveWordsCount(ostream& out);
    ostream& saveParasCount(ostream& out);
    ostream& saveReadingLevel(ostream& out);
    ostream& saveTenMostWords(ostream& out);
    ostream& saveWordsCount_alphabet(ostream& out);
    ostream& saveTotalTime(ostream& out);

    bool fileExists(char* filename);
    void copy(const research& other);
    void nukem();
    void initialize();

};



#endif // RESEARCH

