#include "json_builder.h"
#include <memory>
#include <algorithm>

namespace json {

Builder& Builder::Value(Node node){
    if(IsRoot()){
        root_ = std::move(node);
        value_can_build_ = true;
        return  *this ;
    }
    if(nodes_stack_.size() == 0){
        throw std::logic_error("Double Value Not in Dict or Array");
    }
    Node* node_ptr = nodes_stack_.back();
    if(node_ptr->IsArray()){
        node_ptr->AsArray().emplace_back(std::move(node));
    }
    if(node_ptr->IsDict()){
        if(is_key_){
            node_ptr->AsDict().insert({current_key_,std::move(node)});
            is_key_ = false;
        }else{
            throw std::logic_error("Value not after Key in Dict");
        }

    }
    return  *this ;
}

Builder& Builder::StartArray() {
    if(IsRoot()){
        root_ =  Node(Array());
        nodes_stack_.push_back(std::move(&root_));
        return *this;
    }
    Node* node_ptr = nodes_stack_.back();
    if(node_ptr->IsDict()){
        if(is_key_){                
            Node* node_new = new Node(Array());
            auto pair = node_ptr->AsDict().emplace(current_key_,std::move(*node_new));
            Node *nd = &pair.first->second;
            nodes_stack_.push_back(std::move(nd));
        }else{
            throw std::logic_error("StartArray not after Key in Dict");
        }
    }

    if(node_ptr->IsArray()){
            Node* node_new = new Node(Array());
            Node& nd = node_ptr->AsArray().emplace_back(std::move(*node_new));
            nodes_stack_.push_back(std::move(&nd));
    }
    return *this;
}




Builder& Builder::StartDict() {
    if(IsRoot()){
        root_ = Node(Dict());
        nodes_stack_.push_back(std::move(&root_));
       return  *this ;
    }

    Node* node_ptr = nodes_stack_.back();
    if(node_ptr->IsArray()){      
        Node* node_new = new Node(Dict());
        Node& nd = node_ptr->AsArray().emplace_back(std::move(*node_new));
        nodes_stack_.push_back(std::move(&nd));
    }

    if(node_ptr->IsDict()){
        if(is_key_){
            Node* node_new = new Node(Dict());
            auto pair = node_ptr->AsDict().emplace(current_key_,std::move(*node_new));
            Node *nd = &pair.first->second;
            nodes_stack_.push_back(std::move(nd));
        }else{
            throw std::logic_error("StartDict not after Key in Dict");
        }
    }

    return  *this ;
}

Builder& Builder::EndArray() {
    if(nodes_stack_.size() ==0){
        throw std::logic_error("End Array Zero Stack Size");
    }

    Node* node_ptr = nodes_stack_.back();
    if(node_ptr->IsArray()){
        nodes_stack_.pop_back();
    }else{
         throw std::logic_error("Array expected");
    }
    return *this;
}

Builder& Builder::EndDict() {
    if(nodes_stack_.size() ==0){
        throw std::logic_error("End Dict Zero Stack Size");
    }

    Node* node_ptr = nodes_stack_.back();
    if(node_ptr->IsDict()){
            nodes_stack_.pop_back();
    }else{
        throw std::logic_error("Dict expected");
    }
    return *this;
}


Builder& Builder::Key(std::string string){
    current_key_ = string;
    is_key_ = true;
    return *this ;
}

Node Builder::Build(){
    if(nodes_stack_.size() > 0){
        throw std::logic_error("Not All Array or Dict End");
    }


    return root_;
}



} // end namespace
