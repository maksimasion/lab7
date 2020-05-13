import numpy as np
import matplotlib.pyplot as plt
data=np.loadtxt ("Func.txt")
data1=np.loadtxt ("Proizv.txt")
##############################################
fig, ax = plt.subplots()
ax.plot(data[:,0], data[:,1],color = 'b', linewidth = 2)
ax.plot(data1[:,0], data1[:,1],color = 'r', linewidth = 2)
ax.minorticks_on()

ax.grid(which='major', color = 'g', linewidth = 1)
ax.grid(which='minor', color = 'k', linestyle = ':')

fig.set_figwidth(6)
fig.set_figheight(6)

plt.show()