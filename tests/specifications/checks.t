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
				command => 'tests/code/check-compartment',
				command_tests => [
						  {
						   comment => 'The internal scheduler still schedules heccer, but heccer refuses to do anything, this is normal and part of the test',
						   description => "Are illegal compartment parameters reported properly ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/check-compartment.txt`),
						  },
						 ],
				description => "illegal compartment parameters",
			       },
			      ],
       description => "checking of illegal parameters in the intermediary",
       name => 'checks.t',
      };


return $test;


