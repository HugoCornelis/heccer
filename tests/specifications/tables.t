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
				command => 'tests/code/table-cap',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, p type calcium gates ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/table-cap.txt`),
						   timeout => 18,
						  },
						 ],
				description => "p type calcium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-cat',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, calcium t-type gates ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/table-cat.txt`),
						   timeout => 18,
						  },
						 ],
				description => "Calcium t-type gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-k2',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, K2 potassium gates ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/table-k2.txt`),
						   timeout => 18,
						  },
						 ],
				description => "K2 potassium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-ka',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, simple potassium gates (1)?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/table-ka.txt`),
						   timeout => 18,
						  },
						 ],
				description => "Simple potassium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-kc',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, simple potassium gates (2)?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/table-kc.txt`),
						   timeout => 18,
						  },
						 ],
				description => "Calcium dependent potassium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-kdr',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, delayed rectifier potassium gates ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/table-kdr.txt`),
						   timeout => 18,
						  },
						 ],
				description => "Delayed rectifier potassium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-kdr2',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, regular delayed rectifier potassium gates ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/table-kdr2.txt`),
						   timeout => 18,
						  },
						 ],
				description => "Delayed rectifier potassium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-kh',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, anomalous rectifier potassium gates ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/table-kh.txt`),
						   timeout => 18,
						  },
						 ],
				description => "Anomalous rectifier potassium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-km',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, muscarinic potassium gates ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/table-km.txt`),
						   timeout => 18,
						  },
						 ],
				description => "Muscarinic potassium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-naf',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, simple sodium gates ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/table-naf.txt`),
						   timeout => 18,
						  },
						 ],
				description => "Simple sodium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-nap',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, persistent sodium gates ?",
						   read => (join '', `cat $::global_config->{core_directory}/tests/specifications/strings/table-nap.txt`),
						   timeout => 18,
						  },
						 ],
				description => "Persistent sodium gate tabulation",
			       },
			      ],
       description => "Gate tabulation",
       name => 'tables.t',
      };


return $test;


