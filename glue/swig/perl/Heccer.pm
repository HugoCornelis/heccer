#!/usr/bin/perl -w
#!/usr/bin/perl -w -d:ptkdb
#

package Heccer;


sub compile
{
    my $self = shift;

    my $options = shift;

    my $status = $self->{heccer}->swig_iStatus_get();

    $self->compile2();
}


sub compile2
{
    my $self = shift;

    $self->{heccer}->HeccerCompileP2();

    $self->compile3();
}


sub compile3
{
    my $self = shift;

    $self->{heccer}->HeccerCompileP3();
}


sub dump
{
    my $self = shift;

    my $selection = shift;

    #t not sure how it could be possible to use $file, but anyway,
    #t placeholder for the idea.

    my $file = shift;

    if (!defined $selection)
    {
	$self->{heccer}->HeccerDumpV();
    }
    else
    {
	$self->{heccer}->HeccerDump($file, $selection);
    }
}


sub hecc
{
    my $self = shift;

    $self->{heccer}->HeccerHecc();
}


sub initiate
{
    my $self = shift;

    $self->{heccer}->HeccerInitiate();
}


sub new
{
    my $package = shift;

    my $settings = shift;

    my $result = Heccer::Heccer::new($package, $settings, @_, );

    if (ref $result)
    {
	bless $result, $package;

	# if there was an intermediary

	if ($settings->{intermediary})
	{
	    # set status: HECCER_STATUS_PHASE_2

	    $result->{heccer}->swig_iStatus_set(20);
	}
    }

    return $result;
}


package Heccer::Component;


use SwiggableHeccer;


#t I would like to be able to use MATH_TYPE_Compartment for the type_numbers here.
#t
#t MATH_TYPE_Compartment because of strict subs
#t SwiggableHeccer::MATH_TYPE_Compartment because of strict subs
#t Heccerc::MATH_TYPE_Compartment fails because it returns 0 instead of 1.

my $heccer_mapping
    = {
       callout => {
		   internal_name => 'Callout',
		   translators => {
				   external_function => {
							 target => 'pef',
							 convertor =>
							 sub
							 {
							     my $target = shift;

							     my $value = shift;

							     return $value;
							 },
							},
				   external_results => {
							target => 'per',
						       },
				   internal_results => {
							target => 'pir',
						       },
				  },
		   type_number => ( 0x8000 | 2 ),
		  },
       compartment => {
		       internal_name => 'Compartment',
		       type_number => 1,
		      },
#        external_function => {
# 			    },
       external_results => {
			    internal_name => 'ExternalResults',
			   },
       heccer => {
		  internal_name => 'Heccer',
		  translators => {
				  intermediary => {
						   target => 'inter',
						  },
				  options => {
					      target => 'ho',
					     },
				 },
		 },
       intermediary => {
			internal_name => 'Intermediary',
			translators => {
					compartments => {
							 target => 'pcomp',
							 convertor =>
							 sub
							 {
							     my $target = shift;

							     my $value = shift;

							     my $result = SwiggableHeccer::comp_array($#$value + 1);

							     foreach my $compartment_index (0 .. $#$value)
							     {
								 my $compartment = $value->[$compartment_index];

								 SwiggableHeccer::comp_set($result, $compartment_index, $compartment->{compartment});
							     }

							     return $result;
							 },
							},
					comp2mech => {
						      target => 'piC2m',
						      convertor =>
						      sub
						      {
							  my $target = shift;

							  my $value = shift;

							  my $result = SwiggableHeccer::int_array($#$value + 1);

							  foreach my $compartment_index (0 .. $#$value)
							  {
							      my $compartment_start = $value->[$compartment_index];

							      SwiggableHeccer::int_set($result, $compartment_index, $compartment_start);
							  }

							  return $result;
						      },
						     },
				       },
		       },
       internal_results => {
			    internal_name => 'InternalResults',
			   },
       options => {
		   internal_name => 'HeccerOptions',
		  },
      };


sub new
{
    my $package = shift;

    my $subpackage = shift;

    my $type = shift;

    my $settings = shift;

    if (!exists $heccer_mapping->{$type})
    {
	return "$type is not a Heccer::Component";
    }

    # create the heccer internal object

    my $internal_name = $heccer_mapping->{$type}->{internal_name};

    my $factory_package = "SwiggableHeccer::$internal_name";

    my $self
	= {
	   $type => $factory_package->new(),
	  };

    # never forget to set the heccer type

    my $type_number = $heccer_mapping->{$type}->{type_number};

    if ($type_number)
    {
	my $mc = $self->{$type}->swig_mc_get();

	$mc->swig_iType_set($type_number);
    }

    # just apply all the settings, the missing ones are under
    # control of heccer

    foreach my $setting (keys %$settings)
    {
	# get target name in heccer internal

	my $target = $setting;

	my $value = $settings->{$setting};

	# if there is a translator for this setting

	my $translator = $heccer_mapping->{$type}->{translators}->{$setting};

	if ($translator)
	{
	    # translate the target

	    $target = $translator->{target};

	    # translate the value

	    my $convertor = $translator->{convertor};

	    # for a custom value convertor

	    if ($convertor)
	    {
		# call custom value convertor

		$value = &$convertor($target, $value);;
	    }

	    # else

	    else
	    {
		# default is dereference via the setting name, which
		# presumably gives the heccer internal structure

		$value = $value->{$setting};
	    }
	}

	# set the heccer internal target

	my $subname = "swig_${target}_set";

	$self->{$type}->$subname($value);
    }

    # return result

    bless $self, $package;
}


sub identifier_xml_to_perl
{
    my $identifier = shift;

    my $result = $identifier;

    $result =~ s/([A-Z]{2,})([A-Z])/_\L$1\E$2/g;

    $result =~ s/([A-Z])(?![A-Z])/_\l$1/g;

    return $result;
}


sub identifier_perl_to_xml
{
    my $identifier = shift;

    my $result = $identifier;

    $result =~ s/^([a-z])/\u$1/;

    $result =~ s/_([a-z0-9])/\u$1/g;

    return $result;
}


# construct factory method for each Heccer component

foreach my $component (keys %$heccer_mapping)
{
    my $Component = identifier_perl_to_xml($component);

    print "For $component -> $Component\n";

    my $code = "
package Heccer::$Component;

sub new
{
    my \$package = shift;

    my \$result = Heccer::Component->new(\$package, '$component', \@_, );

    if (ref \$result)
    {
	return bless \$result, \$package;
    }
    else
    {
	return \$result;
    }
}

";

    my $result = eval $code;

    if ($@)
    {
	die "In Heccer.pm: error constructing $component factory methods: $@";
    }
}


1;


