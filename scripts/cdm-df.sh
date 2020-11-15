#!/usr/bin/env bash

# This script should go in /etc/profile.d/
# So that its run whenever you login
# Specify the ttys you want it to run on
ttys="tty1 tty2 tty3 tty4 tty5 tty6" 

valid_tty="false"
for tty in $ttys
do 
	cur_tty="$(tty | cut -d "/" -f 2 )"
	if [ "$cur_tty" = "$tty" ]
	then
		valid_tty="true"	
	fi
done

# Only run in on a valid terminal
if [ "$valid_tty" = "true" ]
then
	# Just run the program and have bash execute the output
	cdm-df | bash
fi
