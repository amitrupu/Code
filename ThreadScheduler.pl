#!/usr/bin/env perl

use strict;
use warnings;
use FileHandle;
use Data::Dumper;
use threads;
use threads::shared;
use Thread::Queue;
my $debug = 1;

#### Thread Scheduler ####

# Create shared hash reference
sub create_shared_hash() {
    my %shared_hash : shared;
    share(%shared_hash);
    my $shared_hash_ref : shared = &share(\%shared_hash);
    return $shared_hash_ref;
}

# Create thread-safe queue of tasks
sub create_task_queue(@) {
    my $task_names = shift @_;
    my $task_queue = Thread::Queue->new();
    $task_queue->enqueue(@$task_names);
    return $task_queue;
}

# Create threads of works and schedule tasks
# Pass two subroutine reference as argument:
# get_key_value_sub - takes task_name as input and returns hash with keys: key, value and value_type
# update_hash_sub - takes $shared_hash{$key}, $key and $value and and update $shared_hash{$key}
sub execute_tasks($$$$$) {
    my ($shared_hash_ref, $task_queue, $get_key_value_sub, $update_hash_sub, $num_threads) = @_;

    # Worker subroutine reference accepting shared hash ref
    my $worker = sub {
        my ($hash_ref, $worker_id) = @_;
        while (my $task_name = $task_queue->dequeue_nb()) {
            my $key_value_hash = $get_key_value_sub->($task_name);
            (defined $key_value_hash) || next;
            my $key = $key_value_hash->{key};
            my $value = $key_value_hash->{value};
            my $value_type = $key_value_hash->{value_type};
            $value_type = 'HASH' if (! defined $value_type);

            lock(%$hash_ref);

            # Initialize nested hash if not exists
            if (!exists $hash_ref->{$key}) {
                if ($value_type eq 'HASH') {
                    my %nested : shared;
                    share(%nested);
                    $hash_ref->{$key} = &share(\%nested);
                } elsif ($value_type eq 'ARRAY') {
                    my @nested : shared;
                    share(@nested);
                    $hash_ref->{$key} = &share(\@nested);
                }
            }
            $update_hash_sub->($hash_ref->{$key}, $key, $value);

            (defined $debug) && print "Worker $worker_id has processed task $task_name\n";
        }
    };

    # Create threads, passing shared hash ref
    my @threads;
    for (my $i = 1; $i <= $num_threads; $i++) {
        (defined $debug) && print "Creating worker $i\n";
        push @threads, threads->create($worker, $shared_hash_ref, $i);
    }

    # Wait for threads to finish
    $_->join() for @threads;
}

#### Main

# Prepare tasks
sub get_key_value($) {
    my ($task_name) = @_;
    sleep(0);
    return { key => $task_name };
}
sub update_hash($$$$) {
    my ($key_hash_ref, $key, $value) = @_;
    die if (defined $value);
    $key_hash_ref->{count} = 0 if (!defined $key_hash_ref->{count});
    $key_hash_ref->{count}++;
}
my $num_tasks = 100;
my @task_name_set = ('A'..'D');
my @task_names;
for (my $i = 0; $i < $num_tasks; $i++) {
    my $random_index = int(rand @task_name_set);
    push @task_names, $task_name_set[$random_index];
}

# Create shared hash, tasks and execute
my $num_threads = qx(grep 'core id' /proc/cpuinfo | sort -u | wc -l); chomp($num_threads);
$num_threads = 4 if ($num_threads < 4);
(defined $debug) && print "Number of threads: $num_threads\n";
my $shared_hash_ref = create_shared_hash();
my $task_queue = create_task_queue(\@task_names);
execute_tasks($shared_hash_ref, $task_queue, \&get_key_value, \&update_hash, $num_threads);

# Print final hash states
print "\nFinal hash state:\n";
foreach my $key (sort(keys %$shared_hash_ref)) {
    print "$key : $shared_hash_ref->{$key}{count}\n";
}

