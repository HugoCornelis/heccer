#   (library/gates/k2_concentration.ndf (neurospaces/n/23_k2_concent 1.1 644))
#   (library/gates/k2_activation.ndf (neurospaces/n/24_k2_activat 1.1 644))
#   (library/gates/cap_inactivation.ndf (neurospaces/n/27_cap_inacti 1.1 644))
#   (library/gates/cap_activation.ndf (neurospaces/n/28_cap_activa 1.1 644))
#   (library/gates/nap_activation.ndf (neurospaces/n/29_nap_activa 1.1 644))
# **** cacKC
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
				command => 'tests/code/table-naf',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, simple sodium gates ?",
						   read => [ `cat $::config->{core_directory}/tests/library/strings/table-naf.txt`, ],
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "Simple sodium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-cap',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, persistent calcium gates ?",
						   read => [ `cat $::config->{core_directory}/tests/library/strings/table-cap.txt`, ],
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "Persistent Calcium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-cat',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, calcium t-type gates ?",
						   read => [ `cat $::config->{core_directory}/tests/library/strings/table-cat.txt`, ],
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "Calcium t-type gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-ka',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, simple potassium gates ?",
						   read => [ `cat $::config->{core_directory}/tests/library/strings/table-ka.txt`, ],
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "Simple potassium gate tabulation",
			       },
			       {
				arguments => [
					     ],
				command => 'tests/code/table-kdr',
				command_tests => [
						  {
						   description => "Are gates tabulated correctly, delayed rectifier potassium gates ?",
						   read => [ `cat $::config->{core_directory}/tests/library/strings/table-kdr.txt`, ],
						   timeout => 18,
						   write => undef,
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
						   read => [ `cat $::config->{core_directory}/tests/library/strings/table-kh.txt`, ],
						   timeout => 18,
						   write => undef,
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
						   read => [ `cat $::config->{core_directory}/tests/library/strings/table-km.txt`, ],
						   timeout => 18,
						   write => undef,
						  },
						 ],
				description => "Muscarinic potassium gate tabulation",
			       },
			      ],
       description => "Gate tabulation",
       name => 'tables.t',
      };


return $test;


