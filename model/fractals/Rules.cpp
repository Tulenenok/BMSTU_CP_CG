//
// Created by Nataliia Gurova on 27.11.2022.
//

#include "Rules.h"
#include <iostream>

Rules::Rules(const std::vector<char> &from, const std::vector<std::string> &to)
{
    this->size = (int)from.size();

    for (int i = 0; i < this->size; ++i)
        this->data[from[i]] = to[i];
}

void Rules::print() {
    std::cout << "Rules:\n";

    auto it = this->data.begin();
    for (int i = 0; it != this->data.end(); it++, i++)
    {
        std::cout << i << ") Ключ " << it->first << ", значение " << it->second << std::endl;
    }
}
