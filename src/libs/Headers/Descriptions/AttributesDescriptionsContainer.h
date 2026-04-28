#pragma once
#include "json.hpp"
#include "DescriptionFactory.h"
#include "GlobalLastIdOfObject.h"

#include <vector>
#include <memory>
#include <map>
#include <iostream>

class AttributesDescriptionsContainer
{
private:
    std::vector<std::unique_ptr<AttributeDescription>> attributeDescs_;
    DescFactory *descFactory_;
    GlobalLastIdOfObject *lastId_;

public:
    AttributesDescriptionsContainer();
    bool addDescription(AttributeType type, nlohmann::ordered_json &json, std::vector<Message> *messagesHistory);
    bool addDescription(std::string attributeName, AttributeType type, std::vector<Message> *messagesHistory);
    bool addDescription(std::unique_ptr<AttributeDescription> descriptionPtr);
    bool addDescriptions(AttributesDescriptionsContainer *container,std::vector<Message> *messageHistory);
    AttributeDescription *getDescription(std::string name);
    inline AttributeDescription *getDescription(int i) { return (i >= 0 && i < attributeDescs_.size()) ? attributeDescs_.at(i).get() : nullptr; }
    inline int getSize() { return attributeDescs_.size(); }
    AttributeDescription *getLast();
    bool deleteDescription(AttributeDescription *description);
    inline std::vector<AttributeTypeC> getRegisteredDescriptionsTypes() { return descFactory_->getRegisteredDescriptionsTypes(); }
    bool deleteLastDescription(std::vector<Message> *messagesHistory);
    bool existsDescription(std::string_view name);
    void findDescriptionsByType(std::vector<AttributeDescription *> &vector, AttributeType type);
    AttributesDescriptionsContainer *findDescriptionContainer(std::string_view descriptionName, uint64_t descriptionId);
    ~AttributesDescriptionsContainer();
    AttributesDescriptionsContainer *getDescriptionContainer(std::string_view descriptionName, uint64_t descriptionId);
    void deleteAllDescriptions(std::vector<Message> *messageHistory);
};


class TemplateAttributesDescription {
    private:
    std::string name_;
    std::unique_ptr<AttributesDescriptionsContainer> templateDescriptionContainer_;

    public:
    TemplateAttributesDescription() {
        templateDescriptionContainer_ = std::make_unique<AttributesDescriptionsContainer>();
    }
    TemplateAttributesDescription(std::string name) : name_(name), templateDescriptionContainer_(std::make_unique<AttributesDescriptionsContainer>()) {}

    std::string getName() { return name_;}
    AttributesDescriptionsContainer *getContainer() { return templateDescriptionContainer_.get();}
};




class TemplateAttributesDescriptionContainer
{
private:
    static TemplateAttributesDescriptionContainer *instance_;
    std::vector<std::unique_ptr<TemplateAttributesDescription>> templateDescriptions_;
    TemplateAttributesDescriptionContainer() = default;

public:
    static TemplateAttributesDescriptionContainer *getInstance();
    bool addTemplateDescription(std::string_view name, std::vector<Message> *messageHistory) {
        if (name.empty()) {
            messageHistory->emplace_back("Name cannot be empty!");
            return false;
        }

        if (templateExists(name)) {
            messageHistory->emplace_back("Names must be unique!");
            return false;
        }

        templateDescriptions_.emplace_back(std::make_unique<TemplateAttributesDescription>(name.data()));
        return true;


    }
    bool templateExists(std::string_view name) {
        if (name.empty()) {
            return true;
        }
        for (int i = 0; i < templateDescriptions_.size(); ++i)
        {
            if (templateDescriptions_.at(i)->getName().compare(name) == 0) {
                return true;
            }
        }
        return false;
    }
    AttributesDescriptionsContainer *getContainer(std::string_view name) {
        if (name.empty()) {
            return nullptr;
        }

        for (int i = 0; i < templateDescriptions_.size(); ++i)
        {
            if (templateDescriptions_.at(i)->getName().compare(name) == 0) {
                return templateDescriptions_.at(i)->getContainer();
            }
        }
        
        return nullptr;
    }
    int getSize() { return templateDescriptions_.size(); }
    std::string getNameByPosition(int position) { 
        if (position > templateDescriptions_.size() || position < 0) {
            return "";
        }
        return templateDescriptions_.at(position)->getName();
    }
    TemplateAttributesDescription *getTemplateByPosition(int position) {
        if (position > templateDescriptions_.size() || position < 0) {
            return nullptr;
        }
        return templateDescriptions_.at(position).get();
    }

    bool removeTemplateDescription(TemplateAttributesDescription *templateDescription) {
        if (templateDescription == nullptr) {
            return false;
        }
        for (auto it = templateDescriptions_.begin(); it != templateDescriptions_.end(); ++it) {
            if (it->get() == templateDescription) {
                templateDescriptions_.erase(it);
                return true;
            }
        }
        return false;
    }
};