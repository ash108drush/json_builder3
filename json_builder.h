#include <iostream>
#include <map>
#include <set>
#include <string>
#include <deque>
#include <memory>
#include "json.h"

namespace json{

class Builder {
    class BaseContext;
    class DictValueContext;
    class ArrayItemContext;
    class ValueContext;
    class KeyContext;
    class BuildContext;
public:
    Builder() = default;
    DictValueContext StartDict();
    ArrayItemContext StartArray();
    ValueContext Value(Node node);

    KeyContext Key(std::string) = delete;
    BaseContext EndDict() = delete;
    BaseContext EndArray() = delete;
    Node Build() = delete;

    bool IsRoot(){
        bool tmp = first_run_;
        first_run_ = false;
        return tmp;
    }

private:
    Node root_;
    std::vector<Node *> nodes_stack_;
    std::string current_key_ = "";

    bool is_key_ = false;
    bool first_run_ = true;
    bool value_can_build_ = false;


    class BaseContext {
    public:
        BaseContext(Builder& builder)
            : builder_(builder){

        }
        KeyContext Key(std::string string);
        BaseContext EndDict();
        BaseContext EndArray();
        Node Build();

        DictValueContext StartDict() {
            return builder_.StartDict();
        }
        ArrayItemContext StartArray() {
             return builder_.StartArray();
        }
        ValueContext Value(Node node) {

            return builder_.Value(node);
        }

        bool IsRoot(){
            return builder_.IsRoot();
        }

        Builder& GetBuilder(){
            return builder_;
        }
    private:
        Builder& builder_;

    };

     class BuildContext : public BaseContext {
     public:
         BuildContext(BaseContext base)
             : BaseContext(base) {
         }
     };

    class DictValueContext : public BaseContext {
    public:
        DictValueContext(BaseContext base)
            : BaseContext(base)
        {
        }
        BaseContext EndArray() = delete;
        DictValueContext StartDict() = delete;
        ArrayItemContext StartArray() = delete;
        ValueContext Value(Node) = delete;
    };

    class ArrayItemContext : public BaseContext {
    public:
        ArrayItemContext(BaseContext base) : BaseContext(base) {}
        BaseContext EndDict() = delete;
    };

    class ValueContext : public BaseContext {
    public:
        ValueContext(BaseContext base)
            : BaseContext(base) {
        }

        ArrayItemContext StartArray() = delete;


        Node Build() {
           // if(GetBuilder().value_can_build_ ){
                return BaseContext {*this}.Build();
           // }else{
           //     throw std::logic_error("Value Build");
           // }

        }
    };

    class KeyContext : public BaseContext {
    public:
        KeyContext(BaseContext base)
            : BaseContext(base){
        }
        KeyContext Key(std::string) = delete;
        BaseContext EndArray() = delete;
        //  DictValueContext StartDict() = delete;
        Node Build() = delete;

    };


};

} //end namespace

