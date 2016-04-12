#include "drive.h"

void summaryPage()
{

}

void loadfile(bst<string>& tree, char *filename)
{
    ifstream in;
    in.open(filename);
    if(in.fail())
    {
       in.close();
       throw 404;
    }
    while(in>>one);
}

void saveToFile()
{

}

int wordsCount()
{

}

int parasCount()
{

}

int sentencesCount()
{

}

int syllablesCount()
{

}

int readingLevel()
{

}

void tenMostWords()
{

}

void wordsCount_alphabet()
{

}

int totalTime()
{

}
