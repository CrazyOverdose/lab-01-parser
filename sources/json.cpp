//
// Created by absinthetoxin on 24.09.2019.
//
#include "json.hpp"
#include <any>
#include "exsept.hpp"
#include <string>
#include <vector>

using namespace std;

Json::Json(std::string s) {
    vector<string> array;
    bool flag = false;  //для { и [
    int exs = 0;
    for (long unsigned int i = 0; i < s.size(); i++) {
        int ch1 = 0, ch2 = 0; // ch1 - счётчик {}, ch2 - []
        if (s[i] == '{' && flag == false && exs == 0) {
            string a = s.substr(i, 1);
            array.push_back(a);
            flag = true;
            exs++;
            continue;
        }

        if (s[i] == '[' && flag == false && exs == 0) {
            string a = s.substr(i, 1);
            array.push_back(a);
            flag = true;
            exs++;
            continue;
        }

        if (s[i] == '"' ) {
            if (exs != 1)
            { if (exs != 3) {
                Except();
                exit (17);
            }}

            int h = i + 1;
            while (s[h] != '"') {
                h++;
            }
            string a = s.substr(i, h - i+1);
            array.push_back(a);
            i = h;
            exs++;
            continue;

        }

        if (s[i] == ':' && exs == 2) {
            string a = s.substr(i, 1);
            array.push_back(a);
            exs++;
            continue;
        }

        if (s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' ||
            s[i] == '8' || s[i] == '9') {

            if (exs != 1)
            { if (exs != 3) {
                    Except();
                    exit (17);
                }}
            int h=i;
            int kol=0;
            while (s[h] != ',' && s[h] != ' ' && s[h] != ']' && s[h] != '}') {
                h++;
                if(s[h]=='.')
                {
                    kol++;
                    if (kol > 1)
                    {
                        Except();
                        exit(17);
                    }
                }
            }
            string a = s.substr(i, h - i);
            array.push_back(a);
            i = h-1;
            exs++;
            continue;
        }

        if (s[i] == 'f' && s[i + 1] == 'a' && s[i + 2] == 'l' && s[i + 3] == 's' && s[i + 4] == 'e' && (exs == 3 || exs == 1)) {

            string a = s.substr(i, 5);
            array.push_back(a);
            i = i + 4;
            exs++;
            continue;
        }
        if (s[i] == 't' && s[i + 1] == 'r' && s[i + 2] == 'u' && s[i + 3] == 'e' && (exs == 3 || exs == 1)) {

            string a = s.substr(i, 4);
            array.push_back(a);
            i = i + 3;
            exs++;
            continue;
        }

        if (s[i] == '{' && flag == true && (exs == 3 || exs == 1)) {
            ch1++;
            for (long unsigned int j = i+1; j < s.length(); j++) {
                if (s[j] == '}') {
                    ch1--;
                }
                if (s[j] == '}' && ch1 == 0) {
                    string a = s.substr(i, j - i+1);
                    array.push_back(a);
                    i = j;
                    break;
                }

                if (s[j] == '{') {
                    ch1++;
                }
            }
            exs++;
            continue;
        }

        if (s[i] == '[' && flag == true && (exs == 3 || exs == 1 )) {
            ch2++;
            for (long unsigned int j = i+1; j < s.length(); j++) {

                if (s[j] == ']') {
                    ch2--;
                }

                if (s[j] == ']' && ch2 == 0) {
                    string a = s.substr(i, j - i+1);
                    array.push_back(a);
                    i = j;
                    break;
                }

                if (s[j] == '[') {
                    ch2++;
                }
            }
            exs++;
            continue;
        }
        if (s[i] == '}' && i == s.length() - 1) {
            string a = s.substr(i, 1);
            array.push_back(a);
            continue;
        }

        if (s[i] == ']' && i == s.length() - 1) {
            string a = s.substr(i, 1);
            array.push_back(a);
            continue;
        }
        if (s[i] == ',' && (exs == 4 || exs == 2)){
            string a = s.substr(i, 1);
            array.push_back(a);
            exs = 1;
            continue;
        }

        if (s[i] == ' ')
        {
            continue;
        }
        else
        {
            Except();
            exit (17);
        }

    }

    string a;
    for (long unsigned int l = 1; l < array.size(); l++)
    {
        a = array[0];

        if (a == "{") {
            for (vector <string>::iterator p = array.begin(); p != array.end(); ++p) {
                if (*p == "," || *p == "}" || *p == ":" ) {
                    if (p != array.begin())
                        array.erase(p--);
                    else {
                        array.erase(p);
                        p = array.begin();
                    }
                }
            }

            for (long unsigned int i = 1; i < array.size(); i++)
            {
                string key = array[i];

                key.erase(key.find('"'), 1);
                key.erase(key.find('"'), 1);

                i++;

                string value = array[i];

                if (value[0] == '"')
                {
                    value.erase(value.find('"'), 1);
                    value.erase(value.find('"'), 1);
                    any val = value;
                    obj.insert({ key, val });
                    l = i;
                    continue;
                }

                if (value[0] == 'f')
                {
                    bool val2 = false;
                    any val = val2;
                    obj.insert({ key, val });
                    l = i;
                    continue;
                }

                if (value[0] == 't')
                {
                    bool val2 = true;
                    any val = val2;
                    obj.insert({ key, val });
                    l = i;
                    continue;
                }

                if (value[0] == '[' || value[0] == '{')
                {
                    Json my(value);
                    any val = my;
                    obj.insert({ key, val });
                    l = i;
                    continue;
                }

                else
                {
                    double val2 = stod(value);
                    any val = val2;
                    obj.insert({ key, val });
                    l = i;
                }

            }
        }

        if (a == "[")
        {
            for (vector <string>::iterator p = array.begin(); p != array.end(); ++p) {
                if (*p == "," || *p == "]") {
                    if (p != array.begin())
                        array.erase(p--);
                    else {
                        array.erase(p);
                        p = array.begin();
                    }
                }
            }
            int chet = 0;
            for (long unsigned int i = 1; i < array.size(); i++)
            {
                string value = array[i];

                if (value[0] == '"')
                {
                    value.erase(value.find('"'), 1);
                    value.erase(value.find('"'), 1);
                    any val = value;
                    obj2.insert({ chet, val });
                    l = i;
                    chet++;
                    continue;
                }

                if (value[0] == 'f')
                {
                    bool val2 = false;
                    any val = val2;
                    obj2.insert({ chet, val });
                    l = i;
                    chet++;
                    continue;
                }

                if (value[0] == 't')
                {
                    bool val2 = true;
                    any val = val2;
                    obj2.insert({ chet, val });
                    l = i;
                    chet++;
                    continue;
                }

                if (value[0] == '[' || value[0] == '{')
                {
                    Json my(value);
                    any val = my;
                    obj2.insert({ chet, val });
                    l = i;
                    chet++;
                    continue;
                }

                else
                {
                    double val2 = stod(value);
                    any val = val2;
                    obj2.insert({ chet, val });
                    l = i;
                    chet++;
                }
            }

        }
    }

}

