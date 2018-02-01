/*****************************************************************************
MIT License

Copyright (c) 2018 stefan-wolfsheimer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 
*/
#include <catch.hpp>
#include "cli_multiple_value.h"

using IntMultipleValue = Cli::MultipleValue<int>;

TEST_CASE("multiple-value-constructor-with-name", "[Value]")
{
  std::vector<int> v;
  REQUIRE_FALSE(IntMultipleValue::make(v, "name")->isFlag());
  REQUIRE(IntMultipleValue::make(v, "name")->getName() == "name");
  REQUIRE(IntMultipleValue::make(v, "name")->getShortName() == '\0');
  REQUIRE_FALSE(IntMultipleValue::make(v, "name")->isSet());
}

TEST_CASE("multiple-value-constructor-with-short-name", "[Value]")
{
  std::vector<int> v;
  REQUIRE_FALSE(IntMultipleValue::make(v, 'n')->isFlag());
  REQUIRE(IntMultipleValue::make(v, 'n')->getName() == "");
  REQUIRE(IntMultipleValue::make(v, 'n')->getShortName() == 'n');
  REQUIRE_FALSE(IntMultipleValue::make(v, 'n')->isSet());
}

TEST_CASE("multiple-value-constructor-with-name-and-short-name", "[Value]")
{
  std::vector<int> v;
  REQUIRE_FALSE(IntMultipleValue::make(v, 'n', "name")->isFlag());
  REQUIRE(IntMultipleValue::make(v, 'n', "name")->getName() == "name");
  REQUIRE(IntMultipleValue::make(v, 'n', "name")->getShortName() == 'n');
  REQUIRE_FALSE(IntMultipleValue::make(v, 'n')->isSet());
}

TEST_CASE("multiple-value-parse", "[Value]")
{
  std::vector<int> v;
  auto value = IntMultipleValue::make(v, "name");
  int argc;
  const char * argv[] = { "progr", "--name", "12" };
  std::vector<std::string> err;
  int i = 1;
  REQUIRE(value->parse(sizeof(argv)/sizeof(char*), argv, i, err));
  REQUIRE(err.empty());
  REQUIRE(value->isSet());
  REQUIRE(i == 2);
  REQUIRE(v == std::vector<int>({12}));
}

TEST_CASE("multiple-value-parse-twice", "[Value]")
{
  std::vector<int> v;
  auto value = IntMultipleValue::make(v, "name");
  int argc;
  const char * argv1[] = { "progr", "--name", "12" };
  const char * argv2[] = { "progr", "--name", "13" };
  std::vector<std::string> err;
  int i = 1;
  REQUIRE(value->parse(sizeof(argv1)/sizeof(char*), argv1, i, err));
  REQUIRE(err.empty());
  REQUIRE(value->isSet());
  REQUIRE(i == 2);
  REQUIRE_FALSE(value->parse(sizeof(argv2)/sizeof(char*), argv2, i, err));
  REQUIRE(err.size() == 1u);
  REQUIRE(v == std::vector<int>({12}));
}

TEST_CASE("multiple-value-parse-argument-required", "[Value]")
{
  std::vector<int> v;
  auto value = IntMultipleValue::make(v, "name");
  int argc;
  const char * argv[] = { "progr", "--name" };
  std::vector<std::string> err;
  int i = 1;
  REQUIRE_FALSE(value->parse(sizeof(argv)/sizeof(char*), argv, i, err));
  REQUIRE(err.size() == 1u);
  REQUIRE_FALSE(value->isSet());
  REQUIRE(i == 1);
  REQUIRE(v.empty());
}

TEST_CASE("multiple-value-parse-invalid-value", "[Value]")
{
  std::vector<int> v;
  auto value = IntMultipleValue::make(v, "name");
  int argc;
  const char * argv[] = { "progr", "--name", "12xx" };
  std::vector<std::string> err;
  int i = 1;
  REQUIRE_FALSE(value->parse(sizeof(argv)/sizeof(char*), argv, i, err));
  REQUIRE(err.size() == 1u);
  REQUIRE(value->isSet());
  REQUIRE(i == 2);
  REQUIRE(v.empty());
}
