#!/usr/bin/env python

import numpy as np
import sys

if __name__ == '__main__':
    if len(sys.argv) == 1:
        print("Must specify n")
        exit()
    n = float(sys.argv[1])
    t = np.linspace(-10, 10, n)
    x = np.sin(t)
    for num in x:
        print(num)
