//
// Created by Andrei Vasilev on 2/4/17.
//

#ifndef BUBBLE_CREATURES_FOODSUPPLY_H
#define BUBBLE_CREATURES_FOODSUPPLY_H

#include "../include/Food.h"
#include <vector>

namespace BC {

    class FoodSupply {
        public:
            FoodSupply(const int, const int);
            void generate_food();

        public:
            std::vector<Food> m_foods;

        private:
            static const int MAX_FOOD_COUNT{10};
            int m_environment_width;
            int m_environment_height;

    };

} /* Namespace BC */

#endif //BUBBLE_CREATURES_FOODSUPPLY_H
