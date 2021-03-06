/* effect.cpp
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

#include "effect.hpp"
#include "globals.hpp"
#include "app.hpp"

namespace yakblt {
	Effect::Effect (int lifespan) :
		_lifespan(lifespan),
		_isDead(false)
	{
	}

	Effect::~Effect () {
	}

	int Effect::getLifespan () {
		return _lifespan;
	}

	bool Effect::isDead () {
		return _isDead;
	}

	void Effect::kill () {
		makeDead();
		removeFromWorld();
		app().addToDelete(*this);
	}

	void Effect::removeFromWorld () {
		app().world().removeEffect(*this);
	}

	void Effect::makeDead () {
		ASSERT(!_isDead)
		_isDead = true;
		dead();
	}

	void Effect::dead () {
	}

	void Effect::onUpdate (float delta) {
		if (_lifespan > 0) {
			_lifespan--;
		} else if (_lifespan == 0) {
			kill();
		}
	}
}
