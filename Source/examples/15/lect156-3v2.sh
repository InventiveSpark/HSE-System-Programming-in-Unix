: '
   Примеры реализаций shell-скриптов. Пример 3 (2-ой вариант)
   Написать shell-скрипт подсчета количества файлов в текущем 
   каталоге, которые содержат текстовую информацию, или в имени 
   файла содержат слово text. Список таких файлов направьте в 
   файл text.txt.
   Сделать файл исполняемым:
   chmod u+x ./lect156-3v2.sh

'

find . -exec file {} \; | grep text | cut -d : -f 1 | tee text.txt | wc -l

: '
Утилита find предусматривает неограниченное количество аргументов и применяется для поиска 
в текущем каталоге всех файлов:
. (каталог поиска) - это отправной каталог (текущий каталог), с которого find начинает поиск
файлов по всем подкаталогам, находящимся внутри;
опция -exec используется для выполнения произвольных команд для найденных файлов. В данном
случае, выполнить команду file для получения подробной информации о каждом файле.
Затем полученная информация передаются через межпроцессный канал (с помощью конвейеризации)
на вход утилиты grep, которая выводит только те записи, которые содержат шаблон "text".
Затем полученный набор записей, содержащих искомый шаблон передается по конвейеру 
на вход утилиты cut, которая вырезает имена файлов, т.е. первое поле каждой записи до 
символа-разделителя двоеточие ":".
Затем полученный набор записей, содержащих имена файлов, по конвейеру передается на вход 
утилите tee, которая записывает вывод любой команды в один или несколько файлов.
В данном случае утилита tee осуществляет два вывода одной и той же информации: 
1. В файл text.txt сохраняется набор записей с именами искомых файлов; 
2. По конвейеру на вход утилиты wc -l, подсчитывающей количество строк из файла стандартного 
   ввода (полученного через конвейер). В результате количество записей с именами файлов будет 
   подсчитано как количество строк.
'