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
						   # $Format: "description => \"Does the version information match with ${package}-${label} ?\","$
description => "Does the version information match with heccer-83c9247effe56b4735580b182b3bfdbda8cd1907.0 ?",

						   # $Format: "read => \"${package}-${label}\","$
read => "heccer-83c9247effe56b4735580b182b3bfdbda8cd1907.0",

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


