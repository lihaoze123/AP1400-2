#include "mocha.h"

Mocha::Mocha() {
    name = "Mocha";

    ingredients.push_back(new Espresso{2});
    ingredients.push_back(new Milk{2});
    ingredients.push_back(new MilkFoam{1});
    ingredients.push_back(new Chocolate{1});
}

Mocha::Mocha(const Mocha &mocha) : EspressoBased(mocha) {
    for (const auto& i : mocha.side_items)
        side_items.push_back(i->copy());
}

Mocha::~Mocha() {
    for (const auto& i : side_items)
        delete i;
    side_items.clear();
}

void Mocha::operator=(const Mocha &mocha) {
    if (this == &mocha)
        return;

    EspressoBased::operator=(mocha);

    side_items.clear();
    for (const auto& i : mocha.side_items)
        side_items.push_back(i->copy());
}

std::string Mocha::get_name() {
    return name;
}

std::vector<Ingredient *>& Mocha::get_side_items() {
    return side_items;
}

double Mocha::price() {
    double res = 0;

    for (const auto& i : ingredients)
        res += i->price();
    for (const auto& i : side_items)
        res += i->price();

    return res;
}