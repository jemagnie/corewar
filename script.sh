echo "definitely lost: 0 bytes in 0 blocks
indirectly lost: 0 bytes in 0 blocks
possibly lost: 72 bytes in 3 blocks" > control
if [ -e asm ]; then
for i in ./champs/*.s
do
	valgrind ./asm $i 1>/dev/null 2>valgrind_tmp
	awk '/definitely lost/ , /possibly lost/  {print $2,$3,$4,$5,$6,$7,$8 }' valgrind_tmp > leak_tmp
	echo "$i :"
	if [ -e ${i%??}.cor ];then
		rm ${i%??}.cor
	fi
	if cmp control leak_tmp >/dev/null
		then echo "\\033[1;32m\t- valgrind [OK]\\033[0m"
	else echo "\\033[1;31m\t- valgrind [KO]\\033[0m" && cat leak_tmp
	fi
	./champs/asm $i >err_asm
	./asm -o tmp.cor $i 2>err_tmp 1>/dev/null
	if [ -e ${i%??}.cor ] && [ -e tmp.cor ];then
	{
		if cmp ${i%??}.cor tmp.cor
			then echo "\\033[1;32m\t- cmp [OK]\\033[0m"
		else
			echo "\\033[1;31m\t- cmp [KO]\\033[0m"
		fi
	}
	elif [ -e ${i%??}.cor ] || [ -e tmp.cor ];then
	{
		echo "\\033[1;33m\t- cmp [DIFF]\\033[0m"
		if [ -e ${i%??}.cor ];then
			cat err_tmp
		else
			cat err_asm
		fi
	}
	else
		echo "\\033[1;36m\t- cmp [OK]\\033[0m"
	fi
	rm valgrind_tmp
	rm leak_tmp
	rm err_tmp
	rm err_asm
	rm -rf asm.dSYM
	if [ -e ${i%??}.cor ]
		then rm ${i%??}.cor
	fi
	if [ -e tmp.cor ]
		then rm tmp.cor 
	fi
done
else
	echo "\\033[1;35mMISSING ASM\\033[0m"
fi
echo "\\033[1;35mTEST FINISH\\033[0m"
rm control
