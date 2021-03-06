: '
   Обработка сигналов в shell. Конструкция trap. Пример
   При поступлении сигнала SIGINT или SIGTSTP будут выполнены три утилиты: ls, who, ps
   Сделать файл исполняемым:
   chmod u+x ./lect154-1.sh
'

# Установка нового обработчика из трех команд при поступлении сигналов прерывания, указанных далее:
trap "
ls
who
ps
" SIGINT SIGTSTP
# В данном случаю сигналы задаются через их символьные константы:
# •	SIGINT (код 2) - сигнал прерывания < Ctrl+C > с терминала, вызывающий завершение процесса;
# •	SIGTSTP (код 23) - сигнал остановки с терминала < Ctrl+Z >, приводящий к остановке процесса.
sleep 3 # Замедление выполнения работы программы на 3 секунды для того, чтобы
        # пользователь успел нажать < Ctrl+C > или < Ctrl+Z >.
