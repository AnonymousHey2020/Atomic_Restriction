for ((j=0; j<10; j++))
do
    for ((i=0; i<10; i++))
    do
        ./nbench $j >> bench$j.txt
    done
done