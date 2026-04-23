#include "json_builder.h"
#include "json.h"
#include <iostream>



using namespace std;

void PracFirstTest() {
    json::Print(
        json::Document{
            json::Builder{}
                .StartDict()
                .Key("key1"s).Value(123)
                .Key("key2"s).Value("value2"s)
                .Key("key3"s).StartArray()
                .Value(456)
                .StartDict().EndDict()
                .StartDict()
                .Key(""s)
                .Value(nullptr)
                .EndDict()
                .Value(""s)
                .EndArray()
                .EndDict()
                .Build()
        },
        cout
        );
    cout << endl;
}

void PracSecondTest() {
    json::Print(
        json::Document{
            json::Builder{}
                .Value("just a string"s)
                .Build()
        },
        cout
        );
    cout << endl;
}

void TestOneLVLArray() {
    json::Print(
        json::Document{
            json::Builder{}.
            StartArray().
            Value("opened array").
            Value("second element of first").
            EndArray().Build()
        },
        cout
        );
    cout << endl;
}

void TestSecondLVLArray() {
    json::Print(
        json::Document{
            json::Builder{}.
            StartArray().
            Value("opened array").
            Value("second element of first").
            StartArray().Value("opened second array").
            EndArray().EndArray().Build()
        },
        cout
        );
    cout << endl;
}

void TestDictOneElement() {
    json::Print(
        json::Document{
            json::Builder{}.
            StartDict().
            Key("first elem").
            Value("first value").
            EndDict().Build()
        },
        cout
        );
    cout << endl;
}

void TestDict() {
    json::Print(
        json::Document{
            json::Builder{}.
            StartDict().
            Key("first elem").
            Value("first value").
            Key("second key").
            Value("second value").
            EndDict().Build()
        },
        cout
        );
    cout << endl;
}

void TestDictInDict() {
    json::Print(
        json::Document{
            json::Builder{}.
            StartDict().
            Key("first elem").
            Value("first value").
            Key("second key").
            StartDict().
            Key("second level").
            Value("second level first value").
            EndDict().
            EndDict().Build()
        },
        cout
        );
    cout << endl;
}

void TestArrayWithDict() {
    json::Print(
        json::Document{
            json::Builder{}.
            StartArray().
            Value("opened array").
            Value("second element of first").
            StartDict().
            Key("first elem").
            Value("first value").EndDict().
            EndArray().Build()
        },
        cout
        );
    cout << endl;
}

void TestDictWithArray() {
    json::Print(
        json::Document{
            json::Builder{}.
            StartDict().
            Key("first elem").
            Value("first value").
            Key("key, then array").
            StartArray().
            Value("first value of array").
            Value("second value of array").
            EndArray().
            Key("onother dict key").Value("another value").
            EndDict().Build()
        },
        cout
        );
    cout << endl;
}

void TestOnlyBuild() {
    json::Print(
        json::Document{
            json::Builder{}
                .Build()

        },
        cout
        );
    cout << endl;
}

void TestOnlyValue() {
    json::Print(
        json::Document{
            json::Builder{}.Value("value")
            .Build()
        },
        cout
        );
    cout << endl;
}

void TesttwoValue() {
    json::Print(
        json::Document{
            json::Builder{}.Value("value").
            Value("value2")
                .Build()
        },
        cout
        );
    cout << endl;
}

void TestEmptyArray() {
    json::Print(
        json::Document{
            json::Builder{}.StartArray().
            EndArray()
                .Build()
        },
        cout
        );

    cout << endl;
}

void TestValueEndArray() {
    json::Print(
        json::Document{
            json::Builder{}.
            Value("value").
            EndArray().
            Build()
        },
        cout
        );
    cout << endl;
}

void TestEmptyArrayThenValue() {
    json::Print(
        json::Document{
            json::Builder{}.
            StartArray().
            Value(" ").
            EndArray().
            StartDict().
            Key("key").Value("Value").
            EndDict().
          //  Value("value").
            Build()
        },
        cout
        );
    cout << endl;
}

void TestUncompleteArray() {
    json::Print(
        json::Document{
            json::Builder{}.
            StartArray().
            Value(16).
            Value(42).
            Build()
        },
        cout
        );
    cout << endl;
}

void TestUncompleteDict() {
    json::Print(
        json::Document{
            json::Builder{}.
            //StartDict().
            //Key("key").
            Value("val").
            EndDict().
            Build()
        },
        cout
        );
    cout << endl;
}

void TestUncompleteDictInArray() {
    json::Print(
        json::Document{
            json::Builder{}.
            StartArray().
            Value("val").
            StartDict().
            Key("key").
            //Value("val").

            EndDict().
            EndArray().
            Build()
        },
        cout
        );
    cout << endl;
}

void TestUncompleteArrayInDict() {
    json::Print(
        json::Document{
            json::Builder{}.
            StartDict().
            Key("key").
            Value("val").
            Key("array").
            StartArray().
            StartDict().
            Key("key").
            Value("value").
            EndDict().
            EndDict().
            Build()
        },
        cout
        );
    cout << endl;
}

void LastTest() {

    json::Print(
        json::Document{
            json::Builder{}
                .Key("err")
                .Value()
                .Build()
        },
        cout
        );
    cout << endl;



}
int main() {

    PracFirstTest();
    PracSecondTest();

    TestOneLVLArray();
    TestSecondLVLArray();
    TestDictOneElement();
    TestDict();
    TestDictInDict();
    TestArrayWithDict();
    TestDictWithArray();

    //
    TestOnlyValue();
    TestEmptyArray();

    //тесты, которые должны бросать исключения (только json_builder)
 //  TestEmptyArrayThenValue();
   // TestValueEndArray();
   // TestOnlyBuild();
   // TesttwoValue();

   // TestUncompleteArray();
   // TestUncompleteDict();
   // TestUncompleteDictInArray();
  //  TestUncompleteArrayInDict();
   LastTest();

}
