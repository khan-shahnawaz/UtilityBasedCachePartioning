
#include "AuxiliaryTagDirectory.h"
//#include "cache.h"
#include "uncore.h"
#include "ooo_cpu.h"
int updateInterval = 5000000;
int lastRefreshCycle = 0;
void ATD::UpdateATD(PACKET *packet, int cpu, int WriteBackHit)
{ // funtion to update auxiliary tag directory

    int set = uncore.LLC.get_set(packet->address); // getting set for current packet
    int curCycle = 0;
    for (int i = 0; i < NUM_CPUS; i++)
    {
        if (current_core_cycle[i] > curCycle)
        {
            curCycle = current_core_cycle[i];
        }
    }
    if ((curCycle - lastRefreshCycle) >= updateInterval)
    {
        uncore.UpdatePartition();
        lastRefreshCycle = curCycle;
    }
    if (set % SamplingFrequency == 0)
    { // If the set is to be included in Set sampling

        ATD *myTagDirectory = &ooo_cpu[cpu].TagDirectory; // Getting tag directory of the CPU sending a packet
        int mySet = set / SamplingFrequency;              // Set number in ATD using DSS
        for (int i = 0; i < LLC_WAY; i++)
        { // Checking if it is a hit in ATD

            if (myTagDirectory->ATDBlock[mySet][i].valid == 1 && myTagDirectory->ATDBlock[mySet][i].tag == packet->address)
            { // Case for a Hit block

                myTagDirectory->UMON_Global[myTagDirectory->ATDBlock[mySet][i].lru]++;
                if (WriteBackHit == 1)
                {
                    return;
                }
                for (int way = 0; way < LLC_WAY; way++)
                { // Updating the LRU position of the ATD Block

                    if (myTagDirectory->ATDBlock[mySet][i].lru > myTagDirectory->ATDBlock[mySet][way].lru)
                    { // incrementing lru values of each block of current row which has lru less than that of hit block.

                        myTagDirectory->ATDBlock[mySet][way].lru++;
                    }
                }

                myTagDirectory->ATDBlock[mySet][i].lru = 0; // assigning current block mru position.
                return;
            }
        }

        for (int i = 0; i < LLC_WAY; i++)
        {
            if (myTagDirectory->ATDBlock[mySet][i].valid == 0)
            { // Case for miss block and at least one valid bit is 0

                myTagDirectory->ATDBlock[mySet][i].lru = LLC_WAY;
                myTagDirectory->ATDBlock[mySet][i].tag = packet->address;
                myTagDirectory->ATDBlock[mySet][i].valid = 1;
                for (int way = 0; way < LLC_WAY; way++)
                {
                    if (myTagDirectory->ATDBlock[mySet][way].lru < myTagDirectory->ATDBlock[mySet][i].lru)
                    { // incrementing lru values of each block of current row which has lru less than that of requested block.

                        myTagDirectory->ATDBlock[mySet][way].lru++;
                    }
                }
                myTagDirectory->ATDBlock[mySet][i].lru = 0; // assigning current block mru position.
                return;
            }
        }

        for (int i = 0; i < LLC_WAY; i++)
        {
            // Case for miss block and all valid bits are 1
            if (myTagDirectory->ATDBlock[mySet][i].lru == LLC_WAY - 1)
            { // Case for miss block and valid bit is 1

                myTagDirectory->ATDBlock[mySet][i].tag = packet->address;
                for (int way = 0; way < LLC_WAY; way++)
                {

                    if (myTagDirectory->ATDBlock[mySet][way].lru < myTagDirectory->ATDBlock[mySet][i].lru)
                    { // incrementing lru values of each block of current row which has lru less than that of requested block.

                        myTagDirectory->ATDBlock[mySet][way].lru++;
                    }
                }
                myTagDirectory->ATDBlock[mySet][i].lru = 0; // assigning current block mru position.
                return;
            }
        }
    }
    return;
}
