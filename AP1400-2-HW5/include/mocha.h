#ifndef MOCHA_H
#define MOCHA_H

#include "espresso_based.h"
#include "sub_ingredients.h"

class Mocha : public EspressoBased {
private:
    std::vector<Ingredient*> side_items;

public:
    Mocha();
    Mocha(const Mocha& mocha);
	~Mocha() override;

    void operator=(const Mocha& mocha);

    std::string get_name() override;
    double price() override;

    void add_side_item(Ingredient* side);
    std::vector<Ingredient*>& get_side_items();
};

#endif // MOCHA_H