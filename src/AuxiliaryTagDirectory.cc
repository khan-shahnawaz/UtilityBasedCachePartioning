#include "AuxiiaryTagDirectory.h"
#include "cache.h"
#include "uncore.h"
#include "ooo_cpu.h"
int UpdateATD(PACKET *packet)
{
    int set= uncore.LLC.get_set(packet->address);
    if (set%SamplingFrequency==0)
    {
        ATD *myTagDirectory = &ooo_cpu[packet->cpu].TagDirectory;
        int mySet = set/SamplingFrequency;
        for (int i=0;i<LLC_WAY;i++)
        {
            if (myTagDirectory->ATDBlock[mySet][i].valid==1 && myTagDirectory->ATDBlock[mySet][i].tag==packet->address)
            {
                
            }
        }
    }
}