//
// Created by absinthetoxin on 30.09.2019.
//

#include <gtest/gtest.h>
#include "json.hpp"
#include "exsept.hpp"
#include <fstream>

TEST(JsonArray, name)
{
    Json json{ "[ \"Alena\" ]" };
    EXPECT_EQ(json.is_object(), false);
    EXPECT_EQ(json.is_array(), true);

    EXPECT_EQ(std::any_cast<std::string>(json[0]), "Alena");
}

TEST(JsonArray, arrays)
{
    Json json{ "[\"Te\", true, 1177, false]" };
    EXPECT_EQ(json.is_object(), false);
    EXPECT_EQ(json.is_array(), true);

    EXPECT_EQ(std::any_cast<std::string>(json[0]), "Te");
    EXPECT_EQ(std::any_cast<bool>(json[1]), true);
    EXPECT_EQ(std::any_cast<double>(json[2]), 1177);
    EXPECT_EQ(std::any_cast<bool>(json[3]), false);
}


TEST(JsonArray, objects)
{
    Json json{ "[{\"bts\": 178}, {\"exo\": false}, {\"ocean\": \"blue\"}]" };

    EXPECT_EQ(json.is_object(), false);
    EXPECT_EQ(json.is_array(), true);

    {
        Json &nested = *std::any_cast<Json *>(json[0]);
        EXPECT_EQ(nested.is_object(), true);
        EXPECT_EQ(nested.is_array(), false);

        EXPECT_EQ(std::any_cast<std::double>(nested["bts"]), 178);
    }

    {
        Json &nested = *std::any_cast<Json *>(json[1]);
        EXPECT_EQ(nested.is_object(), true);
        EXPECT_EQ(nested.is_array(), false);

        EXPECT_EQ(std::any_cast<bool>(nested["exo"]), false);
    }

    {
        Json &nested = *std::any_cast<Json *>(json[2]);
        EXPECT_EQ(nested.is_object(), true);
        EXPECT_EQ(nested.is_array(), false);

        EXPECT_EQ(std::any_cast<std::string>(nested["ocean"]), "blue");
    }
}

TEST(JsonArray, ArrayWithAnything)
{
    Json json{ "[true, 787,false,[ false, false, false ],\"kola\",{ \"open\" : \"eyes\" },\"sprite\" ]" };

    EXPECT_EQ(json.is_object(), false);
    EXPECT_EQ(json.is_array(), true);


    EXPECT_EQ(std::any_cast<bool>(json[0]), true);
    EXPECT_EQ(std::any_cast<double>(json[1]), 787);
    EXPECT_EQ(std::any_cast<bool>(json[2]), false);

    {
        Json &nested = *std::any_cast<Json *>(json[3]);

        EXPECT_EQ(nested.is_object(), false);
        EXPECT_EQ(nested.is_array(), true);

        // 1
        EXPECT_EQ(std::any_cast<bool>(nested[0]), false);

        // 2
        EXPECT_EQ(std::any_cast<bool>(nested[1]), false);

        // 3
        EXPECT_EQ(std::any_cast<bool>(nested[2]), false);
    }

    EXPECT_EQ(std::any_cast<std::string>(json[4]), "kola");

    {
        Json &nested = *std::any_cast<Json *>(json[5]);
        EXPECT_EQ(nested.is_object(), true);
        EXPECT_EQ(nested.is_array(), false);

        EXPECT_EQ(std::any_cast<std::string>(nested["open"]), "eyes");
    }

    // "String"
    EXPECT_EQ(std::any_cast<std::string>(json[6]), "sprite");
}