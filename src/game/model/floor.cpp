#include "floor.h"

Floor::Floor(std::pair<int, int> size, int anchor)
    : _size(size)
    , _anchor(anchor)
{}

Floor::Floor(const Floor& other)
    : _size(other._size)
    , _anchor(other._anchor)
    , _flats(other._flats)
    , _isEmpty(other._isEmpty)
{}

Floor::Floor(Floor&& other)
    : _size(other._size)
    , _anchor(other._anchor)
    , _flats(std::move(other._flats))
    , _isEmpty(other._isEmpty)
{}

bool Floor::addFlat(const Flat& flat)
{
    int position = flat.getPosition().first;
    int size = flat.getSize().first;

    int i = 0;
    while( i < (int)_flats.size() && _flats[i].getPosition().first < position)
        ++i;

    if( i == 0 )
    {
        if( position - size/2-1 < 0 )
            return false;
    }
    else
    {
        int prevPos = _flats[i-1].getPosition().first;
        int prevSize = _flats[i-1].getSize().first;

        if( prevPos + prevSize/2 + 5 > position - size/2 )
            return false;
    }

    if( i == (int)_flats.size() )
    {
        if( position + size/2+1 > _size.first )
            return false;
    }
    else
    {
        int nextPos = _flats[i].getPosition().first;
        int nextSize = _flats[i].getSize().first;

        if( nextPos - nextSize/2 - 5 > position + size/2 )
            return false;
    }

    _flats.insert(_flats.begin() + i, flat);
    if( _isEmpty && flat.getMen() )
        _isEmpty = false;

    return true;
}

int Floor::getHeight() const
{
    return _size.second;
}

int Floor::getWidth() const
{
    return _size.first;
}

int Floor::getAnchor() const
{
    return _anchor;
}

const std::vector<Flat>& Floor::getFlats() const
{
    return _flats;
}

bool Floor::hasMen()
{
    if( _isEmpty )
        return false;

    for( const auto& flat : _flats )
        if( flat.getMen() )
            return true;

    _isEmpty = true;
    return false;
}


