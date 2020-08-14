#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/python/c1c2p1.py',
				command_tests => [
						  {
						   description => "Python: Are two passive compartments with injected current solved correctly ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/c1c2p1.txt`),
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "two passive compartments with injected current via python",			       },
			      ],
       description => "Passive model testing in python",
       name => 'python/pypassive.t',
      };


return $test;
