/*
 * Copyright (C) 2011-2016 Paul Davis <paul@linuxaudiosystems.com>
 * Copyright (C) 2020 Robin Gareus <robin@gareus.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _libardour_pan_contols_h_
#define _libardour_pan_contols_h_

#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "evoral/Parameter.h"
#include "ardour/types.h"

namespace ARDOUR {

class Panner;
class AutomationControl;
class PanControllable;

class LIBARDOUR_API PanControls
{
public:
	virtual ~PanControls () {}

	virtual boost::shared_ptr<AutomationControl> const& pan_azimuth_control () = 0;
	virtual boost::shared_ptr<AutomationControl> const& pan_elevation_control () = 0;
	virtual boost::shared_ptr<AutomationControl> const& pan_width_control () = 0;
	virtual boost::shared_ptr<AutomationControl> const& pan_frontback_control () = 0;
	virtual boost::shared_ptr<AutomationControl> const& pan_lfe_control () = 0;

	/* used by panners to set panner specific defaults
	 * if there is no prior state */
	virtual bool has_state() const = 0;

	/* set automation states of all controls */
	virtual void set_automation_state (AutoState) = 0;
	virtual AutoState automation_state() const = 0;
	virtual bool touching() const = 0;

	virtual const std::set<Evoral::Parameter>& what_can_be_automated() const = 0;

	void set_panner(boost::shared_ptr<Panner> p) {
		_panner = p;
	}

protected:
	boost::weak_ptr<Panner> _panner;

private:
	friend PanControllable;
	/* used only by PanControllable
	 * to clamp and format values */
	boost::shared_ptr<Panner> panner() const { return _panner.lock(); }

};

} // namespace

#endif
