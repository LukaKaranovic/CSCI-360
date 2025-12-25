#/usr/bin/bash

cat /dev/null > resource/logs.txt
cat /dev/null > resource/example_student1.txt
cat /dev/null > resource/example_student2.txt
cat /dev/null > resource/example_student3.txt
cat /dev/null > resource/example_student4.txt
cat /dev/null > resource/example_student5.txt
cat /dev/null > resource/example_student6.txt
cat /dev/null > resource/example_student7.txt
cat /dev/null > resource/example_student8.txt
cat /dev/null > resource/example_student9.txt
cat /dev/null > resource/example_student10.txt
cat /dev/null > resource/example_ta1.txt
cat /dev/null > resource/example_ta2.txt

example/bin/simulator

cat resource/logs.txt | grep -e"Student 1 " > resource/example_student1.txt
cat resource/logs.txt | grep -e"Student 2 " > resource/example_student2.txt
cat resource/logs.txt | grep -e"Student 3 " > resource/example_student3.txt
cat resource/logs.txt | grep -e"Student 4 " > resource/example_student4.txt
cat resource/logs.txt | grep -e"Student 5 " > resource/example_student5.txt
cat resource/logs.txt | grep -e"Student 6 " > resource/example_student6.txt
cat resource/logs.txt | grep -e"Student 7 " > resource/example_student7.txt
cat resource/logs.txt | grep -e"Student 8 " > resource/example_student8.txt
cat resource/logs.txt | grep -e"Student 9 " > resource/example_student9.txt
cat resource/logs.txt | grep -e"Student 10 " > resource/example_student10.txt
cat resource/logs.txt | grep -e"TA 1 "  > resource/example_ta1.txt
cat resource/logs.txt | grep -e"TA 2 "  > resource/example_ta2.txt


echo Student 1 events.............................................................
cat resource/example_student1.txt

echo Student 2 events.............................................................
cat resource/example_student2.txt

echo Student 3 events.............................................................
cat resource/example_student3.txt

echo Student 4 events.............................................................
cat resource/example_student4.txt

echo Student 5 events.............................................................
cat resource/example_student5.txt

echo Student 6 events.............................................................
cat resource/example_student6.txt

echo Student 7 events.............................................................
cat resource/example_student7.txt

echo Student 8 events.............................................................
cat resource/example_student8.txt

echo Student 9 events.............................................................
cat resource/example_student9.txt

echo Student 10 events.............................................................
cat resource/example_student10.txt

echo TA 1 events.............................................................
cat resource/example_ta1.txt

echo TA 2 events.............................................................
cat resource/example_ta2.txt

STATS=resource/EXAMPLE_SIMULATION_STATS.txt

cat /dev/null > "$STATS"

echo Simulation statistics ................ > "$STATS" 2>&1
echo Strudent 1 getting help following times: >> "$STATS" 2>&1
cat resource/example_student1.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 2 getting help following times: >> "$STATS" 2>&1
cat resource/example_student2.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 3 getting help following times: >> "$STATS" 2>&1
cat resource/example_student3.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 4 getting help following times: >> "$STATS" 2>&1
cat resource/example_student4.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 5 getting help following times: >> "$STATS" 2>&1
cat resource/example_student5.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 6 getting help following times: >> "$STATS" 2>&1
cat resource/example_student6.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 7 getting help following times: >> "$STATS" 2>&1
cat resource/example_student7.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 8 getting help following times: >> "$STATS" 2>&1
cat resource/example_student8.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 9 getting help following times: >> "$STATS" 2>&1
cat resource/example_student9.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 10 getting help following times: >> "$STATS" 2>&1
cat resource/example_student10.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo TA 1 helping students  following times: >> "$STATS" 2>&1
cat resource/example_ta1.txt | grep -e "HELPING" | wc -l >> "$STATS" 2>&1
echo TA2 helping students following times: >> "$STATS" 2>&1
cat resource/example_ta2.txt | grep -e "HELPING" | wc -l >> "$STATS" 2>&1

echo
cat "$STATS"

