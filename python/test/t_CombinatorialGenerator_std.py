#! /usr/bin/env python

import openturns as ot

generators = [
    ot.Tuples([4, 6, 9]), ot.KPermutations(4, 6), ot.Combinations(4, 6)]

for generator in generators:
    print('generator:', generator)
    subsets = generator.generate()
    print('subset:', subsets)
