#!/usr/bin/perl 

$packageName = $ARGV[$0];
$zmValue     = 400;

if($packageName eq "System")
{
    $zmValue = 1060;
}

while(<STDIN>)
{
    $_ =~ s/(Zm[0-9]*)/Zm$zmValue/g;

    print("$_");
}
