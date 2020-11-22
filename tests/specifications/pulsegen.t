#!/usr/bin/perl -w
#

use strict;


my $figures
    = [
       {
	axes => {
		 x => {
		       label => "Time",
		       steps => 200,
		       step_size => 0.5,
		      },
		 y => {
		       label => "Pulsegen output",
		      },
		},
	caption => {
		    full => "The output of the pulsegen object is directly coupled to the membrane potential (how can you do that in reality??).",
		    short => "The output of the pulsgen object",
		   },
	name => "pulsegen",
	title => "Pulsgen output over time",
	variables => [
		      {
		       name => "Vm[0]",
		       regex_parser => '\(pdVms\[0\]\) : \((.*?)\)',
		      },
		     ],
       },
      ];


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/code/pulsegen-freerun',
				command_tests => [
						  {
						   description => "Can a single pulsegen object output amplitude in free run mode ?",
						   figures => $figures,
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/pulsegen-freerun.txt`),
						   timeout => 40,
						  },
						 ],
				comment => "This is an integration test for pulsegen and Heccer",
				description => "pulsegen integration functionality, can we output a current in free run mode?",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/pulsegen-extgate',
				command_tests => [
						  {
						   description => " Can a single pulsegen object output amplitude in ext gate mode?",
						   figures => $figures,
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/pulsegen-extgate.txt`),
						   timeout => 40,
						  },
						 ],
				comment => "This is an integration test for pulsegen and Heccer",
				description => "pulsegen integration functionality, can we output a constant pulse with no trigger ?",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/pulsegen-exttrig',
				command_tests => [
						  {
						   description => "Can a single pulsegen object output amplitude in ext gate mode ?",
						   figures => $figures,
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/pulsegen-exttrig.txt`),
						   timeout => 40,
						  },
						 ],
				comment => "This is an integration test for pulsegen and Heccer",
				description => "pulsegen integration functionality, can we output a constant pulse with no gate input ?",
			       },
			      ],
       comment => "All output is obtained with Heccer's disassembler.  The use of the Heccer disassembler for generating the output is useful for debugging and testing, but it may also greatly decrease the accuracy of the figures that are generated from this output.",
       description => "pulsegen simulation object",
       documentation => {
			 explanation => "

The tests instantiate one or more compartments without channels and
connect the membrane potential of one of those compartments with the
output of the pulsgen object.

Note that there is no physical reality behind this simulation.

Models are instantiated by use of C structs with actual variable
values for capacitance and resistance.

",
			 purpose => "
These tests integrate Heccer with the pulsegen object from the
experiment package.
",
			},
       name => 'pulsegen.t',
       tags => [
		'manual',
	       ],
      };


return $test;


