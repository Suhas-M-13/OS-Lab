read -p "Enter range of Numbers : " a b

flag=0

for((i=$a;i<=$b;i++))
    do
        for((j=2;j<$i;j++))
            do
                if [ $(($i%$j)) == 0 ]
                then
                    flag=1
                    break
                else
                flag=0
                fi
            done
        if [ $flag == 0 ]
        then
            echo -ne "$i  "
        fi
    done
echo