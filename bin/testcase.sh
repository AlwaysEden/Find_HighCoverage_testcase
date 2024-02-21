
mkdir 1.gcovfile_branch

a=1
while [ $a -lt 5542 ]
do
	cd ../test
	./t$a.sh
	
	cd -
	gcov -b -i replace #If you want to cover branch, you can use -b option.
	
	mv replace.c.gcov testcase$a.gcov
	sed -i '/branch/!d' testcase$a.gcov #If you want to cover branch, you can use branch instead of lcount. This line is to remove function coverage.
	#sed -i '/,0/d' testcase$a.gcov #It is for line coverage
	
	sed -i '/nottaken/d' testcase$a.gcov 
	sed -i '/notexec/d' testcase$a.gcov 
	
	mv testcase$a.gcov 1.gcovfile_branch

	a=`expr $a + 1`
	rm replace.gcda		
done
