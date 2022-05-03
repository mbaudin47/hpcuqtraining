#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May  3 09:13:39 2022

@author: f37280
"""


# %%
import numpy as np
import openturns as ot
import openturns.viewer as viewer
from matplotlib import pylab as plt
ot.Log.Show(ot.Log.NONE)


# %%
def plot_data_train(x_train, y_train):
    """Plot the data (x_train,y_train) as a Cloud, in red"""
    graph_train = ot.Cloud(x_train, y_train)
    graph_train.setColor("red")
    graph_train.setLegend("Data")
    return graph_train


# %%
def plot_data_test(x_test, y_test):
    """Plot the data (x_test,y_test) as a Curve, in dashed black"""
    graphF = ot.Curve(x_test, y_test)
    graphF.setLegend("Exact")
    graphF.setColor("black")
    graphF.setLineStyle("dashed")
    return graphF


def computeQuantileAlpha(alpha):
    bilateralCI = ot.Normal().computeBilateralConfidenceInterval(1-alpha)
    return bilateralCI.getUpperBound()[0]

# %%
# The following function plots the kriging data.

# %%
def plot_data_kriging(x_test, y_test_MM):
    """Plots (x_test,y_test_MM) from the metamodel as a Curve, in blue"""
    graphK = ot.Curve(x_test, y_test_MM)
    graphK.setColor("blue")
    graphK.setLegend("Kriging")
    return graphK



# %%
# We now compute the bounds of the confidence interval. For this purpose we define a small function
# `computeBoundsConfidenceInterval` :

# %%
def computeBoundsConfidenceInterval(quantileAlpha):
    dataLower = [[y_test_MM[i, 0] - quantileAlpha *
                  conditionalSigma[i, 0]] for i in range(n_test)]
    dataUpper = [[y_test_MM[i, 0] + quantileAlpha *
                  conditionalSigma[i, 0]] for i in range(n_test)]
    dataLower = ot.Sample(dataLower)
    dataUpper = ot.Sample(dataUpper)
    return dataLower, dataUpper

# %%
# In order to create the graphics containing the bounds of the confidence interval, we use the `Polygon`. This will create a colored surface associated to the confidence interval. In order to do this, we create the nodes of the polygons at the lower level `vLow` and at the upper level `vUp`. Then we assemble these nodes to create the polygons. That is what we do inside the `plot_kriging_bounds` function.

# %%

def plot_kriging_bounds(dataLower, dataUpper, n_test, color=[120, 1.0, 1.0]):
    """
    From two lists containing the lower and upper bounds of the region,
    create a PolygonArray.
    Default color is green given by HSV values in color list.
    """
    vLow = [[x_test[i, 0], dataLower[i, 0]] for i in range(n_test)]
    vUp = [[x_test[i, 0], dataUpper[i, 0]] for i in range(n_test)]
    myHSVColor = ot.Polygon.ConvertFromHSV(color[0], color[1], color[2])
    polyData = [[vLow[i], vLow[i+1], vUp[i+1], vUp[i]]
                for i in range(n_test-1)]
    polygonList = [ot.Polygon(polyData[i], myHSVColor, myHSVColor)
                   for i in range(n_test-1)]
    boundsPoly = ot.PolygonArray(polygonList)
    return boundsPoly


plt.close('all')
# %%
g = ot.SymbolicFunction(['x'], ['x*sin(2*pi_*x)'])

# %%
x_train = ot.Uniform(0,1).getSample(5)

xmin = 0.
xmax = 1.
n_test = 100
step = (xmax-xmin)/(n_test-1)
myRegularGrid = ot.RegularGrid(xmin, step, n_test)
x_test = myRegularGrid.getVertices()
y_test = g(x_test)


for i in range(5):
    n_train = x_train.getSize()
    y_train = g(x_train)

    dimension = 1
    basis = ot.ConstantBasisFactory(dimension).build()
    #basis = ot.LinearBasisFactory(dimension).build()
    # basis = ot.QuadraticBasisFactory(dimension).build()
    covarianceModel = ot.MaternModel([1.]*dimension, 1.5)
    algo = ot.KrigingAlgorithm(x_train, y_train, covarianceModel, basis)
    algo.run()
    result = algo.getResult()
    
    krigeageMM = result.getMetaModel()
    y_test_MM = krigeageMM(x_test)
    
    
    # %%
    # In order to compute the kriging error, we can consider the conditional variance. The `getConditionalCovariance` method returns the covariance matrix `covGrid` evaluated at each points in the given sample. Then we can use the diagonal coefficients in order to get the marginal conditional kriging variance. Since this is a variance, we use the square root in order to compute the standard deviation. However, some coefficients in the diagonal are very close to zero and nonpositive, which leads to an exception of the sqrt function. This is why we add an epsilon on the diagonal (nugget factor), which prevents this issue.
    
    # %%
    sqrt = ot.SymbolicFunction(["x"], ["sqrt(x)"])
    epsilon = ot.Sample(n_test, [1.e-8])
    conditionalVariance = result.getConditionalMarginalVariance(x_test)+epsilon
    conditionalSigma = sqrt(conditionalVariance)
    
    # %%
    # The following figure presents the conditional standard deviation depending on :math:`x`.
    
    # %%
    graph = ot.Graph('Standard deviation', 'x',
                     'Standard deviation', True, '')
    box = ot.Interval([0,0],[1,0.5])
    graph.setBoundingBox(box)
    curve = ot.Curve(x_test, conditionalSigma)
    graph.add(curve)
    view = viewer.View(graph)
    plt.savefig('var_step_'+str(i+1)+'.png')
    
    
    
    # %%
    # We define two small lists to draw three different confidence intervals (defined by the alpha value) :
    alphas = [0.05, 0.1, 0.2]
    # three different green colors defined by HSV values
    mycolors = [[120, 1.0, 1.0], [120, 1.0, 0.75], [120, 1.0, 0.5]]
    
    # %%
    # We are ready to display all the previous information and the three confidence intervals we want.
    
    # %%
    # sphinx_gallery_thumbnail_number = 4
    
    validation = ot.MetaModelValidation(x_test,y_test,krigeageMM)
    Q2 = validation.computePredictivityFactor()[0]
    
    graph = ot.Graph('size = %i'%n_train + ', Q2 = %f' %Q2, '', '', True, '')
    box = ot.Interval([0,-1.5],[1,1])
    graph.setBoundingBox(box)
    
    graph.add(plot_data_test(x_test, y_test))
    graph.add(plot_data_train(x_train, y_train))
    graph.add(plot_data_kriging(x_test, y_test_MM))
    
    # Now we loop over the different values :
    for idx, v in enumerate(alphas):
        quantileAlpha = computeQuantileAlpha(v)
        vLow, vUp = computeBoundsConfidenceInterval(quantileAlpha)
        boundsPoly = plot_kriging_bounds(vLow, vUp, n_test, mycolors[idx])
        boundsPoly.setLegend(" %d%% bounds" % ((1.0-v)*100))
        graph.add(boundsPoly)
    
    graph.setAxes(True)
    graph.setXTitle("X")
    graph.setYTitle("Y")
    graph.setLegendPosition("topright")
    view = viewer.View(graph)
    # %%
    # We see that the confidence intervals are small in the regions where two consecutive training points are close to each other (e.g. between :math:`x=11` and :math:`x=11.5`) and large when the two points are not (e.g. between :math:`x=8.` and :math:`x=11`) or when the curvature of the function is large (between :math:`x=4` and :math:`x=6`).
    plt.tight_layout()
    plt.savefig('krig_step_'+str(i+1)+'.png')
    x_train.add(x_test[np.argmax(conditionalSigma)])
    
