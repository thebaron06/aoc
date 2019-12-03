#!/bin/sh

infile="input.txt"

sum1=0
sum2=0
while read -r line; do
	fuel=$((${line} / 3 - 2))
	sum1=$((${fuel} + ${sum1}))
	sum2=$((${fuel} + ${sum2}))

	# calc fuel needs of fuel
	while [ ${fuel} -gt 0 ]; do
		fuel=$((${fuel} / 3 - 2))
		if [ ${fuel} -gt 0 ]; then
			sum2=$((${sum2} + ${fuel}))
		fi
	done
done < ${infile}
echo "solution 1: ${sum1}"
echo "solution 2: ${sum2}"
