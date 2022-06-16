from timeit import default_timer as timer
import matplotlib.pyplot as plt
from pympler import asizeof

x1 = []
y1 = []
d = {}

for a in range(1, 10**4+1):
    d[a] = a
    x1.append(a)
    y1.append(asizeof.asizeof(d))

x2 = []
y2 = []
d = {}

start_time = timer()
for a in range(1, 10 ** 4 + 1):
    x2.append(a)
    y2.append(timer() - start_time)

f1 = open('Map_statistics_memory.txt', "r")
f2 = open('Map_statistics_time.txt', "r")
lines1 = f1.readlines()
lines2 = f2.readlines()
x3 = []
y3 = []
x4 = []
y4 = []

for i in lines1:
    buff = i.split()
    x3.append(buff[1])
    y3.append(buff[5])

for i in lines2:
    buff = i.split()
    x4.append(buff[1])
    y4.append(buff[3])

plt.plot(x1, y1)
plt.title("Dict memory PY")
plt.xlabel("elements")
plt.ylabel("byte")
plt.show()
plt.savefig('Dict_memory.png')

plt.plot(x2, y2)
plt.title("Dict time in seconds PY")
plt.xlabel("elements")
plt.ylabel("time")
plt.show()
plt.savefig('Dict_time_in_seconds.png')

plt.plot(x3, y3)
plt.title("Map memory C++")
plt.xlabel("elements")
plt.ylabel("byte")
plt.show()
plt.savefig('Map_memory.png')

plt.plot(x4, y4)
plt.title("Map time in ms C++")
plt.xlabel("elements")
plt.ylabel("time")
plt.show()
plt.savefig('Map_time_in_ms.png')
