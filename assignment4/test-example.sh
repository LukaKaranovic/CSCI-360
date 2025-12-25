#! /usr/bin/bash

echo ____________________________________________________________________________
echo                                CSCI 360 Assignment5 Example

if [ ! -d resource/output ]; then
    mkdir -p resource/output
fi

cat /dev/null > resource/output/example_results.txt
cat /dev/null > resource/output/example_results_diff.txt
cat /dev/null > resource/output/example_large_results.txt
cat /dev/null > resource/output/example_large_results_diff.txt


example/bin/vmm resource/input/BACKING_STORE.bin resource/input/addresses.txt > resource/output/example_results.txt


echo ____________________________________________________________________________
echo Example regular results
echo
tail -n 4 resource/output/example_results.txt
echo ____________________________________________________________________________
echo Expected regular results
echo
tail -n 4 resource/input/correct_results.txt
echo ____________________________________________________________________________

diff -y resource/input/correct_results.txt resource/output/example_results.txt > resource/output/example_results_diff.txt

echo Differences between example regular results and correct regular results
echo ____________________________________________________________________________
echo 
cat resource/output/example_results_diff.txt | grep -e "|" | tail -n 25


example/bin/vmm resource/input/BACKING_STORE.bin resource/input/large_addresses.txt > resource/output/example_large_results.txt


echo ____________________________________________________________________________
echo Example large results
echo
tail -n 4 resource/output/example_large_results.txt
echo ____________________________________________________________________________
echo Expected large results
echo
tail -n 4 resource/input/large_correct_results.txt
echo ____________________________________________________________________________


diff -y resource/input/large_correct_results.txt resource/output/example_large_results.txt > resource/output/example_large_results_diff.txt


echo Differences between example large results and correct large results
echo ____________________________________________________________________________
echo 
cat resource/output/example_large_results_diff.txt | grep -e "|" | tail -n 25
echo ____________________________________________________________________________

echo
