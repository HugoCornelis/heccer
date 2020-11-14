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
						   timeout => 20,
						  },
						 ],
				description => "perfectclamp integration functionality, ten passive compartments (2)",
			       },
			      ],
       comment => "All output is obtained with the disassembler facility that is built into Heccer.",
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


