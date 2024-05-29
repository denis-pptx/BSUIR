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
 
function move_tile_cust {
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

# Функция для перемешивания элементов на игровом поле
function shuffle_board {
    for ((i = 0; i < 1000; i++)) 
    do
        random=$((RANDOM % 15))
        move_tile_cust $((random / 4 + 1)) $((random % 4 + 1))
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
 
## Функция для получения текущих координат пустой клетки
function get_empty_coordinates {
    for ((row = 0; row < 4; row++)) 
    do
        for ((col = 0; col < 4; col++)) 
        do
            if [[ ${board[row*4 + col]} == "_" ]]
            then
                echo "$row $col"
                return
            fi
        done
    done
}

# Функция для обмена пустой ячейки с соседней плиткой
function move_tile {
    local direction=$1
    local current_empty_coordinates

    current_empty_coordinates=($(get_empty_coordinates))
    local empty_row=${current_empty_coordinates[0]}
    local empty_col=${current_empty_coordinates[1]}

    empty_row=$((empty_row+1))
    empty_col=$((empty_col+1))
    
    case "$direction" in
        "w") move_up $empty_row $empty_col;;
        "s") move_down $empty_row $empty_col;;
        "a") move_left $empty_row $empty_col;;
        "d") move_right $empty_row $empty_col;;
    esac
}

# Функция для движения пустой клетки вверх
function move_up {
    local row=$1
    local col=$2
    
    local target_row=$((row - 1))
    local target_col=$col

  
    if is_valid_position $target_row $target_col
    then
    	swap_tiles $row $col $target_row $target_col
    	((moves++))
    fi
 
}

# Функция для движения пустой клетки вниз
function move_down {
    local row=$1
    local col=$2

    local target_row=$((row + 1))
    local target_col=$col


    if is_valid_position $target_row $target_col
    then
    	swap_tiles $row $col $target_row $target_col
    	((moves++))
    fi
}

# Функция для движения пустой клетки влево
function move_left {
    local row=$1
    local col=$2

    local target_row=$row
    local target_col=$((col - 1))

   
    if is_valid_position $target_row $target_col
    then
    	swap_tiles $row $col $target_row $target_col
    	((moves++))
    fi
}

# Функция для движения пустой клетки вправо
function move_right {
    local row=$1
    local col=$2

    local target_row=$row
    local target_col=$((col + 1))

    if is_valid_position $target_row $target_col
    then
    	swap_tiles $row $col $target_row $target_col
    	((moves++))
    fi
}


 
# Функция для обмена плиток между двумя ячейками
function swap_tiles {
    local row1=$1
    local col1=$2
    local row2=$3
    local col2=$4
    
    #echo $row1 $col1
    #echo $row2 $col2
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



    exit 0  # Игрок выиграл
}


# Глобальные переменные
board=($(seq 1 15))
board+=("_")

moves=0

function main {
    # Перемешивание плиток
    shuffle_board

    # Основной игровой цикл
    while true
    do
        display_board
        check_win

        echo "Ходов сделано: $moves"
        echo "Введите номер направление для перемещения пустой клетки ('w', 'a', 's', 'd') или 'q' для выхода:"
        read -n 1 input
    
        if [ "$input" == "q" ]
        then
            
            echo -e "\nИгра завершена. До свидания!"
            break
        fi
        
        
        move_tile $input

        #return
    done

}


if [ -n "$1" ];
then
    RANDOM=$1
elif [ -s "seed.txt" ]
then
    SEED=$(< "seed.txt")
    RANDOM=$SEED
fi



main 
