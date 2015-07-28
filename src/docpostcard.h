/***************************************************************************
                 DocPostCard - a postcard version of the document
                             -------------------
    begin                : Aug 2006
    copyright            : (C) 2006 by Klaas Freitag
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

#ifndef DOCPOSTCARD_H
#define DOCPOSTCARD_H

#include <qstring.h>
#include "htmlview.h"
#include "kraftdoc.h"

class KUrl;

class DocPostCard : public HtmlView
{
  Q_OBJECT
public:
  enum DisplayMode { Full, Mini };

  DocPostCard( QWidget *parent = 0 );

signals:
  void selectPage( int );

public slots:
  void setHeaderData( const QString&, const QString&, const QString&, const QString&, const QString& );
  void setPositions( DocPositionList, DocPositionBase::TaxType, double, double );
  void setFooterData( const QString&,  const QString& );
  void renderDoc( int id = -1 );
  void slotSetMode( DisplayMode, int id = -1 );
  void slotShowPrices( bool showIt );

protected:
  bool urlSelected (const QString &url, int button, int state, const QString &_target,
                    const KParts::OpenUrlArguments &args=KParts::OpenUrlArguments(),
                    const KParts::BrowserArguments &browserArgs=KParts::BrowserArguments());

  // void urlSelected( const QString &, int , int ,
  //                  const QString &, KParts::openUrlArguments& );
  // openUrlRequestDelayed(const KUrl &, const KParts::OpenUrlArguments&, const KParts::BrowserArguments&)
  
  QString renderDocMini( int ) const;
  QString renderDocFull( int );
  QString header( bool, const QString&, const QString&, const QString&,
                  const QString& = QString() ) const;

private:
  QString linkBit( const QString&, const QString& ) const;
  QString htmlify( const QString& ) const;

  DocGuardedPtr mDoc;
  QString mType;
  QString mId;
  QString mPreText;
  QString mPostText;
  QString mDate;
  QString mAddress;
  QString mPositions;
  QString mGoodbye;
  QString mTotal;
  int mPositionCount;
  DisplayMode mMode;
  bool mShowPrices;
};

#endif
