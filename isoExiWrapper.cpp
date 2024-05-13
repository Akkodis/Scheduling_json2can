/*
 Class to collect all iso1 exi data types in one object and transform it into a json string.
*/

#include "isoExiWrapper.h"
#include <stdio.h>
#include <regex>

const std::string v2g_start = "start";
const std::string v2g_duration = "duration";
const std::string v2g_Multiplier = "Multiplier";
const std::string v2g_Unit = "Unit";
const std::string v2g_Value = "Value";
const std::string v2g_costKind = "costKind";
const std::string v2g_relativePricePercentage = "relativePricePercentage";
const std::string v2g_RenewableGenerationPercentage = "RenewableGenerationPercentage";
const std::string v2g_CarbonDioxideEmission = "CarbonDioxideEmission";
const std::string v2g_amount = "amount";
const std::string v2g_amountMultiplier = "amountMultiplier";
const std::string v2g_startValue = "startValue";
const std::string v2g_Cost = "Cost";
const std::string v2g_TimeInterval = "TimeInterval";
const std::string v2g_RelativeTimeInterval = "RelativeTimeInterval";
const std::string v2g_PMax = "PMax";
const std::string v2g_PMaxScheduleEntry = "PMaxScheduleEntry";
const std::string v2g_EPriceLevel = "EPriceLevel";
const std::string v2g_ConsumptionCost = "ConsumptionCost";
const std::string v2g_Id = "Id";
const std::string v2g_SalesTariffID = "SalesTariffID";
const std::string v2g_SalesTariffDescription = "SalesTariffDescription";
const std::string v2g_NumEPriceLevels = "NumEPriceLevels";
const std::string v2g_SalesTariffEntry = "SalesTariffEntry";
const std::string v2g_SAScheduleTupleID = "SAScheduleTupleID";
const std::string v2g_PMaxSchedule = "PMaxSchedule";
//const std::string v2g_PMaxDischargeSchedule = "PMaxDischargeSchedule";
const std::string v2g_SalesTariff = "SalesTariff";
//const std::string v2g_BuyBackTariff = "BuyBackTariff";
const std::string v2g_SAScheduleList = "SAScheduleList";
const std::string v2g_SAScheduleTuple = "SAScheduleTuple";

IsoExiWrapper::IsoExiWrapper(/* args */) :
    scheduleList() {
}

IsoExiWrapper::~IsoExiWrapper() {
}

template <typename T> IsoExiWrapper::ErrorList initExiStruct(T &obj, Json::Value jsonObj)
{
    IsoExiWrapper::ErrorList ret;
    ret.addErrorMsg("Type " + std::string(typeid(T).name()) + " not yet supported!\n");
        
    return ret;
}

template <typename T> std::string exit2JsonString(T &obj)
{
    std::string ret;
    throw std::invalid_argument( "toJsonString dos not support type: " + std::string(typeid(T).name()));
        
    return ret;
}

