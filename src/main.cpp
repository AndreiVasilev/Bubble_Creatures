#include "../include/Screen.h"

int main() {
    BC::Screen screen;
    BC::Population population(screen.height(), screen.width());

    while(!screen.quit_program()) {
        screen.update_screen(population);
        population.update_population();
    }

    return 0;
}