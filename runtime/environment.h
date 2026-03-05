#pragma once
#include <string>
#include <unordered_map>
#include <variant>
#include <stdexcept>

// A Value can be either a number or a string
using Value = std::variant<double, std::string>;

class Environment {
public:
    void set(const std::string& name, Value val) {
        vars[name] = std::move(val);
    }

    Value get(const std::string& name) const {
        auto it = vars.find(name);
        if (it == vars.end())
            throw std::runtime_error("Undefined variable: '" + name + "'");
        return it->second;
    }

    bool has(const std::string& name) const {
        return vars.count(name) > 0;
    }

private:
    std::unordered_map<std::string, Value> vars;
};
