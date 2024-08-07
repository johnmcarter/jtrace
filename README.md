# jtrace
A user-friendly ftrace for Linux machines. This tool logs all system calls happening on-device.


## Installation
As superuser, run ```install.sh``` in the scripts directory with this command:
```
# ./install.sh <qualified jtrace directory location>
```

## Usage
As superuser, mount the tracefs virtual filesystem and enable the function tracer using the ```setup.sh``` script in the scripts directory:
```
# ./setup.sh
```
and run jtrace to log all system calls happening on the Linux machine:
```
# jtrace <output filename>
```

Or get usage of jtrace:
```
# jtrace -h
```

## Troubleshooting
The executable may need to be recompiled. If so, first remove the executable and then run ```make```:
```
# rm jtrace
# make
```

## Removal
To remove jtrace, as superuser, run ```uninstall.sh``` in the scripts directory with this command:
```
# ./uninstall.sh
```

## Compatibility
Last tested on Ubuntu 20.04 and Raspberry Pi OS (Mar. 2024) but should work for most Linux distributions.


## How It Works
This tool logs all system calls by connecting to the trace pipe located in
```/sys/kernel/debug/tracing/trace_pipe```. The raw output of ```trace_pipe``` is shown below:
```
cat trace
tracer: function

                     _-----=> irqs-off
                    / _----=> need-resched
                   | / _---=> hardirq/softirq
                   || / _--=> preempt-depth
                   ||| /     delay
 TASK-PID   CPU#   ||||    TIMESTAMP  FUNCTION
    | |       |    ||||       |         |
<idle>-0     [001] d...    23.695208: _raw_spin_lock_irqsave <-hrtimer_next_event_wi...
<idle>-0     [001] d...    23.695209: __hrtimer_next_event_base <-hrtimer_next_event...
<idle>-0     [001] d...    23.695210: __next_base <-__hrtimer_next_event_base
<idle>-0     [001] d...    23.695211: __hrtimer_next_event_base <-hrtimer_next_event...
<idle>-0     [001] d...    23.695212: __next_base <-__hrtimer_next_event_base
<idle>-0     [001] d...    23.695213: __next_base <-__hrtimer_next_event_base
<idle>-0     [001] d...    23.695214: _raw_spin_unlock_irqrestore <-hrtimer_next_eve...
<idle>-0     [001] d...    23.695215: get_iowait_load <-menu_select
<idle>-0     [001] d...    23.695217: tick_nohz_tick_stopped <-menu_select
<idle>-0     [001] d...    23.695218: tick_nohz_idle_stop_tick <-do_idle
<idle>-0     [001] d...    23.695219: rcu_idle_enter <-do_idle
<idle>-0     [001] d...    23.695220: call_cpuidle <-do_idle
<idle>-0     [001] d...    23.695221: cpuidle_enter <-call_cpuidle
```
Figure credits: https://embeddedbits.org/tracing-the-linux-kernel-with-ftrace/

Last modified: 1 July 2024
