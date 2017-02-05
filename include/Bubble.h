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
            Bubble(const int, const int);
            void move_bubble();
            void update_health();
            Uint32 color() const;
            double x_center() const;
            double y_center() const;
            double radius() const;
            bool is_dead() const;

        private:
            void set_color(Uint8, Uint8, Uint8);
            void update_health_color();

        private:
            Uint32 m_color;
            int m_environment_height;
            int m_environment_width;
            double m_x_center;
            double m_y_center;
            double m_radius;
            double m_max_health;
            double m_current_health;
            double m_x_vector;
            double m_y_vector;
            double m_speed;
            bool m_dead;

    };

} /* Namespace BC */

#endif //BUBBLE_CREATURES_BUBBLE_H
