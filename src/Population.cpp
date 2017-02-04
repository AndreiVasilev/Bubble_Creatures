//
// Created by Andrei Vasilev on 2/2/17.
//

#include "../include/Population.h"

namespace BC {

    Population::Population() {
        for(auto member : m_population) {
            Bubble bubble;
            member = bubble;
        }
    }

    void Population::update_population() {
        for(Bubble &bubble : m_population) {
            bubble.update_health();
            bubble.move_bubble();
        }
    }

}
