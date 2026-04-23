#include "json_builder.h"
#include <memory>
#include <algorithm>

namespace json {

Builder::ValueContext Builder::Value(Node node){
    if(IsRoot()){
        root_ = node;
        value_can_build_ = true;
        return BaseContext{ *this };
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
            node_ptr->AsDict().insert({current_key_,node});
            is_key_ = false;
        }else{
            throw std::logic_error("Value not after Key in Dict");
        }

    }


    //is_value_ =true;
   // is_key_ = false;
    return BaseContext{ *this };
}

Builder::ArrayItemContext Builder::StartArray() {
    if(IsRoot()){
        root_ =  Node(Array());
        nodes_stack_.push_back(&root_);
        return BaseContext {*this};
    }
    Node* node_ptr = nodes_stack_.back();
    if(node_ptr->IsDict()){
        if(is_key_){                
            Node* node_new = new Node(Array());
            auto pair = node_ptr->AsDict().emplace(current_key_,*node_new);
            Node *nd = &pair.first->second;
            nodes_stack_.push_back(std::move(nd));
        }else{
            throw std::logic_error("StartArray not after Key in Dict");
        }
    }

    if(node_ptr->IsArray()){
            Node* node_new = new Node(Array());
            Node& nd = node_ptr->AsArray().emplace_back(std::move(*node_new));
            nodes_stack_.push_back(&nd);
    }
    return BaseContext {*this};
}


Builder::DictValueContext Builder::StartDict() {
    if(IsRoot()){
        root_ = Node(Dict());
        nodes_stack_.push_back(&root_);
       return BaseContext{ *this };
    }

    Node* node_ptr = nodes_stack_.back();
    if(node_ptr->IsArray()){      
        Node* node_new = new Node(Dict());
        Node& nd = node_ptr->AsArray().emplace_back(std::move(*node_new));
        nodes_stack_.push_back(&nd);
    }

    if(node_ptr->IsDict()){
        if(is_key_){
            Node* node_new = new Node(Dict());
            auto pair = node_ptr->AsDict().emplace(current_key_,*node_new);
            Node *nd = &pair.first->second;
            nodes_stack_.push_back(std::move(nd));
        }else{
            throw std::logic_error("StartDict not after Key in Dict");
        }
    }

    return BaseContext{ *this };
}


Builder::BaseContext Builder::BaseContext::EndArray() {
    Node* node_ptr = builder_.nodes_stack_.back();
    if(node_ptr->IsArray()){
        builder_.nodes_stack_.pop_back();
    }
    return *this;
}

Builder::BaseContext Builder::BaseContext::EndDict() {
    Node* node_ptr = builder_.nodes_stack_.back();
    if(node_ptr->IsDict()){
            builder_.nodes_stack_.pop_back();
    }
    return *this;
}


Builder::KeyContext Builder::BaseContext::Key(std::string string){
    builder_.current_key_ = string;
    builder_.is_key_ = true;
    return BaseContext{ *this };
}

Node Builder::BaseContext::Build(){
    if(builder_.nodes_stack_.size() > 0){
        throw std::logic_error("Not All Array or Dict End");
    }


    return builder_.root_;
}



} // end namespace
