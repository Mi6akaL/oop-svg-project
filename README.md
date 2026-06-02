# SVG Files Editor

Курсов Проект по Обектно-Ориентирано Програмиране (ООП)

---

## Описание на Проекта
Конзолно приложение за обработка на SVG файлове. Програмата чете геометрията от XML-базирания файл, поддържа вътрешна йерархия от фигури (чрез полиморфизъм) и позволява на потребителя да манипулира данните чрез текстови команди.

## Функционалности и команди
* **`open <file>`** – Зарежда фигурите от SVG файл.
* **`close`** – Затваря текущо отворения файл.
* **`save`** – Записва промените в текущия файл.
* **`saveas <file>`** – Записва промените в нов файл.
* **`print`** – Извежда списък с всички заредени фигури.
* **`create <type> <params...>`** – Създава нова фигура.
* **`erase <index>`** – Изтрива фигура по индекс.
* **`translate [<index>] vertical=<dy> horizontal=<dx>`** – Премества фигура/и.
* **`within <region_params...>`** – Проверява кои фигури попадат в даден регион.
* **`help`** – Списък с команди.
* **`exit`** – Изход.

## Структора на Проекта

```text
oop-svg-project/
├── include/              # Заглавни файлове (.hpp)
│   ├── Circle.hpp
│   ├── ColorManager.hpp
│   ├── Ellipses.hpp
│   ├── Line.hpp
│   ├── Polygon.hpp
│   ├── Rect.hpp
│   ├── Shape.hpp
│   ├── ShapeManager.hpp
│   └── SVGparser.hpp
├── src/                  # Имплементационни файлове (.cpp)
│   ├── Circle.cpp
│   ├── ColorManager.cpp
│   ├── Ellipses.cpp
│   ├── Line.cpp
│   ├── Polygon.cpp
│   ├── Rect.cpp
│   ├── Shape.cpp
│   ├── ShapeManager.cpp
│   └── SVGparser.cpp
├── svg_files_examples/   # Примерни .svg файлове за тестване
│   └── generated.output.svg
├── tests/                # Модулни тестове (Unit Tests)
│   ├── doctest.h
│   ├── test_colors.cpp
│   ├── test_geometry.cpp
│   └── test_transformations.cpp
├── main.cpp              # Входна точка и REPL меню
└── README.md
```

## Компилация и стартиране
Изпълнете в главната папка:
```bash
# Компилация на програмата
g++ main.cpp src/*.cpp -o svg_editor

# Стартиране
.\svg_editor.exe
```

## Използвани източници

- [W3C SVG Specification](https://www.w3.org/TR/SVG11/) – За справка относно официалните атрибути, структурата на SVG таговете и правилното парсване на геометрични данни.
- [MDN Web Docs (SVG)](https://developer.mozilla.org/en-US/docs/Web/SVG) – За разбиране на геометричните свойства на примитивите (Circle, Rect, Line) и техните параметри.
- [Cppreference](https://en.cppreference.com/) – Използван за справка при работа със сложни STL алгоритми и методи.
- **Doctest** – Вградената библиотека `doctest.h` за автоматизирано модулно тестване, чрез която се проверява коректността на всяка една функционалност.