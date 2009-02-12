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
				command => 'tests/code/addressing-purk-test-segment',
				command_tests => [
						  {
						   description => "Are the variables in an simplified version of a purkinje segment segment addressed correctly ?",
						   read => ((join '', `cat $::config->{core_directory}/heccer/config.h` =~ m/define\s+HECCER_SOURCE_NEUROSPACES/)
							    ? (join '', `cat $::config->{core_directory}/tests/specifications/strings/addressing-purk-test-segment--with-neurospaces.txt`)
							    : (join '', `cat $::config->{core_directory}/tests/specifications/strings/addressing-purk-test-segment--without-neurospaces.txt`)),
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "addressing variables for a simplified version of a purkinje segment",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/addressing-synchan',
				command_tests => [
						  {
						   description => "Is synchan activation addressed correctly ?",
						   disabled => ((join '', `cat $::config->{core_directory}/heccer/config.h` =~ m/define\s+HECCER_SOURCE_NEUROSPACES/)
								 ? ''
								 : 'HECCER_SOURCE_NEUROSPACES is disabled'),
						   read => '
0 0
1 0
2 0
3 0
4 0
5 0
6 0
7 0
8 0
9 0
10 0.970462
11 0.951245
12 0.932409
13 0.913946
14 0.895849
15 0.87811
16 0.860722
17 0.843679
18 0.826973
19 0.810598
20 0.794547
21 0.778814
22 0.763392
23 0.748276
24 0.733459
25 0.718936
26 0.7047
27 0.690746
28 0.677068
29 0.663661
',
						   timeout => 5,
						   write => undef,
						  },
						 ],
				description => "addressing synchan activation",
			       },
			      ],
       description => "internal and external addressing of variables",
       name => 'addressing.t',
      };


return $test;


