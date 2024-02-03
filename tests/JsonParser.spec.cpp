/*
** EPITECH PROJECT, 2024
** lib
** File description:
** JsonParserSpec
*/

#include "JsonParser/JsonParser.hpp"
#include <string>
#include <vector>
#include "pipunit/include/Assertion.hpp"
#include "pipunit/include/Test.hpp"

pipunit::Assertion json_parsing_assert_number(
    pipunit::CoutRedirect *cout,
    pipunit::CerrRedirect *cerr
)
{
    (void)cout;
    (void)cerr;
    lib::Json::Parser parser("tests/TestData/Number.json");
    parser.parseJson();
    return pipunit::assert_equals(parser.get<double>("num"), -42.3);
}

pipunit::Assertion json_parsing_assert_string(
    pipunit::CoutRedirect *cout,
    pipunit::CerrRedirect *cerr
)
{
    (void)cout;
    (void)cerr;
    lib::Json::Parser parser("tests/TestData/String.json");
    parser.parseJson();

    return pipunit::assert_equals(
        parser.get<std::string>("str"), std::string("Pipitek\n42")
    );
}

pipunit::Assertion json_parsing_assert_true_bool(
    pipunit::CoutRedirect *cout,
    pipunit::CerrRedirect *cerr
)
{
    (void)cout;
    (void)cerr;
    lib::Json::Parser parser("tests/TestData/BoolTrue.json");
    parser.parseJson();

    return pipunit::assert_equals(parser.get<bool>("t"), true);
}

pipunit::Assertion json_parsing_assert_false_bool(
    pipunit::CoutRedirect *cout,
    pipunit::CerrRedirect *cerr
)
{
    (void)cout;
    (void)cerr;
    lib::Json::Parser parser("tests/TestData/BoolFalse.json");
    parser.parseJson();

    return pipunit::assert_equals(parser.get<bool>("f"), false);
}

pipunit::Assertion json_parsing_assert_array_content(
    pipunit::CoutRedirect *cout,
    pipunit::CerrRedirect *cerr
)
{
    (void)cerr;
    lib::Json::Parser parser("tests/TestData/Array.json");
    parser.parseJson();

    std::cout << parser.getJson() << std::endl;

    return pipunit::assert_stdout_equals(cout, "{\"arr\": [1,\n2,\n3]}\n");
}

pipunit::Assertion json_parsing_assert_obj_content(
    pipunit::CoutRedirect *cout,
    pipunit::CerrRedirect *cerr
)
{
    (void)cerr;
    lib::Json::Parser parser("tests/TestData/Object.json");
    parser.parseJson();

    std::cout << parser.get<lib::Json::JsonObject>("obj") << std::endl;

    return pipunit::assert_stdout_equals(cout, "{\"test\": \"test\"}\n");
}

pipunit::Assertion json_parsing_assert_invalid_token(
    pipunit::CoutRedirect *cout,
    pipunit::CerrRedirect *cerr
)
{
    (void)cout;
    (void)cerr;
    lib::Json::Parser parser("tests/TestData/InvalidJson.json");
    try {
        parser.parseJson();
    } catch (lib::Json::InvalidTokenException &e) {
        return pipunit::assert_true(true) &&
            pipunit::assert_true(e.what() != nullptr);
    }
    return pipunit::assert_true(false);
}

pipunit::Assertion json_parsing_assert_invalid_string_token(
    pipunit::CoutRedirect *cout,
    pipunit::CerrRedirect *cerr
)
{
    (void)cout;
    (void)cerr;
    lib::Json::Parser parser("tests/TestData/BadString.json");
    try {
        parser.parseJson();
    } catch (lib::Json::InvalidTokenException &e) {
        return pipunit::assert_true(true);
    }
    return pipunit::assert_true(false);
}

pipunit::Assertion json_parsing_stdout_print(
    pipunit::CoutRedirect *cout,
    pipunit::CerrRedirect *cerr
)
{
    (void)cerr;
    lib::Json::Parser parser("tests/TestData/Array.json");
    parser.parseJson();
    std::cout << parser.getJson() << std::endl;
    return pipunit::assert_stdout_equals(cout, "{\"arr\": [1,\n2,\n3]}\n");
}

pipunit::Assertion json_parsing_file_doesnt_exist(
    pipunit::CoutRedirect *cout,
    pipunit::CerrRedirect *cerr
)
{
    (void)cout;
    (void)cerr;
    lib::Json::Parser parser("tests/TestData/DoesntExist.json");
    try {
        parser.parseJson();
    } catch (lib::Json::InvalidTokenException &e) {
        return pipunit::assert_true(true);
    }
    return pipunit::assert_true(false);
}

std::vector<pipunit::Test> JsonParserSpec()
{
    std::vector<pipunit::Test> tests;
    tests.push_back(pipunit::Test(
        "test json number",
        "testing if a json number is parsed correctly",
        json_parsing_assert_number,
        NULL,
        NULL
    ));

    tests.push_back(pipunit::Test(
        "test json string",
        "testing if a json string is parsed correctly",
        json_parsing_assert_string,
        NULL,
        NULL
    ));

    tests.push_back(pipunit::Test(
        "test json true bool",
        "testing if a json true bool is parsed correctly",
        json_parsing_assert_true_bool,
        NULL,
        NULL
    ));

    tests.push_back(pipunit::Test(
        "test json false bool",
        "testing if a json false bool is parsed correctly",
        json_parsing_assert_false_bool,
        NULL,
        NULL
    ));

    tests.push_back(pipunit::Test(
        "test json array content",
        "testing if a json array content is parsed correctly",
        json_parsing_assert_array_content,
        pipunit::redirectStdout,
        NULL
    ));

    tests.push_back(pipunit::Test(
        "test json object content",
        "testing if a json object content is parsed correctly",
        json_parsing_assert_obj_content,
        pipunit::redirectStdout,
        NULL
    ));

    tests.push_back(pipunit::Test(
        "test json invalid token",
        "testing if a json invalid token is detected",
        json_parsing_assert_invalid_token,
        NULL,
        NULL
    ));

    tests.push_back(pipunit::Test(
        "test json invalid string token",
        "testing if a json invalid string token is detected",
        json_parsing_assert_invalid_string_token,
        NULL,
        NULL
    ));

    tests.push_back(pipunit::Test(
        "test json stdout print",
        "testing if a json is printed correctly",
        json_parsing_stdout_print,
        pipunit::redirectStdout,
        NULL
    ));

    tests.push_back(pipunit::Test(
        "test json file doesnt exist",
        "testing if a json file that doesn't exist is detected",
        json_parsing_file_doesnt_exist,
        NULL,
        NULL
    ));
    return tests;
}
