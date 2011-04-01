#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/python/perfectclamp-passive1.py',
				command_tests => [
						  {
						   description => "Can a single passive compartment be clamped (python) ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/python/perfectclamp-passive1.txt`),
						  },
						 ],
				comment => "This is an integration test for perfectclamp and Heccer (python)",

				description => "perfectclamp integration functionality, single passive compartment",
			       },

			      ],
       description => "perfectclamp circuitry (Python)",
       name => 'perfectclamp.t',
      };


return $test;


