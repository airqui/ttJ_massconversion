for mass in {156..178}
do

    ./ExtractData output LHC13 CT10 $mass 1 30 NLO > ../../logfiles/LHC13_CT10_mt${mass}_mu1_pt30.log &
    ./ExtractData output LHC13 CT10 $mass 2 30 NLO > ../../logfiles/LHC13_CT10_mt${mass}_mu2_pt30.log &
    ./ExtractData output LHC13 CT10 $mass 0.5 30 NLO > ../../logfiles/LHC13_CT10_mt${mass}_mu0.5_pt30.log
done

for mass in 155.5 156.5 157.5 158.5 159.5 160.5 161.5 162.5 163.5 164.5 165.5 166.5 167.5 168.5 169.5 170.5 171.5 172.5 173.5 174.5 175.5 176.5 177.5
do
    echo $mass
    ./ExtractData output LHC13 CT10 $mass 1 30 LO > ../../logfiles/LHC13_CT10_mt${mass}_mu1_pt30.log &
    ./ExtractData output LHC13 CT10 $mass 2 30 LO > ../../logfiles/LHC13_CT10_mt${mass}_mu2_pt30.log &
    ./ExtractData output LHC13 CT10 $mass 0.5 30 LO > ../../logfiles/LHC13_CT10_mt${mass}_mu0.5_pt30.log
done


