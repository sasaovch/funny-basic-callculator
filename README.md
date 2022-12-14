# funny-basic-callculator
*Additional task seminar 1-2 Programming Languages course*

## Что оно может:

- Дефолтные операции `m` | `math`

    Определение unary/binary автоматическое или по флагу (`-u`, `--unary` | `-b`, `--binary`) соответственно
    - Бинарные операции `-b` `--binary`
        | flag                      | result            |
        | ------------------------- | ----------------- |
        | `-s` `--sub` `--subract`  | `a - b`           |
        | `-a` `--add`              | `a +  b`          |
        | `-m` `--mul` `--multiply` | `a * b`           |
        | `-d` `--div` `--divide`   | `a / b`           |
        | `-o` `--mod` `--modulo`   | `a % b`           |
        | `-p` `--pow` `--power`    | `a`<sup>`b`</sup> |

        Аргументы бинарных операций передаются через `stdin`, и используются в выражениях в том порядке, в котором были переданы

    - Унарные операции `-u` `--unary`
        | flag               | result            |
        | ------------------ | ----------------- |
        | `-f` `--factorial` | `a!`              |
        | `-e` `--exp`       | `e`<sup>`a`</sup> |
        | `-l` `--ln`        | `ln a`            |
        | `-a` `--abs`       | `\|a\|`           |

        Аргумент унарной операций передаются через `stdin` \
		Для использования флага `-a` необходино также указать режим унарной операции

- Конвертер `c` | `convert`
    | flag      | result      |
    | --------- | ----------- |
    | `--kmtom` | km -> mile  |
    | `--mtokm` | mile -> km  |
    | `--kgtop` | kg -> pound |
    | `--ptokg` | pound -> kg |
    | `--dtor`  | deg -> rad  |
    | `--rtod`  | rad -> rad  |
    | `--ctof`  | °C -> °F    |
    | `--ctok`  | °C -> K     |
    | `--ftoc`  | °F -> °C    |
    | `--ftok`  | °F -> K     |
    | `--ktoc`  | K -> °C     |
    | `--ktof`  | K -> °F     |

- Перевод СО `cb` | `change-base`
    | flag                | result                                      |
    | ------------------- | ------------------------------------------- |
    | `--tb` `--to-bin`   | `a`<sub>`10`</sub> -> `a`<sub>`2`</sub>     |
    | `--fb` `--from-bin` | `a`<sub>`2`</sub> -> `a`<sub>`10`</sub>     |
    | `--tx` `--to-hex`   | `a`<sub>`10`</sub> -> `a`<sub>`16`</sub>    |
    | `--fx` `--from-hex` | `a`<sub>`16`</sub> -> `a`<sub>`10`</sub>    |
    | `-f` `--from`       | `a`<sub>*`arg`*</sub> -> `a`<sub>`10`</sub> |
    | `-t` `--to`         | `a`<sub>`10`</sub> -> `a`<sub>*`arg`*</sub> |

- Парсинг строчки (*текста*) бизоном и лексом `io`, и вычисление того что в этой строчке написано

    ```
    -> 101_2 + 10 * 2

    <- 25
    ```