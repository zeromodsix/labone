echo >all.txt
i=0
for f in files/*.txt; do
    echo $i>>all.txt
    cat  $f>>all.txt
    echo "\n">>all.txt
    i=$((i+1))
done


