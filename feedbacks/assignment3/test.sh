#/usr/bin/bash

cat /dev/null > resource/logs.txt
cat /dev/null > resource/student1.txt
cat /dev/null > resource/student2.txt
cat /dev/null > resource/student3.txt
cat /dev/null > resource/student4.txt
cat /dev/null > resource/student5.txt
cat /dev/null > resource/student6.txt
cat /dev/null > resource/student7.txt
cat /dev/null > resource/student8.txt
cat /dev/null > resource/student9.txt
cat /dev/null > resource/student10.txt
cat /dev/null > resource/ta1.txt
cat /dev/null > resource/ta2.txt

bin/simulator

cat resource/logs.txt | grep -e"Student 1 " > resource/student1.txt
cat resource/logs.txt | grep -e"Student 2 " > resource/student2.txt
cat resource/logs.txt | grep -e"Student 3 " > resource/student3.txt
cat resource/logs.txt | grep -e"Student 4 " > resource/student4.txt
cat resource/logs.txt | grep -e"Student 5 " > resource/student5.txt
cat resource/logs.txt | grep -e"Student 6 " > resource/student6.txt
cat resource/logs.txt | grep -e"Student 7 " > resource/student7.txt
cat resource/logs.txt | grep -e"Student 8 " > resource/student8.txt
cat resource/logs.txt | grep -e"Student 9 " > resource/student9.txt
cat resource/logs.txt | grep -e"Student 10 " > resource/student10.txt
cat resource/logs.txt | grep -e"TA 1 "  > resource/ta1.txt
cat resource/logs.txt | grep -e"TA 2 "  > resource/ta2.txt


echo Student 1 events.............................................................
cat resource/student1.txt

echo Student 2 events.............................................................
cat resource/student2.txt

echo Student 3 events.............................................................
cat resource/student3.txt

echo Student 4 events.............................................................
cat resource/student4.txt

echo Student 5 events.............................................................
cat resource/student5.txt

echo Student 6 events.............................................................
cat resource/student6.txt

echo Student 7 events.............................................................
cat resource/student7.txt

echo Student 8 events.............................................................
cat resource/student8.txt

echo Student 9 events.............................................................
cat resource/student9.txt

echo Student 10 events.............................................................
cat resource/student10.txt

echo TA 1 events.............................................................
cat resource/ta1.txt

echo TA 2 events.............................................................
cat resource/ta2.txt


STATS=resource/SIMULATION_STATS.txt

cat /dev/null > "$STATS"

echo Simulation statistics ................ > "$STATS" 2>&1
echo Strudent 1 getting help following times: >> "$STATS" 2>&1
cat resource/student1.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 2 getting help following times: >> "$STATS" 2>&1
cat resource/student2.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 3 getting help following times: >> "$STATS" 2>&1
cat resource/student3.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 4 getting help following times: >> "$STATS" 2>&1
cat resource/student4.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 5 getting help following times: >> "$STATS" 2>&1
cat resource/student5.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 6 getting help following times: >> "$STATS" 2>&1
cat resource/student6.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 7 getting help following times: >> "$STATS" 2>&1
cat resource/student7.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 8 getting help following times: >> "$STATS" 2>&1
cat resource/student8.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 9 getting help following times: >> "$STATS" 2>&1
cat resource/student9.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo Strudent 10 getting help following times: >> "$STATS" 2>&1
cat resource/student10.txt | grep -e "GETTING HELP" | wc -l >> "$STATS" 2>&1
echo TA 1 helping students  following times: >> "$STATS" 2>&1
cat resource/ta1.txt | grep -e "HELPING" | wc -l >> "$STATS" 2>&1
echo TA2 helping students following times: >> "$STATS" 2>&1
cat resource/ta2.txt | grep -e "HELPING" | wc -l >> "$STATS" 2>&1

echo
cat "$STATS"


