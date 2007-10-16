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
						   description => "Can a passive compartment be clamped ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/vclamp-passive.txt`),
						  },
						 ],
				description => "vclamp circuitry, passive compartment",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/vclamp-sodium',
				command_tests => [
						  {
						   description => "Can a compartment with a sodium conductance be clamped ?",
						   read => "",
						  },
						 ],
				description => "vclamp circuitry, compartment with a sodium conductance",
			       },
			      ],
       description => "vclamp circuitry",
       name => 'vclamp.t',
      };


return $test;


