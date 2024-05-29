#!/bin/bash
 
# Функция для отображения текущего состояния игрового поля
function display_board {
    clear
    for ((i = 0; i < 4; i++)) 
    do
        for ((j = 0; j < 4; j++)) 
        do
            printf "%3s " "${board[i*4 + j]}"
        done
        echo
    done
}
 
# Функция для перемешивания элементов на игровом поле
function shuffle_board {
    for ((i = 0; i < 1000; i++)) 
    do
        random=$((RANDOM % 15))
        move_tile $((random / 4 + 1)) $((random % 4 + 1))
    done
 
    moves=0
}
 
# Функция для проверки, является ли заданная позиция корректной
function is_valid_position {
    local row=$1
    local col=$2
    if ((row >= 1 && row <= 4 && col >= 1 && col <= 4))
    then
        return 0
    else
        return 1
    fi
}
 
# Функция для обмена пустой ячейки с соседней плиткой
function move_tile {
    local row=$1
    local col=$2
 
    if is_valid_position $row $col
    then
        if [ ${board[(row-1)*4 + col-1]} == "_" ] 
        then
            return
        fi
 
        # Проверка возможности перемещения плитки в пустую ячейку
        if is_valid_position $((row - 1)) $col && [ ${board[((row-2)*4)+col-1]} == "_" ] # вверх
        then
            swap_tiles $row $col $((row-1)) $col
            ((moves++))
        elif is_valid_position $((row + 1)) $col && [ ${board[(row*4)+col-1]} == "_" ] # вниз
        then
            swap_tiles $row $col $((row+1)) $col
            ((moves++))
        elif is_valid_position $row $((col - 1)) && [ ${board[(row-1)*4+col-2]} == "_" ] # влево
        then
            swap_tiles $row $col $row $((col-1))
            ((moves++))
        elif is_valid_position $row $((col + 1)) && [ ${board[(row-1)*4+col]} == "_" ] # вправо
        then
            swap_tiles $row $col $row $((col+1))
            ((moves++))
        fi
    fi
}
 
# Функция для обмена плиток между двумя ячейками
function swap_tiles {
    local row1=$1
    local col1=$2
    local row2=$3
    local col2=$4
 
    local temp=${board[(row1-1)*4 + col1-1]}
    board[(row1-1)*4 + col1-1]=${board[(row2-1)*4 + col2-1]}
    board[(row2-1)*4 + col2-1]=$temp
}
 
# Функция для нахождения координат ячейки с заданным номером
function find_tile_coordinates {
    local target=$1
    for ((row = 0; row < 4; row++)) 
    do
        for ((col = 0; col < 4; col++)) 
        do
            if [[ ${board[row*4 + col]} == "$target" ]]
            then
                echo "$((row+1)) $((col+1))"
                return
            fi
        done
    done
}
 
# Функция проверка победы 
function check_win {
    local win_board=($(seq 1 15))
    win_board+=("_")

    for ((i = 0; i < 16; i++))
    do
        if [ "${board[i]}" != "${win_board[i]}" ]
        then
            return 1  # Игрок не выиграл
        fi
    done

    echo "Поздравляем! Вы выиграли!"
    echo "Ходов сделано: $moves"

    log_event "Победа"

    exit 0  # Игрок выиграл
}

# Функция для логирования событий
function log_event {
    tag=$(echo "[DATE_PLACEHOLDER]" | sed "s/DATE_PLACEHOLDER/$(date +'%Y-%m-%d %H:%M:%S')/")
    echo "$tag $1" >> "$log_file"
}

# Глобальные переменные
board=($(seq 1 15))
board+=("_")

#board=($(seq 1 14))
#board+=("_")
#board+=("15")

moves=0
log_file="game_log.txt"

function main {
    # Перемешивание плиток
    shuffle_board

    log_event "Игра началась. Исходное состояние поля:"
    for ((i = 0; i < ${#board[@]}; i+=4)); do
        log_event "${board[i]} ${board[i+1]} ${board[i+2]} ${board[i+3]}"
    done

    # Основной игровой цикл
    while true
    do
        display_board
        check_win

        echo "Ходов сделано: $moves"
        echo "Введите номер плитки для перемещения (1-15) или 'q' для выхода:"
        read input
    
        if [ "$input" == "q" ]
        then
            echo "Игра завершена. До свидания!"
            break
        fi
    
        if ((input >= 1 && input <= 15))
        then
            local coordinates=$(find_tile_coordinates $input)
            if [ -n "$coordinates" ] 
            then
                local row=${coordinates[0]}
                local col=${coordinates[1]}
                move_tile $row $col
                
                log_event "$(printf "Передвинута плитка %+2s: [%s%s], ходов: %d" "$input" "$row" "$col" "$moves")"
            else
                echo "Некорректный ввод. Плитка с номером $input не найдена."
                sleep 2
            fi
        else
            echo "Некорректный ввод. Введите номер плитки от 1 до 15 или 'q' для выхода."
            sleep 2
        fi
    done

    log_event "Игра окончена"
}

# Инициализация лога
echo -n > "$log_file"

if [ -n "$1" ];
then
    RANDOM=$1
    log_event "Seed: $1 (из консоли)"
elif [ -s "seed.txt" ]
then
    SEED=$(< "seed.txt")
    RANDOM=$SEED
    log_event "Seed: $SEED (из файла seed.txt)"
else
    log_event "Seed: не задан"
fi

# Перенаправление ошибок
exec 2>>$log_file 

main 