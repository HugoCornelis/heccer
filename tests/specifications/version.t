#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/code/version',
				command_tests => [
						  {
						   # $Format: "description => \"Does the version information match with ${label} ?\","$
description => "Does the version information match with 86d130d2d9ceac6696471028a55624df48292e57-0 ?",
						   # $Format: "read => \"${label}\","$
read => "86d130d2d9ceac6696471028a55624df48292e57-0",
						   write => "version",
						  },
						 ],
				description => "check version information",
			       },
			      ],
       description => "run-time versioning",
       name => 'version.t',
      };


return $test;