/*
struct iso1RelativeTimeIntervalType {
	uint32_t start ;
	uint32_t duration ;
	unsigned int duration_isUsed:1;
};
*/
IsoExiWrapper::ErrorList initExiStruct(iso1RelativeTimeIntervalType &obj, Json::Value jsonObj)
{
    IsoExiWrapper::ErrorList ret;
    ret.addOkFill("iso1RelativeTimeIntervalType");
    if (jsonObj.isMember(v2g_start))
    {
        Json::Value valObj = jsonObj.get(v2g_start, "");
        obj.start = valObj.asUInt();
        ret.addOKSetValMsg("iso1RelativeTimeIntervalType.start", obj.start);
    }
    else
        ret.addErrorNotInMsg(v2g_start,"iso1RelativeTimeIntervalType!");

    if (jsonObj.isMember(v2g_duration))
    {
        Json::Value valObj = jsonObj.get(v2g_duration, "");
        obj.duration = valObj.asUInt();
        ret.addOKSetValMsg("iso1RelativeTimeIntervalType.duration", obj.duration);
        obj.duration_isUsed = 1;
    }
    else
        obj.duration_isUsed = 0;
    return ret;
}
/*
struct iso1PhysicalValueType {
	int8_t Multiplier ;
	iso1unitSymbolType Unit ;
	int16_t Value ;
};
*/
IsoExiWrapper::ErrorList initExiStruct(iso1PhysicalValueType &obj, Json::Value jsonObj)
{
    IsoExiWrapper::ErrorList ret;
    ret.addOkFill("iso1PhysicalValueType");

    // uint8_t Multiplier
    if (jsonObj.isMember(v2g_Multiplier)) {
        Json::Value valObj = jsonObj.get(v2g_Multiplier, "");
        obj.Multiplier = valObj.asUInt();
        ret.addOKSetValMsg("iso1PhysicalValueType.Multiplier",obj.Multiplier);
    } else
        ret.addErrorNotInMsg(v2g_Multiplier,"iso1PhysicalValueType");
 
    // uint16_t Unit
    if (jsonObj.isMember(v2g_Unit)) {
        Json::Value valObj = jsonObj.get(v2g_Unit, "");
        std::string strVal = valObj.asString(); 
        bool valueValid = true;
        if (strVal.compare("h")==0) obj.Unit = iso1unitSymbolType_h;
        else if (strVal.compare("m")==0) obj.Unit = iso1unitSymbolType_m;
        else if (strVal.compare("s")==0) obj.Unit = iso1unitSymbolType_s;
        else if (strVal.compare("A")==0) obj.Unit = iso1unitSymbolType_A;
        else if (strVal.compare("V")==0) obj.Unit = iso1unitSymbolType_V;
        else if (strVal.compare("W")==0) obj.Unit = iso1unitSymbolType_W;
        else if (strVal.compare("Wh")==0) obj.Unit = iso1unitSymbolType_Wh;
        else
            valueValid = false;
        if (valueValid)
            ret.addOKSetValMsg("iso1PhysicalValueType.Unit", (short)obj.Unit);
        else
            ret.addErrorSetValMsg("iso1PhysicalValueType.Unit", strVal);
    } else
        ret.addErrorNotInMsg(v2g_Unit, "iso1PhysicalValueType");
 
    // uint16_t Value
    if (jsonObj.isMember(v2g_Value)) {
        Json::Value valObj = jsonObj.get(v2g_Value, "");
        obj.Value = valObj.asUInt();
        ret.addOKSetValMsg("iso1PhysicalValueType.Value",obj.Value);
    } else
        ret.addErrorNotInMsg(v2g_Value, "iso1PhysicalValueType");
 
    return ret;
}

/*
struct iso1CostType {
	iso1costKindType costKind ;
	struct iso1PhysicalValueType amount ;
    int8_t amountMultiplier ;
	unsigned int amountMultiplier_isUsed:1;
};
*/
IsoExiWrapper::ErrorList initExiStruct(iso1CostType &obj, Json::Value jsonObj)
{
    IsoExiWrapper::ErrorList ret;
    ret.addOkFill("iso1CostType");
    if (jsonObj.isMember(v2g_costKind))
    {
        Json::Value valObj = jsonObj.get(v2g_costKind, "");
        std::string costKindString = valObj.asString();
        if (strcasecmp(costKindString.c_str(), v2g_relativePricePercentage.c_str()) == 0) 
            obj.costKind = iso1costKindType_relativePricePercentage;
        else if (strcasecmp(costKindString.c_str(), v2g_RenewableGenerationPercentage.c_str()) == 0) 
            obj.costKind = iso1costKindType_RenewableGenerationPercentage;
        else if (strcasecmp(costKindString.c_str(), v2g_CarbonDioxideEmission.c_str()) == 0) 
            obj.costKind = iso1costKindType_CarbonDioxideEmission;
        ret.addOKSetValMsg("iso1CostType.costKind", (uint)obj.costKind);
    }
    else
        ret.addErrorNotInMsg(v2g_costKind, "iso1CostType");
    if (jsonObj.isMember(v2g_amount))
    {
        Json::Value valObj = jsonObj.get(v2g_amount, "");
        obj.amount = valObj.asUInt();
        ret.addOKSetValMsg("iso1CostType.amout", obj.amount);
    }
    else
        ret.addErrorNotInMsg(v2g_amount,"iso1CostType");
    if (jsonObj.isMember(v2g_amountMultiplier))
    {
        Json::Value valObj = jsonObj.get(v2g_amountMultiplier, "");
        obj.amountMultiplier = valObj.asUInt();
        ret.addOKSetValMsg("iso1CostType.amountMultiplier", obj.amountMultiplier);
        obj.amountMultiplier = 1;
    }
    else
        obj.amountMultiplier = 0;
        
    return ret;
}

