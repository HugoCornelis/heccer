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
				command => 'tests/code/hh1',
				command_tests => [
						  {
						   description => "Is a single compartment with regular HH channels solved correctly ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/active/hh1.txt`),
						   timeout => 25,
						  },
						 ],
				description => "single compartment with regular HH channels",
			       },
			      ],
       description => "interaction between regular HH channels testing",
       name => 'active/hh.t',
      };


return $test;


