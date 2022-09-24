#include <iostream>
#include <fstream>
#include <string>

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
        for (int i=1; i<argc; i++){
            if (argv[i][0] == '-'){
                if (std::string (argv[i]) == "-c" or std::string (argv[i]) == "--bytes"){
                    bytescount(path);
                }
                if (std::string (argv[i]) == "-l" || std::string (argv[i]) == "--lines"){
                    linecount(path);
                }
                if (std::string (argv[i]) == "-w" || std::string (argv[i]) == "--words"){
                    wordscount(path);
                }
                if (std::string (argv[i]) == "-cl" || std::string (argv[i]) == "-lc") {
                    linecount(path);
                    bytescount(path);
                }
                if (std::string (argv[i]) == "-cw" || std::string (argv[i]) == "-wc") {
                    wordscount(path);
                    bytescount(path);
                }
                if (std::string (argv[i]) == "-lw" || std::string (argv[i]) == "-wl"){
                    linecount(path);
                    wordscount(path);
                }
                if (std::string (argv[i]) == "-clw" || std::string (argv[i]) == "-cwl" || std::string (argv[i]) == "-lcw"){
                    linecount(path);
                    wordscount(path);
                    bytescount(path);
                }
                if (std::string (argv[i]) == "-lwc" || std::string (argv[i]) == "-wlc" || std::string (argv[i]) == "-wcl"){
                    linecount(path);
                    wordscount(path);
                    bytescount(path);
                }
            }
        }
    }
    return 0;
}