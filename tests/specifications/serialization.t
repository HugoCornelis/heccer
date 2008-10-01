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
				command => 'tests/code/serialization',
				command_tests => [
						  {
						   description => "Can we serialize a passive model ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization.txt`),
						   write => undef,
						  },
						 ],
				description => "passive model serialization",
				disabled => 'still need to work on serialization of mechanisms for compartments',
			       },
			      ],
       description => "serialization",
       name => 'serialization.t',
      };


return $test;