/*
#define iso1ConsumptionCostType_Cost_ARRAY_SIZE 3
struct iso1ConsumptionCostType {
	struct iso1PhysicalValueType startValue ;
	struct {
		struct iso1CostType array[iso1ConsumptionCostType_Cost_ARRAY_SIZE];
		uint16_t arrayLen;
	} Cost;
};
*/
IsoExiWrapper::ErrorList initExiStruct(iso1ConsumptionCostType &obj, Json::Value jsonObj)
{
    IsoExiWrapper::ErrorList ret;
    ret.addOkFill("iso1ConsumptionCostType");
    if (jsonObj.isMember(v2g_startValue))
    {
        Json::Value valObj = jsonObj.get(v2g_startValue, "");
        IsoExiWrapper::ErrorList retMem = initExiStruct(obj.startValue, valObj);
        ret.append2List(retMem);
    }
    else
        ret.addErrorNotInMsg(v2g_startValue, "iso1ConsumptionCostType");

    obj.Cost.arrayLen = 0;
    if (jsonObj.isMember(v2g_Cost))
    {
        Json::Value valObj = jsonObj.get(v2g_Cost, "");
        if (valObj.size() > iso1ConsumptionCostType_Cost_ARRAY_SIZE)
        {
            ret.addWarningNum(v2g_Cost, valObj.size(), iso1ConsumptionCostType_Cost_ARRAY_SIZE);
            return ret;
        }
        for (size_t i = 0; i < valObj.size(); i++)
        {
            IsoExiWrapper::ErrorList retMem = initExiStruct(obj.Cost.array[obj.Cost.arrayLen], valObj.get(i,""));
            obj.Cost.arrayLen++;
            ret.append2List(retMem);
        }
    } else
        ret.addErrorNotInMsg(v2g_Cost,"iso1ConsumptionCostType");
        
    return ret;
}
/*
struct iso1IntervalType {
	int noContent; / avoid warning 
};
struct iso1PMaxScheduleEntryType {
    struct iso1IntervalType TimeInterval ;
	unsigned int TimeInterval_isUsed:1;
	struct iso1RelativeTimeIntervalType RelativeTimeInterval ;
	unsigned int RelativeTimeInterval_isUsed:1;
	struct iso1PhysicalValueType PMax ;
};
*/
IsoExiWrapper::ErrorList initExiStruct(iso1PMaxScheduleEntryType &obj, Json::Value jsonObj)
{
    IsoExiWrapper::ErrorList ret;
    ret.addOkFill("iso1PMaxScheduleEntryType");
    
     if (jsonObj.isMember(v2g_TimeInterval))
    {
        Json::Value valObj = jsonObj.get(v2g_TimeInterval, "");
        obj.TimeInterval.noContent = valObj.asInt();
        ret.addOKSetValMsg("iso1PMaxScheduleEntryType.TimeInterval.noContent", obj.TimeInterval.noContent);
        obj.TimeInterval_isUsed = 1;
    } else
        obj.TimeInterval_isUsed = 0;

    if (jsonObj.isMember(v2g_RelativeTimeInterval))
    {
        Json::Value valObj = jsonObj.get(v2g_RelativeTimeInterval, "");
        IsoExiWrapper::ErrorList retMem = initExiStruct(obj.RelativeTimeInterval, valObj);
        ret.append2List(retMem);
    } else
        ret.addErrorNotInMsg(v2g_RelativeTimeInterval, "iso1PMaxScheduleEntryType");

    if (jsonObj.isMember(v2g_PMax))
    {
        Json::Value valObj = jsonObj.get(v2g_PMax, "");
        IsoExiWrapper::ErrorList retMem = initExiStruct(obj.PMax, valObj);
        ret.append2List(retMem);
    } else
        ret.addErrorNotInMsg(v2g_PMax, "iso1PMaxScheduleEntryType");
    return ret;
}

