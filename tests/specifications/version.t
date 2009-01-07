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
description => "Does the version information match with heccer-cf4a068565733e3d58db9dc9c04ef8d879c70b05-0 ?",
						   # $Format: "read => \"${package}-${label}\","$
read => "heccer-cf4a068565733e3d58db9dc9c04ef8d879c70b05-0",
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


