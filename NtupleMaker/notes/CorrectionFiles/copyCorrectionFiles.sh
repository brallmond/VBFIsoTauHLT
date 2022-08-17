#!/bin/bash
cp L1TUtmTriggerMenuESProducer.cc ../../../L1Trigger/L1TGlobal/plugins/;

cp SealModule.cc ../../../RecoTauTag/HLTProducers/src/;
cp L1TPFJetsSimpleMatching.cc ../../../RecoTauTag/HLTProducers/src/;
cp L1TPFJetsSimpleMatching.h ../../../RecoTauTag/HLTProducers/interface/;

echo "L1TUtmTriggerMenuESProducer.cc diff after copy";
diff L1TUtmTriggerMenuESProducer.cc ../../../L1Trigger/L1TGlobal/plugins/;

echo "SealModule.cc diff after copy";
diff SealModule.cc ../../../RecoTauTag/HLTProducers/src/;

echo "L1TPFJetsSimpleMatching.cc diff after copy";
diff L1TPFJetsSimpleMatching.cc ../../../RecoTauTag/HLTProducers/src/;

echo "L1TPFJetsSimpleMatching.h diff after copy";
diff L1TPFJetsSimpleMatching.h ../../../RecoTauTag/HLTProducers/interface/;

echo "";
echo "If the diff output is none, copy was successful";
echo "remember to scram!";