/*#define iso1PMaxScheduleType_PMaxScheduleEntry_ARRAY_SIZE 5
struct iso1PMaxScheduleType {
	struct {
		struct iso1PMaxScheduleEntryType array[iso1PMaxScheduleType_PMaxScheduleEntry_ARRAY_SIZE];
		uint16_t arrayLen;
	} PMaxScheduleEntry;
}*/
IsoExiWrapper::ErrorList initExiStruct(iso1PMaxScheduleType &obj, Json::Value jsonObj)
{
    IsoExiWrapper::ErrorList ret;
    ret.addOkFill("iso1PMaxScheduleType");

    obj.PMaxScheduleEntry.arrayLen = 0;
    Json::Value valObj = jsonObj.get(v2g_PMaxScheduleEntry, "");
    if (valObj.size() < 1 &&  valObj.size() > iso1PMaxScheduleType_PMaxScheduleEntry_ARRAY_SIZE)
    {
        ret.addWarningNum(v2g_PMaxScheduleEntry, valObj.size(), iso1PMaxScheduleType_PMaxScheduleEntry_ARRAY_SIZE);
        return ret;
    }
    for (size_t i = 0; i < valObj.size(); i++)
    {
        IsoExiWrapper::ErrorList retMem = initExiStruct(obj.PMaxScheduleEntry.array[obj.PMaxScheduleEntry.arrayLen], valObj.get(i, ""));
        ret.append2List(retMem);
        obj.PMaxScheduleEntry.arrayLen++;
    }
    return ret;
}

