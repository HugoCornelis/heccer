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
				disabled => "Can't get output to match",
				command_tests => [
						  {
						   description => "Can a single passive compartment be clamped (python) ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/python/perfectclamp-passive1.txt`),
						  },
						 ],
				comment => "This is an integration test for perfectclamp and Heccer (python)",

				description => "perfectclamp integration functionality, single passive compartment",
			       },

			       {
				arguments => [
					     ],
				command => 'tests/python/perfectclamp-passive10.py',
				disabled => "Can't get output to match",

				command_tests => [
						  {
						   description => "Can ten passive compartments be clamped in python ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/python/perfectclamp-passive10.txt`),
						   timeout => 100,
						  },
						 ],
				comment => "This is an integration test for perfectclamp and Heccer (python)",
				description => "perfectclamp integration functionality, ten passive compartments (python)",
			       },

			      ],
       description => "perfectclamp circuitry (Python)",
       name => 'perfectclamp.t (python)',
      };


return $test;


