#!/usr/bin/env python

import matplotlib.pyplot as plt
import sys

if __name__ == '__main__':
    points = [[float(x) for x in line.strip().split('\t')] \
                for line in sys.stdin]
    #if len(points) > 0:
    #    for i in range(len(points[0])):
    #        x = [row[i] for row in points]
    #        plt.plot(x)
    plt.plot(points)
    plt.show()
