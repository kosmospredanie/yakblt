/* unit.hpp
 *
 * Copyright (C) 2019-2020 Космическое П. <kosmospredanie@yandex.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __YAKBLT_UNIT_H__
#define __YAKBLT_UNIT_H__

#include "gridentity.hpp"
#include "scripter.hpp"
#include "event.hpp"

namespace yakblt {
	class Bullet;

	class Unit : public GridEntity<Unit> {
	public:
		Unit (Collidable &collidable);
		virtual ~Unit () override;

		virtual bool isHostileTo (Bullet &bullet) = 0;
		/**
		 * Will be called when the unit collides with a **hostile** bullet.
		 *
		 * @param[in] bullet The bullet
		 */
		virtual void hit (Bullet &bullet);
		bool isDead ();
		/**
		 * Kills this unit.
		 *
		 * Default implementation: Makes this dead, remove it
		 * from the world, and delete it.
		 */
		virtual void kill ();
		/**
		 * After this method, you have to delete this object manually if it
		 * has been allocated using operator new.
		 */
		void removeFromWorld ();

		Event<Unit&> &onDead ();

	protected:
		/**
		 * All methods overriding this method must call their base method.
		 */
		virtual void onUpdate (float delta) override;
		virtual void control ();
		virtual void detectCollisions ();
		virtual void restrainActionArea ();
		void makeDead ();
		virtual void dead ();

	private:
		bool _isDead;
		Event<Unit&> _onDead;
	};
}

#endif
