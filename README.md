# Additional files used

1. AuxiliaryTagDirectory.h and AuxiliaryTagDirectory.cc are used for implementing the function which changes the auxiliary tag directory values, i.e. for finding victim and promotion.

2. run_2core.sh and run_8core are used for running the traces on 2 cores and 8 cores in simulator.

# Updated files

1. uncore.cc and uncore.h - partitioning algorithm is implimented in 'em. Since greedy fails to see potentially high gains after the first block if there is no gain from the first block, we used "lookahead algorithm" for partioning the ways for each cpu.

2. lru.llc_repl has been updated to implement the ucp(utility based cache partitioning).

# Commands

1. For 2 cores ->

```
$ chmod +x build_champsim.sh
$ sed -i -e 's/\r$/\n/' build_champsim.sh
$ ./build_champsim.sh bimodal no no no no lru 2
$ chmod +x run_2core.sh
$ sed -i -e 's/\r$/\n/' run_2core.sh
$ ./run_2core.sh bimodal-no-no-no-no-lru-2core 1 10 0 gcc_13B.trace.xz gcc_56B.trace.xz
```

2. For 4 cores ->

```
$ chmod +x build_champsim.sh
$ sed -i -e 's/\r$/\n/' build_champsim.sh
$ ./build_champsim.sh bimodal no no no no lru 4
$ chmod +x run_4core.sh
$ sed -i -e 's/\r$/\n/' run_4core.sh
$ ./run_4core.sh bimodal-no-no-no-no-lru-4core 1 10 0 gcc_13B.trace.xz gcc_56B.trace.xz GemsFDTD_716B.xz bwaves_1861B.xz
```

3. For 8 cores ->

```
$ chmod +x build_champsim.sh
$ sed -i -e 's/\r$/\n/' build_champsim.sh
$ ./build_champsim.sh bimodal no no no no lru 8
$ chmod +x run_8core.sh
$ sed -i -e 's/\r$/\n/' run_8core.sh
$ ./run_8core.sh bimodal-no-no-no-no-lru-8core 1 10 0 gcc_13B.trace.xz gcc_56B.trace.xz GemsFDTD_716B.xz bwaves_1861B.xz gobmk_135B.xz lbm_1004B.xz leslie3d_1186B.xz milc_744B.xz
```

Note : You can change the given traces to whatever traces you want to test on. (PS : Make sure to add the traces in dpc3_traces folder.)

# Traces Folder

```
httPS ://www.dropbox.com/sh/pgmnzfr3hurlutq/AACciuebRwSAOzhJkmj5SEXBa/CRC2_trace?dl=0&subfolder_nav_tracking=1
```
