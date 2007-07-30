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
						   read => [ `cat $::config->{core_directory}/tests/specifications/strings/spiker1.txt`, ],
						   timeout => 8,
						   write => undef,
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
						   description => "Is a single spike reported properly, single source, single spike, multiple targets ?",
						   read => [ `cat $::config->{core_directory}/tests/specifications/strings/spiker2.txt`, ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "single source, single spike, multiple targets",
			       },
			      ],
       description => "spiking behaviour",
       name => 'spikes.t',
      };


return $test;


