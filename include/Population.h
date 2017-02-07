//
// Created by Andrei Vasilev on 2/2/17.
//

#ifndef BUBBLE_CREATURES_POPULATION_H
#define BUBBLE_CREATURES_POPULATION_H

#include "../include/Bubble.h"
#include "../include/FoodSupply.h"
#include <vector>

namespace BC {

    class Population {
        public:
            Population(const int, const int);
            void update_population();
            void check_for_food(FoodSupply &);
            const unsigned long current_size() const;
            const Bubble& operator[](unsigned long index) const { return m_bubble_array[index]; }

        private:
            //void update_healths();


        private:
            static const unsigned INITIAL_POPULATION_SIZE {30};
            static const unsigned MAX_POPULATION_SIZE     {50};
            std::vector<Bubble> m_bubble_array;
            int m_environment_height;
            int m_environment_width;

    };

} /* Namespace BC */


#endif //BUBBLE_CREATURES_POPULATION_H
