#!/bin/bash

(cd .. && make) > null.txt

num_tests=3
tst="$(shuf -n ${num_tests} des_keys.txt)"
i=0
echo "------------DES TESTS------------"
for t in ${tst[@]}; do
	echo "Generating test file..."
	./generate_file $i
	((i=i+1))
	echo "Running test with key: $t"
	echo "Encoding file..."
	(cd .. && ./cipher DES $t ENC test/test_file.txt test/enc.txt) > null.txt
	echo "Decoding file..."
	(cd .. && ./cipher DES $t DEC test/enc.txt test/dec.txt) > null.txt

	res=$(diff test_file.txt dec.txt)
	if [ "$res" != "" ]
	then
		echo "TEST FAILED!"
		pass="False"
	else
		echo "TEST PASSED"
	fi
	rm test_file.txt
	echo ""
done

tst="$(shuf -n ${num_tests} aes_keys.txt)"
i=0
echo "------------AES TESTS------------"
for t in ${tst[@]}; do
	echo "Generating test file..."
	./generate_file $i
	((i=i+1))
	echo "Running test with key: $t"
	echo "Encoding file..."
	(cd .. && ./cipher AES $t ENC test/test_file.txt test/enc.txt) > null.txt
	echo "Decoding file..."
	(cd .. && ./cipher AES $t DEC test/enc.txt test/dec.txt) > null.txt
	
	res=$(diff test_file.txt dec.txt)
	if [ "$res" != "" ]
	then
		echo "TEST FAILED!"
		pass="False"
	else
		echo "TEST PASSED"
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
