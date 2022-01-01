/*
   Пример реализации безусловного перехода, в котором используется 
   несколько функций sigsetjmp() и в обработчике сигнала SIGINT 
   используется функция siglongjmp().
*/

// Заголовочные файлы:
#include <stdio.h>  // Для поддержания стандартного ввода-вывода
#include <signal.h> /* Для работы с сигнальной маской процесса и макросами, 
                       прототипами данных из функции sigaction() */
#include <setjmp.h> /* Нелокальные переходы. Содержит прототипы функций 
                       безусловного нелокального перехода sigsetjmp() 
                       и siglongjmp(), а также определения связанных
                       с ними структур данных */
#include <stdlib.h> // Для библиотечной функции system()
#include <unistd.h> /* Для возможности мобильного переноса с одной вычислительной 
                       платформы на другую. В частности, для поддержания 
                       функции sleep() */

/* Выделение памяти под глобальную переменную: видимая всем функциям данной 
   программы переменная a1 будет сохранять состояние процесса. */
sigjmp_buf a1;

void main()
{
    /* Настройка обработчика сигнала: */
    /* Выделение памяти под объект типа struct sigaction, который содержит 
       3 поля. В объекте ss будет указан новый метод обработки сигнала: */
    struct sigaction ss;
    /* Функция обработки сигнала aaa() должна быть описана или объявлена 
       перед использованием СВ signal() или sigaction(): */
    void aaa(); // Объявление функции обработчика сигнала
    /* Задаются поля структуры struct sigaction:
       В поле sa_handler указывается имя (адрес) функции обработки сигнала, 
       объявленной в начале программы */
    ss.sa_handler = aaa;
    /* Сохранение текущей СМ. Первые 2 аргумента нулевые, т.е. СМ текущего 
       процесса не будет изменяться, а будет записана в переменную ss.sa_mask.
       Поскольку при создании процесс-потомок наследует СМ своего родителя, то 
       весь перечень сигналов, которые поддерживаются ОС, отражен в СМ процесса,
       и ОС должна на него адекватно реагировать. */
    sigprocmask(0, 0, &ss.sa_mask);
    /* Поле sa_flags = 0, т.е. предусматривается стандартная обработка сигнала,
       который будет указан в СВ sigaction(). */
    ss.sa_flags = 0;
    /* После того, как заполнены все три поля нового метода обработки сигнала ss,
       исполняется СВ sigaction(), первым аргументом которого является SIGINT 
       (код 2) - сигнал прерывания < Ctrl+C > с терминала, по умолчанию 
       вызывающий завершение процесса.
       Вторым аргументом является ss - новый метод обработки сигнала.
       Третий аргумент 0 означает, что старый метод обработки сигнала не будет 
       сохранен, т.е. он не будет использоваться в дальнейшем.
       Поле ss.sa_mask определяет набор сигналов, которые будут добавлены к СМ
       процесса перед вызовом функции-обработчика ss.sa_handler = aaa(). Перед
       возвратом из обработчика сигнала СМ будет автоматически восстановлена в 
       прежнее состояние. Таким способом можно блокировать определенные сигналы 
       на время работы функции-обработчика.
       Перед доставкой сигнала, когда вызывается функция-обработчик, сам сигнал 
       также включается в СМ; тем самым на время выполнения обработчика 
       блокируется доставка того же самого сигнала. Такой подход гарантирует 
       то, что во время обработки последующее поступление определенных сигналов 
       будет приостановлено до завершения вызова. */
    sigaction(SIGINT, &ss, 0);
    /* СВ sigaction() описан в начале программы, поэтому, если в дальнейшем 
       поступит сигнал SIGINT, то программа всегда на него отреагирует: любое 
       нажатие < Ctrl+C > на клавиатуре вызовет функцию обработки сигнала aaa(), 
       которая будет выводить текущую дату и время (т.е. время поступления 
       сигнала) в стандартном формате. */

    /* Тело основной программы, в котором находится множество функций sigsetjmp(). 
       Каждая функция sigsetjmp() запоминает текущее состояние (контекст) 
       процесса, чтобы после обработки прерывания посредством siglongjmp() 
       вернуться к последнему запомненному состоянию (к последнему выполненному 
       sigsetjmp-у). 
       При выходе из обработчика прерываний процесс будет начинаться не с того 
       места, где поступил сигнал, а с последнего запомненного состояния процесса, 
       т.е. с последней выполненной функции sigsetjmp(). 
       Именно последняя запомненная функция sigsetjmp() будет всегда возвращать 
       единичку, которая задана во втором аргументе у функции siglongjmp(), 
       вызываемой по окончании работы обработчика. Если же функция sigsetjmp() 
       была вызвана непосредственно (при первом вызове, т.е. при обычном порядке 
       исполнения программы в отсутствии сигналов), то она вернет нулевое 
       значение.
       Первый аргумент a1 функции sigsetjmp() - область памяти, куда будет 
       сохранено текущее состояние процесса, или его контекст (текущие значения 
       счетчика команд, позиции стека, регистров процессора).
       Второй аргумент 2, не равный нулю (т.е. равный TRUE) означает, что 
       в переменную a1 будет сохраняться также и СМ (маска блокированных сигналов 
       и действия, связанные со всеми сигналами) текущего процесса.
       Это позволяет после прерывания вернуться к последнему запомненному 
       состоянию. */
    int ret = sigsetjmp(a1, 2); // Запоминание текущего состояния процесса
    /* Тело программы... */
    for (int i = 0; i < 5; i++) // По сигналу цикл будет перезапущен заново
    {
        printf("1st instance of sigsetjmp. Returned value = %d\n", ret);
        sleep(1); // Ждать 1 секунду, чтобы пользователь успел нажать < Ctrl+C >
    }
    ret = sigsetjmp(a1, 1);     // Запоминание текущего состояния процесса
    /* Тело программы... */
    for (int i = 0; i < 5; i++) // По сигналу цикл будет перезапущен заново
    {
        printf("2nd instance of sigsetjmp. Returned value = %d\n", ret);
        sleep(1); // Ждать 1 секунду, чтобы пользователь успел нажать < Ctrl+C >
    }
    printf("Bye!\n");
}

void aaa() // Описание функции обработчика сигнала
{
    /* СВ system() позволяет вызывающей программе выполнить произвольную 
       консольную команду или вызвать другую программу, не выходя из 
       контекста вызывающего процесса. При нажатии на < Ctrl+C > СВ system()
       запускает утилиту date, которая выводит на монитор текущую дату 
       и время, т.е. дату и время поступления сигнала. */
    system("date");
    /* Безусловный нелокальный переход в последнее состояние процесса, 
       сохраненное функцией sigsetjmp(). Единица - устанавливаемое возвращаемое 
       значение для последней выполненной функции sigsetjmp(). */
    siglongjmp(a1, 1); // Возврат в последнее запомненное состояние процесса.
}