//
// Created by absinthetoxin on 24.09.2019.
//
#include "/home/absinthetoxin/CrazyOverdose/lab01/lab-01-parser/include/json.hpp"  
#include <any>
#include </home/absinthetoxin/CrazyOverdose/lab01/lab-01-parser/include/exsept.hpp>
#include <string>
using namespace std;

Json :: Json(std::string s)
{
    bool flag = false;// если объект, то true, если массив, то false
    vector <string> array;
    for (long unsigned int i=0; i < s.size(); i++)
    {
        int ch1 = 0, ch2 = 0; // ch1 - счётчик {}, ch2 - []
        if (s[i] == '{')
        {
            flag = true;
            ch1++;
            for (long unsigned int j = i + 1; j < s.size(); j++)

            {
                switch (s[j])
                {
                    case '[':
                        ch2++;
                        break;
                    case ']':
                        ch2--;
                        break;
                    case '{':
                        ch1++;
                        break;
                    case '}':
                        ch1--;
                        break;
                }
                if (s[j] == ',' && ch1 == 1 && ch2 == 0)
                {
                    string a = s.substr(i + 1, j - i - 1);
                    array.push_back(a);
                    i = j;
                }

                if (s[j] == '}' && ch1 == 0 && ch2 == 0)
                {
                    string a = s.substr(i + 1, j - i - 1);
                    array.push_back(a);
                    i = j;
                }
            }
        }

        if (s[i] == '[')
        {
            ch2++;
            for (long unsigned int j = i+1; j < s.size(); j++)
            {
                switch (s[j])
                {
                    case '[':
                        ch2++;
                        break;
                    case ']':
                        ch2--;
                        break;
                    case '{':
                        ch1++;
                        break;
                    case '}':
                        ch1--;
                        break;
                }
                if (s[j] == ',' && ch2 == 1 && ch1 == 0)
                {
                    string a = s.substr(i + 1, j - i - 1);
                    array.push_back(a);
                    i = j;
                }
                if (s[j] == ']' && ch2 == 0 && ch1 == 0)
                {
                    string a = s.substr(i + 1, j - i - 1);
                    array.push_back(a);
                    i = j;
                }
            }
        }
        break;
    }


    if (flag == true)
    {
        for (long unsigned int m = 0; m < array.size(); m++)
        {
            string help = array[m];
            string keys="";
            int ch = 0;
            for (long unsigned int i = 0; i < help.size(); i++)
            {
                if (help[i] == '"')
                {
                    i++;
                    while (help[i] != '"')
                    {
                        keys = keys + help[i];
                        i++;
                        ch = i;
                    }

                    if (ch != 0)
                    {
                        break;
                    }
                }
            }

            for ( long unsigned int k = (ch + 1); k < help.size(); k++)
            {
                try
                {
                    if (help[k] != ':' && help[k] != ' ')
                    {
                        throw Except();
                    }
                }
                catch (const std::exception& ex)
                {
                    cout << ex.what() << endl;
                    exit(0);
                }

                if (help[k] == ':')
                {
                    for (long unsigned int j = k + 1; j < help.size(); j++)
                    {
                        if (help[j] == 'f' && help[j + 1] == 'a' && help[j + 2] == 'l' && help[j + 3] == 's' && help[j+4] == 'e')
                        {
                            bool value1 = false;
                            any value = value1;
                            obj.insert({ keys , value });
                            break;
                        }

                        if (help[j] == 't' && help[j + 1] == 'r' && help[j + 2] == 'u' && help[j + 3] == 'e')
                        {
                            bool value1 = true;
                            any value = value1;
                            obj.insert({ keys , value });
                            break;
                        }

                        if (help[j] == '0' || help[j] == '1' || help[j] == '2' || help[j] == '3' || help[j] == '4' || help[j] == '5' || help[j] == '6' || help[j] == '7' || help[j] == '8' || help[j] == '9')
                        {
                            string number1 = ""; double number2 = 0;
                            while (j != help.size() && help[j] != ' ')
                            {
                                number1 = number1 + help[j];
                                j++;
                            }
                            int v = number1.size() - 1;
                            for (long unsigned int i = 0; i < number1.size(); i++)
                            {
                                number2 = number2 + (number1[i] - '0') * pow(10, v);
                                v--;
                            }
                            any value = number2;
                            obj.insert({ keys , value });
                            break;

                        }

                        if (help[j] == '{')
                        {
                            string rek1;
                            for (int i = help.size(); i > 0; i--)
                            {
                                if (help[i] == '}')
                                {
                                    for (int l = j; l < i+1; l++)
                                    {
                                        rek1 = rek1 + help[l];
                                    }
                                }
                            }

                            Json rek (rek1);
                            any value = rek;
                            obj.insert({ keys , value });
                            break;
                        }

                        if (help[j] == '[')
                        {
                            string rek1;
                            for (int i = help.size(); i > 0; i--)
                            {
                                if (help[i] == ']')
                                {

                                    for (int p = j; p < i+1; p++)
                                    {
                                        rek1 = rek1 + help[p];
                                    }
                                }
                            }

                            Json rek (rek1);
                            any value = rek;
                            obj.insert({ keys , value });
                            break;
                        }

                        if (help[j] == '"')
                        {
                            string rek1;
                            for (int i = help.size(); i > 0; i--)
                            {
                                if (help[i] == '"')
                                {
                                    for (int p = j+1; p < i; p++)
                                    {
                                        rek1 = rek1 + help[p];
                                    }
                                    break;
                                }
                            }

                            any value = rek1;
                            obj.insert({ keys , value });
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }

    if (flag == false)
    {     int ch = 0;

        for (long unsigned int m = 0; m < array.size(); m++)
        {
            string help = array[m];
            for (long unsigned int j = 0; j < help.size(); j++)
            {
                if (help[j] == 'f' && help[j + 1] == 'a' && help[j + 2] == 'l' && help[j + 3] == 's' && help[j + 4] == 'e')
                {
                    bool value1 = false;
                    any value = value1;
                    obj2.insert({ ch, value });
                    ch++;
                    break;
                }

                if (help[j] == 't' && help[j + 1] == 'r' && help[j + 2] == 'u' && help[j + 3] == 'e')
                {
                    bool value1 = true;
                    any value = value1;
                    obj2.insert({ ch , value });
                    ch++;
                    break;
                }

                if (help[j] == '0' || help[j] == '1' || help[j] == '2' || help[j] == '3' || help[j] == '4' || help[j] == '5' || help[j] == '6' || help[j] == '7' || help[j] == '8' || help[j] == '9')
                {
                    string number1 = ""; double number2 = 0;
                    while (j != help.size() && help[j] != ' ')
                    {
                        number1 = number1 + help[j];
                        j++;
                    }
                    int v = number1.size() - 1;
                    for ( long unsigned int i = 0; i < number1.size(); i++)
                    {
                        number2 = number2 + (number1[i] - '0') * pow(10, v);
                        v--;
                    }
                    any value = number2;
                    obj2.insert({ ch , value });
                    ch++;
                    break;
                }

                if (help[j] == '{')
                {
                    string rek1;
                    for (int i = help.size(); i > 0; i--)
                    {
                        if (help[i] == '}')
                        {
                            for (int l = j; l < i+1; l++)
                            {
                                rek1 = rek1 + help[l];
                            }
                        }
                    }
                    Json rek (rek1);
                    any value = rek;
                    obj2.insert({ ch , value });
                    ch++;
                    break;
                }

                if (help[j] == '[')
                {
                    string rek1;
                    for (int i = help.size(); i > 0; i--)
                    {
                        if (help[i] == ']')
                        {
                            for (int l = j; l < i+1; l++)
                            {
                                rek1 = rek1 + help[l];
                            }
                        }
                    }

                    Json rek (rek1);
                    any value = rek;
                    obj2.insert({ ch , value });
                    ch++;
                    break;
                }

                if (help[j] == '"')
                {
                    string rek1;
                    for (int i = help.size(); i > 0; i--)
                    {
                        if (help[i] == '"')
                        {
                            for (int l = j+1; l < i; l++)
                            {
                                rek1 = rek1 + help[l];
                            }
                        }
                    }

                    any value = rek1;
                    obj2.insert({ ch , value });
                    ch++;
                    break;
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
    else{ return true;}
}

bool Json ::is_object() const
{
        if (obj.size() == 0)
        {
            return false;
        }
        else{ return true;}

}

any Json::operator[](const std::string& key)
{
    try
    {
        if (obj.size() == 0 || obj2.size()!=0)
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

    string line=""; string line2 = "";

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