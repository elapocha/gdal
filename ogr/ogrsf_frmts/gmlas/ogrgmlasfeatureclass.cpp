/******************************************************************************
 * Project:  OGR
 * Purpose:  OGRGMLASDriver implementation
 * Author:   Even Rouault, <even dot rouault at spatialys dot com>
 *
 * Initial development funded by the European Earth observation programme
 * Copernicus
 *
 ******************************************************************************
 * Copyright (c) 2016, Even Rouault, <even dot rouault at spatialys dot com>
 *
 * SPDX-License-Identifier: MIT
 ****************************************************************************/

#include "ogr_gmlas.h"

/************************************************************************/
/*                             GetTypeFromString()                      */
/************************************************************************/

GMLASFieldType GMLASField::GetTypeFromString(const CPLString &osType)
{
    if (osType == szXS_STRING || osType == szXS_TOKEN ||
        osType == szXS_NMTOKEN || osType == szXS_NCNAME ||
        osType == szXS_QNAME || osType == szXS_IDREF)
    {
        // token has special processing by XML processor: all leading/trailing
        // white space is removed
        return GMLAS_FT_STRING;
    }
    else if (osType == szXS_ID)
        return GMLAS_FT_ID;
    else if (osType == szXS_BOOLEAN)
        return GMLAS_FT_BOOLEAN;
    else if (osType == szXS_SHORT)
        return GMLAS_FT_SHORT;
    else if (osType == szXS_INT)
        return GMLAS_FT_INT32;
    else if (osType == szXS_BYTE || osType == szXS_INTEGER ||
             osType == szXS_NEGATIVE_INTEGER ||
             osType == szXS_NON_NEGATIVE_INTEGER ||
             osType == szXS_NON_POSITIVE_INTEGER ||
             osType == szXS_POSITIVE_INTEGER || osType == szXS_UNSIGNED_BYTE ||
             osType == szXS_UNSIGNED_SHORT ||
             osType == szXS_UNSIGNED_INT)  // FIXME ?
        return GMLAS_FT_INT32;
    else if (osType == szXS_LONG || osType == szXS_UNSIGNED_LONG)
        return GMLAS_FT_INT64;
    else if (osType == szXS_FLOAT)
        return GMLAS_FT_FLOAT;
    else if (osType == szXS_DOUBLE)
        return GMLAS_FT_DOUBLE;
    else if (osType == szXS_DECIMAL)
        return GMLAS_FT_DECIMAL;
    else if (osType == szXS_DATE)
        return GMLAS_FT_DATE;
    else if (osType == szXS_GYEAR)
        return GMLAS_FT_GYEAR;
    else if (osType == szXS_GYEAR_MONTH)
        return GMLAS_FT_GYEAR_MONTH;
    else if (osType == szXS_TIME)
        return GMLAS_FT_TIME;
    else if (osType == szXS_DATETIME)
        return GMLAS_FT_DATETIME;
    else if (osType == szXS_ANY_URI)
        return GMLAS_FT_ANYURI;
    else if (osType == szXS_ANY_TYPE)
        return GMLAS_FT_ANYTYPE;
    else if (osType == szXS_ANY_SIMPLE_TYPE)
        return GMLAS_FT_ANYSIMPLETYPE;
    else if (osType == szXS_DURATION)
        return GMLAS_FT_STRING;
    else if (osType == szXS_BASE64BINARY)
        return GMLAS_FT_BASE64BINARY;
    else if (osType == szXS_HEXBINARY)
        return GMLAS_FT_HEXBINARY;
    else
    {
        CPLError(CE_Warning, CPLE_AppDefined, "Unhandled type: %s",
                 osType.c_str());
        return GMLAS_FT_STRING;
    }
}

/************************************************************************/
/*                               SetType()                              */
/************************************************************************/

void GMLASField::SetType(GMLASFieldType eType, const char *pszTypeName)
{
    m_eType = eType;
    m_osTypeName = pszTypeName;
}

/************************************************************************/
/*                                 SetName()                            */
/************************************************************************/

void GMLASFeatureClass::SetName(const CPLString &osName)
{
    m_osName = osName;
}

/************************************************************************/
/*                                SetXPath()                            */
/************************************************************************/

void GMLASFeatureClass::SetXPath(const CPLString &osXPath)
{
    m_osXPath = osXPath;
}

/************************************************************************/
/*                                AddField()                            */
/************************************************************************/

void GMLASFeatureClass::AddField(const GMLASField &oField)
{
    m_aoFields.push_back(oField);
}

/************************************************************************/
/*                            PrependFields()                           */
/************************************************************************/

void GMLASFeatureClass::PrependFields(const std::vector<GMLASField> &aoFields)
{
    m_aoFields.insert(m_aoFields.begin(), aoFields.begin(), aoFields.end());
}

/************************************************************************/
/*                             AppendFields()                           */
/************************************************************************/

void GMLASFeatureClass::AppendFields(const std::vector<GMLASField> &aoFields)
{
    m_aoFields.insert(m_aoFields.end(), aoFields.begin(), aoFields.end());
}

/************************************************************************/
/*                             AddNestedClass()                         */
/************************************************************************/

void GMLASFeatureClass::AddNestedClass(const GMLASFeatureClass &oNestedClass)
{
    m_aoNestedClasses.push_back(oNestedClass);
}
