#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May  3 14:32:31 2022

@author: f37280
"""

import numpy as np
import openturns as ot
import matplotlib.pyplot as plt

plt.close('all')
dim = 1

myModel = ot.SquaredExponential([0.1],[1])
# Time grid
tmin = 0.0
step = 0.01
n = 100
ntraj = 10

myTimeGrid = ot.RegularGrid(tmin, step, n)
myProcess = ot.GaussianProcess(myModel, myTimeGrid)

real = np.array(myProcess.getSample(ntraj)).reshape((ntraj,n))

plt.figure()
plt.xlabel('x')
plt.ylabel('y')

for i in range(ntraj):
    plt.plot(np.linspace(0,1,n),real[i,:])
plt.tight_layout()
plt.savefig('UncontionedGP.png')

g = ot.SymbolicFunction(['x'], ['x*sin(2*pi_*x)'])

cov = [0.15,0.2,0.25,0.3,0.3]
x = ot.Sample()
for j in range(5):
    x.add(ot.Uniform(0,1).getSample(1))
    y = g(x)
    myModel = ot.SquaredExponential([cov[j]],[1])
    algo = ot.KrigingAlgorithm(x, y, myModel, ot.ConstantBasisFactory(dim).build())
    algo.setOptimizeParameters(False)
    algo.run()
    res = algo.getResult()
    myProcess = ot.ConditionedGaussianProcess(res,myTimeGrid)
    
    real = np.array(myProcess.getSample(ntraj)).reshape((ntraj,n))

    plt.figure()
    plt.xlabel('x')
    plt.ylabel('y')
    for i in range(ntraj):
        plt.plot(np.linspace(0,1,n),real[i,:])
    plt.plot(x,y,'ko',ms = 7)
    plt.tight_layout()
    plt.savefig('ConditionedGP'+str(j+1)+'.png')
