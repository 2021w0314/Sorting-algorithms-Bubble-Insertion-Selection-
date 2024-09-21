import matplotlib.pyplot as plt
import numpy as np

filename = 'testGraphe.txt'
A, B, C, D, E, F= [], [], [], [], [], []
LENGTH = [10., 100., 1000., 10000., 20000.]
with open(filename, 'r') as f:
    lines = f.readlines()
    for line in lines:
        value = [float(s) for s in line.split()]
        A.append(value[0])
        B.append(value[1])
        C.append(value[2])
        D.append(value[3])
        E.append(value[4])
        F.append(value[5])


fig, (ax1, ax2) = plt.subplots(1, 2, figsize = (10, 10), sharey=True)
# plt.sca(ax1)
# plt.tight_layout()

ax1.set_title("*** Randomly generated ***\nRed<->Bubble    Blue<->Insertion    Yellow<->Selection", fontsize = 8)
ax1.set_xlabel("Length of array", fontsize = 8)
ax1.set_ylabel("Time/m", fontsize = 8)
line1 = ax1.plot(LENGTH, A, 'r-')   # red
line2 = ax1.plot(LENGTH, B, 'b-')   # blue
line3 = ax1.plot(LENGTH, C, 'y-')   # yellow

ax2.set_title("*** Reserved ordered ***\nRed<->Bubble    Blue<->Insertion    Yellow<->Selection", fontsize = 8)
ax2.set_xlabel("Length of array", fontsize = 8)
ax2.set_ylabel("Time/m", fontsize = 8)
line4 = ax2.plot(LENGTH, D, 'r-')   # red
line5 = ax2.plot(LENGTH, E, 'b-')   # blue
line6 = ax2.plot(LENGTH, F, 'y-')   # yellow
plt.show()

# data = np.loadtxt('testGraphe.txt')
# plt.plot()