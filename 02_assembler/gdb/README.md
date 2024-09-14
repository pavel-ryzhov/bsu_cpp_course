# gdb

В директории задачи находится исполняемый файл `a.out` (Убедитесь что он последней версии!).

Исходный код функции main вам дан.

```c
int main()
{
    char buf[1024];
    fgets(buf, sizeof(buf)-1, stdin);
    if (check_key(buf)) {
        printf("OK\n");
        return 0;
    } else {
        printf("NOT OK\n");
        return 1;
    }
}
```

Исходный код функции check_key вам неизвестен.

Вам нужно понять, какой ключ нужно подать на вход исполняемому файлу,
чтобы он напечатал `OK`.

0. Запишите в файл input.txt вашу гипотезу.

```console
$ echo -n 1234asdf > input.txt
```

1. Установите плагин к gdb.

```console
$ git clone https://github.com/longld/peda.git ~/peda
$ echo "source ~/peda/peda.py" >> ~/.gdbinit
$ echo "set disassembly-flavor att" >> ~/.gdbinit
$ echo "DONE! debug your program with gdb and enjoy"
```

2. Запустите gdb.

```console
$ gdb ./a.out
```

3. Поставьте `breakpoint` на функцию `check_key` и запустите программу.

```console
$ b check_key
$ run < input.txt
```

4. Пошагайте по инструкциям и попробуйте понять что происходит.

```console
$ si
```
