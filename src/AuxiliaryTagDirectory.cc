
#include "AuxiliaryTagDirectory.h"
//#include "cache.h"
#include "uncore.h"
#include "ooo_cpu.h"
int updateInterval= 5000000;
int lastRefreshCycle =0;
void ATD::UpdateATD(PACKET *packet,int cpu, int WriteBackHit)
{
    
    int set= uncore.LLC.get_set(packet->address);
    int curCycle=0;
    for (int i=0;i<NUM_CPUS;i++)
    {
        if (current_core_cycle[i]>curCycle)
        {
            curCycle=current_core_cycle[i];
        }
    }
    if ((curCycle-lastRefreshCycle)>=updateInterval)
    {
        uncore.UpdatePartition();
        lastRefreshCycle=curCycle;
    }
    if (set%SamplingFrequency==0) //If the set is included in Set sampling
    {
        
        ATD *myTagDirectory = &ooo_cpu[cpu].TagDirectory; // Getting tag directory of the CPU sending a packet
        int mySet = set/SamplingFrequency; //The set in the ATD is mapped to set in the LLC
        for (int i=0;i<LLC_WAY;i++) //Checking if it is a hit in ATD
        {
            if (myTagDirectory->ATDBlock[mySet][i].valid==1 && myTagDirectory->ATDBlock[mySet][i].tag==packet->address)
            {
                
                
                myTagDirectory->UMON_Global[myTagDirectory->ATDBlock[mySet][i].lru]++; //Incrementing the corresponding LRU position in the UMON after a hit
                if (WriteBackHit==1)
                {
                    return;
                }
                for (int way=0;way<LLC_WAY;way++) // Updating the LRU position of the ATD Block
                {
                    if (myTagDirectory->ATDBlock[mySet][i].lru>myTagDirectory->ATDBlock[mySet][way].lru)
                    {
                        myTagDirectory->ATDBlock[mySet][way].lru++;
                    }
                }
                
                myTagDirectory->ATDBlock[mySet][i].lru=0;
                return;
            }
            
        }
        
        for (int i=0;i<LLC_WAY;i++)
        {
            if (myTagDirectory->ATDBlock[mySet][i].valid==0)
            {
                myTagDirectory->ATDBlock[mySet][i].lru=LLC_WAY;
                myTagDirectory->ATDBlock[mySet][i].tag=packet->address;
                myTagDirectory->ATDBlock[mySet][i].valid=1;
                for (int way=0;way<LLC_WAY;way++)
                {
                    if (myTagDirectory->ATDBlock[mySet][way].lru<myTagDirectory->ATDBlock[mySet][i].lru)
                    {
                        myTagDirectory->ATDBlock[mySet][way].lru++;
                    }
                }
                myTagDirectory->ATDBlock[mySet][i].lru=0;
                return;
            }
        }
        
        for (int i=0;i<LLC_WAY;i++)
        {
            if (myTagDirectory->ATDBlock[mySet][i].lru==LLC_WAY-1)
            {
                myTagDirectory->ATDBlock[mySet][i].tag=packet->address;
                for (int way=0;way<LLC_WAY;way++)
                {
                    if (myTagDirectory->ATDBlock[mySet][way].lru<myTagDirectory->ATDBlock[mySet][i].lru)
                    {
                        myTagDirectory->ATDBlock[mySet][way].lru++;
                    }
                }
                myTagDirectory->ATDBlock[mySet][i].lru=0;
                return;
            }
            
        }
        
    }
    return;
}
