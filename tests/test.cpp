// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "json.hpp"
#include "exsept.hpp"
#include <fstream>


TEST(Json, ExampleJson)
{
    Json object("{\"lastname\" : \"Ivanov\",\"firstname\" : \"Ivan\",\"age\" : 25,\"islegal\" : false,\"marks\" : [4,5,5,5,2,3],\"address\" : {\"city\" : \"Moscow\",\"street\" : \"Vozdvijenka\"}}");

    EXPECT_EQ(std::any_cast<std::string>(object["lastname"]), "Ivanov");
    EXPECT_EQ(std::any_cast<bool>(object["islegal"]), false);
    EXPECT_EQ(std::any_cast<double>(object["age"]), 25);

    Json &marks = *std::any_cast<Json *>(object["marks"]);
    EXPECT_EQ(std::any_cast<double>(marks[0]), 4);
    EXPECT_EQ(std::any_cast<double>(marks[1]), 5);

    Json &address = *std::any_cast<Json *>(object["address"]);
    EXPECT_EQ(std::any_cast<std::string>(address["city"]), "Moscow");
    EXPECT_EQ(std::any_cast<std::string>(address["street"]), "Vozdvijenka");
}

TEST(Json, ParseFile)
{
    Json json("../tests/testopenfile");

    EXPECT_EQ(json.is_object(), true);
    EXPECT_EQ(json.is_array(), false);
}

TEST(Json, OperatorArrayTypeException)
{
    Json json{ "[]" };

    EXPECT_THROW(
            json["test"],
            Except
    );
}

TEST(Json, OperatorObjectTypeException)
{
    Json json{ "{}" };

    EXPECT_THROW(
            json[0],
            Except
    );
}

TEST(Json, OperatorArrayExceptionSize)
{
    Json json{ "[]" };

    EXPECT_THROW(
            json[999],
            Except
    );
}


TEST(Json, NoJson)
{
    EXPECT_THROW
    (
            Json json{ "false" },
            Except
    );
}