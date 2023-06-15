#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/python/getversion.py',
				command_tests => [
						  {
# $Format: "description => \"Does the version information match with ${major}.${minor}.${micro}-${label} ?\","$
description => "Does the version information match with 0.0.0-alpha ?",

# $Format: "read => \"${major}.${minor}.${micro}-${label}\","$
read => "0.0.0-alpha",

						   write => "version",
						  },
						 ],
				description => "check version information in python",
			       },
			      ],
       description => "run-time versioning",
       disabled => "the python bindings are broken",
       name => 'python/pyversion.t',
      };


return $test;


