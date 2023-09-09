#number is palindrome or not
read -p "Enter any number : " a

n=$a
sum=0
while [ $n -ne 0 ]
do
r=$(($n%10))
sum=$(($(($sum*10))+$r))
n=$(($n/10))
done

if [ $a -eq $sum ] 
then
    echo "Entered Number $a is palindrome number"
else
    echo "Entered Number $a is not a palindrome number"
fi