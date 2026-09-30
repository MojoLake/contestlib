#import "../../components.typ": algorithm

#algorithm(
  "Dinic's maximum flow",
  "/graph/dinic.cpp",
  complexity: [$O(V^2 E)$ general; $O(E sqrt(V))$ for unit capacities.],
  notes: [
    Vertices are zero-indexed. Call `add_dir_edge(u, v, capacity)` for a
    directed edge or `add_undir_edge` for an undirected capacity, then
    `run(source, sink)`. Capacities and the returned flow use 64-bit integers.
    The residual graph is mutated, so build a new instance before solving a
    different flow problem.
  ],
)
