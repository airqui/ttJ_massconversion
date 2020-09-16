#!/bin/bash
####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

mass=$1
en=$2
pt=$3

source send_1mass_2scale_arg.sh $mass "1" "mur1" "1" "muf1" $en $pt
source send_1mass_2scale_arg.sh $mass "1" "mur1" "2" "muf2" $en $pt
source send_1mass_2scale_arg.sh $mass "1" "mur1" "0.5" "muf0.5" $en $pt

source send_1mass_2scale_arg.sh $mass "2" "mur2" "1" "muf1" $en $pt
source send_1mass_2scale_arg.sh $mass "2" "mur2" "2" "muf2" $en $pt
source send_1mass_2scale_arg.sh $mass "2" "mur2" "0.5" "muf0.5" $en $pt

source send_1mass_2scale_arg.sh $mass "0.5" "mur0.5" "1" "muf1" $en $pt
source send_1mass_2scale_arg.sh $mass "0.5" "mur0.5" "2" "muf2" $en $pt
source send_1mass_2scale_arg.sh $mass "0.5" "mur0.5" "0.5" "muf0.5" $en $pt



#source send_1mass_2scale_arg.sh $mass "2" "mu2" $en $pt
#source send_1mass_2scale_arg.sh $mass "0.5" "mu0.5" $en $pt
