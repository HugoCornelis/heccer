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
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/singlea-naf-current.txt`),
						   timeout => 10,
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
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/singlea-naf2-aggregator.txt`),
						   timeout => 10,
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
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/doublea-aggregator.txt`),
						   timeout => 10,
						  },
						 ],
				description => "single channel currents summation, double compartment case",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/addressing-aggregator1',
				command_tests => [
						  {
						   description => "Are single channel currents summed correctly, single compartment, three aggregators ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/addressing-aggregator1.txt`),
						   timeout => 10,
						  },
						 ],
				description => "single channel currents summation, single compartment, three aggregators",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/aggregator-kc',
				command_tests => [
						  {
						   description => "Are single channel currents summed correctly, single compartment, kc current ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/aggregator-kc.txt`),
						   timeout => 10,
						  },
						 ],
				description => "single channel currents summation, single compartment, kc current",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/aggregator-kc-feedback',
				command_tests => [
						  {
						   description => "Are single channel currents summed correctly, single compartment, kc current in feedback with a ca current ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/aggregator-kc-feedback.txt`),
						   timeout => 10,
						  },
						 ],
				description => "single channel currents summation, single compartment, kc current in feedback with a ca current",
			       },
			      ],
       description => "various options",
       name => 'options.t',
      };


return $test;