/*
#define iso1SalesTariffEntryType_ConsumptionCost_ARRAY_SIZE 3
struct iso1SalesTariffEntryType {
    struct iso1IntervalType TimeInterval ;
	unsigned int TimeInterval_isUsed:1;
	struct iso1RelativeTimeIntervalType RelativeTimeInterval ;
	unsigned int RelativeTimeInterval_isUsed:1;
	uint8_t EPriceLevel ;
	unsigned int EPriceLevel_isUsed:1;
	struct {
		struct iso1ConsumptionCostType array[iso1SalesTariffEntryType_ConsumptionCost_ARRAY_SIZE];
		uint16_t arrayLen;
	} ConsumptionCost;
};
*/
IsoExiWrapper::ErrorList initExiStruct(iso1SalesTariffEntryType &obj, Json::Value jsonObj)
{
    IsoExiWrapper::ErrorList ret; 
    ret.addOkFill("iso1SalesTariffEntryType");

     if (jsonObj.isMember(v2g_TimeInterval))
    {
        Json::Value valObj = jsonObj.get(v2g_TimeInterval, "");
        obj.TimeInterval.noContent = valObj.asInt();
        ret.addOKSetValMsg("iso1SalesTariffEntryType.TimeInterval.noContent", obj.TimeInterval.noContent);
        obj.TimeInterval_isUsed = 1;
    } else
        obj.TimeInterval_isUsed = 0;

    // RelativeTimeInterval
    if (jsonObj.isMember(v2g_RelativeTimeInterval))
    {
        Json::Value valObj = jsonObj.get(v2g_RelativeTimeInterval, "");
        IsoExiWrapper::ErrorList retMem = initExiStruct(obj.RelativeTimeInterval, valObj);
        ret.append2List(retMem);
        obj.RelativeTimeInterval_isUsed = 1;
    } else
        obj.RelativeTimeInterval_isUsed = 0;

    // EPriceLevel and EPriceLevel_isUsed
   if (jsonObj.isMember(v2g_EPriceLevel))
    {
        Json::Value valObj = jsonObj.get(v2g_EPriceLevel, "");
        obj.EPriceLevel = valObj.asUInt();
        obj.EPriceLevel_isUsed = 1;
        ret.addOKSetValMsg("iso1SalesTariffEntryType.EPriceLevel", obj.EPriceLevel);
    } else
        obj.EPriceLevel_isUsed = 0;

    // ConsumptionCost
    obj.ConsumptionCost.arrayLen = 0;
    if (jsonObj.isMember(v2g_ConsumptionCost))
    {
        // collect all ConsumptionCost 
        Json::Value jsonConsumptionCost = jsonObj.get(v2g_ConsumptionCost, "");

        if (jsonConsumptionCost.size() > iso1SalesTariffEntryType_ConsumptionCost_ARRAY_SIZE)
            ret.addWarningNum(v2g_ConsumptionCost, jsonConsumptionCost.size(), iso1SalesTariffEntryType_ConsumptionCost_ARRAY_SIZE);
        else {
            for (size_t i = 0; i < jsonConsumptionCost.size(); i++)
            {
                Json::Value memObj = jsonConsumptionCost.get(i, "");
                IsoExiWrapper::ErrorList retMem = initExiStruct(obj.ConsumptionCost.array[obj.ConsumptionCost.arrayLen], memObj);
                ret.append2List(retMem);
                obj.ConsumptionCost.arrayLen++;
            }
        }
    }
    return ret;
}
/*
struct iso1SalesTariffType {
	struct {
		exi_string_character_t characters[iso1SalesTariffType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	unsigned int Id_isUsed:1;
	uint8_t SalesTariffID ;
	struct {
		exi_string_character_t characters[iso1SalesTariffType_SalesTariffDescription_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  SalesTariffDescription ;
	unsigned int SalesTariffDescription_isUsed:1;
	uint8_t NumEPriceLevels ;
	unsigned int NumEPriceLevels_isUsed:1;
	struct {
		struct iso1SalesTariffEntryType array[iso1SalesTariffType_SalesTariffEntry_ARRAY_SIZE];
		uint16_t arrayLen;
	} SalesTariffEntry;
};
*/
IsoExiWrapper::ErrorList initExiStruct(iso1SalesTariffType &obj, Json::Value jsonObj)
{
    IsoExiWrapper::ErrorList ret;
    ret.addOkFill("iso1SalesTariffType");

    // Id
    obj.Id_isUsed = 0;
    if (jsonObj.isMember(v2g_Id))
    {
        Json::Value valObj = jsonObj.get(v2g_Id, "");
        std::string valText = valObj.asString();
        obj.Id.charactersLen = 0;
        if (valText.size() > iso1SalesTariffType_SalesTariffDescription_CHARACTERS_SIZE)
            ret.addWarningNum(v2g_Id, valText.size(), iso1SalesTariffType_SalesTariffDescription_CHARACTERS_SIZE);
        else {
            obj.Id.charactersLen = valText.size();
            for (size_t i = 0; i < obj.Id.charactersLen; i++)
            {
                obj.Id.characters[i] = valText[i];
            }
            ret.addOKSetValMsg("iso1SalesTariffType.Id", valText);
            obj.Id_isUsed = 0;
        }
    } 

    // uint8_t SalesTariffID
    if (jsonObj.isMember(v2g_SalesTariffID)) {
        Json::Value valObj = jsonObj.get(v2g_SalesTariffID, "");
        obj.SalesTariffID = valObj.asUInt();
        ret.addOKSetValMsg("iso1SalesTariffType.SalesTariffID", obj.SalesTariffID);
    } else
        ret.addErrorNotInMsg(v2g_SalesTariffID, "iso1SalesTariffType");

    // SalesTariffDescription as a char array
    obj.SalesTariffDescription.charactersLen = 0;
    if (jsonObj.isMember(v2g_SalesTariffDescription)) {
        Json::Value valObj = jsonObj.get(v2g_SalesTariffDescription, "");
        std::string valText = valObj.asString();
        if (valText.size() > iso1SalesTariffType_SalesTariffDescription_CHARACTERS_SIZE)
            ret.addWarningNum(v2g_SalesTariffDescription, valText.size(), iso1SalesTariffType_SalesTariffDescription_CHARACTERS_SIZE);
        else {
            obj.SalesTariffDescription.charactersLen = valText.size();
            for (size_t i = 0; i < obj.SalesTariffDescription.charactersLen; i++)
            {
                obj.SalesTariffDescription.characters[i] = valText[i];
            }
           ret.addOKSetValMsg("iso1SalesTariffType.SalesTariffDescription", valText);
        }
        obj.SalesTariffDescription_isUsed = 1;
    } else
        obj.SalesTariffDescription_isUsed = 0;

    // uint8_t NumEPriceLevels  and NumEPriceLevels_isUsed as int
    if (jsonObj.isMember(v2g_NumEPriceLevels))
    {
        Json::Value valObj = jsonObj.get(v2g_NumEPriceLevels, "");
        obj.NumEPriceLevels = valObj.asUInt();
        ret.addOKSetValMsg("iso1SalesTariffType.NumEPriceLevels", obj.NumEPriceLevels);
        obj.NumEPriceLevels_isUsed = 1;
    }
    else
        obj.NumEPriceLevels_isUsed = 0;

    // SalesTariffEntry 
    obj.SalesTariffEntry.arrayLen = 0;
    if (jsonObj.isMember(v2g_SalesTariffEntry))
    {
        // collect all SalesTariffEntry 
        Json::Value valSalesEntries = jsonObj.get(v2g_SalesTariffEntry, "");
        if (valSalesEntries.size() > iso1SalesTariffType_SalesTariffEntry_ARRAY_SIZE)
            ret.addWarningNum(v2g_SalesTariffEntry, valSalesEntries.size(), iso1SalesTariffType_SalesTariffEntry_ARRAY_SIZE);
        else {
            for (size_t i = 0; i < valSalesEntries.size(); i++)
            {
                Json::Value memObj = valSalesEntries.get(i, "");
                IsoExiWrapper::ErrorList retMem = initExiStruct(obj.SalesTariffEntry.array[obj.SalesTariffEntry.arrayLen], memObj);
                ret.append2List(retMem);
                obj.SalesTariffEntry.arrayLen++;
            }
        }
    }
    else
        ret.addErrorNotInMsg(v2g_SalesTariffEntry, "iso1SalesTariffType");
    return ret;
}

