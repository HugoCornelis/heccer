#!/usr/bin/perl -w
#

use strict;


# slurp mode

local $/;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/code/addressing-current',
				command_tests => [
						  {
						   description => "Are calculations for individual transmembrane current variables turned on ?",
						   disabled => ((join '', `cat $::global_config->{core_directory}/heccer/config.h` =~ m/define\s+HECCER_SOURCE_NEUROSPACES/)
								 ? ''
								 : 'HECCER_SOURCE_NEUROSPACES is disabled'),
						   read => 'Initiated
Heccer (pcName) : (unnamed test)
Heccer (iStatus) : (20)
Heccer (iErrorCount) : (0)
Heccer Options (iOptions) : (32)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dConcentrationGateStart) : (4e-05)
Heccer Options (dConcentrationGateEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer Options (iSmallTableSize) : (149)
Heccer (dTime) : (0)
Heccer (dStep) : (6e-06)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 65568.5 1.00018
00001 :: INITIALIZECHANNEL 0.045 0.000209239
00002 :: LOADVOLTAGETABLE
00003 :: CONCEPTGATE 0 3 (nil)							 0.761193
00004 :: CONCEPTGATE 1 1 (nil)							 0.000920406
00005 :: UPDATECOMPARTMENTCURRENT
00006 :: REGISTERCHANNELCURRENT
00007 :: STORESINGLECHANNELCURRENT							 0 0
00008 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.028)
-------
Iteration 0
Heccer (pcName) : (unnamed test)
Heccer (iStatus) : (20)
Heccer (iErrorCount) : (0)
Heccer Options (iOptions) : (32)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dConcentrationGateStart) : (4e-05)
Heccer Options (dConcentrationGateEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer Options (iSmallTableSize) : (149)
Heccer (dTime) : (6e-06)
Heccer (dStep) : (6e-06)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 65568.5 1.00018
00001 :: INITIALIZECHANNEL 0.045 0.000209239
00002 :: LOADVOLTAGETABLE
00003 :: CONCEPTGATE 0 3 (nil)							 0.761194
00004 :: CONCEPTGATE 1 1 (nil)							 0.000920406
00005 :: UPDATECOMPARTMENTCURRENT
00006 :: REGISTERCHANNELCURRENT
00007 :: STORESINGLECHANNELCURRENT							 8.49394e-08 6.20058e-09
00008 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0272104)
-------
Iteration 100
Heccer (pcName) : (unnamed test)
Heccer (iStatus) : (20)
Heccer (iErrorCount) : (0)
Heccer Options (iOptions) : (32)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dConcentrationGateStart) : (4e-05)
Heccer Options (dConcentrationGateEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer Options (iSmallTableSize) : (149)
Heccer (dTime) : (0.000606)
Heccer (dStep) : (6e-06)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 65568.5 1.00018
00001 :: INITIALIZECHANNEL 0.045 0.000209239
00002 :: LOADVOLTAGETABLE
00003 :: CONCEPTGATE 0 3 (nil)							 0.998688
00004 :: CONCEPTGATE 1 1 (nil)							 1.73665e-05
00005 :: UPDATECOMPARTMENTCURRENT
00006 :: REGISTERCHANNELCURRENT
00007 :: STORESINGLECHANNELCURRENT							 3.61947e-09 1.32106e-10
00008 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.00848615)
-------
Iteration 200
Heccer (pcName) : (unnamed test)
Heccer (iStatus) : (20)
Heccer (iErrorCount) : (0)
Heccer Options (iOptions) : (32)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dConcentrationGateStart) : (4e-05)
Heccer Options (dConcentrationGateEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer Options (iSmallTableSize) : (149)
Heccer (dTime) : (0.001206)
Heccer (dStep) : (6e-06)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 65568.5 1.00018
00001 :: INITIALIZECHANNEL 0.045 0.000209239
00002 :: LOADVOLTAGETABLE
00003 :: CONCEPTGATE 0 3 (nil)							 0.998073
00004 :: CONCEPTGATE 1 1 (nil)							 4.45979e-06
00005 :: UPDATECOMPARTMENTCURRENT
00006 :: REGISTERCHANNELCURRENT
00007 :: STORESINGLECHANNELCURRENT							 9.27779e-10 3.62473e-11
00008 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.00590443)
-------
Iteration 300
Heccer (pcName) : (unnamed test)
Heccer (iStatus) : (20)
Heccer (iErrorCount) : (0)
Heccer Options (iOptions) : (32)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dConcentrationGateStart) : (4e-05)
Heccer Options (dConcentrationGateEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer Options (iSmallTableSize) : (149)
Heccer (dTime) : (0.001806)
Heccer (dStep) : (6e-06)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 65568.5 1.00018
00001 :: INITIALIZECHANNEL 0.045 0.000209239
00002 :: LOADVOLTAGETABLE
00003 :: CONCEPTGATE 0 3 (nil)							 0.997201
00004 :: CONCEPTGATE 1 1 (nil)							 6.50155e-06
00005 :: UPDATECOMPARTMENTCURRENT
00006 :: REGISTERCHANNELCURRENT
00007 :: STORESINGLECHANNELCURRENT							 1.34899e-09 5.60774e-11
00008 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.0034068)
-------
Iteration 400
Heccer (pcName) : (unnamed test)
Heccer (iStatus) : (20)
Heccer (iErrorCount) : (0)
Heccer Options (iOptions) : (32)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dConcentrationGateStart) : (4e-05)
Heccer Options (dConcentrationGateEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer Options (iSmallTableSize) : (149)
Heccer (dTime) : (0.002406)
Heccer (dStep) : (6e-06)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 65568.5 1.00018
00001 :: INITIALIZECHANNEL 0.045 0.000209239
00002 :: LOADVOLTAGETABLE
00003 :: CONCEPTGATE 0 3 (nil)							 0.996163
00004 :: CONCEPTGATE 1 1 (nil)							 9.06833e-06
00005 :: UPDATECOMPARTMENTCURRENT
00006 :: REGISTERCHANNELCURRENT
00007 :: STORESINGLECHANNELCURRENT							 1.87569e-09 8.19384e-11
00008 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (0.00129669)
-------
Iteration 500
Heccer (pcName) : (unnamed test)
Heccer (iStatus) : (20)
Heccer (iErrorCount) : (0)
Heccer Options (iOptions) : (32)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dConcentrationGateStart) : (4e-05)
Heccer Options (dConcentrationGateEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer Options (iSmallTableSize) : (149)
Heccer (dTime) : (0.003006)
Heccer (dStep) : (6e-06)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 65568.5 1.00018
00001 :: INITIALIZECHANNEL 0.045 0.000209239
00002 :: LOADVOLTAGETABLE
00003 :: CONCEPTGATE 0 3 (nil)							 0.995059
00004 :: CONCEPTGATE 1 1 (nil)							 1.18844e-05
00005 :: UPDATECOMPARTMENTCURRENT
00006 :: REGISTERCHANNELCURRENT
00007 :: STORESINGLECHANNELCURRENT							 2.45e-09 1.11144e-10
00008 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.000379398)
-------
Iteration 600
Heccer (pcName) : (unnamed test)
Heccer (iStatus) : (20)
Heccer (iErrorCount) : (0)
Heccer Options (iOptions) : (32)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dConcentrationGateStart) : (4e-05)
Heccer Options (dConcentrationGateEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer Options (iSmallTableSize) : (149)
Heccer (dTime) : (0.003606)
Heccer (dStep) : (6e-06)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 65568.5 1.00018
00001 :: INITIALIZECHANNEL 0.045 0.000209239
00002 :: LOADVOLTAGETABLE
00003 :: CONCEPTGATE 0 3 (nil)							 0.994054
00004 :: CONCEPTGATE 1 1 (nil)							 1.45997e-05
00005 :: UPDATECOMPARTMENTCURRENT
00006 :: REGISTERCHANNELCURRENT
00007 :: STORESINGLECHANNELCURRENT							 3.00067e-09 1.39854e-10
00008 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.00161772)
-------
Iteration 700
Heccer (pcName) : (unnamed test)
Heccer (iStatus) : (20)
Heccer (iErrorCount) : (0)
Heccer Options (iOptions) : (32)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dConcentrationGateStart) : (4e-05)
Heccer Options (dConcentrationGateEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer Options (iSmallTableSize) : (149)
Heccer (dTime) : (0.004206)
Heccer (dStep) : (6e-06)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 65568.5 1.00018
00001 :: INITIALIZECHANNEL 0.045 0.000209239
00002 :: LOADVOLTAGETABLE
00003 :: CONCEPTGATE 0 3 (nil)							 0.993237
00004 :: CONCEPTGATE 1 1 (nil)							 1.68948e-05
00005 :: UPDATECOMPARTMENTCURRENT
00006 :: REGISTERCHANNELCURRENT
00007 :: STORESINGLECHANNELCURRENT							 3.46382e-09 1.64391e-10
00008 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.0024662)
-------
Iteration 800
Heccer (pcName) : (unnamed test)
Heccer (iStatus) : (20)
Heccer (iErrorCount) : (0)
Heccer Options (iOptions) : (32)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dConcentrationGateStart) : (4e-05)
Heccer Options (dConcentrationGateEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer Options (iSmallTableSize) : (149)
Heccer (dTime) : (0.004806)
Heccer (dStep) : (6e-06)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 65568.5 1.00018
00001 :: INITIALIZECHANNEL 0.045 0.000209239
00002 :: LOADVOLTAGETABLE
00003 :: CONCEPTGATE 0 3 (nil)							 0.992667
00004 :: CONCEPTGATE 1 1 (nil)							 1.86007e-05
00005 :: UPDATECOMPARTMENTCURRENT
00006 :: REGISTERCHANNELCURRENT
00007 :: STORESINGLECHANNELCURRENT							 3.80701e-09 1.82749e-10
00008 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.00300752)
-------
Iteration 900
Heccer (pcName) : (unnamed test)
Heccer (iStatus) : (20)
Heccer (iErrorCount) : (0)
Heccer Options (iOptions) : (32)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dConcentrationGateStart) : (4e-05)
Heccer Options (dConcentrationGateEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer Options (iSmallTableSize) : (149)
Heccer (dTime) : (0.005406)
Heccer (dStep) : (6e-06)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 65568.5 1.00018
00001 :: INITIALIZECHANNEL 0.045 0.000209239
00002 :: LOADVOLTAGETABLE
00003 :: CONCEPTGATE 0 3 (nil)							 0.992288
00004 :: CONCEPTGATE 1 1 (nil)							 1.97517e-05
00005 :: UPDATECOMPARTMENTCURRENT
00006 :: REGISTERCHANNELCURRENT
00007 :: STORESINGLECHANNELCURRENT							 4.03794e-09 1.95157e-10
00008 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.00333324)
-------
Final Iteration
Heccer (pcName) : (unnamed test)
Heccer (iStatus) : (20)
Heccer (iErrorCount) : (0)
Heccer Options (iOptions) : (32)
Heccer Options (dIntervalStart) : (-0.1)
Heccer Options (dIntervalEnd) : (0.05)
Heccer Options (dConcentrationGateStart) : (4e-05)
Heccer Options (dConcentrationGateEnd) : (0.3)
Heccer Options (iIntervalEntries) : (3000)
Heccer Options (iSmallTableSize) : (149)
Heccer (dTime) : (0.006)
Heccer (dStep) : (6e-06)
Compartment (mc.iType) : (1)
Tables (iTabulatedGateCount) : (2)
Compartment operations
-----
00000 :: FINISH
00001 :: FINISH
Mechanism operations
-----
00000 :: COMPARTMENT							 -2.23189e-10 0 65568.5 1.00018
00001 :: INITIALIZECHANNEL 0.045 0.000209239
00002 :: LOADVOLTAGETABLE
00003 :: CONCEPTGATE 0 3 (nil)							 0.992055
00004 :: CONCEPTGATE 1 1 (nil)							 2.04564e-05
00005 :: UPDATECOMPARTMENTCURRENT
00006 :: REGISTERCHANNELCURRENT
00007 :: STORESINGLECHANNELCURRENT							 4.17907e-09 2.0276e-10
00008 :: FINISH
VM Diagonals (pdDiagonals[0]) : (1.00018)
VM Axial Resistances (pdResults[0]) : (0)
VM Axial Resistances (pdResults[1]) : (0)
VM Membrane Potentials (pdVms[0]) : (-0.00351932)
Membrane potential is -0.00351932
Conductance is 4.17907e-09
Current is 2.0276e-10
',
						  },
						  {
						   description => "Are transmembrane current variables addressed correctly ?",
						   disabled => ((join '', `cat $::global_config->{core_directory}/heccer/config.h` =~ m/define\s+HECCER_SOURCE_NEUROSPACES/)
								 ? ''
								 : 'HECCER_SOURCE_NEUROSPACES is disabled'),
						   read => {
							    application_output_file => '/tmp/output',
							    expected_output_file => "$::global_config->{core_directory}/tests/specifications/strings/addressing-current.txt",
							   },
						  },
						 ],
				description => "addressing channel variables",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/addressing-purk-test-segment',
				command_tests => [
						  {
						   description => "Are the variables in a simplified version of a purkinje segment segment addressed correctly ?",
						   read => ((join '', `cat $::global_config->{core_directory}/heccer/config.h` =~ m/define\s+HECCER_SOURCE_NEUROSPACES/)
							    ? (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/addressing-purk-test-segment--with-neurospaces.txt`)
							    : (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/addressing-purk-test-segment--without-neurospaces.txt`)),
						  },
						 ],
				description => "addressing variables for a simplified version of a purkinje segment",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/addressing-synchan',
				command_tests => [
						  {
						   description => "Is synchan activation addressed correctly ?",
						   disabled => ((join '', `cat $::global_config->{core_directory}/heccer/config.h` =~ m/define\s+HECCER_SOURCE_NEUROSPACES/)
								 ? ''
								 : 'HECCER_SOURCE_NEUROSPACES is disabled'),
						   read => '
0 0 0 0
1 0 0 0
2 0 0 0
3 0 0 0
4 0 0 0
5 0 0 0
6 0 0 0
7 0 0 0
8 0 0 0
9 0 0 0
10 0.970462 0 0
11 0.951245 0 0
12 0.932409 0 0
13 0.913946 0 0
14 0.895849 0 0
15 0.87811 0 0
16 0.860722 0 0
17 0.843679 0 0
18 0.826973 0 0
19 0.810598 0 0
20 0.794547 0 0
21 0.778814 0 0
22 0.763392 0 0
23 0.748276 0 0
24 0.733459 0 0
25 0.718936 0 0
26 0.7047 0 0
27 0.690746 0 0
28 0.677068 0 0
29 0.663661 0 0
0 -1
1 -1
2 -1
3 -1
4 -1
5 -1
6 -1
7 -1
8 -1
9 -1
10 -1
11 -1
12 -1
13 -1
14 -1
15 -1
16 -1
17 -1
18 -1
19 -1
20 -1
21 -1
22 -1
23 -1
24 -1
25 -1
26 -1
27 -1
28 -1
29 -1
',
						  },
						 ],
				description => "addressing synchan activation",
			       },
			      ],
       description => "internal and external addressing of variables",
       name => 'addressing.t',
      };


return $test;


