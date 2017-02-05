//
// Created by Andrei Vasilev on 2/4/17.
//

#include "../include/FoodSupply.h"

namespace BC {

    FoodSupply::FoodSupply(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
        : m_environment_width {SCREEN_WIDTH}, m_environment_height {SCREEN_HEIGHT}
    {
        m_foods.reserve(MAX_FOOD_COUNT);
    }

    void FoodSupply::generate_food() {
        std::random_device rd;
        std::uniform_real_distribution<double> chance_dist(0.0, 1.0);
        double chance = chance_dist(rd);

        // Food has a 0.5% chance of being generated
        if(chance < 0.005 && m_foods.size() < MAX_FOOD_COUNT) {
            Food food(m_environment_width, m_environment_height);
            m_foods.push_back(food);
        }
    }

} /* Namespace BC */