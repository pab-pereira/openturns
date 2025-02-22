#! /usr/bin/env python

from openturns import *
from math import *

TESTPREAMBLE()
RandomGenerator.SetSeed(0)

try:
    # Instantiate one distribution object
    dim = 1
    meanPoint = Point(dim, 1.0)
    meanPoint[0] = 0.5
    sigma = Point(dim, 1.0)
    sigma[0] = 2.0
    R = CorrelationMatrix(dim)

    distribution1 = Normal(meanPoint, sigma, R)

    # Instantiate another distribution object
    meanPoint[0] = -1.5
    sigma[0] = 4.0

    distribution2 = Normal(meanPoint, sigma, R)

    # Test for sampling
    size = 2000
    nBars = 20
    sample1 = distribution1.getSample(size)
    sample2 = distribution2.getSample(size)

    # Construct histograms
    epsilon = 0.1
    min1 = sample1.getMin()[0]
    max1 = sample1.getMax()[0] + epsilon
    min2 = sample2.getMin()[0]
    max2 = sample2.getMax()[0] + epsilon
    tmp = Point(2)
    tmp[0] = (max1 - min1) / nBars
    data1 = Sample(nBars, tmp)
    tmp[0] = (max2 - min2) / nBars
    data2 = Sample(nBars, tmp)

    for i in range(size):
        index = int(floor((sample1[i, 0] - min1) / (max1 - min1) * nBars))
        data1[index, 1] += 1
        index = int(floor((sample2[i, 0] - min2) / (max2 - min2) * nBars))
        data2[index, 1] += 1

    # Create an empty graph
    myGraph = Graph("Some barplots", "y", "frequency", True, "topleft")

    # Create the first barplot
    myBarPlot1 = BarPlot(data1, min1, "blue", "shaded", "dashed", "histogram1")

    # Then, draw it
    myGraph.add(myBarPlot1)
    myGraph.draw("Graph_BarPlot_a_OT.png")

    # Check that the correct files have been generated by computing their
    # checksum

    # Create the second barplot
    myBarPlot2 = BarPlot(data2, min2, "red", "solid", "solid", "histogram2")

    # Add it to the graph and draw everything
    myGraph.add(myBarPlot2)
    myGraph.draw("Graph_BarPlot_b_OT.png")

except:
    import sys
    print("t_BarPlot_std.py", sys.exc_info()[0], sys.exc_info()[1])
