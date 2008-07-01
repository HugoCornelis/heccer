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
				command => 'tests/code/singlea-naf-current',
				command_tests => [
						  {
						   description => "Is a single channel current and conductance computed correctly ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/singlea-naf-current.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "single channel current and conductance option",
			       },
			      ],
       description => "various options",
       name => 'options.t',
      };


return $test;


