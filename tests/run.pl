#!/usr/bin/perl

use File::Basename;
use File::Compare;

use strict;
use warnings;

my $dirname = dirname(__FILE__);
print $dirname, "\n";

for (<$dirname/*>) {
    next unless -d $_;

    print "---- Compiling $_ ----\n";
    system "gcc $dirname/$_/test.c -o $dirname/$_/test";

    print "     Done compiling, running\n";
    system "$dirname/$_/test > $dirname/$_/actual 2>&1";

    if (compare("$dirname/$_/expected", "$dirname/$_/actual")) {
        print "!    $_ failed!\n";
    } else {
        print "     $_ OK\n";
    }
}
