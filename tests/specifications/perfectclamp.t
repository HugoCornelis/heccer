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
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/perfectclamp-passive1.txt`),
						  },
						 ],
				comment => "This is an integration test for perfectclamp and Heccer",

				description => "perfectclamp integration functionality, single passive compartment",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/perfectclamp-passive10',
				command_tests => [
						  {
						   description => "Can ten passive compartments be clamped ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/perfectclamp-passive10.txt`),
						   timeout => 20,
						  },
						 ],
				comment => "This is an integration test for perfectclamp and Heccer",
				description => "perfectclamp integration functionality, ten passive compartments",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/perfectclamp-passive10-2',
				command_tests => [
						  {
						   description => "Can ten passive compartments be clamped (2) ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/perfectclamp-passive10-2.txt`),
						   timeout => 20,
						  },
						 ],
				comment => "This is an integration test for perfectclamp and Heccer",
				description => "perfectclamp integration functionality, ten passive compartments (2)",
			       },
			      ],
       description => "perfectclamp circuitry",
       name => 'perfectclamp.t',
      };


return $test;


