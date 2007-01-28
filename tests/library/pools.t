#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/code/pool1',
				command_tests => [
						  {
						   description => "Is a pool integrated correctly, one compartment, single pool case ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 188248 4e-05 1.1 0
00026 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.028)
-------
Iteration 0
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (2e-05)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 188248 4e-05 1.1 6.07228e-12
00026 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0280607)
-------
Iteration 100
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00202)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 188248 4e-05 1.1 6.90649e-12
00026 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0337602)
-------
Iteration 200
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00402)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 188248 4e-05 1.1 8.67988e-12
00026 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0387491)
-------
Iteration 300
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00602)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 188248 4e-05 1.1 1.05928e-11
00026 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0430863)
-------
Iteration 400
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00802)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 188248 4e-05 1.1 1.19948e-11
00026 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0468564)
-------
Iteration 500
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.01002)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 188248 4e-05 1.1 1.27358e-11
00026 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.05015)
-------
Iteration 600
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.01202)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 188248 4e-05 1.1 1.29065e-11
00026 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0530475)
-------
Iteration 700
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.01402)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 188248 4e-05 1.1 1.26499e-11
00026 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.055615)
-------
Iteration 800
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.01602)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 188248 4e-05 1.1 1.21029e-11
00026 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0579048)
-------
Iteration 900
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.01802)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 188248 4e-05 1.1 1.13796e-11
00026 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0599583)
-------
Iteration 1000
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.02)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 188248 4e-05 1.1 1.05764e-11
00026 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0617904)
', ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "pool integration, one compartment, single pool",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/pool2',
				command_tests => [
						  {
						   description => "Is a pool integrated correctly, two compartments, two pools case ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 1	FORWARD_ELIMINATION    0
00002 :: 4	FINISH
00003 :: 2	BACKWARD_SUBSTITUTION    2
00005 :: 3	FINISH_ROW
00006 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 0
00026 :: 1	COMPARTMENT
00027 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: 21	LOADVOLTAGETABLE
00033 :: 22	CONCEPTGATE    2    1    0
00037 :: 22	CONCEPTGATE    3    1    0
00041 :: 30	UPDATECOMPARTMENTCURRENT
00042 :: 26	REGISTERCHANNELCURRENT
00043 :: 25	FLUXPOOL
00044 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 0
00052 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.11243)
VM Diagonals (pdDiagonals[1]) : (1.01417)
VM Axial Resistances (pdAxres[0]) : (-0.0141406)
VM Axial Resistances (pdAxres[1]) : (-0.112415)
VM Axial Resistances (pdAxres[2]) : (-0.112415)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Axial Resistances (pdResults[2]) : (0)
VM Axial Resistances (pdResults[3]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
VM Membrane Potentials (pdVms[1]) : (-0.028)
-------
Iteration 0
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (1e-06)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 1	FORWARD_ELIMINATION    0
00002 :: 4	FINISH
00003 :: 2	BACKWARD_SUBSTITUTION    2
00005 :: 3	FINISH_ROW
00006 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.07228e-12
00026 :: 1	COMPARTMENT
00027 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: 21	LOADVOLTAGETABLE
00033 :: 22	CONCEPTGATE    2    1    0
00037 :: 22	CONCEPTGATE    3    1    0
00041 :: 30	UPDATECOMPARTMENTCURRENT
00042 :: 26	REGISTERCHANNELCURRENT
00043 :: 25	FLUXPOOL
00044 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.07228e-12
00052 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.11243)
VM Diagonals (pdDiagonals[1]) : (1.01417)
VM Axial Resistances (pdAxres[0]) : (-0.0141406)
VM Axial Resistances (pdAxres[1]) : (-0.112415)
VM Axial Resistances (pdAxres[2]) : (-0.112415)
VM Axial Resistances (pdResults[0]) : (-0.0640087)
VM Axial Resistances (pdResults[1]) : (1.11243)
VM Axial Resistances (pdResults[2]) : (-0.0285036)
VM Axial Resistances (pdResults[3]) : (1.01417)
VM Membrane Potentials (pdVms[0]) : (-0.0600175)
VM Membrane Potentials (pdVms[1]) : (-0.0290071)
-------
Iteration 100
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000101)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 1	FORWARD_ELIMINATION    0
00002 :: 4	FINISH
00003 :: 2	BACKWARD_SUBSTITUTION    2
00005 :: 3	FINISH_ROW
00006 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.29714e-12
00026 :: 1	COMPARTMENT
00027 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: 21	LOADVOLTAGETABLE
00033 :: 22	CONCEPTGATE    2    1    0
00037 :: 22	CONCEPTGATE    3    1    0
00041 :: 30	UPDATECOMPARTMENTCURRENT
00042 :: 26	REGISTERCHANNELCURRENT
00043 :: 25	FLUXPOOL
00044 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.29714e-12
00052 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.11243)
VM Diagonals (pdDiagonals[1]) : (1.01417)
VM Axial Resistances (pdAxres[0]) : (-0.0141406)
VM Axial Resistances (pdAxres[1]) : (-0.112415)
VM Axial Resistances (pdAxres[2]) : (-0.112415)
VM Axial Resistances (pdResults[0]) : (-0.0327161)
VM Axial Resistances (pdResults[1]) : (1.11243)
VM Axial Resistances (pdResults[2]) : (-0.0327246)
VM Axial Resistances (pdResults[3]) : (1.01417)
VM Membrane Potentials (pdVms[0]) : (-0.0327174)
VM Membrane Potentials (pdVms[1]) : (-0.0327259)
-------
Iteration 200
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000201)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 1	FORWARD_ELIMINATION    0
00002 :: 4	FINISH
00003 :: 2	BACKWARD_SUBSTITUTION    2
00005 :: 3	FINISH_ROW
00006 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.36236e-12
00026 :: 1	COMPARTMENT
00027 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: 21	LOADVOLTAGETABLE
00033 :: 22	CONCEPTGATE    2    1    0
00037 :: 22	CONCEPTGATE    3    1    0
00041 :: 30	UPDATECOMPARTMENTCURRENT
00042 :: 26	REGISTERCHANNELCURRENT
00043 :: 25	FLUXPOOL
00044 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.36236e-12
00052 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.11243)
VM Diagonals (pdDiagonals[1]) : (1.01417)
VM Axial Resistances (pdAxres[0]) : (-0.0141406)
VM Axial Resistances (pdAxres[1]) : (-0.112415)
VM Axial Resistances (pdAxres[2]) : (-0.112415)
VM Axial Resistances (pdResults[0]) : (-0.0329642)
VM Axial Resistances (pdResults[1]) : (1.11243)
VM Axial Resistances (pdResults[2]) : (-0.0329734)
VM Axial Resistances (pdResults[3]) : (1.01417)
VM Membrane Potentials (pdVms[0]) : (-0.0329655)
VM Membrane Potentials (pdVms[1]) : (-0.0329746)
-------
Iteration 300
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000301)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 1	FORWARD_ELIMINATION    0
00002 :: 4	FINISH
00003 :: 2	BACKWARD_SUBSTITUTION    2
00005 :: 3	FINISH_ROW
00006 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.42997e-12
00026 :: 1	COMPARTMENT
00027 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: 21	LOADVOLTAGETABLE
00033 :: 22	CONCEPTGATE    2    1    0
00037 :: 22	CONCEPTGATE    3    1    0
00041 :: 30	UPDATECOMPARTMENTCURRENT
00042 :: 26	REGISTERCHANNELCURRENT
00043 :: 25	FLUXPOOL
00044 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.42997e-12
00052 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.11243)
VM Diagonals (pdDiagonals[1]) : (1.01417)
VM Axial Resistances (pdAxres[0]) : (-0.0141406)
VM Axial Resistances (pdAxres[1]) : (-0.112415)
VM Axial Resistances (pdAxres[2]) : (-0.112415)
VM Axial Resistances (pdResults[0]) : (-0.0332089)
VM Axial Resistances (pdResults[1]) : (1.11243)
VM Axial Resistances (pdResults[2]) : (-0.0332187)
VM Axial Resistances (pdResults[3]) : (1.01417)
VM Membrane Potentials (pdVms[0]) : (-0.0332101)
VM Membrane Potentials (pdVms[1]) : (-0.0332199)
-------
Iteration 400
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000401)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 1	FORWARD_ELIMINATION    0
00002 :: 4	FINISH
00003 :: 2	BACKWARD_SUBSTITUTION    2
00005 :: 3	FINISH_ROW
00006 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.49988e-12
00026 :: 1	COMPARTMENT
00027 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: 21	LOADVOLTAGETABLE
00033 :: 22	CONCEPTGATE    2    1    0
00037 :: 22	CONCEPTGATE    3    1    0
00041 :: 30	UPDATECOMPARTMENTCURRENT
00042 :: 26	REGISTERCHANNELCURRENT
00043 :: 25	FLUXPOOL
00044 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.49988e-12
00052 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.11243)
VM Diagonals (pdDiagonals[1]) : (1.01417)
VM Axial Resistances (pdAxres[0]) : (-0.0141406)
VM Axial Resistances (pdAxres[1]) : (-0.112415)
VM Axial Resistances (pdAxres[2]) : (-0.112415)
VM Axial Resistances (pdResults[0]) : (-0.0334504)
VM Axial Resistances (pdResults[1]) : (1.11243)
VM Axial Resistances (pdResults[2]) : (-0.0334607)
VM Axial Resistances (pdResults[3]) : (1.01417)
VM Membrane Potentials (pdVms[0]) : (-0.0334516)
VM Membrane Potentials (pdVms[1]) : (-0.0334619)
-------
Iteration 500
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000501)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 1	FORWARD_ELIMINATION    0
00002 :: 4	FINISH
00003 :: 2	BACKWARD_SUBSTITUTION    2
00005 :: 3	FINISH_ROW
00006 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.57201e-12
00026 :: 1	COMPARTMENT
00027 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: 21	LOADVOLTAGETABLE
00033 :: 22	CONCEPTGATE    2    1    0
00037 :: 22	CONCEPTGATE    3    1    0
00041 :: 30	UPDATECOMPARTMENTCURRENT
00042 :: 26	REGISTERCHANNELCURRENT
00043 :: 25	FLUXPOOL
00044 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.57201e-12
00052 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.11243)
VM Diagonals (pdDiagonals[1]) : (1.01417)
VM Axial Resistances (pdAxres[0]) : (-0.0141406)
VM Axial Resistances (pdAxres[1]) : (-0.112415)
VM Axial Resistances (pdAxres[2]) : (-0.112415)
VM Axial Resistances (pdResults[0]) : (-0.0336889)
VM Axial Resistances (pdResults[1]) : (1.11243)
VM Axial Resistances (pdResults[2]) : (-0.0336996)
VM Axial Resistances (pdResults[3]) : (1.01417)
VM Membrane Potentials (pdVms[0]) : (-0.03369)
VM Membrane Potentials (pdVms[1]) : (-0.0337008)
-------
Iteration 600
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000601)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 1	FORWARD_ELIMINATION    0
00002 :: 4	FINISH
00003 :: 2	BACKWARD_SUBSTITUTION    2
00005 :: 3	FINISH_ROW
00006 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.64627e-12
00026 :: 1	COMPARTMENT
00027 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: 21	LOADVOLTAGETABLE
00033 :: 22	CONCEPTGATE    2    1    0
00037 :: 22	CONCEPTGATE    3    1    0
00041 :: 30	UPDATECOMPARTMENTCURRENT
00042 :: 26	REGISTERCHANNELCURRENT
00043 :: 25	FLUXPOOL
00044 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.64627e-12
00052 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.11243)
VM Diagonals (pdDiagonals[1]) : (1.01417)
VM Axial Resistances (pdAxres[0]) : (-0.0141406)
VM Axial Resistances (pdAxres[1]) : (-0.112415)
VM Axial Resistances (pdAxres[2]) : (-0.112415)
VM Axial Resistances (pdResults[0]) : (-0.0339245)
VM Axial Resistances (pdResults[1]) : (1.11243)
VM Axial Resistances (pdResults[2]) : (-0.0339357)
VM Axial Resistances (pdResults[3]) : (1.01417)
VM Membrane Potentials (pdVms[0]) : (-0.0339257)
VM Membrane Potentials (pdVms[1]) : (-0.0339369)
-------
Iteration 700
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000701)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 1	FORWARD_ELIMINATION    0
00002 :: 4	FINISH
00003 :: 2	BACKWARD_SUBSTITUTION    2
00005 :: 3	FINISH_ROW
00006 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.72257e-12
00026 :: 1	COMPARTMENT
00027 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: 21	LOADVOLTAGETABLE
00033 :: 22	CONCEPTGATE    2    1    0
00037 :: 22	CONCEPTGATE    3    1    0
00041 :: 30	UPDATECOMPARTMENTCURRENT
00042 :: 26	REGISTERCHANNELCURRENT
00043 :: 25	FLUXPOOL
00044 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.72257e-12
00052 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.11243)
VM Diagonals (pdDiagonals[1]) : (1.01417)
VM Axial Resistances (pdAxres[0]) : (-0.0141406)
VM Axial Resistances (pdAxres[1]) : (-0.112415)
VM Axial Resistances (pdAxres[2]) : (-0.112415)
VM Axial Resistances (pdResults[0]) : (-0.0341574)
VM Axial Resistances (pdResults[1]) : (1.11243)
VM Axial Resistances (pdResults[2]) : (-0.034169)
VM Axial Resistances (pdResults[3]) : (1.01417)
VM Membrane Potentials (pdVms[0]) : (-0.0341586)
VM Membrane Potentials (pdVms[1]) : (-0.0341702)
-------
Iteration 800
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000801)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 1	FORWARD_ELIMINATION    0
00002 :: 4	FINISH
00003 :: 2	BACKWARD_SUBSTITUTION    2
00005 :: 3	FINISH_ROW
00006 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.8008e-12
00026 :: 1	COMPARTMENT
00027 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: 21	LOADVOLTAGETABLE
00033 :: 22	CONCEPTGATE    2    1    0
00037 :: 22	CONCEPTGATE    3    1    0
00041 :: 30	UPDATECOMPARTMENTCURRENT
00042 :: 26	REGISTERCHANNELCURRENT
00043 :: 25	FLUXPOOL
00044 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.8008e-12
00052 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.11243)
VM Diagonals (pdDiagonals[1]) : (1.01417)
VM Axial Resistances (pdAxres[0]) : (-0.0141406)
VM Axial Resistances (pdAxres[1]) : (-0.112415)
VM Axial Resistances (pdAxres[2]) : (-0.112415)
VM Axial Resistances (pdResults[0]) : (-0.0343879)
VM Axial Resistances (pdResults[1]) : (1.11243)
VM Axial Resistances (pdResults[2]) : (-0.0343998)
VM Axial Resistances (pdResults[3]) : (1.01417)
VM Membrane Potentials (pdVms[0]) : (-0.034389)
VM Membrane Potentials (pdVms[1]) : (-0.0344009)
-------
Iteration 900
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000901)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 1	FORWARD_ELIMINATION    0
00002 :: 4	FINISH
00003 :: 2	BACKWARD_SUBSTITUTION    2
00005 :: 3	FINISH_ROW
00006 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.8809e-12
00026 :: 1	COMPARTMENT
00027 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: 21	LOADVOLTAGETABLE
00033 :: 22	CONCEPTGATE    2    1    0
00037 :: 22	CONCEPTGATE    3    1    0
00041 :: 30	UPDATECOMPARTMENTCURRENT
00042 :: 26	REGISTERCHANNELCURRENT
00043 :: 25	FLUXPOOL
00044 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.8809e-12
00052 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.11243)
VM Diagonals (pdDiagonals[1]) : (1.01417)
VM Axial Resistances (pdAxres[0]) : (-0.0141406)
VM Axial Resistances (pdAxres[1]) : (-0.112415)
VM Axial Resistances (pdAxres[2]) : (-0.112415)
VM Axial Resistances (pdResults[0]) : (-0.0346158)
VM Axial Resistances (pdResults[1]) : (1.11243)
VM Axial Resistances (pdResults[2]) : (-0.0346281)
VM Axial Resistances (pdResults[3]) : (1.01417)
VM Membrane Potentials (pdVms[0]) : (-0.034617)
VM Membrane Potentials (pdVms[1]) : (-0.0346292)
-------
Iteration 1000
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.001)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 1	FORWARD_ELIMINATION    0
00002 :: 4	FINISH
00003 :: 2	BACKWARD_SUBSTITUTION    2
00005 :: 3	FINISH_ROW
00006 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.96192e-12
00026 :: 1	COMPARTMENT
00027 :: 20	INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: 21	LOADVOLTAGETABLE
00033 :: 22	CONCEPTGATE    2    1    0
00037 :: 22	CONCEPTGATE    3    1    0
00041 :: 30	UPDATECOMPARTMENTCURRENT
00042 :: 26	REGISTERCHANNELCURRENT
00043 :: 25	FLUXPOOL
00044 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.96192e-12
00052 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.11243)
VM Diagonals (pdDiagonals[1]) : (1.01417)
VM Axial Resistances (pdAxres[0]) : (-0.0141406)
VM Axial Resistances (pdAxres[1]) : (-0.112415)
VM Axial Resistances (pdAxres[2]) : (-0.112415)
VM Axial Resistances (pdResults[0]) : (-0.0348393)
VM Axial Resistances (pdResults[1]) : (1.11243)
VM Axial Resistances (pdResults[2]) : (-0.0348517)
VM Axial Resistances (pdResults[3]) : (1.01417)
VM Membrane Potentials (pdVms[0]) : (-0.0348404)
VM Membrane Potentials (pdVms[1]) : (-0.0348529)
', ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "pool integration, two compartments, two pools",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/pool1-feedback1',
				command_tests => [
						  {
						   description => "Is a pool integrated correctly, one compartment, one pool with a feedback loop ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    2 134739568
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 0
00024 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: 21	LOADVOLTAGETABLE
00030 :: 22	CONCEPTGATE    2    1    0
00034 :: 22	CONCEPTGATE    3    1    0
00038 :: 30	UPDATECOMPARTMENTCURRENT
00039 :: 26	REGISTERCHANNELCURRENT
00040 :: 25	FLUXPOOL
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
-------
Iteration 0
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (1e-06)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    2 134739568
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.21291e-12
00024 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: 21	LOADVOLTAGETABLE
00030 :: 22	CONCEPTGATE    2    1    0
00034 :: 22	CONCEPTGATE    3    1    0
00038 :: 30	UPDATECOMPARTMENTCURRENT
00039 :: 26	REGISTERCHANNELCURRENT
00040 :: 25	FLUXPOOL
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0679742)
-------
Iteration 100
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000101)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    2 134739568
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.2009e-12
00024 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: 21	LOADVOLTAGETABLE
00030 :: 22	CONCEPTGATE    2    1    0
00034 :: 22	CONCEPTGATE    3    1    0
00038 :: 30	UPDATECOMPARTMENTCURRENT
00039 :: 26	REGISTERCHANNELCURRENT
00040 :: 25	FLUXPOOL
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0652054)
-------
Iteration 200
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000201)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    2 134739568
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.19608e-12
00024 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: 21	LOADVOLTAGETABLE
00030 :: 22	CONCEPTGATE    2    1    0
00034 :: 22	CONCEPTGATE    3    1    0
00038 :: 30	UPDATECOMPARTMENTCURRENT
00039 :: 26	REGISTERCHANNELCURRENT
00040 :: 25	FLUXPOOL
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0618936)
-------
Iteration 300
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000301)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    2 134739568
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.20524e-12
00024 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: 21	LOADVOLTAGETABLE
00030 :: 22	CONCEPTGATE    2    1    0
00034 :: 22	CONCEPTGATE    3    1    0
00038 :: 30	UPDATECOMPARTMENTCURRENT
00039 :: 26	REGISTERCHANNELCURRENT
00040 :: 25	FLUXPOOL
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0577962)
-------
Iteration 400
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000401)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    2 134739568
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.24581e-12
00024 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: 21	LOADVOLTAGETABLE
00030 :: 22	CONCEPTGATE    2    1    0
00034 :: 22	CONCEPTGATE    3    1    0
00038 :: 30	UPDATECOMPARTMENTCURRENT
00039 :: 26	REGISTERCHANNELCURRENT
00040 :: 25	FLUXPOOL
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0525038)
-------
Iteration 500
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000501)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    2 134739568
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.37277e-12
00024 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: 21	LOADVOLTAGETABLE
00030 :: 22	CONCEPTGATE    2    1    0
00034 :: 22	CONCEPTGATE    3    1    0
00038 :: 30	UPDATECOMPARTMENTCURRENT
00039 :: 26	REGISTERCHANNELCURRENT
00040 :: 25	FLUXPOOL
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0452724)
-------
Iteration 600
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000601)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    2 134739568
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.80327e-12
00024 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: 21	LOADVOLTAGETABLE
00030 :: 22	CONCEPTGATE    2    1    0
00034 :: 22	CONCEPTGATE    3    1    0
00038 :: 30	UPDATECOMPARTMENTCURRENT
00039 :: 26	REGISTERCHANNELCURRENT
00040 :: 25	FLUXPOOL
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0347434)
-------
Iteration 700
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000701)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    2 134739568
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 3.33308e-12
00024 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: 21	LOADVOLTAGETABLE
00030 :: 22	CONCEPTGATE    2    1    0
00034 :: 22	CONCEPTGATE    3    1    0
00038 :: 30	UPDATECOMPARTMENTCURRENT
00039 :: 26	REGISTERCHANNELCURRENT
00040 :: 25	FLUXPOOL
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0187337)
-------
Iteration 800
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000801)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    2 134739568
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 5.95042e-12
00024 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: 21	LOADVOLTAGETABLE
00030 :: 22	CONCEPTGATE    2    1    0
00034 :: 22	CONCEPTGATE    3    1    0
00038 :: 30	UPDATECOMPARTMENTCURRENT
00039 :: 26	REGISTERCHANNELCURRENT
00040 :: 25	FLUXPOOL
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.00483287)
-------
Iteration 900
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000901)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    2 134739568
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.92014e-12
00024 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: 21	LOADVOLTAGETABLE
00030 :: 22	CONCEPTGATE    2    1    0
00034 :: 22	CONCEPTGATE    3    1    0
00038 :: 30	UPDATECOMPARTMENTCURRENT
00039 :: 26	REGISTERCHANNELCURRENT
00040 :: 25	FLUXPOOL
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.0356522)
-------
Iteration 1000
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.001)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    2 134739568
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 5.87208e-12
00024 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: 21	LOADVOLTAGETABLE
00030 :: 22	CONCEPTGATE    2    1    0
00034 :: 22	CONCEPTGATE    3    1    0
00038 :: 30	UPDATECOMPARTMENTCURRENT
00039 :: 26	REGISTERCHANNELCURRENT
00040 :: 25	FLUXPOOL
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.0708423)
', ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "pool integration, one compartment, one pool with a feedback loop",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/pool1-feedback2',
				command_tests => [
						  {
						   description => "Is a pool integrated correctly, one compartment, one pool with a feedback loop, reversed order ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 0
00026 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00031 :: 21	LOADVOLTAGETABLE
00032 :: 22	CONCEPTGATE    2    1    0
00036 :: 22	CONCEPTGATE    3    2 134739576
00040 :: 30	UPDATECOMPARTMENTCURRENT
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
-------
Iteration 0
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (1e-06)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.21291e-12
00026 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00031 :: 21	LOADVOLTAGETABLE
00032 :: 22	CONCEPTGATE    2    1    0
00036 :: 22	CONCEPTGATE    3    2 134739576
00040 :: 30	UPDATECOMPARTMENTCURRENT
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0679742)
-------
Iteration 100
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000101)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.2009e-12
00026 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00031 :: 21	LOADVOLTAGETABLE
00032 :: 22	CONCEPTGATE    2    1    0
00036 :: 22	CONCEPTGATE    3    2 134739576
00040 :: 30	UPDATECOMPARTMENTCURRENT
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0652054)
-------
Iteration 200
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000201)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.19608e-12
00026 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00031 :: 21	LOADVOLTAGETABLE
00032 :: 22	CONCEPTGATE    2    1    0
00036 :: 22	CONCEPTGATE    3    2 134739576
00040 :: 30	UPDATECOMPARTMENTCURRENT
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0618936)
-------
Iteration 300
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000301)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.20524e-12
00026 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00031 :: 21	LOADVOLTAGETABLE
00032 :: 22	CONCEPTGATE    2    1    0
00036 :: 22	CONCEPTGATE    3    2 134739576
00040 :: 30	UPDATECOMPARTMENTCURRENT
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0577962)
-------
Iteration 400
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000401)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.24581e-12
00026 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00031 :: 21	LOADVOLTAGETABLE
00032 :: 22	CONCEPTGATE    2    1    0
00036 :: 22	CONCEPTGATE    3    2 134739576
00040 :: 30	UPDATECOMPARTMENTCURRENT
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0525038)
-------
Iteration 500
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000501)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.37277e-12
00026 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00031 :: 21	LOADVOLTAGETABLE
00032 :: 22	CONCEPTGATE    2    1    0
00036 :: 22	CONCEPTGATE    3    2 134739576
00040 :: 30	UPDATECOMPARTMENTCURRENT
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0452724)
-------
Iteration 600
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000601)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 1.80327e-12
00026 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00031 :: 21	LOADVOLTAGETABLE
00032 :: 22	CONCEPTGATE    2    1    0
00036 :: 22	CONCEPTGATE    3    2 134739576
00040 :: 30	UPDATECOMPARTMENTCURRENT
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0347434)
-------
Iteration 700
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000701)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 3.33308e-12
00026 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00031 :: 21	LOADVOLTAGETABLE
00032 :: 22	CONCEPTGATE    2    1    0
00036 :: 22	CONCEPTGATE    3    2 134739576
00040 :: 30	UPDATECOMPARTMENTCURRENT
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0187337)
-------
Iteration 800
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000801)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 5.95042e-12
00026 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00031 :: 21	LOADVOLTAGETABLE
00032 :: 22	CONCEPTGATE    2    1    0
00036 :: 22	CONCEPTGATE    3    2 134739576
00040 :: 30	UPDATECOMPARTMENTCURRENT
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.00483287)
-------
Iteration 900
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000901)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 6.92014e-12
00026 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00031 :: 21	LOADVOLTAGETABLE
00032 :: 22	CONCEPTGATE    2    1    0
00036 :: 22	CONCEPTGATE    3    2 134739576
00040 :: 30	UPDATECOMPARTMENTCURRENT
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.0356522)
-------
Iteration 1000
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.001)
Heccer (dStep) : (1e-06)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (4)
Compartment operations
-----
00000 :: 4	FINISH
00001 :: 4	FINISH
Mechanism operations
-----
00000 :: 1	COMPARTMENT
00001 :: 20	INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE    0    1    0
00011 :: 22	CONCEPTGATE    1    1    0
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 26	REGISTERCHANNELCURRENT
00017 :: 25	FLUXPOOL
00018 :: 24	EXPONENTIALDECAY 9412.39 4e-05 1.005 5.87208e-12
00026 :: 20	INITIALIZECHANNEL 85 2.80748e-07
00031 :: 21	LOADVOLTAGETABLE
00032 :: 22	CONCEPTGATE    2    1    0
00036 :: 22	CONCEPTGATE    3    2 134739576
00040 :: 30	UPDATECOMPARTMENTCURRENT
00041 :: 2	FINISH
VM Diagonals (pdDiagonals[0]) : (1.00001)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.0708423)
', ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "pool integration, one compartment, one pool with a feedback loop, reversed order",
			       },
			      ],
       description => "pool integration",
       name => 'pools.t',
      };


return $test;


