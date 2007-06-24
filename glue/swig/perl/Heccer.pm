#!/usr/bin/perl -w
#!/usr/bin/perl -w -d:ptkdb
#

package Heccer;


use strict;


# a default config at your convenience, not obligation to use it

our $config
    = {
       basal_activator_end => 0.3,
       basal_activator_start => 4e-5,
       interval_default_end => (0.05),
       interval_default_entries => 3000,
       interval_default_start => (-0.1),
       reporting => {
		     file => undef,
		     granularity => 1,
		     tested_things => $SwiggableHeccer::HECCER_DUMP_ALL,
		    },
       steps => 10,
       time_step => (2e-5),
      };


sub addressable
{
    my $self = shift;

    my $fieldinfo = shift;

    my $result = $self->{heccer}->HeccerAddressVariable($fieldinfo->{serial}, $fieldinfo->{type});

    return $result;
}


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
	if (!$self->compile1())
	{
	    return 0;
	}
    }

    return $self->compile2();
}


sub compile1
{
    my $self = shift;

    return $self->{heccer}->HeccerCompileP1();
}


sub compile2
{
    my $self = shift;

    return $self->{heccer}->HeccerCompileP2()

	&& $self->compile3();
}


sub compile3
{
    my $self = shift;

    return $self->{heccer}->HeccerCompileP3();
}


