# Потоки в c++

Поток — это по сути последовательность инструкций, которые выполняются параллельно с другими потоками. Каждая программа создает по меньшей мере один поток: основной, который запускает функцию main(). Программа, использующая только главный поток, является однопоточной; если добавить один или более потоков, она станет многопоточной.
Потоки — это способ сделать несколько вещей одновременно. Это может быть полезно, например, для отображения анимации и обработки пользовательского ввода данных во время загрузки изображений или звуков. Потоки также широко используется в сетевом программировании, во время ожидания получения данные будет продолжаться обновление и рисование приложения.

Пример создания потока:
```c++
#include <thread>
 
void threadFunction()
{
     // do smth
}
 
int main()
{
     std::thread thr(threadFunction); // Поток запустится сразу после создания
     thr.join(); // Блокируем основной поток, пока thr не завершит свою работу
     return 0;
}
```

Если не ожидать завершения потоков, то они могут быть завершены раньше времени автоматически в момент, когда завершится основной поток программы.

## Передача параметров в поток.

Пример:
```c++
void threadFunction(int i, double d, const std::string &s)
{
     std::cout << i << ", " << d << ", " << s << std::endl;
}

int main()
{
     std::thread thr(threadFunction, 1, 2.34, "example"); // Все пераметры передаются по значению, даже если функция принимает ссылку
     thr.join(); // Блокируем основной поток, пока thr не завершит свою работу
     return 0;
}
```


## Передача параметров в поток по ссылке.

Если в функцию необходимо передать параметры по ссылке, они должны быть обернуты в `std::ref` или `std::cref`.

Пример:
```c++
void threadFunction(int &a)
{
     a++;
}
 
int main()
{
     int a = 1;
     std::thread thr(threadFunction, std::ref(a)); // Передаём параметр по ссылке
     thr.join(); // Блокируем основной поток, пока thr не завершит свою работу
     std::cout << a << std::endl; 
     return 0;
}
```
Лекция 8

## Получение данных из потока
```c++
int threadFunction(int a, int b)
{
     return a + b;
}
 
int main()
{
     int a = 1;
     int b = 5;
     
     std::future<int> result;  // объект для хранения результатов асинхронных вычислений
     result = std::async(threadFunction, a, b);  // запуск функции в отдельном потоке
     
     result.wait();  // Блокируем основной поток
     std::cout << result.get() << std::endl; 
     return 0;
}
```
`Result` - имеет тип данных `std::future`, который хранит в себе `int`
## Std::future

Шаблон класса `std::future` предоставляет механизм для доступа к результату асинхронных операций:
- Асинхронная операция (создается с помощью `std::async` , `std::packaged_task` или `std::promise`) - может предоставить объект std::future создателю этой асинхронной операции.
- Создатель асинхронной операции может затем использовать различные методы для запроса, ожидания или извлечения значения из `std::future` . Эти методы могут блокироваться, если асинхронная операция еще не предоставила значение.
- Когда асинхронная операция готова отправить результат создателю, он может сделать это (например, `std::promise::set_value`), который связан с `std::future` создателя .

Обратите внимание, что std::future ссылается на общее состояние, которое не используется совместно с другими асинхронными объектами возврата.

**Вкратце:**

- `promise` - это то куда ИСПОЛНИТЕЛЬ положит результат

- `future` - это то откуда ПОТРЕБИТЕЛЬ заберет результат

Исходя из этого, `promise` - хранит результат, а `future` - работает потоком потребителя чтобы этот результат передать (может остановить поток).

Пример:

```C
#include <string>
#include <iostream>
#include <future>

using namespace std;

int main() {
  auto ThreadFunc = []() -> const char* { return "S novym godom!";};  // Функция потока

  // Создать поток и получить связанный с ним фьючерс
  auto f = async(ThreadFunc);

  // Ожидать завершения потока и получит результат из фьючерса
  string s = f.get();

  cout << s;
  return 0;
}
```

Связанная пара `promise-future` образует механизм межпоточного взаимодействия, который позволяет передать результат выполнения потока (или исключение, выброшенное в потоке) в вызывающий поток. Механизм одноразовый, то есть передать получится только результат. Для многократной передачи данных нужно использовать другие средства.

## Блокировки

Блокировки нужны, чтобы два и более потока не могли работать с одними и теми же общими данными

Мьютекс — базовый элемент синхронизации и в С++11 представлен в 4 формах в заголовочном файле <mutex>:
- mutex: обеспечивает базовые функции lock() и unlock() и не блокируемый метод try_lock()
- recursive_mutex: может войти «сам в себя»
- timed_mutex: в отличие от обычного мьютекса, имеет еще два метода: try_lock_for() и try_lock_until()
- recursive_timed_mutex: это комбинация timed_mutex и recursive_mutex

Пример:
```c++
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
 
std::mutex g_lock;
 
void threadFunction()
{
     g_lock.lock(); // Поток блокирует (отмечает) мьютекс
 
     std::cout << "entered thread " << std::this_thread::get_id() << std::endl;
     std::this_thread::sleep_for(std::chrono::seconds(rand()%10));
     std::cout << "leaving thread " << std::this_thread::get_id() << std::endl;
 
     g_lock.unlock(); // Работа завершена, освободим
}
 
int main()
{
     srand((unsigned int)time(0));
     std::thread t1(threadFunction);
     std::thread t2(threadFunction);
     std::thread t3(threadFunction);
     t1.join();
     t2.join();
     t3.join();
     return 0;
}
```

Программа должна выводить примерно следующее
```
entered thread 10144
leaving thread 10144
entered thread 4188
leaving thread 4188
entered thread 3424
leaving thread 3424
```

Пример:
```C++
class T{
public:
	T(){}
	~T(){}
	int print(int cnt){
		std::cout << "Текущий поток: " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		return 66;
	}
};
 
int main(int argc, char* argv[])
{
	cout << "Главный поток = " << std::this_thread::get_id() << endl;
	T t1;
	 std :: future <int> result1 = std :: async (std :: launch :: async, & T :: print, std :: ref (t1), 10); // Адрес метода первого параметра класса, ссылка на объект второго параметра класса
	cout << result1.get() << endl;
 
	T t2;
	 std :: future <int> result2 = std :: async (std :: launch :: deferred, & T :: print, std :: ref (t2), 10); // deffered не создает поток для выполнения вызывающей функции, а только вызывает функцию как нормальная функция
	cout << result2.get() << endl;
 
	return 0;
}
```

# Источники
- https://habr.com/ru/post/182610/
