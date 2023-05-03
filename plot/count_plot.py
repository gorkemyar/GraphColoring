import matplotlib.pyplot as plt

file = open('../results/color_count.dat', 'r')
lines = file.readlines()

algo_names = []
line = lines[0]

word = ""
first = True
for ch in line:
    if str(ch).isalnum() or ch in ".()_":
        word += ch
    else:
        if word != "":
            if first:
                first = False
            else:
                algo_names.append(word)
            word = ""


algo_count = len(algo_names)

x = []
data = []
for line in lines[1:]:
    word = ""
    tmp = []*algo_count

    first = True
    for ch in line:
        if str(ch).isalnum() or ch in ".()_":
            word += ch
        else:
            if word != "":
                if first:
                    first = False
                    x.append(int(word))
                else:
                    tmp.append(float(word))
                word = ""
    data.append(tmp) 


for i in range(algo_count):
    plt.plot(x, [row[i] for row in data], label = algo_names[i])

plt.xlabel('Node Count (Edge Count = Node Count * (Node Count / 7)))')
plt.ylabel('Color Count')
plt.title('Color count for graph coloring')
plt.legend()
plt.savefig("../results/count.png")

