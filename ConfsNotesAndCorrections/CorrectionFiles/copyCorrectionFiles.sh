#!/bin/bash
#cp TriggerMenuParser.cc ../../../../L1Trigger/L1TGlobal/plugins/;
#cp L1TUtmTriggerMenuESProducer.cc ../../../../L1Trigger/L1TGlobal/plugins/;
#cp CorrWithOverlapRemovalCondition.cc ../../../../L1Trigger/L1TGlobal/src/;

#cp SealModule.cc ../../../../RecoTauTag/HLTProducers/src/;
#cp L1TPFJetsSimpleMatching.cc ../../../../RecoTauTag/HLTProducers/src/;
#cp PFJetsTauCorrelationCondition.cc ../../../../RecoTauTag/HLTProducers/src/;

#cp L1TPFJetsSimpleMatching.h ../../../../RecoTauTag/HLTProducers/interface/;
#cp PFJetsTauCorrelationCondition.h ../../../../RecoTauTag/HLTProducers/interface/;

echo "TriggerMenuParser.cc diff after copy";
diff TriggerMenuParser.cc ../../../../L1Trigger/L1TGlobal/plugins/; 

echo "L1TUtmTriggerMenuESProducer.cc diff after copy";
diff L1TUtmTriggerMenuESProducer.cc ../../../../L1Trigger/L1TGlobal/plugins/;

echo "CorrWithOverlapRemovalCondition.cc diff after copy";
diff CorrWithOverlapRemovalCondition.cc ../../../../L1Trigger/L1TGlobal/src/;

echo "SealModule.cc diff after copy";
diff SealModule.cc ../../../../RecoTauTag/HLTProducers/src/;

echo "L1TPFJetsSimpleMatching.cc diff after copy";
diff L1TPFJetsSimpleMatching.cc ../../../../RecoTauTag/HLTProducers/src/;

echo "L1TPFJetsSimpleMatching.h diff after copy";
diff L1TPFJetsSimpleMatching.h ../../../../RecoTauTag/HLTProducers/interface/;

echo "PFJetsTauCorrelationCondition.cc diff after copy";
diff PFJetsTauCorrelationCondition.cc ../../../../RecoTauTag/HLTProducers/src/;

echo "PFJetsTauCorrelationCondition.h diff after copy";
diff PFJetsTauCorrelationCondition.h ../../../../RecoTauTag/HLTProducers/interface/;

echo "";
echo "If the diff output is none, copy was successful";
echo "remember to scram!";
