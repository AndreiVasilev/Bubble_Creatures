//
// Created by Andrei Vasilev on 2/2/17.
//

#include "../include/Bubble.h"

namespace BC {

    Bubble::Bubble(const int SCREEN_HEIGHT, const int SCREEN_WIDTH)
        : m_dead{false}, m_environment_height{SCREEN_HEIGHT}, m_environment_width(SCREEN_WIDTH)
    {
        // Create random number device and distributions.
        std::random_device rd;
        std::uniform_int_distribution<int>     speed_dist{10, 20};
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
        m_x_center = static_cast<int>(position_dist(rd) * m_environment_width);
        m_y_center = static_cast<int>(position_dist(rd) * m_environment_height);

        // Set initial color to green.
        set_color(0, 255, 0);
    }

    void Bubble::set_color(Uint8 red, Uint8 green, Uint8 blue) {
        m_color = 0;

        // Bit shift color values into place 8888-RGBA.
        m_color += red;   m_color <<= 8;  // Red
        m_color += green; m_color <<= 8;  // Green
        m_color += blue;  m_color <<= 8;  // Blue
        m_color += 0xFF;                  // Alpha
    }

    void Bubble::move_bubble() {
        // If bubble is near edge of screen, vector changes to opposite direction.
        if(m_x_center > (m_environment_width - m_radius - 10) || m_x_center < (m_radius + 10))
            m_x_vector = -m_x_vector;
        if(m_y_center > (m_environment_height - m_radius - 10) || m_y_center < (m_radius + 10))
            m_y_vector = -m_y_vector;

        // Move bubble by vector amount
        m_x_center += m_x_vector;
        m_y_center += m_y_vector;
    }

    void Bubble::update_health() {
        std::random_device rd;
        std::uniform_real_distribution<double> chance_dist{-2.0, 200.0};
        double chance {chance_dist(rd)};

        // Rate of health loss is directly proportional to speed * size
        if(chance < (m_speed * m_radius)) {
            if(m_current_health > m_speed) {
                m_current_health -= m_speed / 1000;
                update_health_color();
            }
            else m_dead = true;
        }
    }

    void Bubble::update_health_color() {
        // Update color based on the ratio of current_health/max_health
        Uint8 green {static_cast<Uint8>(m_color >> 16)};
        green *= m_current_health/m_max_health;
        set_color(0, green, 0);
    }

} /* Namespace BC */