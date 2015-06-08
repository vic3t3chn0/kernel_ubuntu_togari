#!/usr/bin/perl

open (IN,"ktest.pl");
while (<IN>) {
<<<<<<< HEAD
    # hashes are now used
    if (/\$opt\{"?([A-Z].*?)(\[.*\])?"?\}/ ||
	/^\s*"?([A-Z].*?)"?\s*=>\s*/ ||
=======
<<<<<<< HEAD
    # hashes are now used
    if (/\$opt\{"?([A-Z].*?)(\[.*\])?"?\}/ ||
	/^\s*"?([A-Z].*?)"?\s*=>\s*/ ||
=======
    if (/\$opt\{"?([A-Z].*?)(\[.*\])?"?\}/ ||
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/set_test_option\("(.*?)"/) {
	$opt{$1} = 1;
    }
}
close IN;

open (IN, "sample.conf");
while (<IN>) {
<<<<<<< HEAD
    if (/^\s*#?\s*([A-Z]\S*)\s*=/) {
=======
<<<<<<< HEAD
    if (/^\s*#?\s*([A-Z]\S*)\s*=/) {
=======
    if (/^\s*#?\s*(\S+)\s*=/) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	$samp{$1} = 1;
    }
}
close IN;

foreach $opt (keys %opt) {
    if (!defined($samp{$opt})) {
	print "opt = $opt\n";
    }
}

foreach $samp (keys %samp) {
    if (!defined($opt{$samp})) {
	print "samp = $samp\n";
    }
}
