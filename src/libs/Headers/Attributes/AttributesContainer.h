#pragma once
#include "ImplementedAttribute.h"
#include "AttributesDescriptionsContainer.h"
#include <vector>
#include <memory>
#include <map>

//------------------------------------------

class AttributesContainer
{
private:
    AttributesDescriptionsContainer *attributeDescs_;
    std::vector<std::unique_ptr<Attribute>> attributes_;
    AttributeFactory *attributeFactory_;

public:
    AttributesContainer();
    AttributesContainer(AttributesDescriptionsContainer *attributeDescs);
    ~AttributesContainer();
    bool addDescription(AttributeType type, nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) { return attributeDescs_->addDescription(type, json, &messagesHistory); }
    bool addDescription(std::string attributeName, AttributeType type, std::vector<Message> &messagesHistory) { return attributeDescs_->addDescription(attributeName, type, &messagesHistory); }
    bool createAttributes(std::vector<Message> &messagesHistory);
    inline Attribute *getLast() { return attributes_.at(attributes_.size() - 1).get(); }
    inline int getSize() { return attributes_.size(); }
    inline int getNumberOfDescriptions() { return attributeDescs_->getSize(); }
    inline Attribute *giveAttribute(int rank) { return attributes_.at(rank).get(); }
    Attribute *giveAttributeByName(std::string name);
    bool contains(std::string attributeName);
    bool deleteAttribute(Attribute *attribute);
    bool deleteAttribute(std::string_view name)
    {
        for (auto it = attributes_.begin(); it != attributes_.end(); ++it)
        {
            if (it->get()->getName().compare(name.data()) == 0)
            {
                AttributeDescription *desc = it->get()->getDescription();
                attributes_.erase(it);
                return attributeDescs_->deleteDescription(desc);
            }
        }
        return false;
    }
    bool deleteAttributeByPath(std::string path)
    {
        if (path.empty())
        {
            return false;
        }
        int index = path.find_first_of(".", 0);
        std::string tmpName;
        std::string tmpPath;
        if (index != path.npos)
        {
            tmpName = path.substr(0, 0 + index).data();
            tmpPath = (index + 1 < path.length()) ? path.substr(index + 1, path.length()).data() : "";
        }
        else
        {
            deleteAttribute(path);
        }
        AttributeCluster *tmpAttribute = dynamic_cast<AttributeCluster*>(giveAttributeByName(tmpName));
        if (tmpAttribute == nullptr || tmpAttribute->getAttributeContainer() == nullptr) {
            return false;

        }
        return tmpAttribute->getAttributeContainer()->deleteAttributeByPath(tmpPath);
    }
    void reverseOrder() { std::reverse(attributes_.begin(), attributes_.end()); }
    inline std::vector<AttributeTypeC> getRegisteredDescriptionsTypes() { return attributeDescs_->getRegisteredDescriptionsTypes(); }
    int getPosition(std::string attributeName);
    AttributeDescription *getDescription(int rank) { return attributeDescs_->getDescription(rank); }
    bool deleteLastDescription(std::vector<Message> &messagesHistory) { return attributeDescs_->deleteLastDescription(&messagesHistory); }
    void changeDescriptionContainer(AttributesDescriptionsContainer *descs) { attributeDescs_ = descs; }
    void setControlTypes(ControlComponentsContainer *components, std::vector<Message> &messagehistory);
    bool existDescription(std::string_view name) { return attributeDescs_->existsDescription(name); }
    void findDescriptionsByType(std::vector<AttributeDescription *> &vector, AttributeType type)
    {
        attributeDescs_->findDescriptionsByType(vector, type);
    }
    void deleteAllAttributes(std::vector<Message> &messageHistory);
    Attribute *getAttributeByPath(std::string path);
    const std::vector<Attribute *> getAttributes() const
    {
        std::vector<Attribute *> tmpVector;
        tmpVector.resize(attributes_.size());
        for (auto &attribute : attributes_)
        {
            tmpVector.push_back(attribute.get());
        }
        return tmpVector;
    }
};