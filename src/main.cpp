#include "../include/Screen.h"

int main() {
    BC::Screen screen;
    BC::Population population;

    while(!screen.quit_program()) {
        screen.update(population);
        population.update_population();
    }

    return 0;
}