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
            Bubble& move_bubble();
            Bubble& update_health();
            Bubble& set_characteristics();
            Bubble& set_fed();
            Bubble& set_healthy() { m_healthy = false; return *this; }
            Uint32 fill_color() const { return m_fill_color; }
            Uint32 stroke_color() const { return m_stroke_color; }
            double x_center() const { return m_x_center; }
            double y_center() const { return m_y_center; }
            double radius() const { return m_radius; }
            bool is_dead() const { return m_dead; }
            bool is_healthy() const { return m_healthy; }

        private:
            Uint32 set_color(Uint8, Uint8, Uint8);
            Uint32 update_health_color(Uint32);

        private:
            Uint32 m_max_fill_color;
            Uint32 m_max_stroke_color;
            Uint32 m_fill_color;
            Uint32 m_stroke_color;
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
            bool m_healthy;
            bool m_dead;

    };

    // Setters
    inline Bubble& Bubble::set_fed() {
        m_current_health = m_max_health;
        m_healthy = true;
        return *this;
    }

} /* Namespace BC */

#endif //BUBBLE_CREATURES_BUBBLE_H
