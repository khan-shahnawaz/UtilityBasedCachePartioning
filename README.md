# Group Members

1. Shahnawaz Khan - 2020CSB1123
2. Prashant Mittal - 2020CSB1113
3. Raj - 2020CSB1116
4. Tanish Goyal - 2020CSB1133
5. Anubhav Kataria - 2020CSB1073

# Additional files used

1. AuxiliaryTagDirectory.h and AuxiliaryTagDirectory.cc are used for implementing the function which changes the auxiliary tag directory values, i.e. for finding victim and promotion.

2. run_2core.sh and run_8core are used for running the traces on 2 cores and 8 cores in simulator.

# Updated files

1. uncore.cc and uncore.h - partitioning algorithm is implimented in them. Since greedy fails to see potentially high gains, after the first block if there is no gain from the first block, we used "lookahead algorithm" for partioning the ways for each CPU.

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
$ ./run_4core.sh bimodal-no-no-no-no-lru-4core 1 10 0 gcc_13B.trace.xz gcc_56B.trace.xz GemsFDTD_716B.trace.xz bwaves_1861B.trace.xz
```

3. For 8 cores ->

```
$ chmod +x build_champsim.sh
$ sed -i -e 's/\r$/\n/' build_champsim.sh
$ ./build_champsim.sh bimodal no no no no lru 8
$ chmod +x run_8core.sh
$ sed -i -e 's/\r$/\n/' run_8core.sh
$ ./run_8core.sh bimodal-no-no-no-no-lru-8core 1 10 0 gcc_13B.trace.xz gcc_56B.trace.xz GemsFDTD_716B.trace.xz bwaves_1861B.trace.xz gobmk_135B.trace.xz lbm_1004B.trace.xz leslie3d_1186B.trace.xz milc_744B.trace.xz
```
# Important Notes

1. After extracting the file, download the trace files and then save them in the dcp3_traces folder before running the commands.
2. You can change the given traces to whatever traces you want to test on. (NOTE : Make sure to add the traces in dpc3_traces folder)
3. You can change the number of instructions you want to run on the traces by changing the 10 in last command with any positive integer value.

# Traces Folder

```
https://www.dropbox.com/sh/pgmnzfr3hurlutq/AACciuebRwSAOzhJkmj5SEXBa/CRC2_trace?dl=0&subfolder_nav_tracking=1
```

Note : You can download the trace files from the above link and then save them in the dcp3_traces folder.
