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
description => "Does the version information match with 1b9de3b638c28c0e77b85db9533d1fe686defe02-0 ?",
						   # $Format: "read => \"${label}\","$
read => "1b9de3b638c28c0e77b85db9533d1fe686defe02-0",
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


