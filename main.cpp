#include <iostream>
#include <fstream>
using namespace std;

char* msgTable[] = {"Number of lines: ", "Size of file (bytes): ", "Number of words: ", "Number of chars:", "Unknown key ", "Invalid key letter ", " in ", "WordCount help\n\nWordCount [Options] <filename> [filename2 filename3 ...]\n\nOptions:\n\n   -l, --lines - display number of lines in file\n\n   -c, --bytes - display size of file in bytes\n\n   -w, --words - display number of words in file\n\n   -m, --chars - display number of chars in file\n\n   If none of the above keys is passed, all information about the file will be displayed\n\n   -h, --help - display this message\n", "Unable to open file", "One or more keys were passed more then once"};

bool interruptOnNonCriticalErrors = 0;
bool enableHelp = 1;

int main(int argc, char* argv[]) {
    short lines = 0, bytes = 0, words = 0, chars = 0, help = 0;
    bool invalidKeyPassed = 0;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-') {
                if (strcmp(argv[i], "--lines") == 0)
                    ++lines;
                else if (strcmp(argv[i], "--bytes") == 0)
                    ++bytes;
                else if (strcmp(argv[i], "--words") == 0)
                    ++words;
                else if (strcmp(argv[i], "--chars") == 0)
                    ++chars;
                else if (strcmp(argv[i], "--help") == 0)
                    ++help;
                else {
                    invalidKeyPassed = 1;
                    cout << msgTable[4] << '"' << argv[i] << "\"\n";
                }

            }
            else {
                for (int j = 1; j < strlen(argv[i]); ++j) {
                    if (argv[i][j] == 'l')
                        ++lines;
                    else if (argv[i][j] == 'c')
                        ++bytes;
                    else if (argv[i][j] == 'w')
                        ++words;
                    else if (argv[i][j] == 'm')
                        ++chars;
                    else if (argv[i][j] == 'h')
                        ++help;
                    else {
                        invalidKeyPassed = 1;
                        cout << msgTable[5] << argv[i][j] << msgTable[6] << argv[i] << '\n';
                    }
                }
            }
        }
    }

    if ((lines > 1) || (bytes > 1) || (words > 1) || (chars > 1) || (help > 1)) {
        cout << msgTable[9] << '\n';
        if (interruptOnNonCriticalErrors)
            return 0;
    }

    if (interruptOnNonCriticalErrors && invalidKeyPassed)
        return 0;

    bool invalidHelpKey = 0;

    if (!((lines || bytes) || (words || chars))) {
        lines = 1;
        bytes = 1;
        words = 1;
        chars = 1;
    }

    if (help)
        cout << '\n' << msgTable[7];

    ifstream file, bFile;
    int lineCount, byteCount, wordCount, charCount;
    unsigned char symbol;
    bool inWord = 0, isChar;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-')
            continue;
        lineCount = 0;
        byteCount = -1;
        wordCount = 0;
        charCount = 0;
        symbol = '\0';

        cout << '\n' << argv[i] << '\n';

        bFile.open(argv[i], ios::binary);
        if (bFile.fail()) {
            cout << msgTable[8] << '\n';
            if (!interruptOnNonCriticalErrors)
                continue;
            else
                return 0;
        }
        while (!bFile.eof()) {
            bFile.get();
            ++byteCount;
        }
        bFile.close();

        file.open(argv[i]);
        while (file >> std::noskipws >> symbol) {
            lineCount += (symbol == '\n');
            isChar = ((('!' <= symbol) && (symbol <= '~')) || (((unsigned char)'�' <= symbol) && (symbol <= (unsigned char)'�')) || (((unsigned char)'�' <= symbol) && (symbol <= (unsigned char)'�')));
            if (isChar) {
                ++charCount;
                if (!inWord)
                    ++wordCount;
                    inWord = 1;
            }
            else
                inWord = 0;
            
        }
        lineCount += ((symbol != '\n') && (symbol != '\0'));
        file.close();
        if (lines)
            cout << msgTable[0] << lineCount << '\n';
        if (bytes)
            cout << msgTable[1] << byteCount << '\n';
        if (words)
            cout << msgTable[2] << wordCount << '\n';
        if (chars)
            cout << msgTable[3] << charCount << '\n';
    }
    return 0;
}