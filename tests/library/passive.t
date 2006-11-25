#!/usr/bin/perl -w
#

use strict;

#t
#t Need a test with one passive compartment that has self as parent.
#t This is supposed to fail, but it just gives wrong results instead
#t of failing.
#t
#t This came out as an annoyance during implementation of the swig perl glue.
#t

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
Heccer (dTime) : (0)
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
Heccer (dTime) : (2e-05)
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
Heccer (dTime) : (4e-05)
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
Heccer (dTime) : (6e-05)
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
Heccer (dTime) : (8e-05)
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
Heccer (dTime) : (0.0001)
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
Heccer (dTime) : (0.00012)
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
Heccer (dTime) : (0.00014)
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
Heccer (dTime) : (0.00016)
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
Heccer (dTime) : (0.00018)
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
Heccer (dTime) : (0.0002)
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
Heccer (dTime) : (0)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (2e-05)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (4e-05)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (6e-05)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (8e-05)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0001)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00012)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00014)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00016)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00018)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0002)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (2e-05)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (4e-05)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (6e-05)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (8e-05)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0001)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00012)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00014)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00016)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00018)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0002)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (2e-05)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (4e-05)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (6e-05)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (8e-05)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0001)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00012)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00014)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00016)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00018)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0002)
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
00008 :: 3			HECCER_COP_FINISH_ROW
00009 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00011 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0)
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
00011 :: 3			HECCER_COP_FINISH_ROW
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_FINISH_ROW
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (2e-05)
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
00011 :: 3			HECCER_COP_FINISH_ROW
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_FINISH_ROW
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (4e-05)
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
00011 :: 3			HECCER_COP_FINISH_ROW
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_FINISH_ROW
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (6e-05)
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
00011 :: 3			HECCER_COP_FINISH_ROW
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_FINISH_ROW
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (8e-05)
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
00011 :: 3			HECCER_COP_FINISH_ROW
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_FINISH_ROW
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0001)
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
00011 :: 3			HECCER_COP_FINISH_ROW
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_FINISH_ROW
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00012)
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
00011 :: 3			HECCER_COP_FINISH_ROW
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_FINISH_ROW
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00014)
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
00011 :: 3			HECCER_COP_FINISH_ROW
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_FINISH_ROW
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00016)
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
00011 :: 3			HECCER_COP_FINISH_ROW
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_FINISH_ROW
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00018)
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
00011 :: 3			HECCER_COP_FINISH_ROW
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_FINISH_ROW
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0002)
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
00011 :: 3			HECCER_COP_FINISH_ROW
00012 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00014 :: 3			HECCER_COP_FINISH_ROW
00015 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00017 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0)
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
00002 :: 6			HECCER_COP_NEXT_ROW
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (2e-05)
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
00002 :: 6			HECCER_COP_NEXT_ROW
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (4e-05)
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
00002 :: 6			HECCER_COP_NEXT_ROW
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (6e-05)
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
00002 :: 6			HECCER_COP_NEXT_ROW
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (8e-05)
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
00002 :: 6			HECCER_COP_NEXT_ROW
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0001)
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
00002 :: 6			HECCER_COP_NEXT_ROW
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00012)
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
00002 :: 6			HECCER_COP_NEXT_ROW
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00014)
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
00002 :: 6			HECCER_COP_NEXT_ROW
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00016)
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
00002 :: 6			HECCER_COP_NEXT_ROW
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00018)
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
00002 :: 6			HECCER_COP_NEXT_ROW
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0002)
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
00002 :: 6			HECCER_COP_NEXT_ROW
00003 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00005 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0)
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
00000 :: 6			HECCER_COP_NEXT_ROW
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (2e-05)
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
00000 :: 6			HECCER_COP_NEXT_ROW
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (4e-05)
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
00000 :: 6			HECCER_COP_NEXT_ROW
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (6e-05)
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
00000 :: 6			HECCER_COP_NEXT_ROW
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (8e-05)
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
00000 :: 6			HECCER_COP_NEXT_ROW
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0001)
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
00000 :: 6			HECCER_COP_NEXT_ROW
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00012)
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
00000 :: 6			HECCER_COP_NEXT_ROW
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00014)
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
00000 :: 6			HECCER_COP_NEXT_ROW
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00016)
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
00000 :: 6			HECCER_COP_NEXT_ROW
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00018)
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
00000 :: 6			HECCER_COP_NEXT_ROW
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0002)
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
00000 :: 6			HECCER_COP_NEXT_ROW
00001 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00007 :: 4			HECCER_COP_FINISH
00008 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00010 :: 3			HECCER_COP_FINISH_ROW
00011 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00013 :: 3			HECCER_COP_FINISH_ROW
00014 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00016 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (2e-05)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (4e-05)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (6e-05)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (8e-05)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0001)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00012)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00014)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00016)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00018)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0002)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (2e-05)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (4e-05)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (6e-05)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (8e-05)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0001)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00012)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00014)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00016)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.00018)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
Heccer (dTime) : (0.0002)
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
00005 :: 3			HECCER_COP_FINISH_ROW
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
			       {
				arguments => [
					     ],
				command => 'tests/code/tensizesp',
				command_tests => [
						  {
						   description => "Are ten passive compartments with different properties and injected current solved correctly ?",
						   read => [ 'Initiated
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dTime) : (0)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (10)
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
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (9.95267e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (1.10708e+06)
Compartment (dRm) : (4.9434e+09)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.04817e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (306647)
Compartment (dRm) : (1.61408e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (3)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.8668e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (147150)
Compartment (dRm) : (2.63553e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (4)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.81543e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (335502)
Compartment (dRm) : (1.2895e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (5)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (2.23945e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (230129)
Compartment (dRm) : (2.19696e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (6)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.75406e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (169782)
Compartment (dRm) : (2.80492e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (7)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.37097e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (442254)
Compartment (dRm) : (1.45952e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (8)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.04851e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (518791)
Compartment (dRm) : (9.74544e+09)
MinimumDegree (iEntries) : (10)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (1)
MinimumDegree (piChildren[3][0]) : (4)
MinimumDegree (piChildren[4]) : (1)
MinimumDegree (piChildren[4][0]) : (5)
MinimumDegree (piChildren[5]) : (1)
MinimumDegree (piChildren[5][0]) : (6)
MinimumDegree (piChildren[6]) : (1)
MinimumDegree (piChildren[6][0]) : (7)
MinimumDegree (piChildren[7]) : (1)
MinimumDegree (piChildren[7][0]) : (8)
MinimumDegree (piChildren[8]) : (1)
MinimumDegree (piChildren[8][0]) : (9)
MinimumDegree (piChildren[9]) : (0)
MinimumDegree (piForward[0]) : (9)
MinimumDegree (piForward[1]) : (8)
MinimumDegree (piForward[2]) : (7)
MinimumDegree (piForward[3]) : (6)
MinimumDegree (piForward[4]) : (5)
MinimumDegree (piForward[5]) : (4)
MinimumDegree (piForward[6]) : (3)
MinimumDegree (piForward[7]) : (2)
MinimumDegree (piForward[8]) : (1)
MinimumDegree (piForward[9]) : (0)
MinimumDegree (piBackward[0]) : (9)
MinimumDegree (piBackward[1]) : (8)
MinimumDegree (piBackward[2]) : (7)
MinimumDegree (piBackward[3]) : (6)
MinimumDegree (piBackward[4]) : (5)
MinimumDegree (piBackward[5]) : (4)
MinimumDegree (piBackward[6]) : (3)
MinimumDegree (piBackward[7]) : (2)
MinimumDegree (piBackward[8]) : (1)
MinimumDegree (piBackward[9]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 5			HECCER_COP_SET_DIAGONAL
00006 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00008 :: 5			HECCER_COP_SET_DIAGONAL
00009 :: 1    6		HECCER_COP_FORWARD_ELIMINATION    6
00011 :: 5			HECCER_COP_SET_DIAGONAL
00012 :: 1    8		HECCER_COP_FORWARD_ELIMINATION    8
00014 :: 5			HECCER_COP_SET_DIAGONAL
00015 :: 1   10		HECCER_COP_FORWARD_ELIMINATION   10
00017 :: 5			HECCER_COP_SET_DIAGONAL
00018 :: 1   12		HECCER_COP_FORWARD_ELIMINATION   12
00020 :: 5			HECCER_COP_SET_DIAGONAL
00021 :: 1   14		HECCER_COP_FORWARD_ELIMINATION   14
00023 :: 5			HECCER_COP_SET_DIAGONAL
00024 :: 1   16		HECCER_COP_FORWARD_ELIMINATION   16
00026 :: 4			HECCER_COP_FINISH
00027 :: 2   18		HECCER_COP_BACKWARD_SUBSTITUTION   18
00029 :: 3			HECCER_COP_FINISH_ROW
00030 :: 2   16		HECCER_COP_BACKWARD_SUBSTITUTION   16
00032 :: 3			HECCER_COP_FINISH_ROW
00033 :: 2   14		HECCER_COP_BACKWARD_SUBSTITUTION   14
00035 :: 3			HECCER_COP_FINISH_ROW
00036 :: 2   12		HECCER_COP_BACKWARD_SUBSTITUTION   12
00038 :: 3			HECCER_COP_FINISH_ROW
00039 :: 2   10		HECCER_COP_BACKWARD_SUBSTITUTION   10
00041 :: 3			HECCER_COP_FINISH_ROW
00042 :: 2    8		HECCER_COP_BACKWARD_SUBSTITUTION    8
00044 :: 3			HECCER_COP_FINISH_ROW
00045 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00047 :: 3			HECCER_COP_FINISH_ROW
00048 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00050 :: 3			HECCER_COP_FINISH_ROW
00051 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00053 :: 3			HECCER_COP_FINISH_ROW
00054 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 1			HECCER_MOP_COMPARTMENT
00005 :: 1			HECCER_MOP_COMPARTMENT
00006 :: 1			HECCER_MOP_COMPARTMENT
00007 :: 1			HECCER_MOP_COMPARTMENT
00008 :: 1			HECCER_MOP_COMPARTMENT
00009 :: 1			HECCER_MOP_COMPARTMENT
00010 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (4.81827)
VM Diagonals (pdDiagonals[1]) : (13.426)
VM Diagonals (pdDiagonals[2]) : (47.4699)
VM Diagonals (pdDiagonals[3]) : (46.7046)
VM Diagonals (pdDiagonals[4]) : (20.2012)
VM Diagonals (pdDiagonals[5]) : (53.3701)
VM Diagonals (pdDiagonals[6]) : (33.9933)
VM Diagonals (pdDiagonals[7]) : (5.18436)
VM Diagonals (pdDiagonals[8]) : (4.81797)
VM Diagonals (pdDiagonals[9]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-5.71812)
VM Axial Resistances (pdAxres[1]) : (-3.81807)
VM Axial Resistances (pdAxres[2]) : (-12.8909)
VM Axial Resistances (pdAxres[3]) : (-6.7077)
VM Axial Resistances (pdAxres[4]) : (-26.3007)
VM Axial Resistances (pdAxres[5]) : (-33.5787)
VM Axial Resistances (pdAxres[6]) : (-11.389)
VM Axial Resistances (pdAxres[7]) : (-19.4038)
VM Axial Resistances (pdAxres[8]) : (-15.9664)
VM Axial Resistances (pdAxres[9]) : (-7.81198)
VM Axial Resistances (pdAxres[10]) : (-22.2946)
VM Axial Resistances (pdAxres[11]) : (-36.4034)
VM Axial Resistances (pdAxres[12]) : (-3.27659)
VM Axial Resistances (pdAxres[13]) : (-10.6985)
VM Axial Resistances (pdAxres[14]) : (-1.56946)
VM Axial Resistances (pdAxres[15]) : (-0.90757)
VM Axial Resistances (pdAxres[16]) : (-0.282813)
VM Axial Resistances (pdAxres[17]) : (-2.2483)
VM Axial Resistances (pdAxres[18]) : (-2.2483)
VM Axial Resistances (pdAxres[19]) : (-0.90757)
VM Axial Resistances (pdAxres[20]) : (-10.6985)
VM Axial Resistances (pdAxres[21]) : (-36.4034)
VM Axial Resistances (pdAxres[22]) : (-7.81198)
VM Axial Resistances (pdAxres[23]) : (-19.4038)
VM Axial Resistances (pdAxres[24]) : (-33.5787)
VM Axial Resistances (pdAxres[25]) : (-6.7077)
VM Axial Resistances (pdAxres[26]) : (-3.81807)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Axial Resistances (pdResults[2]) : (0)
VM Axial Resistances (pdResults[3]) : (0)
VM Axial Resistances (pdResults[4]) : (0)
VM Axial Resistances (pdResults[5]) : (0)
VM Axial Resistances (pdResults[6]) : (0)
VM Axial Resistances (pdResults[7]) : (0)
VM Axial Resistances (pdResults[8]) : (0)
VM Axial Resistances (pdResults[9]) : (0)
VM Axial Resistances (pdResults[10]) : (0)
VM Axial Resistances (pdResults[11]) : (0)
VM Axial Resistances (pdResults[12]) : (0)
VM Axial Resistances (pdResults[13]) : (0)
VM Axial Resistances (pdResults[14]) : (0)
VM Axial Resistances (pdResults[15]) : (0)
VM Axial Resistances (pdResults[16]) : (0)
VM Axial Resistances (pdResults[17]) : (0)
VM Axial Resistances (pdResults[18]) : (0)
VM Axial Resistances (pdResults[19]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.068)
VM Membrane Potentials (pdVms[1]) : (-0.068)
VM Membrane Potentials (pdVms[2]) : (-0.068)
VM Membrane Potentials (pdVms[3]) : (-0.068)
VM Membrane Potentials (pdVms[4]) : (-0.068)
VM Membrane Potentials (pdVms[5]) : (-0.068)
VM Membrane Potentials (pdVms[6]) : (-0.068)
VM Membrane Potentials (pdVms[7]) : (-0.068)
VM Membrane Potentials (pdVms[8]) : (-0.068)
VM Membrane Potentials (pdVms[9]) : (-0.068)
-------
Iteration 0
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dTime) : (2e-05)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (10)
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
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (9.95267e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (1.10708e+06)
Compartment (dRm) : (4.9434e+09)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.04817e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (306647)
Compartment (dRm) : (1.61408e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (3)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.8668e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (147150)
Compartment (dRm) : (2.63553e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (4)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.81543e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (335502)
Compartment (dRm) : (1.2895e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (5)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (2.23945e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (230129)
Compartment (dRm) : (2.19696e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (6)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.75406e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (169782)
Compartment (dRm) : (2.80492e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (7)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.37097e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (442254)
Compartment (dRm) : (1.45952e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (8)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.04851e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (518791)
Compartment (dRm) : (9.74544e+09)
MinimumDegree (iEntries) : (10)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (1)
MinimumDegree (piChildren[3][0]) : (4)
MinimumDegree (piChildren[4]) : (1)
MinimumDegree (piChildren[4][0]) : (5)
MinimumDegree (piChildren[5]) : (1)
MinimumDegree (piChildren[5][0]) : (6)
MinimumDegree (piChildren[6]) : (1)
MinimumDegree (piChildren[6][0]) : (7)
MinimumDegree (piChildren[7]) : (1)
MinimumDegree (piChildren[7][0]) : (8)
MinimumDegree (piChildren[8]) : (1)
MinimumDegree (piChildren[8][0]) : (9)
MinimumDegree (piChildren[9]) : (0)
MinimumDegree (piForward[0]) : (9)
MinimumDegree (piForward[1]) : (8)
MinimumDegree (piForward[2]) : (7)
MinimumDegree (piForward[3]) : (6)
MinimumDegree (piForward[4]) : (5)
MinimumDegree (piForward[5]) : (4)
MinimumDegree (piForward[6]) : (3)
MinimumDegree (piForward[7]) : (2)
MinimumDegree (piForward[8]) : (1)
MinimumDegree (piForward[9]) : (0)
MinimumDegree (piBackward[0]) : (9)
MinimumDegree (piBackward[1]) : (8)
MinimumDegree (piBackward[2]) : (7)
MinimumDegree (piBackward[3]) : (6)
MinimumDegree (piBackward[4]) : (5)
MinimumDegree (piBackward[5]) : (4)
MinimumDegree (piBackward[6]) : (3)
MinimumDegree (piBackward[7]) : (2)
MinimumDegree (piBackward[8]) : (1)
MinimumDegree (piBackward[9]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 5			HECCER_COP_SET_DIAGONAL
00006 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00008 :: 5			HECCER_COP_SET_DIAGONAL
00009 :: 1    6		HECCER_COP_FORWARD_ELIMINATION    6
00011 :: 5			HECCER_COP_SET_DIAGONAL
00012 :: 1    8		HECCER_COP_FORWARD_ELIMINATION    8
00014 :: 5			HECCER_COP_SET_DIAGONAL
00015 :: 1   10		HECCER_COP_FORWARD_ELIMINATION   10
00017 :: 5			HECCER_COP_SET_DIAGONAL
00018 :: 1   12		HECCER_COP_FORWARD_ELIMINATION   12
00020 :: 5			HECCER_COP_SET_DIAGONAL
00021 :: 1   14		HECCER_COP_FORWARD_ELIMINATION   14
00023 :: 5			HECCER_COP_SET_DIAGONAL
00024 :: 1   16		HECCER_COP_FORWARD_ELIMINATION   16
00026 :: 4			HECCER_COP_FINISH
00027 :: 2   18		HECCER_COP_BACKWARD_SUBSTITUTION   18
00029 :: 3			HECCER_COP_FINISH_ROW
00030 :: 2   16		HECCER_COP_BACKWARD_SUBSTITUTION   16
00032 :: 3			HECCER_COP_FINISH_ROW
00033 :: 2   14		HECCER_COP_BACKWARD_SUBSTITUTION   14
00035 :: 3			HECCER_COP_FINISH_ROW
00036 :: 2   12		HECCER_COP_BACKWARD_SUBSTITUTION   12
00038 :: 3			HECCER_COP_FINISH_ROW
00039 :: 2   10		HECCER_COP_BACKWARD_SUBSTITUTION   10
00041 :: 3			HECCER_COP_FINISH_ROW
00042 :: 2    8		HECCER_COP_BACKWARD_SUBSTITUTION    8
00044 :: 3			HECCER_COP_FINISH_ROW
00045 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00047 :: 3			HECCER_COP_FINISH_ROW
00048 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00050 :: 3			HECCER_COP_FINISH_ROW
00051 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00053 :: 3			HECCER_COP_FINISH_ROW
00054 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 1			HECCER_MOP_COMPARTMENT
00005 :: 1			HECCER_MOP_COMPARTMENT
00006 :: 1			HECCER_MOP_COMPARTMENT
00007 :: 1			HECCER_MOP_COMPARTMENT
00008 :: 1			HECCER_MOP_COMPARTMENT
00009 :: 1			HECCER_MOP_COMPARTMENT
00010 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (4.81827)
VM Diagonals (pdDiagonals[1]) : (13.426)
VM Diagonals (pdDiagonals[2]) : (47.4699)
VM Diagonals (pdDiagonals[3]) : (46.7046)
VM Diagonals (pdDiagonals[4]) : (20.2012)
VM Diagonals (pdDiagonals[5]) : (53.3701)
VM Diagonals (pdDiagonals[6]) : (33.9933)
VM Diagonals (pdDiagonals[7]) : (5.18436)
VM Diagonals (pdDiagonals[8]) : (4.81797)
VM Diagonals (pdDiagonals[9]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-5.71812)
VM Axial Resistances (pdAxres[1]) : (-3.81807)
VM Axial Resistances (pdAxres[2]) : (-12.8909)
VM Axial Resistances (pdAxres[3]) : (-6.7077)
VM Axial Resistances (pdAxres[4]) : (-26.3007)
VM Axial Resistances (pdAxres[5]) : (-33.5787)
VM Axial Resistances (pdAxres[6]) : (-11.389)
VM Axial Resistances (pdAxres[7]) : (-19.4038)
VM Axial Resistances (pdAxres[8]) : (-15.9664)
VM Axial Resistances (pdAxres[9]) : (-7.81198)
VM Axial Resistances (pdAxres[10]) : (-22.2946)
VM Axial Resistances (pdAxres[11]) : (-36.4034)
VM Axial Resistances (pdAxres[12]) : (-3.27659)
VM Axial Resistances (pdAxres[13]) : (-10.6985)
VM Axial Resistances (pdAxres[14]) : (-1.56946)
VM Axial Resistances (pdAxres[15]) : (-0.90757)
VM Axial Resistances (pdAxres[16]) : (-0.282813)
VM Axial Resistances (pdAxres[17]) : (-2.2483)
VM Axial Resistances (pdAxres[18]) : (-2.2483)
VM Axial Resistances (pdAxres[19]) : (-0.90757)
VM Axial Resistances (pdAxres[20]) : (-10.6985)
VM Axial Resistances (pdAxres[21]) : (-36.4034)
VM Axial Resistances (pdAxres[22]) : (-7.81198)
VM Axial Resistances (pdAxres[23]) : (-19.4038)
VM Axial Resistances (pdAxres[24]) : (-33.5787)
VM Axial Resistances (pdAxres[25]) : (-6.7077)
VM Axial Resistances (pdAxres[26]) : (-3.81807)
VM Axial Resistances (pdResults[0]) : (-0.0679279)
VM Axial Resistances (pdResults[1]) : (4.81827)
VM Axial Resistances (pdResults[2]) : (-0.0679126)
VM Axial Resistances (pdResults[3]) : (8.8949)
VM Axial Resistances (pdResults[4]) : (-0.0678861)
VM Axial Resistances (pdResults[5]) : (37.7487)
VM Axial Resistances (pdResults[6]) : (-0.0678725)
VM Axial Resistances (pdResults[7]) : (23.3094)
VM Axial Resistances (pdResults[8]) : (-0.0678473)
VM Axial Resistances (pdResults[9]) : (10.7204)
VM Axial Resistances (pdResults[10]) : (-0.0677908)
VM Axial Resistances (pdResults[11]) : (41.7354)
VM Axial Resistances (pdResults[12]) : (-0.0677602)
VM Axial Resistances (pdResults[13]) : (14.5469)
VM Axial Resistances (pdResults[14]) : (-0.0676737)
VM Axial Resistances (pdResults[15]) : (2.77461)
VM Axial Resistances (pdResults[16]) : (-0.0669993)
VM Axial Resistances (pdResults[17]) : (4.3046)
VM Axial Resistances (pdResults[18]) : (-0.0660822)
VM Axial Resistances (pdResults[19]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0678558)
VM Membrane Potentials (pdVms[1]) : (-0.0678252)
VM Membrane Potentials (pdVms[2]) : (-0.0677722)
VM Membrane Potentials (pdVms[3]) : (-0.067745)
VM Membrane Potentials (pdVms[4]) : (-0.0676946)
VM Membrane Potentials (pdVms[5]) : (-0.0675815)
VM Membrane Potentials (pdVms[6]) : (-0.0675203)
VM Membrane Potentials (pdVms[7]) : (-0.0673474)
VM Membrane Potentials (pdVms[8]) : (-0.0659986)
VM Membrane Potentials (pdVms[9]) : (-0.0641645)
-------
Iteration 1
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dTime) : (4e-05)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (10)
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
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (9.95267e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (1.10708e+06)
Compartment (dRm) : (4.9434e+09)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.04817e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (306647)
Compartment (dRm) : (1.61408e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (3)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.8668e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (147150)
Compartment (dRm) : (2.63553e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (4)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.81543e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (335502)
Compartment (dRm) : (1.2895e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (5)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (2.23945e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (230129)
Compartment (dRm) : (2.19696e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (6)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.75406e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (169782)
Compartment (dRm) : (2.80492e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (7)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.37097e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (442254)
Compartment (dRm) : (1.45952e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (8)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.04851e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (518791)
Compartment (dRm) : (9.74544e+09)
MinimumDegree (iEntries) : (10)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (1)
MinimumDegree (piChildren[3][0]) : (4)
MinimumDegree (piChildren[4]) : (1)
MinimumDegree (piChildren[4][0]) : (5)
MinimumDegree (piChildren[5]) : (1)
MinimumDegree (piChildren[5][0]) : (6)
MinimumDegree (piChildren[6]) : (1)
MinimumDegree (piChildren[6][0]) : (7)
MinimumDegree (piChildren[7]) : (1)
MinimumDegree (piChildren[7][0]) : (8)
MinimumDegree (piChildren[8]) : (1)
MinimumDegree (piChildren[8][0]) : (9)
MinimumDegree (piChildren[9]) : (0)
MinimumDegree (piForward[0]) : (9)
MinimumDegree (piForward[1]) : (8)
MinimumDegree (piForward[2]) : (7)
MinimumDegree (piForward[3]) : (6)
MinimumDegree (piForward[4]) : (5)
MinimumDegree (piForward[5]) : (4)
MinimumDegree (piForward[6]) : (3)
MinimumDegree (piForward[7]) : (2)
MinimumDegree (piForward[8]) : (1)
MinimumDegree (piForward[9]) : (0)
MinimumDegree (piBackward[0]) : (9)
MinimumDegree (piBackward[1]) : (8)
MinimumDegree (piBackward[2]) : (7)
MinimumDegree (piBackward[3]) : (6)
MinimumDegree (piBackward[4]) : (5)
MinimumDegree (piBackward[5]) : (4)
MinimumDegree (piBackward[6]) : (3)
MinimumDegree (piBackward[7]) : (2)
MinimumDegree (piBackward[8]) : (1)
MinimumDegree (piBackward[9]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 5			HECCER_COP_SET_DIAGONAL
00006 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00008 :: 5			HECCER_COP_SET_DIAGONAL
00009 :: 1    6		HECCER_COP_FORWARD_ELIMINATION    6
00011 :: 5			HECCER_COP_SET_DIAGONAL
00012 :: 1    8		HECCER_COP_FORWARD_ELIMINATION    8
00014 :: 5			HECCER_COP_SET_DIAGONAL
00015 :: 1   10		HECCER_COP_FORWARD_ELIMINATION   10
00017 :: 5			HECCER_COP_SET_DIAGONAL
00018 :: 1   12		HECCER_COP_FORWARD_ELIMINATION   12
00020 :: 5			HECCER_COP_SET_DIAGONAL
00021 :: 1   14		HECCER_COP_FORWARD_ELIMINATION   14
00023 :: 5			HECCER_COP_SET_DIAGONAL
00024 :: 1   16		HECCER_COP_FORWARD_ELIMINATION   16
00026 :: 4			HECCER_COP_FINISH
00027 :: 2   18		HECCER_COP_BACKWARD_SUBSTITUTION   18
00029 :: 3			HECCER_COP_FINISH_ROW
00030 :: 2   16		HECCER_COP_BACKWARD_SUBSTITUTION   16
00032 :: 3			HECCER_COP_FINISH_ROW
00033 :: 2   14		HECCER_COP_BACKWARD_SUBSTITUTION   14
00035 :: 3			HECCER_COP_FINISH_ROW
00036 :: 2   12		HECCER_COP_BACKWARD_SUBSTITUTION   12
00038 :: 3			HECCER_COP_FINISH_ROW
00039 :: 2   10		HECCER_COP_BACKWARD_SUBSTITUTION   10
00041 :: 3			HECCER_COP_FINISH_ROW
00042 :: 2    8		HECCER_COP_BACKWARD_SUBSTITUTION    8
00044 :: 3			HECCER_COP_FINISH_ROW
00045 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00047 :: 3			HECCER_COP_FINISH_ROW
00048 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00050 :: 3			HECCER_COP_FINISH_ROW
00051 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00053 :: 3			HECCER_COP_FINISH_ROW
00054 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 1			HECCER_MOP_COMPARTMENT
00005 :: 1			HECCER_MOP_COMPARTMENT
00006 :: 1			HECCER_MOP_COMPARTMENT
00007 :: 1			HECCER_MOP_COMPARTMENT
00008 :: 1			HECCER_MOP_COMPARTMENT
00009 :: 1			HECCER_MOP_COMPARTMENT
00010 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (4.81827)
VM Diagonals (pdDiagonals[1]) : (13.426)
VM Diagonals (pdDiagonals[2]) : (47.4699)
VM Diagonals (pdDiagonals[3]) : (46.7046)
VM Diagonals (pdDiagonals[4]) : (20.2012)
VM Diagonals (pdDiagonals[5]) : (53.3701)
VM Diagonals (pdDiagonals[6]) : (33.9933)
VM Diagonals (pdDiagonals[7]) : (5.18436)
VM Diagonals (pdDiagonals[8]) : (4.81797)
VM Diagonals (pdDiagonals[9]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-5.71812)
VM Axial Resistances (pdAxres[1]) : (-3.81807)
VM Axial Resistances (pdAxres[2]) : (-12.8909)
VM Axial Resistances (pdAxres[3]) : (-6.7077)
VM Axial Resistances (pdAxres[4]) : (-26.3007)
VM Axial Resistances (pdAxres[5]) : (-33.5787)
VM Axial Resistances (pdAxres[6]) : (-11.389)
VM Axial Resistances (pdAxres[7]) : (-19.4038)
VM Axial Resistances (pdAxres[8]) : (-15.9664)
VM Axial Resistances (pdAxres[9]) : (-7.81198)
VM Axial Resistances (pdAxres[10]) : (-22.2946)
VM Axial Resistances (pdAxres[11]) : (-36.4034)
VM Axial Resistances (pdAxres[12]) : (-3.27659)
VM Axial Resistances (pdAxres[13]) : (-10.6985)
VM Axial Resistances (pdAxres[14]) : (-1.56946)
VM Axial Resistances (pdAxres[15]) : (-0.90757)
VM Axial Resistances (pdAxres[16]) : (-0.282813)
VM Axial Resistances (pdAxres[17]) : (-2.2483)
VM Axial Resistances (pdAxres[18]) : (-2.2483)
VM Axial Resistances (pdAxres[19]) : (-0.90757)
VM Axial Resistances (pdAxres[20]) : (-10.6985)
VM Axial Resistances (pdAxres[21]) : (-36.4034)
VM Axial Resistances (pdAxres[22]) : (-7.81198)
VM Axial Resistances (pdAxres[23]) : (-19.4038)
VM Axial Resistances (pdAxres[24]) : (-33.5787)
VM Axial Resistances (pdAxres[25]) : (-6.7077)
VM Axial Resistances (pdAxres[26]) : (-3.81807)
VM Axial Resistances (pdResults[0]) : (-0.0675414)
VM Axial Resistances (pdResults[1]) : (4.81827)
VM Axial Resistances (pdResults[2]) : (-0.0674626)
VM Axial Resistances (pdResults[3]) : (8.8949)
VM Axial Resistances (pdResults[4]) : (-0.0673409)
VM Axial Resistances (pdResults[5]) : (37.7487)
VM Axial Resistances (pdResults[6]) : (-0.0672813)
VM Axial Resistances (pdResults[7]) : (23.3094)
VM Axial Resistances (pdResults[8]) : (-0.0671765)
VM Axial Resistances (pdResults[9]) : (10.7204)
VM Axial Resistances (pdResults[10]) : (-0.066957)
VM Axial Resistances (pdResults[11]) : (41.7354)
VM Axial Resistances (pdResults[12]) : (-0.0668435)
VM Axial Resistances (pdResults[13]) : (14.5469)
VM Axial Resistances (pdResults[14]) : (-0.0665435)
VM Axial Resistances (pdResults[15]) : (2.77461)
VM Axial Resistances (pdResults[16]) : (-0.0645714)
VM Axial Resistances (pdResults[17]) : (4.3046)
VM Axial Resistances (pdResults[18]) : (-0.0625587)
VM Axial Resistances (pdResults[19]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0672269)
VM Membrane Potentials (pdVms[1]) : (-0.0671)
VM Membrane Potentials (pdVms[2]) : (-0.0669096)
VM Membrane Potentials (pdVms[3]) : (-0.0668177)
VM Membrane Potentials (pdVms[4]) : (-0.0666583)
VM Membrane Potentials (pdVms[5]) : (-0.0663324)
VM Membrane Potentials (pdVms[6]) : (-0.0661667)
VM Membrane Potentials (pdVms[7]) : (-0.0657395)
VM Membrane Potentials (pdVms[8]) : (-0.0631443)
VM Membrane Potentials (pdVms[9]) : (-0.060953)
-------
Iteration 2
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dTime) : (6e-05)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (10)
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
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (9.95267e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (1.10708e+06)
Compartment (dRm) : (4.9434e+09)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.04817e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (306647)
Compartment (dRm) : (1.61408e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (3)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.8668e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (147150)
Compartment (dRm) : (2.63553e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (4)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.81543e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (335502)
Compartment (dRm) : (1.2895e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (5)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (2.23945e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (230129)
Compartment (dRm) : (2.19696e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (6)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.75406e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (169782)
Compartment (dRm) : (2.80492e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (7)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.37097e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (442254)
Compartment (dRm) : (1.45952e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (8)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.04851e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (518791)
Compartment (dRm) : (9.74544e+09)
MinimumDegree (iEntries) : (10)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (1)
MinimumDegree (piChildren[3][0]) : (4)
MinimumDegree (piChildren[4]) : (1)
MinimumDegree (piChildren[4][0]) : (5)
MinimumDegree (piChildren[5]) : (1)
MinimumDegree (piChildren[5][0]) : (6)
MinimumDegree (piChildren[6]) : (1)
MinimumDegree (piChildren[6][0]) : (7)
MinimumDegree (piChildren[7]) : (1)
MinimumDegree (piChildren[7][0]) : (8)
MinimumDegree (piChildren[8]) : (1)
MinimumDegree (piChildren[8][0]) : (9)
MinimumDegree (piChildren[9]) : (0)
MinimumDegree (piForward[0]) : (9)
MinimumDegree (piForward[1]) : (8)
MinimumDegree (piForward[2]) : (7)
MinimumDegree (piForward[3]) : (6)
MinimumDegree (piForward[4]) : (5)
MinimumDegree (piForward[5]) : (4)
MinimumDegree (piForward[6]) : (3)
MinimumDegree (piForward[7]) : (2)
MinimumDegree (piForward[8]) : (1)
MinimumDegree (piForward[9]) : (0)
MinimumDegree (piBackward[0]) : (9)
MinimumDegree (piBackward[1]) : (8)
MinimumDegree (piBackward[2]) : (7)
MinimumDegree (piBackward[3]) : (6)
MinimumDegree (piBackward[4]) : (5)
MinimumDegree (piBackward[5]) : (4)
MinimumDegree (piBackward[6]) : (3)
MinimumDegree (piBackward[7]) : (2)
MinimumDegree (piBackward[8]) : (1)
MinimumDegree (piBackward[9]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 5			HECCER_COP_SET_DIAGONAL
00006 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00008 :: 5			HECCER_COP_SET_DIAGONAL
00009 :: 1    6		HECCER_COP_FORWARD_ELIMINATION    6
00011 :: 5			HECCER_COP_SET_DIAGONAL
00012 :: 1    8		HECCER_COP_FORWARD_ELIMINATION    8
00014 :: 5			HECCER_COP_SET_DIAGONAL
00015 :: 1   10		HECCER_COP_FORWARD_ELIMINATION   10
00017 :: 5			HECCER_COP_SET_DIAGONAL
00018 :: 1   12		HECCER_COP_FORWARD_ELIMINATION   12
00020 :: 5			HECCER_COP_SET_DIAGONAL
00021 :: 1   14		HECCER_COP_FORWARD_ELIMINATION   14
00023 :: 5			HECCER_COP_SET_DIAGONAL
00024 :: 1   16		HECCER_COP_FORWARD_ELIMINATION   16
00026 :: 4			HECCER_COP_FINISH
00027 :: 2   18		HECCER_COP_BACKWARD_SUBSTITUTION   18
00029 :: 3			HECCER_COP_FINISH_ROW
00030 :: 2   16		HECCER_COP_BACKWARD_SUBSTITUTION   16
00032 :: 3			HECCER_COP_FINISH_ROW
00033 :: 2   14		HECCER_COP_BACKWARD_SUBSTITUTION   14
00035 :: 3			HECCER_COP_FINISH_ROW
00036 :: 2   12		HECCER_COP_BACKWARD_SUBSTITUTION   12
00038 :: 3			HECCER_COP_FINISH_ROW
00039 :: 2   10		HECCER_COP_BACKWARD_SUBSTITUTION   10
00041 :: 3			HECCER_COP_FINISH_ROW
00042 :: 2    8		HECCER_COP_BACKWARD_SUBSTITUTION    8
00044 :: 3			HECCER_COP_FINISH_ROW
00045 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00047 :: 3			HECCER_COP_FINISH_ROW
00048 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00050 :: 3			HECCER_COP_FINISH_ROW
00051 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00053 :: 3			HECCER_COP_FINISH_ROW
00054 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 1			HECCER_MOP_COMPARTMENT
00005 :: 1			HECCER_MOP_COMPARTMENT
00006 :: 1			HECCER_MOP_COMPARTMENT
00007 :: 1			HECCER_MOP_COMPARTMENT
00008 :: 1			HECCER_MOP_COMPARTMENT
00009 :: 1			HECCER_MOP_COMPARTMENT
00010 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (4.81827)
VM Diagonals (pdDiagonals[1]) : (13.426)
VM Diagonals (pdDiagonals[2]) : (47.4699)
VM Diagonals (pdDiagonals[3]) : (46.7046)
VM Diagonals (pdDiagonals[4]) : (20.2012)
VM Diagonals (pdDiagonals[5]) : (53.3701)
VM Diagonals (pdDiagonals[6]) : (33.9933)
VM Diagonals (pdDiagonals[7]) : (5.18436)
VM Diagonals (pdDiagonals[8]) : (4.81797)
VM Diagonals (pdDiagonals[9]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-5.71812)
VM Axial Resistances (pdAxres[1]) : (-3.81807)
VM Axial Resistances (pdAxres[2]) : (-12.8909)
VM Axial Resistances (pdAxres[3]) : (-6.7077)
VM Axial Resistances (pdAxres[4]) : (-26.3007)
VM Axial Resistances (pdAxres[5]) : (-33.5787)
VM Axial Resistances (pdAxres[6]) : (-11.389)
VM Axial Resistances (pdAxres[7]) : (-19.4038)
VM Axial Resistances (pdAxres[8]) : (-15.9664)
VM Axial Resistances (pdAxres[9]) : (-7.81198)
VM Axial Resistances (pdAxres[10]) : (-22.2946)
VM Axial Resistances (pdAxres[11]) : (-36.4034)
VM Axial Resistances (pdAxres[12]) : (-3.27659)
VM Axial Resistances (pdAxres[13]) : (-10.6985)
VM Axial Resistances (pdAxres[14]) : (-1.56946)
VM Axial Resistances (pdAxres[15]) : (-0.90757)
VM Axial Resistances (pdAxres[16]) : (-0.282813)
VM Axial Resistances (pdAxres[17]) : (-2.2483)
VM Axial Resistances (pdAxres[18]) : (-2.2483)
VM Axial Resistances (pdAxres[19]) : (-0.90757)
VM Axial Resistances (pdAxres[20]) : (-10.6985)
VM Axial Resistances (pdAxres[21]) : (-36.4034)
VM Axial Resistances (pdAxres[22]) : (-7.81198)
VM Axial Resistances (pdAxres[23]) : (-19.4038)
VM Axial Resistances (pdAxres[24]) : (-33.5787)
VM Axial Resistances (pdAxres[25]) : (-6.7077)
VM Axial Resistances (pdAxres[26]) : (-3.81807)
VM Axial Resistances (pdResults[0]) : (-0.0665807)
VM Axial Resistances (pdResults[1]) : (4.81827)
VM Axial Resistances (pdResults[2]) : (-0.0664149)
VM Axial Resistances (pdResults[3]) : (8.8949)
VM Axial Resistances (pdResults[4]) : (-0.066171)
VM Axial Resistances (pdResults[5]) : (37.7487)
VM Axial Resistances (pdResults[6]) : (-0.0660554)
VM Axial Resistances (pdResults[7]) : (23.3094)
VM Axial Resistances (pdResults[8]) : (-0.0658591)
VM Axial Resistances (pdResults[9]) : (10.7204)
VM Axial Resistances (pdResults[10]) : (-0.0654703)
VM Axial Resistances (pdResults[11]) : (41.7354)
VM Axial Resistances (pdResults[12]) : (-0.065276)
VM Axial Resistances (pdResults[13]) : (14.5469)
VM Axial Resistances (pdResults[14]) : (-0.0647876)
VM Axial Resistances (pdResults[15]) : (2.77461)
VM Axial Resistances (pdResults[16]) : (-0.0619721)
VM Axial Resistances (pdResults[17]) : (4.3046)
VM Axial Resistances (pdResults[18]) : (-0.0594836)
VM Axial Resistances (pdResults[19]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0659344)
VM Membrane Potentials (pdVms[1]) : (-0.0657299)
VM Membrane Potentials (pdVms[2]) : (-0.0654325)
VM Membrane Potentials (pdVms[3]) : (-0.065293)
VM Membrane Potentials (pdVms[4]) : (-0.0650599)
VM Membrane Potentials (pdVms[5]) : (-0.0646082)
VM Membrane Potentials (pdVms[6]) : (-0.0643854)
VM Membrane Potentials (pdVms[7]) : (-0.0638357)
VM Membrane Potentials (pdVms[8]) : (-0.0607998)
VM Membrane Potentials (pdVms[9]) : (-0.0580143)
-------
Iteration 3
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dTime) : (8e-05)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (10)
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
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (9.95267e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (1.10708e+06)
Compartment (dRm) : (4.9434e+09)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.04817e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (306647)
Compartment (dRm) : (1.61408e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (3)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.8668e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (147150)
Compartment (dRm) : (2.63553e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (4)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.81543e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (335502)
Compartment (dRm) : (1.2895e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (5)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (2.23945e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (230129)
Compartment (dRm) : (2.19696e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (6)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.75406e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (169782)
Compartment (dRm) : (2.80492e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (7)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.37097e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (442254)
Compartment (dRm) : (1.45952e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (8)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.04851e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (518791)
Compartment (dRm) : (9.74544e+09)
MinimumDegree (iEntries) : (10)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (1)
MinimumDegree (piChildren[3][0]) : (4)
MinimumDegree (piChildren[4]) : (1)
MinimumDegree (piChildren[4][0]) : (5)
MinimumDegree (piChildren[5]) : (1)
MinimumDegree (piChildren[5][0]) : (6)
MinimumDegree (piChildren[6]) : (1)
MinimumDegree (piChildren[6][0]) : (7)
MinimumDegree (piChildren[7]) : (1)
MinimumDegree (piChildren[7][0]) : (8)
MinimumDegree (piChildren[8]) : (1)
MinimumDegree (piChildren[8][0]) : (9)
MinimumDegree (piChildren[9]) : (0)
MinimumDegree (piForward[0]) : (9)
MinimumDegree (piForward[1]) : (8)
MinimumDegree (piForward[2]) : (7)
MinimumDegree (piForward[3]) : (6)
MinimumDegree (piForward[4]) : (5)
MinimumDegree (piForward[5]) : (4)
MinimumDegree (piForward[6]) : (3)
MinimumDegree (piForward[7]) : (2)
MinimumDegree (piForward[8]) : (1)
MinimumDegree (piForward[9]) : (0)
MinimumDegree (piBackward[0]) : (9)
MinimumDegree (piBackward[1]) : (8)
MinimumDegree (piBackward[2]) : (7)
MinimumDegree (piBackward[3]) : (6)
MinimumDegree (piBackward[4]) : (5)
MinimumDegree (piBackward[5]) : (4)
MinimumDegree (piBackward[6]) : (3)
MinimumDegree (piBackward[7]) : (2)
MinimumDegree (piBackward[8]) : (1)
MinimumDegree (piBackward[9]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 5			HECCER_COP_SET_DIAGONAL
00006 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00008 :: 5			HECCER_COP_SET_DIAGONAL
00009 :: 1    6		HECCER_COP_FORWARD_ELIMINATION    6
00011 :: 5			HECCER_COP_SET_DIAGONAL
00012 :: 1    8		HECCER_COP_FORWARD_ELIMINATION    8
00014 :: 5			HECCER_COP_SET_DIAGONAL
00015 :: 1   10		HECCER_COP_FORWARD_ELIMINATION   10
00017 :: 5			HECCER_COP_SET_DIAGONAL
00018 :: 1   12		HECCER_COP_FORWARD_ELIMINATION   12
00020 :: 5			HECCER_COP_SET_DIAGONAL
00021 :: 1   14		HECCER_COP_FORWARD_ELIMINATION   14
00023 :: 5			HECCER_COP_SET_DIAGONAL
00024 :: 1   16		HECCER_COP_FORWARD_ELIMINATION   16
00026 :: 4			HECCER_COP_FINISH
00027 :: 2   18		HECCER_COP_BACKWARD_SUBSTITUTION   18
00029 :: 3			HECCER_COP_FINISH_ROW
00030 :: 2   16		HECCER_COP_BACKWARD_SUBSTITUTION   16
00032 :: 3			HECCER_COP_FINISH_ROW
00033 :: 2   14		HECCER_COP_BACKWARD_SUBSTITUTION   14
00035 :: 3			HECCER_COP_FINISH_ROW
00036 :: 2   12		HECCER_COP_BACKWARD_SUBSTITUTION   12
00038 :: 3			HECCER_COP_FINISH_ROW
00039 :: 2   10		HECCER_COP_BACKWARD_SUBSTITUTION   10
00041 :: 3			HECCER_COP_FINISH_ROW
00042 :: 2    8		HECCER_COP_BACKWARD_SUBSTITUTION    8
00044 :: 3			HECCER_COP_FINISH_ROW
00045 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00047 :: 3			HECCER_COP_FINISH_ROW
00048 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00050 :: 3			HECCER_COP_FINISH_ROW
00051 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00053 :: 3			HECCER_COP_FINISH_ROW
00054 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 1			HECCER_MOP_COMPARTMENT
00005 :: 1			HECCER_MOP_COMPARTMENT
00006 :: 1			HECCER_MOP_COMPARTMENT
00007 :: 1			HECCER_MOP_COMPARTMENT
00008 :: 1			HECCER_MOP_COMPARTMENT
00009 :: 1			HECCER_MOP_COMPARTMENT
00010 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (4.81827)
VM Diagonals (pdDiagonals[1]) : (13.426)
VM Diagonals (pdDiagonals[2]) : (47.4699)
VM Diagonals (pdDiagonals[3]) : (46.7046)
VM Diagonals (pdDiagonals[4]) : (20.2012)
VM Diagonals (pdDiagonals[5]) : (53.3701)
VM Diagonals (pdDiagonals[6]) : (33.9933)
VM Diagonals (pdDiagonals[7]) : (5.18436)
VM Diagonals (pdDiagonals[8]) : (4.81797)
VM Diagonals (pdDiagonals[9]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-5.71812)
VM Axial Resistances (pdAxres[1]) : (-3.81807)
VM Axial Resistances (pdAxres[2]) : (-12.8909)
VM Axial Resistances (pdAxres[3]) : (-6.7077)
VM Axial Resistances (pdAxres[4]) : (-26.3007)
VM Axial Resistances (pdAxres[5]) : (-33.5787)
VM Axial Resistances (pdAxres[6]) : (-11.389)
VM Axial Resistances (pdAxres[7]) : (-19.4038)
VM Axial Resistances (pdAxres[8]) : (-15.9664)
VM Axial Resistances (pdAxres[9]) : (-7.81198)
VM Axial Resistances (pdAxres[10]) : (-22.2946)
VM Axial Resistances (pdAxres[11]) : (-36.4034)
VM Axial Resistances (pdAxres[12]) : (-3.27659)
VM Axial Resistances (pdAxres[13]) : (-10.6985)
VM Axial Resistances (pdAxres[14]) : (-1.56946)
VM Axial Resistances (pdAxres[15]) : (-0.90757)
VM Axial Resistances (pdAxres[16]) : (-0.282813)
VM Axial Resistances (pdAxres[17]) : (-2.2483)
VM Axial Resistances (pdAxres[18]) : (-2.2483)
VM Axial Resistances (pdAxres[19]) : (-0.90757)
VM Axial Resistances (pdAxres[20]) : (-10.6985)
VM Axial Resistances (pdAxres[21]) : (-36.4034)
VM Axial Resistances (pdAxres[22]) : (-7.81198)
VM Axial Resistances (pdAxres[23]) : (-19.4038)
VM Axial Resistances (pdAxres[24]) : (-33.5787)
VM Axial Resistances (pdAxres[25]) : (-6.7077)
VM Axial Resistances (pdAxres[26]) : (-3.81807)
VM Axial Resistances (pdResults[0]) : (-0.0650709)
VM Axial Resistances (pdResults[1]) : (4.81827)
VM Axial Resistances (pdResults[2]) : (-0.0648481)
VM Axial Resistances (pdResults[3]) : (8.8949)
VM Axial Resistances (pdResults[4]) : (-0.0645263)
VM Axial Resistances (pdResults[5]) : (37.7487)
VM Axial Resistances (pdResults[6]) : (-0.0643757)
VM Axial Resistances (pdResults[7]) : (23.3094)
VM Axial Resistances (pdResults[8]) : (-0.0641241)
VM Axial Resistances (pdResults[9]) : (10.7204)
VM Axial Resistances (pdResults[10]) : (-0.063637)
VM Axial Resistances (pdResults[11]) : (41.7354)
VM Axial Resistances (pdResults[12]) : (-0.0633967)
VM Axial Resistances (pdResults[13]) : (14.5469)
VM Axial Resistances (pdResults[14]) : (-0.062803)
VM Axial Resistances (pdResults[15]) : (2.77461)
VM Axial Resistances (pdResults[16]) : (-0.0595181)
VM Axial Resistances (pdResults[17]) : (4.3046)
VM Axial Resistances (pdResults[18]) : (-0.0566531)
VM Axial Resistances (pdResults[19]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0642073)
VM Membrane Potentials (pdVms[1]) : (-0.0639664)
VM Membrane Potentials (pdVms[2]) : (-0.0636201)
VM Membrane Potentials (pdVms[3]) : (-0.0634583)
VM Membrane Potentials (pdVms[4]) : (-0.0631883)
VM Membrane Potentials (pdVms[5]) : (-0.0626659)
VM Membrane Potentials (pdVms[6]) : (-0.062408)
VM Membrane Potentials (pdVms[7]) : (-0.0617704)
VM Membrane Potentials (pdVms[8]) : (-0.0582365)
VM Membrane Potentials (pdVms[9]) : (-0.055292)
-------
Iteration 4
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dTime) : (0.0001)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (10)
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
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (9.95267e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (1.10708e+06)
Compartment (dRm) : (4.9434e+09)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.04817e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (306647)
Compartment (dRm) : (1.61408e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (3)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.8668e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (147150)
Compartment (dRm) : (2.63553e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (4)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.81543e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (335502)
Compartment (dRm) : (1.2895e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (5)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (2.23945e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (230129)
Compartment (dRm) : (2.19696e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (6)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.75406e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (169782)
Compartment (dRm) : (2.80492e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (7)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.37097e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (442254)
Compartment (dRm) : (1.45952e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (8)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.04851e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (518791)
Compartment (dRm) : (9.74544e+09)
MinimumDegree (iEntries) : (10)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (1)
MinimumDegree (piChildren[3][0]) : (4)
MinimumDegree (piChildren[4]) : (1)
MinimumDegree (piChildren[4][0]) : (5)
MinimumDegree (piChildren[5]) : (1)
MinimumDegree (piChildren[5][0]) : (6)
MinimumDegree (piChildren[6]) : (1)
MinimumDegree (piChildren[6][0]) : (7)
MinimumDegree (piChildren[7]) : (1)
MinimumDegree (piChildren[7][0]) : (8)
MinimumDegree (piChildren[8]) : (1)
MinimumDegree (piChildren[8][0]) : (9)
MinimumDegree (piChildren[9]) : (0)
MinimumDegree (piForward[0]) : (9)
MinimumDegree (piForward[1]) : (8)
MinimumDegree (piForward[2]) : (7)
MinimumDegree (piForward[3]) : (6)
MinimumDegree (piForward[4]) : (5)
MinimumDegree (piForward[5]) : (4)
MinimumDegree (piForward[6]) : (3)
MinimumDegree (piForward[7]) : (2)
MinimumDegree (piForward[8]) : (1)
MinimumDegree (piForward[9]) : (0)
MinimumDegree (piBackward[0]) : (9)
MinimumDegree (piBackward[1]) : (8)
MinimumDegree (piBackward[2]) : (7)
MinimumDegree (piBackward[3]) : (6)
MinimumDegree (piBackward[4]) : (5)
MinimumDegree (piBackward[5]) : (4)
MinimumDegree (piBackward[6]) : (3)
MinimumDegree (piBackward[7]) : (2)
MinimumDegree (piBackward[8]) : (1)
MinimumDegree (piBackward[9]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 5			HECCER_COP_SET_DIAGONAL
00006 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00008 :: 5			HECCER_COP_SET_DIAGONAL
00009 :: 1    6		HECCER_COP_FORWARD_ELIMINATION    6
00011 :: 5			HECCER_COP_SET_DIAGONAL
00012 :: 1    8		HECCER_COP_FORWARD_ELIMINATION    8
00014 :: 5			HECCER_COP_SET_DIAGONAL
00015 :: 1   10		HECCER_COP_FORWARD_ELIMINATION   10
00017 :: 5			HECCER_COP_SET_DIAGONAL
00018 :: 1   12		HECCER_COP_FORWARD_ELIMINATION   12
00020 :: 5			HECCER_COP_SET_DIAGONAL
00021 :: 1   14		HECCER_COP_FORWARD_ELIMINATION   14
00023 :: 5			HECCER_COP_SET_DIAGONAL
00024 :: 1   16		HECCER_COP_FORWARD_ELIMINATION   16
00026 :: 4			HECCER_COP_FINISH
00027 :: 2   18		HECCER_COP_BACKWARD_SUBSTITUTION   18
00029 :: 3			HECCER_COP_FINISH_ROW
00030 :: 2   16		HECCER_COP_BACKWARD_SUBSTITUTION   16
00032 :: 3			HECCER_COP_FINISH_ROW
00033 :: 2   14		HECCER_COP_BACKWARD_SUBSTITUTION   14
00035 :: 3			HECCER_COP_FINISH_ROW
00036 :: 2   12		HECCER_COP_BACKWARD_SUBSTITUTION   12
00038 :: 3			HECCER_COP_FINISH_ROW
00039 :: 2   10		HECCER_COP_BACKWARD_SUBSTITUTION   10
00041 :: 3			HECCER_COP_FINISH_ROW
00042 :: 2    8		HECCER_COP_BACKWARD_SUBSTITUTION    8
00044 :: 3			HECCER_COP_FINISH_ROW
00045 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00047 :: 3			HECCER_COP_FINISH_ROW
00048 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00050 :: 3			HECCER_COP_FINISH_ROW
00051 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00053 :: 3			HECCER_COP_FINISH_ROW
00054 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 1			HECCER_MOP_COMPARTMENT
00005 :: 1			HECCER_MOP_COMPARTMENT
00006 :: 1			HECCER_MOP_COMPARTMENT
00007 :: 1			HECCER_MOP_COMPARTMENT
00008 :: 1			HECCER_MOP_COMPARTMENT
00009 :: 1			HECCER_MOP_COMPARTMENT
00010 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (4.81827)
VM Diagonals (pdDiagonals[1]) : (13.426)
VM Diagonals (pdDiagonals[2]) : (47.4699)
VM Diagonals (pdDiagonals[3]) : (46.7046)
VM Diagonals (pdDiagonals[4]) : (20.2012)
VM Diagonals (pdDiagonals[5]) : (53.3701)
VM Diagonals (pdDiagonals[6]) : (33.9933)
VM Diagonals (pdDiagonals[7]) : (5.18436)
VM Diagonals (pdDiagonals[8]) : (4.81797)
VM Diagonals (pdDiagonals[9]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-5.71812)
VM Axial Resistances (pdAxres[1]) : (-3.81807)
VM Axial Resistances (pdAxres[2]) : (-12.8909)
VM Axial Resistances (pdAxres[3]) : (-6.7077)
VM Axial Resistances (pdAxres[4]) : (-26.3007)
VM Axial Resistances (pdAxres[5]) : (-33.5787)
VM Axial Resistances (pdAxres[6]) : (-11.389)
VM Axial Resistances (pdAxres[7]) : (-19.4038)
VM Axial Resistances (pdAxres[8]) : (-15.9664)
VM Axial Resistances (pdAxres[9]) : (-7.81198)
VM Axial Resistances (pdAxres[10]) : (-22.2946)
VM Axial Resistances (pdAxres[11]) : (-36.4034)
VM Axial Resistances (pdAxres[12]) : (-3.27659)
VM Axial Resistances (pdAxres[13]) : (-10.6985)
VM Axial Resistances (pdAxres[14]) : (-1.56946)
VM Axial Resistances (pdAxres[15]) : (-0.90757)
VM Axial Resistances (pdAxres[16]) : (-0.282813)
VM Axial Resistances (pdAxres[17]) : (-2.2483)
VM Axial Resistances (pdAxres[18]) : (-2.2483)
VM Axial Resistances (pdAxres[19]) : (-0.90757)
VM Axial Resistances (pdAxres[20]) : (-10.6985)
VM Axial Resistances (pdAxres[21]) : (-36.4034)
VM Axial Resistances (pdAxres[22]) : (-7.81198)
VM Axial Resistances (pdAxres[23]) : (-19.4038)
VM Axial Resistances (pdAxres[24]) : (-33.5787)
VM Axial Resistances (pdAxres[25]) : (-6.7077)
VM Axial Resistances (pdAxres[26]) : (-3.81807)
VM Axial Resistances (pdResults[0]) : (-0.0632236)
VM Axial Resistances (pdResults[1]) : (4.81827)
VM Axial Resistances (pdResults[2]) : (-0.0629693)
VM Axial Resistances (pdResults[3]) : (8.8949)
VM Axial Resistances (pdResults[4]) : (-0.0626033)
VM Axial Resistances (pdResults[5]) : (37.7487)
VM Axial Resistances (pdResults[6]) : (-0.0624324)
VM Axial Resistances (pdResults[7]) : (23.3094)
VM Axial Resistances (pdResults[8]) : (-0.0621477)
VM Axial Resistances (pdResults[9]) : (10.7204)
VM Axial Resistances (pdResults[10]) : (-0.0615991)
VM Axial Resistances (pdResults[11]) : (41.7354)
VM Axial Resistances (pdResults[12]) : (-0.061329)
VM Axial Resistances (pdResults[13]) : (14.5469)
VM Axial Resistances (pdResults[14]) : (-0.060665)
VM Axial Resistances (pdResults[15]) : (2.77461)
VM Axial Resistances (pdResults[16]) : (-0.0570456)
VM Axial Resistances (pdResults[17]) : (4.3046)
VM Axial Resistances (pdResults[18]) : (-0.0539872)
VM Axial Resistances (pdResults[19]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0622399)
VM Membrane Potentials (pdVms[1]) : (-0.0619722)
VM Membrane Potentials (pdVms[2]) : (-0.0615865)
VM Membrane Potentials (pdVms[3]) : (-0.0614066)
VM Membrane Potentials (pdVms[4]) : (-0.0611072)
VM Membrane Potentials (pdVms[5]) : (-0.0605322)
VM Membrane Potentials (pdVms[6]) : (-0.06025)
VM Membrane Potentials (pdVms[7]) : (-0.0595597)
VM Membrane Potentials (pdVms[8]) : (-0.0558547)
VM Membrane Potentials (pdVms[9]) : (-0.0526824)
-------
Iteration 5
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dTime) : (0.00012)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (10)
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
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (9.95267e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (1.10708e+06)
Compartment (dRm) : (4.9434e+09)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.04817e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (306647)
Compartment (dRm) : (1.61408e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (3)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.8668e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (147150)
Compartment (dRm) : (2.63553e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (4)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.81543e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (335502)
Compartment (dRm) : (1.2895e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (5)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (2.23945e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (230129)
Compartment (dRm) : (2.19696e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (6)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.75406e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (169782)
Compartment (dRm) : (2.80492e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (7)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.37097e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (442254)
Compartment (dRm) : (1.45952e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (8)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.04851e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (518791)
Compartment (dRm) : (9.74544e+09)
MinimumDegree (iEntries) : (10)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (1)
MinimumDegree (piChildren[3][0]) : (4)
MinimumDegree (piChildren[4]) : (1)
MinimumDegree (piChildren[4][0]) : (5)
MinimumDegree (piChildren[5]) : (1)
MinimumDegree (piChildren[5][0]) : (6)
MinimumDegree (piChildren[6]) : (1)
MinimumDegree (piChildren[6][0]) : (7)
MinimumDegree (piChildren[7]) : (1)
MinimumDegree (piChildren[7][0]) : (8)
MinimumDegree (piChildren[8]) : (1)
MinimumDegree (piChildren[8][0]) : (9)
MinimumDegree (piChildren[9]) : (0)
MinimumDegree (piForward[0]) : (9)
MinimumDegree (piForward[1]) : (8)
MinimumDegree (piForward[2]) : (7)
MinimumDegree (piForward[3]) : (6)
MinimumDegree (piForward[4]) : (5)
MinimumDegree (piForward[5]) : (4)
MinimumDegree (piForward[6]) : (3)
MinimumDegree (piForward[7]) : (2)
MinimumDegree (piForward[8]) : (1)
MinimumDegree (piForward[9]) : (0)
MinimumDegree (piBackward[0]) : (9)
MinimumDegree (piBackward[1]) : (8)
MinimumDegree (piBackward[2]) : (7)
MinimumDegree (piBackward[3]) : (6)
MinimumDegree (piBackward[4]) : (5)
MinimumDegree (piBackward[5]) : (4)
MinimumDegree (piBackward[6]) : (3)
MinimumDegree (piBackward[7]) : (2)
MinimumDegree (piBackward[8]) : (1)
MinimumDegree (piBackward[9]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 5			HECCER_COP_SET_DIAGONAL
00006 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00008 :: 5			HECCER_COP_SET_DIAGONAL
00009 :: 1    6		HECCER_COP_FORWARD_ELIMINATION    6
00011 :: 5			HECCER_COP_SET_DIAGONAL
00012 :: 1    8		HECCER_COP_FORWARD_ELIMINATION    8
00014 :: 5			HECCER_COP_SET_DIAGONAL
00015 :: 1   10		HECCER_COP_FORWARD_ELIMINATION   10
00017 :: 5			HECCER_COP_SET_DIAGONAL
00018 :: 1   12		HECCER_COP_FORWARD_ELIMINATION   12
00020 :: 5			HECCER_COP_SET_DIAGONAL
00021 :: 1   14		HECCER_COP_FORWARD_ELIMINATION   14
00023 :: 5			HECCER_COP_SET_DIAGONAL
00024 :: 1   16		HECCER_COP_FORWARD_ELIMINATION   16
00026 :: 4			HECCER_COP_FINISH
00027 :: 2   18		HECCER_COP_BACKWARD_SUBSTITUTION   18
00029 :: 3			HECCER_COP_FINISH_ROW
00030 :: 2   16		HECCER_COP_BACKWARD_SUBSTITUTION   16
00032 :: 3			HECCER_COP_FINISH_ROW
00033 :: 2   14		HECCER_COP_BACKWARD_SUBSTITUTION   14
00035 :: 3			HECCER_COP_FINISH_ROW
00036 :: 2   12		HECCER_COP_BACKWARD_SUBSTITUTION   12
00038 :: 3			HECCER_COP_FINISH_ROW
00039 :: 2   10		HECCER_COP_BACKWARD_SUBSTITUTION   10
00041 :: 3			HECCER_COP_FINISH_ROW
00042 :: 2    8		HECCER_COP_BACKWARD_SUBSTITUTION    8
00044 :: 3			HECCER_COP_FINISH_ROW
00045 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00047 :: 3			HECCER_COP_FINISH_ROW
00048 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00050 :: 3			HECCER_COP_FINISH_ROW
00051 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00053 :: 3			HECCER_COP_FINISH_ROW
00054 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 1			HECCER_MOP_COMPARTMENT
00005 :: 1			HECCER_MOP_COMPARTMENT
00006 :: 1			HECCER_MOP_COMPARTMENT
00007 :: 1			HECCER_MOP_COMPARTMENT
00008 :: 1			HECCER_MOP_COMPARTMENT
00009 :: 1			HECCER_MOP_COMPARTMENT
00010 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (4.81827)
VM Diagonals (pdDiagonals[1]) : (13.426)
VM Diagonals (pdDiagonals[2]) : (47.4699)
VM Diagonals (pdDiagonals[3]) : (46.7046)
VM Diagonals (pdDiagonals[4]) : (20.2012)
VM Diagonals (pdDiagonals[5]) : (53.3701)
VM Diagonals (pdDiagonals[6]) : (33.9933)
VM Diagonals (pdDiagonals[7]) : (5.18436)
VM Diagonals (pdDiagonals[8]) : (4.81797)
VM Diagonals (pdDiagonals[9]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-5.71812)
VM Axial Resistances (pdAxres[1]) : (-3.81807)
VM Axial Resistances (pdAxres[2]) : (-12.8909)
VM Axial Resistances (pdAxres[3]) : (-6.7077)
VM Axial Resistances (pdAxres[4]) : (-26.3007)
VM Axial Resistances (pdAxres[5]) : (-33.5787)
VM Axial Resistances (pdAxres[6]) : (-11.389)
VM Axial Resistances (pdAxres[7]) : (-19.4038)
VM Axial Resistances (pdAxres[8]) : (-15.9664)
VM Axial Resistances (pdAxres[9]) : (-7.81198)
VM Axial Resistances (pdAxres[10]) : (-22.2946)
VM Axial Resistances (pdAxres[11]) : (-36.4034)
VM Axial Resistances (pdAxres[12]) : (-3.27659)
VM Axial Resistances (pdAxres[13]) : (-10.6985)
VM Axial Resistances (pdAxres[14]) : (-1.56946)
VM Axial Resistances (pdAxres[15]) : (-0.90757)
VM Axial Resistances (pdAxres[16]) : (-0.282813)
VM Axial Resistances (pdAxres[17]) : (-2.2483)
VM Axial Resistances (pdAxres[18]) : (-2.2483)
VM Axial Resistances (pdAxres[19]) : (-0.90757)
VM Axial Resistances (pdAxres[20]) : (-10.6985)
VM Axial Resistances (pdAxres[21]) : (-36.4034)
VM Axial Resistances (pdAxres[22]) : (-7.81198)
VM Axial Resistances (pdAxres[23]) : (-19.4038)
VM Axial Resistances (pdAxres[24]) : (-33.5787)
VM Axial Resistances (pdAxres[25]) : (-6.7077)
VM Axial Resistances (pdAxres[26]) : (-3.81807)
VM Axial Resistances (pdResults[0]) : (-0.0611732)
VM Axial Resistances (pdResults[1]) : (4.81827)
VM Axial Resistances (pdResults[2]) : (-0.060897)
VM Axial Resistances (pdResults[3]) : (8.8949)
VM Axial Resistances (pdResults[4]) : (-0.0605007)
VM Axial Resistances (pdResults[5]) : (37.7487)
VM Axial Resistances (pdResults[6]) : (-0.0603161)
VM Axial Resistances (pdResults[7]) : (23.3094)
VM Axial Resistances (pdResults[8]) : (-0.0600095)
VM Axial Resistances (pdResults[9]) : (10.7204)
VM Axial Resistances (pdResults[10]) : (-0.0594214)
VM Axial Resistances (pdResults[11]) : (41.7354)
VM Axial Resistances (pdResults[12]) : (-0.0591329)
VM Axial Resistances (pdResults[13]) : (14.5469)
VM Axial Resistances (pdResults[14]) : (-0.0584267)
VM Axial Resistances (pdResults[15]) : (2.77461)
VM Axial Resistances (pdResults[16]) : (-0.0546243)
VM Axial Resistances (pdResults[17]) : (4.3046)
VM Axial Resistances (pdResults[18]) : (-0.0514203)
VM Axial Resistances (pdResults[19]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0601064)
VM Membrane Potentials (pdVms[1]) : (-0.0598218)
VM Membrane Potentials (pdVms[2]) : (-0.0594149)
VM Membrane Potentials (pdVms[3]) : (-0.0592256)
VM Membrane Potentials (pdVms[4]) : (-0.0589117)
VM Membrane Potentials (pdVms[5]) : (-0.0583106)
VM Membrane Potentials (pdVms[6]) : (-0.0580157)
VM Membrane Potentials (pdVms[7]) : (-0.0572938)
VM Membrane Potentials (pdVms[8]) : (-0.0533938)
VM Membrane Potentials (pdVms[9]) : (-0.0501582)
-------
Iteration 6
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dTime) : (0.00014)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (10)
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
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (9.95267e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (1.10708e+06)
Compartment (dRm) : (4.9434e+09)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.04817e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (306647)
Compartment (dRm) : (1.61408e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (3)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.8668e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (147150)
Compartment (dRm) : (2.63553e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (4)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.81543e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (335502)
Compartment (dRm) : (1.2895e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (5)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (2.23945e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (230129)
Compartment (dRm) : (2.19696e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (6)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.75406e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (169782)
Compartment (dRm) : (2.80492e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (7)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.37097e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (442254)
Compartment (dRm) : (1.45952e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (8)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.04851e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (518791)
Compartment (dRm) : (9.74544e+09)
MinimumDegree (iEntries) : (10)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (1)
MinimumDegree (piChildren[3][0]) : (4)
MinimumDegree (piChildren[4]) : (1)
MinimumDegree (piChildren[4][0]) : (5)
MinimumDegree (piChildren[5]) : (1)
MinimumDegree (piChildren[5][0]) : (6)
MinimumDegree (piChildren[6]) : (1)
MinimumDegree (piChildren[6][0]) : (7)
MinimumDegree (piChildren[7]) : (1)
MinimumDegree (piChildren[7][0]) : (8)
MinimumDegree (piChildren[8]) : (1)
MinimumDegree (piChildren[8][0]) : (9)
MinimumDegree (piChildren[9]) : (0)
MinimumDegree (piForward[0]) : (9)
MinimumDegree (piForward[1]) : (8)
MinimumDegree (piForward[2]) : (7)
MinimumDegree (piForward[3]) : (6)
MinimumDegree (piForward[4]) : (5)
MinimumDegree (piForward[5]) : (4)
MinimumDegree (piForward[6]) : (3)
MinimumDegree (piForward[7]) : (2)
MinimumDegree (piForward[8]) : (1)
MinimumDegree (piForward[9]) : (0)
MinimumDegree (piBackward[0]) : (9)
MinimumDegree (piBackward[1]) : (8)
MinimumDegree (piBackward[2]) : (7)
MinimumDegree (piBackward[3]) : (6)
MinimumDegree (piBackward[4]) : (5)
MinimumDegree (piBackward[5]) : (4)
MinimumDegree (piBackward[6]) : (3)
MinimumDegree (piBackward[7]) : (2)
MinimumDegree (piBackward[8]) : (1)
MinimumDegree (piBackward[9]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 5			HECCER_COP_SET_DIAGONAL
00006 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00008 :: 5			HECCER_COP_SET_DIAGONAL
00009 :: 1    6		HECCER_COP_FORWARD_ELIMINATION    6
00011 :: 5			HECCER_COP_SET_DIAGONAL
00012 :: 1    8		HECCER_COP_FORWARD_ELIMINATION    8
00014 :: 5			HECCER_COP_SET_DIAGONAL
00015 :: 1   10		HECCER_COP_FORWARD_ELIMINATION   10
00017 :: 5			HECCER_COP_SET_DIAGONAL
00018 :: 1   12		HECCER_COP_FORWARD_ELIMINATION   12
00020 :: 5			HECCER_COP_SET_DIAGONAL
00021 :: 1   14		HECCER_COP_FORWARD_ELIMINATION   14
00023 :: 5			HECCER_COP_SET_DIAGONAL
00024 :: 1   16		HECCER_COP_FORWARD_ELIMINATION   16
00026 :: 4			HECCER_COP_FINISH
00027 :: 2   18		HECCER_COP_BACKWARD_SUBSTITUTION   18
00029 :: 3			HECCER_COP_FINISH_ROW
00030 :: 2   16		HECCER_COP_BACKWARD_SUBSTITUTION   16
00032 :: 3			HECCER_COP_FINISH_ROW
00033 :: 2   14		HECCER_COP_BACKWARD_SUBSTITUTION   14
00035 :: 3			HECCER_COP_FINISH_ROW
00036 :: 2   12		HECCER_COP_BACKWARD_SUBSTITUTION   12
00038 :: 3			HECCER_COP_FINISH_ROW
00039 :: 2   10		HECCER_COP_BACKWARD_SUBSTITUTION   10
00041 :: 3			HECCER_COP_FINISH_ROW
00042 :: 2    8		HECCER_COP_BACKWARD_SUBSTITUTION    8
00044 :: 3			HECCER_COP_FINISH_ROW
00045 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00047 :: 3			HECCER_COP_FINISH_ROW
00048 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00050 :: 3			HECCER_COP_FINISH_ROW
00051 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00053 :: 3			HECCER_COP_FINISH_ROW
00054 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 1			HECCER_MOP_COMPARTMENT
00005 :: 1			HECCER_MOP_COMPARTMENT
00006 :: 1			HECCER_MOP_COMPARTMENT
00007 :: 1			HECCER_MOP_COMPARTMENT
00008 :: 1			HECCER_MOP_COMPARTMENT
00009 :: 1			HECCER_MOP_COMPARTMENT
00010 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (4.81827)
VM Diagonals (pdDiagonals[1]) : (13.426)
VM Diagonals (pdDiagonals[2]) : (47.4699)
VM Diagonals (pdDiagonals[3]) : (46.7046)
VM Diagonals (pdDiagonals[4]) : (20.2012)
VM Diagonals (pdDiagonals[5]) : (53.3701)
VM Diagonals (pdDiagonals[6]) : (33.9933)
VM Diagonals (pdDiagonals[7]) : (5.18436)
VM Diagonals (pdDiagonals[8]) : (4.81797)
VM Diagonals (pdDiagonals[9]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-5.71812)
VM Axial Resistances (pdAxres[1]) : (-3.81807)
VM Axial Resistances (pdAxres[2]) : (-12.8909)
VM Axial Resistances (pdAxres[3]) : (-6.7077)
VM Axial Resistances (pdAxres[4]) : (-26.3007)
VM Axial Resistances (pdAxres[5]) : (-33.5787)
VM Axial Resistances (pdAxres[6]) : (-11.389)
VM Axial Resistances (pdAxres[7]) : (-19.4038)
VM Axial Resistances (pdAxres[8]) : (-15.9664)
VM Axial Resistances (pdAxres[9]) : (-7.81198)
VM Axial Resistances (pdAxres[10]) : (-22.2946)
VM Axial Resistances (pdAxres[11]) : (-36.4034)
VM Axial Resistances (pdAxres[12]) : (-3.27659)
VM Axial Resistances (pdAxres[13]) : (-10.6985)
VM Axial Resistances (pdAxres[14]) : (-1.56946)
VM Axial Resistances (pdAxres[15]) : (-0.90757)
VM Axial Resistances (pdAxres[16]) : (-0.282813)
VM Axial Resistances (pdAxres[17]) : (-2.2483)
VM Axial Resistances (pdAxres[18]) : (-2.2483)
VM Axial Resistances (pdAxres[19]) : (-0.90757)
VM Axial Resistances (pdAxres[20]) : (-10.6985)
VM Axial Resistances (pdAxres[21]) : (-36.4034)
VM Axial Resistances (pdAxres[22]) : (-7.81198)
VM Axial Resistances (pdAxres[23]) : (-19.4038)
VM Axial Resistances (pdAxres[24]) : (-33.5787)
VM Axial Resistances (pdAxres[25]) : (-6.7077)
VM Axial Resistances (pdAxres[26]) : (-3.81807)
VM Axial Resistances (pdResults[0]) : (-0.0589912)
VM Axial Resistances (pdResults[1]) : (4.81827)
VM Axial Resistances (pdResults[2]) : (-0.0587022)
VM Axial Resistances (pdResults[3]) : (8.8949)
VM Axial Resistances (pdResults[4]) : (-0.0582882)
VM Axial Resistances (pdResults[5]) : (37.7487)
VM Axial Resistances (pdResults[6]) : (-0.0580956)
VM Axial Resistances (pdResults[7]) : (23.3094)
VM Axial Resistances (pdResults[8]) : (-0.0577761)
VM Axial Resistances (pdResults[9]) : (10.7204)
VM Axial Resistances (pdResults[10]) : (-0.0571644)
VM Axial Resistances (pdResults[11]) : (41.7354)
VM Axial Resistances (pdResults[12]) : (-0.0568644)
VM Axial Resistances (pdResults[13]) : (14.5469)
VM Axial Resistances (pdResults[14]) : (-0.0561313)
VM Axial Resistances (pdResults[15]) : (2.77461)
VM Axial Resistances (pdResults[16]) : (-0.0521985)
VM Axial Resistances (pdResults[17]) : (4.3046)
VM Axial Resistances (pdResults[18]) : (-0.0489191)
VM Axial Resistances (pdResults[19]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0578759)
VM Membrane Potentials (pdVms[1]) : (-0.0575825)
VM Membrane Potentials (pdVms[2]) : (-0.0571616)
VM Membrane Potentials (pdVms[3]) : (-0.0569656)
VM Membrane Potentials (pdVms[4]) : (-0.0566405)
VM Membrane Potentials (pdVms[5]) : (-0.0560181)
VM Membrane Potentials (pdVms[6]) : (-0.0557131)
VM Membrane Potentials (pdVms[7]) : (-0.0549689)
VM Membrane Potentials (pdVms[8]) : (-0.0510033)
VM Membrane Potentials (pdVms[9]) : (-0.0476799)
-------
Iteration 7
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dTime) : (0.00016)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (10)
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
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (9.95267e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (1.10708e+06)
Compartment (dRm) : (4.9434e+09)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.04817e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (306647)
Compartment (dRm) : (1.61408e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (3)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.8668e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (147150)
Compartment (dRm) : (2.63553e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (4)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.81543e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (335502)
Compartment (dRm) : (1.2895e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (5)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (2.23945e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (230129)
Compartment (dRm) : (2.19696e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (6)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.75406e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (169782)
Compartment (dRm) : (2.80492e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (7)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.37097e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (442254)
Compartment (dRm) : (1.45952e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (8)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.04851e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (518791)
Compartment (dRm) : (9.74544e+09)
MinimumDegree (iEntries) : (10)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (1)
MinimumDegree (piChildren[3][0]) : (4)
MinimumDegree (piChildren[4]) : (1)
MinimumDegree (piChildren[4][0]) : (5)
MinimumDegree (piChildren[5]) : (1)
MinimumDegree (piChildren[5][0]) : (6)
MinimumDegree (piChildren[6]) : (1)
MinimumDegree (piChildren[6][0]) : (7)
MinimumDegree (piChildren[7]) : (1)
MinimumDegree (piChildren[7][0]) : (8)
MinimumDegree (piChildren[8]) : (1)
MinimumDegree (piChildren[8][0]) : (9)
MinimumDegree (piChildren[9]) : (0)
MinimumDegree (piForward[0]) : (9)
MinimumDegree (piForward[1]) : (8)
MinimumDegree (piForward[2]) : (7)
MinimumDegree (piForward[3]) : (6)
MinimumDegree (piForward[4]) : (5)
MinimumDegree (piForward[5]) : (4)
MinimumDegree (piForward[6]) : (3)
MinimumDegree (piForward[7]) : (2)
MinimumDegree (piForward[8]) : (1)
MinimumDegree (piForward[9]) : (0)
MinimumDegree (piBackward[0]) : (9)
MinimumDegree (piBackward[1]) : (8)
MinimumDegree (piBackward[2]) : (7)
MinimumDegree (piBackward[3]) : (6)
MinimumDegree (piBackward[4]) : (5)
MinimumDegree (piBackward[5]) : (4)
MinimumDegree (piBackward[6]) : (3)
MinimumDegree (piBackward[7]) : (2)
MinimumDegree (piBackward[8]) : (1)
MinimumDegree (piBackward[9]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 5			HECCER_COP_SET_DIAGONAL
00006 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00008 :: 5			HECCER_COP_SET_DIAGONAL
00009 :: 1    6		HECCER_COP_FORWARD_ELIMINATION    6
00011 :: 5			HECCER_COP_SET_DIAGONAL
00012 :: 1    8		HECCER_COP_FORWARD_ELIMINATION    8
00014 :: 5			HECCER_COP_SET_DIAGONAL
00015 :: 1   10		HECCER_COP_FORWARD_ELIMINATION   10
00017 :: 5			HECCER_COP_SET_DIAGONAL
00018 :: 1   12		HECCER_COP_FORWARD_ELIMINATION   12
00020 :: 5			HECCER_COP_SET_DIAGONAL
00021 :: 1   14		HECCER_COP_FORWARD_ELIMINATION   14
00023 :: 5			HECCER_COP_SET_DIAGONAL
00024 :: 1   16		HECCER_COP_FORWARD_ELIMINATION   16
00026 :: 4			HECCER_COP_FINISH
00027 :: 2   18		HECCER_COP_BACKWARD_SUBSTITUTION   18
00029 :: 3			HECCER_COP_FINISH_ROW
00030 :: 2   16		HECCER_COP_BACKWARD_SUBSTITUTION   16
00032 :: 3			HECCER_COP_FINISH_ROW
00033 :: 2   14		HECCER_COP_BACKWARD_SUBSTITUTION   14
00035 :: 3			HECCER_COP_FINISH_ROW
00036 :: 2   12		HECCER_COP_BACKWARD_SUBSTITUTION   12
00038 :: 3			HECCER_COP_FINISH_ROW
00039 :: 2   10		HECCER_COP_BACKWARD_SUBSTITUTION   10
00041 :: 3			HECCER_COP_FINISH_ROW
00042 :: 2    8		HECCER_COP_BACKWARD_SUBSTITUTION    8
00044 :: 3			HECCER_COP_FINISH_ROW
00045 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00047 :: 3			HECCER_COP_FINISH_ROW
00048 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00050 :: 3			HECCER_COP_FINISH_ROW
00051 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00053 :: 3			HECCER_COP_FINISH_ROW
00054 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 1			HECCER_MOP_COMPARTMENT
00005 :: 1			HECCER_MOP_COMPARTMENT
00006 :: 1			HECCER_MOP_COMPARTMENT
00007 :: 1			HECCER_MOP_COMPARTMENT
00008 :: 1			HECCER_MOP_COMPARTMENT
00009 :: 1			HECCER_MOP_COMPARTMENT
00010 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (4.81827)
VM Diagonals (pdDiagonals[1]) : (13.426)
VM Diagonals (pdDiagonals[2]) : (47.4699)
VM Diagonals (pdDiagonals[3]) : (46.7046)
VM Diagonals (pdDiagonals[4]) : (20.2012)
VM Diagonals (pdDiagonals[5]) : (53.3701)
VM Diagonals (pdDiagonals[6]) : (33.9933)
VM Diagonals (pdDiagonals[7]) : (5.18436)
VM Diagonals (pdDiagonals[8]) : (4.81797)
VM Diagonals (pdDiagonals[9]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-5.71812)
VM Axial Resistances (pdAxres[1]) : (-3.81807)
VM Axial Resistances (pdAxres[2]) : (-12.8909)
VM Axial Resistances (pdAxres[3]) : (-6.7077)
VM Axial Resistances (pdAxres[4]) : (-26.3007)
VM Axial Resistances (pdAxres[5]) : (-33.5787)
VM Axial Resistances (pdAxres[6]) : (-11.389)
VM Axial Resistances (pdAxres[7]) : (-19.4038)
VM Axial Resistances (pdAxres[8]) : (-15.9664)
VM Axial Resistances (pdAxres[9]) : (-7.81198)
VM Axial Resistances (pdAxres[10]) : (-22.2946)
VM Axial Resistances (pdAxres[11]) : (-36.4034)
VM Axial Resistances (pdAxres[12]) : (-3.27659)
VM Axial Resistances (pdAxres[13]) : (-10.6985)
VM Axial Resistances (pdAxres[14]) : (-1.56946)
VM Axial Resistances (pdAxres[15]) : (-0.90757)
VM Axial Resistances (pdAxres[16]) : (-0.282813)
VM Axial Resistances (pdAxres[17]) : (-2.2483)
VM Axial Resistances (pdAxres[18]) : (-2.2483)
VM Axial Resistances (pdAxres[19]) : (-0.90757)
VM Axial Resistances (pdAxres[20]) : (-10.6985)
VM Axial Resistances (pdAxres[21]) : (-36.4034)
VM Axial Resistances (pdAxres[22]) : (-7.81198)
VM Axial Resistances (pdAxres[23]) : (-19.4038)
VM Axial Resistances (pdAxres[24]) : (-33.5787)
VM Axial Resistances (pdAxres[25]) : (-6.7077)
VM Axial Resistances (pdAxres[26]) : (-3.81807)
VM Axial Resistances (pdResults[0]) : (-0.0567299)
VM Axial Resistances (pdResults[1]) : (4.81827)
VM Axial Resistances (pdResults[2]) : (-0.0564327)
VM Axial Resistances (pdResults[3]) : (8.8949)
VM Axial Resistances (pdResults[4]) : (-0.0560073)
VM Axial Resistances (pdResults[5]) : (37.7487)
VM Axial Resistances (pdResults[6]) : (-0.0558094)
VM Axial Resistances (pdResults[7]) : (23.3094)
VM Axial Resistances (pdResults[8]) : (-0.0554814)
VM Axial Resistances (pdResults[9]) : (10.7204)
VM Axial Resistances (pdResults[10]) : (-0.0548541)
VM Axial Resistances (pdResults[11]) : (41.7354)
VM Axial Resistances (pdResults[12]) : (-0.0545469)
VM Axial Resistances (pdResults[13]) : (14.5469)
VM Axial Resistances (pdResults[14]) : (-0.0537972)
VM Axial Resistances (pdResults[15]) : (2.77461)
VM Axial Resistances (pdResults[16]) : (-0.0497936)
VM Axial Resistances (pdResults[17]) : (4.3046)
VM Axial Resistances (pdResults[18]) : (-0.0464581)
VM Axial Resistances (pdResults[19]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0555839)
VM Membrane Potentials (pdVms[1]) : (-0.0552829)
VM Membrane Potentials (pdVms[2]) : (-0.0548529)
VM Membrane Potentials (pdVms[3]) : (-0.0546532)
VM Membrane Potentials (pdVms[4]) : (-0.0543222)
VM Membrane Potentials (pdVms[5]) : (-0.0536902)
VM Membrane Potentials (pdVms[6]) : (-0.0533807)
VM Membrane Potentials (pdVms[7]) : (-0.0526255)
VM Membrane Potentials (pdVms[8]) : (-0.0485839)
VM Membrane Potentials (pdVms[9]) : (-0.0452362)
-------
Iteration 8
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dTime) : (0.00018)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (10)
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
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (9.95267e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (1.10708e+06)
Compartment (dRm) : (4.9434e+09)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.04817e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (306647)
Compartment (dRm) : (1.61408e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (3)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.8668e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (147150)
Compartment (dRm) : (2.63553e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (4)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.81543e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (335502)
Compartment (dRm) : (1.2895e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (5)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (2.23945e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (230129)
Compartment (dRm) : (2.19696e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (6)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.75406e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (169782)
Compartment (dRm) : (2.80492e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (7)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.37097e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (442254)
Compartment (dRm) : (1.45952e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (8)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.04851e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (518791)
Compartment (dRm) : (9.74544e+09)
MinimumDegree (iEntries) : (10)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (1)
MinimumDegree (piChildren[3][0]) : (4)
MinimumDegree (piChildren[4]) : (1)
MinimumDegree (piChildren[4][0]) : (5)
MinimumDegree (piChildren[5]) : (1)
MinimumDegree (piChildren[5][0]) : (6)
MinimumDegree (piChildren[6]) : (1)
MinimumDegree (piChildren[6][0]) : (7)
MinimumDegree (piChildren[7]) : (1)
MinimumDegree (piChildren[7][0]) : (8)
MinimumDegree (piChildren[8]) : (1)
MinimumDegree (piChildren[8][0]) : (9)
MinimumDegree (piChildren[9]) : (0)
MinimumDegree (piForward[0]) : (9)
MinimumDegree (piForward[1]) : (8)
MinimumDegree (piForward[2]) : (7)
MinimumDegree (piForward[3]) : (6)
MinimumDegree (piForward[4]) : (5)
MinimumDegree (piForward[5]) : (4)
MinimumDegree (piForward[6]) : (3)
MinimumDegree (piForward[7]) : (2)
MinimumDegree (piForward[8]) : (1)
MinimumDegree (piForward[9]) : (0)
MinimumDegree (piBackward[0]) : (9)
MinimumDegree (piBackward[1]) : (8)
MinimumDegree (piBackward[2]) : (7)
MinimumDegree (piBackward[3]) : (6)
MinimumDegree (piBackward[4]) : (5)
MinimumDegree (piBackward[5]) : (4)
MinimumDegree (piBackward[6]) : (3)
MinimumDegree (piBackward[7]) : (2)
MinimumDegree (piBackward[8]) : (1)
MinimumDegree (piBackward[9]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 5			HECCER_COP_SET_DIAGONAL
00006 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00008 :: 5			HECCER_COP_SET_DIAGONAL
00009 :: 1    6		HECCER_COP_FORWARD_ELIMINATION    6
00011 :: 5			HECCER_COP_SET_DIAGONAL
00012 :: 1    8		HECCER_COP_FORWARD_ELIMINATION    8
00014 :: 5			HECCER_COP_SET_DIAGONAL
00015 :: 1   10		HECCER_COP_FORWARD_ELIMINATION   10
00017 :: 5			HECCER_COP_SET_DIAGONAL
00018 :: 1   12		HECCER_COP_FORWARD_ELIMINATION   12
00020 :: 5			HECCER_COP_SET_DIAGONAL
00021 :: 1   14		HECCER_COP_FORWARD_ELIMINATION   14
00023 :: 5			HECCER_COP_SET_DIAGONAL
00024 :: 1   16		HECCER_COP_FORWARD_ELIMINATION   16
00026 :: 4			HECCER_COP_FINISH
00027 :: 2   18		HECCER_COP_BACKWARD_SUBSTITUTION   18
00029 :: 3			HECCER_COP_FINISH_ROW
00030 :: 2   16		HECCER_COP_BACKWARD_SUBSTITUTION   16
00032 :: 3			HECCER_COP_FINISH_ROW
00033 :: 2   14		HECCER_COP_BACKWARD_SUBSTITUTION   14
00035 :: 3			HECCER_COP_FINISH_ROW
00036 :: 2   12		HECCER_COP_BACKWARD_SUBSTITUTION   12
00038 :: 3			HECCER_COP_FINISH_ROW
00039 :: 2   10		HECCER_COP_BACKWARD_SUBSTITUTION   10
00041 :: 3			HECCER_COP_FINISH_ROW
00042 :: 2    8		HECCER_COP_BACKWARD_SUBSTITUTION    8
00044 :: 3			HECCER_COP_FINISH_ROW
00045 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00047 :: 3			HECCER_COP_FINISH_ROW
00048 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00050 :: 3			HECCER_COP_FINISH_ROW
00051 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00053 :: 3			HECCER_COP_FINISH_ROW
00054 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 1			HECCER_MOP_COMPARTMENT
00005 :: 1			HECCER_MOP_COMPARTMENT
00006 :: 1			HECCER_MOP_COMPARTMENT
00007 :: 1			HECCER_MOP_COMPARTMENT
00008 :: 1			HECCER_MOP_COMPARTMENT
00009 :: 1			HECCER_MOP_COMPARTMENT
00010 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (4.81827)
VM Diagonals (pdDiagonals[1]) : (13.426)
VM Diagonals (pdDiagonals[2]) : (47.4699)
VM Diagonals (pdDiagonals[3]) : (46.7046)
VM Diagonals (pdDiagonals[4]) : (20.2012)
VM Diagonals (pdDiagonals[5]) : (53.3701)
VM Diagonals (pdDiagonals[6]) : (33.9933)
VM Diagonals (pdDiagonals[7]) : (5.18436)
VM Diagonals (pdDiagonals[8]) : (4.81797)
VM Diagonals (pdDiagonals[9]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-5.71812)
VM Axial Resistances (pdAxres[1]) : (-3.81807)
VM Axial Resistances (pdAxres[2]) : (-12.8909)
VM Axial Resistances (pdAxres[3]) : (-6.7077)
VM Axial Resistances (pdAxres[4]) : (-26.3007)
VM Axial Resistances (pdAxres[5]) : (-33.5787)
VM Axial Resistances (pdAxres[6]) : (-11.389)
VM Axial Resistances (pdAxres[7]) : (-19.4038)
VM Axial Resistances (pdAxres[8]) : (-15.9664)
VM Axial Resistances (pdAxres[9]) : (-7.81198)
VM Axial Resistances (pdAxres[10]) : (-22.2946)
VM Axial Resistances (pdAxres[11]) : (-36.4034)
VM Axial Resistances (pdAxres[12]) : (-3.27659)
VM Axial Resistances (pdAxres[13]) : (-10.6985)
VM Axial Resistances (pdAxres[14]) : (-1.56946)
VM Axial Resistances (pdAxres[15]) : (-0.90757)
VM Axial Resistances (pdAxres[16]) : (-0.282813)
VM Axial Resistances (pdAxres[17]) : (-2.2483)
VM Axial Resistances (pdAxres[18]) : (-2.2483)
VM Axial Resistances (pdAxres[19]) : (-0.90757)
VM Axial Resistances (pdAxres[20]) : (-10.6985)
VM Axial Resistances (pdAxres[21]) : (-36.4034)
VM Axial Resistances (pdAxres[22]) : (-7.81198)
VM Axial Resistances (pdAxres[23]) : (-19.4038)
VM Axial Resistances (pdAxres[24]) : (-33.5787)
VM Axial Resistances (pdAxres[25]) : (-6.7077)
VM Axial Resistances (pdAxres[26]) : (-3.81807)
VM Axial Resistances (pdResults[0]) : (-0.0544187)
VM Axial Resistances (pdResults[1]) : (4.81827)
VM Axial Resistances (pdResults[2]) : (-0.0541163)
VM Axial Resistances (pdResults[3]) : (8.8949)
VM Axial Resistances (pdResults[4]) : (-0.0536839)
VM Axial Resistances (pdResults[5]) : (37.7487)
VM Axial Resistances (pdResults[6]) : (-0.0534829)
VM Axial Resistances (pdResults[7]) : (23.3094)
VM Axial Resistances (pdResults[8]) : (-0.0531499)
VM Axial Resistances (pdResults[9]) : (10.7204)
VM Axial Resistances (pdResults[10]) : (-0.0525136)
VM Axial Resistances (pdResults[11]) : (41.7354)
VM Axial Resistances (pdResults[12]) : (-0.0522021)
VM Axial Resistances (pdResults[13]) : (14.5469)
VM Axial Resistances (pdResults[14]) : (-0.0514422)
VM Axial Resistances (pdResults[15]) : (2.77461)
VM Axial Resistances (pdResults[16]) : (-0.0473884)
VM Axial Resistances (pdResults[17]) : (4.3046)
VM Axial Resistances (pdResults[18]) : (-0.044024)
VM Axial Resistances (pdResults[19]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.0532534)
VM Membrane Potentials (pdVms[1]) : (-0.0529497)
VM Membrane Potentials (pdVms[2]) : (-0.0525148)
VM Membrane Potentials (pdVms[3]) : (-0.0523126)
VM Membrane Potentials (pdVms[4]) : (-0.0519775)
VM Membrane Potentials (pdVms[5]) : (-0.0513371)
VM Membrane Potentials (pdVms[6]) : (-0.0510235)
VM Membrane Potentials (pdVms[7]) : (-0.0502588)
VM Membrane Potentials (pdVms[8]) : (-0.046193)
VM Membrane Potentials (pdVms[9]) : (-0.0428119)
-------
Iteration 9
Heccer (iStatus) : (20)
Heccer (iOptions) : (0)
Heccer (dTime) : (0.0002)
Heccer (dStep) : (2e-05)
Heccer (pvService) : ((nil))
Intermediary (iCompartments) : (10)
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
Compartment (mc.iType) : (1)
Compartment (iParent) : (1)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (9.95267e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (1.10708e+06)
Compartment (dRm) : (4.9434e+09)
Compartment (mc.iType) : (1)
Compartment (iParent) : (2)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.04817e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (306647)
Compartment (dRm) : (1.61408e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (3)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.8668e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (147150)
Compartment (dRm) : (2.63553e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (4)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.81543e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (335502)
Compartment (dRm) : (1.2895e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (5)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (2.23945e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (230129)
Compartment (dRm) : (2.19696e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (6)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (1.75406e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (169782)
Compartment (dRm) : (2.80492e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (7)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (3.37097e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (442254)
Compartment (dRm) : (1.45952e+10)
Compartment (mc.iType) : (1)
Compartment (iParent) : (8)
Compartment (iMechanisms) : (0)
Compartment (dCm) : (5.04851e-12)
Compartment (dEm) : (-0.08)
Compartment (dInitVm) : (-0.068)
Compartment (dInject) : (0)
Compartment (dRa) : (518791)
Compartment (dRm) : (9.74544e+09)
MinimumDegree (iEntries) : (10)
MinimumDegree (piChildren[0]) : (1)
MinimumDegree (piChildren[0][0]) : (1)
MinimumDegree (piChildren[1]) : (1)
MinimumDegree (piChildren[1][0]) : (2)
MinimumDegree (piChildren[2]) : (1)
MinimumDegree (piChildren[2][0]) : (3)
MinimumDegree (piChildren[3]) : (1)
MinimumDegree (piChildren[3][0]) : (4)
MinimumDegree (piChildren[4]) : (1)
MinimumDegree (piChildren[4][0]) : (5)
MinimumDegree (piChildren[5]) : (1)
MinimumDegree (piChildren[5][0]) : (6)
MinimumDegree (piChildren[6]) : (1)
MinimumDegree (piChildren[6][0]) : (7)
MinimumDegree (piChildren[7]) : (1)
MinimumDegree (piChildren[7][0]) : (8)
MinimumDegree (piChildren[8]) : (1)
MinimumDegree (piChildren[8][0]) : (9)
MinimumDegree (piChildren[9]) : (0)
MinimumDegree (piForward[0]) : (9)
MinimumDegree (piForward[1]) : (8)
MinimumDegree (piForward[2]) : (7)
MinimumDegree (piForward[3]) : (6)
MinimumDegree (piForward[4]) : (5)
MinimumDegree (piForward[5]) : (4)
MinimumDegree (piForward[6]) : (3)
MinimumDegree (piForward[7]) : (2)
MinimumDegree (piForward[8]) : (1)
MinimumDegree (piForward[9]) : (0)
MinimumDegree (piBackward[0]) : (9)
MinimumDegree (piBackward[1]) : (8)
MinimumDegree (piBackward[2]) : (7)
MinimumDegree (piBackward[3]) : (6)
MinimumDegree (piBackward[4]) : (5)
MinimumDegree (piBackward[5]) : (4)
MinimumDegree (piBackward[6]) : (3)
MinimumDegree (piBackward[7]) : (2)
MinimumDegree (piBackward[8]) : (1)
MinimumDegree (piBackward[9]) : (0)
Compartment operations
-----
00000 :: 1    0		HECCER_COP_FORWARD_ELIMINATION    0
00002 :: 5			HECCER_COP_SET_DIAGONAL
00003 :: 1    2		HECCER_COP_FORWARD_ELIMINATION    2
00005 :: 5			HECCER_COP_SET_DIAGONAL
00006 :: 1    4		HECCER_COP_FORWARD_ELIMINATION    4
00008 :: 5			HECCER_COP_SET_DIAGONAL
00009 :: 1    6		HECCER_COP_FORWARD_ELIMINATION    6
00011 :: 5			HECCER_COP_SET_DIAGONAL
00012 :: 1    8		HECCER_COP_FORWARD_ELIMINATION    8
00014 :: 5			HECCER_COP_SET_DIAGONAL
00015 :: 1   10		HECCER_COP_FORWARD_ELIMINATION   10
00017 :: 5			HECCER_COP_SET_DIAGONAL
00018 :: 1   12		HECCER_COP_FORWARD_ELIMINATION   12
00020 :: 5			HECCER_COP_SET_DIAGONAL
00021 :: 1   14		HECCER_COP_FORWARD_ELIMINATION   14
00023 :: 5			HECCER_COP_SET_DIAGONAL
00024 :: 1   16		HECCER_COP_FORWARD_ELIMINATION   16
00026 :: 4			HECCER_COP_FINISH
00027 :: 2   18		HECCER_COP_BACKWARD_SUBSTITUTION   18
00029 :: 3			HECCER_COP_FINISH_ROW
00030 :: 2   16		HECCER_COP_BACKWARD_SUBSTITUTION   16
00032 :: 3			HECCER_COP_FINISH_ROW
00033 :: 2   14		HECCER_COP_BACKWARD_SUBSTITUTION   14
00035 :: 3			HECCER_COP_FINISH_ROW
00036 :: 2   12		HECCER_COP_BACKWARD_SUBSTITUTION   12
00038 :: 3			HECCER_COP_FINISH_ROW
00039 :: 2   10		HECCER_COP_BACKWARD_SUBSTITUTION   10
00041 :: 3			HECCER_COP_FINISH_ROW
00042 :: 2    8		HECCER_COP_BACKWARD_SUBSTITUTION    8
00044 :: 3			HECCER_COP_FINISH_ROW
00045 :: 2    6		HECCER_COP_BACKWARD_SUBSTITUTION    6
00047 :: 3			HECCER_COP_FINISH_ROW
00048 :: 2    4		HECCER_COP_BACKWARD_SUBSTITUTION    4
00050 :: 3			HECCER_COP_FINISH_ROW
00051 :: 2    2		HECCER_COP_BACKWARD_SUBSTITUTION    2
00053 :: 3			HECCER_COP_FINISH_ROW
00054 :: 4			HECCER_COP_FINISH
Mechanism operations
-----
00000 :: 1			HECCER_MOP_COMPARTMENT
00001 :: 1			HECCER_MOP_COMPARTMENT
00002 :: 1			HECCER_MOP_COMPARTMENT
00003 :: 1			HECCER_MOP_COMPARTMENT
00004 :: 1			HECCER_MOP_COMPARTMENT
00005 :: 1			HECCER_MOP_COMPARTMENT
00006 :: 1			HECCER_MOP_COMPARTMENT
00007 :: 1			HECCER_MOP_COMPARTMENT
00008 :: 1			HECCER_MOP_COMPARTMENT
00009 :: 1			HECCER_MOP_COMPARTMENT
00010 :: 2			HECCER_MOP_FINISH
VM Diagonals (pdDiagonals[0]) : (4.81827)
VM Diagonals (pdDiagonals[1]) : (13.426)
VM Diagonals (pdDiagonals[2]) : (47.4699)
VM Diagonals (pdDiagonals[3]) : (46.7046)
VM Diagonals (pdDiagonals[4]) : (20.2012)
VM Diagonals (pdDiagonals[5]) : (53.3701)
VM Diagonals (pdDiagonals[6]) : (33.9933)
VM Diagonals (pdDiagonals[7]) : (5.18436)
VM Diagonals (pdDiagonals[8]) : (4.81797)
VM Diagonals (pdDiagonals[9]) : (1.28342)
VM Axial Resistances (pdAxres[0]) : (-5.71812)
VM Axial Resistances (pdAxres[1]) : (-3.81807)
VM Axial Resistances (pdAxres[2]) : (-12.8909)
VM Axial Resistances (pdAxres[3]) : (-6.7077)
VM Axial Resistances (pdAxres[4]) : (-26.3007)
VM Axial Resistances (pdAxres[5]) : (-33.5787)
VM Axial Resistances (pdAxres[6]) : (-11.389)
VM Axial Resistances (pdAxres[7]) : (-19.4038)
VM Axial Resistances (pdAxres[8]) : (-15.9664)
VM Axial Resistances (pdAxres[9]) : (-7.81198)
VM Axial Resistances (pdAxres[10]) : (-22.2946)
VM Axial Resistances (pdAxres[11]) : (-36.4034)
VM Axial Resistances (pdAxres[12]) : (-3.27659)
VM Axial Resistances (pdAxres[13]) : (-10.6985)
VM Axial Resistances (pdAxres[14]) : (-1.56946)
VM Axial Resistances (pdAxres[15]) : (-0.90757)
VM Axial Resistances (pdAxres[16]) : (-0.282813)
VM Axial Resistances (pdAxres[17]) : (-2.2483)
VM Axial Resistances (pdAxres[18]) : (-2.2483)
VM Axial Resistances (pdAxres[19]) : (-0.90757)
VM Axial Resistances (pdAxres[20]) : (-10.6985)
VM Axial Resistances (pdAxres[21]) : (-36.4034)
VM Axial Resistances (pdAxres[22]) : (-7.81198)
VM Axial Resistances (pdAxres[23]) : (-19.4038)
VM Axial Resistances (pdAxres[24]) : (-33.5787)
VM Axial Resistances (pdAxres[25]) : (-6.7077)
VM Axial Resistances (pdAxres[26]) : (-3.81807)
VM Axial Resistances (pdResults[0]) : (-0.0520772)
VM Axial Resistances (pdResults[1]) : (4.81827)
VM Axial Resistances (pdResults[2]) : (-0.0517719)
VM Axial Resistances (pdResults[3]) : (8.8949)
VM Axial Resistances (pdResults[4]) : (-0.0513351)
VM Axial Resistances (pdResults[5]) : (37.7487)
VM Axial Resistances (pdResults[6]) : (-0.0511322)
VM Axial Resistances (pdResults[7]) : (23.3094)
VM Axial Resistances (pdResults[8]) : (-0.0507959)
VM Axial Resistances (pdResults[9]) : (10.7204)
VM Axial Resistances (pdResults[10]) : (-0.0501537)
VM Axial Resistances (pdResults[11]) : (41.7354)
VM Axial Resistances (pdResults[12]) : (-0.0498393)
VM Axial Resistances (pdResults[13]) : (14.5469)
VM Axial Resistances (pdResults[14]) : (-0.0490729)
VM Axial Resistances (pdResults[15]) : (2.77461)
VM Axial Resistances (pdResults[16]) : (-0.0449926)
VM Axial Resistances (pdResults[17]) : (4.3046)
VM Axial Resistances (pdResults[18]) : (-0.0416071)
VM Axial Resistances (pdResults[19]) : (1.28342)
VM Membrane Potentials (pdVms[0]) : (-0.050901)
VM Membrane Potentials (pdVms[1]) : (-0.050594)
VM Membrane Potentials (pdVms[2]) : (-0.0501554)
VM Membrane Potentials (pdVms[3]) : (-0.0499517)
VM Membrane Potentials (pdVms[4]) : (-0.0496143)
VM Membrane Potentials (pdVms[5]) : (-0.0489702)
VM Membrane Potentials (pdVms[6]) : (-0.0486551)
VM Membrane Potentials (pdVms[7]) : (-0.047887)
VM Membrane Potentials (pdVms[8]) : (-0.0437921)
VM Membrane Potentials (pdVms[9]) : (-0.0404023)
', ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "ten passive compartments with different properties and injected current",
			       },
			      ],
       description => "passive model testing",
      };


return $test;


