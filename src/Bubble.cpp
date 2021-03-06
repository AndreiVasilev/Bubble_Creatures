//
// Created by Andrei Vasilev on 2/2/17.
//

#include "../include/Bubble.h"

namespace BC {

    Bubble::Bubble(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
        : m_dead{false}, m_healthy(false), m_environment_width{SCREEN_WIDTH}, m_environment_height{SCREEN_HEIGHT}
    {
        // Create random number device and distributions.
        std::random_device rd;
        std::uniform_int_distribution<int> speed_dist{10, 20};
        std::uniform_real_distribution<double> radius_dist{1.5, 40.0};
        std::uniform_real_distribution<double> health_dist{10, 100};
        std::uniform_real_distribution<double> position_dist{0.1, 0.9};
        std::uniform_real_distribution<double> angle_dist{0.0, 2 * M_PI};

        // Generate random radius and speed, they're indirectly proportional.
        m_radius = radius_dist(rd);
        m_speed = speed_dist(rd) / m_radius;

        // Generate random health based on size
        m_max_health = health_dist(rd) * m_radius;
        m_current_health = m_max_health;

        // Generate random vector
        m_x_vector = m_speed * cos(angle_dist(rd));
        m_y_vector = m_speed * sin(angle_dist(rd));

        // Generate random starting position
        m_x_center = position_dist(rd) * m_environment_width;
        m_y_center = position_dist(rd) * m_environment_height;

        // Set fill color to light green, stroke color to dark green
        m_fill_color = m_max_fill_color = set_color(0, 255, 25);
        m_stroke_color = m_max_stroke_color = set_color(25, 150, 0);
    }

    Uint32 Bubble::set_color(Uint8 red, Uint8 green, Uint8 blue) {
        Uint32 color = 0;

        // Bit shift color values into place 8888-RGBA.
        color += red;   color <<= 8;  // Red
        color += green; color <<= 8;  // Green
        color += blue;  color <<= 8;  // Blue
        color += 0xFF;                // Alpha

        return color;
    }

    Bubble& Bubble::move_bubble() {
        // If bubble is near edge of screen, vector changes to opposite direction.
        if(m_x_center > (m_environment_width - m_radius - 10) || m_x_center < (m_radius + 10))
            m_x_vector = -m_x_vector;
        if(m_y_center > (m_environment_height - m_radius - 10) || m_y_center < (m_radius + 10))
            m_y_vector = -m_y_vector;

        // Move bubble by vector amount
        m_x_center += m_x_vector;
        m_y_center += m_y_vector;

        return *this;
    }

    Bubble& Bubble::update_health() {

        // If health falls below 80%, it's no longer healthy
        if(m_current_health/m_max_health < 0.8)
            m_healthy = false;

        // If health above 10%, there's a chance to lose health.
        // If health falls below 10%, the bubble dies.
        if(m_current_health > m_max_health * 0.1) {
            std::random_device rd;
            std::uniform_real_distribution<double> chance_dist{-2.0, 200.0};
            double chance {chance_dist(rd)};

            // Chance of health loss is directly proportional to speed * size,
            // actual health loss is directly proportional to speed + size
            if (chance < (m_speed * m_radius)) {
                m_current_health -= m_speed/10 + m_radius/10;
                m_fill_color = update_health_color(m_max_fill_color);
                m_stroke_color = update_health_color(m_max_stroke_color);
            }
        }
        else {
            m_dead = true;
        }

        return *this;
    }

    Uint32 Bubble::update_health_color(Uint32 color) {
        Uint8 red   {static_cast<Uint8>(color >> 24)};
        Uint8 green {static_cast<Uint8>(color >> 16)};
        Uint8 blue  {static_cast<Uint8>(color >> 8)};

        // Update color based on the ratio of current_health/max_health
        red *= m_current_health/m_max_health;
        green *= m_current_health/m_max_health;
        blue *= m_current_health/m_max_health;

        return set_color(red, green, blue);
    }

    Bubble& Bubble::set_characteristics() {
        std::random_device rd;
        std::uniform_real_distribution<double> rad_dist{0, 2*M_PI};
        std::uniform_real_distribution<double> speed_dist{0.75, 2.0};
        std::uniform_real_distribution<double> size_dist{0.75, 1.5};

        // Refactor speed by some amount between 75% and 200%
        m_speed = speed_dist(rd);

        // Refactor vectors
        m_x_vector = m_speed * cos(rad_dist(rd));
        m_y_vector = m_speed * sin(rad_dist(rd));

        // Refactor size by some amount between 75% and 150%
        m_radius *= size_dist(rd);

        // Position at center of screen
        m_x_center = m_environment_width/2;
        m_y_center = m_environment_height/2;

        return *this;
    }

} /* Namespace BC */
