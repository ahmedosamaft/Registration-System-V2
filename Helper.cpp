//
// Created by andro on 8/18/2023.
//

#include "Helper.h"
#include <fstream>

int Helper::RunMenu(std::vector<std::string> &menu) {
    std::cout << "Please make a choice:\n";
    for (int i = 0; i < menu.size(); ++i) {
        std::cout << i + 1 << " - " << menu[i] << std::endl;
    }
    std::cout << "Choice >> ";
    int choose;
    std::cin >> choose;
    return choose;
}

std::vector<std::string> Helper::parseLine(string &line, char delimiter) {
    std::vector<std::string> parsed;
    // To add last word!
    line += delimiter;
    std::string word;
    for (const auto &ch: line)
        if (ch == delimiter) {
            if (!word.empty())
                parsed.push_back(word);
            word.clear();
        } else
            word.push_back(ch);

    return parsed;
}

std::string Helper::makeEntity(std::vector<std::string> &attributes,char delimiter){
    std::string line;
    for (int i = 0; i < attributes.size() - 1; ++i) {
        line += attributes[i] + delimiter;
    }
    line += attributes.back();
    return line;
}

