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
						   comment => 'note that perfect clamps have only been validated with passive compartments.',
						   description => "Can a single passive compartment be clamped ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/perfectclamp-passive1.txt`),
						  },
						 ],
				description => "perfectclamp functionality, single passive compartment",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/perfectclamp-passive10',
				command_tests => [
						  {
						   comment => 'note that perfect clamps have only been validated with passive compartments.',
						   description => "Can ten passive compartments be clamped ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/perfectclamp-passive10.txt`),
						  },
						 ],
				description => "perfectclamp functionality, ten passive compartments",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/perfectclamp-passive10-2',
				command_tests => [
						  {
						   comment => 'note that perfect clamps have only been validated with passive compartments.',
						   description => "Can ten passive compartments be clamped (2) ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/perfectclamp-passive10-2.txt`),
						  },
						 ],
				description => "perfectclamp functionality, ten passive compartments (2)",
			       },
			      ],
       description => "perfectclamp circuitry",
       name => 'perfectclamp.t',
      };


return $test;


