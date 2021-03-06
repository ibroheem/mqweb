#!/usr/bin/perl
use strict;
use warnings;
use feature qw(say);

use JSON;
use LWP::UserAgent;
use HTTP::Request::Common;

# This sample will show all connections of the MQWeb daemon

my $qmgr = shift;
die("Please pass me the name of a queuemanager as argument")
	unless defined($qmgr);

my $json = JSON->new;

my %input = ( 
	'StringFilterCommand' => {
		'Parameter' => 'ApplTag',
		'Operator' => 'LK',
		'FilterValue' => 'mqweb*'
	}
);

my $content = $json->encode(\%input);    

my $ua = LWP::UserAgent->new;
my $req = POST 'http://localhost:8081/api/conn/inquire/' . $qmgr;
$req->header(
	'Content-Type' => 'application/json',
	'Content-length' => length($content)
);
$req->content($content);

my $res = $ua->request($req);
die $res->status_line unless $res->is_success;
	
my $mqweb = $json->decode($res->content());
if ( exists($mqweb->{error}) ) {
	say 'An MQ error occurred while inquiring connections.';
	say 'Reason Code: '
		, $mqweb->{error}->{reason}->{code}
		, ' - '
		, $mqweb->{error}->{reason}->{desc};
}
else {
	foreach my $connection(@{$mqweb->{data}}) {
		say $connection->{ApplTag}->{value}
			, ' = '
			, $connection->{ApplType}->{display} 
			, ' (pid='
			, $connection->{ProcessId}->{value}
			, ')';
	}
}

