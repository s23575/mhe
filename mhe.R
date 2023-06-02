# install.packages("igraph")

library(igraph)

g <- graph_from_literal(1--0, 3--0, 3--1, 3--2, 4--3, 5--0, 5--2, 5--4, 6--0, 6--1, 6--2, 6--3, 6--4, 6--5, 7--0, 7--1,
                        7--2, 7--3, 7--5, 7--6, 8--1, 8--3, 8--4, 8--5, 8--6, 8--7, 9--0, 9--1, 9--3, 9--4, 9--5, 9--7, 9--8, 0--0)
plot.igraph(g, layout=layout_with_kk, vertex.color="green")
clique_num(g)
largest_cliques(g)