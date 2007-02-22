#!/usr/bin/perl -w
#!/usr/bin/perl -w -d:ptkdb
#

package Heccer;


# a default config at your convenience, not obligation to use it

our $config
    = {
       basal_activator_end => 0.3,
       basal_activator_start => 4e-5,
       interval_default_end => (0.05),
       interval_default_entries => 3000,
       interval_default_start => (-0.1),
       reporting_granularity => 1,
       steps => 10,
       tested_things => $SwiggableHeccer::HECCER_DUMP_ALL,
       time_step => (2e-5),
      };

sub advance
{
    my $self = shift;

    my $time = shift;

    my $result = $self->{heccer}->HeccerHeccs($time);

    return $result;
}


sub backend
{
    my $self = shift;

    return $self->{heccer};
}


sub compile
{
    my $self = shift;

    my $options = shift;

    my $status = $self->{heccer}->swig_iStatus_get();

    if ($status le $SwiggableHeccer::HECCER_STATUS_PHASE_1)
    {
	$self->compile1();
    }

    $self->compile2();
}


sub compile1
{
    my $self = shift;

    $self->{heccer}->HeccerCompileP1();
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

    my $constructor = $settings->{constructor} || "Heccer::Heccer::new";

    my $result;

    if (exists $settings->{service_name}
	&& $settings->{service_name} eq 'neurospaces')
    {
	$result = $package->new_neurospaces($settings, @_, );
    }
    else
    {
	no strict "refs";

	$result = &$constructor($package, $settings, @_, );
    }

    if (ref $result)
    {
	bless $result, $package;

	# if there was an intermediary

	if ($settings->{intermediary})
	{
	    # set status: HECCER_STATUS_PHASE_2

	    $result->{heccer}->swig_iStatus_set($SwiggableHeccer::HECCER_STATUS_PHASE_2);
	}
    }

    return $result;
}


#t the need for an additional adapter is really lame ...

sub new_neurospaces
{
    my $package = shift;

    my $settings = shift;

    my $others = { @_, };

    #! note that the constructor setting is entirely ignored

    my $service_backend = $settings->{service_backend}->backend();

    my $modelname = $settings->{modelname};

    my $result
	= {
	   heccer => SwiggableHeccer::HeccerConstruct($service_backend, $modelname),
	  };

    bless $result, $package;

    # return result

    return $result;
}


