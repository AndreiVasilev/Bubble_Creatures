//
// Created by Andrei Vasilev on 2/2/17.
//

#include "../include/Population.h"

namespace BC {

    Population::Population(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
    : m_environment_width{SCREEN_WIDTH}, m_environment_height{SCREEN_HEIGHT}
    {
        m_bubble_array.reserve(INITIAL_POPULATION_SIZE);
        m_current_size = INITIAL_POPULATION_SIZE;

        for(u_long index = 0; index < INITIAL_POPULATION_SIZE; index++) {
            Bubble bubble(SCREEN_HEIGHT, SCREEN_WIDTH);
            m_bubble_array.push_back(bubble);
        }
    }

    void Population::update_population() {
        for(u_long index = 0; index < m_current_size; index++) {

            // Check bubble health & erase if dead
            m_bubble_array[index].update_health();
            if(m_bubble_array[index].is_dead()) {
                m_bubble_array.erase(m_bubble_array.begin() + index);
                --m_current_size;
                continue;
            }

            // Update bubble positions
            m_bubble_array[index].move_bubble();
        }
    }

    u_long Population::current_size() const { return m_current_size; }


} /* Namespace BC */
