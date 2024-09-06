/*
 *
 *  Copyright (C) 2008-2012, OFFIS e.V. and ICSMED AG, Oldenburg, Germany
 *  Copyright (C) 2013-2023, J. Riesmeier, Oldenburg, Germany
 *  All rights reserved.  See COPYRIGHT file for details.
 *
 *  Source file for class DRTToleranceTableSequence
 *
 *  Generated automatically from DICOM PS 3.3-2023b
 *  File created on 2023-05-19 16:00:57
 *
 */


#include "dcmtk/config/osconfig.h"     // make sure OS specific configuration is included first

#include "dcmtk/dcmrt/seq/drttts.h"


// --- item class ---

DRTToleranceTableSequence::Item::Item(const OFBool emptyDefaultItem)
  : EmptyDefaultItem(emptyDefaultItem),
    BeamLimitingDeviceAngleTolerance(DCM_BeamLimitingDeviceAngleTolerance),
    BeamLimitingDeviceToleranceSequence(emptyDefaultItem /*emptyDefaultSequence*/),
    GantryAngleTolerance(DCM_GantryAngleTolerance),
    GantryPitchAngleTolerance(DCM_GantryPitchAngleTolerance),
    PatientSupportAngleTolerance(DCM_PatientSupportAngleTolerance),
    TableTopEccentricAngleTolerance(DCM_TableTopEccentricAngleTolerance),
    TableTopLateralPositionTolerance(DCM_TableTopLateralPositionTolerance),
    TableTopLongitudinalPositionTolerance(DCM_TableTopLongitudinalPositionTolerance),
    TableTopPitchAngleTolerance(DCM_TableTopPitchAngleTolerance),
    TableTopRollAngleTolerance(DCM_TableTopRollAngleTolerance),
    TableTopVerticalPositionTolerance(DCM_TableTopVerticalPositionTolerance),
    ToleranceTableLabel(DCM_ToleranceTableLabel),
    ToleranceTableNumber(DCM_ToleranceTableNumber)
{
}


DRTToleranceTableSequence::Item::Item(const Item &copy)
  : EmptyDefaultItem(copy.EmptyDefaultItem),
    BeamLimitingDeviceAngleTolerance(copy.BeamLimitingDeviceAngleTolerance),
    BeamLimitingDeviceToleranceSequence(copy.BeamLimitingDeviceToleranceSequence),
    GantryAngleTolerance(copy.GantryAngleTolerance),
    GantryPitchAngleTolerance(copy.GantryPitchAngleTolerance),
    PatientSupportAngleTolerance(copy.PatientSupportAngleTolerance),
    TableTopEccentricAngleTolerance(copy.TableTopEccentricAngleTolerance),
    TableTopLateralPositionTolerance(copy.TableTopLateralPositionTolerance),
    TableTopLongitudinalPositionTolerance(copy.TableTopLongitudinalPositionTolerance),
    TableTopPitchAngleTolerance(copy.TableTopPitchAngleTolerance),
    TableTopRollAngleTolerance(copy.TableTopRollAngleTolerance),
    TableTopVerticalPositionTolerance(copy.TableTopVerticalPositionTolerance),
    ToleranceTableLabel(copy.ToleranceTableLabel),
    ToleranceTableNumber(copy.ToleranceTableNumber)
{
}


DRTToleranceTableSequence::Item::~Item()
{
}


DRTToleranceTableSequence::Item &DRTToleranceTableSequence::Item::operator=(const Item &copy)
{
    if (this != &copy)
    {
        EmptyDefaultItem = copy.EmptyDefaultItem;
        BeamLimitingDeviceAngleTolerance = copy.BeamLimitingDeviceAngleTolerance;
        BeamLimitingDeviceToleranceSequence = copy.BeamLimitingDeviceToleranceSequence;
        GantryAngleTolerance = copy.GantryAngleTolerance;
        GantryPitchAngleTolerance = copy.GantryPitchAngleTolerance;
        PatientSupportAngleTolerance = copy.PatientSupportAngleTolerance;
        TableTopEccentricAngleTolerance = copy.TableTopEccentricAngleTolerance;
        TableTopLateralPositionTolerance = copy.TableTopLateralPositionTolerance;
        TableTopLongitudinalPositionTolerance = copy.TableTopLongitudinalPositionTolerance;
        TableTopPitchAngleTolerance = copy.TableTopPitchAngleTolerance;
        TableTopRollAngleTolerance = copy.TableTopRollAngleTolerance;
        TableTopVerticalPositionTolerance = copy.TableTopVerticalPositionTolerance;
        ToleranceTableLabel = copy.ToleranceTableLabel;
        ToleranceTableNumber = copy.ToleranceTableNumber;
    }
    return *this;
}


