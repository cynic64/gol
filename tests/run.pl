#!/usr/bin/perl

use File::Compare;

use strict;
use warnings;

for (<*>) {
    next unless -d $_;

    print "---- Compiling $_ ----\n";
    system "cd $_; gcc -O3 test.c -o test";

    print "     Done compiling, running\n";
    if ($_ =~ /bench/) {
        system "cd $_; ./test";
    } else {
        system "cd $_; ./test > actual 2>&1";

        if (compare("$_/expected", "$_/actual")) {
            print "!    $_ failed!\n";
        } else {
            print "     $_ OK\n";
        }
    }
}
