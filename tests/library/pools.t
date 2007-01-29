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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00061
00011 :: CONCEPTGATE 1 1 (nil)							 0.988964
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4e-05
00018 :: EXPONENTIALDECAY 188248 4e-05 1.1 0							 7.9212e-310
00026 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00061
00011 :: CONCEPTGATE 1 1 (nil)							 0.988964
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.10392e-05
00018 :: EXPONENTIALDECAY 188248 4e-05 1.1 6.07228e-12							 7.9212e-310
00026 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00061
00011 :: CONCEPTGATE 1 1 (nil)							 0.972013
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.64434e-05
00018 :: EXPONENTIALDECAY 188248 4e-05 1.1 6.90649e-12							 7.9212e-310
00026 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00061
00011 :: CONCEPTGATE 1 1 (nil)							 0.908947
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.80857e-05
00018 :: EXPONENTIALDECAY 188248 4e-05 1.1 8.67988e-12							 7.9212e-310
00026 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00061
00011 :: CONCEPTGATE 1 1 (nil)							 0.793915
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.98964e-05
00018 :: EXPONENTIALDECAY 188248 4e-05 1.1 1.05928e-11							 7.9212e-310
00026 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00061
00011 :: CONCEPTGATE 1 1 (nil)							 0.658612
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 5.12433e-05
00018 :: EXPONENTIALDECAY 188248 4e-05 1.1 1.19948e-11							 7.9212e-310
00026 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00061
00011 :: CONCEPTGATE 1 1 (nil)							 0.533034
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 5.19679e-05
00018 :: EXPONENTIALDECAY 188248 4e-05 1.1 1.27358e-11							 7.9212e-310
00026 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00061
00011 :: CONCEPTGATE 1 1 (nil)							 0.427522
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 5.215e-05
00018 :: EXPONENTIALDECAY 188248 4e-05 1.1 1.29065e-11							 7.9212e-310
00026 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00061
00011 :: CONCEPTGATE 1 1 (nil)							 0.342135
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 5.19239e-05
00018 :: EXPONENTIALDECAY 188248 4e-05 1.1 1.26499e-11							 7.9212e-310
00026 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00061
00011 :: CONCEPTGATE 1 1 (nil)							 0.27403
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 5.14189e-05
00018 :: EXPONENTIALDECAY 188248 4e-05 1.1 1.21029e-11							 7.9212e-310
00026 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00061
00011 :: CONCEPTGATE 1 1 (nil)							 0.220073
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 5.07437e-05
00018 :: EXPONENTIALDECAY 188248 4e-05 1.1 1.13796e-11							 7.9212e-310
00026 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00061
00011 :: CONCEPTGATE 1 1 (nil)							 0.177829
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.99901e-05
00018 :: EXPONENTIALDECAY 188248 4e-05 1.1 1.05764e-11							 7.9212e-310
00026 :: FINISH
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
00000 :: FORWARD_ELIMINATION    0
00002 :: FINISH
00003 :: BACKWARD_SUBSTITUTION    2
00005 :: FINISH_ROW
00006 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.11243
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.11243
00011 :: CONCEPTGATE 1 1 (nil)							 0.0389187
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 0							 -2.23189e-10
00026 :: COMPARTMENT							 0 10928.1 1.01417 0.988964
00027 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: LOADVOLTAGETABLE
00033 :: CONCEPTGATE 2 1 (nil)							 0.988964
00037 :: CONCEPTGATE 3 1 (nil)							 0.00265921
00041 :: UPDATECOMPARTMENTCURRENT
00042 :: REGISTERCHANNELCURRENT
00043 :: FLUXPOOL							 1.78301e-309
00044 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 0							 0
00052 :: FINISH
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
00000 :: FORWARD_ELIMINATION    0
00002 :: FINISH
00003 :: BACKWARD_SUBSTITUTION    2
00005 :: FINISH_ROW
00006 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.11243
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.11243
00011 :: CONCEPTGATE 1 1 (nil)							 0.0389187
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.07228e-12							 -2.23189e-10
00026 :: COMPARTMENT							 0 10928.1 1.01417 0.988964
00027 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: LOADVOLTAGETABLE
00033 :: CONCEPTGATE 2 1 (nil)							 0.988964
00037 :: CONCEPTGATE 3 1 (nil)							 0.00265921
00041 :: UPDATECOMPARTMENTCURRENT
00042 :: REGISTERCHANNELCURRENT
00043 :: FLUXPOOL							 1.78301e-309
00044 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.07228e-12							 0
00052 :: FINISH
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
00000 :: FORWARD_ELIMINATION    0
00002 :: FINISH
00003 :: BACKWARD_SUBSTITUTION    2
00005 :: FINISH_ROW
00006 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.11243
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.11243
00011 :: CONCEPTGATE 1 1 (nil)							 0.0817519
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.37282e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.29714e-12							 -2.23189e-10
00026 :: COMPARTMENT							 0 10928.1 1.01417 0.987195
00027 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: LOADVOLTAGETABLE
00033 :: CONCEPTGATE 2 1 (nil)							 0.987195
00037 :: CONCEPTGATE 3 1 (nil)							 0.00268598
00041 :: UPDATECOMPARTMENTCURRENT
00042 :: REGISTERCHANNELCURRENT
00043 :: FLUXPOOL							 1.78301e-309
00044 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.29714e-12							 0
00052 :: FINISH
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
00000 :: FORWARD_ELIMINATION    0
00002 :: FINISH
00003 :: BACKWARD_SUBSTITUTION    2
00005 :: FINISH_ROW
00006 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.11243
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.11243
00011 :: CONCEPTGATE 1 1 (nil)							 0.124603
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.51404e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.36236e-12							 -2.23189e-10
00026 :: COMPARTMENT							 0 10928.1 1.01417 0.985296
00027 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: LOADVOLTAGETABLE
00033 :: CONCEPTGATE 2 1 (nil)							 0.985296
00037 :: CONCEPTGATE 3 1 (nil)							 0.00271506
00041 :: UPDATECOMPARTMENTCURRENT
00042 :: REGISTERCHANNELCURRENT
00043 :: FLUXPOOL							 1.78301e-309
00044 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.36236e-12							 0
00052 :: FINISH
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
00000 :: FORWARD_ELIMINATION    0
00002 :: FINISH
00003 :: BACKWARD_SUBSTITUTION    2
00005 :: FINISH_ROW
00006 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.11243
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.11243
00011 :: CONCEPTGATE 1 1 (nil)							 0.164319
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.56996e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.42997e-12							 -2.23189e-10
00026 :: COMPARTMENT							 0 10928.1 1.01417 0.983339
00027 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: LOADVOLTAGETABLE
00033 :: CONCEPTGATE 2 1 (nil)							 0.983339
00037 :: CONCEPTGATE 3 1 (nil)							 0.00274542
00041 :: UPDATECOMPARTMENTCURRENT
00042 :: REGISTERCHANNELCURRENT
00043 :: FLUXPOOL							 1.78301e-309
00044 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.42997e-12							 0
00052 :: FINISH
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
00000 :: FORWARD_ELIMINATION    0
00002 :: FINISH
00003 :: BACKWARD_SUBSTITUTION    2
00005 :: FINISH_ROW
00006 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.11243
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.11243
00011 :: CONCEPTGATE 1 1 (nil)							 0.201167
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.59463e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.49988e-12							 -2.23189e-10
00026 :: COMPARTMENT							 0 10928.1 1.01417 0.981318
00027 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: LOADVOLTAGETABLE
00033 :: CONCEPTGATE 2 1 (nil)							 0.981318
00037 :: CONCEPTGATE 3 1 (nil)							 0.00277705
00041 :: UPDATECOMPARTMENTCURRENT
00042 :: REGISTERCHANNELCURRENT
00043 :: FLUXPOOL							 1.78301e-309
00044 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.49988e-12							 0
00052 :: FINISH
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
00000 :: FORWARD_ELIMINATION    0
00002 :: FINISH
00003 :: BACKWARD_SUBSTITUTION    2
00005 :: FINISH_ROW
00006 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.11243
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.11243
00011 :: CONCEPTGATE 1 1 (nil)							 0.235377
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.60795e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.57201e-12							 -2.23189e-10
00026 :: COMPARTMENT							 0 10928.1 1.01417 0.979229
00027 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: LOADVOLTAGETABLE
00033 :: CONCEPTGATE 2 1 (nil)							 0.979229
00037 :: CONCEPTGATE 3 1 (nil)							 0.00280993
00041 :: UPDATECOMPARTMENTCURRENT
00042 :: REGISTERCHANNELCURRENT
00043 :: FLUXPOOL							 1.78301e-309
00044 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.57201e-12							 0
00052 :: FINISH
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
00000 :: FORWARD_ELIMINATION    0
00002 :: FINISH
00003 :: BACKWARD_SUBSTITUTION    2
00005 :: FINISH_ROW
00006 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.11243
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.11243
00011 :: CONCEPTGATE 1 1 (nil)							 0.267166
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.61721e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.64627e-12							 -2.23189e-10
00026 :: COMPARTMENT							 0 10928.1 1.01417 0.977068
00027 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: LOADVOLTAGETABLE
00033 :: CONCEPTGATE 2 1 (nil)							 0.977068
00037 :: CONCEPTGATE 3 1 (nil)							 0.00284405
00041 :: UPDATECOMPARTMENTCURRENT
00042 :: REGISTERCHANNELCURRENT
00043 :: FLUXPOOL							 1.78301e-309
00044 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.64627e-12							 0
00052 :: FINISH
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
00000 :: FORWARD_ELIMINATION    0
00002 :: FINISH
00003 :: BACKWARD_SUBSTITUTION    2
00005 :: FINISH_ROW
00006 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.11243
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.11243
00011 :: CONCEPTGATE 1 1 (nil)							 0.296727
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.62511e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.72257e-12							 -2.23189e-10
00026 :: COMPARTMENT							 0 10928.1 1.01417 0.974831
00027 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: LOADVOLTAGETABLE
00033 :: CONCEPTGATE 2 1 (nil)							 0.974831
00037 :: CONCEPTGATE 3 1 (nil)							 0.00287938
00041 :: UPDATECOMPARTMENTCURRENT
00042 :: REGISTERCHANNELCURRENT
00043 :: FLUXPOOL							 1.78301e-309
00044 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.72257e-12							 0
00052 :: FINISH
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
00000 :: FORWARD_ELIMINATION    0
00002 :: FINISH
00003 :: BACKWARD_SUBSTITUTION    2
00005 :: FINISH_ROW
00006 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.11243
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.11243
00011 :: CONCEPTGATE 1 1 (nil)							 0.324225
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.63262e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.8008e-12							 -2.23189e-10
00026 :: COMPARTMENT							 0 10928.1 1.01417 0.972517
00027 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: LOADVOLTAGETABLE
00033 :: CONCEPTGATE 2 1 (nil)							 0.972517
00037 :: CONCEPTGATE 3 1 (nil)							 0.00291589
00041 :: UPDATECOMPARTMENTCURRENT
00042 :: REGISTERCHANNELCURRENT
00043 :: FLUXPOOL							 1.78301e-309
00044 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.8008e-12							 0
00052 :: FINISH
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
00000 :: FORWARD_ELIMINATION    0
00002 :: FINISH
00003 :: BACKWARD_SUBSTITUTION    2
00005 :: FINISH_ROW
00006 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.11243
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.11243
00011 :: CONCEPTGATE 1 1 (nil)							 0.34982
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.6401e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.8809e-12							 -2.23189e-10
00026 :: COMPARTMENT							 0 10928.1 1.01417 0.970119
00027 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: LOADVOLTAGETABLE
00033 :: CONCEPTGATE 2 1 (nil)							 0.970119
00037 :: CONCEPTGATE 3 1 (nil)							 0.00295361
00041 :: UPDATECOMPARTMENTCURRENT
00042 :: REGISTERCHANNELCURRENT
00043 :: FLUXPOOL							 1.78301e-309
00044 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.8809e-12							 0
00052 :: FINISH
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
00000 :: FORWARD_ELIMINATION    0
00002 :: FINISH
00003 :: BACKWARD_SUBSTITUTION    2
00005 :: FINISH_ROW
00006 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.11243
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.11243
00011 :: CONCEPTGATE 1 1 (nil)							 0.373424
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.6476e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.96192e-12							 -2.23189e-10
00026 :: COMPARTMENT							 0 10928.1 1.01417 0.967663
00027 :: INITIALIZECHANNEL 0.137526 1.39493e-08
00032 :: LOADVOLTAGETABLE
00033 :: CONCEPTGATE 2 1 (nil)							 0.967663
00037 :: CONCEPTGATE 3 1 (nil)							 0.00299208
00041 :: UPDATECOMPARTMENTCURRENT
00042 :: REGISTERCHANNELCURRENT
00043 :: FLUXPOOL							 1.78301e-309
00044 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.96192e-12							 0
00052 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 85 2.80748e-07
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 2 (4e-05)							 0.0635319
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 0							 4e-05
00024 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: LOADVOLTAGETABLE
00030 :: CONCEPTGATE 2 1 (nil)							 0
00034 :: CONCEPTGATE 3 1 (nil)							 1.78963e-309
00038 :: UPDATECOMPARTMENTCURRENT
00039 :: REGISTERCHANNELCURRENT
00040 :: FLUXPOOL							 0
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 85 2.80748e-07
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 2 (4e-05)							 0.0635096
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.21291e-12							 4e-05
00024 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: LOADVOLTAGETABLE
00030 :: CONCEPTGATE 2 1 (nil)							 1.21291e-12
00034 :: CONCEPTGATE 3 1 (nil)							 1.78963e-309
00038 :: UPDATECOMPARTMENTCURRENT
00039 :: REGISTERCHANNELCURRENT
00040 :: FLUXPOOL							 0
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 85 2.80748e-07
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 2 (4.07173e-05)							 0.074116
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.2009e-12							 4.07173e-05
00024 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: LOADVOLTAGETABLE
00030 :: CONCEPTGATE 2 1 (nil)							 1.2009e-12
00034 :: CONCEPTGATE 3 1 (nil)							 1.78963e-309
00038 :: UPDATECOMPARTMENTCURRENT
00039 :: REGISTERCHANNELCURRENT
00040 :: FLUXPOOL							 0
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 85 2.80748e-07
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 2 (4.09763e-05)							 0.0901266
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.19608e-12							 4.09763e-05
00024 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: LOADVOLTAGETABLE
00030 :: CONCEPTGATE 2 1 (nil)							 1.19608e-12
00034 :: CONCEPTGATE 3 1 (nil)							 1.78963e-309
00038 :: UPDATECOMPARTMENTCURRENT
00039 :: REGISTERCHANNELCURRENT
00040 :: FLUXPOOL							 0
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 85 2.80748e-07
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 2 (4.1073e-05)							 0.113708
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.20524e-12							 4.1073e-05
00024 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: LOADVOLTAGETABLE
00030 :: CONCEPTGATE 2 1 (nil)							 1.20524e-12
00034 :: CONCEPTGATE 3 1 (nil)							 1.78963e-309
00038 :: UPDATECOMPARTMENTCURRENT
00039 :: REGISTERCHANNELCURRENT
00040 :: FLUXPOOL							 0
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 85 2.80748e-07
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 2 (4.11234e-05)							 0.150558
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.24581e-12							 4.11234e-05
00024 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: LOADVOLTAGETABLE
00030 :: CONCEPTGATE 2 1 (nil)							 1.24581e-12
00034 :: CONCEPTGATE 3 1 (nil)							 1.78963e-309
00038 :: UPDATECOMPARTMENTCURRENT
00039 :: REGISTERCHANNELCURRENT
00040 :: FLUXPOOL							 0
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 85 2.80748e-07
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 2 (4.1191e-05)							 0.211866
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.37277e-12							 4.1191e-05
00024 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: LOADVOLTAGETABLE
00030 :: CONCEPTGATE 2 1 (nil)							 1.37277e-12
00034 :: CONCEPTGATE 3 1 (nil)							 1.78963e-309
00038 :: UPDATECOMPARTMENTCURRENT
00039 :: REGISTERCHANNELCURRENT
00040 :: FLUXPOOL							 0
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 85 2.80748e-07
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 2 (4.13756e-05)							 0.316779
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.80327e-12							 4.13756e-05
00024 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: LOADVOLTAGETABLE
00030 :: CONCEPTGATE 2 1 (nil)							 1.80327e-12
00034 :: CONCEPTGATE 3 1 (nil)							 1.78963e-309
00038 :: UPDATECOMPARTMENTCURRENT
00039 :: REGISTERCHANNELCURRENT
00040 :: FLUXPOOL							 0
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 85 2.80748e-07
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 2 (4.20186e-05)							 0.482033
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 3.33308e-12							 4.20186e-05
00024 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: LOADVOLTAGETABLE
00030 :: CONCEPTGATE 2 1 (nil)							 3.33308e-12
00034 :: CONCEPTGATE 3 1 (nil)							 1.78963e-309
00038 :: UPDATECOMPARTMENTCURRENT
00039 :: REGISTERCHANNELCURRENT
00040 :: FLUXPOOL							 0
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 85 2.80748e-07
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 2 (4.36468e-05)							 0.677571
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 5.95042e-12							 4.36468e-05
00024 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: LOADVOLTAGETABLE
00030 :: CONCEPTGATE 2 1 (nil)							 5.95042e-12
00034 :: CONCEPTGATE 3 1 (nil)							 1.78963e-309
00038 :: UPDATECOMPARTMENTCURRENT
00039 :: REGISTERCHANNELCURRENT
00040 :: FLUXPOOL							 0
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 85 2.80748e-07
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 2 (4.53258e-05)							 0.830684
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.92014e-12							 4.53258e-05
00024 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: LOADVOLTAGETABLE
00030 :: CONCEPTGATE 2 1 (nil)							 6.92014e-12
00034 :: CONCEPTGATE 3 1 (nil)							 1.78963e-309
00038 :: UPDATECOMPARTMENTCURRENT
00039 :: REGISTERCHANNELCURRENT
00040 :: FLUXPOOL							 0
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 85 2.80748e-07
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 2 (4.5798e-05)							 0.916404
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 5.87208e-12							 4.5798e-05
00024 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00029 :: LOADVOLTAGETABLE
00030 :: CONCEPTGATE 2 1 (nil)							 5.87208e-12
00034 :: CONCEPTGATE 3 1 (nil)							 1.78963e-309
00038 :: UPDATECOMPARTMENTCURRENT
00039 :: REGISTERCHANNELCURRENT
00040 :: FLUXPOOL							 0
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 1 (nil)							 0.0389187
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 0							 0.0635319
00026 :: INITIALIZECHANNEL 85 2.80748e-07
00031 :: LOADVOLTAGETABLE
00032 :: CONCEPTGATE 2 1 (nil)							 0
00036 :: CONCEPTGATE 3 2 (4e-05)							 0
00040 :: UPDATECOMPARTMENTCURRENT
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 1 (nil)							 0.0389187
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.00114e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.21291e-12							 0.0635096
00026 :: INITIALIZECHANNEL 85 2.80748e-07
00031 :: LOADVOLTAGETABLE
00032 :: CONCEPTGATE 2 1 (nil)							 0
00036 :: CONCEPTGATE 3 2 (4.00114e-05)							 0
00040 :: UPDATECOMPARTMENTCURRENT
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 1 (nil)							 0.0390489
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.07214e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.2009e-12							 0.074116
00026 :: INITIALIZECHANNEL 85 2.80748e-07
00031 :: LOADVOLTAGETABLE
00032 :: CONCEPTGATE 2 1 (nil)							 0
00036 :: CONCEPTGATE 3 2 (4.07214e-05)							 0
00040 :: UPDATECOMPARTMENTCURRENT
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 1 (nil)							 0.0395562
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.09777e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.19608e-12							 0.0901266
00026 :: INITIALIZECHANNEL 85 2.80748e-07
00031 :: LOADVOLTAGETABLE
00032 :: CONCEPTGATE 2 1 (nil)							 0
00036 :: CONCEPTGATE 3 2 (4.09777e-05)							 0
00040 :: UPDATECOMPARTMENTCURRENT
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 1 (nil)							 0.0407586
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.10736e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.20524e-12							 0.113708
00026 :: INITIALIZECHANNEL 85 2.80748e-07
00031 :: LOADVOLTAGETABLE
00032 :: CONCEPTGATE 2 1 (nil)							 0
00036 :: CONCEPTGATE 3 2 (4.10736e-05)							 0
00040 :: UPDATECOMPARTMENTCURRENT
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 1 (nil)							 0.0434445
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.11239e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.24581e-12							 0.150558
00026 :: INITIALIZECHANNEL 85 2.80748e-07
00031 :: LOADVOLTAGETABLE
00032 :: CONCEPTGATE 2 1 (nil)							 0
00036 :: CONCEPTGATE 3 2 (4.11239e-05)							 0
00040 :: UPDATECOMPARTMENTCURRENT
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 1 (nil)							 0.0500527
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.1192e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.37277e-12							 0.211866
00026 :: INITIALIZECHANNEL 85 2.80748e-07
00031 :: LOADVOLTAGETABLE
00032 :: CONCEPTGATE 2 1 (nil)							 0
00036 :: CONCEPTGATE 3 2 (4.1192e-05)							 0
00040 :: UPDATECOMPARTMENTCURRENT
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 1 (nil)							 0.0703922
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.13788e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 1.80327e-12							 0.316779
00026 :: INITIALIZECHANNEL 85 2.80748e-07
00031 :: LOADVOLTAGETABLE
00032 :: CONCEPTGATE 2 1 (nil)							 0
00036 :: CONCEPTGATE 3 2 (4.13788e-05)							 0
00040 :: UPDATECOMPARTMENTCURRENT
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 1 (nil)							 0.144986
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.20297e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 3.33308e-12							 0.482033
00026 :: INITIALIZECHANNEL 85 2.80748e-07
00031 :: LOADVOLTAGETABLE
00032 :: CONCEPTGATE 2 1 (nil)							 0
00036 :: CONCEPTGATE 3 2 (4.20297e-05)							 0
00040 :: UPDATECOMPARTMENTCURRENT
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 1 (nil)							 0.307169
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.36662e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 5.95042e-12							 0.677571
00026 :: INITIALIZECHANNEL 85 2.80748e-07
00031 :: LOADVOLTAGETABLE
00032 :: CONCEPTGATE 2 1 (nil)							 0
00036 :: CONCEPTGATE 3 2 (4.36662e-05)							 0
00040 :: UPDATECOMPARTMENTCURRENT
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 1 (nil)							 0.464315
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.53376e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 6.92014e-12							 0.830684
00026 :: INITIALIZECHANNEL 85 2.80748e-07
00031 :: LOADVOLTAGETABLE
00032 :: CONCEPTGATE 2 1 (nil)							 0
00036 :: CONCEPTGATE 3 2 (4.53376e-05)							 0
00040 :: UPDATECOMPARTMENTCURRENT
00041 :: FINISH
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
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -9.35826e-12 0 86876 1.00001
00001 :: INITIALIZECHANNEL 0.147021 1.75467e-09
00006 :: LOADVOLTAGETABLE
00007 :: CONCEPTGATE 0 1 (nil)							 1.00001
00011 :: CONCEPTGATE 1 1 (nil)							 0.585857
00015 :: UPDATECOMPARTMENTCURRENT
00016 :: REGISTERCHANNELCURRENT
00017 :: FLUXPOOL							 4.57954e-05
00018 :: EXPONENTIALDECAY 9412.39 4e-05 1.005 5.87208e-12							 0.916404
00026 :: INITIALIZECHANNEL 85 2.80748e-07
00031 :: LOADVOLTAGETABLE
00032 :: CONCEPTGATE 2 1 (nil)							 0
00036 :: CONCEPTGATE 3 2 (4.57954e-05)							 0
00040 :: UPDATECOMPARTMENTCURRENT
00041 :: FINISH
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


