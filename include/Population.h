//
// Created by Andrei Vasilev on 2/2/17.
//

#ifndef BUBBLE_CREATURES_POPULATION_H
#define BUBBLE_CREATURES_POPULATION_H

#include "../include/Bubble.h"
#include <vector>

namespace BC {

    class Population {
        public:
            u_long m_current_size;
            std::vector<Bubble> m_bubble_array;

        public:
            Population(const int, const int);
            void update_population();

        private:
            static const unsigned MAX_POPULATION_SIZE    {200};
            static const unsigned INITIAL_POPULATION_SIZE {30};
            int m_environment_height;
            int m_environment_width;

    };

} /* Namespace BC */


#endif //BUBBLE_CREATURES_POPULATION_H
