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
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0)
Heccer (dStep) : (6e-06)
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
00001 :: 20	INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE 0 3 (nil)
00011 :: 22	CONCEPTGATE 1 1 (nil)
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 2	FINISH
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
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (6e-06)
Heccer (dStep) : (6e-06)
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
00001 :: 20	INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE 0 3 (nil)
00011 :: 22	CONCEPTGATE 1 1 (nil)
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 2	FINISH
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
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.000606)
Heccer (dStep) : (6e-06)
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
00001 :: 20	INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE 0 3 (nil)
00011 :: 22	CONCEPTGATE 1 1 (nil)
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 2	FINISH
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
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.001206)
Heccer (dStep) : (6e-06)
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
00001 :: 20	INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE 0 3 (nil)
00011 :: 22	CONCEPTGATE 1 1 (nil)
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 2	FINISH
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
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.001806)
Heccer (dStep) : (6e-06)
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
00001 :: 20	INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE 0 3 (nil)
00011 :: 22	CONCEPTGATE 1 1 (nil)
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 2	FINISH
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
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.002406)
Heccer (dStep) : (6e-06)
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
00001 :: 20	INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE 0 3 (nil)
00011 :: 22	CONCEPTGATE 1 1 (nil)
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 2	FINISH
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
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.003006)
Heccer (dStep) : (6e-06)
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
00001 :: 20	INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE 0 3 (nil)
00011 :: 22	CONCEPTGATE 1 1 (nil)
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 2	FINISH
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
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.003606)
Heccer (dStep) : (6e-06)
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
00001 :: 20	INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE 0 3 (nil)
00011 :: 22	CONCEPTGATE 1 1 (nil)
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 2	FINISH
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
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.004206)
Heccer (dStep) : (6e-06)
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
00001 :: 20	INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE 0 3 (nil)
00011 :: 22	CONCEPTGATE 1 1 (nil)
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 2	FINISH
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
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.004806)
Heccer (dStep) : (6e-06)
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
00001 :: 20	INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE 0 3 (nil)
00011 :: 22	CONCEPTGATE 1 1 (nil)
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 2	FINISH
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
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.005406)
Heccer (dStep) : (6e-06)
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
00001 :: 20	INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE 0 3 (nil)
00011 :: 22	CONCEPTGATE 1 1 (nil)
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 2	FINISH
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
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.006)
Heccer (dStep) : (6e-06)
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
00001 :: 20	INITIALIZECHANNEL 0.045 0.000209239
00006 :: 21	LOADVOLTAGETABLE
00007 :: 22	CONCEPTGATE 0 3 (nil)
00011 :: 22	CONCEPTGATE 1 1 (nil)
00015 :: 30	UPDATECOMPARTMENTCURRENT
00016 :: 2	FINISH
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


