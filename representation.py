import json
#pip install networkx
import matplotlib.pyplot as plt
import networkx as nx

# Opening JSON file
f = open('results/graph.json')
adj_list = json.load(f)
f.close()


G = nx.from_dict_of_lists(adj_list['nodes'])
print(G)
color_map = adj_list['colors']
#print(adj_list['colors'])
#print(adj_list['nodes'])

nx.draw(G, with_labels = True, node_color = color_map)
plt.savefig("results/result.png")