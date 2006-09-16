#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/code/singlep',
				command_tests => [
						  {
						   description => "Is a single passive compartment solved correctly ?",
						   read => [ 'Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (1)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
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
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
-------
Iteration 0
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (1)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
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
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680146)
-------
Iteration 1
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (1)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
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
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680292)
-------
Iteration 2
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (1)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
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
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680438)
-------
Iteration 3
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (1)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
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
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680584)
-------
Iteration 4
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (1)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
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
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680729)
-------
Iteration 5
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (1)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
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
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0680875)
-------
Iteration 6
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (1)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
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
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068102)
-------
Iteration 7
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (1)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
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
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0681165)
-------
Iteration 8
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (1)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
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
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068131)
-------
Iteration 9
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (1)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
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
Compartment operations
-----
00000 :: 4			HECCER_COP_FINISH
00001 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.00061)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0681455)
', ],
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "single passive compartment.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/doublep',
				command_tests => [
						  {
						   description => "Is a double passive compartment solved correctly ?",
						   read => [ 'Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (2)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (2)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piForward[0]) : (1)
MinimumDegree (piForward[1]) : (0)
MinimumDegree (piBackward[0]) : (1)
MinimumDegree (piBackward[1]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 4			HECCER_COP_FINISH
00003 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00005 :: 3			HECCER_COP_CALC_RESULTS
00006 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Axial Resistances (pdResults[2]) : (0)
VM Axial Resistances (pdResults[3]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
VM Membrane Potentials (pdVms[1]) : (-0.068)
-------
Iteration 0
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (2)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (2)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piForward[0]) : (1)
MinimumDegree (piForward[1]) : (0)
MinimumDegree (piBackward[0]) : (1)
MinimumDegree (piBackward[1]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 4			HECCER_COP_FINISH
00003 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00005 :: 3			HECCER_COP_CALC_RESULTS
00006 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680073)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680073)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0680146)
VM Membrane Potentials (pdVms[1]) : (-0.0680146)
-------
Iteration 1
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (2)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (2)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piForward[0]) : (1)
MinimumDegree (piForward[1]) : (0)
MinimumDegree (piBackward[0]) : (1)
MinimumDegree (piBackward[1]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 4			HECCER_COP_FINISH
00003 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00005 :: 3			HECCER_COP_CALC_RESULTS
00006 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680219)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680219)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0680292)
VM Membrane Potentials (pdVms[1]) : (-0.0680292)
-------
Iteration 2
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (2)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (2)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piForward[0]) : (1)
MinimumDegree (piForward[1]) : (0)
MinimumDegree (piBackward[0]) : (1)
MinimumDegree (piBackward[1]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 4			HECCER_COP_FINISH
00003 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00005 :: 3			HECCER_COP_CALC_RESULTS
00006 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680365)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680365)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0680438)
VM Membrane Potentials (pdVms[1]) : (-0.0680438)
-------
Iteration 3
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (2)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (2)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piForward[0]) : (1)
MinimumDegree (piForward[1]) : (0)
MinimumDegree (piBackward[0]) : (1)
MinimumDegree (piBackward[1]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 4			HECCER_COP_FINISH
00003 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00005 :: 3			HECCER_COP_CALC_RESULTS
00006 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680511)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680511)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0680584)
VM Membrane Potentials (pdVms[1]) : (-0.0680584)
-------
Iteration 4
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (2)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (2)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piForward[0]) : (1)
MinimumDegree (piForward[1]) : (0)
MinimumDegree (piBackward[0]) : (1)
MinimumDegree (piBackward[1]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 4			HECCER_COP_FINISH
00003 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00005 :: 3			HECCER_COP_CALC_RESULTS
00006 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680657)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680657)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0680729)
VM Membrane Potentials (pdVms[1]) : (-0.0680729)
-------
Iteration 5
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (2)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (2)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piForward[0]) : (1)
MinimumDegree (piForward[1]) : (0)
MinimumDegree (piBackward[0]) : (1)
MinimumDegree (piBackward[1]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 4			HECCER_COP_FINISH
00003 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00005 :: 3			HECCER_COP_CALC_RESULTS
00006 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680802)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680802)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0680875)
VM Membrane Potentials (pdVms[1]) : (-0.0680875)
-------
Iteration 6
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (2)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (2)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piForward[0]) : (1)
MinimumDegree (piForward[1]) : (0)
MinimumDegree (piBackward[0]) : (1)
MinimumDegree (piBackward[1]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 4			HECCER_COP_FINISH
00003 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00005 :: 3			HECCER_COP_CALC_RESULTS
00006 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680947)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680947)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.068102)
VM Membrane Potentials (pdVms[1]) : (-0.068102)
-------
Iteration 7
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (2)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (2)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piForward[0]) : (1)
MinimumDegree (piForward[1]) : (0)
MinimumDegree (piBackward[0]) : (1)
MinimumDegree (piBackward[1]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 4			HECCER_COP_FINISH
00003 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00005 :: 3			HECCER_COP_CALC_RESULTS
00006 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681093)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681093)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0681165)
VM Membrane Potentials (pdVms[1]) : (-0.0681165)
-------
Iteration 8
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (2)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (2)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piForward[0]) : (1)
MinimumDegree (piForward[1]) : (0)
MinimumDegree (piBackward[0]) : (1)
MinimumDegree (piBackward[1]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 4			HECCER_COP_FINISH
00003 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00005 :: 3			HECCER_COP_CALC_RESULTS
00006 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681237)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681237)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.068131)
VM Membrane Potentials (pdVms[1]) : (-0.068131)
-------
Iteration 9
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (2)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (2)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piForward[0]) : (1)
MinimumDegree (piForward[1]) : (0)
MinimumDegree (piBackward[0]) : (1)
MinimumDegree (piBackward[1]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 4			HECCER_COP_FINISH
00003 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00005 :: 3			HECCER_COP_CALC_RESULTS
00006 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681382)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681382)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0681455)
VM Membrane Potentials (pdVms[1]) : (-0.0681455)
', ],
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "double passive compartment.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/triplep',
				command_tests => [
						  {
						   description => "Is a triple passive compartment solved correctly ?",
						   read => [ 'Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Axial Resistances (pdResults[2]) : (0)
VM Axial Resistances (pdResults[3]) : (0)
VM Axial Resistances (pdResults[4]) : (0)
VM Axial Resistances (pdResults[5]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
VM Membrane Potentials (pdVms[1]) : (-0.068)
VM Membrane Potentials (pdVms[2]) : (-0.068)
-------
Iteration 0
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680073)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680073)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680073)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0680146)
VM Membrane Potentials (pdVms[1]) : (-0.0680146)
VM Membrane Potentials (pdVms[2]) : (-0.0680146)
-------
Iteration 1
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680219)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680219)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680219)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0680292)
VM Membrane Potentials (pdVms[1]) : (-0.0680292)
VM Membrane Potentials (pdVms[2]) : (-0.0680292)
-------
Iteration 2
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680365)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680365)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680365)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0680438)
VM Membrane Potentials (pdVms[1]) : (-0.0680438)
VM Membrane Potentials (pdVms[2]) : (-0.0680438)
-------
Iteration 3
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680511)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680511)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680511)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0680584)
VM Membrane Potentials (pdVms[1]) : (-0.0680584)
VM Membrane Potentials (pdVms[2]) : (-0.0680584)
-------
Iteration 4
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680657)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680657)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680657)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0680729)
VM Membrane Potentials (pdVms[1]) : (-0.0680729)
VM Membrane Potentials (pdVms[2]) : (-0.0680729)
-------
Iteration 5
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680802)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680802)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680802)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0680875)
VM Membrane Potentials (pdVms[1]) : (-0.0680875)
VM Membrane Potentials (pdVms[2]) : (-0.0680875)
-------
Iteration 6
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680947)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680947)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680947)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.068102)
VM Membrane Potentials (pdVms[1]) : (-0.068102)
VM Membrane Potentials (pdVms[2]) : (-0.068102)
-------
Iteration 7
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681093)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681093)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0681093)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0681165)
VM Membrane Potentials (pdVms[1]) : (-0.0681165)
VM Membrane Potentials (pdVms[2]) : (-0.0681165)
-------
Iteration 8
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681237)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681237)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0681237)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.068131)
VM Membrane Potentials (pdVms[1]) : (-0.068131)
VM Membrane Potentials (pdVms[2]) : (-0.068131)
-------
Iteration 9
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681382)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681382)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0681382)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0681455)
VM Membrane Potentials (pdVms[1]) : (-0.0681455)
VM Membrane Potentials (pdVms[2]) : (-0.0681455)
', ],
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "triple passive compartment.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/fork3p',
				command_tests => [
						  {
						   description => "Is a fork of three passive compartment solved correctly ?",
						   read => [ 'Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Axial Resistances (pdResults[2]) : (0)
VM Axial Resistances (pdResults[3]) : (0)
VM Axial Resistances (pdResults[4]) : (0)
VM Axial Resistances (pdResults[5]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
VM Membrane Potentials (pdVms[1]) : (-0.068)
VM Membrane Potentials (pdVms[2]) : (-0.068)
-------
Iteration 0
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680073)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680073)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680073)
VM Axial Resistances (pdResults[5]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680146)
VM Membrane Potentials (pdVms[1]) : (-0.0680146)
VM Membrane Potentials (pdVms[2]) : (-0.0680146)
-------
Iteration 1
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680219)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680219)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680219)
VM Axial Resistances (pdResults[5]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680292)
VM Membrane Potentials (pdVms[1]) : (-0.0680292)
VM Membrane Potentials (pdVms[2]) : (-0.0680292)
-------
Iteration 2
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680365)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680365)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680365)
VM Axial Resistances (pdResults[5]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680438)
VM Membrane Potentials (pdVms[1]) : (-0.0680438)
VM Membrane Potentials (pdVms[2]) : (-0.0680438)
-------
Iteration 3
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680511)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680511)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680511)
VM Axial Resistances (pdResults[5]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680584)
VM Membrane Potentials (pdVms[1]) : (-0.0680584)
VM Membrane Potentials (pdVms[2]) : (-0.0680584)
-------
Iteration 4
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680657)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680657)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680657)
VM Axial Resistances (pdResults[5]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680729)
VM Membrane Potentials (pdVms[1]) : (-0.0680729)
VM Membrane Potentials (pdVms[2]) : (-0.0680729)
-------
Iteration 5
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680802)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680802)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680802)
VM Axial Resistances (pdResults[5]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680875)
VM Membrane Potentials (pdVms[1]) : (-0.0680875)
VM Membrane Potentials (pdVms[2]) : (-0.0680875)
-------
Iteration 6
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680947)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680947)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680947)
VM Axial Resistances (pdResults[5]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.068102)
VM Membrane Potentials (pdVms[1]) : (-0.068102)
VM Membrane Potentials (pdVms[2]) : (-0.068102)
-------
Iteration 7
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681093)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681093)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0681093)
VM Axial Resistances (pdResults[5]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0681165)
VM Membrane Potentials (pdVms[1]) : (-0.0681165)
VM Membrane Potentials (pdVms[2]) : (-0.0681165)
-------
Iteration 8
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681237)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681237)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0681237)
VM Axial Resistances (pdResults[5]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.068131)
VM Membrane Potentials (pdVms[1]) : (-0.068131)
VM Membrane Potentials (pdVms[2]) : (-0.068131)
-------
Iteration 9
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : (0)
Intermediary (iCompartments) : (3)
Compartment (mc.iSerial, mc.iType) : (1, 1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (2, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iSerial, mc.iType) : (3, 1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (3)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piForward[0]) : (2)
MinimumDegree (piForward[1]) : (1)
MinimumDegree (piForward[2]) : (0)
MinimumDegree (piBackward[0]) : (2)
MinimumDegree (piBackward[1]) : (1)
MinimumDegree (piBackward[2]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00005 :: 4			HECCER_COP_FINISH
00006 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00008 :: 3			HECCER_COP_CALC_RESULTS
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681382)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681382)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0681382)
VM Axial Resistances (pdResults[5]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0681455)
VM Membrane Potentials (pdVms[1]) : (-0.0681455)
VM Membrane Potentials (pdVms[2]) : (-0.0681455)
', ],
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "fork of three passive compartment.",
			       },
			      ],
       description => "passive model testing",
      };


return $test;