void DRTToleranceTableSequence::Item::clear()
{
    if (!EmptyDefaultItem)
    {
        /* clear all DICOM attributes */
        ToleranceTableNumber.clear();
        ToleranceTableLabel.clear();
        GantryAngleTolerance.clear();
        GantryPitchAngleTolerance.clear();
        BeamLimitingDeviceAngleTolerance.clear();
        BeamLimitingDeviceToleranceSequence.clear();
        PatientSupportAngleTolerance.clear();
        TableTopEccentricAngleTolerance.clear();
        TableTopPitchAngleTolerance.clear();
        TableTopRollAngleTolerance.clear();
        TableTopVerticalPositionTolerance.clear();
        TableTopLongitudinalPositionTolerance.clear();
        TableTopLateralPositionTolerance.clear();
    }
}


OFBool DRTToleranceTableSequence::Item::isEmpty()
{
    return ToleranceTableNumber.isEmpty() &&
           ToleranceTableLabel.isEmpty() &&
           GantryAngleTolerance.isEmpty() &&
           GantryPitchAngleTolerance.isEmpty() &&
           BeamLimitingDeviceAngleTolerance.isEmpty() &&
           BeamLimitingDeviceToleranceSequence.isEmpty() &&
           PatientSupportAngleTolerance.isEmpty() &&
           TableTopEccentricAngleTolerance.isEmpty() &&
           TableTopPitchAngleTolerance.isEmpty() &&
           TableTopRollAngleTolerance.isEmpty() &&
           TableTopVerticalPositionTolerance.isEmpty() &&
           TableTopLongitudinalPositionTolerance.isEmpty() &&
           TableTopLateralPositionTolerance.isEmpty();
}


OFBool DRTToleranceTableSequence::Item::isValid() const
{
    return !EmptyDefaultItem;
}


OFCondition DRTToleranceTableSequence::Item::read(DcmItem &item)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultItem)
    {
        /* re-initialize object */
        clear();
        getAndCheckElementFromDataset(item, ToleranceTableNumber, "1", "1", "ToleranceTableSequence");
        getAndCheckElementFromDataset(item, ToleranceTableLabel, "1", "3", "ToleranceTableSequence");
        getAndCheckElementFromDataset(item, GantryAngleTolerance, "1", "3", "ToleranceTableSequence");
        getAndCheckElementFromDataset(item, GantryPitchAngleTolerance, "1", "3", "ToleranceTableSequence");
        getAndCheckElementFromDataset(item, BeamLimitingDeviceAngleTolerance, "1", "3", "ToleranceTableSequence");
        BeamLimitingDeviceToleranceSequence.read(item, "1-n", "3", "ToleranceTableSequence");
        getAndCheckElementFromDataset(item, PatientSupportAngleTolerance, "1", "3", "ToleranceTableSequence");
        getAndCheckElementFromDataset(item, TableTopEccentricAngleTolerance, "1", "3", "ToleranceTableSequence");
        getAndCheckElementFromDataset(item, TableTopPitchAngleTolerance, "1", "3", "ToleranceTableSequence");
        getAndCheckElementFromDataset(item, TableTopRollAngleTolerance, "1", "3", "ToleranceTableSequence");
        getAndCheckElementFromDataset(item, TableTopVerticalPositionTolerance, "1", "3", "ToleranceTableSequence");
        getAndCheckElementFromDataset(item, TableTopLongitudinalPositionTolerance, "1", "3", "ToleranceTableSequence");
        getAndCheckElementFromDataset(item, TableTopLateralPositionTolerance, "1", "3", "ToleranceTableSequence");
        result = EC_Normal;
    }
    return result;
}


