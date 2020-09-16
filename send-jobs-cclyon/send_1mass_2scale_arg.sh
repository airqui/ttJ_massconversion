#!/bin/bash
####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
export MASS=$1

export SCALEr=$2
export muSCALEr=$3

export SCALEf=$4
export muSCALEf=$5


export energy=$6

export pt=$7


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
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_born_gg"

source modifyJOB_2scales

if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi 
#rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --leadingorder --virtual --qqb"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_born_qqb"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob


#----------
export PROCESS=$sqrt" --ktmin "$pt" --leadingorder --virtual --gqb"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_born_gqb"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --leadingorder --virtual --qg"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_born_qg"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 


#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# VIRTUAL PROCESSES, 
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

export PROCESS=$sqrt" --ktmin "$pt" --virtual --gg"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_virtual_gg_2"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --virtual --qqb"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_virtual_qqb"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --virtual --gqb"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_virtual_gqb"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --virtual --qg"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_virtual_qg"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# REAL PROCESSES, 
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

export PROCESS=$sqrt" --ktmin "$pt" --real --proc 0"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_real_0_2"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 1"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_real_1"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 3"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_real_3"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 6"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_real_6"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 7"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_real_7"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 8"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_real_8"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 9"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_real_9"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 11"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_real_11"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 13"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_real_13"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 14"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_real_14"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 15"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_real_15"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --real --proc 17"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_real_17"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# SUBTRACTION PROCESSES, 
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

export PROCESS=$sqrt" --ktmin "$pt" --subtractions --proc 18"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_subtractions_18"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------

export PROCESS=$sqrt" --ktmin "$pt" --subtractions --proc 20"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_subtractions_20"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --subtractions --proc 21"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_subtractions_21"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 

#----------
export PROCESS=$sqrt" --ktmin "$pt" --subtractions --proc 24"
export NAMEjob=$energy"_CT10_mt"$MASS"_pt"$pt"_"$muSCALEr"_"$muSCALEf"_subtractions_24"
                                                                                                        
source modifyJOB_2scales
if [ -f $folder$NAMEjob".log" ]; then
    echo "Skip "$NAMEjob
else 
    qsub jobtest2scales_$NAMEjob
fi
rm jobtest2scales_$NAMEjob 
