3#! /usr/bin/env python
"""
This test checks for the for the Heccer modules 
to be present and importable.
"""
import os
import sys
import pdb

from test_library import add_package_path

add_package_path("heccer")



import heccer as heccer
from heccer.heccer_base import Compartment
from heccer.heccer_base import ChannelAct
from heccer.heccer_base import Intermediary

c1 = Compartment()

c1.dCm = 4.57537e-11
c1.dEm = -0.08
c1.dInitVm = -0.065
c1.dInject = 2e-9
c1.dRa = 360502
c1.dRm = 3.58441e+08
c1.iParent = -1

caKdr = ChannelAct()
caKdr.dReversalPotential = -0.085
caKdr.iReversalPotential = -1
caKdr.dMaximalConductance = 1.004349542e-06
caKdr.iPool = -1
caKdr.pgc.iPower = 4
caKdr.pgc.gc.dInitActivation = 0.3176769506
caKdr.pgc.gc.iTable = -1
caKdr.pgc.gc.parameters.gkA.dHHAddNum = -550.0
caKdr.pgc.gc.parameters.gkA.dHHMult = 10000
caKdr.pgc.gc.parameters.gkA.dHHOffsetM = 0.0
caKdr.pgc.gc.parameters.gkA.iHHFactorFlag = -1
caKdr.pgc.gc.parameters.gkA.dHHAddDen = -1.0
caKdr.pgc.gc.parameters.gkA.dHHOffsetE = 0.055
caKdr.pgc.gc.parameters.gkA.dHHDivE = -0.01


caKdr.pgc.gc.parameters.gkB.dHHAddNum = 125.0
caKdr.pgc.gc.parameters.gkB.dHHOffsetM = 0.0
caKdr.pgc.gc.parameters.gkB.iHHFactorFlag = -1
caKdr.pgc.gc.parameters.gkB.dHHAddDen = 0.0
caKdr.pgc.gc.parameters.gkB.dHHOffsetE = 0.0
caKdr.pgc.gc.parameters.gkB.dHHDiveE = 0.08
caKdr.pgc.gc.parameters.gkB.dHHMultExp = 1.0

caiNaF = ChannelActInact()
caiNaF.dReversalPotential = 0.045
caiNaF.iReversalPotential = -1
caiNaF.dMaximalConductance = 0.00001
caiNaF.iPool = -1
caiNaF.pgcActivation.iPower = 3
caiNaF.pgcActivation.gc.dInitActivation = 0.01224204035
caiNaF.pgcActivation.gc.iTable = -1
# Activation parameters
caiNaF.pgcActivation.gc.parameters.gkA.dHHAddNum = 35.0e3
caiNaF.pgcActivation.gc.parameters.gkA.dHHMultExp = 0.0
caiNaF.pgcActivation.gc.parameters.gkA.dHHOffsetM = 0.0
caiNaF.pgcActivation.gc.parameters.gkA.iHHFactorFlag = -1
caiNaF.pgcActivation.gc.parameters.gkA.dHHAddDen = 0.0
caiNaF.pgcActivation.gc.parameters.gkA.dHHOffsetE = 5.0e-3
caiNaF.pgcActivation.gc.parameters.gkA.dHHDiveE = -10.0e-3
caiNaF.pgcActivation.gc.parameters.gkA.dHHMultExp = 1.0

caiNaF.pgcActivation.gc.parameters.gkB.dHHAddNum = 7.0e3
caiNaF.pgcActivation.gc.parameters.gkB.dHHMultExp = 0.0
caiNaF.pgcActivation.gc.parameters.gkB.dHHOffsetM = 0.0
caiNaF.pgcActivation.gc.parameters.gkB.iHHFactorFlag = -1
caiNaF.pgcActivation.gc.parameters.gkB.dHHAddDen = 0.0
caiNaF.pgcActivation.gc.parameters.gkB.dHHOffsetE = 65.0e-3
caiNaF.pgcActivation.gc.parameters.gkB.dHHDiveE = 20.0e-3
caiNaF.pgcActivation.gc.parameters.gkB.dHHMultExp = 1.0

caiNaF.pgcInactivation.iPower = 1
caiNaF.pgcInactivation.gc.dInitActivation = 0.1930685015
caiNaF.pgcInactivation.gc.iTable = -1
#inactivation parameters
caiNaF.pgcInactivation.gc.parameters.gkA.dHHAddNum = 0.225e3
caiNaF.pgcInactivation.gc.parameters.gkA.dHHMultExp = 0.0
caiNaF.pgcInactivation.gc.parameters.gkA.dHHOffsetM = 0.0
caiNaF.pgcInactivation.gc.parameters.gkA.iHHFactorFlag = -1
caiNaF.pgcInactivation.gc.parameters.gkA.dHHAddDen = 1.0
caiNaF.pgcInactivation.gc.parameters.gkA.dHHOffsetE = 80.0e-3
caiNaF.pgcInactivation.gc.parameters.gkA.dHHDiveE = 10.0e-3
caiNaF.pgcInactivation.gc.parameters.gkA.dHHMultExp = 1.0

caiNaF.pgcInactivation.gc.parameters.gkB.dHHAddNum = 7.5e3
caiNaF.pgcInactivation.gc.parameters.gkB.dHHMultExp = 0.0
caiNaF.pgcInactivation.gc.parameters.gkB.dHHOffsetM = 0.0
caiNaF.pgcInactivation.gc.parameters.gkB.iHHFactorFlag = -1
caiNaF.pgcInactivation.gc.parameters.gkB.dHHAddDen = 0.0
caiNaF.pgcInactivation.gc.parameters.gkB.dHHOffsetE = -33.0e-3
caiNaF.pgcInactivation.gc.parameters.gkB.dHHDiveE = -18.0e-3
caiNaF.pgcInactivation.gc.parameters.gkB.dHHMultExp = 1.0


# intermediary = Intermediary()
# intermediary.comp2mech = [0, 0, -1]
# intermediary.compartments = [c1, c2]
# intermediary.iCompartments = 2










print "Done!"
