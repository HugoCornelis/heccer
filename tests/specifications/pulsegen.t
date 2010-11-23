#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/code/pulsegen-freerun',
				command_tests => [
						  {
						   description => "Can a single pulsegen object output amplitude in free run mode ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/pulsegen-freerun.txt`),
						   timeout => 40,
						  },
						 ],
				comment => "This is an integration test for pulsegen and Heccer",
				description => "pulsegen integration functionality, can we output a current in free run mode?",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/pulsegen-extgate',
				command_tests => [
						  {
						   description => " Can a single pulsegen object output amplitude in ext gate mode?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/pulsegen-extgate.txt`),
						   timeout => 40,
						  },
						 ],
				comment => "This is an integration test for pulsegen and Heccer",
				description => "pulsegen integration functionality, can we output a constant pulse with no trigger ?",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/pulsegen-exttrig',
				command_tests => [
						  {
						   description => "Can a single pulsegen object output amplitude in ext gate mode ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/pulsegen-exttrig.txt`),
						   timeout => 40,
						  },
						 ],
				comment => "This is an integration test for pulsegen and Heccer",
				description => "pulsegen integration functionality, can we output a constant pulse with no gate input ?",
			       },
			      ],
       description => "pulsegen simulation object",
       name => 'pulsegen.t',
      };


return $test;


