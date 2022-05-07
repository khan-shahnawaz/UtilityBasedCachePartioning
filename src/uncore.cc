#include "uncore.h"

// uncore
UNCORE uncore;

// constructor
UNCORE::UNCORE() {
    for (int i=0;i<NUM_CPUS;i++)
    {
        wayAllocated[i]=LLC_WAY/NUM_CPUS;
    }
}
