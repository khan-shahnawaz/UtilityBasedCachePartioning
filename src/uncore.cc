#include "uncore.h"
#include "ooo_cpu.h"
// uncore
UNCORE uncore;

// constructor
UNCORE::UNCORE() {
    for (int i=0;i<NUM_CPUS;i++)
    {
        wayAllocated[i]=LLC_WAY/NUM_CPUS;
    }
}
void UNCORE:: UpdatePartition() // lookahead algorithm (UCP paper)
{
    int balance = LLC_WAY-NUM_CPUS;
    for (int core =0;core<NUM_CPUS;core++)
    {
        wayAllocated[core]=1;
    }
    
    int wayReq[NUM_CPUS];
    float maxUtil[NUM_CPUS];
    
    while (balance>0)
    {
        float curUtil=-1;
        int way=0;
        int maxUtilCore;
        
        for (int core=0;core<NUM_CPUS;core++)
        {
            int alloc = wayAllocated[core];
            maxUtil[core]=-1;
            
            float sum=0;
            int cnt=0;
            
            for (int i=alloc;i<alloc+balance;i++)
            {
                sum+=ooo_cpu[core].TagDirectory.UMON_Global[i];
                cnt+=1;
                if (sum/cnt>maxUtil[core])
                {
                    maxUtil[core]=sum/cnt;
                    wayReq[core]=cnt;
                }
            }
            
            if (curUtil<maxUtil[core])
            {
                curUtil=maxUtil[core];
                maxUtilCore=core;
                way=wayReq[core];
            }
        }
        wayAllocated[maxUtilCore]+=way;
        balance-=way;
        
    }
    for (int core=0;core<NUM_CPUS;core++)
    {
        for (int i=0;i<LLC_WAY;i++)
        {
            ooo_cpu[core].TagDirectory.UMON_Global[i]/=2;
        }
    }
}
