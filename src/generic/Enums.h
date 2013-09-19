#ifndef ENUMS_H
#define ENUMS_H

namespace eImage {
    enum Enum {
        BFeld = 0,
        BFarm,

        VFarmer,
        COUNT
    };
}

namespace eBuilding {
    enum class Work {
        Feld,
        Farm
    };

    enum class Art {
        Weizenfeld = 0,
        Weizenfarm,
        ZZZCOUNT
    };
}

namespace eVec {
    enum class Action {
        Idle, Rotate, Move, Work
    };

    enum class Art {
        Farmer = 0,
        Count
    };
}







#endif // ENUMS_H
