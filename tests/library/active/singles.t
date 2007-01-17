#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/code/singlea-naf',
				command_tests => [
						  {
						   description => "Is a single compartment with a naf conductance solved correctly ?",
						   read => [
							    'Initiated
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0)
Heccer (dStep) : (6e-06)
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
00001 :: 20 0.045 0.000209239			HECCER_MOP_INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    3			HECCER_MOP_CONCEPTGATE    0    3
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
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
Heccer (dTime) : (6e-06)
Heccer (dStep) : (6e-06)
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
00001 :: 20 0.045 0.000209239			HECCER_MOP_INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    3			HECCER_MOP_CONCEPTGATE    0    3
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0272104)
-------
Iteration 100
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000606)
Heccer (dStep) : (6e-06)
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
00001 :: 20 0.045 0.000209239			HECCER_MOP_INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    3			HECCER_MOP_CONCEPTGATE    0    3
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.00848558)
-------
Iteration 200
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.001206)
Heccer (dStep) : (6e-06)
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
00001 :: 20 0.045 0.000209239			HECCER_MOP_INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    3			HECCER_MOP_CONCEPTGATE    0    3
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.00590388)
-------
Iteration 300
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.001806)
Heccer (dStep) : (6e-06)
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
00001 :: 20 0.045 0.000209239			HECCER_MOP_INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    3			HECCER_MOP_CONCEPTGATE    0    3
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.00340627)
-------
Iteration 400
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.002406)
Heccer (dStep) : (6e-06)
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
00001 :: 20 0.045 0.000209239			HECCER_MOP_INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    3			HECCER_MOP_CONCEPTGATE    0    3
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.00129625)
-------
Iteration 500
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.003006)
Heccer (dStep) : (6e-06)
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
00001 :: 20 0.045 0.000209239			HECCER_MOP_INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    3			HECCER_MOP_CONCEPTGATE    0    3
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.000379716)
-------
Iteration 600
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.003606)
Heccer (dStep) : (6e-06)
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
00001 :: 20 0.045 0.000209239			HECCER_MOP_INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    3			HECCER_MOP_CONCEPTGATE    0    3
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.00161789)
-------
Iteration 700
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.004206)
Heccer (dStep) : (6e-06)
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
00001 :: 20 0.045 0.000209239			HECCER_MOP_INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    3			HECCER_MOP_CONCEPTGATE    0    3
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.00246622)
-------
Iteration 800
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.004806)
Heccer (dStep) : (6e-06)
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
00001 :: 20 0.045 0.000209239			HECCER_MOP_INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    3			HECCER_MOP_CONCEPTGATE    0    3
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.00300751)
-------
Iteration 900
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.005406)
Heccer (dStep) : (6e-06)
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
00001 :: 20 0.045 0.000209239			HECCER_MOP_INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    3			HECCER_MOP_CONCEPTGATE    0    3
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.00333324)
-------
Iteration 1000
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.006)
Heccer (dStep) : (6e-06)
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
00001 :: 20 0.045 0.000209239			HECCER_MOP_INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21			HECCER_MOP_LOADVOLTAGETABLE
00007 :: 22    0    3			HECCER_MOP_CONCEPTGATE    0    3
00010 :: 22    1    1			HECCER_MOP_CONCEPTGATE    1    1
00013 :: 30			HECCER_MOP_UPDATECOMPARTMENTCURRENT
00014 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.00351931)
',
							   ],
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "single compartment with a naf conductance.",
			       },
			      ],
       description => "active single compartment testing",
       name => 'singles.t',
      };


return $test;


