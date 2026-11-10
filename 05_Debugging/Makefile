target = range
test_generates = script1.etalon script2.etalon script1.out script2.out


$(target):	$(target).c
	cc -g -O0 $^ -o $@

script1.etalon:
	echo "5, 1, 12, 1" >> $@
	echo "10, 1, 12, 1" >> $@

script2.etalon:
	echo "-19, -100, 100, 3" >> $@
	echo "-16, -100, 100, 3" >> $@
	echo "-13, -100, 100, 3" >> $@
	echo "-10, -100, 100, 3" >> $@
	echo "-7, -100, 100, 3" >> $@
	echo "-4, -100, 100, 3" >> $@
	echo "-1, -100, 100, 3" >> $@
	echo "2, -100, 100, 3" >> $@

script1.out:
	@gdb -x  script1.gdb --batch --quiet 2>/dev/null | grep @@@ | tr -d '@' > script1.out

script2.out:
	@gdb -x  script2.gdb --batch --quiet 2>/dev/null | grep @@@ | tr -d '@' > script2.out

test:	$(target) script1.out script2.out script1.etalon script2.etalon
	-cmp script1.out script1.etalon
	-cmp script2.out script2.etalon

clean:	
	rm -f $(target) $(test_generates) a.out *~