OFCondition DRTToleranceTableSequence::Item::write(DcmItem &item)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultItem)
    {
        result = EC_Normal;
        addElementToDataset(result, item, new DcmIntegerString(ToleranceTableNumber), "1", "1", "ToleranceTableSequence");
        addElementToDataset(result, item, new DcmShortString(ToleranceTableLabel), "1", "3", "ToleranceTableSequence");
        addElementToDataset(result, item, new DcmDecimalString(GantryAngleTolerance), "1", "3", "ToleranceTableSequence");
        addElementToDataset(result, item, new DcmFloatingPointSingle(GantryPitchAngleTolerance), "1", "3", "ToleranceTableSequence");
        addElementToDataset(result, item, new DcmDecimalString(BeamLimitingDeviceAngleTolerance), "1", "3", "ToleranceTableSequence");
        if (result.good()) result = BeamLimitingDeviceToleranceSequence.write(item, "1-n", "3", "ToleranceTableSequence");
        addElementToDataset(result, item, new DcmDecimalString(PatientSupportAngleTolerance), "1", "3", "ToleranceTableSequence");
        addElementToDataset(result, item, new DcmDecimalString(TableTopEccentricAngleTolerance), "1", "3", "ToleranceTableSequence");
        addElementToDataset(result, item, new DcmFloatingPointSingle(TableTopPitchAngleTolerance), "1", "3", "ToleranceTableSequence");
        addElementToDataset(result, item, new DcmFloatingPointSingle(TableTopRollAngleTolerance), "1", "3", "ToleranceTableSequence");
        addElementToDataset(result, item, new DcmDecimalString(TableTopVerticalPositionTolerance), "1", "3", "ToleranceTableSequence");
        addElementToDataset(result, item, new DcmDecimalString(TableTopLongitudinalPositionTolerance), "1", "3", "ToleranceTableSequence");
        addElementToDataset(result, item, new DcmDecimalString(TableTopLateralPositionTolerance), "1", "3", "ToleranceTableSequence");
    }
    return result;
}


