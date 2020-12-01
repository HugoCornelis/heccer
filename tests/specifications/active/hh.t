#!/usr/bin/perl -w
#

use strict;


# slurp mode

local $/;


my $figures
    = [
       {
	axes => {
		 x => {
		       label => "Time",
		       steps => 40000,
		       step_size => 5e-07,
		      },
		 y => {
		       label => "Compartmental membrane potential",
		      },
		},
	caption => {
		    full => "The membrane potential of a single compartment with regular Hodgkin-Huxley channels with applied current injection.",
		    short => "Compartmental membrane potential",
		   },
	name => "hh",
	title => "Compartmental membrane potential over time",
	variables => [
		      {
		       name => "Vm",
		       regex_parser => "\n" . '[0-9]+ (-?[0-9]*\.[-0-9]+([-e0-9]+)?)',
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
				command => 'tests/code/hh1',
				command_tests => [
						  {
						   description => "Is a single compartment with regular HH channels solved correctly ?",
						   figures => $figures,
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/active/hh1.txt`),
						   timeout => 25,
						  },
						 ],
				description => "single compartment with regular HH channels",
			       },
			      ],
       comment => "All output is obtained with Heccer's disassembler.  The use of the Heccer disassembler for generating the output is useful for debugging and testing, but it may also greatly decrease the accuracy of the figures that are generated from this output.",
       description => "interaction between regular HH channels testing",
       documentation => {
			 explanation => "

This test instantiates one compartment with the well-known
Hodgkin-Huxley channels with the parameters that were reported in
their publications that earned them the Nobel prize.

A current of 3e-10 is applied.  This causes the compartment to
generate regular spikes.

Models are instantiated by use of C structs with actual variable
values for capacitance and resistance.

",
			 purpose => "
These tests integrate Heccer with the perfectclamp object from the
experiment package.
",
			},
       name => 'active/hh.t',
       tags => [
		'manual',
	       ],
      };


return $test;


