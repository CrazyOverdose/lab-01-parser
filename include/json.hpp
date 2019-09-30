//
// Created by absinthetoxin on 23.09.2019.
//

#ifndef UNTITLED2_JSON_H
#define UNTITLED2_JSON_H

#include <any>
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

class Json
{

public:

    unordered_multimap <string, any> obj; // для объекта
    unordered_multimap <int, any> obj2; // для массива



    // Конструктор из строки, содержащей Json-данные.
    Json(std::string s);

    //// Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool is_array() const;

    //// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object() const;

    //// Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
    //// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    //// Если экземпляр является JSON-массивом, генерируется исключение.
    std::any operator[](const std::string& key);

    //// Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
    //// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    //// Если экземпляр является JSON-объектом, генерируется исключение.
    std::any operator[](int index);

    //// Метод возвращает объект класса Json из строки, содержащей Json-данные.
    Json parse(const std::string& s);

    //// Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
    Json parseFile(const std::string path_to_file);
};



#endif //UNTITLED2_JSON_H
