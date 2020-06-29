for ((i=0; i<=9; i++))
do
    ./bench1 0 $i > bench$i.txt
    echo $i
done