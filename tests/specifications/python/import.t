#!/usr/bin/perl -w
#

use strict;


my $test
    = {
       command_definitions => [
			       {
				arguments => [
					     ],
				command => 'tests/python/import_test.py',
				command_tests => [
						  {
						   description => "Can we import the heccer module and it's base class ?",
						   read => 'Importing heccer_base
Importing Heccer
Done!
',
						  },
						 ],
				description => "a simple application that imports the built heccer python modules",
			       },

			       {
				arguments => [
					     ],
				command => 'tests/python/import_test_1.py',
				disabled => 'Disabling this until the standard location installation is done.',
				command_tests => [
						  {
						   description => "Can we import the heccer module and it's base class from the installed location ?",
						   read => 'Importing heccer_base
Importing Heccer
Done!
',
						  },
						 ],
				description => "A simple application that imports the built heccer python modules from /usr/local/glue/swig/python",
			       },

			      ],
       description => "Simple python functionality tests",
       name => 'python/import.t',
      };


return $test;


