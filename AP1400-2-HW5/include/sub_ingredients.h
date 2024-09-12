#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"
#include <string>
#include <cstddef>

using std::size_t;

#define DEFCLASS(__NAME, __PRICE)   \
class __NAME : public Ingredient { \
public: \
    __NAME(size_t units) : Ingredient{__PRICE, units} { \
        this->name = #__NAME; \
    } \
     \
    virtual std::string get_name() const { return this->name; } \
}

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

#endif // SUB_INGREDIENTS_H
