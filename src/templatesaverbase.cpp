/***************************************************************************
             templatesaverbase  -
                             -------------------
    begin                : 2005-20-01
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

// include files for KDE
#include <klocale.h>
#include <kdebug.h>

#include "templatesaverbase.h"


TemplateSaverBase::TemplateSaverBase( )
{

}

bool TemplateSaverBase::saveTemplate(FloskelTemplate*)
{
    return false;
}

void TemplateSaverBase::saveTemplateChapter( FloskelTemplate* )
{
  // do nothing
}

TemplateSaverBase::~TemplateSaverBase( )
{

}


CalculationsSaverBase::CalculationsSaverBase()
{

}

CalculationsSaverBase::CalculationsSaverBase( TargetType )
{

}

/* END */


