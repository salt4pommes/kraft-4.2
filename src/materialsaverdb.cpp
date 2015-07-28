/***************************************************************************
             materialsaverdb  -
                             -------------------
    begin                : 2006-12-07
    copyright            : (C) 2005 by Klaas Freitag
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


// include files for Qt
#include <QDateTime>
#include <QSqlTableModel>
#include <QSqlRecord>

// include files for KDE
#include <klocale.h>
#include <kdebug.h>
#include <kglobal.h>

#include "kraftdb.h"
#include "kraftglobals.h"
#include "dbids.h"
#include "materialsaverdb.h"
#include "stockmaterial.h"

MaterialSaverDB::MaterialSaverDB( )
    : MaterialSaverBase()
{

}

MaterialSaverBase *MaterialSaverDB::self()
{
  K_GLOBAL_STATIC(MaterialSaverDB, mSelf);
  return mSelf;
}

bool MaterialSaverDB::saveTemplate( StockMaterial *mat )
{
    bool res = true;

    // Transaktion ?

    QSqlTableModel model;
    model.setTable("stockMaterial");
    QString templID = QString::number( mat->getID() );
    model.setFilter( "matID=" + templID );
    model.select();

    QSqlRecord buffer = model.record();

    if( model.rowCount() > 0)
    {
        kDebug() << "Updating material " << mat->getID() << endl;

        // mach update
        buffer = model.record(0);
        fillMaterialBuffer( buffer, mat, false );
        model.setRecord(0, buffer);
        model.submitAll();
    }
    else
    {
        // insert
        kDebug() << "Creating new material database entry" << endl;

        fillMaterialBuffer( buffer, mat, true );
        model.insertRecord(-1, buffer);
        model.submitAll();

        /* Jetzt die neue Template-ID selecten */
        dbID id = KraftDB::self()->getLastInsertID();
        kDebug() << "New Database ID=" << id.toInt() << endl;

        if( id.isOk() ) {
            mat->setID( id.toInt() );
            templID = id.toString();
        } else {
            kDebug() << "ERROR: Kann AUTOINC nicht ermitteln" << endl;
            res = false;
        }
    }
    return res;
}

void MaterialSaverDB::fillMaterialBuffer( QSqlRecord &rec, StockMaterial *mat, bool isNew )
{
  if( ! ( mat ) ) return;
  rec.setValue( "chapterID", mat->chapter() );
  rec.setValue( "material", mat->name() );
  rec.setValue( "unitID", mat->getUnit().id() );
  rec.setValue( "perPack", mat->getAmountPerPack() );
  rec.setValue( "priceIn", mat->purchPrice().toDouble() );
  rec.setValue( "priceOut", mat->salesPrice().toDouble() );

  QString dtString = KraftDB::self()->currentTimeStamp();

  if( isNew ) {
    rec.setValue( "enterDate", dtString);
  }
  rec.setValue("modifyDate", dtString );
}

void MaterialSaverDB::saveTemplateChapter( StockMaterial* tmpl )
{
    if( ! tmpl ) {
        kDebug() << "Parameter error, zero material!";
        return;
    }
    dbID id = tmpl->getID();
    dbID chapId = tmpl->chapterId();

    QSqlTableModel model;
    model.setTable("stockMaterial");
    QString templID = id.toString();
    model.setFilter( "matID=" + templID );
    model.select();

    QSqlRecord buffer = model.record();

    if( model.rowCount() > 0)
    {
        kDebug() << "Updating material chapter " << templID << endl;
        buffer = model.record(0);
        buffer.setValue( "chapterID", chapId.toString() );
        model.setRecord(0, buffer);
        model.submitAll();
    } else {
        kDebug() << "Could not update material chapter, not found with id " << templID;
    }
}
