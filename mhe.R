# install.packages("igraph")

library(igraph)

file_str <- paste(readLines("graph_for_R.txt"), collapse="\n")
file_str

plot.igraph(g, layout=layout_with_kk, vertex.color="green")

clique_num(g)

# get_k_edges_ct <- (clique_num(g) * (clique_num(g)-1))/2
# get_k_edges_ct

get_goal <- clique_num(g) * 1000
get_goal

largest_cliques(g)