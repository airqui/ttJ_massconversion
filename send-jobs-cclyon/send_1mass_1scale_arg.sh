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
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_born_gg"
                                                                                                        
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
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_born_qqb"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob


#----------
export PROCESS=$sqrt" --ktmin "$pt" --leadingorder --virtual --gqb"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_born_gqb"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --leadingorder --virtual --qg"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_born_qg"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 


#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# VIRTUAL PROCESSES, 
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

export PROCESS=$sqrt" --ktmin "$pt" --virtual --gg"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_virtual_gg_2"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --virtual --qqb"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_virtual_qqb"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --virtual --gqb"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_virtual_gqb"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --virtual --qg"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_virtual_qg"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# REAL PROCESSES, 
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

export PROCESS=$sqrt" --ktmin "$pt" --real --proc 0"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_real_0_2"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 1"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_real_1"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 3"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_real_3"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 6"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_real_6"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 7"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_real_7"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 8"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_real_8"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 9"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_real_9"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 11"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_real_11"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 13"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_real_13"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 14"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_real_14"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 15"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_real_15"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 17"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_real_17"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# SUBTRACTION PROCESSES, 
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

export PROCESS=$sqrt" --ktmin "$pt" --subtractions --proc 18"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_subtractions_18"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------

export PROCESS=$sqrt" --ktmin "$pt" --subtractions --proc 20"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_subtractions_20"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --subtractions --proc 21"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_subtractions_21"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --subtractions --proc 24"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALE"_subtractions_24"
                                                                                                        
source modifyJOB
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest_$NAMEjob
fi
rm jobtest_$NAMEjob 
