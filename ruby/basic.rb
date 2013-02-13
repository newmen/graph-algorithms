def max_edges_num(vertex_num)
  vertex_num * (vertex_num - 1) / 2
end

def max_graphs_num(vertex_num)
  2 ** max_edges_num(vertex_num)
end

