#!/usr/bin/perl
use warnings;
use strict;
# die "program x y density" unless (scalar(@ARGV) == 3);
my ($x, $y, $density) = (10, 10, 5);
print "Content-type: text/plain\n\n";
print "<html>\n<body>\n";
print "$y.ox\n";
for (my $i = 0; $i < $y; $i++) {
	for (my $j = 0; $j < $x; $j++) {
		if (int(rand($y) * 2) < $density) {
			print "o";
		}
		else {
			print ".";
		}
	}
	print "\n";
}
print "</body>\n</html>";