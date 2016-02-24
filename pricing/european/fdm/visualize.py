#!/usr/bin/env python
# coding=utf-8

from mpl_toolkits.mplot3d import Axes3D
import matplotlib
import numpy as np
from matplotlib import cm
from matplotlib import pyplot as plt

x, y, z = np.loadtxt('fdm.csv', unpack=True)

X = np.reshape(x, (20,20))
Y = np.reshape(y, (20,20))
Z = np.reshape(z, (20,20))

print X.shape, Y.shape, Z.shape

step = 0.04
maxval = 1.0
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.YlGnBu_r)
ax.set_zlim3d(0, 1.0)
ax.set_xlabel(r'$S$')
ax.set_ylabel(r'$T-t$')
ax.set_zlabel(r'$C(S,t)$')
plt.show() 
