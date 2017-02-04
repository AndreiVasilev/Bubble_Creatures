//
// Created by Andrei Vasilev on 2/2/17.
//

#ifndef BUBBLE_CREATURES_POPULATION_H
#define BUBBLE_CREATURES_POPULATION_H

#include "../include/Bubble.h"

namespace BC {

    class Population {
        public:
            static const int m_population_size{20};
            Bubble m_population[m_population_size];

        public:
            Population();
            void update_population();
    };

} /* Namespace BC */


#endif //BUBBLE_CREATURES_POPULATION_H
