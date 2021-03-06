#!/usr/bin/perl -w
#

use strict;


# slurp mode

local $/;


my $test
    = {
       command_definitions => [
			       # regular tests

			       (
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-singlep',
				 command_tests => [
						   {
						    description => "Can we serialize a single compartment passive model ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-singlep.txt`),
						   },
						  ],
				 description => "single compartment passive model serialization",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-doublep',
				 command_tests => [
						   {
						    description => "Can we serialize a double compartment passive model ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-doublep.txt`),
						   },
						  ],
				 description => "double compartment passive model serialization",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-triplep',
				 command_tests => [
						   {
						    description => "Can we serialize a triplep compartment passive model ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-triplep.txt`),
						    timeout => 15,
						   },
						  ],
				 description => "triplet passive compartment serialization.",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-fork3p',
				 command_tests => [
						   {
						    description => "Can we serialize a fork3p compartment passive model ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-fork3p.txt`),
						    timeout => 15,
						   },
						  ],
				 description => "fork3p fork of three passive compartments.",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-fork4p1',
				 command_tests => [
						   {
						    description => "Can we serialize a fork4p1 compartment passive model ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-fork4p1.txt`),
						    timeout => 8,
						   },
						  ],
				 description => "fork4p1 fork of four passive compartments, first alternative.",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-fork4p2',
				 command_tests => [
						   {
						    description => "Can we serialize a fork4p2 compartment passive model ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-fork4p2.txt`),
						    timeout => 8,
						   },
						  ],
				 description => "fork4p2 fork of four passive compartments, second alternative.",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-fork4p3',
				 command_tests => [
						   {
						    description => "Can we serialize a fork4p3 compartment passive model ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-fork4p3.txt`),
						    timeout => 8,
						   },
						  ],
				 description => "fork4p3 fork of four passive compartments, third alternative.",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-c1c2p1',
				 command_tests => [
						   {
						    description => "Can we serialize a c1c2p1 compartment passive model ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-c1c2p1.txt`),
						    timeout => 15,
						   },
						  ],
				 description => "c1c2p1 two passive compartments with injected current",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-c1c2p2',
				 command_tests => [
						   {
						    description => "Can we serialize a c1c2p2 compartment passive model ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-c1c2p2.txt`),
						    timeout => 15,
						   },
						  ],
				 description => "c1c2p2 two passive compartments with asymetric properties and injected current",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-tensizesp',
				 command_tests => [
						   {
						    description => "Can we serialize a tensizesp compartment passive model ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-tensizesp.txt`),
						    timeout => 18,
						   },
						  ],
				 description => "tensizesp ten passive compartments with different properties and injected current",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-singlea-naf',
				 command_tests => [
						   {
						    description => "Can we serialize a single compartment with a naf conductance ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-singlea-naf.txt`),
						    timeout => 15,
						   },
						  ],
				 description => "a single compartment with a naf conductance",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-pool2',
				 command_tests => [
						   {
						    description => "Can we serialize two compartments with two pools ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-pool2.txt`),
						    timeout => 15,
						   },
						  ],
				 description => "two compartments with two pools",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-pool1-feedback2',
				 command_tests => [
						   {
						    description => "Can we serialize a compartment with a pool with a feedback loop, reversed order ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-pool1-feedback2.txt`),
						    timeout => 15,
						   },
						  ],
				 description => "compartment with a pool with a feedback loop, reversed order",
# 				 disabled => 'temporary disabled for testing purposes',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-channel2-nernst2',
				 command_tests => [
						   {
						    description => "Can we serialize two solved nernst potentials applied for two channel reversal potentials ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/serialization-channel2-nernst2.txt`),
						    timeout => 15,
						   },
						  ],
				 description => "compartment with a pool with a feedback loop, reversed order",
# 				 disabled => 'temporary disabled for testing purposes',
				},
			       ),

			       # save - load tests with executable reload

			       (
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-save-singlep',
				 command_tests => [
						   {
						    description => "Can we save the state of a single compartment passive model ?",
						    read => "singlep-saved",
						   },
						  ],
				 description => "single compartment passive model serialization",
 				 disabled => 'needs implementation, low priority, see gshell tests',
				},
				{
				 arguments => [
					      ],
				 command => 'tests/code/serialization-load-singlep',
				 command_tests => [
						   {
						    description => "Can we load the state of a serialized single compartment passive model ?",
						    read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/singlep.txt`),
						   },
						  ],
				 description => "single compartment passive model serialization",
 				 disabled => 'needs implementation, low priority, see gshell tests',
				},
			       ),
			      ],
       description => "serialization",
       name => 'serialization.t',
      };


return $test;


