#!/usr/bin/perl -w
#

use strict;


my $figures
    = [
       {
	axes => {
		 x => {
		       label => "Time",
		       steps => 1000,
		       step_size => (3e-6),
		      },
		 y => {
		       label => "Compartmental voltage",
		      },
		},
	caption => {
		    full => "A chain of ten passive compartments of which the first one is clamped with a command voltage of 0.1V using a perfect clamp object.",
		    short => "Ten clamped passive compartments",
		   },
	name => "perfectclamp",
	title => "Compartmental membrane potential over time",
	variables => [
		      {
		       name => "Vm[0]",
		       regex_parser => '\(pdVms\[0\]\) : \((.*?)\)',
		      },
		      {
		       name => "Vm[1]",
		       regex_parser => '\(pdVms\[1\]\) : \((.*?)\)',
		      },
		      {
		       name => "Vm[2]",
		       regex_parser => '\(pdVms\[2\]\) : \((.*?)\)',
		      },
		      {
		       name => "Vm[3]",
		       regex_parser => '\(pdVms\[3\]\) : \((.*?)\)',
		      },
		      {
		       name => "Vm[4]",
		       regex_parser => '\(pdVms\[4\]\) : \((.*?)\)',
		      },
		      {
		       name => "Vm[5]",
		       regex_parser => '\(pdVms\[5\]\) : \((.*?)\)',
		      },
		      {
		       name => "Vm[6]",
		       regex_parser => '\(pdVms\[6\]\) : \((.*?)\)',
		      },
		      {
		       name => "Vm[7]",
		       regex_parser => '\(pdVms\[7\]\) : \((.*?)\)',
		      },
		      {
		       name => "Vm[8]",
		       regex_parser => '\(pdVms\[8\]\) : \((.*?)\)',
		      },
		      {
		       name => "Vm[9]",
		       regex_parser => '\(pdVms\[9\]\) : \((.*?)\)',
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
				command => 'tests/code/perfectclamp-passive1',
				command_tests => [
						  {
						   description => "Can a single passive compartment be clamped ?",
						   figures => [
							       {
								axes => {
									 x => {
									       label => "Time",
									       steps => 1000,
									       step_size => (3e-6),
									      },
									 y => {
									       label => "Compartmental voltage",
									      },
									},
								caption => {
									    full => "A single compartment clamped with a command voltage of 0.1V using a perfect clamp object.",
									    short => "A single clamped passive compartment",
									   },
								name => "perfectclamp",
								title => "Compartmental membrane potential over time",
								variables => [
									      {
									       name => "Vm[0]",
									       regex_parser => '\(pdVms\[0\]\) : \((.*?)\)',
									      },
									     ],
							       },
							      ],
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/perfectclamp-passive1.txt`),
						  },
						 ],
				description => "perfectclamp integration functionality, single passive compartment",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/perfectclamp-passive10',
				command_tests => [
						  {
						   description => "Can ten passive compartments be clamped ?",
						   figures => $figures,
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/perfectclamp-passive10.txt`),
						   timeout => 20,
						  },
						 ],
				description => "perfectclamp integration functionality, ten passive compartments",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/perfectclamp-passive10-2',
				command_tests => [
						  {
						   description => "Can ten passive compartments be clamped (2) ?",
						   figures => $figures,
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/perfectclamp-passive10-2.txt`),
						   timeout => 20,
						  },
						 ],
				description => "perfectclamp integration functionality, ten passive compartments (2)",
			       },
			      ],
       comment => "All output is obtained with Heccer's disassembler.  The use of the Heccer disassembler for generating the output is useful for debugging and testing, but it may also greatly decrease the accuracy of the figures that are generated from this output.",
       description => "perfectclamp circuitry",
       documentation => {
			 explanation => "

The tests instantiate one or more compartments without channels and
connect the membrane potential of one of those compartments with the
output of the perfect clamp object.

Models are instantiated by use of C structs with actual variable
values for capacitance and resistance.

",
			 purpose => "
These tests integrate Heccer with the perfectclamp object from the
experiment package.
",
			},
       name => 'perfectclamp.t',
       tags => [
		'manual',
	       ],
      };


return $test;


