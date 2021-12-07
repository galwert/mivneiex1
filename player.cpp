//
// Created by galwe on 24/11/2021.
//

#include "player.h"

std::ostream &Ehsan::operator<<(std::ostream &os, const Ehsan::IDRank &idRank) {
    os << "rank: "<<idRank.rank <<" id: " <<idRank.ID;
    return os;
}
