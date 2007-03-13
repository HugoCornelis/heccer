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
				command => 'tests/code/table-naf',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, simple sodium gates ?",
						   read => [ `cat $::config->{core_directory}/tests/library/strings/table-naf.txt`, ],
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "Simple sodium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-ka',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, simple potassium gates ?",
						   read => [ `cat $::config->{core_directory}/tests/library/strings/table-ka.txt`, ],
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "Simple potassium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-kdr',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, delayed rectifier potassium gates ?",
						   read => [ `cat $::config->{core_directory}/tests/library/strings/table-kdr.txt`, ],
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "Delayed rectifier potassium gate tabulation",
			       },
			      ],
       description => "Gate tabulation",
       name => 'tables.t',
      };


return $test;


