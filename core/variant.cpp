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

#include <algorithm> //swap
#include <sstream>

#include "core/variant.h"
#include "core/objecttype.h"
#include "core/error/errormanager.h"

const std::vector<std::string>& typeNames = {"unknown", "integer", "unsigned integer" , "float", "string","object type"};

const std::string emptyString;
const ObjectType nullType;

Variant::Variant() : _type(unknown)
{
}

Variant::Variant(const Variant& other) : _type(other._type)
{
    switch(_type)
    {
        case integer:
            _data.l = other._data.l;
            break;

        case unsignedInteger:
            _data.ul = other._data.ul;
            break;

        case floating:
            _data.f = other._data.f;
            break;


        case string:
            _data.s = new std::string(*other._data.s);
            break;

        case objectType:
            _data.t = new ObjectType(*other._data.t);
            break;

        default:
        break;
    }
}

Variant::Variant(bool l)
{
    _type = integer;
    _data.l = l;
}

Variant::Variant(char l)
{
    _type = integer;
    _data.l = l;
}

Variant::Variant(int l)
{
    _type = integer;
    _data.l = l;
}

Variant::Variant(long l)
{
    _type = integer;
    _data.l = l;
}

Variant::Variant(long long l)
{
    _type = integer;
    _data.l = l;
}

Variant::Variant(unsigned char ul)
{
    _type = unsignedInteger;
    _data.ul = ul;
}

Variant::Variant(unsigned int ul)
{
    _type = unsignedInteger;
    _data.ul = ul;
}

Variant::Variant(unsigned long ul)
{
    _type = unsignedInteger;
    _data.ul = ul;
}

Variant::Variant(unsigned long long ul)
{
    _type = unsignedInteger;
    _data.ul = ul;
}

Variant::Variant(float f)
{
    _type = floating;
    _data.f = f;
}

Variant::Variant(double f)
{
    _type = floating;
    _data.f = f;
}

Variant::Variant(const std::string& s)
{
    _type = string;
    _data.s = new std::string(s);
}

Variant::Variant(const char* s)
{
    _type = string;
    _data.s = new std::string(s);
}

Variant::Variant(const ObjectType& t)
{
    _type = objectType;
    _data.t = new ObjectType(t);
}

Variant::~Variant()
{
    clear();
}

void swap(Variant &a, Variant &b)
{
    using std::swap;

    swap(a._type, b._type);
    swap(a._data, b._data);
}

Variant& Variant::operator=(Variant other)
{
    swap(*this, other);
    return *this;
}

void Variant::setValue(Variant other)
{
    swap(*this, other);
}

void Variant::setValue(bool l)
{
    clear();
    _type = integer;
    _data.l = l;
}

void Variant::setValue(char l)
{
    clear();
    _type = integer;
    _data.l = l;
}

void Variant::setValue(int l)
{
    clear();
    _type = integer;
    _data.l = l;
}

void Variant::setValue(long l)
{
    clear();
    _type = integer;
    _data.l = l;
}

void Variant::setValue(long long l)
{
    clear();
    _type = integer;
    _data.l = l;
}

void Variant::setValue(unsigned char ul)
{
    clear();
    _type = unsignedInteger;
    _data.ul = ul;
}

void Variant::setValue(unsigned int ul)
{
    clear();
    _type = unsignedInteger;
    _data.ul = ul;
}

void Variant::setValue(unsigned long ul)
{
    clear();
    _type = unsignedInteger;
    _data.ul = ul;
}

void Variant::setValue(unsigned long long ul)
{
    clear();
    _type = unsignedInteger;
    _data.ul = ul;
}

void Variant::setValue(float f)
{
    clear();
    _type = floating;
    _data.f = f;
}

void Variant::setValue(double f)
{
    clear();
    _type = floating;
    _data.f = f;
}
void Variant::setValue(const std::string& s)
{
    clear();
    _type = string;
    _data.s = new std::string(s);
}

void Variant::setValue(const char* s)
{
    clear();
    _type = string;
    _data.s = new std::string(s);
}

void Variant::setValue(const ObjectType& t)
{
    clear();
    _type = objectType;
    _data.t = new ObjectType(t);
}

void Variant::clear()
{
    switch(_type)
    {
        case string:
            delete _data.s;
            break;
        case objectType:
            delete _data.t;
            break;
        default:
            break;
    }
    _type = unknown;
}


