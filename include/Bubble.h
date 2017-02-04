//
// Created by Andrei Vasilev on 2/2/17.
//

#ifndef BUBBLE_CREATURES_BUBBLE_H
#define BUBBLE_CREATURES_BUBBLE_H

#include <cmath>
#include <random>
#include <SDL2/SDL.h>

namespace BC {

    class Bubble {
        public:
            Uint32 m_color;
            double m_x_center;
            double m_y_center;
            double m_radius;

        public:
            Bubble();
            void move_bubble();
            void update_health();

        private:
            static const int SCREEN_WIDTH{1000};
            static const int SCREEN_HEIGHT{800};
            double m_max_health;
            double m_current_health;
            double m_x_vector;
            double m_y_vector;
            double m_speed;
            bool m_dead;

        private:
            void set_color(Uint8, Uint8, Uint8);
            void update_health_color();

    };

}

#endif //BUBBLE_CREATURES_BUBBLE_H
