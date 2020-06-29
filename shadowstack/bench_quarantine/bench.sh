for ((i=0; i<=10; i++))
do
    ./bench $i > bench$i.txt
    echo $i
done