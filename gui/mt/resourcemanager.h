//This file is part of the HexaMonkey project, a multimedia analyser
//Copyright (C) 2013  Sevan Drapeau-Martin, Nicolas Fleury

//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#ifndef RESURCEMANAGER_H
#define RESURCEMANAGER_H

#include <QMap>
#include <QMutex>
#include <QObject>

#include "core/object.h"

class Resource;
class TreeModel;

class ResourceManager: public QObject {
    Q_OBJECT
public:
    ResourceManager(TreeModel& model);

    void lock(Object& object);

    void unlock(Object& object);

    void insert(File& file);

    Resource& resource(Object& object);

private:
    QMap<File*,Resource*> _map;
    TreeModel& _model;

};

#endif // RESURCEMANAGER_H
