#include "json_builder.h"
#include "json.h"
#include <iostream>



using namespace std;

int main() {

    json::Print(
        json::Document{
            json::Builder{}
                .Value("just a string"s)
                .Build()
        },
        cout
        );

    json::Print(
        json::Document{
            json::Builder{}
                .StartArray()
                .Value(123)
                .Value("value2"s)
                .EndArray()
                .Build()
        },
        cout
        );
    cout << endl;

    json::Print(
        json::Document{
            json::Builder{}
                .StartDict()
                .Key("key1"s).Value(123)
                .Key("key2"s).Value("value2"s)
                .EndDict()
                .Build()
        },
        cout
        );
    cout << endl;

    std::cout << "MAIN EXAMPLE" << std::endl;
    json::Print(
        json::Document{
            json::Builder{}
                .StartDict()
                .Key("key1"s).Value(123)
                .Key("key2"s).Value("value2"s)
                .Key("key3"s).StartArray()
                .Value(456)
                .Value(457)
                .Value(458)
                .StartDict().EndDict()
                .StartDict()
                .Key(""s)
                .Value(nullptr)
                .EndDict()
                .EndArray()
                .EndDict()
                .Build()
        },
        cout
        );
    cout << endl;

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


    cout << endl;
    json::Print(
        json::Document{
            json::Builder{}
                .StartDict()
                .Key("key1"s).Value(123)
                .Key("key2"s).Value("value2"s)
                .EndDict()
                .Build()
        },
        cout
        );
    cout << endl;

    json::Print(
        json::Document{
            json::Builder{}
                .StartArray()
                .Value(123)
                .Value("value2"s)
                .EndArray()
                .Build()
        },
        cout
        );
    cout << endl;


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

/*

    json::Print(
        json::Document{
            json::Builder{}.StartArray().StartArray().EndArray().Value(1).EndArray().Build()
        },
        cout
        );
    cout << endl;


    json::Print(
        json::Document{
            json::Builder{}.StartDict().Key("1").StartDict().EndDict().Key("2").Value(2).EndDict().Build()
        },
        cout
        );
    cout << endl;
*/

/*
    json::Print(
        json::Document{
            json::Builder{}.StartDict().Key("1").StartArray().EndArray().Key("2").Value(2).EndDict().Build()
        },
        cout
        );
    cout << endl;
*/
/*

    json::Print(
        json::Document{
            //json::Builder{}.StartDict().Key("1"s).Value("2"s).StartDict().Key("1"s).Value("2"s).EndDict().EndDict().Build()
            json::Builder{}.StartArray().StartArray().EndArray().Value(1).EndArray().Build()
        },
        cout
        );
    cout << endl;

*/
    json::Print(
        json::Document{
            //json::Builder{}.StartDict().Key("1"s).Value("2"s).StartDict().Key("1"s).Value("2"s).EndDict().EndDict().Build()
            json::Builder{}.StartArray().Value("s"s).Value("ss").EndDict()
        },
        cout
        );
    cout << endl;

//StartArray и серии Value следует не Value, не StartDict, не StartArray и не EndArray.
    /* Key- +
     * Build-+
     * EndDict-+
     * Value+
     * StartDict+
     * StartArray+
     * EndArray+
     * /
/*
 * сли брать версию которая была в архиве в начальном посте, то:
    разделяем функциональность:
        оставляем ValueContext когда возвращаем из KeyContext::Value.
        в Builder::Value возвращаем что-то другое (Builder& подойдет поскольку задача упрощена, но в полной тут бы был отдельный класс).
        ArrayContext::Value в этой версии возвращал ArrayContext, это правильно, оставляем.
    добавляем ошибки компиляции:
        в ValueContext убираем все кроме Key() и EndDict()

собственно все
*/



 /*
  errors
json::Builder{}.StartArray().StartDict().Key("1"s).Value(12).EndDict().EndDict().Build()
json::Builder{}.Value("s"s).Value("1"s).Build()

   json::Print(
        json::Document{
            json::Builder{}
                .StartDict()
                    .Key("key1"s).Value(123)
                    .EndArray() // <-- тут должна быть ошибка
                .EndDict()
                .Build()},
        cout);

.StartDict().Key("").Value(1).Build()
.StartDict().Key("").Value(1).StartArray()
.StartDict().Key("").Value(1).EndArray()
.StartDict().Key("").Value(1).Value(1)

*/



/*
success
json::Builder{}.StartArray().StartDict().EndDict().Value(1).EndArray().Build()
json::Builder{}.StartArray().StartArray().EndArray().Value(1).EndArray().Build()
json::Builder{}.StartDict().Key("1").StartDict().EndDict().Key("2").Value(2).EndDict().Build()
json::Builder{}.StartDict().Key("1").StartArray().EndArray().Key("2").Value(2).EndDict().Build()

json::Print(
        json::Document{
            json::Builder{}
                .StartDict()
                    .Key("key1"s).Value(123)
                    .Key("key2"s).Value("value2"s)
                    .Key("key3"s).StartArray()
                        .Value(456)
                        .StartDict()
                        .EndDict()
                        .StartDict()
                            .Key(""s).Value(nullptr)
                        .EndDict()
                        .Value(""s) // Builder::Value()
                    .EndArray() // <-- ок
                .EndDict()
                .Build()},
        cout);

*/
}
