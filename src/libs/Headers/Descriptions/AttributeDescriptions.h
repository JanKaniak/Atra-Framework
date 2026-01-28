#pragma once
#include "json.hpp"
#include "DescriptionFactory.h"

#include <vector>
#include <memory>
#include <map>
#include <iostream>





class AttributeDescriptions {
    private:
        std::vector<std::unique_ptr<AttributeDescription>> attributeDescs_;
        DescFactory& descFactory_ = DescFactory::getInstance();
    public:
        AttributeDescriptions();
        void addDescription(std::string agentName,std::string attributeName, AttributeType type,AttributeTypeVariant minimum, AttributeTypeVariant maximum);
        bool addDescriptions(AttributeType type,nlohmann::ordered_json &json, std::string agentName, std::string &outputMessage);
        AttributeDescription* getDescription(std::string name, std::string agentName);
        inline AttributeDescription* getDescription(int i) { return attributeDescs_.at(i).get();}
        inline int getSize() { return attributeDescs_.size();}

        inline AttributeDescription* getLast() { 
            if (attributeDescs_.empty()) {
                return nullptr;
            }
            return attributeDescs_.at(attributeDescs_.size() - 1).get(); 
        }

        inline int getNumberOfDescriptions() { return attributeDescs_.size();}

        bool deleteDescription(AttributeDescription *description);

        void vypis() {
            for (auto& nvm : attributeDescs_) {
                std::cout << nvm.get()->getAgent() << " " << nvm.get()->getName() << "\n";
            }
        }

};