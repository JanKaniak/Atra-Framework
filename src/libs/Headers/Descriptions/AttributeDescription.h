#pragma once
#include "json.hpp"

#include <string>
#include <variant>
#include <memory>

enum class AttributeType
{
    INT,
    DOUBLE,
    BOOL,
    CHAR
};

using AttributeTypeVariant = std::variant<int, double, char>;

class AttributeDescription
{
protected:
    std::string name_;
    AttributeType type_;
    std::string agent_;

public:
    AttributeDescription(AttributeType type) : type_(type) {};
    inline std::string getName() { return name_; };
    inline AttributeType getType() { return type_; };
    inline void setName(std::string name) { name_ = name; };
    inline std::string getAgent() { return agent_;}
    void setAgent(std::string agent) { agent_ = agent;}

public:
    virtual double getMin() = 0;
    virtual double getMax() = 0;
    virtual ~AttributeDescription() {};
    virtual std::unique_ptr<AttributeDescription> clone() = 0;
    virtual void setLimit(AttributeTypeVariant minimum, AttributeTypeVariant maximum) = 0;
    virtual bool jsonParse(nlohmann::json &json, std::string &outputMessage) = 0;
};

class AttributeDescription_int : public AttributeDescription
{
private:
    int min_ = 10;
    int max_ = 50;

public:
    AttributeDescription_int() : AttributeDescription(AttributeType::INT) {}
    inline double getMin() override { return min_; }
    inline double getMax() override { return max_; }
    std::unique_ptr<AttributeDescription> clone() override;
    void setLimit(AttributeTypeVariant minimum, AttributeTypeVariant maximum) override;
    bool jsonParse(nlohmann::json &json, std::string &outputMessage) override;
};

/*class AtributeDescription_double : public AtributeDescription
{
private:
    double min_ = 10;
    double max_ = 50;

public:
    AtributeDescription_double() : AtributeDescription(AtributeType::DOUBLE) {}
    inline double getMin() override { return min_; }
    inline double getMax() override { return max_; }
    AtributeDescription_double* clone() override;
    void setLimit(AtributeTypeVariant minimum, AtributeTypeVariant maximum) override;
};

class AtributeDescription_char : public AtributeDescription
{
private:
    int min_ = 0;
    int max_ = 1;

public:
    AtributeDescription_char() : AtributeDescription(AtributeType::CHAR) {}
    inline double getMin() override { return min_; }
    inline double getMax() override { return max_; }
    AtributeDescription_char* clone() override;
    void setLimit(AtributeTypeVariant minimum, AtributeTypeVariant maximum) override;
};*/