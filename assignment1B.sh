#!/bin/bash

check_file(){
    local FILE=$1  
    if [ -f "$FILE" ]; then  
        echo "---Using database $FILE---"
        # Insert "$FILE"
    else  
        echo -e "Name\t||\tNumber\t||\tAddress" >> "$FILE"
        echo "Database Created"
        Insert "$FILE"
    fi
}

check_file_selected(){
    if [ -z "$fileName" ]; then
        echo "No database selected. Please create or select a database first."
        return 1
    fi
    return 0
}

Insert(){
    local FILE=$1
    local cont=1
    while [ "$cont" -gt 0 ]
    do
        echo -e "\nEnter Name"
        read name
        echo -e "Enter Phone Number of $name"
        read number
        echo -e "Enter Address of $name"
        read address
        echo -e "$name\t\t$number\t\t$address" >> "$FILE"
        echo "Enter 0 to Stop, 1 to Enter next record"
        read cont
    done
}

DeleteRecord(){
    local FILE=$1
    echo -e "Delete record\nEnter Name/Phone Number (Separate multiple names by space)"
    read patterns
    for pattern in $patterns
    do
        echo "Deleting records matching pattern: $pattern from file: $FILE"
        sed -i "/$pattern/d" "$FILE"
    done
}

ModifyRecord(){
    local FILE=$1
    echo -e "Modify record\nEnter Name/Phone Number"
    read pattern
    echo "Enter Name"
    read name
    echo "Enter Phone Number of $name"
    read number
    echo "Enter Address of $name"
    read address
    sed -i "/$pattern/c\\$name\\t$number\\t$address" "$FILE"
}

SearchRecord(){
    local FILE=$1
    echo -e "Search record\nEnter Name/Phone Number"
    read pattern
    grep "$pattern" "$FILE"
}

SortRecords(){
    local FILE=$1
    echo -e "Sort records by:\n1. Name\n2. Number\n3. Address"
    read sortOption
    case $sortOption in
        1) sort -k 1,1 "$FILE" -o "$FILE" ;;
        2) sort -k 2,2 "$FILE" -o "$FILE" ;;
        3) sort -k 3,3 "$FILE" -o "$FILE" ;;
        *) echo "Invalid option. Sorting by name by default." ; sort -k 1,1 "$FILE" -o "$FILE" ;;
    esac
    echo "Records sorted successfully."
}

opt=1
while [ "$opt" -lt 8 ]
do
    echo -e "\nChoose one of the Following\n1. Create a New Address Book\n2. View Records\n3. Insert new Record\n4. Delete a Record\n5. Modify a Record\n6. Search Records\n7. Sort Records\n8. Exit"
    read opt
    case $opt in
    1)
        echo "Enter filename"
        read fileName
        check_file "$fileName"
        ;;
    2)
        check_file_selected || continue
        cat "$fileName"
        ;;
    3)
        check_file_selected || continue
        Insert "$fileName"
        ;;
    4)
        check_file_selected || continue
        DeleteRecord "$fileName"
        ;;
    5)
        check_file_selected || continue
        ModifyRecord "$fileName"
        ;;
    6)
        check_file_selected || continue
        SearchRecord "$fileName"
        ;;
    7)
        check_file_selected || continue
        SortRecords "$fileName"
        ;;
    8)
        echo "Exiting..."
        exit 0
        ;;
    *)
        echo "Invalid option. Please try again."
        ;;
    esac
done
