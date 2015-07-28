/***************************************************************************
                          einheit.cpp  -
                             -------------------
    begin                : Don Jan 1 2004
    copyright            : (C) 2004 by Klaas Freitag
    email                : freitag@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "einheit.h"

Einheit::Einheit()
 :m_dbId(-1)
{
}

Einheit::Einheit( int id, const QString& einh, const QString& einhLong,
                  const QString& einhPlu, const QString& einhPluLong  )
    : m_dbId(id)
{
   m_einheitSingular = einh;
   m_einheitPlural = einhPlu;
   m_einheitSingularLong = einhLong;
   m_einheitPluralLong = einhPluLong;
}

Einheit::Einheit( int id )
 : m_dbId(id)
{
    // Ask the Unitmanager here.

}

Einheit::Einheit( const QString& einhText )
{
    m_einheitSingular = einhText;
    m_einheitPlural = einhText;
    m_einheitSingularLong = einhText;
    m_einheitPluralLong = einhText;
}

Einheit::~Einheit(){
}

QString Einheit::einheit( int anz ) {
    if( anz == 1 )
        return einheitSingular();
    else
        return einheitPlural();
}

QString Einheit::einheit( double anz ) {
    if( anz == 1.0 )
        return einheitSingular();
    else
        return einheitPlural();
}

Einheit& Einheit::operator=( const Einheit& e )
{
  if ( this == &e ) return *this;

  m_dbId = e.m_dbId;
  m_einheitSingular = e.m_einheitSingular;
  m_einheitPlural = e.m_einheitPlural;
  m_einheitSingularLong = e.m_einheitSingularLong;
  m_einheitPluralLong = e.m_einheitPluralLong;

  return *this;
}
