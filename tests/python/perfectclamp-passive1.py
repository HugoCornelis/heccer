#! /usr/bin/env python
"""
test of the perfectclamp bindings.
"""
import os
import sys
import pdb

from test_library import add_package_path

add_package_path("heccer",subdir='neurospaces')
add_package_path("experiment", subdir='neurospaces')

from heccer import Heccer
from heccer import Compartment
from heccer import Intermediary


from heccer.heccer_base import HECCER_DUMP_VM_COMPARTMENT_MATRIX
from heccer.heccer_base import HECCER_DUMP_VM_COMPARTMENT_MATRIX_DIAGONALS
from heccer.heccer_base import HECCER_DUMP_VM_MECHANISM_OPERATIONS

HECCER_TESTED_THINGS=1245184

c1 = Compartment()

c1.dCm = 4.57537e-11
c1.dEm = -0.08
c1.dInitVm = -0.068
c1.dInject = 0
c1.dRa = 360502
c1.dRm = 3.58441e+08
c1.iParent = -1

intermediary = Intermediary([c1], [0, -1])


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

i = 0

while i < STEPS:
    
    simulation_time = i * TIME_STEP + TIME_GRANULARITY

    my_heccer.Step(simulation_time)
    perfect_clamp.Step(simulation_time)

    if i % reporting_granularity == 0:
    
        print "Iteration %d" % i
        
        my_heccer.Dump(0, HECCER_TESTED_THINGS)

        if i < STEPS-1:
        
            print "-------"
    
    i += 1
