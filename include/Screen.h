//
// Created by Andrei Vasilev on 2/2/17.
//

#ifndef BUBBLE_CREATURES_SCREEN_H
#define BUBBLE_CREATURES_SCREEN_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <cmath>
#include "../include/Population.h"
#include "../include/FoodSupply.h"

namespace BC {

    class Screen {
        public:
            Screen();
            ~Screen();
            void update_screen(const Population &, const FoodSupply &);
            int height();
            int width();
            bool quit_program();

        private:
            void init_SDL();
            void init_window();
            void init_renderer();
            void init_texture();
            void init_buffer();
            void update_texture();
            void update_renderer();
            void draw_population(const Population &);
            void draw_food(const FoodSupply &);

        private:
            static const int SCREEN_HEIGHT {800};
            static const int SCREEN_WIDTH {1000};
            SDL_Window *m_window {nullptr};
            SDL_Renderer *m_renderer {nullptr};
            SDL_Texture *m_texture {nullptr};
            Uint32 *m_main_buffer {nullptr};
            SDL_Event m_event;
    };

} /* Namespace BC */


#endif //BUBBLE_CREATURES_SCREEN_H
