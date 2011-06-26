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
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/springmass1.txt && cat $::config->{core_directory}/tests/specifications/strings/springmass1-output.txt`),
						   timeout => 8,
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
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/springmass2.txt`),
						   timeout => 8,
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
						   disabled => (`cat $::config->{core_directory}/heccer/config.h` =~ m/define RANDOM.*ran1/ ? 1 : 0),
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/springmass3.txt && cat $::config->{core_directory}/tests/specifications/strings/springmass3-output.txt`),
						   timeout => 8,
						  },
						 ],
				description => "synaptic (springmass) channel integration, endogenous firing",
			       },
			       {
				arguments => [
					      (
					       $ENV{srcdir}
					       ? (
						  -f '../../_build/tests/code/springmass4'
						  ? ('-c', "cd $ENV{srcdir} && ../_build/tests/code/springmass4")
						  : ('-c', "cd $ENV{srcdir} && ../tests/code/springmass4")
						 )
					       : ('-c', "cd tests && ./code/springmass4")
					      ),
					     ],
				command => (
					    $ENV{srcdir}
					    ? "/bin/sh"
					    : "/bin/sh" # 'tests/code/springmass4'
					   ),
				command_tests => [
						  {
						   description => "Is a synaptic (springmass) channel integrated correctly, larger time step, events from a file ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/springmass2.txt`),
						   timeout => 8,
						  },
						 ],
				description => "synaptic (springmass) channel integration, events from a file",
			       },
			      ],
       description => "synaptic channels",
       name => 'synaptic.t',
      };


return $test;


