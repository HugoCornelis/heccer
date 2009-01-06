#!/usr/bin/perl -w
#!/usr/bin/perl -w -d:ptkdb
#

package Heccer;


use strict;


# a default config at your convenience, not obligation to use it

our $config
    = {
       concentration_gate_end => 0.3,
       concentration_gate_start => 4e-5,
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


# sub advance
# {
#     my $self = shift;

#     my $scheduler = shift;

#     my $time = shift;

#     my $result = $self->{heccer}->HeccerHeccs($time);

#     return $result;
# }


sub backend
{
    my $self = shift;

    return $self->{heccer};
}


sub compile
{
    my $self = shift;

    my $scheduler = shift;

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


sub deserialize2
{
    my $old_self = shift;

    my $filename = shift;

    my $backend = SwiggableHeccer::HeccerDeserializeFromFilename($filename);

    my $self
	= {
	   %$old_self,
	   heccer => $backend,
	  };

    bless $self, __PACKAGE__;

    return $self;
}


sub deserialize_state
{
    my $self = shift;

    my $filename = shift;

    my $result = 1;

    my $backend = $self->backend();

    my $file = SwiggableHeccer::HeccerSerializationOpenRead($filename);

    $result = $result && $backend->HeccerDeserializeCompartmentState($file);

    $result = $result && $backend->HeccerDeserializeMechanismState($file);

    if (SwiggableHeccer::HeccerSerializationClose($file) != 0)
    {
	$result = 0;
    }

    return $result;
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

    my $current_time = $self->{heccer}->swig_dTime_get();

    my $current_step = $self->{heccer}->swig_dStep_get();

    my $small_thing = $current_step / 2;

    my $target_time = $current_time + $current_step - $small_thing;

    $self->{heccer}->HeccerHeccs($target_time);
}


sub finish
{
    my $self = shift;

    #! that is ok.
}


sub get_driver
{
    my $self = shift;

    my $result
	= {
	   data => $self->{heccer}->heccer_get_driver_data(),
	   method => $self->{heccer}->heccer_get_driver_method(),
# 	   data => \&SwiggableHeccer::HeccerHeccs$self->{heccer},
# 	   method => \&SwiggableHeccer::HeccerHeccs,
	  };

    return $result;
}


sub get_time_step
{
    my $self = shift;

    # get time step from the low level solver

    my $result = $self->{heccer}->swig_dStep_get();

    # return result

    return $result;
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

    #! note that ignored settings are ignored because of an empty translator.

    #! what setting keys get ignored again ?

    my $result = Heccer::Heccer::new($package, $settings, @_, );

    # if construction was successful

    if (ref $result)
    {
	bless $result, $package;

	my $event_distributor_backend;

	if ($settings->{event_distributor}->{event_distributor_backend})
	{
	    $event_distributor_backend = $settings->{event_distributor}->{event_distributor_backend}->backend();
	}

	# if there is a model source

	my $model_source = $settings->{model_source};

	if (exists $model_source->{service_name})
	{
	    # if setting up from the neurospaces model container

	    my $service_name = $model_source->{service_name};

	    if ($service_name eq 'neurospaces')
	    {
		my $service_backend = $model_source->{service_backend}->backend();

		my $modelname = $model_source->{modelname};

		my $heccer_backend = $result->backend();

		# setup the interface to build an intermediary

		my $success = SwiggableHeccer::HeccerConstruct($heccer_backend, $service_backend, $modelname, $event_distributor_backend);

		if (!$success)
		{
		    return "HeccerConstruct from neurospaces failed";
		}

		# if there was an intermediary

		if ($settings->{intermediary})
		{
		    # set status: HECCER_STATUS_PHASE_2

		    $result->{heccer}->swig_iStatus_set($SwiggableHeccer::HECCER_STATUS_PHASE_2);
		}
	    }

	    # if setting up from an inlined heccer_intermediary

	    elsif ($service_name eq 'heccer_intermediary')
	    {
		# get reference to the inlined heccer_intermediary

		my $service_backend = $model_source->{service_backend};

		my $intermediary = $service_backend->backend();

		# get low-level intermediary

		my $intermediary_backend = $intermediary->backend();

		my $modelname = $model_source->{modelname};

		# link the heccer with the intermediary

		my $heccer_backend = $result->backend();

		$heccer_backend->swig_inter_set($intermediary_backend);

		$heccer_backend->swig_iStatus_set($SwiggableHeccer::HECCER_STATUS_PHASE_2);

		my $success = 1;

		if (!$success)
		{
		    return "HeccerConstruct from heccer_intermediary failed";
		}
	    }
	    else
	    {
		# no other services supported

		return
"Heccer does only know neurospaces as a service.
If you need a different service, you have to install
the appropriate integrator plugin for Heccer,
and let the perl package know how to call the integrator.";
	    }
	}

	# if was a direct initialization

	else
	{
	    # if there was an intermediary

	    if ($settings->{intermediary})
	    {
		# set status: HECCER_STATUS_PHASE_2

		$result->{heccer}->swig_iStatus_set($SwiggableHeccer::HECCER_STATUS_PHASE_2);
	    }
	}
    }

    return $result;
}


sub report
{
    #t call ->dump() with dump options in this object.

    my $self = shift;

    my $scheduler = shift;

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


sub set_addressable
{
    my $self = shift;

    my $fieldinfo = shift;

    my $value = shift;

    my $result = $self->{heccer}->HeccerAddressableSet($fieldinfo->{serial}, $fieldinfo->{type}, $value);

    return $result;
}


sub serialize
{
    my $self = shift;

    my $filename = shift;

    my $backend = $self->backend();

    return $backend->HeccerSerializeToFilename($filename);
}


sub serialize_state
{
    my $self = shift;

    my $filename = shift;

    my $result = 1;

    my $backend = $self->backend();

    my $file = SwiggableHeccer::HeccerSerializationOpenWrite($filename);

    $result = $result && $backend->HeccerSerializeCompartmentState($file);

    $result = $result && $backend->HeccerSerializeMechanismState($file);

    if (SwiggableHeccer::HeccerSerializationClose($file) != 0)
    {
	$result = 0;
    }

    return $result;
}


sub step
{
    return hecc(@_);
}


sub version
{
    # $Format: "    my $version=\"${package}-${label}\";"$
    my $version="heccer-python-3";

    return $version;
}


package Heccer::Component;


use SwiggableHeccer;


my $heccer_mapping
    = {
       concentration_activator => {
				   constructor_settings => {
							    iTable => -1,
							   },
				   internal_name => 'ConcentrationActivator',
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
						   A => {
							 source => 'gate_kinetic',
							 target => 'gkA',
							},
						   B => {
							 source => 'gate_kinetic',
							 target => 'gkB',
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
						       dConcentrationGateEnd => $SwiggableHeccer::HECCER_INTERVAL_CONCENTRATION_GATE_DEFAULT_END,
						       dConcentrationGateStart => $SwiggableHeccer::HECCER_INTERVAL_CONCENTRATION_GATE_DEFAULT_START,
						       dIntervalEnd => $SwiggableHeccer::HECCER_INTERVAL_DEFAULT_END,
						       dIntervalStart => $SwiggableHeccer::HECCER_INTERVAL_DEFAULT_START,
						       iIntervalEntries => $SwiggableHeccer::HECCER_INTERVAL_DEFAULT_ENTRIES,
						       iSmallTableSize => $SwiggableHeccer::HECCER_INTERPOL_INTERVAL_DEFAULT_ENTRIES,

						       #t the default at C level is wrong, needs a careful check.

# 						       iOptions => $SwiggableHeccer::HECCER_OPTION_BRANCHES_FIRST_SCHEDULING,
						      },

					   #! this is mainly to get the tests to work ...

					   pcName => "unnamed test",
					  },
		  internal_name => 'Heccer',
		  translators => {
				  configuration => {
						   },

				  #t event_distributor, see model_source comments below

				  event_distributor => {
						       },

				  intermediary => {
						   target => 'inter',
						  },

				  # model_source comes from SSP, should not be translated

				  #t we should use this to translate the model_source into the TranslationServiceData or so

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

								#! why again +2: 1 is from the perl $#$ operator offset, the other 1 is for the terminating -1

								my $types = SwiggableHeccer::int_array($#$value + 2);

								# loop over all given value entries

								foreach my $math_component_index (0 .. $#$value)
								{
								    my $type = $value->[$math_component_index]->heccer_object()->swig_mc_get()->swig_iType_get();

								    SwiggableHeccer::int_set($types, $math_component_index, $type);
								}

								# set the terminating -1 in the types array

								SwiggableHeccer::int_set($types, $#$value + 1, -1);

								# allocate a math component array for these types

								$result->heccer_object()->MathComponentArrayCallocData($types);

								# loop over all given value entries

								foreach my $math_component_index (0 .. $#$value)
								{
								    # copy the memory of the low level entry

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
					    dConcentrationGateEnd => $SwiggableHeccer::HECCER_INTERVAL_CONCENTRATION_GATE_DEFAULT_END,
					    dConcentrationGateStart => $SwiggableHeccer::HECCER_INTERVAL_CONCENTRATION_GATE_DEFAULT_START,
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
						     concentration_activator => {
										 source => 'concentration_activator',
										 target => 'ca',
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
    # default control of the C code

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


sub backend
{
    my \$self = shift;

    my \$result = \$self->{$component};

    return \$result;
}


";

    my $result = eval $code;

    if ($@)
    {
	die "$0: In Heccer.pm: error constructing $component factory methods: $@";
    }
}


package Heccer::DES::Distributor;


BEGIN { our @ISA = qw(Heccer::Glue); }


sub add_output
{
    my $self = shift;

    my $outputclass = shift;

#! normally done automatically during ->instantiate_outputs()

#     pogSpike = OutputGeneratorNew("/tmp/output_spike");

#! normally done automatically by Heccer::Event::Output::add

#     double *pdSpike = HeccerAddressMechanismVariable(pheccer, 2, "spike"); \
#     OutputGeneratorAddVariable(pogSpike, "spike", pdSpike)


#! should be done here: fill in in heccer intermediary

#     //m table in event distributor with targets

#     0,


#! should be done here

#     //- link spiking element to output generator

#     pogSpike = OutputGeneratorNew("/tmp/output_spike");

#     pedm[0].pvObject = pogSpike;
#     pedm[0].pvFunction = OutputGeneratorTimedStep;


    # lookup the backend for the output

    my $scheduler = $outputclass->{scheduler};

    my $output_backend = $outputclass->backend();

    # add the output object to the connection matrix

    my $distributor = $self->{backend};

    #! argument value 1: sets the output function

    my $result = $distributor->EventDistributorAddConnection($output_backend, 1);

    # return result

    return $result;
}


sub compile
{
    my $self = shift;

    my $peer = shift;

    my $options = shift;

#     my $distributor; # $scheduler->lookup_service('event_distributor');

    # construct a connection matrix

    my $scheduler = $peer->{scheduler};

    my $outputs = $scheduler->{outputs};

    my $connections = scalar grep { $_->{distributor_service} } @$outputs;

    my $connection_matrix = SwiggableHeccer::EventDistributorDataNew($connections);

    $self->{backend} = SwiggableHeccer::EventDistributorNew($connection_matrix);

    if (!defined $self->{backend})
    {
	return undef;
    }

    # lookup service

    my $service = $scheduler->lookup_object($options->{service});

    my $service_backend = $service->backend();

    # fill in the serials in the connection matrix

    my $count = 0;

    foreach my $output (grep { $_->{distributor_service} } @$outputs)
    {
	# get output component name

	my $component_name = $output->{component_name};

	# convert to serial

	my $serial = $service_backend->component_2_serial($component_name);

	if (!defined $serial)
	{
	    die "$0: Component_name $component_name cannot be found during DES output compilation";
	}

	# fill in the entry

	my $entry = $connection_matrix->EventDistributorDataGetEntry($count);

	$entry->swig_iSerial_set($serial);

	$count++;
    }

    # fill in a default send function

    if (!$self->{backend}->EventDistributorInitiate(1))
    {
	die "$0: error setting up the event distributor, EventDistributorInitiate() failed";
    }

#     $self->{backend}->swig_eventDistribute_set(\&SwiggableHeccer::EventDistributorSend);

#     $self->{backend}->swig_pedd_set($);

#     #t build a table that converts model container serials to entries in the connection matrix

#     my $connection_table = ConnectionTableNew($connections);

#     my $count = 0;

#     my $connection_table_entries
# 	= [
# 	   map
# 	   {
# 	       # lookup serial for this component

# 	       my $output = $_;

# 	       my $service = $scheduler->lookup_object($options->{service});

# 	       my $solver_info = $service->output_2_solverinfo($output);

# 	       my $result
# 		   = {
# 		      serial => $solver_info->{serial},
# 		      count => $count,
# 		     };

# 	       $count++;

# 	       $result;
# 	   }
# 	   grep { $_->{distributor_service} } @$outputs,
# 	  ];

#     foreach my $connection_table_entry (@$connection_table_entries)
#     {
# 	$connection_table->ConnectionTableSetEntry($connection_table_entry->{serial}, $connection_table_entry->{count}, );
#     }

    return 1;
}


sub new
{
    my $package = shift;

    my $options = shift;

    my $self = { %$options, };

    bless $self, $package;

    return $self;
}


package Heccer::DES::Queuer;


BEGIN { our @ISA = qw(Heccer::Glue); }


sub compile
{
    my $self = shift;

    my $peer = shift;

    my $queuer; # $scheduler->lookup_service('event_queuer');

    $self->{backend} = SwiggableHeccer::EventQueuerNew($queuer);

    if (!defined $self->{backend})
    {
	return undef;
    }

    return 1;
}


sub new
{
    my $package = shift;

    my $options = shift;

    my $self = { %$options, };

    bless $self, $package;

    return $self;
}


package Heccer::Event::Output;


BEGIN { our @ISA = qw(Heccer::Glue); }


sub add
{
    my $self = shift;

    my $options = shift;

    my $backend = $self->backend();

    #t if I am correct we also have to set the iTable of the SpikeGen
    #t overhere, not sure.

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


# sub advance
# {
#     my $self = shift;

#     # event output is not dependent on advancing time

#     return undef;
# }


sub finish
{
    my $self = shift;

    # close files, free memory

    my $backend = $self->backend();

    $backend->OutputGeneratorFinish();
}


sub get_driver
{
    my $self = shift;

    my $result
	= {
	   data => $self->{backend}->output_generator_get_driver_data(),
	   method => undef,
# 	   data => $self->{backend},
# 	   method => undef,
	  };

    return $result;
}


sub get_time_step
{
    my $self = shift;

    # an event output object does not have a time step

    return undef;
}


sub initiate
{
    my $self = shift;

    # create files

    my $backend = $self->backend();

    $backend->OutputGeneratorInitiate();
}


sub new
{
    my $package = shift;

    my $options = shift;

    # construct object

    my $self = { %$options, };

    bless $self, $package;

    if (!defined $self->{filename})
    {
	$self->{filename} = "/tmp/EventOutputGenerator";
    }

    # construct backend

    $self->{backend} = SwiggableHeccer::OutputGeneratorNew($self->{filename});

    if (!defined $self->{backend})
    {
	return undef;
    }

    # lookup the event_distributor service

    my $event_source = $options->{event_source};

    my $scheduler = $self->{scheduler};

    my $ssp_distributor = $scheduler->lookup_object($event_source);

    if (!$ssp_distributor)
    {
	die "$0: " . __PACKAGE__ . " cannot construct, $event_source not found as an ssp service";
    }

    my $distributor = $ssp_distributor->backend();

    if (!$distributor)
    {
	die "$0: " . __PACKAGE__ . " cannot construct, $event_source has no low-level backend";
    }

    if (!$distributor->add_output($self))
    {
	die "$0: " . __PACKAGE__ . " cannot construct";
    }

    # return result

    return $self;
}


sub pause
{
    my $self = shift;

    # flush files

    my $backend = $self->backend();

    $backend->OutputGeneratorFlush();
}


sub report
{
    my $self = shift;

    #t nothing I guess ?
}


sub step
{
    my $self = shift;

    my $scheduler = shift;

    my $options = shift;

    my $backend = $self->backend();

    # event output is not dependent on advancing time

#     my $result = $backend->OutputGeneratorAnnotatedStep("$options->{steps}");

#     return $result;

    # return success

    return 1;
}


package Heccer::Glue;



sub backend
{
    my $self = shift;

    return $self->{backend};
}


package Heccer::Intermediary::Compiler;


BEGIN { our @ISA = qw(Heccer::Glue); }


sub load
{
    my $self = shift;

    my $ssp_service = shift;

    my $arguments = shift;

    my $intermediary = Heccer::Intermediary->new($arguments);

    $self->{backend} = $intermediary;

    my $result = defined $intermediary;

    return $result;
}


sub new
{
    my $package = shift;

    my $options = shift;

    my $self = { %$options, };

    bless $self, $package;

    return $self;
}


sub register_engine
{
    my $self = shift;

    my $engine = shift;

    my $modelname = shift;

    # do some concy checking for this restricted model container.

    if (defined $modelname)
    {
	die "$0: " . __PACKAGE__ . " cannot register_engine() for a named model ($modelname)";
    }

#     if (!$engine->isa('Heccer::Intermediary::Compiler'))
#     {
# 	die "$0: register_engine() called for a object that is not a 'Heccer::Intermediary::Compiler' ($engine)";
#     }

    # return success

    return 1;
}


package Heccer::Output;


BEGIN { our @ISA = qw(Heccer::Glue); }


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


# sub advance
# {
#     my $self = shift;

#     my $scheduler = shift;

#     my $time = shift;

#     # call the appropriate method

#     my $backend = $self->backend();

#     my $result = $backend->OutputGeneratorAnnotatedStep($time);

#     # return result

#     return $result;
# }


sub finish
{
    my $self = shift;

    # close files, free memory

    my $backend = $self->backend();

    $backend->OutputGeneratorFinish();
}


sub get_time_step
{
    my $self = shift;

    # an output object does not have a time step

    return undef;
}


sub get_driver
{
    my $self = shift;

    my $result
	= {
	   data => $self->{backend}->output_generator_get_driver_data(),
	   method => $self->{backend}->output_generator_get_driver_method(),
# 	   data => $self->{backend},
# 	   method => \&SwiggableHeccer::OutputGeneratorAnnotatedStep,
	  };

    return $result;
}


sub initiate
{
    my $self = shift;

    # create files

    my $backend = $self->backend();

    $backend->OutputGeneratorInitiate();
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


sub pause
{
    my $self = shift;

    # flush files

    my $backend = $self->backend();

    $backend->OutputGeneratorFlush();
}


sub report
{
    my $self = shift;

    #t nothing I guess ?
}


sub step
{
    my $self = shift;

    my $scheduler = shift;

    my $options = shift;

    my $backend = $self->backend();

    my $result;

    if ($self->{format}) # eq 'steps')
    {
	$result = $backend->OutputGeneratorAnnotatedStep("$options->{steps}");
    }
    else
    {
	$result = $backend->OutputGeneratorTimedStep($options->{time});
    }

    return $result;
}


package Heccer::PerfectClamp;


BEGIN { our @ISA = qw(Heccer::Glue); }


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

    my $result = $backend->PerfectClampAddVariable($options->{address});

    return $result;
}


# sub advance
# {
#     my $self = shift;

#     #t call the appropriate method or something

#     return undef;
# }


sub finish
{
    my $self = shift;

    # close files, free memory

    my $backend = $self->backend();

    $backend->PerfectClampFinish();
}


sub get_driver
{
    my $self = shift;

    my $result
	= {
	   data => $self->{backend}->perfect_clamp_get_driver_data(),
	   method => $self->{backend}->perfect_clamp_get_driver_method(),
# 	   data => $self->{backend},
# 	   method => \&SwiggableHeccer::PerfectClampSingleStep,
	  };

    return $result;
}


sub get_time_step
{
    my $self = shift;

    # a perfect clamp object does not have a time step

    return undef;
}


sub initiate
{
    my $self = shift;

    #t perhaps need to set the command voltage here ?
}


sub new
{
    my $package = shift;

    my $options = shift;

    my $self = { %$options, };

    bless $self, $package;

    if (!defined $self->{name})
    {
	$self->{name} = "a pc";
    }

    $self->{backend} = SwiggableHeccer::PerfectClampNew($self->{name});

    if (!defined $self->{backend})
    {
	return undef;
    }

    # make distinction between command_filename and command voltage option

    if (defined $options->{command})
    {
	my $backend = $self->backend();

	$backend->PerfectClampSetFields($options->{command}, undef);
    }
    elsif (defined $options->{filename})
    {
	my $backend = $self->backend();

	#! the command voltage is ignored in this case, use an
	#! unreasonable value to make result invalid if it would be used
	#! (due to a bug).

	$backend->PerfectClampSetFields(-10000, $options->{filename});
    }
    else
    {
	return "Heccer::PerfectClamp constructor: cannot construct a perfect clamp without command voltage and without a filename";
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

    my $scheduler = shift;

    my $options = shift;

    my $backend = $self->backend();

    my $result = $backend->PerfectClampSingleStep($options->{steps});

    return $result;
}


package Heccer::Tabulator;


BEGIN { our @ISA = qw(Heccer::Glue); }


sub dump
{
    my $self = shift;

    my $ssp_analyzer = shift;

    my $arguments = [ @_, ];

    my $result;

    # define the format

    my $format = $arguments->[0]->{format};

    my $existing_formats
	= {
	   'alpha-beta' => 1,
	   'steadystate-tau' => 1,
	   'A-B' => 1,
	   'internal' => 1,
	  };

    if (!$existing_formats->{$format})
    {
	die "$0: Heccer::Tabulator::dump(): unknown format $format";
    }

    # lookup the object with the tables

    my $scheduler = $ssp_analyzer->{scheduler};

    # convert the arguments to a serial

    my $source = $arguments->[0]->{source};

    my $service_name = $self->{ssp_engine}->{service_name};

    my $source_info = $scheduler->lookup_object($service_name);

    my $service = $source_info->backend();

    # we check here for 'A' or 'B' in the source
    # component, and assign a different field name to them, this makes
    # it easier in the C code to differentiate between those two.

    my $field
	= (
	   $source =~ m'A$'
	   ? 'table_A_index'
	   : (
	      $source =~ m'B$'
	      ? 'table_B_index'
	      : 'invalid table reference'
	     )
	   );

    my $solver_info
	= $service->output_2_solverinfo
	    (
	     {
	      component_name => $source,
	      field => $field,
	     },
	    );

    use Data::Dumper;

    print Dumper($solver_info);

    # get access to the low level C structure

    my $backend = $self->backend();

#     my $heccer = $backend->backend();

    #t not sure about this one yet

    my $synaptic = 0;

    if ($synaptic)
    {
    }
    else
    {
	# convert the table serial to an addressable: an index into the table structures

	my $table_index
	    = $self->kinetic_serial_2_table_index
		(
		 $solver_info->{serial},
		 $field,
		);

	# get access to tables

	my $tgt = $backend->{heccer}->swig_tgt_get();

	print "tgt is $tgt, table_index is $table_index\n";

	my $tables_defined = $tgt->swig_iTabulatedGateCount_get();

	if ($table_index >= $tables_defined)
	{
	    die "$0: internal error, table index for $source is $table_index, but that is >= $tables_defined (serial is $solver_info->{serial}, field is $field)";
	}

	# implement SwiggableHeccer::htg_get()

	my $htg = SwiggableHeccer::htg_get($tgt, $table_index);

	my $A_doubles = $htg->swig_pdA_get();

	my $B_doubles = $htg->swig_pdB_get();

	# get number of entries

	my $entries = $htg->swig_iEntries_get();

	# get start, end, step size

	my $hi = $htg->swig_hi_get();

	my $end = $hi->swig_dEnd_get();

	my $start = $hi->swig_dStart_get();

	my $step = $hi->swig_dStep_get();

	# convert to array of values

	my $A = [];
	my $B = [];

	map
	{
	    $A->[$_] = SwiggableHeccer::double_get($A_doubles, $_);
	    $B->[$_] = SwiggableHeccer::double_get($B_doubles, $_);
	}
	    0 .. $entries - 1;

	# set result

	$result
	    = {
	       A => $A,
	       B => $B,
	       entries => $entries,
	       hi => {
		      end => $end,
		      start => $start,
		      step => $step,
		     },
	      };

	# now do the conversion according to the format

	my $existing_formats
	    = {
	       'alpha-beta' =>
	       sub
	       {
		   my $result = shift;

		   my $A = $result->{A};
		   my $B = $result->{B};

		   my $alpha = [ @$A, ];

		   #! expensive operation, expands the full array

		   my $beta = [];

		   foreach my $index (0 ... $#$B)
		   {
		       $beta->[$index] = $B->[$index] - $A->[$index];
		   }

		   $result->{alpha} = $alpha;

		   $result->{beta} = $beta;

		   return $result;
	       },
	       'steadystate-tau' =>
	       sub
	       {
		   my $result = shift;

		   my $A = $result->{A};
		   my $B = $result->{B};

		   #! expensive operation, expands the full array

		   my $steady = [];

		   foreach my $index (0 ... $#$B)
		   {
		       #t what with zeros for B ?

		       $steady->[$index] = $A->[$index] / $B->[$index];
		   }

		   #! expensive operation, expands the full array

		   my $tau = [];

		   foreach my $index (0 ... $#$B)
		   {
		       #t what with zeros for B ?

		       $tau->[$index] = 1 / $B->[$index];
		   }

		   $result->{steady} = $steady;

		   $result->{tau} = $tau;

		   return $result;
	       },
	       'A-B' => 1,
	       'internal' => 1,
	      };

	my $convertor = $existing_formats->{$format};

	if (ref $convertor eq 'CODE')
	{
	    $result = &$convertor($result);
	}
    }

    # if a result was produced

    if ($result)
    {
	# if output should go to stdout

	my $output = $arguments->[0]->{output} || 'stdout';

	if ($output eq 'stdout')
	{
	    use YAML;

	    print Dump(bless($result, 'Heccer::Tabulator::Result'));
	}

	elsif ($output =~ m|^file://(.*)|)
	{
	    my $filename = $1;

	    use IO::File;

	    my $fh = IO::File->new(">$filename");

	    if (!$fh)
	    {
		die "$0: Heccer::Tabulator::dump(): cannot open file $filename";
	    }

	    use YAML;

	    print $fh Dump(bless($result, 'Heccer::Tabulator::Result'));

	    $fh->close();
	}
    }

    # return result

    return $result;
}


sub kinetic_serial_2_table_index
{
    my $self = shift;

    my $serial = shift;

    my $type = shift;

    my $result;

    # get access to the low level C structure

    my $backend = $self->backend();

    my $heccer = $backend->backend();

    $result = $heccer->HeccerAddressTableIndex($serial, $type);

    return $result;
}


sub new
{
    my $package = shift;

    my $options = shift || {};

    my $self
	= {
	   #! this gets called before Heccer is instantiated so there
	   #! is no backend yet.

	   backend => undef,

	   %$options,
	  };

    bless $self, $package;

    return $self;
}


sub serve
{
    my $self = shift;

    my $ssp_analyzer = shift;

    my $options = shift;

    # lookup the object with the tables

    my $scheduler = $ssp_analyzer->{scheduler};

    # lookup the heccer

    my $solver = $scheduler->lookup_solver_engine($options->{source});

    if (!defined $solver)
    {
	die "$0: Heccer::Tabulator::serve(): solver not found";
    }

    $self->{ssp_engine} = $solver;

    my $backend = $solver->backend();

    if (!$backend->isa("Heccer"))
    {
	die "$0: Heccer::Tabulator::serve(): $backend is not a Heccer object";
    }

    # get access to the low level C structure

    my $heccer = $backend->backend();

    $self->{backend} = $backend;

    1;
}


package Heccer::Tabulator::Result;

#! nothing here, just place holder for loading tables from YAML streams.


1;


