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
				command => 'tests/glue/swig/perl/table-naf',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, simple sodium gates ?",
						   read => [ `cat $::config->{core_directory}/tests/specifications/strings/table-naf.txt`, ],
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "Simple sodium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/glue/swig/perl/table-ka',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, simple potassium gates ?",
						   read => [ `cat $::config->{core_directory}/tests/specifications/strings/table-ka.txt`, ],
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "Simple potassium gate tabulation",
			       },
			      ],
       description => "Gate tabulation",
       name => 'tables.t',
      };


return $test;


