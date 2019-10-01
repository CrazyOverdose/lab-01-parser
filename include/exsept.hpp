//
// Created by absinthetoxin on 30.09.2019.
//

#ifndef JSON_EXSEPT_H
#define JSON_EXSEPT_H

#include </home/absinthetoxin/CrazyOverdose/lab01/lab-01-parser/include/json.hpp>
#include <exception>

class Except : public exception
{
public:
    const char*what() const noexcept
    {
        return "Error: Wrong input\n";
    }
};

#endif //JSON_EXSEPT_H
