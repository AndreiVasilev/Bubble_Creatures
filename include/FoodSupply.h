//
// Created by Andrei Vasilev on 2/4/17.
//

#ifndef BUBBLE_CREATURES_FOODSUPPLY_H
#define BUBBLE_CREATURES_FOODSUPPLY_H

#include "../include/Food.h"

namespace BC {

    class FoodSupply {
        private:
            static const int MAX_FOOD_COUNT{10};

        public:
            Food m_foods[MAX_FOOD_COUNT];

    };

} /* Namespace BC */

#endif //BUBBLE_CREATURES_FOODSUPPLY_H
