read -p "Enter two numbers : " a b
echo -e "Main Menu\n1.Add\n2.Sub\n3.Mul\n4.Div\n5.Mod"
read ch
case $ch in
1) echo "Addition = $(($a+$b))";;
2) echo "Subtraction = $((a-b))";;
3) echo "Multiplication = $((a*b))";;
4) echo "Division = $((a/b))";;
5) echo "Modulo = $((a%b))";;
*) echo "Invalid Operation Request"
esac