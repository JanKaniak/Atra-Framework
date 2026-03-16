#pragma once
#include "json.hpp"
#include "DescriptionFactory.h"
#include "GlobalLastIdOfObject.h"


#include <vector>
#include <memory>
#include <map>
#include <iostream>





class AttributeDescriptionsContainer {
    private:
        std::vector<std::unique_ptr<AttributeDescription>> attributeDescs_;
        DescFactory* descFactory_;
        GlobalLastIdOfObject* lastId_;
    public:
        AttributeDescriptionsContainer();
        bool addDescriptions(AttributeType type,nlohmann::ordered_json &json, std::vector<Message>& messagesHistory);
        bool addDescriptions(std::string attributeName,AttributeType type, std::vector<Message>& messagesHistory);
        AttributeDescription* getDescription(std::string name);
        inline AttributeDescription* getDescription(int i) { return (i >= 0 && i < attributeDescs_.size()) ? attributeDescs_.at(i).get() : nullptr;}
        inline int getSize() { return attributeDescs_.size();}

        inline AttributeDescription* getLast() { 
            if (attributeDescs_.empty()) {
                return nullptr;
            }
            return attributeDescs_.at(attributeDescs_.size() - 1).get(); 
        }
        bool deleteDescription(AttributeDescription *description);
        inline std::vector<AttributeTypeC> getRegisteredDescriptionsTypes() { return descFactory_->getRegisteredDescriptionsTypes();}
        bool deleteLastDescription(std::vector<Message>& messagesHistory);
        bool existsDescription(std::string_view name) {
            for (int i = 0; i < attributeDescs_.size(); ++i)
            {
                if (attributeDescs_.at(i)->getName().compare(name) == 0) {
                    return true;
                }
            }
            return false;
            
        }
        void findDescriptionsByType(std::vector<AttributeDescription*>& vector,AttributeType type);
        AttributeDescriptionsContainer* findDescriptionContainer(std::string_view descriptionName,uint64_t descriptionId) {
            for (int i = 0; i < attributeDescs_.size(); ++i) {
                AttributeDescriptionsContainer* container = attributeDescs_.at(i)->getContainer(descriptionName,descriptionId);
                if (container != nullptr) {
                    return container;
                }
            }
            return this;
        }
        ~AttributeDescriptionsContainer() {
            descFactory_ = nullptr;
            attributeDescs_.clear();
        }
};