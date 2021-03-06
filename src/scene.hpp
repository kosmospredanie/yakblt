/* scene.hpp
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

#ifndef __YAKBLT_SCENE_H__
#define __YAKBLT_SCENE_H__

#include "node.hpp"
#include "event.hpp"

namespace yakblt {
	class Scene {
	public:
		Scene ();
		virtual ~Scene ();
		/**
		 * Called just after this scene becomes the current scene.
		 *
		 * @param[in] oldScene The old scene
		 */
		virtual void show (Scene *oldScene);
		/**
		 * Called just before this scene is replaced by another scene.
		 *
		 * @param[in] newScene The new scene
		 */
		virtual void hide (Scene *newScene);
		virtual void update (float delta);
		virtual void draw (RenderTarget &target);
		Event<sf::Event> &onSfmlEvent ();

	private:
		Event<sf::Event> _onSfmlEvent;
	};
}

#endif
