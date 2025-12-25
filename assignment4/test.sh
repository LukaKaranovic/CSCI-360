#! /usr/bin/bash

echo ____________________________________________________________________________
echo                                CSCI 360 Assignment5

if [ ! -d resource/output ]; then
    mkdir -p resource/output
fi

cat /dev/null > resource/output/results.txt
cat /dev/null > resource/output/results_diff.txt
cat /dev/null > resource/output/large_results.txt
cat /dev/null > resource/output/large_results_diff.txt


bin/vmm resource/input/BACKING_STORE.bin resource/input/addresses.txt > resource/output/results.txt


echo ____________________________________________________________________________
echo Your regular results
echo
tail -n 4 resource/output/results.txt
echo ____________________________________________________________________________
echo Expected regular results
echo
tail -n 4 resource/input/correct_results.txt
echo ____________________________________________________________________________

diff -y resource/input/correct_results.txt resource/output/results.txt > resource/output/results_diff.txt

echo Differences between your regular results and correct regular results
echo ____________________________________________________________________________
echo 
cat resource/output/results_diff.txt | grep -e "|" | tail -n 25


bin/vmm resource/input/BACKING_STORE.bin resource/input/large_addresses.txt > resource/output/large_results.txt


echo ____________________________________________________________________________
echo Your large results
echo
tail -n 4 resource/output/large_results.txt
echo ____________________________________________________________________________
echo Expected large results
echo
tail -n 4 resource/input/large_correct_results.txt
echo ____________________________________________________________________________


diff -y resource/input/large_correct_results.txt resource/output/large_results.txt > resource/output/large_results_diff.txt


echo Differences between your large results and correct large results
echo ____________________________________________________________________________
echo 
cat resource/output/large_results_diff.txt | grep -e "|" | tail -n 25
echo ____________________________________________________________________________

echo

