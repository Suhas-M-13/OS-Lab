read -p "Enter Rows: " Row
read -p "Enter Columns: " Column

echo "Enter Array-1"
for ((i=0; i<Row; i++)) 
do
    for ((j=0; j<Column; j++))
    do
        read -p "Enter A[$i,$j]: " value
        A[$((i*Column+j))]=$value
    done
done

echo "Enter Array-2"
for ((i=0; i<Row; i++)) 
do
    for ((j=0; j<Column; j++))
    do
        read -p "Enter B[$i,$j]: " value
        B[$((i*Column+j))]=$value
    done
done

echo "Entered Array-1: "
for ((i=0; i<Row; i++)) 
do
    for ((j=0; j<Column; j++))
    do
        echo -n "${A[$((i*Column+j))]} "
    done
    echo
done

echo "Entered Array-2: "
for ((i=0; i<Row; i++)) 
do
    for ((j=0; j<Column; j++))
    do
        echo -n "${B[$((i*Column+j))]} "
    done
    echo
done

echo "Sum is: "
for ((i=0; i<Row; i++)) 
do
    for ((j=0; j<Column; j++))
    do
        idx=$((i*Column+j))
        C[$idx]=$((${A[$idx]}+${B[$idx]}))
        echo -n "${C[$idx]} "
    done
    echo
done
