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
						   description => "Is a single spike reported properly ?",
						   read => [ `cat $::config->{core_directory}/tests/specifications/strings/spiker1.txt`, ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "sodium and potassium channel, single spike",
			       },
			      ],
       description => "spiking behaviour",
       name => 'spikes.t',
      };


return $test;


