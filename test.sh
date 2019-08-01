#!/bin/bash
STACK_SIZE=102400

for input in "$2"/*.in
do
	./"$1" <"$input" >/tmp/quantization.out 2> /tmp/quantization.err
	diff -- /tmp/quantization.out "${input%in}out" >/dev/null
	DIFF_OUT=$?
	diff -- /tmp/quantization.err "${input%in}err" >/dev/null
	DIFF_ERR=$?
	if [[ $DIFF_OUT -eq 1 ]] || [[ $DIFF_ERR -eq 1 ]]
	then echo "Test $input zakończył się niepowodzeniem"
	else echo "Test $input zakończył się powodzeniem"
	fi
	valgrind --error-exitcode=2 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --main-stacksize=$(($STACK_SIZE * 1024)) -- "./$1" < "$input" &>/dev/null
	VALGRIN=$?
	if [[ $VALGRIND -eq 2 ]]
	then echo "Problem z pamięcią"
    else echo "Pamięć poprawna"
    fi
	rm -- /tmp/quantization.out /tmp/quantization.err
done
