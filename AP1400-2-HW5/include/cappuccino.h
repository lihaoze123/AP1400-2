#ifndef CAPPUCCINO
#define CAPPUCCINO

#include "espresso_based.h"
#include "sub_ingredients.h"

class Cappuccino : public EspressoBased {
private:
    std::vector<Ingredient*> side_items;

public:
    Cappuccino();
    Cappuccino(const Cappuccino& cap);
	~Cappuccino() override;

    void operator=(const Cappuccino& cap);

    std::string get_name() override;
    double price() override;

    void add_side_item(Ingredient* side);
    std::vector<Ingredient*>& get_side_items();
};

#endif // CAPPUCCINO
