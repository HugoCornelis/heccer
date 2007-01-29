#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/code/callout1',
				command_tests => [
						  {
						   description => "Are callouts correctly executed, one compartment case ?",
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
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
The pefSoma callout says that it is computing current and conductance externally
The pefSoma callout is advancing to time 2e-05
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
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680146)
The pefSoma callout says that it is computing current and conductance externally
The pefSoma callout is advancing to time 4e-05
-------
Iteration 1
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (4e-05)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680292)
The pefSoma callout says that it is computing current and conductance externally
The pefSoma callout is advancing to time 6e-05
-------
Iteration 2
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (6e-05)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680438)
The pefSoma callout says that it is computing current and conductance externally
The pefSoma callout is advancing to time 8e-05
-------
Iteration 3
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (8e-05)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680584)
The pefSoma callout says that it is computing current and conductance externally
The pefSoma callout is advancing to time 0.0001
-------
Iteration 4
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.0001)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680729)
The pefSoma callout says that it is computing current and conductance externally
The pefSoma callout is advancing to time 0.00012
-------
Iteration 5
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00012)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680875)
The pefSoma callout says that it is computing current and conductance externally
The pefSoma callout is advancing to time 0.00014
-------
Iteration 6
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00014)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068102)
The pefSoma callout says that it is computing current and conductance externally
The pefSoma callout is advancing to time 0.00016
-------
Iteration 7
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00016)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0681165)
The pefSoma callout says that it is computing current and conductance externally
The pefSoma callout is advancing to time 0.00018
-------
Iteration 8
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00018)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068131)
The pefSoma callout says that it is computing current and conductance externally
The pefSoma callout is advancing to time 0.0002
-------
Iteration 9
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.0002)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0681455)
', ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "callout execution, one compartment case",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/calloutInjector',
				command_tests => [
						  {
						   description => "Are callouts correctly executed, one compartment case, injected current for some steps ?",
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
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
The pefInjector callout injected 0 current, and added 0 conductance, at step 1
The pefInjector callout is advancing to time 2e-05
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
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680146)
The pefInjector callout injected 0 current, and added 0 conductance, at step 2
The pefInjector callout is advancing to time 4e-05
-------
Iteration 1
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (4e-05)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680292)
The pefInjector callout injected 5e-10 current, and added 0 conductance, at step 3
The pefInjector callout is advancing to time 6e-05
-------
Iteration 2
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (6e-05)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0678254)
The pefInjector callout injected 5e-10 current, and added 0 conductance, at step 4
The pefInjector callout is advancing to time 8e-05
-------
Iteration 3
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (8e-05)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0676218)
The pefInjector callout injected 5e-10 current, and added 0 conductance, at step 5
The pefInjector callout is advancing to time 0.0001
-------
Iteration 4
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.0001)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0674185)
The pefInjector callout injected 5e-10 current, and added 0 conductance, at step 6
The pefInjector callout is advancing to time 0.00012
-------
Iteration 5
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00012)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0672154)
The pefInjector callout injected 5e-10 current, and added 0 conductance, at step 7
The pefInjector callout is advancing to time 0.00014
-------
Iteration 6
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00014)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0670125)
The pefInjector callout injected 5e-10 current, and added 0 conductance, at step 8
The pefInjector callout is advancing to time 0.00016
-------
Iteration 7
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00016)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0668099)
The pefInjector callout injected 0 current, and added 0 conductance, at step 9
The pefInjector callout is advancing to time 0.00018
-------
Iteration 8
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.00018)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.066826)
The pefInjector callout injected 0 current, and added 0 conductance, at step 10
The pefInjector callout is advancing to time 0.0002
-------
Iteration 9
Heccer (iStatus) : (20)
Heccer Options (iOptions) : (0)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dBasalActivatorStart) : (4e-05)
Heccer Options (dBasalActivatorEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer (dTime) : (0.0002)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (1)
MinimumDegree (piChildren[0]) : (0)
MinimumDegree (piForward[0]) : (0)
MinimumDegree (piBackward[0]) : (0)
Tables (iTabulatedGateCount) : (0)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 218562 1.00061
00001 :: CALLOUT
00002 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0668421)
', ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "callout execution, one compartment case, injected current",
			       },
			      ],
       description => "external callout testing",
       name => 'callout.t',
      };


return $test;


