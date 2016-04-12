#include "research_bst.h"

research::research()
{
    initialize();
}

research::~research()
{
    nukem();
}

research::research(const research& other)
{
    initialize();
    copy(other);
}

research& research::operator=(const research& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

ostream& research::saveSummaryPage(ostream& out)
{
    ////////////////////////////////
    return out;
}

void research::loadfile(bst<string>& tree, char *filename)
{
    if(fileExists(filename))
    {
        ifstream myfile;
        myfile.open(filename);
        if(myfile.is_open())
        {
            //LOGIC HERE
            myfile.close();
        }
    }
    else
    {
        cout << "Error, the specified file does not exist." << endl;
    }
}

void research::traceText()
{

}

void research::checkSentence(char* c)
{

}

void research::checkParas(char* c)
{

}

void research::checkWord(char* c)
{

}

void research::checkSyllable(char* c)
{

}





ostream& research::saveToFile(ostream& out)
{
    showMenu(out);
}

ostream& research::showMenu(ostream& out)
{
    string title[9] = {
        " Please make a selection to save in the file: ",
        "  0. Save whole summary page",
        "  1. Save words count",
        "  2. Save paragraphs count",
        "  3. Save reading level",
        "  4. Save 10 most frequently words",
        "  5. Save words count in 26 order",
        "  6. Save total process time",
        " Your selection:\n"};
    system("cls");
    for(int i = 0; i < 9; ++i)
        out << title[i] << endl;
    return out;
}

ostream& research::saveWordsCount(ostream& out)
{
    out << "words count: " << wordsCount << endl;
    return out;
}

ostream& research::saveParasCount(ostream& out)
{
    out << "paragraphs count: " << parasCount << endl;
    return out;
}

ostream& research::saveReadingLevel(ostream& out)
{
    out << "reading level: " << readingLevel << endl;
    return out;
}

ostream& research::saveTenMostWords(ostream& out)
{
    /////////////////////////////////////////////////
    return out;
}

ostream& research::saveWordsCount_alphabet(ostream& out)
{
    /////////////////////////////////////////////////
    return out;
}

ostream& research::saveTotalTime(ostream& out)
{
    out << "process time: " << std::setprecision(2) << time/1000.0 << " sec" << endl;
    return out;
}

bool research::fileExists(char* filename)
{
    fstream f;
    f.open(filename);
    return f.is_open();
}

void research::copy(const research& other)
{
    wordsCount = other.wordsCount;
    parasCount = other.parasCount;
    linesCount = other.linesCount;
    sentencesCount = other.sentencesCount;
    syllablesCount = other.syllablesCount;
    readingLevel = other.readingLevel;
    time = other.time;
    tree = other.tree;

    for(size_t i = 0; i < LETTERS; ++i)
        *(alphabet + i) = *(other.alphabet + i);

    for(size_t i = 0; i < MOST; ++i)
        *(tenMostWords + i) = *(other.tenMostWords + i);

    fileName = other.fileName;
    text = other.text;

}

void research::nukem()
{
    wordsCount = parasCount = linesCount = sentencesCount = syllablesCount = readingLevel = time = size_t();
    fileName = text = NULL;

    for(size_t i = 0; i < LETTERS; ++i)
        delete (alphabet + i);
    delete[] alphabet;

    for(size_t i = 0; i < MOST; ++i)
        delete (tenMostWords + i);
    delete[] tenMostWords;
}

void research::initialize()
{
    wordsCount = linesCount = parasCount = sentencesCount = syllablesCount = readingLevel = time = 0;
    alphabet = new size_t[LETTERS];
    tenMostWords = new size_t[MOST];
    tree = bst<std::string>(IN_ORDER);
    fileName = text = NULL;

    whatToDo[0] = &research::saveSummaryPage;
    whatToDo[1] = &research::saveWordsCount;
    whatToDo[2] = &research::saveParasCount;
    whatToDo[3] = &research::saveReadingLevel;
    whatToDo[4] = &research::saveTenMostWords;
    whatToDo[5] = &research::saveWordsCount_alphabet;
    whatToDo[6] = &research::saveTotalTime;
}
