/*
   Поддержка сигналов ядром ОС UNIX/
   Обработка сигналов в ОС UNIX. Программная реализация
*/
// Заголовочные файлы:
#include <signal.h> // Для использования своего обработчика сигналов
#include <stdlib.h> // Для СВ system()

void main()
{
    /* Функция обработки сигнала handl() должна быть объявлена (или описана) 
       перед использованием СВ signal() или sigaction(): */
    void aaa();
    /* СВ signal() должен быть объявлен в начальных инструкциях программы, 
       иначе в начале программы ОС будет применять обработчик по умолчанию.
       Установка функции aaa() в качестве пользовательского обработчика 
       сигнала SIGINT (код 2): */
    signal(SIGINT, aaa);   
    /* Тело программы.
       Каждое нажатие комбинации клавиш < Ctrl+C > во время выполнения 
       программы сгенерирует сигнал прерывания SIGINT, после чего будет 
       выполнена программа обработчика, затем процесс продолжит свое 
       функционирование с той точки исходной программы, в которой получил
       соответствующий сигнал.
       Бесконечный цикл для того, чтобы пользователь успел нажать < Ctrl+C >:
    */
    while (1); 
}
void aaa() // Описание функции обработчика сигнала
{
    /* СВ system() позволяет вызывающей программе выполнить произвольную 
       консольную команду или вызвать другую программу, не выходя из 
       контекста вызывающего процесса. При нажатии на < Ctrl+C > СВ system()
       запускает утилиту date, которая выводит на монитор текущую дату 
       и время, т.е. дату и время поступления сигнала. */
    system("date");
}
