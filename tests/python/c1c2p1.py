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

from heccer import Heccer
from heccer import Compartment
from heccer import Intermediary

c1 = Compartment()

c1.dCm = 4.57537e-11
c1.dEm = -0.08
c1.dInitVm = -0.068
c1.dInject = 1e-8
c1.dRa = 360502
c1.dRm = 3.58441e+08
c1.iParent = -1

c2 = Compartment()

c2.dCm = 4.57537e-11
c2.dEm = -0.08
c2.dInitVm = -0.068
c2.dInject = 0
c2.dRa = 360502
c2.dRm = 3.58441e+08
c2.iParent = 0



intermediary = Intermediary([c1, c2])

#intermediary.SetCompartments([c1, c2])

#intermediary.SetComp2Mech([0, 0, -1])



my_heccer = Heccer(name="unnamed test", pinter=intermediary)

from test_library import TIME_STEP
from test_library import INTERVAL_START
from test_library import INTERVAL_END
from test_library import INTERVAL_ENTRIES
from test_library import INTERPOL_INTERVAL_ENTRIES
from test_library import OPTIONS
from test_library import STEPS
from test_library import TIME_GRANULARITY

my_heccer.SetTimeStep(TIME_STEP)

my_heccer.SetIntervalStart(INTERVAL_START)

my_heccer.SetIntervalEnd(INTERVAL_END)

my_heccer.SetIntervalEntries(INTERVAL_ENTRIES)

my_heccer.SetSmallTableSize(INTERPOL_INTERVAL_ENTRIES)

my_heccer.SetOptions(OPTIONS)


my_heccer.CompileP1()

my_heccer.CompileP2()

my_heccer.CompileP3()

my_heccer.Initiate()

print "Initiated"

my_heccer.DumpV()

simulation_time = 0.0

print "-------"

from heccer.heccer_base import HECCER_DUMP_ALL  

HECCER_TESTED_THINGS=HECCER_DUMP_ALL

for i in range(0,STEPS):

    simulation_time = i * TIME_STEP + TIME_GRANULARITY

    my_heccer.Step(simulation_time)

    print "Iteration %d" % i

    my_heccer.Dump(0, HECCER_TESTED_THINGS)

    if i < STEPS-1:
        
        print "-------"
    

