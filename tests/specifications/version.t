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
description => "Does the version information match with heccer-1bbb77ee3b2b51952249db25e41129ce548e8b57-0 ?",

						   # $Format: "read => \"${package}-${label}\","$
read => "heccer-1bbb77ee3b2b51952249db25e41129ce548e8b57-0",

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


