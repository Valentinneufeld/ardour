/*
	Copyright (C) 2006,2007 John Anderson

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#include "controls.h"
#include "types.h"
#include "mackie_midi_builder.h"

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Mackie;
using namespace std;

void Group::add( Control & control )
{
	_controls.push_back( &control );
}

Strip::Strip( const std::string & name, int index )
	: Group( name )
	, _solo( 0 )
	, _recenable( 0 )
	, _mute( 0 )
	, _select( 0 )
	, _vselect( 0 )
	, _fader_touch( 0 )
	, _vpot( 0 )
	, _gain( 0 )
	, _index( index )
{
}

Control::Control( int id, int ordinal, std::string name, Group & group )
: _id( id )
, _ordinal( ordinal )
, _name( name )
, _group( group )
, _in_use_timeout( 250 )
{
}

/**
 generated with

controls[1].each do |x|
  puts <<EOF
#{x.class.name} & Strip::#{x.name}()
{
	if ( _#{x.name} == 0 )
		throw MackieControlException( "#{x.name} is null" );
	return *_#{x.name};
}
EOF
end
*/
Fader & Strip::gain()
{
	if ( _gain == 0 )
		throw MackieControlException( "gain is null" );
	return *_gain;
}
Pot & Strip::vpot()
{
	if ( _vpot == 0 )
		throw MackieControlException( "vpot is null" );
	return *_vpot;
}
Button & Strip::recenable()
{
	if ( _recenable == 0 )
		throw MackieControlException( "recenable is null" );
	return *_recenable;
}
Button & Strip::solo()
{
	if ( _solo == 0 )
		throw MackieControlException( "solo is null" );
	return *_solo;
}
Button & Strip::mute()
{
	if ( _mute == 0 )
		throw MackieControlException( "mute is null" );
	return *_mute;
}
Button & Strip::select()
{
	if ( _select == 0 )
		throw MackieControlException( "select is null" );
	return *_select;
}
Button & Strip::vselect()
{
	if ( _vselect == 0 )
		throw MackieControlException( "vselect is null" );
	return *_vselect;
}
Button & Strip::fader_touch()
{
	if ( _fader_touch == 0 )
		throw MackieControlException( "fader_touch is null" );
	return *_fader_touch;
}

bool Control::in_use() const
{
	return _in_use;
}

Control & Control::in_use( bool rhs )
{
	_in_use = rhs;
	return *this;
}

ostream & Mackie::operator << ( ostream & os, const Mackie::Control & control )
{
	os << typeid( control ).name();
	os << " { ";
	os << "name: " << control.name();
	os << ", ";
	os << "id: " << "0x" << setw(4) << setfill('0') << hex << control.id() << setfill(' ');
	os << ", ";
	os << "type: " << "0x" << setw(2) << setfill('0') << hex << control.type() << setfill(' ');
	os << ", ";
	os << "raw_id: " << "0x" << setw(2) << setfill('0') << hex << control.raw_id() << setfill(' ');
	os << ", ";
	os << "ordinal: " << dec << control.ordinal();
	os << ", ";
	os << "group: " << control.group().name();
	os << " }";
	
	return os;
}
