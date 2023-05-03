import matplotlib.pyplot as plt

file = open('algo_timings.dat', 'r')
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





# plotting the points

for i in range(algo_count):
    plt.plot(x, [row[i] for row in data], label = algo_names[i])

# naming the x axis
plt.xlabel('Node Count (Edge Count = Node Count * (Node Count / 7))')
# naming the y axis
plt.ylabel('Time (ms)')
# giving a title to my graph
plt.title('Time for graph coloring')

# show a legend on the plot
plt.legend()

# function to show the plot

plt.savefig("time.png")
