gcc -c main.c 
gcc -c testing_ADC.c
gcc -c test_ADC.c
gcc main.o testing_ADC.o test_ADC.c -o Test_All.exe 