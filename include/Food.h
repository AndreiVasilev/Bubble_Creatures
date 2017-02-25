//
// Created by Andrei Vasilev on 2/4/17.
//

#ifndef BUBBLE_CREATURES_FOOD_H
#define BUBBLE_CREATURES_FOOD_H

#include <SDL2/SDL.h>
#include <cmath>
#include <map>
#include <random>

namespace BC {

    class Food {
        public:
            Food(const int, const int);
            Uint32 color() const { return m_color; }
            double x_coord() const { return m_x_coord; }
            double y_coord() const { return m_y_coord; }
            int size() const { return m_size; }
            bool check_touching(const double, const double, const double);
            bool eaten() const { return m_eaten; }
            void set_eaten() { m_eaten = true; }

        private:
            void set_color(Uint8 red, Uint8 green, Uint8 blue);

        private:
            std::map<double, double> m_coordinates;
            Uint32 m_color;
            double m_x_coord;
            double m_y_coord;
            int m_size;
            int m_environment_height;
            int m_environment_width;
            bool m_eaten;

    };

} /* Namespace BC */


#endif //BUBBLE_CREATURES_FOOD_H
