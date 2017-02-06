//
// Created by Andrei Vasilev on 2/4/17.
//

#include "../include/Food.h"

namespace BC {

    Food::Food(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
        : m_environment_width{SCREEN_WIDTH}, m_environment_height{SCREEN_HEIGHT}, m_eaten{false}
    {
        std::random_device rd;
        std::uniform_real_distribution<double> position_dist{0.1, 0.9};

        // Generate random position for top left pixel of food
        m_x_coord = static_cast<int>(position_dist(rd) * m_environment_width);
        m_y_coord = static_cast<int>(position_dist(rd) * m_environment_height);

        // Set initial food color to orange.
        set_color(255, 165, 0);
    }

    void Food::set_color(Uint8 red, Uint8 green, Uint8 blue) {
        m_color = 0;

        // Bit shift color values into place 8888-RGBA.
        m_color += red;   m_color <<= 8;  // Red
        m_color += green; m_color <<= 8;  // Green
        m_color += blue;  m_color <<= 8;  // Blue
        m_color += 0xFF;                  // Alpha
    }

    // Getters
    Uint32 Food::color() const { return m_color; }
    double Food::x_coord() const { return m_x_coord; }
    double Food::y_coord() const { return m_y_coord; }
    bool Food::eaten() const { return m_eaten; }


} /* Namespace BC */