//
// Created by absinthetoxin on 30.09.2019.
//

#include <gtest/gtest.h>

#include "Json.hpp"

TEST(JsonObject, obj)
{
    Json json{ "{ \"hello\" : \"buy\" }" };
    EXPECT_EQ(json.is_object(), true);
    EXPECT_EQ(json.is_array(), false);

    EXPECT_EQ(std::any_cast<std::string>(json["hello"]), "buy");
}

TEST(JsonObject, ObjectInsideObject)
{
    Json json{ "{ \"my\" : { \"book\":   \"red\" } }" };
    EXPECT_EQ(json.is_object(), true);
    EXPECT_EQ(json.is_array(), false);

    Json &nested = *std::any_cast<Json *>(json["my"]);
    EXPECT_EQ(nested.is_object(), true);
    EXPECT_EQ(nested.is_array(), false);

    EXPECT_EQ(std::any_cast<std::string>(nested["book"]), "red");
}

TEST(JsonObject, ObjectdWithArray)
{
    Json json{ "{ \"key\" : [1,2,3] }" };
    EXPECT_EQ(json.is_object(), true);
    EXPECT_EQ(json.is_array(), false);
    EXPECT_EQ(json.is_empty(), false);

    Json &nested = *std::any_cast<Json *>(json["key"]);
    EXPECT_EQ(nested.is_object(), false);
    EXPECT_EQ(nested.is_array(), true);
    EXPECT_EQ(nested.is_empty(), false);

    EXPECT_EQ(std::any_cast<double>(nested[0]), 1);
}

TEST(JsonObject, ObjectsWithArrayAndValues)
{
    Json json{ "{ \"fanta\" : [9,true,23], \"animal\": \"dog\" }" };
    EXPECT_EQ(json.is_object(), true);
    EXPECT_EQ(json.is_array(), false);

    Json &nested = *std::any_cast<Json *>(json["fanta"]);
    EXPECT_EQ(nested.is_object(), false);
    EXPECT_EQ(nested.is_array(), true);

    EXPECT_EQ(std::any_cast<double>(nested[0]), 9);
    EXPECT_EQ(std::any_cast<bool>(nested[1]), true);
    EXPECT_EQ(std::any_cast<double>(nested[2]), 23);

    EXPECT_EQ(std::any_cast<bool>(json["animal"]), "dog");
}

