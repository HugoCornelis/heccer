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
				command => 'tests/code/singlea-naf-current',
				command_tests => [
						  {
						   description => "Is a single channel current and conductance computed correctly ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/singlea-naf-current.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "single channel current and conductance option",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/singlea-naf2-aggregator',
				command_tests => [
						  {
						   description => "Are single channel currents summed correctly ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/singlea-naf2-aggregator.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "single channel currents summation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/doublea-aggregator',
				command_tests => [
						  {
						   description => "Are single channel currents summed correctly, double compartment case ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/doublea-aggregator.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "single channel currents summation, double compartment case",
			       },
			      ],
       description => "various options",
       name => 'options.t',
      };


return $test;


