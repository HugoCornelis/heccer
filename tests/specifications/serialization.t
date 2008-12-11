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
				command => 'tests/code/serialization-singlep',
				command_tests => [
						  {
						   description => "Can we serialize a single compartment passive model ?",
 						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-singlep.txt`),
						   write => undef,
						  },
						 ],
				description => "single compartment passive model serialization",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/serialization-doublep',
				command_tests => [
						  {
						   description => "Can we serialize a double compartment passive model ?",
 						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-doublep.txt`),
						   write => undef,
						  },
						 ],
				description => "double compartment passive model serialization",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/serialization-triplep',
				command_tests => [
						  {
						   description => "Can we serialize a triplep compartment passive model ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-triplep.txt`),
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "triplet passive compartment serialization.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/serialization-fork3p',
				command_tests => [
						  {
						   description => "Can we serialize a fork3p compartment passive model ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-fork3p.txt`),
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "fork3p fork of three passive compartments.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/serialization-fork4p1',
				command_tests => [
						  {
						   description => "Can we serialize a fork4p1 compartment passive model ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-fork4p1.txt`),
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "fork4p1 fork of four passive compartments, first alternative.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/serialization-fork4p2',
				command_tests => [
						  {
						   description => "Can we serialize a fork4p2 compartment passive model ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-fork4p2.txt`),
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "fork4p2 fork of four passive compartments, second alternative.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/serialization-fork4p3',
				command_tests => [
						  {
						   description => "Can we serialize a fork4p3 compartment passive model ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-fork4p3.txt`),
						   timeout => 8,
						   write => undef,
						  },
						 ],
				description => "fork4p3 fork of four passive compartments, third alternative.",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/serialization-c1c2p1',
				command_tests => [
						  {
						   description => "Can we serialize a c1c2p1 compartment passive model ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-c1c2p1.txt`),
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "c1c2p1 two passive compartments with injected current",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/serialization-c1c2p2',
				command_tests => [
						  {
						   description => "Can we serialize a c1c2p2 compartment passive model ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-c1c2p2.txt`),
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "c1c2p2 two passive compartments with asymetric properties and injected current",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/serialization-tensizesp',
				command_tests => [
						  {
						   description => "Can we serialize a tensizesp compartment passive model ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-tensizesp.txt`),
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "tensizesp ten passive compartments with different properties and injected current",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/serialization-singlea-naf',
				command_tests => [
						  {
						   description => "Can we serialize a single compartment with a naf conductance ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-singlea-naf.txt`),
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "a single compartment with a naf conductance",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/serialization-pool2',
				command_tests => [
						  {
						   description => "Can we serialize two compartments with two pools ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-pool2.txt`),
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "two compartments with two pools",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/serialization-pool1-feedback2',
				command_tests => [
						  {
						   description => "Can we serialize a compartment with a pool with a feedback loop, reversed order ?",
						   read => (join '', `cat $::config->{core_directory}/tests/specifications/strings/serialization-pool1-feedback2.txt`),
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "compartment with a pool with a feedback loop, reversed order",
			       },
			      ],
       description => "serialization",
       name => 'serialization.t',
      };


return $test;


