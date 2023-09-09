#!/bin/bash

# Prompt the user to enter the number of terms in the Fibonacci series
echo "Enter the number of terms in the Fibonacci series:"
read n

# Initialize variables
a=0
b=1

# Display the Fibonacci series
echo "Fibonacci series:"

for ((i=0; i<n; i++))
do
  echo -n "$a "

  # Calculate the next term
  temp=$((a + b))
  a=$b
  b=$temp
done

echo