bool Variant::canConvertTo(Variant::Type otherType) const
{
    if(_type == otherType)
        return true;

    switch(_type)
    {
        case integer:
            switch(otherType)
            {
                case unsignedInteger:
                return true;

                case floating:
                return true;

                default:
                return false;
            }

        case unsignedInteger:
            switch(otherType)
            {
                case integer:
                return true;

                case floating:
                return true;

                default:
                return false;
            }

        case floating:
            switch(otherType)
            {
                case integer:
                return true;

                case unsignedInteger:
                return true;

                default:
                return false;
            }
        default:
            return false;
    }
}

Variant& Variant::convertTo(Variant::Type newType)
{
    ErrorManager* em = ErrorManager::getInstance();
    if(_type == newType)
        return *this;

    switch(_type)
    {
        case integer:
            switch(newType)
            {
                case unsignedInteger:
                    _data.ul = (unsigned long long) _data.l;
                    break;

                case floating:
                    _data.f = (double) _data.l;
                    break;

                default:
                    em->errorMessage<<"Error: Invalid type conversion : "<<typeNames[_type]<<" to "<<typeNames[newType];
                    em->notify();
                    clear();
            }
            break;

        case unsignedInteger:
            switch(newType)
            {
                case integer:
                    _data.l = (long long) _data.ul;
                    break;

                case floating:
                    _data.f = (double) _data.ul;
                    break;

                default:
                    em->errorMessage<<"Error: Invalid type conversion : "<<typeNames[_type]<<" to "<<typeNames[newType]<<std::endl;
                    em->notify();
                    clear();
            }
            break;

        case floating:
            switch(newType)
            {
                case integer:
                    _data.l = (long long) _data.f;
                    break;

                case unsignedInteger:
                    _data.ul = (double) _data.f;
                    break;

                default:
                    em->errorMessage<<"Error: Invalid type conversion : "<<typeNames[_type]<<" to "<<typeNames[newType]<<std::endl;
                    em->notify();
                    clear();
            }
            break;

        default:
            em->errorMessage<<"Error: Invalid type conversion : "<<typeNames[_type]<<" to "<<typeNames[newType]<<std::endl;
            em->notify();
            clear();
    }
    _type = newType;
    return *this;
}

long long Variant::toInteger() const
{
    if(_type == integer || _type == unsignedInteger)
    {
        return _data.l;
    }
    else
    {
        if(canConvertTo(integer))
        {
            return Variant(*this).convertTo(integer)._data.l;
        }
        else
        {
            return 0LL;
        }
    }
}

unsigned long long Variant::toUnsignedInteger() const
{
    if(_type == integer || _type == unsignedInteger)
    {
        return _data.ul;
    }
    else
    {
        if(canConvertTo(unsignedInteger))
        {
            return Variant(*this).convertTo(unsignedInteger)._data.ul;
        }
        else
        {
            return 0LL;
        }
    }
}

double Variant::toDouble() const
{
    if(_type == floating)
    {
        return _data.f;
    }
    else
    {
        if(canConvertTo(floating))
        {
            return Variant(*this).convertTo(floating)._data.f;
        }
        else
        {
            return 0.;
        }
    }
}

const std::string& Variant::toString() const
{
    if(_type == string)
    {
        return *_data.s;
    }
    else
    {
        if(canConvertTo(string))
        {
            return *Variant(*this).convertTo(string)._data.s;
        }
        else
        {
            return emptyString;
        }
    }
}

const ObjectType& Variant::toObjectType() const
{
    if(_type == objectType)
    {
        return *_data.t;
    }
    else
    {
        if(canConvertTo(objectType))
        {
            return *Variant(*this).convertTo(objectType)._data.t;
        }
        else
        {
            return nullType;
        }
    }
}

ObjectType& Variant::toObjectType()
{
    return *_data.t;
}

bool Variant::toBool() const
{
    switch(_type)
    {
    case integer:
        return _data.l != 0LL;
    case unsignedInteger:
        return _data.ul != 0LL;
    case floating:
        return _data.f != 0.;
    case string:
        return !_data.s->empty();
    case objectType:
        return !_data.t->isNull();
    default:
        return false;

    }
}

Variant::Type Variant::type() const
{
    return _type;
}

bool Variant::hasNumericalType() const
{
    return _type == integer || _type == unsignedInteger || _type == floating;
}

bool Variant::isNull() const
{
    return _type == unknown;
}

std::ostream& Variant::display(std::ostream& out) const
{
    switch(_type)
    {
        case integer:
            out<<_data.l;
            break;

        case unsignedInteger:
            out<<_data.ul;
            break;

        case floating:
            out<<_data.f;
            break;

        case string:
            out<<*_data.s;
            break;

        case objectType:
            out<<*_data.t;
            break;

        default:
        break;
    }
    return out;
}

