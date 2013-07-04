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

#include "compositescope.h"

void CompositeScope::addScope(Scope &scope)
{
    _scopes.push_back(&scope);
}

Variable CompositeScope::doGet(const Variant &key) const
{
    for(Scope* scope : _scopes)
    {
        Variable variable = scope->get(key);
        if(variable.isDefined())
            return variable;
    }
    return Variable();
}

Scope *CompositeScope::doGetScope(const Variant &key) const
{
    for(Scope* scope : _scopes)
    {
        Scope* s = scope->getScope(key);
        if(s != nullptr)
            return s;
    }
    return nullptr;
}

Variable CompositeScope::doDeclare(const Variant &key)
{
    for(Scope* scope : _scopes)
    {
        Variable variable = scope->declare(key);
        if(variable.isDefined())
            return variable;
    }
    return Variable();
}
