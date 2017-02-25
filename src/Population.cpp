//
// Created by Andrei Vasilev on 2/2/17.
//

#include "../include/Population.h"

namespace BC {

    Population::Population(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
    : m_environment_width{SCREEN_WIDTH}, m_environment_height{SCREEN_HEIGHT}
    {
        m_bubble_array.reserve(INITIAL_POPULATION_SIZE);

        for(u_long index = 0; index < INITIAL_POPULATION_SIZE; index++) {
            Bubble bubble(SCREEN_HEIGHT, SCREEN_WIDTH);
            m_bubble_array.push_back(bubble);
        }
    }

    void Population::update_population() {
        for(int index = 0; index < m_bubble_array.size(); index++) {

            // Check bubble health & erase if dead
            m_bubble_array[index].update_health();
            if(m_bubble_array[index].is_dead()) {
                m_bubble_array.erase(m_bubble_array.begin() + index);
                continue;
            }

            // Update bubble positions
            m_bubble_array[index].move_bubble();

            // Check if healthy and then chance at reproducing
            if(m_bubble_array[index].is_healthy()) {
                reproduce(m_bubble_array[index]);
            }

        }

        // If all population dead, exit program.
        if(!m_bubble_array.size())
            exit(EXIT_SUCCESS);
    }

    void Population::check_for_food(FoodSupply &food_supply) {
        for(int index = 0; index < m_bubble_array.size(); index++) {
            Bubble &bubble = m_bubble_array[index];

            if(food_supply.if_in_proximity(bubble))
                bubble.set_fed();
        }
    }

    void Population::reproduce(Bubble &bubble) {
        std::random_device rd;
        std::uniform_real_distribution<double> chance_dist{0.0, 1.0};
        double chance = chance_dist(rd);

        // 0.05% chance to reproduce
        if(chance <= 0.0005 && m_bubble_array.size() <= MAX_POPULATION_SIZE) {
            bubble.set_healthy();
            Bubble newBubble = bubble;
            newBubble.set_characteristics();
            m_bubble_array.push_back(newBubble);
        }
    }


} /* Namespace BC */
