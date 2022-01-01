: '
   Примеры реализаций shell-скриптов. Пример 2
   Написать shell процедуру подсчета символов в цепочке 
   символов, вводимой с клавиатуры.
   Сделать файл исполняемым:
   chmod u+x ./lect156-2.sh

   Ответ:
   Введите цепочку символов:
   Hello ALL!
   введенная строка символов: Hello ALL!
   цепочка символов состоит из 10 символов
'
echo "Введите цепочку символов:"
read a # Чтение в shell-переменную $a из терминала
echo "введенная строка символов: $a"
leng=`expr "$a" : '.*'` # Создается переменная $leng и ей присваивается результат
                        # сравнения $a с произвольной цепочкой символов ".*" - т.е.
                        # количество совпадающих символов (длина цепочки $a).
# Примечание: Здесь указано "$a", т.е. учитываются все считанные из терминала символы,
# включая повторяющиеся пробелы.
echo "цепочка символов состоит из $leng символов"