#!/usr/bin/perl -w
#

use strict;


# slurp mode

local $/;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/code/spiker1',
				command_tests => [
						  {
						   description => "Is a single spike reported properly, single spike ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/spiker1.txt`),
						   timeout => 8,
						  },
						 ],
				description => "sodium and potassium channel, single spike",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/spiker2',
				command_tests => [
						  {
						   description => "Is a single spike reported properly, single source, single spike, multiple targets, hardcoded connection matrix ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/spiker2.txt | grep -v DES:`),
						   timeout => 8,
						  },
						 ],
				description => "single source, single spike, multiple targets, hardcoded connection matrix",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/spiker3',
				command_tests => [
						  {
						   description => "Is a single spike reported properly, single source, single spike, multiple targets ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/spiker2.txt`),
						   timeout => 8,
						  },
						 ],
				description => "single source, single spike, multiple targets",
			       },
			      ],
       description => "spiking behaviour",
       name => 'spikes.t',
      };


return $test;


