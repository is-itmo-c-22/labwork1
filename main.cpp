#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

void show_usage(std::string argv0) { //сообщение об ошибке
    std::cerr << "Usage: " << argv0 << " <option(s)> SOURCES\n"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << std::endl;
}

int line_count(std::string fileName){
    std::string line;
    std::ifstream file;
    int i = 0;
    file.open(fileName); // окрываем файл для чтения C:\TestText.txt
    if (file.is_open()) {
        while (getline(file, line)) { //пока есть строки
            i++;
        }
    } else {
        std::cout << "file not found" << std::endl;
    }
    file.close();     // закрываем файл
    return i;
}

int byte_count(std::string fileName){
    std::filesystem::path p{fileName};
    return std::filesystem::file_size(p);
}

int word_count(std::string fileName){
    std::string line;
    std::ifstream file;
    int i = 0; //счетчик
    file.open(fileName); // окрываем файл для чтения C:\TestText.txt
    if (file.is_open()) {
        for (std::string line, word; std::getline(file, line); ){
            std::istringstream iss(line);

            while (iss >> word){
                bool alpha = true;

                for (char c : word) // словами считаем только набор буквенных символов
                    if (!std::isalpha(c)) alpha = false; //проверяем на то, что состоит только из букв

                if (alpha) ++i;
            }
        }
    } else {
        std::cout << "file not found" << std::endl;
    }
    file.close();     // закрываем файл
    return i;
}

int char_count (std::string fileName) {
    std::string line;
    std::ifstream file;
    int k = 0;
    file.open(fileName); // окрываем файл для чтения C:\TestText.txt
    if (file.is_open()) {
        while (getline(file, line)) {
            for (int i = 0; i < line.length(); i++) {
                if (isalpha((unsigned char)line[i])) { //буквами считаем только БУКВЫ
                    k++;
                }
            }
        }
    } else {
        std::cout << "file not found" << std::endl;
    }
    return k;
}




int main(int argc, char* argv[]){
    std::ifstream file;
    if (argc < 2) { //проверяем на наличие аргументов
        show_usage(argv[0]);
        return 1;
    }
    bool flagl = false; //флаги для функционала
    bool flagc = false;
    bool flagw = false;
    bool flagm = false;
    bool flagh = false;
    bool flagall = true;
    std::vector <std::string> fileBar; // массив для файлов
    for(int i = 1; i<argc; i++) {
        std::string buf = argv[i];
        if (buf[0] == '-' and buf[1] != '-') {
            flagall = false;
            if (buf.find('l') != std::string::npos) {
                flagl = true;
            }
            if (buf.find('c') != std::string::npos) {
                flagc = true;
            }
            if (buf.find('w') != std::string::npos) {
                flagw = true;
            }
            if (buf.find('m') != std::string::npos) {
                flagm = true;
            }
            if (buf.find('h') != std::string::npos) {
                flagh = true;
            }
        } else if (buf[0] == '-' and buf[1] == '-') {
            flagall = false;
            if (buf.find("lines") != std::string::npos) {
                flagl = true;
            }
            if (buf.find("bytes") != std::string::npos) {
                flagc = true;
            }
            if (buf.find("words") != std::string::npos) {
                flagw = true;
            }
            if (buf.find("chars") != std::string::npos) {
                flagm = true;
            }
            if (buf.find("help") != std::string::npos) {
                flagh = true;
            }

        } else {
            fileBar.emplace_back(argv[i]);
        }
    }
    if (flagh){
        std::cerr << "Help:"
                  << "\tEnter the full path to the file and: \n"
                  << "\t-l or --lines to count the number of lines\n"
                  << "\t-c or --bytes to count the number of bytes\n"
                  << "\t-w or --words to count the number of words\n"
                  << "\t-m or --chars to count the number of letters"
                  << std::endl;
    }
    for (int h = 0; h<fileBar.size(); h++){
        std::string fileNameBuf = fileBar[h];
        std::cout << "Work with: " << fileNameBuf << std::endl;
        if (flagl or flagall){
            std::cout << line_count(fileNameBuf) << " - number of lines in "<< fileNameBuf << std::endl;
        }
        if (flagc or flagall){
            std::cout << byte_count(fileNameBuf) << " - number of bytes in "<< fileNameBuf << std::endl;
        }
        if (flagw or flagall){
            std::cout << word_count(fileNameBuf) << " - number of words in "<< fileNameBuf << std::endl;
        }
        if (flagm or flagall){
            std::cout << char_count(fileNameBuf) << " - number of chars in "<< fileNameBuf << std::endl;
        }
    }
    return 0;
}