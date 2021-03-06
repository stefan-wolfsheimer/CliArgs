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

#include <catch2/catch.hpp>
#include <cli_multiple_flag.h>

using MultipleFlag = Cli::MultipleFlag;

TEST_CASE("multiple-flag-constructor-with-name", "[MultipleFlag]")
{
  REQUIRE(MultipleFlag::make("name")->isFlag());
  REQUIRE(MultipleFlag::make("name")->getName() == "name");
  REQUIRE(MultipleFlag::make("name")->getShortName() == '\0');
  REQUIRE_FALSE(MultipleFlag::make("name")->isSet());
}

TEST_CASE("multiple-flag-constructor-with-short-name", "[MultipleFlag]")
{
  REQUIRE(MultipleFlag::make('n')->isFlag());
  REQUIRE(MultipleFlag::make('n')->getName() == "");
  REQUIRE(MultipleFlag::make('n')->getShortName() == 'n');
  REQUIRE_FALSE(MultipleFlag::make('n')->isSet());
}

TEST_CASE("multiple-flag-constructor-with-name-and-short-name", "[MultipleFlag]")
{
  REQUIRE(MultipleFlag::make('n', "name")->isFlag());
  REQUIRE(MultipleFlag::make('n', "name")->getName() == "name");
  REQUIRE(MultipleFlag::make('n', "name")->getShortName() == 'n');
  REQUIRE_FALSE(MultipleFlag::make('n')->isSet());
}

TEST_CASE("multiple-flag-parse", "[MultipleFlag]")
{
  auto flag = MultipleFlag::make("name");
  int argc;
  const char * argv[] = { "progr" };
  std::vector<std::string> err;
  int i = 0;
  REQUIRE(flag->parse(sizeof(argv)/sizeof(char*), argv, i, err));
  REQUIRE(err.empty());
  REQUIRE(flag->isSet());

  REQUIRE(flag->parse(sizeof(argv)/sizeof(char*), argv, i, err));
  REQUIRE(err.empty());
  REQUIRE(flag->isSet());
}

