## Цель проекта
###### Перевести всех муравьев из комнаты start в комнату end испольуя наиболее оптимальный маршрут,одновременно в 1ой комнате может находиться только 1 муравей, а также за время не превышающее в идеале 3 сек.

____

## Сборка проекта
###### ->make
____

## Запуск
###### ->./lemin < "карта"

###### - кроме исполняемого файла для запуска необходима карта с комнатами. Карту можно получить с помощью generator(./generator --help  macos only) из папки maps или заполнив вручную.
###### - карта имеет след. структуру ->
![](https://i.imgur.com/rrMKaNZ.png "пример карты")
###### содержание карты:
- 1 строка - число муравьев(до этого числа могут идти только комментарии или незнакомые команды)
- 2 строка - комментарий(может быть в любом месте,будет проигнорирован)
- 3 строка - команда стартовой комнаты(за ней идет название стартовой комнаты для всех муравьев)
- 4 строка - стартовая комната(после идут ее координаты - не используется)
- 5 строка - комната
- 6 строка - аналогично со стартовой идет заключительная комната
- 9 строка - связь между двумя комнатами
- 13 строка - неизвестная команда(будет проигнорирована)
____

### Вывод
![](https://i.imgur.com/RMdH0og.png "Вывод")
