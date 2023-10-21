#include "exposed/expose.h"

#include <iostream>

// Assume you do not have the ability to edit this class, but you have to use it
// But you would really like to edit `i_` after construction...
class Immutable {
  public:
    constexpr Immutable(int i, int j) : i_{i}, j_{j} {}
    int i() const { return i_; }
    int j() const { return j_; }

  private:
    int j_;
    int i_;
};

// Smuggle the pointer to member i_ out as Plunder
template struct mrl::Smuggle<class StealImuttableI, &Immutable::i_>;

LOOT(Immutable, j_, int);

int main() {
    Immutable immutable{0, 0};

    std::cout << immutable.i() << ',' << immutable.j() << std::endl;

    mrl::Plunder<StealImuttableI, int Immutable::*>::access(immutable) = 1;
    std::cout << immutable.i() << ',' << immutable.j() << std::endl;

    LootImmutablej_{}(immutable) = 2;
    std::cout << immutable.i() << ',' << immutable.j() << std::endl;
}
