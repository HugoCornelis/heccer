#! /usr/bin/env python
"""
This test checks for the for the Heccer modules 
to be present and importable.
"""
import os
import sys
import pdb

from test_library import add_package_path

add_package_path("heccer")



import heccer.heccer
from heccer.heccer_base import Compartment
from heccer.heccer_base import Intermediary

c1 = Compartment()

c1.dCm = 4.57537e-11
c1.dEm = -0.08
c1.dInitVm = -0.068
c1.dInject = 1e-8
c1.dRa = 360502
c1.dRm = 3.58441e+08
c1.iParent = -1


c2 = Compartment()

c2.dCm = 5.755329373e-12
c2.dEm = -0.08
c2.dInitVm = -0.068
c2.dInject = 0
c2.dRa = 772813.4375
c2.dRm = 8.548598272e9
c2.iParent = 0


intermediary = Intermediary()
intermediary.comp2mech = [0, 0, -1]
intermediary.compartments = [c1, c2]
intermediary.iCompartments = 2










print "Done!"
