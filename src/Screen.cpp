//
// Created by Andrei Vasilev on 2/2/17.
//

#include "../include/Screen.h"

namespace BC {

    Screen::Screen() : m_window(nullptr), m_renderer(nullptr), m_texture(nullptr), m_main_buffer(nullptr){
        // Initialize SDL functionality and create required SDL2 objects
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
        // Initialize SDL library. Must be called before using any SDL2 functionality.
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

    int Screen::height() { return SCREEN_HEIGHT; }
    int Screen::width()  { return SCREEN_WIDTH;  }

    bool Screen::quit_program() {
        // Check for SDL events. If the window is closed, quit the program.
        while(SDL_PollEvent(&m_event)) {
            if(m_event.type == SDL_QUIT)
                return true;
        }
        return false;
    }

    void Screen::draw_population(const Population &population) {

        // Update main_buffer with color and position information of each bubble in population
        for(u_long i = 0 ; i < population.m_current_size; i++) {

            // Use polar coordinates to draw bubbles
            for (float theta = 0; theta < 2 * M_PI; theta += (1 / population.m_bubble_array[i].m_radius)) {

                const Bubble* bubble = &population.m_bubble_array[i];

                Uint32 x = static_cast<Uint32>(bubble->m_x_center + bubble->m_radius * cos(theta));
                Uint32 y = static_cast<Uint32>(bubble->m_y_center + bubble->m_radius * sin(theta));

                m_main_buffer[x + (y * SCREEN_WIDTH)] = bubble->m_color;
            }
        }
    }

    void Screen::update_screen(const Population &population) {
        draw_population(population);
        update_texture();
        update_renderer();
    }

} /* Namespace BC */