/* Complex type name='urn:iso:15118:2:2016:MsgDataTypes,SAScheduleTupleType',  base type name='anyType',  content type='ELEMENT',  isAbstract='false',  hasTypeId='false',  final='0',  block='0',  particle='("urn:iso:15118:2:2016:MsgDataTypes":SAScheduleTupleID,"urn:iso:15118:2:2016:MsgDataTypes":PMaxSchedule,"urn:iso:15118:2:2016:MsgDataTypes":PMaxDischargeSchedule{0-1},"urn:iso:15118:2:2016:MsgDataTypes":SalesTariff{0-1},"urn:iso:15118:2:2016:MsgDataTypes":BuyBackTariff{0-1})',  derivedBy='RESTRICTION'.  
struct iso1SAScheduleTupleType {
	uint8_t SAScheduleTupleID ;
	struct iso1PMaxScheduleType PMaxSchedule ;
	struct iso1SalesTariffType SalesTariff ;
	unsigned int SalesTariff_isUsed:1;
}*/
IsoExiWrapper::ErrorList initExiStruct(iso1SAScheduleTupleType &obj, Json::Value jsonObj)
{
    IsoExiWrapper::ErrorList ret;
    ret.addOkFill("iso1SAScheduleTupleType");

    if (jsonObj.isMember(v2g_SAScheduleTupleID))
    {
        Json::Value valObj = jsonObj.get(v2g_SAScheduleTupleID, "");
        obj.SAScheduleTupleID = valObj.asUInt();
        ret.addOKSetValMsg("iso1SAScheduleTupleType.SAScheduleTupleID", obj.SAScheduleTupleID);
    }
    else
        ret.addErrorNotInMsg(v2g_SAScheduleTupleID, "iso1SAScheduleTupleType");
   
    if (jsonObj.isMember(v2g_PMaxSchedule))
    {
        Json::Value valObj = jsonObj.get(v2g_PMaxSchedule, "");
        IsoExiWrapper::ErrorList retMem = initExiStruct(obj.PMaxSchedule, valObj);
        ret.append2List(retMem);
    }
    else
        ret.addErrorNotInMsg(v2g_PMaxSchedule, "iso1SAScheduleTupleType");

    if (jsonObj.isMember(v2g_SalesTariff))
    {
        Json::Value valObj = jsonObj.get(v2g_SalesTariff, "");
        IsoExiWrapper::ErrorList retMem = initExiStruct(obj.SalesTariff, valObj);
        obj.SalesTariff_isUsed = 1;
        ret.append2List(retMem);
    }
    else
        obj.SalesTariff_isUsed = 0;


    return ret;
}