OFCondition DRTToleranceTableSequence::Item::getBeamLimitingDeviceAngleTolerance(OFString &value, const signed long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return getStringValueFromElement(BeamLimitingDeviceAngleTolerance, value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getBeamLimitingDeviceAngleTolerance(Float64 &value, const unsigned long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return OFconst_cast(DcmDecimalString &, BeamLimitingDeviceAngleTolerance).getFloat64(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getGantryAngleTolerance(OFString &value, const signed long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return getStringValueFromElement(GantryAngleTolerance, value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getGantryAngleTolerance(Float64 &value, const unsigned long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return OFconst_cast(DcmDecimalString &, GantryAngleTolerance).getFloat64(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getGantryPitchAngleTolerance(Float32 &value, const unsigned long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return OFconst_cast(DcmFloatingPointSingle &, GantryPitchAngleTolerance).getFloat32(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getPatientSupportAngleTolerance(OFString &value, const signed long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return getStringValueFromElement(PatientSupportAngleTolerance, value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getPatientSupportAngleTolerance(Float64 &value, const unsigned long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return OFconst_cast(DcmDecimalString &, PatientSupportAngleTolerance).getFloat64(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getTableTopEccentricAngleTolerance(OFString &value, const signed long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return getStringValueFromElement(TableTopEccentricAngleTolerance, value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getTableTopEccentricAngleTolerance(Float64 &value, const unsigned long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return OFconst_cast(DcmDecimalString &, TableTopEccentricAngleTolerance).getFloat64(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getTableTopLateralPositionTolerance(OFString &value, const signed long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return getStringValueFromElement(TableTopLateralPositionTolerance, value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getTableTopLateralPositionTolerance(Float64 &value, const unsigned long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return OFconst_cast(DcmDecimalString &, TableTopLateralPositionTolerance).getFloat64(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getTableTopLongitudinalPositionTolerance(OFString &value, const signed long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return getStringValueFromElement(TableTopLongitudinalPositionTolerance, value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getTableTopLongitudinalPositionTolerance(Float64 &value, const unsigned long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return OFconst_cast(DcmDecimalString &, TableTopLongitudinalPositionTolerance).getFloat64(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getTableTopPitchAngleTolerance(Float32 &value, const unsigned long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return OFconst_cast(DcmFloatingPointSingle &, TableTopPitchAngleTolerance).getFloat32(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getTableTopRollAngleTolerance(Float32 &value, const unsigned long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return OFconst_cast(DcmFloatingPointSingle &, TableTopRollAngleTolerance).getFloat32(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getTableTopVerticalPositionTolerance(OFString &value, const signed long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return getStringValueFromElement(TableTopVerticalPositionTolerance, value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getTableTopVerticalPositionTolerance(Float64 &value, const unsigned long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return OFconst_cast(DcmDecimalString &, TableTopVerticalPositionTolerance).getFloat64(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getToleranceTableLabel(OFString &value, const signed long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return getStringValueFromElement(ToleranceTableLabel, value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getToleranceTableNumber(OFString &value, const signed long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return getStringValueFromElement(ToleranceTableNumber, value, pos);
}


OFCondition DRTToleranceTableSequence::Item::getToleranceTableNumber(Sint32 &value, const unsigned long pos) const
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return OFconst_cast(DcmIntegerString &, ToleranceTableNumber).getSint32(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::setBeamLimitingDeviceAngleTolerance(const OFString &value, const OFBool check)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultItem)
    {
        result = (check) ? DcmDecimalString::checkStringValue(value, "1") : EC_Normal;
        if (result.good())
            result = BeamLimitingDeviceAngleTolerance.putOFStringArray(value);
    }
    return result;
}


OFCondition DRTToleranceTableSequence::Item::setGantryAngleTolerance(const OFString &value, const OFBool check)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultItem)
    {
        result = (check) ? DcmDecimalString::checkStringValue(value, "1") : EC_Normal;
        if (result.good())
            result = GantryAngleTolerance.putOFStringArray(value);
    }
    return result;
}


OFCondition DRTToleranceTableSequence::Item::setGantryPitchAngleTolerance(const Float32 value, const unsigned long pos)
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return GantryPitchAngleTolerance.putFloat32(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::setPatientSupportAngleTolerance(const OFString &value, const OFBool check)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultItem)
    {
        result = (check) ? DcmDecimalString::checkStringValue(value, "1") : EC_Normal;
        if (result.good())
            result = PatientSupportAngleTolerance.putOFStringArray(value);
    }
    return result;
}


OFCondition DRTToleranceTableSequence::Item::setTableTopEccentricAngleTolerance(const OFString &value, const OFBool check)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultItem)
    {
        result = (check) ? DcmDecimalString::checkStringValue(value, "1") : EC_Normal;
        if (result.good())
            result = TableTopEccentricAngleTolerance.putOFStringArray(value);
    }
    return result;
}


OFCondition DRTToleranceTableSequence::Item::setTableTopLateralPositionTolerance(const OFString &value, const OFBool check)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultItem)
    {
        result = (check) ? DcmDecimalString::checkStringValue(value, "1") : EC_Normal;
        if (result.good())
            result = TableTopLateralPositionTolerance.putOFStringArray(value);
    }
    return result;
}


OFCondition DRTToleranceTableSequence::Item::setTableTopLongitudinalPositionTolerance(const OFString &value, const OFBool check)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultItem)
    {
        result = (check) ? DcmDecimalString::checkStringValue(value, "1") : EC_Normal;
        if (result.good())
            result = TableTopLongitudinalPositionTolerance.putOFStringArray(value);
    }
    return result;
}


OFCondition DRTToleranceTableSequence::Item::setTableTopPitchAngleTolerance(const Float32 value, const unsigned long pos)
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return TableTopPitchAngleTolerance.putFloat32(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::setTableTopRollAngleTolerance(const Float32 value, const unsigned long pos)
{
    if (EmptyDefaultItem)
        return EC_IllegalCall;
    else
        return TableTopRollAngleTolerance.putFloat32(value, pos);
}


OFCondition DRTToleranceTableSequence::Item::setTableTopVerticalPositionTolerance(const OFString &value, const OFBool check)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultItem)
    {
        result = (check) ? DcmDecimalString::checkStringValue(value, "1") : EC_Normal;
        if (result.good())
            result = TableTopVerticalPositionTolerance.putOFStringArray(value);
    }
    return result;
}


OFCondition DRTToleranceTableSequence::Item::setToleranceTableLabel(const OFString &value, const OFBool check)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultItem)
    {
        result = (check) ? DcmShortString::checkStringValue(value, "1") : EC_Normal;
        if (result.good())
            result = ToleranceTableLabel.putOFStringArray(value);
    }
    return result;
}


OFCondition DRTToleranceTableSequence::Item::setToleranceTableNumber(const OFString &value, const OFBool check)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultItem)
    {
        result = (check) ? DcmIntegerString::checkStringValue(value, "1") : EC_Normal;
        if (result.good())
            result = ToleranceTableNumber.putOFStringArray(value);
    }
    return result;
}


// --- sequence class ---

DRTToleranceTableSequence::DRTToleranceTableSequence(const OFBool emptyDefaultSequence)
  : EmptyDefaultSequence(emptyDefaultSequence),
    SequenceOfItems(),
    CurrentItem(),
    EmptyItem(OFTrue /*emptyDefaultItem*/)
{
    CurrentItem = SequenceOfItems.end();
}


DRTToleranceTableSequence::DRTToleranceTableSequence(const DRTToleranceTableSequence &copy)
  : EmptyDefaultSequence(copy.EmptyDefaultSequence),
    SequenceOfItems(),
    CurrentItem(),
    EmptyItem(OFTrue /*emptyDefaultItem*/)
{
    /* create a copy of the internal sequence of items */
    Item *item = NULL;
    OFListConstIterator(Item *) current = copy.SequenceOfItems.begin();
    const OFListConstIterator(Item *) last = copy.SequenceOfItems.end();
    while (current != last)
    {
        item = new Item(**current);
        if (item != NULL)
        {
            SequenceOfItems.push_back(item);
        } else {
            /* memory exhausted, there is nothing we can do about it */
            break;
        }
        ++current;
    }
    CurrentItem = SequenceOfItems.begin();
}


DRTToleranceTableSequence &DRTToleranceTableSequence::operator=(const DRTToleranceTableSequence &copy)
{
    if (this != &copy)
    {
        clear();
        EmptyDefaultSequence = copy.EmptyDefaultSequence;
        /* create a copy of the internal sequence of items */
        Item *item = NULL;
        OFListConstIterator(Item *) current = copy.SequenceOfItems.begin();
        const OFListConstIterator(Item *) last = copy.SequenceOfItems.end();
        while (current != last)
        {
            item = new Item(**current);
            if (item != NULL)
            {
                SequenceOfItems.push_back(item);
            } else {
                /* memory exhausted, there is nothing we can do about it */
                break;
            }
            ++current;
        }
        CurrentItem = SequenceOfItems.begin();
    }
    return *this;
}


DRTToleranceTableSequence::~DRTToleranceTableSequence()
{
    clear();
}


void DRTToleranceTableSequence::clear()
{
    if (!EmptyDefaultSequence)
    {
        CurrentItem = SequenceOfItems.begin();
        const OFListConstIterator(Item *) last = SequenceOfItems.end();
        /* delete all items and free memory */
        while (CurrentItem != last)
        {
            delete (*CurrentItem);
            CurrentItem = SequenceOfItems.erase(CurrentItem);
        }
        /* make sure that the list is empty */
        SequenceOfItems.clear();
        CurrentItem = SequenceOfItems.end();
    }
}


OFBool DRTToleranceTableSequence::isEmpty()
{
    return SequenceOfItems.empty();
}


OFBool DRTToleranceTableSequence::isValid() const
{
    return !EmptyDefaultSequence;
}


size_t DRTToleranceTableSequence::getNumberOfItems() const
{
    return SequenceOfItems.size();
}


OFCondition DRTToleranceTableSequence::gotoFirstItem()
{
    OFCondition result = EC_IllegalCall;
    if (!SequenceOfItems.empty())
    {
        CurrentItem = SequenceOfItems.begin();
        result = EC_Normal;
    }
    return result;
}


OFCondition DRTToleranceTableSequence::gotoNextItem()
{
    OFCondition result = EC_IllegalCall;
    if (++CurrentItem != SequenceOfItems.end())
    {
        if (*CurrentItem != NULL)
            result = EC_Normal;
        else
            result = EC_CorruptedData;
    }
    return result;
}


OFCondition DRTToleranceTableSequence::gotoItem(const size_t num, OFListIterator(Item *) &iterator)
{
    OFCondition result = EC_IllegalCall;
    if (!SequenceOfItems.empty())
    {
        size_t idx = num + 1;
        iterator = SequenceOfItems.begin();
        const OFListConstIterator(Item *) last = SequenceOfItems.end();
        while ((--idx > 0) && (iterator != last))
            ++iterator;
        /* specified list item found? */
        if ((idx == 0) && (iterator != last))
            result = EC_Normal;
        else
            result = EC_IllegalParameter;
    }
    return result;
}


OFCondition DRTToleranceTableSequence::gotoItem(const size_t num, OFListConstIterator(Item *) &iterator) const
{
    OFCondition result = EC_IllegalCall;
    if (!SequenceOfItems.empty())
    {
        size_t idx = num + 1;
        iterator = SequenceOfItems.begin();
        const OFListConstIterator(Item *) last = SequenceOfItems.end();
        while ((--idx > 0) && (iterator != last))
            ++iterator;
        /* specified list item found? */
        if ((idx == 0) && (iterator != last))
            result = EC_Normal;
        else
            result = EC_IllegalParameter;
    }
    return result;
}


OFCondition DRTToleranceTableSequence::gotoItem(const size_t num)
{
    return gotoItem(num, CurrentItem);
}


OFCondition DRTToleranceTableSequence::getCurrentItem(Item *&item) const
{
    OFCondition result = EC_IllegalCall;
    if (CurrentItem != SequenceOfItems.end())
    {
        item = *CurrentItem;
        result = EC_Normal;
    }
    return result;
}


DRTToleranceTableSequence::Item &DRTToleranceTableSequence::getCurrentItem()
{
    if (CurrentItem != SequenceOfItems.end())
        return **CurrentItem;
    else
        return EmptyItem;
}


const DRTToleranceTableSequence::Item &DRTToleranceTableSequence::getCurrentItem() const
{
    if (CurrentItem != SequenceOfItems.end())
        return **CurrentItem;
    else
        return EmptyItem;
}


OFCondition DRTToleranceTableSequence::getItem(const size_t num, Item *&item)
{
    OFListIterator(Item *) iterator;
    OFCondition result = gotoItem(num, iterator);
    if (result.good())
        item = *iterator;
    return result;
}


DRTToleranceTableSequence::Item &DRTToleranceTableSequence::getItem(const size_t num)
{
    OFListIterator(Item *) iterator;
    if (gotoItem(num, iterator).good())
        return **iterator;
    else
        return EmptyItem;
}


const DRTToleranceTableSequence::Item &DRTToleranceTableSequence::getItem(const size_t num) const
{
    OFListConstIterator(Item *) iterator;
    if (gotoItem(num, iterator).good())
        return **iterator;
    else
        return EmptyItem;
}


DRTToleranceTableSequence::Item &DRTToleranceTableSequence::operator[](const size_t num)
{
    return getItem(num);
}


const DRTToleranceTableSequence::Item &DRTToleranceTableSequence::operator[](const size_t num) const
{
    return getItem(num);
}


OFCondition DRTToleranceTableSequence::addItem(Item *&item)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultSequence)
    {
        item = new Item();
        if (item != NULL)
        {
            SequenceOfItems.push_back(item);
            result = EC_Normal;
        } else
            result = EC_MemoryExhausted;
    }
    return result;
}


OFCondition DRTToleranceTableSequence::insertItem(const size_t pos, Item *&item)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultSequence)
    {
        OFListIterator(Item *) iterator;
        result = gotoItem(pos, iterator);
        if (result.good())
        {
            item = new Item();
            if (item != NULL)
            {
                SequenceOfItems.insert(iterator, 1, item);
                result = EC_Normal;
            } else
                result = EC_MemoryExhausted;
        } else
            result = addItem(item);
    }
    return result;
}


OFCondition DRTToleranceTableSequence::removeItem(const size_t pos)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultSequence)
    {
        OFListIterator(Item *) iterator;
        if (gotoItem(pos, iterator).good())
        {
            delete *iterator;
            iterator = SequenceOfItems.erase(iterator);
            result = EC_Normal;
        } else
            result = EC_IllegalParameter;
    }
    return result;
}


OFCondition DRTToleranceTableSequence::read(DcmItem &dataset,
                                            const OFString &card,
                                            const OFString &type,
                                            const char *moduleName)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultSequence)
    {
        /* re-initialize object */
        clear();
        /* retrieve sequence element from dataset */
        DcmSequenceOfItems *sequence;
        result = dataset.findAndGetSequence(DCM_ToleranceTableSequence, sequence);
        if (sequence != NULL)
        {
            if (checkElementValue(*sequence, card, type, result, moduleName))
            {
                DcmStack stack;
                OFBool first = OFTrue;
                /* iterate over all sequence items */
                while (result.good() && sequence->nextObject(stack, first /*intoSub*/).good())
                {
                    DcmItem *ditem = OFstatic_cast(DcmItem *, stack.top());
                    if (ditem != NULL)
                    {
                        Item *item = new Item();
                        if (item != NULL)
                        {
                            result = item->read(*ditem);
                            if (result.good())
                            {
                                /* append new item to the end of the list */
                                SequenceOfItems.push_back(item);
                                first = OFFalse;
                            }
                        } else
                            result = EC_MemoryExhausted;
                    } else
                        result = EC_CorruptedData;
                }
            }
        } else {
            DcmSequenceOfItems element(DCM_ToleranceTableSequence);
            checkElementValue(element, card, type, result, moduleName);
        }
    }
    return result;
}


OFCondition DRTToleranceTableSequence::write(DcmItem &dataset,
                                             const OFString &card,
                                             const OFString &type,
                                             const char *moduleName)
{
    OFCondition result = EC_IllegalCall;
    if (!EmptyDefaultSequence)
    {
        result = EC_MemoryExhausted;
        DcmSequenceOfItems *sequence = new DcmSequenceOfItems(DCM_ToleranceTableSequence);
        if (sequence != NULL)
        {
            result = EC_Normal;
            /* an empty optional sequence is not written */
            if ((type == "2") || !SequenceOfItems.empty())
            {
                OFListIterator(Item *) iterator = SequenceOfItems.begin();
                const OFListConstIterator(Item *) last = SequenceOfItems.end();
                /* iterate over all sequence items */
                while (result.good() && (iterator != last))
                {
                    DcmItem *item = new DcmItem();
                    if (item != NULL)
                    {
                        /* append new item to the end of the sequence */
                        result = sequence->append(item);
                        if (result.good())
                        {
                            result = (*iterator)->write(*item);
                            ++iterator;
                        } else
                            delete item;
                    } else
                        result = EC_MemoryExhausted;
                }
                if (result.good())
                {
                    /* insert sequence element into the dataset */
                    result = dataset.insert(sequence, OFTrue /*replaceOld*/);
                }
                if (DCM_dcmrtLogger.isEnabledFor(OFLogger::WARN_LOG_LEVEL))
                    checkElementValue(*sequence, card, type, result, moduleName);
                if (result.good())
                {
                    /* forget reference to sequence object (avoid deletion below) */
                    sequence = NULL;
                }
            }
            else if (type == "1")
            {
                /* empty type 1 sequence not allowed */
                result = RT_EC_InvalidValue;
                if (DCM_dcmrtLogger.isEnabledFor(OFLogger::WARN_LOG_LEVEL))
                    checkElementValue(*sequence, card, type, result, moduleName);
            }
            /* delete sequence (if not inserted into the dataset) */
            delete sequence;
        }
    }
    return result;
}


// end of source file
