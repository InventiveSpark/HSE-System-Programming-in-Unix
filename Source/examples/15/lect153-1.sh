: '
   Пример
   Конструкция цикла for. Примеры реализации
   Сделать файл исполняемым:
   chmod u+x ./lect153-1.sh

   Ответ:
    number 1
    number 2
    number 65
    number 10
'

for i in 1 2 65 10   # Переменная $i перебирает все варианты в списке 1 2 65 10
do
    echo number $i   # В стандартный файл вывода (монитор) выводится слово и значение переменной
done
