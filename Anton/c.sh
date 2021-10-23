#!/bin/bash

for ((;;))
do
	clear
	leaks minishell | grep -A10 for
	sleep 1
done
