#!/bin/bash

source launch_1mass_2scales.sh 172.5 LHC13 30

for mass in 166.5 169.5 171.5 172.5 173.5 175.5 178.5
do 
    source launch_1mass.sh $mass "LHC13" "30"
done 