sub step
{
    return hecc(@_);
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
       activator => {
		     internal_name => 'Activator',
		     constructor_settings => {
					      iTable => -1,
					     },
		    },
       callout => {
		   internal_name => 'Callout',
		   translators => {
				   external_function => {
							 convertor =>
							 sub
							 {
							     my $target = shift;

							     my $value = shift;

							     return $value;
							 },
							 target => 'pef',
							},
				   external_results => {
							target => 'per',
						       },
				   internal_results => {
							target => 'pir',
						       },
				  },
		   type_number => $SwiggableHeccer::MATH_TYPE_CallOut_conductance_current,
		  },
       channel_activation_concentration => {
					    constructor_settings => {
								     iPool => -1,
								    },
					    internal_name => 'ChannelActConc',
					    translators => {
							    activation => {
									   source => 'powered_gate_concept',
									   target => 'pgc',
									  },
							    powered_activator => {
										  source => 'powered_activator_concept',
										  target => 'pac',
										 },
							   },
					    type_number => $SwiggableHeccer::MATH_TYPE_ChannelActConc,
					   },
       channel_activation_inactivation => {
					   constructor_settings => {
								    iPool => -1,
								   },
					   internal_name => 'ChannelActInact',
					   translators => {
							   activation => {
									  source => 'powered_gate_concept',
									  target => 'pgcActivation',
									 },
							   inactivation => {
									    source => 'powered_gate_concept',
									    target => 'pgcInactivation',
									   },
							  },
					   type_number => $SwiggableHeccer::MATH_TYPE_ChannelActInact,
					  },
       compartment => {
		       constructor_settings => {
						iParent => -1,
					       },
		       internal_name => 'Compartment',
		       type_number => $SwiggableHeccer::MATH_TYPE_Compartment,
		      },
       exponential_decay => {
			     constructor_settings => {
						      iExternal => -1,
						     },
			     internal_name => 'ExponentialDecay',
			     type_number => $SwiggableHeccer::MATH_TYPE_ExponentialDecay,
			    },
#        external_function => {
# 			    },
       external_results => {
			    internal_name => 'ExternalResults',
			   },
       gate_concept => {
			constructor_settings => {
						 iTable => -1,
						},
			internal_name => 'GateConcept',
			translators => {
					backward => {
						     source => 'gate_kinetic',
						     target => 'gkBackward',
						    },
					forward => {
						    source => 'gate_kinetic',
						    target => 'gkForward',
						   },
				       },
		       },
       gate_kinetic => {
			internal_name => 'GateKinetic',
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
							 convertor =>
							 sub
							 {
							     my $target = shift;

							     my $value = shift;

							     my $result = SwiggableHeccer::comp_array($#$value + 1);

							     foreach my $compartment_index (0 .. $#$value)
							     {
								 my $compartment = $value->[$compartment_index];

								 my $ref = ref $compartment;

								 if ($ref =~ /^HASH/)
								 {
								     $compartment = Heccer::Compartment->new($compartment);
								 }

								 SwiggableHeccer::comp_set($result, $compartment_index, $compartment->{compartment});
							     }

							     return $result;
							 },
							 target => 'pcomp',
							},
					comp2mech => {
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
						      target => 'piC2m',
						     },
					math_components => {
							    convertor =>
							    sub
							    {
								my $target = shift;

								my $value = shift;

								my $result = Heccer::MathComponentArray->new( { iMathComponents => 0, } );

								my $types = SwiggableHeccer::int_array($#$value + 1);

								foreach my $math_component_index (0 .. $#$value)
								{
								    #! sure that if this confesses, the user is going to go a long way to figure out why

								    my $type = $value->[$math_component_index]->heccer_object()->swig_mc_get()->swig_iType_get();

								    SwiggableHeccer::int_set($types, $math_component_index, $type);
								}

								SwiggableHeccer::int_set($types, $#$value + 1, -1);

								$result->heccer_object()->MathComponentArrayCallocData($types);

								foreach my $math_component_index (0 .. $#$value)
								{
								    my $mc = $value->[$math_component_index]->heccer_object()->swig_mc_get();

								    $result->heccer_object()->MathComponentArraySetAdvance($mc);
								}

								# the math_component array will be set in the intermediary at C level,
								# so perl should not touch it anymore.

								$result->heccer_object()->DISOWN();

								return $result->heccer_object();
							    },
							    target => 'pmca',
							   },
				       },
		       },
       internal_results => {
			    internal_name => 'InternalResults',
			   },
       math_component_array => {
				internal_name => 'MathComponentArray',
			       },
       options => {
		   internal_name => 'HeccerOptions',
		  },
       powered_activator_concept => {
				     internal_name => 'PoweredActivatorConcept',
				     translators => {
						     activator => {
								   source => 'activator',
								   target => 'ac',
								  },
						    },
				    },
       powered_gate_concept => {
				internal_name => 'PoweredGateConcept',
				translators => {
						gate_concept => {
								 source => 'gate_concept',
								 target => 'gc',
								},
					       },
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

    # base initialization done

    #! implicit assumption that this is a Heccer::Component, but can be overriden

    bless $self, $package;

    # apply constructor settings

    $self->settings($type, $heccer_mapping->{$type}->{constructor_settings});

    # apply user settings

    $self->settings($type, $settings);

    # return result

    return $self;
}


sub settings
{
    my $self = shift;

    my $type = shift;

    my $settings = shift;

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

	    # for a custom value convertor

	    if ($translator->{convertor})
	    {
		# call custom value convertor

		my $convertor = $translator->{convertor};

		$value = &$convertor($target, $value);;
	    }

	    # for a simple source to target translator

	    elsif ($translator->{source})
	    {
		# get the factory method for the target object

		my $source = $translator->{source};

		my $factory_source = "Heccer::" . identifier_perl_to_xml($source);

		# translate the source structure to a target object

		$value = $factory_source->new($value);

		$value = $value->{$source};
	    }

	    # else

	    else
	    {
		# default is dereference via the setting name, which
		# presumably gives the heccer internal structure

		$value = $value->{$setting};
	    }
	}

	# if there was a target

	if (defined $target)
	{
	    # set the heccer internal target

	    my $subname = "swig_${target}_set";

	    $self->{$type}->$subname($value);
	}

	# else

	else
	{
	    # the convertor has done the necessary setting, void here
	}
    }
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

#     print "For $component -> $Component\n";

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


sub heccer_object
{
    my \$self = shift;

    my \$result = \$self->{$component};

    return \$result;
}


";

    my $result = eval $code;

    if ($@)
    {
	die "In Heccer.pm: error constructing $component factory methods: $@";
    }
}


1;


