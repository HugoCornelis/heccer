#!/usr/bin/perl -w
#!/usr/bin/perl -w -d:ptkdb
#

# swig -perl5 -makedefault -module Heccer heccer.i
# gcc -c heccer_wrap.c `perl -MExtUtils::Embed -e ccopts` 
# gcc -shared heccer_wrap.o -L. -lheccer -o Heccer.so

use strict;


$| = 1;


BEGIN
{
    push @INC, '.';

    push @INC, '/usr/local/glue/swig/perl';
}


use SwiggableHeccer;


print "hello there\n";


use Data::Dumper;


{
    no strict "refs";

    print Dumper(\%{"main::"});

    print "Found these methods for SwiggableHeccer::\n";

    print Dumper(\%{"SwiggableHeccer::"});

    print "Found these methods for SwiggableHeccer::Heccer::\n";

    print Dumper(\%{"SwiggableHeccer::Heccer::"});

    print "Found these methods for SwiggableHeccer::Intermediary::\n";

    print Dumper(\%{"SwiggableHeccer::Intermediary::"});

    print "Found these methods for SwiggableHeccer::Compartment::\n";

    print Dumper(\%{"SwiggableHeccer::Compartment::"});

    print "Found these methods for SwiggableHeccer::ChannelActInact::\n";

    print Dumper(\%{"SwiggableHeccer::ChannelActInact::"});

    print "Found these methods for SwiggableHeccer::GateConcept::\n";

    print Dumper(\%{"SwiggableHeccer::GateConcept::"});

    print "Found these methods for SwiggableHeccer::GateKinetic::\n";

    print Dumper(\%{"SwiggableHeccer::GateKinetic::"});

    print "Found these methods for SwiggableHeccer::PoweredGateConcept::\n";

    print Dumper(\%{"SwiggableHeccer::PoweredGateConcept::"});

    print "Found these methods for SwiggableHeccer::ExponentialDecay::\n";

    print Dumper(\%{"SwiggableHeccer::ExponentialDecay::"});

}


sub singlep
{
    print "singlep bindings\n";

    # construct soma compartment

    my $soma = SwiggableHeccer::Compartment->new();

    my $mc = $soma->swig_mc_get();


    #t I would like to be able to use MATH_TYPE_Compartment here.
    #t
    #t MATH_TYPE_Compartment because of strict subs
    #t SwiggableHeccer::MATH_TYPE_Compartment because of strict subs
    #t Heccerc::MATH_TYPE_Compartment fails because it returns 0 instead of 1.

    $mc->swig_iType_set(1);

    $soma->swig_dCm_set(4.57537e-11);
    $soma->swig_dEm_set(-0.08);
    $soma->swig_dInitVm_set(-0.068);
    $soma->swig_dInject_set(0);
    $soma->swig_dRa_set(360502);
    $soma->swig_dRm_set(3.58441e+08);
    $soma->swig_iParent_set(-1);

    my $intermediary = SwiggableHeccer::Intermediary->new();

    $intermediary->swig_iCompartments_set(1);

    $intermediary->swig_pcomp_set($soma);

    my $pi = $intermediary->swig_piC2m_get();

    my $piC2m = SwiggableHeccer::int_array(2);

    #t get rid of count by implementing a push, needs current.

    my $comp2mech = [ 0, -1];

    my $count = 0;

    map { SwiggableHeccer::int_set($piC2m, $count++, $_) } @$comp2mech;

    # SwiggableHeccer::piC2m_set($intermediary, $piC2m, );

    $intermediary->swig_piC2m_set( $piC2m );

    # instantiate a heccer with an initialized intermediary

    my $heccer = SwiggableHeccer::HeccerNewP2($intermediary);

    # build indices for optimization

    $heccer->HeccerCompileP2();

    # compile to byte code

    $heccer->HeccerCompileP3();

    # initiate values

    $heccer->HeccerInitiate();

    # initial dump

    $heccer->HeccerDumpV();

    # a couple of times

    foreach (0 .. 2)
    {
	# step

	$heccer->HeccerHecc();

	# dump

	print "-------\n";

	print "Iteration $_\n";

	$heccer->HeccerDumpV();
    }

    print "singlep bindings: done\n";
}


sub c1c2p2
{
    print "c1c2p2 bindings\n";

    # construct soma compartment

    my $soma = SwiggableHeccer::Compartment->new();

    my $mc_soma = $soma->swig_mc_get();


    #t I would like to be able to use MATH_TYPE_Compartment here.
    #t
    #t MATH_TYPE_Compartment because of strict subs
    #t SwiggableHeccer::MATH_TYPE_Compartment because of strict subs
    #t Heccerc::MATH_TYPE_Compartment fails because it returns 0 instead of 1.

    $mc_soma->swig_iType_set(1);

    $soma->swig_dCm_set(4.57537e-11);
    $soma->swig_dEm_set(-0.08);
    $soma->swig_dInitVm_set(-0.068);
    $soma->swig_dInject_set(1e-8);
    $soma->swig_dRa_set(360502);
    $soma->swig_dRm_set(3.58441e+08);
    $soma->swig_iParent_set(-1);


    my $main = SwiggableHeccer::Compartment->new();

    my $mc_main = $main->swig_mc_get();


    #t I would like to be able to use MATH_TYPE_Compartment here.
    #t
    #t MATH_TYPE_Compartment because of strict subs
    #t SwiggableHeccer::MATH_TYPE_Compartment because of strict subs
    #t Heccerc::MATH_TYPE_Compartment fails because it returns 0 instead of 1.

    $mc_main->swig_iType_set(1);

    $main->swig_dCm_set(5.755329373e-12);
    $main->swig_dEm_set(-0.08);
    $main->swig_dInitVm_set(-0.068);
    $main->swig_dInject_set(0);
    $main->swig_dRa_set(772813.4375);
    $main->swig_dRm_set(8.548598272e9);
    $main->swig_iParent_set(0);

    my $intermediary = SwiggableHeccer::Intermediary->new();

    $intermediary->swig_iCompartments_set(2);

    my $comp_array = SwiggableHeccer::comp_array(2);

    SwiggableHeccer::comp_set($comp_array, 0, $soma);

    SwiggableHeccer::comp_set($comp_array, 1, $main);

    $intermediary->swig_pcomp_set($comp_array);

    my $pi = $intermediary->swig_piC2m_get();

    my $piC2m = SwiggableHeccer::int_array(2);

    #t get rid of count by implementing a push, needs current.

    my $comp2mech = [ 0, 0, -1];

    my $count = 0;

    map { SwiggableHeccer::int_set($piC2m, $count++, $_) } @$comp2mech;

    # SwiggableHeccer::piC2m_set($intermediary, $piC2m, );

    $intermediary->swig_piC2m_set( $piC2m );

    # instantiate a heccer with an initialized intermediary

    my $heccer = SwiggableHeccer::HeccerNewP2($intermediary);

    # build indices for optimization

    $heccer->HeccerCompileP2();

    # compile to byte code

    $heccer->HeccerCompileP3();

    # initiate values

    $heccer->HeccerInitiate();

    # initial dump

    $heccer->HeccerDumpV();

    # a couple of times

    foreach (0 .. 2)
    {
	# step

	$heccer->HeccerHecc();

	# dump

	print "-------\n";

	print "Iteration $_\n";

	$heccer->HeccerDumpV();
    }

    print "c1c2p2 bindings: done\n";
}


singlep();

c1c2p2();

print "Perl script finished\n";
