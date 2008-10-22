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
				command => 'tests/code/addressing-purk-test-segment',
				command_tests => [
						  {
						   description => "Are the variables in an simplified version of a purkinje segment segment addressed correctly ?",
						   read => [
							    ((join '', `cat $::config->{core_directory}/heccer/config.h` =~ m/define\s+HECCER_SOURCE_NEUROSPACES/)
							     ? (join '', `cat $::config->{core_directory}/tests/specifications/strings/addressing-purk-test-segment--with-neurospaces.txt`)
							     : (join '', `cat $::config->{core_directory}/tests/specifications/strings/addressing-purk-test-segment--without-neurospaces.txt`)),
							   ],
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "addressing variables for an simplified version of a purkinje segment",
			       },
			      ],
       description => "internal and external addressing of variables",
       name => 'addressing.t',
      };


return $test;


