## Программа в этом проекте имеет следующие три функции:
    1. Вычисление значения численного выражения записанного в строковой форме. Аналог функции из матпакета sympy - evalf(). Численным выражением называется выражение , содержащие числа (целые , вещественные , комплексные) , Арифметические операторы ( '+' , '-' , '' , '/' ) и функции тригонометрические ( 'sin' , 'cos' , 'tg' , 'ctg' ) , обратные тригонометрические ( 'arcsin' , 'arccos' , 'arctg' , 'arcctg' ) , логарифмичиские функции ( 'ln' , 'log' ) , экспоненциальные функции ('exp' , 'pow' ) , гиперболические функции ('sh' , 'ch' , 'th' , 'cth' ) , обратные гиперболические функции и обратные гиперболические функции ( 'arcsh' , 'arcch' , 'arcth' , 'arccth' ).Численное выражение не содержит переменных и неизвестных. Некоторые числа могут быть представлены вкачестве литералов, например число ПИ. Его литерал - 'Pi'. В алгоритме литерал заменяется на его численное значение. Примеры выражений , которые могут быть вычислены в этой функции:
      1. "(1+3/4)^2(1-5/74/11)2+(1+5/6)"
      2. "4(3+7)^2" 
      3. "26/(3+4/5)*(1-2/(3+4/5-9/71)+7/9-7/23)^2"
      4. "cos(1)sin(2)"
      5. "arcsin(11/679)"
      6. "arccos(5/17)"
      7. "arctg(1 + exp(3^2))"
      8. "tg(11Pi/16)"
      9. "sin(Pi/4)*cos(Pi/6)sin(Pi/6)"
      10. "log(16 , 64)"
      11. "ln(2+1/901)"
      12. "ln(3/4+8/91)6/7(1+7/29)/(1+tg(3/4Pi)9/13(3/4-8/11)^2)"
      Алгоритм основан на преобразовании выражения в Обратную Польскую Нотацию с последующем вычислением значения выражения с помощью стекового алгоритма.
   2. Представление выражения в виде дерева операторов и печать этого дерева. Дерево операторов - структура данных для представления синтаксической структуры выражений или программы. В этой дереве листьями являются операнды ( числа , алгебраические символы), а другие узлы содеражть операторы. Дерево задает порядок вычисления самого выражения.В нем дочерние поддерева или листья объединяются с помощью родительского оператора.
   3. Вычисление производной функции от функции. Аналог функции из матпакета sympy - diff(). Но без упрощения выражения. Верность выполнения функции тестируется с помощью сравнения с результатом численного дифференцирования. Для того чтобы запустить процесс тестирования этой функции нужно выплнить: 1. В файле algebra.cpp #define DEBUG 0 заменить на #define DEBUG 1. 2. В файле algebra.cpp в функции Verify() установить значение константы n = 7. Перед входом в функцию происходит проверка корректности введенных пользовательских данных Примечания: Цветной вывод на консоль работает только под Windows


    
