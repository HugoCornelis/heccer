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
				command => 'tests/code/table-dual-kdr',
				command_tests => [
						  {
						   description => "Are gates tables shared across compartments, kdr case ?",
						   read => [ `cat $::config->{core_directory}/tests/specifications/strings/table-dual-kdr.txt`, ],
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "two delayed rectifier channels in two compartments",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-dual-km',
				command_tests => [
						  {
						   description => "Are gates tables shared across compartments, km case ?",
						   read => [ `cat $::config->{core_directory}/tests/specifications/strings/table-dual-km.txt`, ],
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "two muscarinic channels in two compartments",
			       },
			      ],
       description => "table sharing accross compartments",
       name => 'table-sharing.t',
      };


return $test;


