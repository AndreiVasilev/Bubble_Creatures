//
// Created by Andrei Vasilev on 2/4/17.
//

#include "../include/Food.h"

namespace BC {

    Food::Food(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
        : m_environment_width{SCREEN_WIDTH}, m_environment_height{SCREEN_HEIGHT},
          m_eaten{false}, m_size{14}
    {
        std::random_device rd;
        std::uniform_real_distribution<double> position_dist{0.1, 0.9};

        // Generate random position for top left pixel of food
        m_x_coord = position_dist(rd) * m_environment_width;
        m_y_coord = position_dist(rd) * m_environment_height;

        // Insert food corner coordinates into map<x,y>
        m_coordinates[m_x_coord] = m_y_coord;
        m_coordinates[m_x_coord] = m_y_coord + m_size;
        m_coordinates[m_x_coord + m_size] = m_y_coord;
        m_coordinates[m_x_coord + m_size] = m_y_coord + m_size;

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

    bool Food::check_touching(const double radius, const double x, const double y) {

        double shortest_dist = m_environment_width;

        // Check the distance between the bubble's center and each corner of the food
        for(auto coords : m_coordinates) {
            double dist = sqrt(pow(floor(x - coords.first), 2) + pow(floor(y - coords.second), 2));
            shortest_dist = std::min(dist, shortest_dist);
        }

        // If bubble's radius is larger than the distance from the bubble's center to
        // the food, that means the bubble is touching the food. Return true.
        return ceil(radius) >= floor(shortest_dist);
    }


} /* Namespace BC */