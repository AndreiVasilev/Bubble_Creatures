//
// Created by Andrei Vasilev on 2/4/17.
//

#include "../include/FoodSupply.h"

namespace BC {

    FoodSupply::FoodSupply(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
        : m_environment_width {SCREEN_WIDTH}, m_environment_height {SCREEN_HEIGHT}
    {
        m_food_array.reserve(MAX_FOOD_COUNT);
    }

    FoodSupply& FoodSupply::generate_food() {
        std::random_device rd;
        std::uniform_real_distribution<double> chance_dist(0.0, 1.0);
        double chance = chance_dist(rd);

        // Food has a 0.5% chance of being generated
        if(chance < 0.005 && m_food_array.size() <= MAX_FOOD_COUNT) {
            Food food(m_environment_width, m_environment_height);
            m_food_array.push_back(food);
        }

        return *this;
    }

    FoodSupply& FoodSupply::update_food_supply() {
        for(int index = 0; index < m_food_array.size(); index++) {
            if(m_food_array[index].eaten())
                m_food_array.erase(m_food_array.begin() + index);
        }
        return *this;
    }

    bool FoodSupply::if_in_proximity(const Bubble &bubble) {
        for(auto &food : m_food_array) {
            if(food.check_touching(bubble.radius(), bubble.x_center(), bubble.y_center())) {
                food.set_eaten();
                return true;
            }
        }
        return false;
    }


} /* Namespace BC */