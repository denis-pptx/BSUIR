#!/bin/bash

add_prefix() {
    local prefix_length=4
    local counter=0
    local sort_option=$1
    local reverse_option=$2
    
    # Получаем отсортированный список файлов в зависимости от критерия
    case "$sort_option" in
        "name")
            local sorted_files=($(ls -1 | sort))
            ;;
        "date")
            local sorted_files=($(ls -1t -r))
            ;;
        "size")
            local sorted_files=($(ls -1S -r))
            ;;
        "random")
            local sorted_files=($(ls -1 | shuf))
            ;;
        *)
            echo "Unknown sort option"
            exit 1
            ;;
    esac

    if [ "$reverse_option" == "reverse" ]; then
        sorted_files=($(echo "${sorted_files[@]}" | awk '{for(i=NF;i>0;i--) print $i}'))
    fi

    for file in "${sorted_files[@]}"; do
        if [ -f "$file" ] && [ "$file" != "$script_name" ]; then
            # Генерация нового префикса с ведущими нулями
            prefix=$(printf "%0${prefix_length}d." "$counter")

            # Старое имя файла
            old_filename=$(basename "$file")

            # Переименование файла с добавлением нового префикса
            mv "$file" "./$prefix${old_filename}"

            ((counter++))
        fi
    done
}


remove_prefix() {
    local script_name="lab2.sh"

    for file in *; do
        if [ -f "$file" ] && [ "$file" != "$script_name" ]; then
            # Получение старого имени файла без префикса и точки
            old_filename="${file##*/}"
            new_filename="$(echo "$old_filename" | sed 's/^[0-9]*\.//')"

            # Проверка, если старое имя НЕ равно новому, то производим переименование
            if [ "$old_filename" != "$new_filename" ]; then
                # Удаление префикса и точки из имени файла
                mv "$file" "$new_filename"
            fi
        fi
    done
}



# Проверка наличия аргументов
if [ $# -eq 0 ]; then
    echo "Usage: $0 [add|remove] [name|date|size|random] [reverse]"
    exit 1
fi

# Определение действия
action=$1

# Определение сортировки
sort_option=${2:-"name"}

# Определение направления сортировки
reverse_option=""
if [ "$3" == "reverse" ]; then
    reverse_option="reverse"
fi

script_name="lab2.sh"

IFS=$'\n'
 
case "$action" in
    "add")
        remove_prefix 
        add_prefix "$sort_option" "$reverse_option"
        ;;
    "remove")
        remove_prefix 
        ;;
    *)
        echo "Unknown action"
        exit 1
        ;;
esac