sub dump
{
    my $self = shift;

    #t not sure how it could be possible to use $file, but anyway,
    #t placeholder for the idea.

    my $file = shift;

    my $selection = shift;

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


sub finish
{
    my $self = shift;

    #! that is ok.
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

    #! note that ignored settings are ignore because of an empty translator.

    my $result = Heccer::Heccer::new($package, $settings, @_, );

    if (ref $result)
    {
	bless $result, $package;

	my $model_source = $settings->{model_source};

	if (exists $model_source->{service_name})
	{
	    my $service_name = $model_source->{service_name};

	    if ($service_name eq 'neurospaces')
	    {
		my $service_backend = $model_source->{service_backend}->backend();

		my $modelname = $model_source->{modelname};

		my $heccer_backend = $result->backend();

		my $success = SwiggableHeccer::HeccerConstruct($heccer_backend, $service_backend, $modelname);

		if (!$success)
		{
		    return "HeccerConstruct failed";
		}
	    }
	    else
	    {
		# no other services supported

		return "Heccer does only know neurospaces as a service.
If you need a different service, you have to install
the appropriate integrator plugin for Heccer, and let the perl
package know how to call the integrator.";
	    }
	}

	# if there was an intermediary

	if ($settings->{intermediary})
	{
	    # set status: HECCER_STATUS_PHASE_2

	    $result->{heccer}->swig_iStatus_set($SwiggableHeccer::HECCER_STATUS_PHASE_2);
	}
    }

    return $result;
}


sub report
{
    #t call ->dump() with dump options in this object.

    my $self = shift;

    my $options = shift;

    my $result = 1;

    if ($options->{verbose})
    {
	my $header;

	my $steps = $options->{steps};

	my $reporting = $self->{configuration}->{reporting};

	if (!defined $steps)
	{
	    $header = "Initiated\n";
	}
	else
	{
	    if ($steps eq -1)
	    {
		if ($self->{final_report})
		{
		    $header = "-------\nFinal Iteration\n";
		}
	    }
	    else
	    {
		my $reporting_granularity = $reporting->{granularity} || 1;

		if (($steps % $reporting_granularity) == 0)
		{
		    $header = "-------\nIteration $steps\n";
		}
		else
		{
		    $self->{final_report} = 1;
		}
	    }
	}

	if ($header)
	{
	    my $file = $reporting->{file};

	    if (defined $file)
	    {
		print $file $header;
	    }
	    else
	    {
		print $header;
	    }

	    my $tested_things = $reporting->{tested_things} || $SwiggableHeccer::HECCER_DUMP_ALL;

	    $result = $self->dump($file, $tested_things);
	}
    }

    return $result;
}


sub step
{
    return hecc(@_);
}


package Heccer::Component;


use SwiggableHeccer;


my $heccer_mapping
    = {
       activator => {
		     constructor_settings => {
					      iTable => -1,
					     },
		     internal_name => 'Activator',
		     translators => {
				     parameters => {
						    source => 'activator_parameters',
						    target => 'parameters',
						   },
				    },
		    },
       activator_parameters => {
				internal_name => 'ActivatorParameters',
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
								     iReversalPotential => -1,
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
								    iReversalPotential => -1,
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
						      piExternal => [
								     map { -1, } 1 .. $SwiggableHeccer::EXPONENTIALDECAY_CONTRIBUTORS,
								    ],
						     },
			     internal_name => 'ExponentialDecay',
			     translators => {
					     piExternal => {
							    convertor =>
							    sub
							    {
								my $target = shift;

								my $value = shift;

								my $result = SwiggableHeccer::int_array($SwiggableHeccer::EXPONENTIALDECAY_CONTRIBUTORS);

								foreach my $external_index (0 .. $SwiggableHeccer::EXPONENTIALDECAY_CONTRIBUTORS - 1)
								{
								    my $external = $value->[$external_index];

								    if (!defined $external)
								    {
									$external = -1;
								    }

								    SwiggableHeccer::int_set($result, $external_index, $external);
								}

								return $result;
							    },
							    target => 'piExternal',
							   },
					    },
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
					parameters => {
						       source => 'gate_concept_parameters',
						       target => 'parameters',
						      },
				       },
		       },
       gate_concept_parameters => {
				   internal_name => 'GateConceptParameters',
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
		  constructor_settings => {
					   dStep => 2e-5,
					   options => {
						       dBasalActivatorEnd => $SwiggableHeccer::HECCER_INTERVAL_BASAL_ACTIVATOR_DEFAULT_END,
						       dBasalActivatorStart => $SwiggableHeccer::HECCER_INTERVAL_BASAL_ACTIVATOR_DEFAULT_START,
						       dIntervalEnd => $SwiggableHeccer::HECCER_INTERVAL_DEFAULT_END,
						       dIntervalStart => $SwiggableHeccer::HECCER_INTERVAL_DEFAULT_START,
						       iIntervalEntries => $SwiggableHeccer::HECCER_INTERVAL_DEFAULT_ENTRIES,
						       iSmallTableSize => $SwiggableHeccer::HECCER_INTERPOL_INTERVAL_DEFAULT_ENTRIES,

						       #t the default at C level is wrong, needs a careful check.

# 						       iOptions => $SwiggableHeccer::HECCER_OPTION_BRANCHES_FIRST_SCHEDULING,
						      },
					  },
		  internal_name => 'Heccer',
		  translators => {
				  configuration => {
						   },
				  intermediary => {
						   target => 'inter',
						  },
				  model_source => {
						  },
				  options => {
					      source => 'options',
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

								my $types = SwiggableHeccer::int_array($#$value + 2);

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
		   constructor_settings => {
					    dBasalActivatorEnd => $SwiggableHeccer::HECCER_INTERVAL_BASAL_ACTIVATOR_DEFAULT_END,
					    dBasalActivatorStart => $SwiggableHeccer::HECCER_INTERVAL_BASAL_ACTIVATOR_DEFAULT_START,
					    dIntervalEnd => $SwiggableHeccer::HECCER_INTERVAL_DEFAULT_END,
					    dIntervalStart => $SwiggableHeccer::HECCER_INTERVAL_DEFAULT_START,
					    iIntervalEntries => $SwiggableHeccer::HECCER_INTERVAL_DEFAULT_ENTRIES,
					    iSmallTableSize => $SwiggableHeccer::HECCER_INTERPOL_INTERVAL_DEFAULT_ENTRIES,

					    #t the default at C level is wrong, needs a careful check.

# 					    iOptions => $SwiggableHeccer::HECCER_OPTION_BRANCHES_FIRST_SCHEDULING,
					   },
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

# 	if (ref $value eq 'HASH')
# 	{
# 	    no strict "refs";

# 	    my $Component = identifier_perl_to_xml($target);

# 	    my $constructor = "Heccer::${Component}::new";

# 	    $value = &$constructor($Component, $value);
# 	}

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

	    #! so the constructor_settings entry applies this hook too,
	    #! and perhaps already created the object

	    elsif ($translator->{source})
	    {
		# if still needs translation

		if (!exists $value->{$translator->{source}})
		{
		    # get the factory method for the target object

		    my $source = $translator->{source};

		    my $factory_source = "Heccer::" . identifier_perl_to_xml($source);

		    # translate the source structure to a target object

		    $value = $factory_source->new($value);

		    # fetch the target object

		    $value = $value->{$source};
		}

		# else the constructor_settings has already constructed the target object

		else
		{
		    # fetch the target object

		    $value = $value->{$setting};
		}
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
	    # the convertor has done the necessary setting, or a void

	    #! see e.g. configuration, module_name and service_name for the heccer entry

	    # but it is useful to keep the original

	    #! allows to set runtime configuration options

	    $self->{$setting} = $settings->{$setting};
	}
    }

    return $self;
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


package Heccer::Output;


sub add
{
    my $self = shift;

    my $options = shift;

    my $backend = $self->backend();

    my $name
	= $options->{service_request}->{component_name}
	    . "__"
		. $options->{service_request}->{field};

    $name =~ s/\//____/g;
#     $name =~ s/\>/__/g;
#     $name =~ s/\-//g;

    my $result = $backend->OutputGeneratorAddVariable($name, $options->{address});

    return $result;
}


sub advance
{
    my $self = shift;

    #t call the appropriate method or something

    return 1;
}


sub backend
{
    my $self = shift;

    return $self->{backend};
}


sub finish
{
    my $self = shift;

    # close files, free memory

    my $backend = $self->backend();

    $backend->OutputGeneratorFinish();
}


sub initiate
{
    my $self = shift;

    #t could create the files here ?
}


sub new
{
    my $package = shift;

    my $options = shift;

    my $self = { %$options, };

    bless $self, $package;

    if (!defined $self->{filename})
    {
	$self->{filename} = "/tmp/OutputGenerator";
    }

    $self->{backend} = SwiggableHeccer::OutputGeneratorNew($self->{filename});

    if (!defined $self->{backend})
    {
	return undef;
    }

    return $self;
}


sub report
{
    my $self = shift;

    #t nothing I guess ?
}


sub step
{
    my $self = shift;

    my $options = shift;

    my $backend = $self->backend();

    my $result = $backend->OutputGeneratorAnnotatedStep("$options->{steps}");

    return $result;
}


1;