bool operator==(const Variant& a, const Variant& b)
{

    if(a._type != b._type)
    {
        if(b._type == Variant::Type::floating)
        {
            if(a.canConvertTo(b._type))
            {
                Variant converted = a;
                converted.convertTo(b._type);
                return b == converted;
            }
            else
            {
                return false;
            }
        }
        else if(b.canConvertTo(a.type()))
        {
            Variant converted = b;
            converted.convertTo(a._type);
            return a == converted;
        }
        else
        {
            return false;
        }
    }


    switch(a._type)
    {
        case Variant::integer:
            return (a._data.l == b._data.l);

        case Variant::unsignedInteger:
            return (a._data.ul == b._data.ul);

        case Variant::floating:
            return (a._data.f == b._data.f);

        case Variant::string:
            return (*a._data.s == *b._data.s);

        case Variant::objectType:
            return (*a._data.t == *b._data.t);

        default:
            return true;
    }
}

bool operator!=(const Variant& a, const Variant& b)
{
    return !(a==b);
}

bool operator< (const Variant& a, const Variant& b)
{
    if(a._type != b._type)
    {
        if(b.canConvertTo(a.type()))
        {
            Variant converted = b;
            converted.convertTo(a._type);
            return a < converted;
        }
        else
        {
            return a._type < b._type;
        }
    }

    switch(a._type)
    {
        case Variant::integer:
            return (a._data.l < b._data.l);

        case Variant::unsignedInteger:
            return (a._data.ul < b._data.ul);

        case Variant::floating:
            return (a._data.f < b._data.f);

        case Variant::string:
            return (*a._data.s < *b._data.s);

        case Variant::objectType:
            return (*a._data.t < *b._data.t);

        default:
            return false;
    }
}

bool operator<=(const Variant& a, const Variant& b)
{
    return a==b || a<b;
}

bool operator> (const Variant& a, const Variant& b)
{
    return !(a<=b);
}

bool operator>=(const Variant& a, const Variant& b)
{
    return !(a<b);
}


std::ostream& operator<<(std::ostream& out, const Variant& variant)
{
    return variant.display(out);
}

Variant &Variant::operator +=(const Variant &other)
{
    if(_type == string || other._type == string)
    {
        std::stringstream S;
        S<<*this<<other;
        setValue(S.str());
    }
    else
    {
        switch(_type)
        {
        case integer:
            if(other.type() == floating)
            {
                convertTo(floating);
                _data.f += other.toDouble();
                break;
            }
            _data.l += other.toInteger();
            break;

        case unsignedInteger:
            if(other.type() == floating)
            {
                convertTo(floating);
                _data.f += other.toDouble();
                break;
            }
            _data.ul += other.toInteger();
            break;

        case floating:
            _data.f += other.toDouble();
            break;

        case string:
            *_data.s += other.toString();
            break;

        default:
            ErrorManager::getInstance()->notify("Invalid operation : +=");
        }
    }
    return *this;
}

Variant &Variant::operator -=(const Variant &other)
{
    switch(_type)
    {
    case integer:
        if(other.type() == floating)
        {
            convertTo(floating);
            _data.f -= other.toDouble();
            break;
        }
        _data.l -= other.toInteger();
        break;

    case unsignedInteger:
        if(other.type() == floating)
        {
            convertTo(floating);
            _data.f -= other.toDouble();
            break;
        }
        _data.ul -= other.toInteger();
        break;

    case floating:
        _data.f -= other.toDouble();
        break;

    default:
        ErrorManager::getInstance()->notify("Invalid operation : -=");
    }
    return *this;
}

Variant &Variant::operator *=(const Variant &other)
{
    switch(_type)
    {
    case integer:
        _data.l *= other.toInteger();
        if(other.type() == floating)
        {
            convertTo(floating);
            _data.f *= other.toDouble();
            break;
        }
        break;

    case unsignedInteger:
        if(other.type() == floating)
        {
            convertTo(floating);
            _data.f *= other.toDouble();
            break;
        }
        _data.ul *= other.toInteger();
        break;

    case floating:
        _data.f *= other.toDouble();
        break;

    default:
        ErrorManager::getInstance()->notify("Invalid operation : *=");
    }
    return *this;
}

Variant &Variant::operator /=(const Variant &other)
{
    switch(_type)
    {
    case integer:
        if(other.type() == floating)
        {
            convertTo(floating);
            _data.f /= other.toDouble();
            break;
        }
        _data.l /= other.toInteger();
        break;

    case unsignedInteger:
        if(other.type() == floating)
        {
            convertTo(floating);
            _data.f /= other.toDouble();
            break;
        }
        _data.ul /= other.toInteger();
        break;

    case floating:
        _data.f /= other.toDouble();
        break;

    default:
        ErrorManager::getInstance()->notify("Invalid operation : /=");
    }
    return *this;
}

