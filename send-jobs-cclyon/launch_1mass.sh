#!/bin/bash
####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

mass=$1
en=$2
pt=$3

source send_1mass_1scale_arg.sh $mass "1" "mu1" $en $pt
source send_1mass_1scale_arg.sh $mass "2" "mu2" $en $pt
source send_1mass_1scale_arg.sh $mass "0.5" "mu0.5" $en $pt


#delta=0.5
#massp="$( bc <<<"$mass + $delta" )"
#massm="$( bc <<<"$mass - $delta" )"

#source sendLO_1mass_1scale_arg.sh $massp "1" "mu1" $en $pt
#source sendLO_1mass_1scale_arg.sh $massp "2" "mu2" $en $pt
#source sendLO_1mass_1scale_arg.sh $massp "0.5" "mu0.5" $en $pt

#source sendLO_1mass_1scale_arg.sh $massm "1" "mu1" $en $pt
#source sendLO_1mass_1scale_arg.sh $massm "2" "mu2" $en $pt
#source sendLO_1mass_1scale_arg.sh $massm "0.5" "mu0.5" $en $pt

