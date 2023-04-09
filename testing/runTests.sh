#!/bin/bash

#!/bin/bash

# Loop through all files in the current directory with a .txt extension
for file in *.txt
do
    # Run your command on each file
    ./Stocks "$file"
done
