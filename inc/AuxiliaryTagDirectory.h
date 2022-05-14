#ifndef ATD_H
#define ATD_H
#include "champsim.h"
#include "cache.h"
#define SamplingFrequency 32

// ATD BLOCK
class ATDBlocks
{
public:
    uint64_t tag;
    uint32_t valid, lru;

    ATDBlocks()
    { // constructor to assign initial value
        valid = 0;
        lru = 0;
        tag = 0;
    };
};

class ATD
{
public:
    ATDBlocks **ATDBlock;
    int UMON_Global[LLC_WAY];
    ATD()
    {
        int ATDsets = 1 + LLC_SET / SamplingFrequency;
        ATDBlock = new ATDBlocks *[ATDsets]; // assing memroy for each row.
        for (int i = 0; i < ATDsets; i++)
        {
            ATDBlock[i] = new ATDBlocks[LLC_WAY]; // assigning memory to each block in one row.
        }
        for (int i = 0; i < LLC_WAY; i++)
        {
            UMON_Global[i] = 0; // initially all hit counts are zero.
        }
    };
    void UpdateATD(PACKET *packet, int cpu, int WriteBackHit); // calling updateATD for each updation in axiliary tag dir.
};
#endif
