#pragma once
#include<string>
#include<unordered_map>

inline const std::unordered_map<std::string, std::unordered_map<std::string, double>> kTypeChart = {
    {"Normal", {{"Rock", 0.5}, {"Ghost", 0.0}, {"Steel", 0.5}}},
    {"Fire", {{"Rock", 0.5}, {"Water", 0.5}, {"Dragon", 0.5}, {"Fire", 0.5}, {"Grass", 2.0}, {"Bug", 2.0}, {"Steel", 2.0}, {"Ice", 2.0}}},
    {"Water", {{"Water", 0.5}, {"Grass", 0.5}, {"Dragon", 0.5}, {"Fire", 2.0}, {"Rock", 2.0}, {"Ground", 2.0}}},
    {"Grass", {{"Grass", 0.5}, {"Poison", 0.5}, {"Fire", 0.5}, {"Dragon", 0.5}, {"Steel", 0.5}, {"Flying", 0.5}, {"Bug", 0.5}, {"Rock", 2.0}, {"Ground", 2.0}, {"Water", 2.0}}},
    {"Bug", {{"Fairy", 0.5}, {"Flying", 0.5}, {"Fire", 0.5}, {"Fighting", 0.5}, {"Poison", 0.5}, {"Ghost", 0.5}, {"Steel", 0.5}, {"Psychic", 2.0}, {"Dark", 2.0}, {"Grass", 2.0}}},
    {"Electric", {{"Ground", 0.0}, {"Grass", 0.5}, {"Electric", 0.5}, {"Dragon", 0.5}, {"Water", 2.0}, {"Flying", 2.0}}},
    {"Ice", {{"Ice", 0.5}, {"Fire", 0.5}, {"Water", 0.5}, {"Steel", 0.5}, {"Grass", 2.0}, {"Dragon", 2.0}, {"Flying", 2.0}}},
    {"Fighting", {{"Ghost", 0.0}, {"Psychic", 0.5}, {"Fairy", 0.5}, {"Flying", 0.5}, {"Bug", 0.5}, {"Dark", 2.0}, {"Normal", 2.0}, {"Ice", 2.0}, {"Rock", 2.0}, {"Steel", 2.0}}},
    {"Psychic", {{"Dark", 0.0}, {"Psychic", 0.5}, {"Steel", 0.5}, {"Fighting", 2.0}, {"Poison", 2.0}}},
    {"Dark", {{"Dark", 0.5}, {"Fighting", 0.5}, {"Fairy", 0.5}, {"Psychic", 2.0}, {"Ghost", 2.0}}},
    {"Ghost", {{"Ghost", 2.0}, {"Normal", 0.0}, {"Dark", 0.5}, {"Psychic", 2.0}}},
    {"Poison", {{"Poison", 0.5}, {"Ground", 0.5}, {"Steel", 0.0}, {"Rock", 0.5}, {"Bug", 0.5}, {"Grass", 2.0}, {"Fairy", 2.0}}},
    {"Ground", {{"Flying", 0.0}, {"Grass", 0.5}, {"Bug", 0.5}, {"Fire", 2.0}, {"Rock", 2.0}, {"Poison", 2.0}, {"Steel", 2.0}, {"Electric", 2.0}}},
    {"Rock", {{"Rock", 0.5}, {"Ground", 0.5}, {"Fighting", 0.5}, {"Steel", 0.5}, {"Flying", 2.0}, {"Fire", 2.0}, {"Bug", 2.0}, {"Ice", 2.0}}},
    {"Flying", {{"Rock", 0.5}, {"Steel", 0.5}, {"Electric", 0.5}, {"Grass", 2.0}, {"Bug", 2.0}, {"Fighting", 2.0}}},
    {"Dragon", {{"Dragon", 2.0}, {"Fairy", 0.0}, {"Steel", 0.5}}},
    {"Fairy", {{"Fire", 0.5}, {"Poison", 0.5}, {"Steel", 0.5}, {"Dark", 2.0}, {"Fighting", 2.0}, {"Dragon", 2.0}}},
    {"Steel", {{"Steel", 0.5}, {"Fire", 0.5}, {"Water", 0.5}, {"Electric", 0.5}, {"Fairy", 2.0}, {"Rock", 2.0}, {"Ice", 2.0}}}
};

inline double type_effectiveness(const std::string &move_type, const std::vector<std::string> &defender_types) {
    double multiplier = 1.0;
    auto it = kTypeChart.find(move_type);
    if (it == kTypeChart.end()) return multiplier;

    for (const auto &def_type : defender_types) {
        auto found = it->second.find(def_type);
        if (found != it->second.end()) multiplier *= found->second;
    }
    return multiplier;
}