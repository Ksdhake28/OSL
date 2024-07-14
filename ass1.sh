opt=1
while [ "$opt" -lt 6 ]
do

	echo -e "Choose one of the Following\n1. Create a New Address Book\n2. View Records\n3. Insert new Record\n4. Delete a Record\n5. Modify a Record\n6. Exit"
	read opt
	case $opt in

	1)
		echo "Enter filename"
		read fileName
		if [ -e $fileName ] ; then
			rm $fileName
		fi
		cont=1
		echo -e "NAME\tNUMBER\t\tADDRESS\n===============================\n" | cat >> $fileName
		while [ "$cont" -gt 0 ]
		do
			echo -e "\nEnter Name"
			read name
			echo -e "Enter Phone Number of $name"
			read number
			echo -e "Enter Address of $name"
			read address
			echo -e "$name\t$number\t\t$address" | cat >> $fileName
			echo "Enter 0 to Stop, 1 to Enter next"
			read cont
		done
		;;

	2)
		cat $fileName
		;;
	3)
		echo -e "\nEnter Name"
		read name
		echo "Enter Phone Number of $name"
		read number
		echo "Enter Address of $name"
		read address
		echo -e "$name\t$number\t\t$address" | cat >> $fileName
		;;
	4)
		echo -e "Delete record\nEnter Name/Phone Number (Separate multiple names by space)"
		read patterns
		for pattern in $patterns
		do
			sed -i "/$pattern/d" "$fileName"
		done	
		;;
	5)
		echo -e "Modify record\nEnter Name/Phone Number"
		read pattern
		echo "Enter Name"
		read name
		echo "Enter Phone Number of $name"
		read number
		echo "Enter Address of $name"
		read address
		temp=$(mktemp)
		sed -i "/$pattern/c\\$name\t$number\t$address" "$fileName"
		;;
	esac
done