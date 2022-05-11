#include "cache.h"
#include "uncore.h"
#include "ooo_cpu.h"
// initialize replacement state
void CACHE::llc_initialize_replacement()
{

}
// find replacement victim
uint32_t CACHE::llc_find_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    // baseline LRU
    uint32_t way = 0;
    // fill invalid line first
    for (way=0; way<NUM_WAY; way++) {
        if (block[set][way].valid == false) {
            //cout << way <<"afgn";
    
            DP ( if (warmup_complete[cpu]) {
            cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " invalid set: " << set << " way: " << way;
            cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
            cout << dec << " lru: " << block[set][way].lru << endl; });

            break;
        }
    }
    // LRU victim
    //cout << way<< " "<< NUM_WAY;
    uint32_t cpuBlockCount[NUM_CPUS];
    for (int i = 0; i<NUM_CPUS;i++)
    {
            cpuBlockCount[i]=0;
    }
    for (int i = 0; i<NUM_WAY;i++)
    {
        if (block[set][i].valid)
            cpuBlockCount[block[set][i].cpu]++;
    }
    if (way == NUM_WAY) {
        
        if (cpuBlockCount[cpu]>=uncore.wayAllocated[cpu])
        {
            for (way=0; way<NUM_WAY; way++) {
                if (block[set][way].lru == cpuBlockCount[cpu]-1 && block[set][way].cpu==cpu) {
                    DP ( if (warmup_complete[cpu]) {
                    cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " replace set: " << set << " way: " << way;
                    cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
                    cout << dec << " lru: " << block[set][way].lru << endl; });

                    break;
                }
            }
        }
        else
        {
            for (way=0; way<NUM_WAY; way++) {
                if (block[set][way].lru == cpuBlockCount[block[set][way].cpu]-1 && uncore.wayAllocated[block[set][way].cpu]<cpuBlockCount[block[set][way].cpu]) {
                    DP ( if (warmup_complete[cpu]) {
                    cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " replace set: " << set << " way: " << way;
                    cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
                    cout << dec << " lru: " << block[set][way].lru << endl; });

                    break;
                }
            }
        }
        
    }
    //cout << way<<NUM_WAY;
    if (way == NUM_WAY) {
        cerr << "[" << NAME << "] " << __func__ << " no victim! set: " << set  << endl;
        for (int i=0;i<NUM_CPUS;i++)
        {
            cerr << uncore.wayAllocated[i] << " "<< cpuBlockCount[i] << endl;
        }
        for (int i=0;i<NUM_WAY;i++)
        {
            cerr << "CPU: " << block[set][i].cpu << " LRU: "<< block[set][i].lru << " Valid: " << block[set][i].valid<<"Requested: "<<cpu <<endl;
        }
        assert(0);
    }
    // if (set)
    // {
    // for (int i=0;i<NUM_CPUS;i++)
    // {
    //     cout << cpuBlockCount[i] << ": "<<uncore.wayAllocated[i]<<" |";
    // }
    // cout <<"\n";
    // }
     return way;
}

// called on every cache hit and cache fill
void CACHE::llc_update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type, uint8_t hit)
{
    string TYPE_NAME;
    if (type == LOAD)
        TYPE_NAME = "LOAD";
    else if (type == RFO)
        TYPE_NAME = "RFO";
    else if (type == PREFETCH)
        TYPE_NAME = "PF";
    else if (type == WRITEBACK)
        TYPE_NAME = "WB";
    else
        assert(0);

    if (hit)
        TYPE_NAME += "_HIT";
    else
        TYPE_NAME += "_MISS";

    if ((type == WRITEBACK) && ip)
        assert(0);

    // uncomment this line to see the LLC accesses
    // cout << "CPU: " << cpu << "  LLC " << setw(9) << TYPE_NAME << " set: " << setw(5) << set << " way: " << setw(2) << way;
    // cout << hex << " paddr: " << setw(12) << paddr << " ip: " << setw(8) << ip << " victim_addr: " << victim_addr << dec << endl;

    // baseline LRU
    if (hit && (type == WRITEBACK)) // writeback hit does not update LRU state
        return;
        
    //uncore.UpdatePartition();
    // for (int i=0;i<NUM_CPUS;i++)
    // {
    //     cout << uncore.wayAllocated[i] <<" "<<current_core_cycle[i]<<" ";
    // }
    // cout <<"\n";
    if (hit==0)
    {
        block[set][way].lru=UINT32_MAX;
    }
    // for (int cc=0;cc<NUM_CPUS;cc++)
    // {
    //     cout << cc << ":\n";
    //     for (int i=0;i<LLC_WAY;i++)
    //     {
    //         cout << ooo_cpu[cc].TagDirectory.UMON_Global[i]<<" ";
    //     }
    //     cout << "\n";
    // }
    //cout << cpu << " " << block[set][way].cpu << " " << hit <<endl;
    for (uint32_t i=0; i<NUM_WAY; i++) {
        if (block[set][i].lru < block[set][way].lru && block[set][i].cpu==cpu) {
            block[set][i].lru++;
            
        }
    }
    block[set][way].lru = 0; // promote to the MRU position
    //return lru_update(set, way);
}

void CACHE::llc_replacement_final_stats()
{

}
