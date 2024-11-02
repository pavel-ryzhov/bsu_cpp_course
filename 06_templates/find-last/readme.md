#Find Last

Реализуйте шаблон функции `FindLast(first, last, value)`. Функция возвращает итератор на последнее вхождение `value` в
последовательность `[first, last)` или `last` в случае, когда такого вхождения нет.
Можете считать, что итераторы по-крайней мере, [bidirectional](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator).

### Примечания

* Используйте только оператор `==` для сравнения элементов.
* Когда будете сравнивать элементы, будет ошибка clang-tidy, отключите её командой
* Можно использовать:
// NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
