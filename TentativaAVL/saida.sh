for file in 1 2 3 4
do
    echo "Teste ${file}"
    ./myavl < "testes/teste${file}.in" > out.out
    paste out.out "testes/teste${file}.out"
    diff out.out  "testes/teste${file}.out"
    echo
done