Variant &Variant::operator %=(const Variant &other)
{
    switch(_type)
    {
    case integer:
        _data.l %= other.toInteger();
        break;

    case unsignedInteger:
        _data.ul %= other.toInteger();
        break;

    default:
        ErrorManager::getInstance()->notify("Invalid operation : %=");
    }
    return *this;
}

Variant &Variant::operator ++()
{
    switch(_type)
    {
    case integer:
        ++_data.l;
        break;

    case unsignedInteger:
        ++_data.ul;
        break;

    case floating:
        ++_data.f;
        break;

    default:
        ErrorManager::getInstance()->notify("Invalid operation : *=");
    }
    return *this;
}

Variant Variant::operator ++(int)
{
    Variant result(*this);
    operator++();
    return result;
}

Variant &Variant::operator --()
{
    switch(_type)
    {
    case integer:
        --_data.l;
        break;

    case unsignedInteger:
        if(_data.ul == 0)
            convertTo(integer);
        --_data.ul;

        break;

    case floating:
        --_data.f;
        break;

    default:
        ErrorManager::getInstance()->notify("Invalid operation : --");
    }
    return *this;
}

Variant Variant::operator --(int)
{
    Variant result(*this);
    operator--();
    return result;
}

Variant Variant::operator -() const
{
    Variant result = *this;
    switch(_type)
    {
        case unsignedInteger:
            result.convertTo(integer);
        case integer:
            result._data.l = -result._data.l;
            break;

        case floating:
            result._data.f = -result._data.f;
            break;

        default:
            ErrorManager::getInstance()->notify("Invalid operation : -");

    }
    return result;
}

Variant &Variant::operator |=(const Variant &other)
{
    if(hasNumericalType() && other.hasNumericalType())
    {
        _data.ul |= other._data.ul;
    }
    else
    {
        ErrorManager::getInstance()->notify("Invalid operation : |=");
    }
    return *this;
}

Variant &Variant::operator ^=(const Variant &other)
{
    if(hasNumericalType() && other.hasNumericalType())
    {
        _data.ul ^= other._data.ul;
    }
    else
    {
        ErrorManager::getInstance()->notify("Invalid operation : ^=");
    }
    return *this;
}

Variant &Variant::operator &=(const Variant &other)
{
    if(hasNumericalType() && other.hasNumericalType())
    {
        _data.ul &= other._data.ul;
    }
    else
    {
        ErrorManager::getInstance()->notify("Invalid operation : &=");
    }
    return *this;
}

Variant &Variant::operator <<=(const Variant &other)
{
    if(hasNumericalType() && other.hasNumericalType())
    {
        convertTo(unsignedInteger);
        _data.ul <<= other.toInteger();
    }
    else
    {
        ErrorManager::getInstance()->notify("Invalid operation : <<=");
    }
    return *this;
}

Variant &Variant::operator >>=(const Variant &other)
{
    if(hasNumericalType() && other.hasNumericalType())
    {
        convertTo(unsignedInteger);
        _data.ul >>= other.toInteger();
    }
    else
    {
        ErrorManager::getInstance()->notify("Invalid operation : >>=");
    }
    return *this;
}

Variant Variant::operator ~() const
{
    if(!hasNumericalType())
    {
        ErrorManager::getInstance()->notify("Invalid operation : ~");
        return *this;
    }

    Variant result = *this;
    result._data.ul = ~result._data.ul;
    return result;
}

bool Variant::operator !() const
{
    return !toBool();
}

bool operator&&(const Variant& a, const Variant& b)
{
    return a.toBool() && b.toBool();
}

bool operator||(const Variant& a, const Variant& b)
{
    return a.toBool() || b.toBool();
}

Variant operator+ (Variant a, const Variant& b)
{
    a += b;
    return a;
}

Variant operator- (Variant a, const Variant& b)
{
    a -= b;
    return a;
}

Variant operator* (Variant a, const Variant& b)
{
    a *= b;
    return a;
}

Variant operator/ (Variant a, const Variant& b)
{
    a /= b;
    return a;
}

Variant operator% (Variant a, const Variant& b)
{
    a %= b;
    return a;
}

Variant operator| (Variant a, const Variant& b)
{
    a |= b;
    return a;
}

Variant operator^ (Variant a, const Variant& b)
{
    a ^= b;
    return a;
}

Variant operator& (Variant a, const Variant& b)
{
    a &= b;
    return a;
}

Variant operator<<(Variant a, const Variant& b)
{
    a <<= b;
    return a;
}

Variant operator>>(Variant a, const Variant& b)
{
    a >>= b;
    return a;
}
