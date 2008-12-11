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
				command => 'tests/code/pool1',
				command_tests => [
						  {
						   description => "Is a pool integrated correctly, one compartment, single pool case ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/pool1.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "pool integration, one compartment, single pool",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/pool2',
				command_tests => [
						  {
						   description => "Is a pool integrated correctly, two compartments, two pools case ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/pool2.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "pool integration, two compartments, two pools",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/pool1-feedback1',
				command_tests => [
						  {
						   description => "Is a pool integrated correctly, one compartment, one pool with a feedback loop ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/pool1-feedback1.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "pool integration, one compartment, one pool with a feedback loop",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/pool1-feedback2',
				command_tests => [
						  {
						   description => "Is a pool integrated correctly, one compartment, one pool with a feedback loop, reversed order ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/pool1-feedback2.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "pool integration, one compartment, one pool with a feedback loop, reversed order",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/pool1-contributors2',
				command_tests => [
						  {
						   description => "Is a pool integrated correctly, one compartment, one pool feed by two channels ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/pool1-contributors2.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "pool integration, one compartment, one pool feed by two channels",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/pool1-nernst',
				command_tests => [
						  {
						   description => "Is the concentration dependent nernst potential calculated correctly ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/pool1-nernst.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "concentration dependent nernst potential calculation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/channel1-nernst1',
				command_tests => [
						  {
						   description => "Is the solved nernst potential applied for channel reversal potentials ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/channel1-nernst1.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "solved nernst potential application for channel reversal potentials",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/channel2-nernst1',
				command_tests => [
						  {
						   description => "Is the solved nernst potential applied for two channel reversal potentials ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/channel2-nernst1.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "solved nernst potential application for two channel reversal potentials",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/channel2-nernst2',
				command_tests => [
						  {
						   description => "Are two solved nernst potentials applied for two channel reversal potentials ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/channel2-nernst2.txt`),
						   timeout => 10,
						   write => undef,
						  },
						 ],
				description => "two solved nernst potentials application for two channel reversal potentials",
			       },
			      ],
       description => "pool integration & related",
       name => 'pools.t',
      };


return $test;