bool Json::is_array() const
{
    if (obj2.size() == 0)
    {
        return false;
    }
    else { return true; }
}

bool Json::is_object() const
{
    if (obj.size() == 0)
    {
        return false;
    }
    else { return true; }

}

any Json::operator[](const std::string& key)
{
    try
    {
        if (obj.size() == 0 || obj2.size() != 0)
        {
            throw Except();
        }

        else
        {
            any search = obj.find(key)->second;

            return search;
        }
    }
    catch (const std::exception& ex)
    {
        cout << ex.what() << endl;
        exit(0);
    }


}

std::any Json::operator[](int index)
{
    try
    {
        if (obj2.size() == 0 || obj.size() != 0)
        {
            throw Except();
        }

        else
        {
            any search = obj2.find(index)->second;

            return search;
        }
    }
    catch (const std::exception& ex)
    {
        cout << ex.what() << endl;
        exit(0);
    }

}


Json Json::parseFile(const std::string path_to_file)
{
    ifstream file(path_to_file);

    string line = ""; string line2 = "";

    if (!file.is_open()) {
        throw Except();
    }
    else
    {
        while (!file.eof())
        {
            getline(file, line2);

            line = line + line2;
        }
    }
    file.close();

    Json obj3(line);

    return obj3;
}

Json Json::parse(const std::string& s)
{
    string line = s;
    Json obj3(line);

    return obj3;
}