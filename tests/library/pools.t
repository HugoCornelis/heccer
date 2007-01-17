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
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 20 0.137526 1.39493e-08			HECCER_MOP_INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    1			HECCER_MOP_CONCEPTGATE    0    1
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 26			HECCER_MOP_REGISTERCHANNELCURRENT
00015 :: 25    0			HECCER_MOP_FLUXPOOL    0
00017 :: 24 1.1 1.3793e-312 -2.23189e-10			HECCER_MOP_EXPONENTIALDECAY 1.1 1.3793e-312 -2.23189e-10
00024 :: 2			HECCER_MOP_FINISH
VM Fluxes (pdFluxes[0]) : (0)
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
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (2e-05)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 20 0.137526 1.39493e-08			HECCER_MOP_INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    1			HECCER_MOP_CONCEPTGATE    0    1
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 26			HECCER_MOP_REGISTERCHANNELCURRENT
00015 :: 25    0			HECCER_MOP_FLUXPOOL    0
00017 :: 24 1.1 1.3793e-312 -2.23189e-10			HECCER_MOP_EXPONENTIALDECAY 1.1 1.3793e-312 -2.23189e-10
00024 :: 2			HECCER_MOP_FINISH
VM Fluxes (pdFluxes[0]) : (6.07228e-12)
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
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00202)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 20 0.137526 1.39493e-08			HECCER_MOP_INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    1			HECCER_MOP_CONCEPTGATE    0    1
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 26			HECCER_MOP_REGISTERCHANNELCURRENT
00015 :: 25    0			HECCER_MOP_FLUXPOOL    0
00017 :: 24 1.1 1.3793e-312 -2.23189e-10			HECCER_MOP_EXPONENTIALDECAY 1.1 1.3793e-312 -2.23189e-10
00024 :: 2			HECCER_MOP_FINISH
VM Fluxes (pdFluxes[0]) : (6.90649e-12)
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
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00402)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 20 0.137526 1.39493e-08			HECCER_MOP_INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    1			HECCER_MOP_CONCEPTGATE    0    1
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 26			HECCER_MOP_REGISTERCHANNELCURRENT
00015 :: 25    0			HECCER_MOP_FLUXPOOL    0
00017 :: 24 1.1 1.3793e-312 -2.23189e-10			HECCER_MOP_EXPONENTIALDECAY 1.1 1.3793e-312 -2.23189e-10
00024 :: 2			HECCER_MOP_FINISH
VM Fluxes (pdFluxes[0]) : (8.67988e-12)
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
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00602)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 20 0.137526 1.39493e-08			HECCER_MOP_INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    1			HECCER_MOP_CONCEPTGATE    0    1
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 26			HECCER_MOP_REGISTERCHANNELCURRENT
00015 :: 25    0			HECCER_MOP_FLUXPOOL    0
00017 :: 24 1.1 1.3793e-312 -2.23189e-10			HECCER_MOP_EXPONENTIALDECAY 1.1 1.3793e-312 -2.23189e-10
00024 :: 2			HECCER_MOP_FINISH
VM Fluxes (pdFluxes[0]) : (1.05928e-11)
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
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00802)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 20 0.137526 1.39493e-08			HECCER_MOP_INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    1			HECCER_MOP_CONCEPTGATE    0    1
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 26			HECCER_MOP_REGISTERCHANNELCURRENT
00015 :: 25    0			HECCER_MOP_FLUXPOOL    0
00017 :: 24 1.1 1.3793e-312 -2.23189e-10			HECCER_MOP_EXPONENTIALDECAY 1.1 1.3793e-312 -2.23189e-10
00024 :: 2			HECCER_MOP_FINISH
VM Fluxes (pdFluxes[0]) : (1.19948e-11)
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
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.01002)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 20 0.137526 1.39493e-08			HECCER_MOP_INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    1			HECCER_MOP_CONCEPTGATE    0    1
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 26			HECCER_MOP_REGISTERCHANNELCURRENT
00015 :: 25    0			HECCER_MOP_FLUXPOOL    0
00017 :: 24 1.1 1.3793e-312 -2.23189e-10			HECCER_MOP_EXPONENTIALDECAY 1.1 1.3793e-312 -2.23189e-10
00024 :: 2			HECCER_MOP_FINISH
VM Fluxes (pdFluxes[0]) : (1.27358e-11)
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
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.01202)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 20 0.137526 1.39493e-08			HECCER_MOP_INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    1			HECCER_MOP_CONCEPTGATE    0    1
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 26			HECCER_MOP_REGISTERCHANNELCURRENT
00015 :: 25    0			HECCER_MOP_FLUXPOOL    0
00017 :: 24 1.1 1.3793e-312 -2.23189e-10			HECCER_MOP_EXPONENTIALDECAY 1.1 1.3793e-312 -2.23189e-10
00024 :: 2			HECCER_MOP_FINISH
VM Fluxes (pdFluxes[0]) : (1.29065e-11)
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
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.01402)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 20 0.137526 1.39493e-08			HECCER_MOP_INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    1			HECCER_MOP_CONCEPTGATE    0    1
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 26			HECCER_MOP_REGISTERCHANNELCURRENT
00015 :: 25    0			HECCER_MOP_FLUXPOOL    0
00017 :: 24 1.1 1.3793e-312 -2.23189e-10			HECCER_MOP_EXPONENTIALDECAY 1.1 1.3793e-312 -2.23189e-10
00024 :: 2			HECCER_MOP_FINISH
VM Fluxes (pdFluxes[0]) : (1.26499e-11)
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
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.01602)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 20 0.137526 1.39493e-08			HECCER_MOP_INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    1			HECCER_MOP_CONCEPTGATE    0    1
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 26			HECCER_MOP_REGISTERCHANNELCURRENT
00015 :: 25    0			HECCER_MOP_FLUXPOOL    0
00017 :: 24 1.1 1.3793e-312 -2.23189e-10			HECCER_MOP_EXPONENTIALDECAY 1.1 1.3793e-312 -2.23189e-10
00024 :: 2			HECCER_MOP_FINISH
VM Fluxes (pdFluxes[0]) : (1.21029e-11)
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
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.01802)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 20 0.137526 1.39493e-08			HECCER_MOP_INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    1			HECCER_MOP_CONCEPTGATE    0    1
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 26			HECCER_MOP_REGISTERCHANNELCURRENT
00015 :: 25    0			HECCER_MOP_FLUXPOOL    0
00017 :: 24 1.1 1.3793e-312 -2.23189e-10			HECCER_MOP_EXPONENTIALDECAY 1.1 1.3793e-312 -2.23189e-10
00024 :: 2			HECCER_MOP_FINISH
VM Fluxes (pdFluxes[0]) : (1.13796e-11)
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
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.02)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 20 0.137526 1.39493e-08			HECCER_MOP_INITIALIZECHANNEL 0.137526 1.39493e-08
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    1			HECCER_MOP_CONCEPTGATE    0    1
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 26			HECCER_MOP_REGISTERCHANNELCURRENT
00015 :: 25    0			HECCER_MOP_FLUXPOOL    0
00017 :: 24 1.1 1.3793e-312 -2.23189e-10			HECCER_MOP_EXPONENTIALDECAY 1.1 1.3793e-312 -2.23189e-10
00024 :: 2			HECCER_MOP_FINISH
VM Fluxes (pdFluxes[0]) : (1.05764e-11)
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
			      ],
       description => "pool integration",
       name => 'pools.t',
      };


return $test;


