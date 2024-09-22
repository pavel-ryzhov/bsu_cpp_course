# Небольшой гайд по настройке VSCode + WSL + CMake

1) поставить VS Code, WSL (инструкция в [docs/SETUP.md](docs/SETUP.md))
2) поставить в WSL `cmake`, `clang` и всё, что нужно, с помощью команды: `sudo apt install build-essential gdb cmake clang clang-format clang-tidy`
3) установить в VS Code расширения:
   - C/C++ Extension Pack (автор — Microsoft), WSL (Microsoft),
   - CMake (twxs),
   - CMake Tools (Microsoft),
   - Clang-Format (Xaver Hellauer)

Итого, что имеем:

- В WSL можно с помощью команды `code .` запустить VS Code из директории проекта прямо в WSL.
- Можно запускать тесты заданий из нового бокового меню «CMake» с помощью выбора в контекстном меню «`Run in Terminal`» на нужном target. Пример: выбрать «`01_first_tasks/test_binpow`», открыть контекстное меню, выбрать «`Run in Terminal`» — вуаля: в Терминале видим «`All tests passed`» или ошибку, что пошло не так.
- Можно использовать clang-format с помощью «`Format Selection`» (выбранный фрагмент) или «`Format Document`» (весь документ) в
контекстном меню
- Для power user'ов: можно использовать команды расширений CMake и CMake Tools, которые доступны через `>` в верхнем поле

### Небольшой Q&A

##### Как запустить линтер локально?
1) перейти в терминале в build: `cd build`
2) запустить `../run_linter.sh <путь из корня репозитория к папке с задачей>`. Пример: `../run_linter.sh 00_test/sum`

##### Почему я не рекомендую использовать расширения для clang-tidy?
Они не заявлены как stable или имеют малую пользовательскую базу, поэтому никто не гарантирует работоспособность и безопасность.
