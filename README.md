# Lin-Kernighan Heuristic

## How to compile?
```
make
```

## How to execute?
```
./bin/lk.exe input_file_name
```

## Input file format
```
6               // number of nodes, node id from 0 ~ n
0 1 2 3 4 5     // initial partition, (# of nodes in 1st partition) <= (# of nodes in 2nd partion)
9               // number of edges
0 2 3           // (node id) (node id) (edge weight)
0 3 5
1 2 8
1 3 1
1 5 3
2 3 5
3 4 6
3 5 4
4 5 9
```