/*
struct iso1SAScheduleListType {
	struct {
		struct iso1SAScheduleTupleType array[iso1SAScheduleListType_SAScheduleTuple_ARRAY_SIZE];
		uint16_t arrayLen;
	} SAScheduleTuple;
};
*/
IsoExiWrapper::ErrorList initExiStruct(iso1SAScheduleListType &obj, Json::Value jsonObj)
{
    IsoExiWrapper::ErrorList ret;
    ret.addOkFill("v2g_SAScheduleTuple");

    if (jsonObj.isMember(v2g_SAScheduleTuple))
    {
        Json::Value scheduleObj = jsonObj.get(v2g_SAScheduleTuple, "");
        if (scheduleObj.size() > iso1SAScheduleListType_SAScheduleTuple_ARRAY_SIZE)
            ret.addWarningNum(v2g_SAScheduleTuple, scheduleObj.size(), iso1SAScheduleListType_SAScheduleTuple_ARRAY_SIZE);
        else
        {
            for (size_t i = 0; i < scheduleObj.size(); i++)
            {
                Json::Value memObj = scheduleObj.get(i, "");
                IsoExiWrapper::ErrorList retMem = initExiStruct(obj.SAScheduleTuple.array[obj.SAScheduleTuple.arrayLen], memObj);
                ret.append2List(retMem);
                obj.SAScheduleTuple.arrayLen++;
            }
        }
    }
    else
        ret.addErrorNotInMsg(v2g_SAScheduleTuple, "iso1SAScheduleListType");
    return ret;
}


std::string exit2JsonString(iso1SAScheduleListType &obj)
{
    std::string ret;

    return ret;
}


IsoExiWrapper::ErrorList IsoExiWrapper::init( Json::Value jsonObj) {
    IsoExiWrapper::ErrorList ret;
    if (jsonObj.isMember(v2g_SAScheduleList))
    {
        Json::Value slObj = jsonObj.get(v2g_SAScheduleList, "");
        return initExiStruct(scheduleList, slObj);
    }
    return ret;
}
std::string IsoExiWrapper::toJsonString() {
    return exit2JsonString(scheduleList);
}

 void IsoExiWrapper::add2Buffer(std::string text, uint32_t index) {
     bufferStr += text;
     if (iByte != index) {
         std::cout<<index<<" recieved but "<<iByte<<" was expected\n";
     }
     iByte+=4;
     std::cout<<"_______________add2Buffer "<<iByte<<" "<<index<<" "<<numBytes<<"\n";
     isComplete = (iByte)>=numBytes;
 }

void IsoExiWrapper::clear() {
    isComplete = false;
    //std::cout<<bufferStr<<std::endl;
    bufferStr = "";
    numBytes = 0;
    iByte = 0;
}
IsoExiWrapper::ErrorList IsoExiWrapper::evaluate() {
     IsoExiWrapper::ErrorList ret;
    // std::cout<<"evaluate this string: "<<std::endl;
     std::cout<<"evaluate this string: "<<bufferStr<<std::endl;

     std::regex e ("\\\\n");
       bufferStr = std::regex_replace(bufferStr,e,"");
       Json::Value root;
       Json::Reader reader;
       bool parsingSuccessful = reader.parse(bufferStr.c_str(), root); // parse process
       if (!parsingSuccessful)
       {
           std::cout << "Failed to parse"
                     << reader.getFormattedErrorMessages();
           return ret;
        }
        std::cout << "parsing successful\n";
        ret = init(root);
        for (auto &error : ret.elements) {
               if (error.status == IsoExiWrapper::ErrorFlag::isOk)
                   std::cout << "ExiWrapper: " << error.message;
               else if (error.status == IsoExiWrapper::ErrorFlag::isWarning)
                   std::cout << "ExiWrapper - Warning: " << error.message;
               else if (error.status == IsoExiWrapper::ErrorFlag::isError)
                   std::cout << "ExiWrapper - Error : " << error.message;
           }

    return ret;
}