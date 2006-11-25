#!/usr/bin/perl -w
#!/usr/bin/perl -w -d:ptkdb
#

# swig -perl5 -makedefault -module Heccer heccer.i
# gcc -c heccer_wrap.c `perl -MExtUtils::Embed -e ccopts` 
# gcc -shared heccer_wrap.o -L. -lheccer -o Heccer.so

use strict;


BEGIN
{
    push @INC, '.';
}


use Heccer;


print "hello there\n";


use Data::Dumper;


{
    no strict "refs";

    print Dumper(\%{"Heccer::Intermediary::"});

    print Dumper(\%{"Heccer::Compartment::"});
}

# construct soma compartment

my $soma = Heccer::Compartment->new();

print Dumper($soma);

$soma->swig_dCm_set(4.57537e-11);
$soma->swig_dEm_set(-0.08);
$soma->swig_dInitVm_set(-0.068);
$soma->swig_dInject_set(0);
$soma->swig_dRa_set(360502);
$soma->swig_dRm_set(3.58441e+08);
$soma->swig_iParent_set(-1);

my $intermediary = Heccer::Intermediary->new();

$intermediary->swig_iCompartments_set(1);

$intermediary->swig_pcomp_set($soma);

my $heccer = Heccer::HeccerNewP2($intermediary);

$heccer->HeccerCompileP2();

$heccer->HeccerDumpV();

$heccer->HeccerCompileP3();

$heccer->HeccerDumpV();

$heccer->HeccerInitiate();

$heccer->HeccerDumpV();

$heccer->HeccerHecc();

$heccer->HeccerDumpV();

print "Perl script finished\n";
