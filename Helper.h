//
// Created by andro on 8/18/2023.
//

#ifndef REGISTRATION_SYSTEM_V2_HELPER_H
#define REGISTRATION_SYSTEM_V2_HELPER_H
#include "./Characters/Person.h"
#include "iostream"
#include "string"
#include "vector"
#include <memory>

class Helper {
public:
    static int RunMenu(std::vector<std::string> &);
    static std::vector<std::string> parseLine(string &, char );
    static string makeEntity(std::vector<std::string> &,char);
};


#endif//REGISTRATION_SYSTEM_V2_HELPER_H
