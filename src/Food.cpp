//
// Created by Andrei Vasilev on 2/4/17.
//

#include "../include/Food.h"

namespace BC {

    Food::Food() : m_eaten{false} {
        std::random_device rd;
        std::uniform_real_distribution<double> position_dist{0.1, 0.9};

        // Generate random starting position
        //m_x_coord = static_cast<int>(position_dist(rd) * SCREEN_WIDTH);
        //m_y_coord = static_cast<int>(position_dist(rd) * SCREEN_HEIGHT);

        set_color(0, 0, 255);
    }

    void Food::set_color(Uint8 red, Uint8 green, Uint8 blue) {
        m_color = 0;

        // Bit shift color values into place 8888-RGBA.
        m_color += red;   m_color <<= 8;  // Red
        m_color += green; m_color <<= 8;  // Green
        m_color += blue;  m_color <<= 8;  // Blue
        m_color += 0xFF;                  // Alpha
    }


} /* Namespace BC */