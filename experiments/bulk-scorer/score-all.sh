#!/usr/bin/env bash
# MAKE SURE YOU HAVE BUILT THE BULK-SCORER TARGET BEFORE RUNNING THIS SCRIPT
# DATA IS EXPECTED TO BE INSIDE A "data" FOLDER AT THE SAME LEVEL AS THIS SCRIPT

rm bulk-scorer
ln ../cmake-build-debug/bulk-scorer bulk-scorer

./bulk-scorer data/10kERNModel-0101100.csv data/10kERNModel-0101100_scored.csv ERN_0101100 10000
./bulk-scorer data/10kERNModel-1100111.csv data/10kERNModel-1100111_scored.csv ERN_1100111 10000

# ===============================================================================================================================================

./bulk-scorer data/100kERNModel-0101100.csv data/100kERNModel-0101100_scored.csv ERN_0101100 100000
./bulk-scorer data/100kERNModel-1100111.csv data/100kERNModel-1100111_scored.csv ERN_1100111 100000
./bulk-scorer data/100kBackwardPModel.csv data/100kBackwardPModel_scored.csv ERN_1100111 100000

#./bulk-scorer data/100kERNModel-0101100.csv data/100kERNModel-0101100_1000_scored.csv ERN_0101100 100000 1000
#./bulk-scorer data/100kERNModel-1100111.csv data/100kERNModel-1100111_1000_scored.csv ERN_1100111 100000 1000
#./bulk-scorer data/100kBackwardPModel.csv data/100kBackwardPModel_1000_scored.csv ERN_1100111 100000 1000

./bulk-scorer data/100kERNModel-0101100.csv data/100kERNModel-0101100_1300_scored.csv ERN_0101100 100000 1300
./bulk-scorer data/100kERNModel-1100111.csv data/100kERNModel-1100111_1300_scored.csv ERN_1100111 100000 1300
./bulk-scorer data/100kBackwardPModel.csv data/100kBackwardPModel_1300_scored.csv ERN_1100111 100000 1300

#./bulk-scorer data/100kERNModel-0101100.csv data/100kERNModel-0101100_1400_scored.csv ERN_0101100 100000 1400
#./bulk-scorer data/100kERNModel-1100111.csv data/100kERNModel-1100111_1400_scored.csv ERN_1100111 100000 1400
#./bulk-scorer data/100kBackwardPModel.csv data/100kBackwardPModel_1400_scored.csv ERN_1100111 100000 1400

# ===============================================================================================================================================

./bulk-scorer data/1milERNModel-0101100.csv data/1milERNModel-0101100_scored.csv ERN_0101100 1000000
./bulk-scorer data/1milERNModel-1100111.csv data/1milERNModel-1100111_scored.csv ERN_1100111 1000000
./bulk-scorer data/1milBackwardPModel.csv data/1milBackwardPModel_scored.csv ERN_1100111 1000000

#./bulk-scorer data/1milERNModel-0101100.csv data/1milERNModel-0101100_1000_scored.csv ERN_0101100 1000000 1000
#./bulk-scorer data/1milERNModel-1100111.csv data/1milERNModel-1100111_1000_scored.csv ERN_1100111 1000000 1000
#./bulk-scorer data/1milBackwardPModel.csv data/1milBackwardPModel_1000_scored.csv ERN_1100111 1000000 1000

./bulk-scorer data/1milERNModel-0101100.csv data/1milERNModel-0101100_1300_scored.csv ERN_0101100 1000000 1300
./bulk-scorer data/1milERNModel-1100111.csv data/1milERNModel-1100111_1300_scored.csv ERN_1100111 1000000 1300
./bulk-scorer data/1milBackwardPModel.csv data/1milBackwardPModel_1300_scored.csv ERN_1100111 1000000 1300

#./bulk-scorer data/1milERNModel-0101100.csv data/1milERNModel-0101100_1400_scored.csv ERN_0101100 1000000 1400
#./bulk-scorer data/1milERNModel-1100111.csv data/1milERNModel-1100111_1400_scored.csv ERN_1100111 1000000 1400
#./bulk-scorer data/1milBackwardPModel.csv data/1milBackwardPModel_1400_scored.csv ERN_1100111 1000000 1400

# ===============================================================================================================================================

./bulk-scorer data/10milERNModel-0101100.csv data/10milERNModel-0101100_scored.csv ERN_0101100 10000000
./bulk-scorer data/10milERNModel-1100111.csv data/10milERNModel-1100111_scored.csv ERN_1100111 10000000
./bulk-scorer data/10milBackwardPModel.csv data/10milBackwardPModel_scored.csv ERN_1100111 10000000

./bulk-scorer data/10milERNModel-0101100.csv data/10milERNModel-0101100_1300_scored.csv ERN_0101100 10000000 1300
./bulk-scorer data/10milERNModel-1100111.csv data/10milERNModel-1100111_1300_scored.csv ERN_1100111 10000000 1300
./bulk-scorer data/10milBackwardPModel.csv data/10milBackwardPModel_1300_scored.csv ERN_1100111 10000000 1300

#./bulk-scorer data/10milERNModel-0101100.csv data/10milERNModel-0101100_1400_scored.csv ERN_0101100 10000000 1400
#./bulk-scorer data/10milERNModel-1100111.csv data/10milERNModel-1100111_1400_scored.csv ERN_1100111 10000000 1400
#./bulk-scorer data/10milBackwardPModel.csv data/10milBackwardPModel_1400_scored.csv ERN_1100111 10000000 1400

#./bulk-scorer data/10milERNModel-0101100.csv data/10milERNModel-0101100_1000_scored.csv ERN_0101100 10000000 1000
#./bulk-scorer data/10milERNModel-1100111.csv data/10milERNModel-1100111_1000_scored.csv ERN_1100111 10000000 1000
#./bulk-scorer data/10milBackwardPModel.csv data/10milBackwardPModel_1000_scored.csv ERN_1100111 10000000 1000
