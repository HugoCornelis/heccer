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
description => "Does the version information match with swig-6-pre-release ?",
						   # $Format: "read => \"${label}\","$
read => "swig-6-pre-release",
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


