#include "../include/Screen.h"

int main() {

    BC::Screen screen;
    BC::Population population(screen.height(), screen.width());
    BC::FoodSupply food_supply(screen.width(), screen.height());

    while(!screen.quit_program()) {
        screen.update_screen(population, food_supply);
        food_supply.generate_food();
        population.check_for_food(food_supply);
        population.update_population();
        food_supply.update_food_supply();
    }

    return 0;
}