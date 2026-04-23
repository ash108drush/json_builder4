#include <iostream>
#include <map>
#include <set>
#include <string>
#include <deque>
#include <memory>
#include "json.h"

namespace json{

class Builder {

public:
    Builder() = default;
    Builder& StartDict();
    Builder& StartArray();
    Builder&Value(Node node);
    Builder& Value(){
        throw std::logic_error("Empty value");
    };


    Builder& Key(std::string);

    Builder& EndDict();
    Builder& EndArray();
    Node Build();

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
};

} //end namespace

