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
				command => 'tests/code/addressing-purk-test-axon',
				command_tests => [
						  {
						   description => "Are the variables in an undocumented version of a purkinje axon segment addressed correctly ?",
						   read => [
							    (`cat $::config->{core_directory}/heccer/config.h` =~ m/define\s+HECCER_SOURCE_NEUROSPACES/
							     ? `cat $::config->{core_directory}/tests/specifications/strings/addressing-purk-test-axon--with-neurospaces.txt`
							     : `cat $::config->{core_directory}/tests/specifications/strings/addressing-purk-test-axon--without-neurospaces.txt`),
							   ],
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "addressing variables for an undocumented version of a purkinje axon segment",
			       },
			      ],
       description => "internal and external addressing of variables",
       name => 'addressing.t',
      };


return $test;


