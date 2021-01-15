for mass in {156..178}
do
    ./ExtractData LHC13 CT18NLO $mass 1 30 NLO > ../../ready/LHC13_CT18NLO/results/LHC13_CT18NLO_mt${mass}_pt30_mu1.log &
    ./ExtractData LHC13 CT18NLO $mass 2 30 NLO > ../../ready/LHC13_CT18NLO/results/LHC13_CT18NLO_mt${mass}_pt30_mu2.log &
    ./ExtractData LHC13 CT18NLO $mass 0.5 30 NLO > ../../ready/LHC13_CT18NLO/results/LHC13_CT18NLO_mt${mass}_pt30_mu0.5.log
done

for mass in 155.5 156.5 157.5 158.5 159.5 160.5 161.5 162.5 163.5 164.5 165.5 166.5 167.5 168.5 169.5 170.5 171.5 172.5 173.5 174.5 175.5 176.5 177.5
do
    echo $mass
    ./ExtractData LHC13 CT18NLO $mass 1 30 LO > ../../ready/LHC13_CT18NLO/results/LHC13_CT18NLO_mt${mass}_pt30_mu1.log &
    ./ExtractData LHC13 CT18NLO $mass 2 30 LO > ../../ready/LHC13_CT18NLO/results/LHC13_CT18NLO_mt${mass}_pt30_mu2.log &
    ./ExtractData LHC13 CT18NLO $mass 0.5 30 LO > ../../ready/LHC13_CT18NLO/results/LHC13_CT18NLO_mt${mass}_pt30_mu0.5.log
done


