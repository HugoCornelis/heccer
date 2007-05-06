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
				command => 'tests/code/springmass1',
				command_tests => [
						  {
						   description => "Is a synaptic (springmass) channel integrated correctly, smaller time step ?",
						   read => [ `cat $::config->{core_directory}/tests/specifications/strings/springmass1.txt`, ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "synaptic (springmass) channel integration, smaller time step",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/springmass2',
				command_tests => [
						  {
						   description => "Is a synaptic (springmass) channel integrated correctly, larger time step ?",
						   read => [ `cat $::config->{core_directory}/tests/specifications/strings/springmass2.txt`, ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "synaptic (springmass) channel integration, larger time step",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/springmass3',
				command_tests => [
						  {
						   description => "Is a synaptic (springmass) channel integrated correctly, endogenous firing (works only with the linux rng) ?",
						   disabled => (`cat $::config->{core_directory}/heccer/config.h` =~ m/define RANDOM/),
						   read => [ `cat $::config->{core_directory}/tests/specifications/strings/springmass3.txt`, ],
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "synaptic (springmass) channel integration, endogenous firing",
			       },
			      ],
       description => "synaptic channels",
       name => 'synaptic.t',
      };


return $test;


