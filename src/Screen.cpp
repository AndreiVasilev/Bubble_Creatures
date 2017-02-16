//
// Created by Andrei Vasilev on 2/2/17.
//

#include "../include/Screen.h"

namespace BC {

    Screen::Screen() : m_window(nullptr), m_renderer(nullptr), m_texture(nullptr), m_main_buffer(nullptr){
        // Initialize SDL functionality and create required SDL objects
        init_SDL();
        init_window();
        init_renderer();
        init_texture();
        init_buffer();
    }

    Screen::~Screen() {
        delete [] m_main_buffer;
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyTexture(m_texture);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Screen::init_SDL() {
        // Initialize SDL library. Must be called before using any SDL functionality.
        if(SDL_Init(SDL_INIT_VIDEO)) {
            fprintf(stderr, "Failed to initialize SDL2: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    }

    void Screen::init_window() {
        // Create SDL window object
        m_window = SDL_CreateWindow(
                "Bubble Creatures",          // Window title
                SDL_WINDOWPOS_UNDEFINED,     // Initial x position
                SDL_WINDOWPOS_UNDEFINED,     // Initial y position
                SCREEN_WIDTH,                // Width, in pixels
                SCREEN_HEIGHT,               // Height, in pixels
                SDL_WINDOW_ALLOW_HIGHDPI     // Increases resolution
        );

        // Check if window creation failed.
        if(!m_window) {
            fprintf(stderr, "Failed to create SDL window: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    }

    void Screen::init_renderer() {
        // Creates an SDL renderer struct: a rendering context relative to the associated window.
        m_renderer = SDL_CreateRenderer(
                m_window,                      // Window associated with the renderer.
                -1,                            // Index of rendering driver to initialize, -1 to use first available.
                SDL_RENDERER_PRESENTVSYNC |    // Synchronize rendering with window refresh rate.
                SDL_RENDERER_ACCELERATED);     // Allow renderer to use hardware acceleration.

        // Check if renderer creation failed.
        if(!m_renderer) {
            fprintf(stderr, "Failed to create SDL renderer: %s\n", SDL_GetError());
            SDL_DestroyWindow(m_window);
            exit(EXIT_FAILURE);
        }
    }

    void Screen::init_texture() {
        // Creates an SDL texture struct: a set of pixel data to be sent to the renderer.
        m_texture = SDL_CreateTexture(
                m_renderer,                    // The associated renderer.
                SDL_PIXELFORMAT_RGBA8888,      // Format of the pixel color information, RGBA 8 bits per channel.
                SDL_TEXTUREACCESS_STATIC,      // How the texture is accessed when updated.
                SCREEN_WIDTH,                  // Texture width in pixels, equals associated window width.
                SCREEN_HEIGHT                  // Texture height in pixels, equals associated window height.
        );

        // Check if texture creation failed.
        if(!m_texture) {
            fprintf(stderr, "Failed to create SDL texture: %s\n", SDL_GetError());
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            exit(EXIT_FAILURE);
        }
    }

    void Screen::init_buffer() {
        // Initialize main_buffer memory.
        m_main_buffer = new Uint32[SCREEN_HEIGHT * SCREEN_WIDTH];
        memset(m_main_buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));
    }

    void Screen::update_texture() {
        // Updates the texture with new pixel data.
        SDL_UpdateTexture(
                m_texture,                      // Texture to be updated.
                NULL,                           // Area in texture to update, NULL for entire area.
                m_main_buffer,                  // Updated pixel data being sent to the texture.
                SCREEN_WIDTH * sizeof(Uint32)   // Number of bytes in a row of pixel data.
        );
    }

    void Screen::update_renderer() {
        // Copies the newly updated texture into the renderer.
        SDL_RenderCopy(
                m_renderer,    // The renderer to be updated.
                m_texture,     // The source texture.
                NULL,          // Amount of texture to be copied, NULL for entire texture.
                NULL           // Amount of renderer to be updated, NULL for entire renderer.
        );

        // Loads the renderer to the SDL window.
        SDL_RenderPresent(m_renderer);

        // Clear main_buffer (clears bubbles from screen before next draw)
        memset(m_main_buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));
    }

    bool Screen::quit_program() {
        // Check for SDL events. If the window is closed, quit the program.
        while(SDL_PollEvent(&m_event)) {
            if(m_event.type == SDL_QUIT)
                return true;
        }
        return false;
    }

    void Screen::draw_population(const Population &population) {
        // Update main_buffer with position and color of each bubble in population
        for(int index = 0; index < population.current_size(); index++) {
            draw_bubble(population[index]);
        }
    }

    void Screen::draw_bubble(const Bubble &bubble) {

        // Use polar coordinates to draw bubbles
        for (double theta = 0; theta <= M_PI; theta += (1 / bubble.radius())) {

            // Calculate coordinates of bubble, neg_y is for the bottom half of each
            Uint32 x = static_cast<Uint32>(bubble.x_center() + bubble.radius() * cos(theta));
            Uint32 y = static_cast<Uint32>(bubble.y_center() + bubble.radius() * sin(theta));
            Uint32 neg_y = static_cast<Uint32>(bubble.y_center() + bubble.radius() * sin(-theta));

            // Fill bubble with color and stroke color
            for (int i = y; i >= neg_y; i--) {
                if (i < y - 1 && i > neg_y + 1)
                    m_main_buffer[x + (i * SCREEN_WIDTH)] = bubble.fill_color();
                else
                    m_main_buffer[x + (i * SCREEN_WIDTH)] = bubble.stroke_color();
            }
        }
    }

    void Screen::draw_food_supply(const FoodSupply &food_supply) {
        // Update main_buffer with color and position information of each food in food supply
        for(int index = 0; index < food_supply.current_size(); index++) {
            draw_food(food_supply[index]);
        }
    }

    void Screen::draw_food(const Food &food) {
        // Draw a square for each piece of food, coordinates
        // start at the upper left hand corner of each piece.
        for (int y_inc = 0; y_inc < food.size(); y_inc++) {

            for(int x_inc = 0; x_inc < food.size(); x_inc++) {

                Uint32 x = static_cast<Uint32>(food.x_coord() + x_inc);
                Uint32 y = static_cast<Uint32>(food.y_coord() + y_inc);
                m_main_buffer[x + (y * SCREEN_WIDTH)] = food.color();
            }
        }
    }

    void Screen::update_screen(const Population &population, const FoodSupply &food_supply) {
        draw_food_supply(food_supply);
        draw_population(population);
        update_texture();
        update_renderer();
    }

    // Screen Getters
    int Screen::height() { return SCREEN_HEIGHT; }
    int Screen::width() { return SCREEN_WIDTH; }

} /* Namespace BC */