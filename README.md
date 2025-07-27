# Custom C++ List Implementation

Это минималистичная реализация двусвязного списка `List<T>` с поддержкой шаблонов и пользовательских итераторов. Код написан на чистом C++ без использования стандартных контейнеров или вспомогательных структур. Все базовые операции реализованы вручную.

## Особенности

- Шаблонный тип `List<T>`
- Двусвязная структура (next / prev)
- Собственные итераторы (`Iterator`)
- Поддержка конструкций `for (auto& x : list)`
- Базовые операции:
  - `push_back`, `push_front`
  - `pop_back`, `pop_front`
  - `insert`, `erase`
  - `clear`
  - `size`, `empty`

## Пример использования

```cpp
#include "list.h"

int main() {
    Destruct::List<int> numbers;

    numbers.push_back(10);
    numbers.push_front(5);
    numbers.push_back(15);

    for (const auto& num : numbers) {
        std::cout << num << ' ';
    }
    // Вывод: 5 10 15

    numbers.pop_front();
    numbers.pop_back();

    std::cout << "\nAfter pops:\n";
    for (const auto& num : numbers) {
        std::cout << num << ' ';
    }
    // Вывод: 10
}
