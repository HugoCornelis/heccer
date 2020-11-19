#!/usr/bin/perl -w
#

use strict;


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
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/perfectclamp-passive10-2.txt`),
						   figures => [
							       {
								axes => {
									 x => {
									       label => "Compartmental voltage",
									       steps => 1000,
									       step_size => (3e-6),
									      },
									 y => {
									       label => "Time",
									      },
									},
								caption => {
									    full => "Ten passive compartments clamped with command voltage of 0.1V using a perfect clamp object.",
									    short => "Ten passive compartments clamped",
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
							      ],
						   timeout => 20,
						  },
						 ],
				description => "perfectclamp integration functionality, ten passive compartments (2)",
			       },
			      ],
       comment => "All output is obtained with the disassembler facility that is built into Heccer.  The use of the Heccer disassembler for generating the output is useful for debugging, but it also distorts the figure created with this type of output.",
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
      };


return $test;


