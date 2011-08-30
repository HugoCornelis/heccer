#! /usr/bin/env python
"""
test of the perfectclamp bindings.
"""
import os
import sys
import pdb

from test_library import add_package_path

add_package_path("heccer", "neurospaces")
add_package_path("experiment", "neurospaces")


from heccer import Heccer
from heccer import Compartment
from heccer import Intermediary


from heccer.heccer_base import HECCER_DUMP_VM_COMPARTMENT_MATRIX
from heccer.heccer_base import HECCER_DUMP_VM_COMPARTMENT_MATRIX_DIAGONALS
from heccer.heccer_base import HECCER_DUMP_VM_MECHANISM_OPERATIONS

HECCER_TESTED_THINGS=1245184


compartments = []

c1 = Compartment()

c1.dCm = 4.57537e-11
c1.dEm = -0.08
c1.dInitVm = -0.068
c1.dInject = 1e-8
c1.dRa = 360501.9688
c1.dRm = 358440928
c1.iParent = -1

compartments.append(c1)

c2 = Compartment()

c2.dCm = 5.755329373e-12
c2.dEm = -0.08
c2.dInitVm = -0.068
c2.dInject = 0
c2.dRa = 772813.4375
c2.dRm = 8548598272.0
c2.iParent = 0

compartments.append(c2)

c3 = Compartment()

c3.dCm = 9.952665428e-12
c3.dEm = -0.08
c3.dInitVm = -0.068
c3.dInject = 0
c3.dRa = 1107083.25
c3.dRm = 4943399424.0
c3.iParent = 1

compartments.append(c3)


c4 = Compartment()

c4.dCm = 3.048169139e-12
c4.dEm = -0.08
c4.dInitVm = -0.068
c4.dInject = 0
c4.dRa = 306646.9688
c4.dRm = 1.614083584e+10
c4.iParent = 2

compartments.append(c4)



c5 = Compartment()

c5.dCm = 1.866796431e-12
c5.dEm = -0.08
c5.dInitVm = -0.068
c5.dInject = 0
c5.dRa = 147150.0781
c5.dRm = 2.635531059e+10
c5.iParent = 3

compartments.append(c5)


c6 = Compartment()

c6.dCm = 3.81543408e-12
c6.dEm = -0.08
c6.dInitVm = -0.068
c6.dInject = 0
c6.dRa = 335501.9375
c6.dRm = 1.289499341e+10
c6.iParent = 4

compartments.append(c6)


c7 = Compartment()

c7.dCm = 2.239454065e-12
c7.dEm = -0.08
c7.dInitVm = -0.068
c7.dInject = 0
c7.dRa = 230128.9531
c7.dRm = 2.196964147e+10
c7.iParent = 5

compartments.append(c7)


c8 = Compartment()

c8.dCm = 1.754059463e-12
c8.dEm = -0.08
c8.dInitVm = -0.068
c8.dInject = 0
c8.dRa = 169781.8594
c8.dRm = 2.804921958e+10
c8.iParent = 6

compartments.append(c8)


c9 = Compartment()

c9.dCm = 3.37096605e-12
c9.dEm = -0.08
c9.dInitVm = -0.068
c9.dInject = 0
c9.dRa = 442254.125
c9.dRm = 1.459522355e+10
c9.iParent = 7

compartments.append(c9)

c10 = Compartment()

c10.dCm = 5.048512389e-12
c10.dEm = -0.08
c10.dInitVm = -0.068
c10.dInject = 0
c10.dRa = 518791.0938
c10.dRm = 9745444864.0
c10.iParent = 8

compartments.append(c10)


intermediary = Intermediary(compartments)


my_heccer = Heccer(name="unnamed test", pinter=intermediary)


from test_library import INTERVAL_START
from test_library import INTERVAL_END
from test_library import INTERVAL_ENTRIES
from test_library import INTERPOL_INTERVAL_ENTRIES
from test_library import OPTIONS
from test_library import STEPS
from test_library import TIME_GRANULARITY


TIME_STEP=3e-6
STEPS=1000
reporting_granularity=100


my_heccer.SetTimeStep(TIME_STEP)

my_heccer.SetIntervalStart(INTERVAL_START)

my_heccer.SetIntervalEnd(INTERVAL_END)

my_heccer.SetIntervalEntries(INTERVAL_ENTRIES)

my_heccer.SetSmallTableSize(INTERPOL_INTERVAL_ENTRIES)

my_heccer.SetOptions(OPTIONS)

my_heccer.CompileAll()

# Create the perfect clamp and connect it
# to a solved variable.
from experiment.perfectclamp import PerfectClamp

perfect_clamp = PerfectClamp("pc object")

perfect_clamp.SetCommandVoltage(0.1)

address = my_heccer.GetCompartmentAddress(0,"Vm")

perfect_clamp.AddVariable(address)


my_heccer.Initiate()


print "Initiated"

my_heccer.DumpV()

simulation_time = 0.0

print "-------"

for i in range(0,STEPS):

    simulation_time = i * TIME_STEP + TIME_GRANULARITY

    my_heccer.Step(simulation_time)
    perfect_clamp.Step(simulation_time)

    if i % reporting_granularity == 0:
    
        print "Iteration %d" % i
        
        my_heccer.Dump(0, HECCER_TESTED_THINGS)

        if i < STEPS-1:
        
            print "-------"
    

