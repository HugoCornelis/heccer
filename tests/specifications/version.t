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
description => "Does the version information match with heccer-3b20c9c93df9a68c2deb59ab041ba09c0c159a30-0 ?",

						   # $Format: "read => \"${package}-${label}\","$
read => "heccer-3b20c9c93df9a68c2deb59ab041ba09c0c159a30-0",

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


