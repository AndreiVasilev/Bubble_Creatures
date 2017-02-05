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
            Food(const int, const int);
            Uint32 color() const;
            double x_coord() const;
            double y_coord() const;
            bool eaten() const;

        private:
            void set_color(Uint8 red, Uint8 green, Uint8 blue);

        private:
            Uint32 m_color;
            int m_environment_height;
            int m_environment_width;
            double m_x_coord;
            double m_y_coord;
            bool m_eaten;

    };

} /* Namespace BC */


#endif //BUBBLE_CREATURES_FOOD_H
