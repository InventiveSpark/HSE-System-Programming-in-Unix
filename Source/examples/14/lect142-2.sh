: '
   Пример
   Вычисление арифметических выражений в shell.
   Сделать файл исполняемым:
   chmod u+x ./lect142-2.sh

   1 Hello
   2 Hello
   3 Hello
'

a=1               # Объявление переменной $a и присвоение ей значения
while let "a<=3"  # Цикл будет выполняться до тех пор, пока значение переменной $a <= 3
do
    echo $a Hello # Вывод в стандартный файл вывода (монитор) значения переменной и цепочки символов
    let "a=a+1"   # Увеличение значения переменной на единицу
done
