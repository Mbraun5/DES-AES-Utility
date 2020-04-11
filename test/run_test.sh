#!/bin/bash

(cd .. && make) > null.txt

num_tests=5
file_size=20000

tst="$(shuf -n ${num_tests} des_keys.txt)"
i=0
echo "------------DES TESTS------------"
for t in ${tst[@]}; do
	echo "Generating test file..."
	./generate_file $i $file_size
	((i=i+1))
	echo "Running test with key: $t"
	echo "Encoding file..."
	../cipher DES $t ENC test_file.txt enc.txt > null.txt
	if [ "$?" != 0 ]
	then
		echo "TEST FAILED! Encoding file exited with exit status failure."
		pass="False"
	else
		echo "Decoding file..."
		../cipher DES $t DEC enc.txt dec.txt > null.txt
		if [ "$?" != 0 ]
		then
			echo "TEST FAILED! Decoding file exited with exit status failure."
			pass="False"
		else
			res=$(diff test_file.txt dec.txt)
			if [ "$res" != "" ]
			then
				echo "TEST FAILED! Decoded file is not the same as the original."
				pass="False"
			else
				echo "TEST PASSED"
			fi
		fi
	fi
	rm test_file.txt
	echo ""
done

tst="$(shuf -n ${num_tests} aes_keys.txt)"
i=0
echo "------------AES TESTS------------"
for t in ${tst[@]}; do
	echo "Generating test file..."
	./generate_file $i $file_size
	((i=i+1))
	echo "Running test with key: $t"
	echo "Encoding file..."
	../cipher AES $t ENC test_file.txt enc.txt > null.txt
	if [ "$?" != 0 ]
	then
		echo "TEST FAILED! Encoding file exited with exit status failure."
		pass="False"
	else
		echo "Decoding file..."
		../cipher AES $t DEC enc.txt dec.txt > null.txt
		if [ "$?" != 0 ]
		then
			echo "TEST FAILED! Decoding file exited with exit status failure."
			pass="False"
		else
			res=$(diff test_file.txt dec.txt)
			if [ "$res" != "" ]
			then
				echo "TEST FAILED!"
				pass="False"
			else
				echo "TEST PASSED"
			fi
		fi
	fi
	rm test_file.txt
	echo ""
done

(cd .. && make clean) > null.txt
rm enc.txt dec.txt null.txt

if [ "$pass" == "False" ]
then
	echo "INTEGRATION TEST FAILED"
	exit 1
fi

echo "INTEGRATION TEST PASSED"
exit 0
