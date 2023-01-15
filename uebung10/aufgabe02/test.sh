# run a.out multiple times and check if the output differs from the last run

# run a.out and save the output to a variable
output=$(./a.out)

# loop 100 times
for i in {1..100}; do
    # run a.out again and compare the output to the last run and save the output to a variable
    new_output=$(./a.out)
    if [ "$output" != "$new_output" ]; then
        echo "$new_output"
    fi
    output=$new_output
done