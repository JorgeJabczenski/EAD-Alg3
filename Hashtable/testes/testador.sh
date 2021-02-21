for file in 1 2 3 4
do
    echo "Teste ${file}"
    ../myht < "teste${file}.in" > out.out
    paste out.out "teste${file}.out"
    diff out.out  "teste${file}.out"
    echo
done

rm out.out