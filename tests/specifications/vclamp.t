#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/code/vclamp-passive',
				command_tests => [
						  {
						   comment => 'this test still needs tuning.',
						   description => "Can a passive compartment be clamped ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/vclamp-passive.txt`),
						  },
						 ],
				comment => "This is an integration test for voltageclamp and Heccer",
				description => "vclamp circuitry, passive compartment",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/vclamp-sodium',
				command_tests => [
						  {
						   description => "Can a compartment with a sodium conductance be clamped ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/vclamp-sodium.txt`),
						  },
						 ],
				comment => "This is an integration test for voltageclamp and Heccer",
				description => "vclamp circuitry, compartment with a sodium conductance",
			       },
			      ],
       description => "vclamp circuitry",
       disabled => 'voltage clamp has been replaced with perfect clamp, and is no longer maintained',
       name => 'vclamp.t',
      };


return $test;


