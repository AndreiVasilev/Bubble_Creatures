//
// Created by Andrei Vasilev on 2/4/17.
//

#ifndef BUBBLE_CREATURES_FOODSUPPLY_H
#define BUBBLE_CREATURES_FOODSUPPLY_H

#include "../include/Bubble.h"
#include "../include/Food.h"
#include <vector>

namespace BC {

    class FoodSupply {
        public:
            FoodSupply(const int, const int);
            void generate_food();
            void update_food_supply();
            bool if_in_proximity(const Bubble &);
            const unsigned long current_size() const { return m_food_array.size(); }
            const Food& operator[](unsigned long index) const { return m_food_array[index]; }

        private:
            static const unsigned MAX_FOOD_COUNT{10};
            std::vector<Food> m_food_array;
            int m_environment_width;
            int m_environment_height;

    };

} /* Namespace BC */

#endif //BUBBLE_CREATURES_FOODSUPPLY_H
