# A json converted schema xml should be transfered into the internal data structure

## 1. From the norm ISO 15118-2:2014(E) t the json
### SAScheduleList
SAScheduleList --> SAScheduleTuple [1..3]
```
"SAScheduleList": {  
    "SAScheduleTuples": [SAScheduleTuple]
}
```
SAScheduleList with 3 entries:
```
"SAScheduleList": {  
    "SAScheduleTuples": [SAScheduleTuple1, SAScheduleTuple2, SAScheduleTuple3]
}
```

### SAScheduleTuple
SAScheduleTuple --> SAScheduleTupleID, PMaxSchedule (,SalesTariff)
```
{SAScheduleTupleID, PMaxSchedule}
```
SAScheduleTuple with Sales Tariff
```
{SAScheduleTupleID, PMaxSchedule, SalesTariff}
```

### SAScheduleTupleID
Value between 1 and 255
```
"SAScheduleTupleID":val   
```
### PMaxSchedule
PMaxSchedule --> PMaxScheduleEntries[1..1024]
```
"PMaxSchedule":{
    PMaxScheduleEntries:[PMaxScheduleEntry1, ..., PMaxScheduleEntry_n]
}
```

### PMaxScheduleEntry
PMaxScheduleEntry --> RelativeTimeInterval, PMax
```
{RelativeTimeInterval, PMax}
```

### RelativeTimeInterval
RelativeTimeInterval --> start(,duration)
```
"RelativeTimeInterval": {  
    "start":val1
}, 
```
with duration
```
"RelativeTimeInterval": {  
    "start":val1,  
    "duration":val2  
}, 
```

### PMax
PMax --> Multiplier, Unit, Value  
Multiplier: range in [-3..3]  
Unit: symbol in unit list
Value: value in range according to unit
```
"PMax": {   
    "Multiplier":val1,  
    "Unit":"text",  
    "Value":val2  
}
```

### SalesTariff
SalesTariff --> {Id, SalesTariffID, SalesTariffDescription, NumEPriceLevels, SalesTariffEntry[1..1024]}
```
"SalesTariff":{
    "Id":"text1",
    "SalesTariffID":val1,
    "SalesTariffDescription":"text2",
    "NumEPriceLevels":val2,
    "SalesTariffEntries": [SalesTariffEntry1,.., SalesTariffEntries_n]
}
```

### SalesTariffEntry
SalesTariffEntry --> {RelativeTimeInterval(, EPriceLevel, ConsumptionCosts[0..3]}
```
{
    "RelativeTimeInterval":{
        "start":0,
        "duration":36000
    },
    "EPriceLevel":1,
    "ConsumptionCosts": [ConsumptionCost1(, ConsumptionCost2,ConsumptionCost3)]
}
```
### ConsumptionCost
ConsumptionCost --> {startValue, Costs[1..3]}
```
{
    "startValue": {
        "Multiplier":val1,
        "Unit":"text1",
        "Value":val2
    },
    "Costs":[Cost1(,Costs2,Costs3)]
}
```
### Cost
Cost --> {costKind, amount(,amountMultiplier)}
amount: unsigned int
costKind: {"relativePricePercentage","RenewableGenerationPercentage","CarbonDioxideEmission"} as text
amountMultiplier: in range [-3,3] but is not supported in internal structure now
```
{
    "costKind":"text1",
    "amount":v1,
    "amountMultiplier":v2 
}
```

## 1. Transfer a schedule xml file, defined in the norm ISO 15118-2:2014(E) into json string as test  
### Example
XML defined in Norm:  
```
<v2gci_t:SAScheduleList>  
  <v2gci_t:SAScheduleTuple>
    <v2gci_t:SAScheduleTupleID>55</v2gci_t:SAScheduleTupleID>  
    <v2gci_t:PMaxSchedule>  
      <v2gci_t:PMaxScheduleEntry>  
        <v2gci_t:RelativeTimeInterval>  
          <v2gci_t:start>0</v2gci_t:start>  
          <v2gci_t:duration>3600</v2gci_t:duration>  
        </v2gci_t:RelativeTimeInterval>  
        <v2gci_t:PMax>  
          <v2gci_t:Multiplier>0</v2gci_t:Multiplier>  
          <v2gci_t:Unit>W</v2gci_t:Unit>  
          <v2gci_t:Value>22000</v2gci_t:Value>  
        </v2gci_t:PMax>  
      </v2gci_t:PMaxScheduleEntry>  
    </v2gci_t:PMaxSchedule>  
  </v2gci_t:SAScheduleTuple>  
</v2gci_t:SAScheduleList>  
  ```
-->  
JSON:  
```
{
    "SAScheduleList": {  
        "SAScheduleTuples": [{  
            "SAScheduleTupleID":55,   
            "PMaxSchedule": {  
                "PMaxScheduleEntries": [{  
                    "RelativeTimeInterval": {  
                        "start"0,  
                        "duration":3600  
                    }, 
                    "PMax": {   
                        "Multiplier":0,  
                        "Unit":"W",  
                        "Value":22000  
                    } 
                }] 
            }  
        }] 
    }
}  
```