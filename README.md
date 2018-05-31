**Гречков Станислав, группа 6303**
Лабораторная работа №6:_"Алгоритм Ахо-Корасик"_
# Сборка проекта
В директории с исходными файлами выполнить:

    cmake .
## Сборка всех исполняемых файлов

    make
## Сборка программ для реализации алгоритмов:

 1. **Алгоритм поиска паттернов в тексте**


	`make FullSubstringSearch`

 2. **Алгоритм поиска с джокером**
	`make WildCardSearch`
## Сборка тестирующих программ
1. **Тест алгоритма поиска паттернов в тексте**

    `make AhoCorasicktest `

2. **Тест алгоритма поиска с джокером**

    `make WildCardSearchtest

# Запуск
## Запуск программ для реализации алгоритмов
(ипользование программ - как на Степике)
1. **Алгоритм поиска паттернов в тексте**
	`./FullSubstringSearch

 2. **Алгоритм поиска с джокером**
	./WildCardSearch`
## Прогон всех тестов

   `make test`

## Запуск тестов по отдельности
1. **Тест алгоритма поиска паттернов в тексте**
	./AhoCorasicktest

2. **Тест алгоритма поиска с джокером**
	./WildCardSearchtest
