//
// Created by Andrei Vasilev on 2/4/17.
//

#ifndef BUBBLE_CREATURES_FOOD_H
#define BUBBLE_CREATURES_FOOD_H

#include <SDL2/SDL.h>
#include <random>
//#include "../include/Screen.h"

namespace BC {

    class Food {
        public:
            Uint32 m_color;
            double m_x_coord;
            double m_y_coord;
            bool m_eaten;

        public:
            Food();

        private:
            void set_color(Uint8 red, Uint8 green, Uint8 blue);

    };

} /* Namespace BC */


#endif //BUBBLE_CREATURES_FOOD_H
