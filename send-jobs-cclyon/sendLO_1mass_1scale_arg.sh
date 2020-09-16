#!/bin/bash
####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
export MASS=$1

export SCALE=$2
export muSCALE=$3

export energy=$4

export pt=$5


export sqrt="aa"

if [ $energy == 'LHC8' ]
then
    sqrt="--sqrtshad=8000"
fi

if [ $energy == 'LHC13' ]
then
    sqrt="--sqrtshad=13000"
fi

if [ $energy == 'LHC14' ]
then
    sqrt="--sqrtshad=14000"
fi

echo $energy
echo $sqrt

folder="/pbs/home/a/airles/private/ttJ_scripts_2019/production_2020/output/"
###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# BORN  PROCESSES, 
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

export PROCESS=$sqrt" --ktmin "$pt" --leadingorder --virtual --gg"
export NAMEjob=$energy"_CT10_mt"$MASS"_"$muSCALE"_pt"$pt"_born_gg"
                                                                                                        
source modifyJOB
#qsub jobtest_$NAMEjob
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --leadingorder --virtual --qqb"
export NAMEjob=$energy"_CT10_mt"$MASS"_"$muSCALE"_pt"$pt"_born_qqb"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob


#----------
export PROCESS=$sqrt" --ktmin "$pt" --leadingorder --virtual --gqb"
export NAMEjob=$energy"_CT10_mt"$MASS"_"$muSCALE"_pt"$pt"_born_gqb"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --leadingorder --virtual --qg"
export NAMEjob=$energy"_CT10_mt"$MASS"_"$muSCALE"_pt"$pt"_born_qg"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 


