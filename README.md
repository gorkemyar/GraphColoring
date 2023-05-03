# GraphColoring

## Description

This project is a graph coloring program that uses a greedy algorithms to color a graph. The program takes in node count and edge count as input and then generates a random graph. The program then colors the graph using a greedy algorithm and outputs the number of colors used.
As an output the program also creates a .json file that contains the graph and the colors used to color the graph.

Another input is the algorithm to be used. The program can use the following algorithms:

- Greedy
- LDO (Largest Degree Order)
- RLF (Recursive Largest First)
- DSATUR (Degree of Saturation)
- Welsh Powell

All of the algorithms are greedy algorithms but they use different heuristics to color the graph. The heuristics that are used are as follows:

- Greedy: Sorts the nodes in descending order according to their degree and then colors the nodes in that order. While picking a color for a node it picks the first color that is not used by any of the adjacent nodes.

- LDO: Sorts the nodes in ascending order according to their degree and then colors the nodes in that order. While picking a color for a node it picks the first color that is not used by any of the adjacent nodes.

- RLF: Let S = an empty solution. Also, let G = (V, E) be the graph we wish to color, comprising a vertex set V and an edge set E.

  1.  The first vertex added to S should be the vertex in G that has the largest number of neighbors
  2.  Subsequent vertices added to S should be chosen as those that
      Find the vertices that are not currently adjacent to any vertex in S
      Sort the vertices according to their maximal number of neighbors that are adjacent to vertices in S
      (In a ties condition select the vertex with the minimum number of neighbors not in S.)
      Add these vertices to S in the order determined by the sorting if it is possible.
  3.  Remove S from G, check whether G is empty if not start from the beginning

- DSATUR: 1. Arrange the vertices by decreasing order of degrees. 2. Color a vertex of maximal degree with color 1. 3. Choose a vertex with a maximal saturation degree. If there is an equality,
  choose any vertex of maximal degree in the uncolored subgraph. 4. Color the chosen vertex with the least possible (lowest numbered) color. 5. If all the vertices are colored, stop. Otherwise, return to 3.

- Welsh Powell: Sorts the nodes in descending order according to their degree and then colors the nodes in that order. While picking a color for a node it picks the least used color. Then try to color unclored nodes with the same color.

## Installation

The program can be installed with the following command:

        git clone https://github.com/gorkemyar/GraphColoring.git

## Running

There are some options to run program:

- Run with default values (node count 30, edge count 100, algorithm Greedy)

  First use command "make" to create executable file. Then run the program with the following command:

        ./main

  If you run the program with main you will only generate graph.json file in results directory. If you would like to see the graph you can use the following command:

        ./runall

  This command will generate graph.json file and also generate result.png file in results directory. You can see the colored graph in result.png file.

- Run with custom values

  you can run the program with custom values. You can use the following command:

        ./main <node count> <edge count> <algorithm>

  Note: node count and edge count must be positive integers.

  For using the following algorithms the options are:
  "g" for Greedy
  "l" for LDO
  "r" for RLF
  "d" for DSATUR
  "w" for Welsh Powell

  For example if you would like to run the program with 50 nodes, 200 edges and RLF algorithm you can use the following command:

        ./main 50 200 r

  If you run the program with main you will only generate graph.json file in results directory. If you would like to see the graph you can use the following command:

        ./runall 50 200 r

  This command will generate graph.json file and also generate result.png file in results directory. You can see the colored graph in result.png file.
