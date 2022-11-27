//
// Created by Nataliia Gurova on 27.11.2022.
//

#ifndef C_VERSION_RULES_H
#define C_VERSION_RULES_H

#include <map>
#include <vector>
#include <string>

typedef std::map<std::string, std::string> rules_t;

class Rules
{
public:
    Rules(const std::vector<std::string> &from, const std::vector<std::string> &to);
    void print();

    int size;
    std::map<std::string, std::string> data;
};


#endif //C_VERSION_RULES_H
