#include "json_builder.h"
#include <memory>
#include <algorithm>

namespace json {

Builder::ValueContext Builder::Value(Node node){
    if(nodes_stack_.size() ==0){
        root_ = node;
        return BaseContext{ *this };

    }

    Node* node_ptr = nodes_stack_.back();
    if(node_ptr->IsArray()){
        node_ptr->AsArray().emplace_back(node);
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
            node_ptr->AsDict().insert({current_key_,*node_new});
            nodes_stack_.push_back(node_new);
        }else{
            throw std::logic_error("StartArray not after Key in Dict");
        }
    }



    return BaseContext {*this};
}

Builder::BaseContext Builder::BaseContext::EndArray() {

    Node* node_ptr = builder_.nodes_stack_.back();
    if(node_ptr->IsArray()){
            builder_.nodes_stack_.pop_back();

    }

    return *this;
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
        node_ptr->AsArray().emplace_back(*node_new);
        nodes_stack_.push_back(std::move(node_new));
    }

    return BaseContext{ *this };
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
    // if(nodes_stack_.size() == 1){
    //std::cout << "stack size: " << nodes_stack_.size()  << std::endl;
/*
    if(builder_.nodes_stack_.empty()){
        throw std::logic_error("nodes_stack_ empty");
    }

    if(builder_.in_array_  || builder_.in_dict_){
        throw std::logic_error("builder in array or in dict");
    }

    if(builder_.nodes_stack_.size() > 1){
        throw std::logic_error("nodes stack size >1");
    }

    if(builder_.nodes_stack_.size() == 0){
        throw std::logic_error("nodes stack size =0");
    }


    Node node = *builder_.nodes_stack_.back();
    if(builder_.first_run_){
        throw std::logic_error("Build first run");
    }
    if(builder_.nodes_stack_.empty()){
        throw std::logic_error("nodes_stack_ empty");
    }
*/
   // std::cout << "builder: " <<builder_.nodes_stack_.size() << std::endl;
    //Node node = *builder_.nodes_stack_[0];
   // builder_.root_ = std::move(node);

    return builder_.root_;
}



} // end namespace
