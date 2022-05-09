#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Apr 22 11:52:42 2022

@author: f37280
"""

import numpy as np
import matplotlib.pyplot as plt

plt.close('all')

def fun(x,alpha, beta):
    return alpha*x*np.sin(beta*x)




N = 10
xdata = np.random.rand(N)
ydata = fun(xdata,1.,np.pi)+np.random.randn(N)*0.05


plt.figure(figsize = (16,10))
plt.plot(xdata,ydata,'*', label = 'Data')


xplot = np.arange(0,1,0.01)
yplot = fun(xplot,1, np.pi)
plt.plot(xplot,yplot, 'k--', label = 'True model')

for i in range(10):
    a = np.random.rand(1)+0.5
    b = np.random.rand(1)*2+2
    xplot = np.arange(0,1,0.01)
    yplot = fun(xplot,a,b)
    plt.plot(xplot,yplot, alpha = 0.5)
plt.xlabel('x', fontsize = 16)
plt.ylabel('y', fontsize = 16)
plt.legend(fontsize = 20)
plt.tight_layout()
plt.savefig('example',format = 'pdf')