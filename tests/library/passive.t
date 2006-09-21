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
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (1)
Compartment (mc.iType) : (1)
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
						   description => "Are two passive compartments solved correctly ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
				description => "doublet passive compartment.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/triplep',
				command_tests => [
						  {
						   description => "Are three passive compartments solved correctly ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
				description => "triplet passive compartment.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/fork3p',
				command_tests => [
						  {
						   description => "Is a fork of three passive compartments solved correctly ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (3)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
				description => "fork of three passive compartments.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/fork4p1',
				command_tests => [
						  {
						   description => "Is a fork of four passive compartments solved correctly, first alternative ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (3)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 5			HECCER_COP_SET_DIAGONAL
00004 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00006 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00008 :: 4			HECCER_COP_FINISH
00009 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_CALC_RESULTS
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_CALC_RESULTS
00018 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Axial Resistances (pdResults[2]) : (0)
VM Axial Resistances (pdResults[3]) : (0)
VM Axial Resistances (pdResults[4]) : (0)
VM Axial Resistances (pdResults[5]) : (0)
VM Axial Resistances (pdResults[6]) : (0)
VM Axial Resistances (pdResults[7]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
VM Membrane Potentials (pdVms[1]) : (-0.068)
VM Membrane Potentials (pdVms[2]) : (-0.068)
VM Membrane Potentials (pdVms[3]) : (-0.068)
-------
Iteration 0
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (3)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 5			HECCER_COP_SET_DIAGONAL
00004 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00006 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00008 :: 4			HECCER_COP_FINISH
00009 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_CALC_RESULTS
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_CALC_RESULTS
00018 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680073)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680073)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680073)
VM Axial Resistances (pdResults[5]) : (1.98441)
VM Axial Resistances (pdResults[6]) : (-0.0680073)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680146)
VM Membrane Potentials (pdVms[1]) : (-0.0680146)
VM Membrane Potentials (pdVms[2]) : (-0.0680146)
VM Membrane Potentials (pdVms[3]) : (-0.0680146)
-------
Iteration 1
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (3)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 5			HECCER_COP_SET_DIAGONAL
00004 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00006 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00008 :: 4			HECCER_COP_FINISH
00009 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_CALC_RESULTS
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_CALC_RESULTS
00018 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680219)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680219)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680219)
VM Axial Resistances (pdResults[5]) : (1.98441)
VM Axial Resistances (pdResults[6]) : (-0.0680219)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680292)
VM Membrane Potentials (pdVms[1]) : (-0.0680292)
VM Membrane Potentials (pdVms[2]) : (-0.0680292)
VM Membrane Potentials (pdVms[3]) : (-0.0680292)
-------
Iteration 2
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (3)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 5			HECCER_COP_SET_DIAGONAL
00004 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00006 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00008 :: 4			HECCER_COP_FINISH
00009 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_CALC_RESULTS
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_CALC_RESULTS
00018 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680365)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680365)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680365)
VM Axial Resistances (pdResults[5]) : (1.98441)
VM Axial Resistances (pdResults[6]) : (-0.0680365)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680438)
VM Membrane Potentials (pdVms[1]) : (-0.0680438)
VM Membrane Potentials (pdVms[2]) : (-0.0680438)
VM Membrane Potentials (pdVms[3]) : (-0.0680438)
-------
Iteration 3
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (3)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 5			HECCER_COP_SET_DIAGONAL
00004 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00006 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00008 :: 4			HECCER_COP_FINISH
00009 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_CALC_RESULTS
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_CALC_RESULTS
00018 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680511)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680511)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680511)
VM Axial Resistances (pdResults[5]) : (1.98441)
VM Axial Resistances (pdResults[6]) : (-0.0680511)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680584)
VM Membrane Potentials (pdVms[1]) : (-0.0680584)
VM Membrane Potentials (pdVms[2]) : (-0.0680584)
VM Membrane Potentials (pdVms[3]) : (-0.0680584)
-------
Iteration 4
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (3)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 5			HECCER_COP_SET_DIAGONAL
00004 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00006 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00008 :: 4			HECCER_COP_FINISH
00009 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_CALC_RESULTS
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_CALC_RESULTS
00018 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680657)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680657)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680657)
VM Axial Resistances (pdResults[5]) : (1.98441)
VM Axial Resistances (pdResults[6]) : (-0.0680657)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680729)
VM Membrane Potentials (pdVms[1]) : (-0.0680729)
VM Membrane Potentials (pdVms[2]) : (-0.0680729)
VM Membrane Potentials (pdVms[3]) : (-0.0680729)
-------
Iteration 5
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (3)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 5			HECCER_COP_SET_DIAGONAL
00004 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00006 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00008 :: 4			HECCER_COP_FINISH
00009 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_CALC_RESULTS
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_CALC_RESULTS
00018 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680802)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680802)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680802)
VM Axial Resistances (pdResults[5]) : (1.98441)
VM Axial Resistances (pdResults[6]) : (-0.0680802)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680875)
VM Membrane Potentials (pdVms[1]) : (-0.0680875)
VM Membrane Potentials (pdVms[2]) : (-0.0680875)
VM Membrane Potentials (pdVms[3]) : (-0.0680875)
-------
Iteration 6
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (3)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 5			HECCER_COP_SET_DIAGONAL
00004 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00006 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00008 :: 4			HECCER_COP_FINISH
00009 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_CALC_RESULTS
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_CALC_RESULTS
00018 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680947)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680947)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680947)
VM Axial Resistances (pdResults[5]) : (1.98441)
VM Axial Resistances (pdResults[6]) : (-0.0680947)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.068102)
VM Membrane Potentials (pdVms[1]) : (-0.068102)
VM Membrane Potentials (pdVms[2]) : (-0.068102)
VM Membrane Potentials (pdVms[3]) : (-0.068102)
-------
Iteration 7
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (3)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 5			HECCER_COP_SET_DIAGONAL
00004 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00006 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00008 :: 4			HECCER_COP_FINISH
00009 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_CALC_RESULTS
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_CALC_RESULTS
00018 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681093)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681093)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0681093)
VM Axial Resistances (pdResults[5]) : (1.98441)
VM Axial Resistances (pdResults[6]) : (-0.0681093)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0681165)
VM Membrane Potentials (pdVms[1]) : (-0.0681165)
VM Membrane Potentials (pdVms[2]) : (-0.0681165)
VM Membrane Potentials (pdVms[3]) : (-0.0681165)
-------
Iteration 8
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (3)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 5			HECCER_COP_SET_DIAGONAL
00004 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00006 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00008 :: 4			HECCER_COP_FINISH
00009 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_CALC_RESULTS
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_CALC_RESULTS
00018 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681237)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681237)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0681237)
VM Axial Resistances (pdResults[5]) : (1.98441)
VM Axial Resistances (pdResults[6]) : (-0.0681237)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.068131)
VM Membrane Potentials (pdVms[1]) : (-0.068131)
VM Membrane Potentials (pdVms[2]) : (-0.068131)
VM Membrane Potentials (pdVms[3]) : (-0.068131)
-------
Iteration 9
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (3)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 5			HECCER_COP_SET_DIAGONAL
00001 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00003 :: 5			HECCER_COP_SET_DIAGONAL
00004 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00006 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00008 :: 4			HECCER_COP_FINISH
00009 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00011 :: 3			HECCER_COP_CALC_RESULTS
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_CALC_RESULTS
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_CALC_RESULTS
00018 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (2.21315)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681382)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681382)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0681382)
VM Axial Resistances (pdResults[5]) : (1.98441)
VM Axial Resistances (pdResults[6]) : (-0.0681382)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0681455)
VM Membrane Potentials (pdVms[1]) : (-0.0681455)
VM Membrane Potentials (pdVms[2]) : (-0.0681455)
VM Membrane Potentials (pdVms[3]) : (-0.0681455)
', ],
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "fork of four passive compartments, first alternative.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/fork4p2',
				command_tests => [
						  {
						   description => "Is a fork of four passive compartments solved correctly, second alternative ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 6			HECCER_COP_SKIP_DIAGONAL
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Axial Resistances (pdResults[2]) : (0)
VM Axial Resistances (pdResults[3]) : (0)
VM Axial Resistances (pdResults[4]) : (0)
VM Axial Resistances (pdResults[5]) : (0)
VM Axial Resistances (pdResults[6]) : (0)
VM Axial Resistances (pdResults[7]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
VM Membrane Potentials (pdVms[1]) : (-0.068)
VM Membrane Potentials (pdVms[2]) : (-0.068)
VM Membrane Potentials (pdVms[3]) : (-0.068)
-------
Iteration 0
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 6			HECCER_COP_SKIP_DIAGONAL
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680073)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680073)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680073)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680073)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680146)
VM Membrane Potentials (pdVms[1]) : (-0.0680146)
VM Membrane Potentials (pdVms[2]) : (-0.0680146)
VM Membrane Potentials (pdVms[3]) : (-0.0680146)
-------
Iteration 1
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 6			HECCER_COP_SKIP_DIAGONAL
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680219)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680219)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680219)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680219)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680292)
VM Membrane Potentials (pdVms[1]) : (-0.0680292)
VM Membrane Potentials (pdVms[2]) : (-0.0680292)
VM Membrane Potentials (pdVms[3]) : (-0.0680292)
-------
Iteration 2
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 6			HECCER_COP_SKIP_DIAGONAL
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680365)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680365)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680365)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680365)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680438)
VM Membrane Potentials (pdVms[1]) : (-0.0680438)
VM Membrane Potentials (pdVms[2]) : (-0.0680438)
VM Membrane Potentials (pdVms[3]) : (-0.0680438)
-------
Iteration 3
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 6			HECCER_COP_SKIP_DIAGONAL
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680511)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680511)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680511)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680511)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680584)
VM Membrane Potentials (pdVms[1]) : (-0.0680584)
VM Membrane Potentials (pdVms[2]) : (-0.0680584)
VM Membrane Potentials (pdVms[3]) : (-0.0680584)
-------
Iteration 4
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 6			HECCER_COP_SKIP_DIAGONAL
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680657)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680657)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680657)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680657)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680729)
VM Membrane Potentials (pdVms[1]) : (-0.0680729)
VM Membrane Potentials (pdVms[2]) : (-0.0680729)
VM Membrane Potentials (pdVms[3]) : (-0.0680729)
-------
Iteration 5
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 6			HECCER_COP_SKIP_DIAGONAL
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680802)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680802)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680802)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680802)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0680875)
VM Membrane Potentials (pdVms[1]) : (-0.0680875)
VM Membrane Potentials (pdVms[2]) : (-0.0680875)
VM Membrane Potentials (pdVms[3]) : (-0.0680875)
-------
Iteration 6
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 6			HECCER_COP_SKIP_DIAGONAL
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680947)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680947)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0680947)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680947)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.068102)
VM Membrane Potentials (pdVms[1]) : (-0.068102)
VM Membrane Potentials (pdVms[2]) : (-0.068102)
VM Membrane Potentials (pdVms[3]) : (-0.068102)
-------
Iteration 7
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 6			HECCER_COP_SKIP_DIAGONAL
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681093)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681093)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0681093)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0681093)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0681165)
VM Membrane Potentials (pdVms[1]) : (-0.0681165)
VM Membrane Potentials (pdVms[2]) : (-0.0681165)
VM Membrane Potentials (pdVms[3]) : (-0.0681165)
-------
Iteration 8
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 6			HECCER_COP_SKIP_DIAGONAL
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681237)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681237)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0681237)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0681237)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.068131)
VM Membrane Potentials (pdVms[1]) : (-0.068131)
VM Membrane Potentials (pdVms[2]) : (-0.068131)
VM Membrane Potentials (pdVms[3]) : (-0.068131)
-------
Iteration 9
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (2)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 6			HECCER_COP_SKIP_DIAGONAL
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (2.21315)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.21315)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681382)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681382)
VM Axial Resistances (pdResults[3]) : (1.98441)
VM Axial Resistances (pdResults[4]) : (-0.0681382)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0681382)
VM Axial Resistances (pdResults[7]) : (2.21315)
VM Membrane Potentials (pdVms[0]) : (-0.0681455)
VM Membrane Potentials (pdVms[1]) : (-0.0681455)
VM Membrane Potentials (pdVms[2]) : (-0.0681455)
VM Membrane Potentials (pdVms[3]) : (-0.0681455)
', ],
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "fork of four passive compartments, second alternative.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/fork4p3',
				command_tests => [
						  {
						   description => "Is a fork of four passive compartments solved correctly, third alternative ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (3)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[0][2]) : (3)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 6			HECCER_COP_SKIP_DIAGONAL
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.81942)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Axial Resistances (pdResults[2]) : (0)
VM Axial Resistances (pdResults[3]) : (0)
VM Axial Resistances (pdResults[4]) : (0)
VM Axial Resistances (pdResults[5]) : (0)
VM Axial Resistances (pdResults[6]) : (0)
VM Axial Resistances (pdResults[7]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
VM Membrane Potentials (pdVms[1]) : (-0.068)
VM Membrane Potentials (pdVms[2]) : (-0.068)
VM Membrane Potentials (pdVms[3]) : (-0.068)
-------
Iteration 0
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (3)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[0][2]) : (3)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 6			HECCER_COP_SKIP_DIAGONAL
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.81942)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680073)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680073)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680073)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680073)
VM Axial Resistances (pdResults[7]) : (2.81942)
VM Membrane Potentials (pdVms[0]) : (-0.0680146)
VM Membrane Potentials (pdVms[1]) : (-0.0680146)
VM Membrane Potentials (pdVms[2]) : (-0.0680146)
VM Membrane Potentials (pdVms[3]) : (-0.0680146)
-------
Iteration 1
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (3)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[0][2]) : (3)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 6			HECCER_COP_SKIP_DIAGONAL
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.81942)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680219)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680219)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680219)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680219)
VM Axial Resistances (pdResults[7]) : (2.81942)
VM Membrane Potentials (pdVms[0]) : (-0.0680292)
VM Membrane Potentials (pdVms[1]) : (-0.0680292)
VM Membrane Potentials (pdVms[2]) : (-0.0680292)
VM Membrane Potentials (pdVms[3]) : (-0.0680292)
-------
Iteration 2
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (3)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[0][2]) : (3)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 6			HECCER_COP_SKIP_DIAGONAL
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.81942)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680365)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680365)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680365)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680365)
VM Axial Resistances (pdResults[7]) : (2.81942)
VM Membrane Potentials (pdVms[0]) : (-0.0680438)
VM Membrane Potentials (pdVms[1]) : (-0.0680438)
VM Membrane Potentials (pdVms[2]) : (-0.0680438)
VM Membrane Potentials (pdVms[3]) : (-0.0680438)
-------
Iteration 3
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (3)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[0][2]) : (3)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 6			HECCER_COP_SKIP_DIAGONAL
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.81942)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680511)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680511)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680511)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680511)
VM Axial Resistances (pdResults[7]) : (2.81942)
VM Membrane Potentials (pdVms[0]) : (-0.0680584)
VM Membrane Potentials (pdVms[1]) : (-0.0680584)
VM Membrane Potentials (pdVms[2]) : (-0.0680584)
VM Membrane Potentials (pdVms[3]) : (-0.0680584)
-------
Iteration 4
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (3)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[0][2]) : (3)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 6			HECCER_COP_SKIP_DIAGONAL
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.81942)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680657)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680657)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680657)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680657)
VM Axial Resistances (pdResults[7]) : (2.81942)
VM Membrane Potentials (pdVms[0]) : (-0.0680729)
VM Membrane Potentials (pdVms[1]) : (-0.0680729)
VM Membrane Potentials (pdVms[2]) : (-0.0680729)
VM Membrane Potentials (pdVms[3]) : (-0.0680729)
-------
Iteration 5
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (3)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[0][2]) : (3)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 6			HECCER_COP_SKIP_DIAGONAL
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.81942)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680802)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680802)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680802)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680802)
VM Axial Resistances (pdResults[7]) : (2.81942)
VM Membrane Potentials (pdVms[0]) : (-0.0680875)
VM Membrane Potentials (pdVms[1]) : (-0.0680875)
VM Membrane Potentials (pdVms[2]) : (-0.0680875)
VM Membrane Potentials (pdVms[3]) : (-0.0680875)
-------
Iteration 6
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (3)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[0][2]) : (3)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 6			HECCER_COP_SKIP_DIAGONAL
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.81942)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0680947)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0680947)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0680947)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0680947)
VM Axial Resistances (pdResults[7]) : (2.81942)
VM Membrane Potentials (pdVms[0]) : (-0.068102)
VM Membrane Potentials (pdVms[1]) : (-0.068102)
VM Membrane Potentials (pdVms[2]) : (-0.068102)
VM Membrane Potentials (pdVms[3]) : (-0.068102)
-------
Iteration 7
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (3)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[0][2]) : (3)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 6			HECCER_COP_SKIP_DIAGONAL
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.81942)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681093)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681093)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0681093)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0681093)
VM Axial Resistances (pdResults[7]) : (2.81942)
VM Membrane Potentials (pdVms[0]) : (-0.0681165)
VM Membrane Potentials (pdVms[1]) : (-0.0681165)
VM Membrane Potentials (pdVms[2]) : (-0.0681165)
VM Membrane Potentials (pdVms[3]) : (-0.0681165)
-------
Iteration 8
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (3)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[0][2]) : (3)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 6			HECCER_COP_SKIP_DIAGONAL
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.81942)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681237)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681237)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0681237)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0681237)
VM Axial Resistances (pdResults[7]) : (2.81942)
VM Membrane Potentials (pdVms[0]) : (-0.068131)
VM Membrane Potentials (pdVms[1]) : (-0.068131)
VM Membrane Potentials (pdVms[2]) : (-0.068131)
VM Membrane Potentials (pdVms[3]) : (-0.068131)
-------
Iteration 9
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (4)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
MinimumDegree (iEntries) : (4)
MinimumDegree (piChildren[0]) : (3)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[0][1]) : (2)
MinimumDegree (piChildren[0][2]) : (3)
MinimumDegree (piChildren[1]) : (0)
MinimumDegree (piChildren[2]) : (0)
MinimumDegree (piChildren[3]) : (0)
MinimumDegree (piForward[0]) : (3)
MinimumDegree (piForward[1]) : (2)
MinimumDegree (piForward[2]) : (1)
MinimumDegree (piForward[3]) : (0)
MinimumDegree (piBackward[0]) : (3)
MinimumDegree (piBackward[1]) : (2)
MinimumDegree (piBackward[2]) : (1)
MinimumDegree (piBackward[3]) : (0)
Compartment operations
-----
00000 :: 6			HECCER_COP_SKIP_DIAGONAL
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_CALC_RESULTS
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_CALC_RESULTS
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_CALC_RESULTS
00017 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (1.60688)
VM Diagonals (pdDiagonals[1]) : (1.60688)
VM Diagonals (pdDiagonals[2]) : (1.60688)
VM Diagonals (pdDiagonals[3]) : (2.81942)
VM Axial Resistances (pdAxres[0]) : (-0.60627)
VM Axial Resistances (pdAxres[1]) : (-0.60627)
VM Axial Resistances (pdAxres[2]) : (-0.60627)
VM Axial Resistances (pdAxres[3]) : (-0.60627)
VM Axial Resistances (pdAxres[4]) : (-0.60627)
VM Axial Resistances (pdAxres[5]) : (-0.60627)
VM Axial Resistances (pdAxres[6]) : (-0.60627)
VM Axial Resistances (pdAxres[7]) : (-0.60627)
VM Axial Resistances (pdAxres[8]) : (-0.60627)
VM Axial Resistances (pdResults[0]) : (-0.0681382)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0681382)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Axial Resistances (pdResults[4]) : (-0.0681382)
VM Axial Resistances (pdResults[5]) : (1.60688)
VM Axial Resistances (pdResults[6]) : (-0.0681382)
VM Axial Resistances (pdResults[7]) : (2.81942)
VM Membrane Potentials (pdVms[0]) : (-0.0681455)
VM Membrane Potentials (pdVms[1]) : (-0.0681455)
VM Membrane Potentials (pdVms[2]) : (-0.0681455)
VM Membrane Potentials (pdVms[3]) : (-0.0681455)
', ],
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "fork of four passive compartments, third alternative.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/c1c2p1',
				command_tests => [
						  {
						   description => "Are two passive compartments with injected current solved correctly ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
VM Axial Resistances (pdResults[0]) : (-0.067409)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0664214)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0668179)
VM Membrane Potentials (pdVms[1]) : (-0.0648428)
-------
Iteration 1
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
VM Axial Resistances (pdResults[0]) : (-0.0656868)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0638068)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0645558)
VM Membrane Potentials (pdVms[1]) : (-0.0627709)
-------
Iteration 2
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
VM Axial Resistances (pdResults[0]) : (-0.0634782)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0616841)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0624006)
VM Membrane Potentials (pdVms[1]) : (-0.0605973)
-------
Iteration 3
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
VM Axial Resistances (pdResults[0]) : (-0.0613193)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0595169)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0602379)
VM Membrane Potentials (pdVms[1]) : (-0.0584365)
-------
Iteration 4
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
VM Axial Resistances (pdResults[0]) : (-0.0591584)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0573569)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0580789)
VM Membrane Potentials (pdVms[1]) : (-0.0562773)
-------
Iteration 5
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
VM Axial Resistances (pdResults[0]) : (-0.0570007)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0551991)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0559225)
VM Membrane Potentials (pdVms[1]) : (-0.0541208)
-------
Iteration 6
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
VM Axial Resistances (pdResults[0]) : (-0.0548455)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0530439)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0537686)
VM Membrane Potentials (pdVms[1]) : (-0.051967)
-------
Iteration 7
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
VM Axial Resistances (pdResults[0]) : (-0.052693)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0508914)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0516174)
VM Membrane Potentials (pdVms[1]) : (-0.0498158)
-------
Iteration 8
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
VM Axial Resistances (pdResults[0]) : (-0.0505431)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0487415)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0494688)
VM Membrane Potentials (pdVms[1]) : (-0.0476672)
-------
Iteration 9
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
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
VM Axial Resistances (pdResults[0]) : (-0.0483958)
VM Axial Resistances (pdResults[1]) : (1.60688)
VM Axial Resistances (pdResults[2]) : (-0.0465942)
VM Axial Resistances (pdResults[3]) : (1.60688)
VM Membrane Potentials (pdVms[0]) : (-0.0473228)
VM Membrane Potentials (pdVms[1]) : (-0.0455212)
', ],
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "two passive compartments with injected current",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/c1c2p2',
				command_tests => [
						  {
						   description => "Are two passive compartments with asymetric properties and injected current solved correctly ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.75533e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (772813)
Compartment (dRm) : (8.5486e+09)
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
VM Diagonals (pdDiagonals[0]) : (3.24851)
VM Diagonals (pdDiagonals[1]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-0.282813)
VM Axial Resistances (pdAxres[1]) : (-2.2483)
VM Axial Resistances (pdAxres[2]) : (-2.2483)
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
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.75533e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (772813)
Compartment (dRm) : (8.5486e+09)
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
VM Diagonals (pdDiagonals[0]) : (3.24851)
VM Diagonals (pdDiagonals[1]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-0.282813)
VM Axial Resistances (pdAxres[1]) : (-2.2483)
VM Axial Resistances (pdAxres[2]) : (-2.2483)
VM Axial Resistances (pdResults[0]) : (-0.0666148)
VM Axial Resistances (pdResults[1]) : (3.24851)
VM Axial Resistances (pdResults[2]) : (-0.0659975)
VM Axial Resistances (pdResults[3]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0652296)
VM Membrane Potentials (pdVms[1]) : (-0.063995)
-------
Iteration 1
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.75533e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (772813)
Compartment (dRm) : (8.5486e+09)
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
VM Diagonals (pdDiagonals[0]) : (3.24851)
VM Diagonals (pdDiagonals[1]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-0.282813)
VM Axial Resistances (pdAxres[1]) : (-2.2483)
VM Axial Resistances (pdAxres[2]) : (-2.2483)
VM Axial Resistances (pdResults[0]) : (-0.0630601)
VM Axial Resistances (pdResults[1]) : (3.24851)
VM Axial Resistances (pdResults[2]) : (-0.0620936)
VM Axial Resistances (pdResults[3]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0608906)
VM Membrane Potentials (pdVms[1]) : (-0.0601923)
-------
Iteration 2
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.75533e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (772813)
Compartment (dRm) : (8.5486e+09)
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
VM Diagonals (pdDiagonals[0]) : (3.24851)
VM Diagonals (pdDiagonals[1]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-0.282813)
VM Axial Resistances (pdAxres[1]) : (-2.2483)
VM Axial Resistances (pdAxres[2]) : (-2.2483)
VM Axial Resistances (pdResults[0]) : (-0.0590644)
VM Axial Resistances (pdResults[1]) : (3.24851)
VM Axial Resistances (pdResults[2]) : (-0.0582502)
VM Axial Resistances (pdResults[3]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0572381)
VM Membrane Potentials (pdVms[1]) : (-0.0563081)
-------
Iteration 3
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.75533e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (772813)
Compartment (dRm) : (8.5486e+09)
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
VM Diagonals (pdDiagonals[0]) : (3.24851)
VM Diagonals (pdDiagonals[1]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-0.282813)
VM Axial Resistances (pdAxres[1]) : (-2.2483)
VM Axial Resistances (pdAxres[2]) : (-2.2483)
VM Axial Resistances (pdResults[0]) : (-0.0552661)
VM Axial Resistances (pdResults[1]) : (3.24851)
VM Axial Resistances (pdResults[2]) : (-0.0543868)
VM Axial Resistances (pdResults[3]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0532941)
VM Membrane Potentials (pdVms[1]) : (-0.0524655)
-------
Iteration 4
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.75533e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (772813)
Compartment (dRm) : (8.5486e+09)
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
VM Diagonals (pdDiagonals[0]) : (3.24851)
VM Diagonals (pdDiagonals[1]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-0.282813)
VM Axial Resistances (pdAxres[1]) : (-2.2483)
VM Axial Resistances (pdAxres[2]) : (-2.2483)
VM Axial Resistances (pdResults[0]) : (-0.0513885)
VM Axial Resistances (pdResults[1]) : (3.24851)
VM Axial Resistances (pdResults[2]) : (-0.0505383)
VM Axial Resistances (pdResults[3]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0494828)
VM Membrane Potentials (pdVms[1]) : (-0.0486111)
-------
Iteration 5
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.75533e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (772813)
Compartment (dRm) : (8.5486e+09)
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
VM Diagonals (pdDiagonals[0]) : (3.24851)
VM Diagonals (pdDiagonals[1]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-0.282813)
VM Axial Resistances (pdAxres[1]) : (-2.2483)
VM Axial Resistances (pdAxres[2]) : (-2.2483)
VM Axial Resistances (pdResults[0]) : (-0.0475515)
VM Axial Resistances (pdResults[1]) : (3.24851)
VM Axial Resistances (pdResults[2]) : (-0.0466895)
VM Axial Resistances (pdResults[3]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0456202)
VM Membrane Potentials (pdVms[1]) : (-0.044768)
-------
Iteration 6
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.75533e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (772813)
Compartment (dRm) : (8.5486e+09)
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
VM Diagonals (pdDiagonals[0]) : (3.24851)
VM Diagonals (pdDiagonals[1]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-0.282813)
VM Axial Resistances (pdAxres[1]) : (-2.2483)
VM Axial Resistances (pdAxres[2]) : (-2.2483)
VM Axial Resistances (pdResults[0]) : (-0.0437031)
VM Axial Resistances (pdResults[1]) : (3.24851)
VM Axial Resistances (pdResults[2]) : (-0.0428471)
VM Axial Resistances (pdResults[3]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.041786)
VM Membrane Potentials (pdVms[1]) : (-0.0409262)
-------
Iteration 7
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.75533e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (772813)
Compartment (dRm) : (8.5486e+09)
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
VM Diagonals (pdDiagonals[0]) : (3.24851)
VM Diagonals (pdDiagonals[1]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-0.282813)
VM Axial Resistances (pdAxres[1]) : (-2.2483)
VM Axial Resistances (pdAxres[2]) : (-2.2483)
VM Axial Resistances (pdResults[0]) : (-0.0398658)
VM Axial Resistances (pdResults[1]) : (3.24851)
VM Axial Resistances (pdResults[2]) : (-0.0390082)
VM Axial Resistances (pdResults[3]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0379457)
VM Membrane Potentials (pdVms[1]) : (-0.0370901)
-------
Iteration 8
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.75533e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (772813)
Compartment (dRm) : (8.5486e+09)
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
VM Diagonals (pdDiagonals[0]) : (3.24851)
VM Diagonals (pdDiagonals[1]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-0.282813)
VM Axial Resistances (pdAxres[1]) : (-2.2483)
VM Axial Resistances (pdAxres[2]) : (-2.2483)
VM Axial Resistances (pdResults[0]) : (-0.03603)
VM Axial Resistances (pdResults[1]) : (3.24851)
VM Axial Resistances (pdResults[2]) : (-0.0351739)
VM Axial Resistances (pdResults[3]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0341143)
VM Membrane Potentials (pdVms[1]) : (-0.0332577)
-------
Iteration 9
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (2)
Compartment (mc.iType) : (1)
Compartment (iParent) : (-1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (4.57537e-11)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (1e-08)
Compartment (dRa) : (360502)
Compartment (dRm) : (3.58441e+08)
Compartment (mc.iType) : (1)
Compartment (iParent) : (0)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.75533e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (772813)
Compartment (dRm) : (8.5486e+09)
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
VM Diagonals (pdDiagonals[0]) : (3.24851)
VM Diagonals (pdDiagonals[1]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-0.282813)
VM Axial Resistances (pdAxres[1]) : (-2.2483)
VM Axial Resistances (pdAxres[2]) : (-2.2483)
VM Axial Resistances (pdResults[0]) : (-0.0321997)
VM Axial Resistances (pdResults[1]) : (3.24851)
VM Axial Resistances (pdResults[2]) : (-0.0313438)
VM Axial Resistances (pdResults[3]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0302852)
VM Membrane Potentials (pdVms[1]) : (-0.0294299)
', ],
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "two passive compartments with asymetric properties and injected current",
			       },
			      ],
       description => "passive model testing",
      };


return $test;


