#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>

std::string path;


void bytescount(std::string(path)){

    std::ifstream f;
    f.open(path);

    std::streampos fsize = 0;

    f.seekg(0, f.end);
    fsize = f.tellg();
    std::cout << "Bytes: " << fsize << std::endl;
}

void wordscount(std::string(path)){
    std::ifstream f;
    f.open(path);
    int words = 0;
    std::string s;
    while (!f.eof()){
        f >> s;
        if (!s.empty()){
            words++;
        }
    }
    std::cout << "Words: " << words << std::endl;
}

void linecount(std::string(path)){

    std::ifstream f;
    f.open(path);

    std::string line;

    int lines = 0;
    while (getline(f, line)){
        lines++;
    }
    std::cout << "Lines: " << lines << std::endl;
}

int main(int argc, char* argv[]) {
    static struct option long_opt[] = {
            {"lines", 0, 0, 'l'},
            {"words", 0, 0, 'w'},
            {"bytes", 0, 0, 'c'},
            {0, 0, 0, 0}
    };

    if (argc == 2) {
        path = argv[1];
        linecount(path);
        wordscount(path);
        bytescount(path);
    }

    if (argc >=3){
        for (int j = 1; j < argc; j++){
            std::ifstream f;
            f.open(argv[j]);
            if (f.is_open()){
                path = argv[j];
            }
        }
        int c;
        int optIdx;
        while ((c = getopt_long(argc, argv, "lwc", long_opt, &optIdx)) != -1){
            switch (c) {
                case 'l':
                    linecount(path);
                    break;
                case 'w':
                    wordscount(path);
                    break;
                case 'c':
                    bytescount(path);
                    break;
            }

        }
    }
    return 0;
}