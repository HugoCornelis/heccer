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
				command => 'tests/code/springmass',
				command_tests => [
						  {
						   description => "Is a synaptic (springmass) channel integrated correctly ?",
						   read => [ `cat $::config->{core_directory}/tests/specifications/strings/springmass.txt`, ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "synaptic (springmass) channel integration",
			       },
			      ],
       description => "synaptic channels",
       name => 'synaptic.t',
      };


return $test;


